# 4. Encoding and Evolution

- [4. Encoding and Evolution](#4-encoding-and-evolution)
  - [Formats for Encoding Data](#formats-for-encoding-data)
    - [Language-Specific Formats](#language-specific-formats)
    - [JSON, XML, and Binary Variants](#json-xml-and-binary-variants)
      - [Binary encoding](#binary-encoding)
    - [Thrift and Protocol Buffers](#thrift-and-protocol-buffers)
      - [Field tags and schema evolution](#field-tags-and-schema-evolution)
      - [Datatypes and schema evolution](#datatypes-and-schema-evolution)
    - [Avro](#avro)
      - [The writer's schema and the reader's schema](#the-writers-schema-and-the-readers-schema)
      - [Schema evolution rules](#schema-evolution-rules)
      - [But what is the writer's schema?](#but-what-is-the-writers-schema)
      - [Dynamically generated schemas](#dynamically-generated-schemas)
      - [Code generation and dynamically typed languages](#code-generation-and-dynamically-typed-languages)
    - [The Merits of Schemas](#the-merits-of-schemas)
  - [Modes of Dataflow](#modes-of-dataflow)
    - [Dataflow Through Databases](#dataflow-through-databases)
      - [Different values written at different times](#different-values-written-at-different-times)
      - [Archival storage](#archival-storage)
    - [Dataflow Through Services: REST and RPC](#dataflow-through-services-rest-and-rpc)

In a large application, code changes often cannot happen instantaneously:

With server-side applications, it is better to perform a *rolling upgrade*,
deploying the new version to a few nodes at a time.

## Formats for Encoding Data

- In memory, data is kept in objects, structs, lists, arrays, has tables, trees,
  and so on.
- When data is written to a file or sent over the network, they needs to be
  encoded as some kind of self-contained sequence of bytes.

The translation from the in-memory representation to a byte sequence is called
*encoding* (also called *serialization*, or *marshalling*). And the reverse is
called *decoding* (*parsing*, *deserialization*, *unmarshalling*).

### Language-Specific Formats

### JSON, XML, and Binary Variants

Subtle problems with JSON, XML, and CSV:

- In XML and CSV, you cannot distinguish between a number and a string consists
  of digits. JSON doesn't distinguishes integer and float. Numbers greater than
  $2^{53}$ cannot be exactly represented in an IEEE 754 double-precision
  floating-point number.
- JSON and XML don't support binary strings (sequences of bytes without a
  character encoding).
- CSV does not have any schema, so it is up to the application to define the
  meaning of each row and column.

#### Binary encoding

Popular binary encodings for JSON and XML:

- JSON
  - MessagePack
  - BSON
  - BJSON
  - UBJSON
  - BISON
  - Smile
- XML
  - WBXML
  - Fast Infoset

Those who keep the JSON/XML data model unchanged don't prescribe a schema, so
they need to include all the object field names within the encoded data.

### Thrift and Protocol Buffers

Thrift and Protocol Buffers are based on the same principle. Both of them
require a schema for any data that is encoded.

Thrift has two different binary encoding formats called *BinaryProtocol* and
*CompactProtocol*.

Protocol Buffers has one binary encoding format.

Each field of their schema was marked either `required` or `optional`, but this
information is not encoded in the binary data. They are used to enable a runtime
check at those fields.

#### Field tags and schema evolution

*schema evolution*: schemas inevitably need to change over time.

Compatibility is a relationship between one process that encodes the data, and
another process that decodes it.

How do Thrift and Protocol Buffers handle schema changes?

- Forward compatibility: old code can read records that were written by new
  code:
  - You can change the name of a field in the schema, since the encoded data
    never refers to field names, but you cannot change a field's tag, since
    that would make all existing encoded data invalid.
  - You can add new fields to the schema, provided that you give each field a
    new tag number. If old code tries to read data written by new code,
    including a new field with tag number it doesn't recognize, it can simply
    ignore that field.
  - The datatype annotation allows the parser to determine how many bytes it
    needs to skip.
  - A required field cannot be removed, because the check would fail if old code
    reads records written by new code.
- Backward compatibility: new code can read records that were written by old
  code:
  - As long as each field has a unique tag number, new code can always read old
    data.
  - If you add a new field, you cannot make it required or the check would fail
    if new code read data written by old code. A new field must be optional or
    have a default value.
  - You can never use the same tag number again, because you might still have
    data including the old tag number which must be ignored by new code.

#### Datatypes and schema evolution

Changing the datatype of a field is possible, but there is a risk that values
will lose precision or get truncated.

Protocol Buffers doesn't have a list or array datatype, but instead has a
`repeated` marker for fields, which is a third option alongside `required` and
`optional`. Encoding of a `repeated` field is that the same field tag appears
multiple times in the record. This has the nice effect that it's okay to change
an `optional` field into a `repeated` field. Old code reading new data sees only
the last element of the list.

Thrift has a list datatype, so it has the advantage of supporting nested lists.

### Avro

Avro has two schema languages: Avro IDL intended for human editing, and JSON is
more easily machine-readable.

Avro doesn't use tag numbers for fields in the schema.

To parse the binary data, it goes through the fields in the order that they
appear in the schema and use the schema to tell what the datatype or each field
is. This means that the binary data can only be decoded correctly if the code
reading the data is using the ***exact same schema*** as the code that wrote the
data.

#### The writer's schema and the reader's schema

The key idea with Avro is that the writer's schema and the reader's schema don't
have to be the same -- they only need to be compatible.

When data is decoded, the Avro library resolves the difference by looking at the
writer's schema and the reader's schema side by side and translating the data
from the writer's schema into the reader's schema.

- If the code reading the data encounters a field that appears in the writer's
  schema but not in the reader's schema, it is ignored. It the code reading the
  data expects some field, but the writer's schema does not contain a field of
  that name, it is filled in with a default value declared in the reader's
  schema.

#### Schema evolution rules

With Avro,

- Forward compatibility: you can have a new version of the schema as writer and
  an old version of the schema as reader.
- Backward compatibility: you can have a new version of the schema as reader and
  an old version as writer.

To maintain compatibility, only adding or removing a field that has a default
value are allowed.

- If you add a field that has no default value, new readers will break when
  reading old data, breaking backward compatibility.
- If you remove a field that has no default value, old readers will break when
  reading new data, breaking forward compatibility.

You can use `null` as a default value if it is the first branch of the `union`
type.

- Changing the datatype of a field is possible, provided that Avro can convert
  the type.
- Changing the name of a field is possible, the reader's schema can contain
  aliases for field names, so it can match an old writer's schema. This means
  that changing a field name is backward compatible but not forward compatible.
- Adding a branch to a union type is backward compatible but not forward
  compatible.

#### But what is the writer's schema?

How does the reader know the writer's schema with which a particular piece of
data was encoded?

The answer depends on the context in which Avro is being used:

- **Large file with lots of records**: the writer of that file can just include
  the writer's schema once at the begining of the file.
- **Database with individually written records**: In a database, the simplest
  solution is to include a version number at the beginning of every encoded
  record, and to keep a list of schema versions in the database.
  - A reader first fetch a record, extract the version number, and then fetch
    the writer's schema for that version from the database.
- **Sending records over a network connection**: Two sides first negotiate the
  schema version on connection setup and then use it for the lifetime of the
  connection. (Avro RPC protocol works like this.)

#### Dynamically generated schemas

Avro's schema doesn't contain any tag numbers. This makes Avro friendlier to
*dynamically generated* schemas.

For example, you have a relational database whose contents is to be dumped to a
file. If the database schema changes, you can just generate a new Avro schema
from the updated database schema.

By contrast, if you were using Thrift or Protocol Buffers for this purpose, the
field tags would likely have to assigned by hand: Every time the database schema
changes, an administrator would have to manually update the mapping from
database column names to field tags. (Automating this is possible, but the
previously used tag numbers must not be assigned.)

#### Code generation and dynamically typed languages

In dynamically typed languages, there is not much point in generating code,
since there is no compile-time type checker to satisfy.

### The Merits of Schemas

- They can be much more compact than the various "binary JSON" variants.
- The schema is a valueable form of documentation, and because the schema is
  required for decoding, you can be sure that it is up to date. Whereas manually
  maintained documentation may easily diverge from reality.
- Keeping a database of schemas allows you to check forward and backward
  compatibility of schema changes, before anything is deployed.
- For users of statically typed programming languages, the ability to generate
  code from the schemas is useful.

## Modes of Dataflow

- Via databases
- Via service calls
- Via asynchronous message passing

### Dataflow Through Databases

There is a special case: you add a field to a record schema, and the new code
writes a value for that new field to the database. Subsequently, the old code
reads the record, updates it, and writes it back. in this situation, the
desirable behavior for the old code is to keep the new field intact.

#### Different values written at different times

Rewriting data into a new schema is possible, but it's an expensive thing to do
on a large dataset, so most databases avoid it if possible.

#### Archival storage

In this case, the data dump will typically be encoded using the latest schema.

As the data dump is written in one go and is thereafter immutable, formats like
Avro object container files are a good fit.

### Dataflow Through Services: REST and RPC

>>>>> progress
