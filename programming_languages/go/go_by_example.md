# Go by Example

> <https://gobyexample.com/>

- [Go by Example](#go-by-example)
  - [Interfaces](#interfaces)
  - [Channels](#channels)
  - [Context](#context)

## Interfaces

> <https://gobyexample.com/interfaces>

*Interfaces* are named collections of method signatures.

```go
package main
import (
    "fmt"
    "math"
)

// Here’s a basic interface for geometric shapes.
type geometry interface {
    area() float64
    perim() float64
}

// For our example we’ll implement this interface on rect and circle types.
type rect struct {
    width, height float64
}

type circle struct {
    radius float64
}

// To implement an interface in Go, we just need to implement all the methods
// in the interface.
func (r rect) area() float64 {
    return r.width * r.height
}

func (r rect) perim() float64 {
    return 2*r.width + 2*r.height
}

// The implementation for circles.
func (c circle) area() float64 {
    return math.Pi * c.radius * c.radius
}

func (c circle) perim() float64 {
    return 2 * math.Pi * c.radius
}

// If a variable has an interface type, then we can call methods that are in
// the named interface. Here’s a generic measure function taking advantage of
// this to work on any geometry.
func measure(g geometry) {
    fmt.Println(g)
    fmt.Println(g.area())
    fmt.Println(g.perim())
}
func main() {
    r := rect{width: 3, height: 4}
    c := circle{radius: 5}

    // The circle and rect struct types both implement the geometry interface
    // so we can use instances of these structs as arguments to measure.
    measure(r)
    measure(c)
}

```sh
$ go run interfaces.go
{3 4}
12
14
{5}
78.53981633974483
31.41592653589793
```

## Channels

> <https://gobyexample.com/channels>

Channels are the pipes that connect concurrent goroutines. You can send values
into channels from one goroutine and receive those values into another
goroutine.

```go
package main

import "fmt"

func main() {
    // Create a new channel with make(chan val-type).
    // Channels are typed by the values they convey.
    messages := make(chan string)

    // Send a value into a channel using the channel <- syntax.
    go func() { messages <- "ping" }()

    // The <-channel syntax receives a value from the channel.
    msg := <-messages
    fmt.Println(msg)
}
```

By default sends and receives block until both the sender and receiver are
ready.

## Context

> <https://gobyexample.com/context>

A `Context` carries deadlines, cancellation signals, and other request-scoped
values across API boundaries and goroutines.

```go
package main
import (
    "fmt"
    "net/http"
    "time"
)

func hello(w http.ResponseWriter, req *http.Request) {
    // A context.Context is created for each request by the net/http machinery,
    // and is available with the Context() method.

    ctx := req.Context()
    fmt.Println("server: hello handler started")
    defer fmt.Println("server: hello handler ended")

    // While working, keep an eye on the context’s Done() channel for a signal that we should cancel the work and return as soon as possible.
    select {
    case <-time.After(10 * time.Second):
        fmt.Fprintf(w, "hello\n")
    case <-ctx.Done():
    // The context’s Err() method returns an error that explains why the Done()
    // channel was closed.
        err := ctx.Err()
        fmt.Println("server:", err)
        internalError := http.StatusInternalServerError
        http.Error(w, err.Error(), internalError)
    }
}

func main() {
    http.HandleFunc("/hello", hello)
    http.ListenAndServe(":8090", nil)
}
```

Run the server in the background.

```sh
$ go run context-in-http-servers.go &
# Simulate a client request to /hello, hitting Ctrl+C shortly after starting to
# signal cancellation.

$ curl localhost:8090/hello
server: hello handler started
^C
server: context canceled
server: hello handler ended
```
