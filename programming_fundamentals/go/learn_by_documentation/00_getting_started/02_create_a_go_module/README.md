# Tutorial: Create a Go module

> * [Tutorial: Create a Go module](https://golang.org/doc/tutorial/create-module)
> * [Call your code from another module](https://golang.org/doc/tutorial/call-module-code)

## Function

> A function whose name startse with a capital letter can be called by a
> function not in the same package. This is known in Go as an exported name.

```go
func Hello(name string) string {}
     -----      ------  ------
   Function   Parameter Return
   name      type      type
```

## Package

`main` package: In Go, code executed as an application must be in a `main`
package.

## Module

> Go code is grouped into packages, and packages are grouped into modules.

That means `module` > `package`.

### Installing Module

```shell
go mod tidy
```

### Local Module

For module that has not been published yet, we could use it in local by
replacing module path.

```shell
# e.g.
go mod edit -replace example.com/greetings=../greetings
```
