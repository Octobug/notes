# Chapter 21: Looking into the Crystal Ball

> The future cannot be predicted, but futures can be invented. It was man’s
> ability to invent which has made human society what it is.
>
> —Dennis Gabor, Hungarian physicist, 1971 Nobel Prize winner in physics for
> inventing holography, from Inventing the Future (1963)

- [Chapter 21: Looking into the Crystal Ball](#chapter-21-looking-into-the-crystal-ball)
  - [Continued Security Challenges](#continued-security-challenges)
    - [Ongoing Breaches](#ongoing-breaches)
    - [Evolving Targets](#evolving-targets)
    - [Increasing Complexity](#increasing-complexity)
    - [Diversifying Motives](#diversifying-motives)
  - [More Targets](#more-targets)
    - [Homes and Businesses](#homes-and-businesses)
    - [Cars](#cars)
    - [Medical Implants and Monitoring](#medical-implants-and-monitoring)
    - [Robots](#robots)
    - [Erosion of Perimeter Protection](#erosion-of-perimeter-protection)
  - [Identity - Not Just for Humans](#identity---not-just-for-humans)
    - [Personal Agents](#personal-agents)
    - [Autonomous Vehicles](#autonomous-vehicles)
    - [IoT Devices](#iot-devices)
    - [Identity: Robots](#identity-robots)
  - [On the Horizon](#on-the-horizon)
    - [e-Identity](#e-identity)
    - [Stronger Authentication](#stronger-authentication)
    - [Solutions for Smaller Devices](#solutions-for-smaller-devices)
    - [Asynchronous Online Interaction](#asynchronous-online-interaction)
    - [Easier Adoption](#easier-adoption)
  - [Lessons Learned](#lessons-learned)
    - [Always Look Forward](#always-look-forward)
    - [Usability Is Important](#usability-is-important)
    - [Validation Is Critical](#validation-is-critical)
    - [Logout Takes Time](#logout-takes-time)
    - [Monitor Trends and Vulnerabilities](#monitor-trends-and-vulnerabilities)
  - [Summary](#summary)
    - [Key Points](#key-points)

The notion of identity will need to spread from humans to all manner of
devices, agents, and robots acting on our behalf, and such entities will need
identity management as part of their defenses against malicious attacks.

## Continued Security Challenges

### Ongoing Breaches

### Evolving Targets

As one industry or avenue of theft comes under attack, consumers and service
providers implement mitigations, causing cybercriminals to pivot to easier
targets. The financial industry was an early target, but as financial
institutions implemented more defenses, the entertainment and retail industries
came under increasing attack, often as a source for stolen credit card data.

### Increasing Complexity

### Diversifying Motives

## More Targets

### Homes and Businesses

Even smart dolls designed to interact with children have been found to have
significant privacy and security issues, being hackable via Bluetooth
connection. A particularly eye-opening example is
[the hack of a network-attached sensor for an aquarium heater for a large fish
tank in a Las Vegas casino lobby](https://www.washingtonpost.com/news/innovations/wp/2017/07/21/how-a-fish-tank-helped-hack-a-casino/?noredirect=on&utm_term=.a22c8c331869).

### Cars

### Medical Implants and Monitoring

### Robots

### Erosion of Perimeter Protection

Organizations have been moving toward architectures based on Zero Trust
principles, making identity and access management services critical to protect
the access to individual infrastructure components.

## Identity - Not Just for Humans

### Personal Agents

### Autonomous Vehicles

### IoT Devices

### Identity: Robots

## On the Horizon

### e-Identity

### Stronger Authentication

The W3C Web Authentication (webauthn) specification creates a more standardized
level of abstraction between applications and specific authenticators.
Developers will be able to implement authenticator-agnostic strong
authentication, and users will gain the ability to use authenticators of their
own choosing, whether hardware security tokens or biometric factors collected by
their device.

### Solutions for Smaller Devices

Entities which need to validate the likes of security messages and certificates
depend on having accurate time as well as solutions for detecting certificate
revocations, but existing solutions may not work on constrained devices.
[The Constrained Application Protocol (CoAP)](https://tools.ietf.org/html/rfc7252#section-9),
[Transport Layer Security (TLS) 1.3](https://tools.ietf.org/html/rfc8446),
and
[Datagram Transport Layer Security (DTLS) 1.3](https://datatracker.ietf.org/doc/rfc9147/)
may prove useful for solutions involving such devices.

### Asynchronous Online Interaction

Users may want to facilitate automation by authorizing third-party entities to
perform tasks on their behalf or to access their data. For example, when
applying for a loan online, a lender might require information about an
applicant’s income, credit score, ratio of debt to income, past tax returns,
and credit card statements. A user could authorize the loan site to obtain
information about their salary from an employer, data on their credit history
from a credit reporting agency, and perhaps credit purchase history from their
credit card company, but such checks would likely occur asynchronously,
triggered by a cascade of online transactions once the applicant submits their
request.

Specifications such as the
[User Managed Access grant for OAuth 2.0](https://docs.kantarainitiative.org/uma/wg/rec-oauth-uma-grant-2.0.html)
from the [Kantara Initiative](https://kantarainitiative.org/) may contribute to
making such use cases feasible, in parallel with efforts to explore the risk,
liability, and privacy rights applicable for such scenarios. This standard
allows a user to authorize access to their content to a third-party while
decoupling the timing of the authorization from the access request. A third
party can initiate a request to a resource server without the user’s
synchronous involvement.

The third party interacts with the `authorization server` to obtain claims to
satisfy access policy specified by the owner of the requested data.

### Easier Adoption

We need better resources created to make correct implementation of identity
management easier for developers. Libraries will be needed that are well
documented, support a good user experience, and help developers implement the
protocols/frameworks correctly.

## Lessons Learned

### Always Look Forward

Being able to look ahead and develop identity features for your application as
a service that can be worked on independently from your application allows you
to easily integrate and expand the identity service to meet your future
requirements.

Open standards play a very large role in being able to realize this vision.

### Usability Is Important

### Validation Is Critical

“Garbage In, Garbage Out.”

### Logout Takes Time

### Monitor Trends and Vulnerabilities

## Summary

### Key Points

- Security challenges will continue with diversified targets, actors, and
  motives.
- We will face more security and privacy risks from network-connected devices
  in our lives such as smart home devices, car infotainment, and medical
  monitoring.
- The number of nonhuman entities that will need identities and identity
  management will grow substantially, considering technologies such as personal
  agents, autonomous vehicles, and IoT devices including robots.
- More governments and/or private consortiums will issue electronic identities
  based on more strongly validated identity information.
- Passwords as a single authentication factor will continue to be replaced with
  stronger forms of authentication.
- Security protocols will need to accommodate the small memory, processing
  power, and power consumption requirements of small IoT devices to better
  secure them.
- Identity management will become even more important in the future to help
  protect innovative new services and devices.
- It is essential to design for the entire identity life cycle, from
  provisioning/onboarding to deprovisioning, and even audit records required
  for accountability after deprovisioning.
- Architecting your application to treat identity management as a separable
  component will enable you to work on it in parallel with your application and
  take advantage of open source or third-party solutions where it makes sense.
- The use of open standards will give you flexibility to adopt open source or
  third-party solutions that can provide many important security features.
- Identity management features should satisfy both security and usability
  requirements.
- It is critical to validate all inputs to security decisions and policy
  enforcement points, including security tokens and identity profile attributes.
- Implementing logout features can take time, especially when there are
  multiple sessions for users across different components. Research
  requirements early so you can allow sufficient time to implement logout well.
- To avoid surprises, periodically monitor trends in security, identity
  management solutions, types of attacks, common root causes of breaches,
  updated guidance for how to use open standards, and nonsecurity-related
  trends impacting your target customer base.
