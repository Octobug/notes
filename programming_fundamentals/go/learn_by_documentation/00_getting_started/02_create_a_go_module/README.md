# Tutorial: Create a Go module

> <https://golang.org/doc/tutorial/create-module>

## Module

> Go code is grouped into packages, and packages are grouped into modules.

That means `module` > `package`.

## Function

> A function whose name startse with a capital letter can be called by a
> function not in the same package. This is known in Go as an exported name.

```go
func Hello(name string) string {}
     -----      ------  ------
    Function  Parameter Return
    name         type    type
```
