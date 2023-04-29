// declare a main package
package main

import (
	"fmt"

	"rsc.io/quote"
)

// a main function executes by default when the main package runs
func main() {
	fmt.Println("Hello, World!")
	fmt.Println(quote.Go())
}
