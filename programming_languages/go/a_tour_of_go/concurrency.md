# Concurrency

- [Concurrency](#concurrency)
  - [Goroutines](#goroutines)
  - [Channels](#channels)
  - [Buffered Channels](#buffered-channels)
  - [Range and Close](#range-and-close)
  - [Select](#select)
  - [Default Selection](#default-selection)
  - [Exercise: Equivalent Binary Trees](#exercise-equivalent-binary-trees)
  - [sync.Mutex](#syncmutex)
  - [Exercise: Web Crawler](#exercise-web-crawler)

## Goroutines

```go
package main

import (
  "fmt"
  "time"
)

func say(s string) {
  for i := 0; i < 5; i++ {
    time.Sleep(100 * time.Millisecond)
    fmt.Println(s)
  }
}

func main() {
  go say("world")
  say("hello")
}
```

A `goroutine` is a lightweight thread managed by the Go runtime.

```go
go f(x, y, z)
```

starts a new goroutine running

```go
f(x, y, z)
```

The evaluation of `f`, `x`, `y`, and `z` happens in the current goroutine and
the execution of `f` happens in the new goroutine.

Goroutines run in the same address space, so access to shared memory must be
synchronized. The `sync` package provides useful primitives, although you won't
need them much in Go as there are other primitives.

## Channels

```go
package main

import "fmt"

func sum(s []int, c chan int) {
  sum := 0
  for _, v := range s {
    sum += v
  }
  c <- sum // send sum to c
}

func main() {
  s := []int{7, 2, 8, -9, 4, 0}

  c := make(chan int)
  go sum(s[:len(s)/2], c)
  go sum(s[len(s)/2:], c)
  x, y := <-c, <-c // receive from c

  fmt.Println(x, y, x+y)
}
```

Channels are a typed conduit through which you can send and receive values with
the channel operator, `<-`.

```go
ch <- v    // Send v to channel ch.
v := <-ch  // Receive from ch, and
           // assign value to v.
```

(The data flows in the direction of the arrow.)

Like maps and slices, channels must be created before use:

```go
ch := make(chan int)
```

By default, sends and receives block until the other side is ready. This allows
goroutines to synchronize without explicit locks or condition variables.

The example code sums the numbers in a slice, distributing the work between two
goroutines. Once both goroutines have completed their computation, it
calculates the final result.

## Buffered Channels

```go
package main

import "fmt"

func main() {
  ch := make(chan int, 2)
  ch <- 1
  ch <- 2
  fmt.Println(<-ch)
  fmt.Println(<-ch)
}
```

Channels can be *buffered*. Provide the buffer length as the second argument to
`make` to initialize a buffered channel:

```go
ch := make(chan int, 100)
```

Sends to a buffered channel block only when the buffer is full. Receives block
when the buffer is empty.

Overfilling the buffer will cause a fatal error:

```log
fatal error: all goroutines are asleep - deadlock!

goroutine 1 [chan send]:
main.main()
  /tmp/sandbox246315059/prog.go:9 +0x5c
```

## Range and Close

```go
package main

import (
  "fmt"
)

func fibonacci(n int, c chan int) {
  x, y := 0, 1
  for i := 0; i < n; i++ {
    c <- x
    x, y = y, x+y
  }
  close(c)
}

func main() {
  c := make(chan int, 10)
  go fibonacci(cap(c), c)
  for i := range c {
    fmt.Println(i)
  }
}
```

A sender can `close` a channel to indicate that no more values will be sent.
Receivers can test whether a channel has been closed by assigning a second
parameter to the receive expression: after

```go
v, ok := <-ch
```

`ok` is `false` if there are no more values to receive and the channel is
closed.

The loop `for i := range c` receives values from the channel repeatedly until
it is closed.

**Note**: Only the sender should close a channel, never the receiver. Sending
on a closed channel will cause a panic.

**Another note**: Channels aren't like files; you don't usually need to close
them. Closing is only necessary when the receiver must be told there are no
more values coming, such as to terminate a `range` loop.

## Select

```go
package main

import "fmt"

func fibonacci(c, quit chan int) {
  x, y := 0, 1
  for {
    select {
    case c <- x:
      x, y = y, x+y
    case <-quit:
      fmt.Println("quit")
      return
    }
  }
}

func main() {
  c := make(chan int)
  quit := make(chan int)
  go func() {
    for i := 0; i < 10; i++ {
      fmt.Println(<-c)
    }
    quit <- 0
  }()
  fibonacci(c, quit)
}
```

The `select` statement lets a goroutine wait on multiple communication
operations.

A `select` blocks until one of its cases can run, then it executes that case.
It chooses one at random if multiple are ready.

## Default Selection

```go
package main

import (
  "fmt"
  "time"
)

func main() {
  tick := time.Tick(100 * time.Millisecond)
  boom := time.After(500 * time.Millisecond)
  for {
    select {
    case <-tick:
      fmt.Println("tick.")
    case <-boom:
      fmt.Println("BOOM!")
      return
    default:
      fmt.Println("    .")
      time.Sleep(50 * time.Millisecond)
    }
  }
}
```

The `default` case in a `select` is run if no other case is ready.

Use a `default` case to try a send or receive without blocking:

```go
select {
case i := <-c:
    // use i
default:
    // receiving from c would block
}
```

## Exercise: Equivalent Binary Trees

There can be many different binary trees with the same sequence of values
stored in it. For example, here are two binary trees storing the sequence
1, 1, 2, 3, 5, 8, 13.

A function to check whether two binary trees store the same sequence is quite
complex in most languages. We'll use Go's concurrency and channels to write a
simple solution.

This example uses the `tree` package, which defines the type:

```go
type Tree struct {
    Left  *Tree
    Value int
    Right *Tree
}
```

1. Implement the `Walk` function.
2. Test the `Walk` function.

    The function `tree.New(k)` constructs a randomly-structured (but always
    sorted) binary tree holding the values `k`, `2k`, `3k`, ..., `10k`.

    Create a new channel `ch` and kick off the walker:

    ```go
    go Walk(tree.New(1), ch)
    ```

    Then read and print 10 values from the channel. It should be the numbers 1,
    2, 3, ..., 10.

3. Implement the `Same` function using `Walk` to determine whether `t1` and `t2`
   store the same values.
4. Test the `Same` function.

    `Same(tree.New(1), tree.New(1))` should return `true`, and
    `Same(tree.New(1), tree.New(2))` should return `false`.

```go
package main

import (
  "fmt"
  "golang.org/x/tour/tree"
)

// Walk walks the tree t sending all values
// from the tree to the channel ch.
func Walk(t *tree.Tree, ch chan int) {
  var walker func(t *tree.Tree)

  walker = func (t *tree.Tree) {
      if (t == nil) {
          return
      }
      walker(t.Left)
      ch <- t.Value
      walker(t.Right)
  }

  walker(t)
  close(ch)
}

// Same determines whether the trees
// t1 and t2 contain the same values.
func Same(t1, t2 *tree.Tree) bool {
  ch1, ch2 := make(chan int), make(chan int)

    go Walk(t1, ch1)
    go Walk(t2, ch2)

    for {
        v1,ok1 := <- ch1
        v2,ok2 := <- ch2

        if v1 != v2 || ok1 != ok2 {
            return false
        }

        if !ok1 {
            break
        }
    }

    return true
}

func main() {
  ch := make(chan int)

  go Walk(tree.New(1), ch)

  for i := 0; i < 10; i++ {
    fmt.Println(<-ch)
  }

  fmt.Println(Same(tree.New(1), tree.New(1)))
  fmt.Println(Same(tree.New(1), tree.New(2)))
}
```

## sync.Mutex

```go
package main

import (
  "fmt"
  "sync"
  "time"
)

// SafeCounter is safe to use concurrently.
type SafeCounter struct {
  mu sync.Mutex
  v  map[string]int
}

// Inc increments the counter for the given key.
func (c *SafeCounter) Inc(key string) {
  c.mu.Lock()
  // Lock so only one goroutine at a time can access the map c.v.
  c.v[key]++
  c.mu.Unlock()
}

// Value returns the current value of the counter for the given key.
func (c *SafeCounter) Value(key string) int {
  c.mu.Lock()
  // Lock so only one goroutine at a time can access the map c.v.
  defer c.mu.Unlock()
  return c.v[key]
}

func main() {
  c := SafeCounter{v: make(map[string]int)}
  for i := 0; i < 1000; i++ {
    go c.Inc("somekey")
  }

  time.Sleep(time.Second)
  fmt.Println(c.Value("somekey"))
}
```

To make sure only one goroutine can access a variable at a time to avoid
conflicts:

This concept is called *mutual exclusion*, and the conventional name for the
data structure that provides it is `mutex`.

Go's standard library provides mutual exclusion with `sync.Mutex` and its two
methods:

- `Lock`
- `Unlock`

We can define a block of code to be executed in mutual exclusion by surrounding
it with a call to `Lock` and `Unlock` as shown on the `Inc` method.

We can also use `defer` to ensure the mutex will be unlocked as in the `Value`
method.

## Exercise: Web Crawler

In this exercise you'll use Go's concurrency features to parallelize a web
crawler.

Modify the `Crawl` function to fetch URLs in parallel without fetching the same
URL twice.

**Hint**: you can keep a cache of the URLs that have been fetched on a map, but
maps alone are not safe for concurrent use!

```go
package main

import (
  "fmt"
  "sync"
)

type Locker struct {
  v   map[string]bool
  mux sync.Mutex
}

type Fetcher interface {
  // Fetch returns the body of URL and
  // a slice of URLs found on that page.
  Fetch(url string) (body string, urls []string, err error)
}

var cnt Locker = Locker{v: make(map[string]bool)}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
func Crawl(url string, depth int, fetcher Fetcher, exit chan bool) {
  // Fetch URLs in parallel.
  if depth <= 0 {
    exit <- true
    return
  }

  cnt.mux.Lock()
  // Don't fetch the same URL twice.
  _, ok := cnt.v[url]
  if ok == false {
    cnt.v[url] = true
    cnt.mux.Unlock()
  } else {
    exit <- true
    cnt.mux.Unlock()
    return
  }

  body, urls, err := fetcher.Fetch(url)
  if err != nil {
    fmt.Println(err)
    exit <- true
    return
  }
  fmt.Printf("found: %s %q\n", url, body)

  e := make(chan bool)
  for _, u := range urls {
    go Crawl(u, depth-1, fetcher, e)
  }
  
  // wait for all child gorountines to exit
  for i := 0; i < len(urls); i++ {
    <-e
  }
  exit <- true
}

func main() {
  exit := make(chan bool)
  go Crawl("https://golang.org/", 4, fetcher, exit)
  <-exit
}

// fakeFetcher is Fetcher that returns canned results.
type fakeFetcher map[string]*fakeResult

type fakeResult struct {
  body string
  urls []string
}

func (f fakeFetcher) Fetch(url string) (string, []string, error) {
  if res, ok := f[url]; ok {
    return res.body, res.urls, nil
  }
  return "", nil, fmt.Errorf("not found: %s", url)
}

// fetcher is a populated fakeFetcher.
var fetcher = fakeFetcher{
  "https://golang.org/": &fakeResult{
    "The Go Programming Language",
    []string{
      "https://golang.org/pkg/",
      "https://golang.org/cmd/",
    },
  },
  "https://golang.org/pkg/": &fakeResult{
    "Packages",
    []string{
      "https://golang.org/",
      "https://golang.org/cmd/",
      "https://golang.org/pkg/fmt/",
      "https://golang.org/pkg/os/",
    },
  },
  "https://golang.org/pkg/fmt/": &fakeResult{
    "Package fmt",
    []string{
      "https://golang.org/",
      "https://golang.org/pkg/",
    },
  },
  "https://golang.org/pkg/os/": &fakeResult{
    "Package os",
    []string{
      "https://golang.org/",
      "https://golang.org/pkg/",
    },
  },
}
```
