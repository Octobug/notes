# 2 Using an API Gateway

It's a question about how your application's clients interact with the
microservices.

## Introduction

### A sample shopping application

A product details page may display a lot of information:

1. Number of items in the shopping cart
2. Order history
3. Customer reviews
4. Low inventory warning
5. Shipping options
6. Various recommendations, including other products this product is frequently
    bought with, ...
7. Alternative purchasing options

When using a monolithic application architecture, a mobile client retrieves data
by making a single REST call to the application, such as:

```http
GET api.company.com/productdetails/productId
```

A load balancer routes the request to one of serveral identical application
instances. The application then queries various database tables and return the
response to the client.

When using the microservices architecture, the data displayed on the product
details page may be owned by multiple microservices:

- Shopping Cart Service - Number of items in the shopping cart
- Order Service - Order history
- Catalog Service - Basic product information, such as product name, image, and
  price
- Review Service - Customer reviews
- Inventory Service - Low inventory warning
- Shipping Service - Shipping options, deadlines, and costs, drawn separately
  from the shipping provider's API
- Recommendation Service(s) - Suggested items

So, how the mobile client accesses these services?

### Direct Client-to-Microservice Communication

In theory, a client could make requests to each of the microservices directly.
Each microservice would have a public endpoint:

```url
https://serviceName.api.company.name
```

Challenges and limitations:

- The client has to make multiple separate requests
- It makes the client code much more complex
- The microservices might use protocols that are not web-friendly
- It makes refactoring the microservices harder
- It makes authentication harder

### Using an API Gateway

An API Gateway is a server that is the single entry point into the system.

The API Gateway encapsulates the internal system architecture and provides an
API that is tailored to each client.

It might have other responsibilities such as authentication, monitoring, load
balancing, caching, request shaping and management, and static response
handling.

*Using an API Gateway with microservices*.

![Using an API Gateway with microservices](images/2_3_api_gatway.png)

All requests from clients first go through the API Gateway. It then routes
requests to the appropriate microservices. And handles the request by invoking
the various services - product information, reviews, etc. - and combining the
results.

### Benefits and Drawbacks of an API Gateway
