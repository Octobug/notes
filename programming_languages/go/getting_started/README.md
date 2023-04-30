# Getting Started

> <https://go.dev/doc/>

- [Getting Started](#getting-started)
  - [Download and install](#download-and-install)
    - [Managing Go installations](#managing-go-installations)
  - [Tutorial: Get started with Go](#tutorial-get-started-with-go)
    - [pkg source](#pkg-source)
  - [Tutorial: Create a Go Module](#tutorial-create-a-go-module)
    - [Start a module that others can use](#start-a-module-that-others-can-use)
      - [Package](#package)
      - [Module](#module)
      - [Function](#function)
    - [Call your code from another module](#call-your-code-from-another-module)
      - [Local Module](#local-module)
      - [Installing Module](#installing-module)
    - [Return and handle an error](#return-and-handle-an-error)
    - [Return a random greeting](#return-a-random-greeting)
      - [Slice](#slice)
      - [`init()`](#init)
    - [Return greetings for multiple people](#return-greetings-for-multiple-people)
    - [Add a test](#add-a-test)
    - [Compile and install the application](#compile-and-install-the-application)
  - [Tutorial: Getting started with multi-module workspaces](#tutorial-getting-started-with-multi-module-workspaces)
  - [Tutorial: Developing a RESTful API with Go and Gin](#tutorial-developing-a-restful-api-with-go-and-gin)

## Download and install

> <https://go.dev/doc/install>

### Managing Go installations

> <https://go.dev/doc/manage-install>

## Tutorial: Get started with Go

> <https://go.dev/doc/tutorial/getting-started>

- the [hello](getting_started/hello/) project
- `go.mod`: manage dependencies
  - `go mod init`: initialize a go project
  - `go mod tidy`: automatically manage modules

### pkg source

> <https://pkg.go.dev/>

## Tutorial: Create a Go Module

### Start a module that others can use

> <https://go.dev/doc/tutorial/create-module>

In a `module`, one or more related `packages` are included for a discrete and
useful set of functions.

#### Package

- `package main`: In Go, code executed as an application must be in a `main`
package.

#### Module

- Go code is grouped into packages, and packages are grouped into modules.
  That means `module` > `package`.
- Dependencies including Go version are specified at the module level.

```sh
go get .
go mod download
```

> <https://stackoverflow.com/a/66584699/7267801>
>
> Your module's `go.mod` file records which versions of dependencies it
> requires. The source code for those dependencies is stored in a local cache.
>
> `go get` updates the requirements listed in your `go.mod` file. It also
> ensures that those requirements are self-consistent, and adds new
> requirements as needed so that every package imported by the packages you
> named on the command line is provided by some module in your requirements.
>
> As a *side-effect of updating and adding requirements*, go get also downloads
> the modules containing the named packages (and their dependencies) to the
> local module cache.
>
> In contrast, `go mod download` *does not* add new requirements or update
> existing requirements. (At most, it will ensure that the existing
> requirements are self-consistent, which can occur if you have hand-edited the
> `go.mod` file.) It only downloads either the specific module versions you've
> requested (if you requested specific versions), or the versions of modules
> that appear in your requirements.

#### Function

```go
func Hello(name string) string {}
     -----      ------  ------
//  Function   Parameter Return
//  name       type      type
```

- A function whose name starts with a **capital letter** can be called by a
  function not in the same package. This is known in Go as an exported name.
- The `:=` operator is a shortcut for declaring and initializing a variable in
  one line. Go uses the value on the right to determine the variable's type.

  It's equivalent to:

  ```go
  var message string
  message = fmt.Sprintf("Hi, %v. Welcome!", name)
  ```

### Call your code from another module

> <https://go.dev/doc/tutorial/call-module-code>

#### Local Module

For module that has not been published yet, we could use it in local by
replacing module path.

```sh
go mod edit -replace example.com/greetings=../greetings
```

#### Installing Module

Then use

```sh
go mod tidy
```

to install modules.

```mod
replace example.com/greetings => ../greetings
require example.com/greetings v0.0.0-00010101000000-000000000000
```

- the `replace` directive
- the `require` directive

The number following the module path is a *pseudo-version number* -- a
generated number used in place of a semantic version number (which the module
doesn't have yet).

### Return and handle an error

> <https://go.dev/doc/tutorial/handle-errors>

```go
func Hello(name string) (string, error) {
    // If no name was given, return an error with a message.
    if name == "" {
        return "", errors.New("empty name")
    }
}
```

- Any Go function can return multiple values.
- `log.Fatal()`: print the error and stop the program.

### Return a random greeting

> <https://go.dev/doc/tutorial/random-greeting>

#### Slice

- A slice is like an array, except that its size changes dynamically as you add
  and remove items.
- `[]`: slice, omiting its size in the brackets tells Go that the size of the
  array underlying the slice can be dynamically changed

```go
[]string{
  "a",
  "b"
}
```

#### `init()`

- Go executes init functions automatically at program startup, after global
- variables have been initialized.

### Return greetings for multiple people

> <https://go.dev/doc/tutorial/greetings-multiple-people>

- In Go, you initialize a `map` with the following syntax:
  `make(map[key-type]value-type)`
- `range iterables` returns two values:
  - the index of the current item
  - a **copy** of the item's value
- `_`: the Go blank identifier

### Add a test

> <https://go.dev/doc/tutorial/add-a-test>

- file naming convention: `*_test.go`
- case naming convention: `func TestName(t *testing.T)`
  - the parameter is a `pointer` to the `testing.T` type, we use its methods for
    reporting and logging.
- `go test`: to execute the tests

### Compile and install the application

> <https://go.dev/doc/tutorial/compile-install>

- `go build`: compiles the packages, along with their dependencies, generates an
  executable
- `go install`: compiles and installs the packages
- `go list -f '{{.Target}}'`: find out where the go command will install the
  current package
- `go env -w GOBIN=/path/to/your/bin`: customize go installation target
  directory

## Tutorial: Getting started with multi-module workspaces

> <https://go.dev/doc/tutorial/workspaces>

## [Tutorial: Developing a RESTful API with Go and Gin](developing_a_restful_api_with_go_and_gin)
