# 4. Encoding and Evolution

- [4. Encoding and Evolution](#4-encoding-and-evolution)
  - [Formats for Encoding Data](#formats-for-encoding-data)
    - [Language-Specific Formats](#language-specific-formats)
    - [JSON, XML, and Binary Variants](#json-xml-and-binary-variants)
      - [Binary encoding](#binary-encoding)
    - [Thrift and Protocol Buffers](#thrift-and-protocol-buffers)
      - [Field tags and schema evolution](#field-tags-and-schema-evolution)

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

>>>>> progress
