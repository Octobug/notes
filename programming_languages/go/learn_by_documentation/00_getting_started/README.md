# Getting Started

> <https://golang.org/doc/#getting-started>

## Managing Go installations

> <https://golang.org/doc/manage-install#installing-multiple>

## pkg source

> <https://pkg.go.dev/>

## Function

> A function whose name startse with a capital letter can be called by a
> function not in the same package. This is known in Go as an exported name.

```go
func Hello(name string) string {}
     -----      ------  ------
   Function   Parameter Return
   name       type      type
```

## Package

`main` package: In Go, code executed as an application must be in a `main`
package.

## Module

> Go code is grouped into packages, and packages are grouped into modules.

That means `module` > `package`.

### Installing Module

```shell
go get .
go mod download
go mod tidy
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

### Local Module

For module that has not been published yet, we could use it in local by
replacing module path.

```shell
# e.g.
go mod edit -replace example.com/greetings=../greetings
```

## Slice

> A slice is like an array, except that its size changes dynamically as you
> add and remove items.

```go
[]string{
  "a",
  "b"
}
```

- `[]`: slice, omiting its size in the brackets tells Go that the size of the
  array underlying the slice can be dynamically changed

## `init()`

> Go executes init functions automatically at program startup, after global
> variables have been initialized.

## map

> In Go, you initialize a map with the following syntax:
> `make(map[key-type]value-type)`.

## Testing

- file naming convention: `*_test.go`
- case naming convention: `func TestName(t *testing.T)`

## Compile and install

- `go build`: compiles the packages, along with their dependencies, generate an
  executable
- `go list -f '{{.Target}}'`: find out where the go command will install the
  current package
- `go env -w GOBIN=/path/to/your/bin`: custom go installation target
- `go install`: install the executable

## Struct

```go
// `json:"id"` specifies what a field's name should be when the struct's cotents
//  are serialized into JSON
type album struct {
    ID     string  `json:"id"`
    Title  string  `json:"title"`
    Artist string  `json:"artist"`
    Price  float64 `json:"price"`
}
```
