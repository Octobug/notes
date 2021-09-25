# Questions

## Differences between handling connections and requests?

### Handling many requests

- Handling many requests per second requires high throughput (processing them
  quickly.
- Handling many requests per second is concerned with the speed of handling
  requests.

### Handling many concurrent connections

- A high number of concurrent connections requires efficient scheduling of
connections.
- A system capable of handling a high number of concurrent connections does not
  necessarily have to be a fast system, only one where each request will
  deterministically return a response within a (not necessarily fixed) finite
  amount of time.

## What is it?

## Why is it a problem?

### Operating system layer

- Multi-processing capabilities
- Memory management
- I/O management

### Application layer

## Status quo?

c10m became reality in 2010s.

## How was it solved?

### How did the industrial solved it?

### How to solve it in Python?
