# 7. Error management

## 7.1 #48: Panicking

Once a panic is triggered, it continues up the call stack until either the current goroutine has returned or `panic` is caught with `recover`:

```go
func main() {
    defer func() {
        if r := recover(); r != nil {
            fmt.Println("recover", r)
        }
    }()

    f()
}

func f() {
    fmt.Println("a")
    panic("foo")
    fmt.Println("b")
}
```

⚠️ Calling `recover()` to capture a goroutine panicking is only useful inside a `defer` function; otherwise, the function would return `nil` and have no other effect. This is because `defer` functions are also executed when the surrounding function panics.

e.g.,

- Compiling a `regexp` that must be successful (using `MustCompile`).
- ...

In most other cases, error management should be done with a function that returns a proper `error` type as the last return argument.

## 7.2 #49: Ignoring when to wrap an error
