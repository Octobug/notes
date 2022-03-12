# 4 Service Discovery

- [4 Service Discovery](#4-service-discovery)
  - [Why Use Service Discovery?](#why-use-service-discovery)
  - [The Client-Side Discovery Pattern](#the-client-side-discovery-pattern)
  - [The Server-Side Discovery Pattern](#the-server-side-discovery-pattern)
  - [The Service Registry](#the-service-registry)
  - [Service Registration Options](#service-registration-options)
  - [The Self-Registration Pattern](#the-self-registration-pattern)

## Why Use Service Discovery?

*Figure 4-1. A client to API Gateway need help finding services*.

![A client to API Gateway need help finding services](images/4_1_a_client_need_help_finding_services.png)

In a modern, cloud-based microservices application, service instances have
dynamically assigned network locations. Moreover, the set of service instances
changes dynamically because of autoscaling, failures, and upgrades.

There are two main service discovery patterns: client-side discovery and
service-side discovery,

## The Client-Side Discovery Pattern

The client queries a **service registry**, which is a database of available
service instances. The client then uses a load-balancing algorithm to select
one of the available service instances and makes a request.

*Figure 4-2. Clients can take on the task of discovering services*.

![Clients can take on the task of discovering services](images/4_2_client_discover_services.png)

The network location of a service instance is registered with the service
registry when it starts up. It is removed from the service registry when the
instance terminates. The service instance's registration is typically refreshed
periodically using a heartbeat mechanism.

Benefits:

- This pattern is straightforward
- There are no other moving parts except for the service registry
- Clients can make load-balancing decisions by themselves.

Drawbacks:

- It couples the client with the service discovering code.

## The Server-Side Discovery Pattern

*Figure 4-3. Service discovery can also be handled among servers*.

![Service discovery can also be handled among servers](images/4_3_service_discovery_among_servers.png)

The client makes a request to a service via a load balancer. The load balancer
queries the service registry and routes each request to an available service
instance.

Examples:

- ELB (AWS Elastic Load Balancer)
- NGINX PLUS or NGINX with `Consul Template` and `Consul service registry`
- Deployment environments such as `Kubernetes` and `Marathon` run a proxy which
  plays the role of a server-side discovery load balancer on each host in the
  cluster.

Benefits:

- Datails of discovery are abstracted away from the client.

Drawbacks:

- It is yet another highly available system component that needs to be managed
  unless the service registry is provided by the deployment environment.

## The Service Registry

A service registry needs to be highly available and up to date.

`Netflix Eureka` provides a REST API for registering (`POST`) and querying
(`GET`) service instances. Every 30 seconds it refreshes (`PUT`) its
registration and remove (`DELETE` or a `timeout`) a registration.

Other examples of service registries:

- `etcd` (used by `Kubernetes` and `Cloud Foundry`)
- `Consul`
- `Apache ZooKeeper`

## Service Registration Options

- **Self-registration pattern**: Service instances register themselves.
- **Third-party registration pattern**: Other system component manages the
  registration.

## The Self-Registration Pattern

>>>>> progress
