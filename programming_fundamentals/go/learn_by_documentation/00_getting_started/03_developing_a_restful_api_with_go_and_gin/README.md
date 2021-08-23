# Tutorial: Developing a RESTful API with Go and Gin

> - [Tutorial: Developing a RESTful API with Go and Gin](https://golang.org/doc/tutorial/web-service-gin)

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
