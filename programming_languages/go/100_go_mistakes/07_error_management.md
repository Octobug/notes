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

In general, the two main use cases for error wrapping are:

- Adding additional context to an error
- Marking an error as a specific error

```go
// custom error types
type BarError struct {
    Err error
}
func (b BarError) Error() string {
    return "bar failed: " + b.Err.Error()
}

func Foo() error {
    err := bar()
    if err != nil {
        return fmt.Errorf("bar failed: %w", err)
        // another option is using %v:
        return fmt.Errorf("bar failed: %v", err)
    }
}
```

`fmt.Errorf("bar failed: %w", err)` wraps the source error to add additional context without having to create another error type.

Because the source error remains available, a client can unwrap the parent error and then check whether the source error was of a specific type or value.

`fmt.Errorf("bar failed: %v", err)`: the difference is that the error itself isn't wrapped. It is transformed into another error to to add context, and the source error is no longer available.

`%w` is not necessarily better than `%v`. Wrapping an error makes the source error available for callers. Hence, it means introducing potential coupling. To make sure callers don't rely on implementation details, the error returned should be transformed, not wrapped. In such a case, using `%v` instead of `%w` might be better.

- If we need to mark an error, we should create a custom error type.
- If we just want to add extra context, we should use `fmt.Errorf` with `%w` directive as it doesn't require creating a custom error type.

## 7.3 #50: Checking an error type inaccurately

e.g. checking wrapped `%w` errors

- an HTTP handler to return the transaction amount from an ID
- The handler will parse the request to get the ID and retrieve the transaction amount from DB.

The implementation can fail in two cases:

- If the ID is invalid (`StatusBadRequest`)
- If querying the DB fails (`ServiceUnavailable`)

```go
// version 1: with custom error
type transientError struct {
    err error
}

func (t transientError) Error() string {
    return fmt.Sprintf("transient error: %v", t.err)
}

func getTransactionAmount(transactionID string) (float32, error) {
    if len(transactionID) != 5 {
        // simple error
        return 0, fmt.Errorf("id is invalid: %s", transactionID)
    }

    amount, err := getTransactionAmountFromDB(transactionID)
    if err != nil {
        return 0, transientError{err: err}
    }
    return amount, nil
}

func handler(w http.ResponseWriter, r *http.Request) {
    transactionID := r.URL.Query().Get("transaction")

    amount, err := getTransactionAmount(transactionID)
    if err != nil {
        switch err.(type) {
        case transientError:
            http.Error(w, err.Error(), http.StatusServiceUnavailable)
        default:
            http.Error(w, err.Error(), http.StatusBadRequest)
        }
        return
    }

    // Write response
}
```

```go
// version 2: with wrapped error
type transientError struct {
    err error
}

func (t transientError) Error() string {
    return fmt.Sprintf("transient error: %v", t.err)
}

func getTransactionAmount(transactionID string) (float32, error) {
    if len(transactionID) != 5 {
        // simple error
        return 0, fmt.Errorf("id is invalid: %s", transactionID)
    }

    amount, err := getTransactionAmountFromDB(transactionID)
    if err != nil {
        return 0, fmt.Errorf("failed to get transaction %s: %w", transactionID, err)
    }
    return amount, nil
}

func getTransactionAmountFromDB(transactionID string) (float32, error) {
    // ...
    if err != nil {
        return 0, transientError{err: err}
    }
    // ...
}

// not working
func handler(w http.ResponseWriter, r *http.Request) {
    transactionID := r.URL.Query().Get("transaction")

    amount, err := getTransactionAmount(transactionID)
    if err != nil {
        switch err.(type) {
        case transientError:
            // this case now cannot match the wrapped transientError
            http.Error(w, err.Error(), http.StatusServiceUnavailable)
        default:
            http.Error(w, err.Error(), http.StatusBadRequest)
        }
        return
    }

    // Write response
}

// correct one
func handler(w http.ResponseWriter, r *http.Request) {
    transactionID := r.URL.Query().Get("transaction")

    amount, err := getTransactionAmount(transactionID)
    if err != nil {
        if errors.As(err, &transientError{}) {
            http.Error(w, err.Error(), http.StatusServiceUnavailable)
        } else {
            http.Error(w, err.Error(), http.StatusBadRequest)
        }    
        return
    }

    // Write response
}
```

`errors.As`: it recursively unwraps an error and returns `true` if
an error in the chain matches the expected type.

If rely on error wrapping, we must use `errors.As` to check whether an error is a specific type.

## 7.4 #51: Checking an error value inaccurately

A ***sentinel error*** is an error defined as a global variable:

```go
import "errors"

var ErrFoo = errors.New("foo")
```

In general, the convention is to start with `Err` followed by the
error type: `ErrFoo`. A sentinel error conveys an expected error.

We want to design a `Query` method that allows us to execute a query to a database.
This method returns a slice of rows. When there are no rows found,we have two options:

- Return a sentinel value: a `nil` slice (like `strings.Index`,
which returns the sentinel value `–1` if a substring isn’t present).
- Return a specific error that a client can check.

If using the error way:

We can classify this as an ***expected*** error, because passing a request that returns no rows is allowed. Conversely, situations like network issues and connection polling errors are unexpected errors. It doesn’t mean we don’t want to handle unexpected
errors; it means that semantically, those errors convey a different meaning.

Sentinel errors examples of standard libraries:

- `sql.ErrNoRows` — Returned when a query doesn’t return any rows
- `io.EOF` — Returned by an `io.Reader` when no more input is available

Sentinel errors convey an expected error that clients will expect to check. Therefore, as general guidelines,

- Expected errors should be designed as error values (sentinel errors): `var ErrFoo = errors.New("foo")`.
- Unexpected errors should be designed as error types: `type BarError struct { … }`, with `BarError` implementing the `error` interface.

We compare an error to a specific value by using the `==` operator:

```go
err := query()
if err != nil {
    if err == sql.ErrNoRows {
        // ...
    } else {
        // ...
    }
}
```

A sentinel error can also be wrapped. If an `sql.ErrNoRows` is wrapped using `fmt.Errorf` and the `%w` directive, `err == sql.ErrNoRows` will always be `false`.

`errors.As` is used to check an error against a type. With error values, we can use its counterpart: `errors.Is`:

```go
err := query()
if err != nil {
    if errors.Is(err, sql.ErrNoRows) {
        // ...
    } else {
        // ...
    }
}
```

Using `errors.Is` instead of the `==` operator allows the comparison to work even if the error is wrapped using `%w`.

## 7.5 #52: Handling an error twice

The example: `GetRoute` function will get the route from a pair of sources to a pair of target coordinates. This function will call an
unexported `getRoute` function that contains the business logic to calculate the best route. Before calling `getRoute`, we use `validateCoordinates` to validate the source and target coordinates:

```go
// not working
func GetRoute(srcLat, srcLng, dstLat, dstLng float32) (Route, error) {
    err := validateCoordinates(srcLat, srcLng)
    if err != nil {
        log.Println("failed to validate source coordinates")
        return Route{}, err
    }

    err = validateCoordinates(dstLat, dstLng)
    if err != nil {
        log.Println("failed to validate target coordinates")
        return Route{}, err
    }

    return getRoute(srcLat, srcLng, dstLat, dstLng)
}

func validateCoordinates(lat, lng float32) error {
    if lat > 90.0 || lat < -90.0 {
        log.Printf("invalid latitude: %f", lat)
        // cumbersome repeated msg
        return fmt.Errorf("invalid latitude: %f", lat)
    }
    if lng > 180.0 || lng < -180.0 {
        log.Printf("invalid longitude: %f", lng)
        // cumbersome repeated msg
        return fmt.Errorf("invalid longitude: %f", lng)
    }
    return nil
}
```

As a rule of thumb, an error should be handled only once. Logging an error is handling an error, and so is returning an error. Hence, we should either log or return an error, ***never both***.

```go
// each error is handled only once by being returned directly.
// and wrapped with specific information that which call to `validateCoordinates` was falling
func GetRoute(srcLat, srcLng, dstLat, dstLng float32) (Route, error) {
    err := validateCoordinates(srcLat, srcLng)
    if err != nil {
        return Route{},
            fmt.Errorf("failed to validate source coordinates: %w", err)
    }

    err = validateCoordinates(dstLat, dstLng)
    if err != nil {
        return Route{},
            fmt.Errorf("failed to validate target coordinates: %w", err)
    }

    return getRoute(srcLat, srcLng, dstLat, dstLng)
}

func validateCoordinates(lat, lng float32) error {
    if lat > 90.0 || lat < -90.0 {
        return fmt.Errorf("invalid latitude: %f", lat)
    }
    if lng > 180.0 || lng < -180.0 {
        return fmt.Errorf("invalid longitude: %f", lng)
    }
    return nil
}
```

The caller of `GetRoute` may handle the possible errors with logging, or return them to its upper caller.

With this version, we have covered all the different cases: a single log, without losing any valuable information. In addition, each error is handled only once, which simplifies the code by avoiding repeating error messages.

***Handling an error should be done only once***. Using error wrapping is the most convenient approach as it allows us to propagate the source error and add context to an error.

## 7.6 #53: Not handling an error

In some cases, we may want to ignore an error returned by a function.

If we’re not interested in an error, we want to purposely omit any error handling:

```go
func f() {
    // ...
    notify()
}

func notify() error {
    // ...
}
```

Because we want to ignore the error, we just call `notify` without assigning its output to a classic `err` variable.

However, from a maintainability perspective, the code can lead to some issues:

- How can we guess whether or not handling the error was intentional?
- How can we know whether the previous developer forgot to handle it or did it purposely?

For these reasons, when we want to ignore an error in Go, there’s only one way to write it: `_ = notify()`

A comment can also accompany such code, but not a comment like the following that mentions ignoring the error:

```go
// Ignore the error
_ = notify()
```

This comment just duplicates what the code does and should be avoided. But it may be a good idea to write a comment that indicates the rationale for why the error is ignored, like this:

```go
// At-most once delivery.
// Hence, it's accepted to miss some of them in case of errors.
_ = notify()
```

Ignoring an error in Go should be the exception. In many cases, we may still favor logging them, even at a low log level.

## 7.7 #54: Not handling defer errors

Not handling errors in `defer` statements is a mistake that’s frequently made by Go developers.

Here’s a possible implementation:

```go
const query = "..."

func getBalance(db *sql.DB, clientID string) (
float32, error) {
    rows, err := db.Query(query, clientID)
    if err != nil {
        return 0, err
    }
    defer rows.Close()

    // Use rows
}
```

`rows` is a `*sql.Rows` type. It implements the `Closer` interface:

```go
type Closer interface {
    Close() error
}
```

This interface contains a single `Close` method that returns an error. But in this case, the error returned by the `defer` call is ignored: `defer rows.Close()`

If we don’t want to handle the error, we should ignore it explicitly using the blank identifier:

```go
defer func() { _ = rows.Close() }()
```

In this case, calling `Close()` returns an error when it fails to free a DB connection from the pool. Hence, ignoring this error is probably not intended. Most likely, a better option would be to
log a message:

```go
defer func() {
    err := rows.Close()
    if err != nil {
        log.Printf("failed to close rows: %v", err)
    }
}()
```

What if, instead of handling the error, we prefer to propagate it to the caller of `getBalance` so that they can decide how to handle it?

```go
defer func() {
    err := rows.Close()
    if err != nil {
        return err
    }
}()
```

This implementation doesn’t compile. Indeed, the `return` statement is associated with the anonymous `func()` function, not `getBalance`.

If we want to tie the error returned by `getBalance` to the error caught in the `defer` call, we must use named result parameters:

```go
func getBalance(db *sql.DB, clientID string) (
balance float32, err error) {
    rows, err := db.Query(query, clientID)
    if err != nil {
        return 0, err
    }
    defer func() {
        err = rows.Close()
    }()

    if rows.Next() {
        err := rows.Scan(&balance)
        if err != nil {
            return 0, err
        }
        return balance, nil
    }
    // ...
}
```

Once the `rows` variable has been correctly created, we defer the call to `rows.Close()` in an anonymous function. This function assigns the error to the `err` variable, which is initialized using named result parameters.

This code may look okay, but there’s a problem with it. If `rows.Scan` returns an error, `rows.Close` is executed anyway; but because this call overrides the error returned by `getBalance`, instead of returning an error, we may return a `nil` error if `rows.Close` returns successfully. In other words, if the call to `db.Query` succeeds, the error returned by `getBalance` will always be the one returned by `rows.Close`, which isn’t what we want.

The logic we need to implement isn’t straightforward:

- If `rows.Scan` succeeds,
  - If `rows.Close` succeeds, return no error.
  - If `rows.Close` fails, return this error.

And if `rows.Scan` fails, the logic is a bit more complex because we may have to handle two errors:

- If `rows.Scan` fails,
  - If `rows.Close` succeeds, return the error from `rows.Scan`.
  - If `rows.Close` fails . . . then what?

If both `rows.Scan` and `rows.Close` fail, there are several options:

- return a custom error that conveys two errors
- return the `rows.Scan` error but log the `rows.Close` error (in this case we choose it)

```go
func getBalance(db *sql.DB, clientID string) (
balance float32, err error) {
    rows, err := db.Query(query, clientID)
    if err != nil {
        return 0, err
    }

    defer func() {
        closeErr := rows.Close()
        if err != nil {
            if closeErr != nil {
                log.Printf("failed to close rows: %v", err)
            }
            return
        }
        err = closeErr
    }()

    if rows.Next() {
        err := rows.Scan(&balance)
        if err != nil {
            return 0, err
        }
        return balance, nil
    }
    // ...
}
```

The `rows.Close` error is assigned to another variable: `closeErr`. Before assigning it to `err`, we check whether `err` is different from `nil`. If that’s the case, an error was already returned by `getBalance`, so we decide to log `err` and return the existing error.

In the case of errors returned by defer calls, the very least we should do is ignore them explicitly. If this isn’t enough, we can handle the error directly by logging it or propagating it up to the caller.

## Summary

- Using `panic` is an option to deal with errors in Go. However, it should only be used sparingly in unrecoverable conditions: for example, to signal a programmer error or when you fail to load a mandatory dependency.
- Wrapping an error allows you to mark an error and/or provide additional context. However, error wrapping creates potential coupling as it makes the source error available for the caller. If you want to prevent that, don’t use error wrapping.
- If you use error wrapping with the `%w` directive and `fmt.Errorf`, comparing an error against a type or a value has to be done using `errors.As` or `errors.Is`, respectively. Otherwise, if the returned error you want to check is wrapped, it will fail the checks.
- To convey an expected error, use error sentinels (error values). An unexpected error should be a specific error type.
- In most situations, an error should be handled only once. Logging an error is handling an error. Therefore, you have to choose between logging or returning an error. In many cases, error wrapping is the solution as it allows you to provide additional context to an error and return the source error.
- Ignoring an error, whether during a function call or in a `defer` function, should be done explicitly using the blank identifier. Otherwise, future readers may be confused about whether it was intentional or a miss.
- In many cases, you shouldn’t ignore an error returned by a `defer` function. Either handle it directly or propagate it to the caller, depending on the context. If you want to ignore it, use the blank identifier.
