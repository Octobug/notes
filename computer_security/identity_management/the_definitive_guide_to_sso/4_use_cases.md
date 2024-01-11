# Chapter 4: Use Cases

- [Chapter 4: Use Cases](#chapter-4-use-cases)
  - [Single Sign On (SSO) for Your Organization](#single-sign-on-sso-for-your-organization)
  - [Single Sign On (SSO) for your Applications](#single-sign-on-sso-for-your-applications)
    - [Business to Consumer (B2C)](#business-to-consumer-b2c)
    - [Business to Business (B2B)](#business-to-business-b2b)
    - [Business to Enterprise (B2E)](#business-to-enterprise-b2e)
  - [Single Sign On: Build vs Buy](#single-sign-on-build-vs-buy)
    - [The Argument for Build](#the-argument-for-build)
    - [The Argument for Buy](#the-argument-for-buy)

## Single Sign On (SSO) for Your Organization

SSO enables the consolidation of user identity and management.

## Single Sign On (SSO) for your Applications

### Business to Consumer (B2C)

OAuth and OpenID Connect based SSO is the suitable implementation for this.

For the employees, a traditional SAML based SSO solution may also be applicable.

### Business to Business (B2B)

For B2B software, the organization will typically need to support SAML, LDAP or
WS-Federation SSO. SAML based SSO is most commonly found in B2B SaaS.

### Business to Enterprise (B2E)

SAML, WS-Federation and LDAP based SSO are the standards for B2E. And OAuth and
OpenID Connect are gaining ground.

## Single Sign On: Build vs Buy

### The Argument for Build

- advantages
  - complete control
  - reducing dependencies on external vendors
- disadvantages
  - complex expertise required to get it done right
  - it takes time to maintain, patch, and evolve the identity solution

### The Argument for Buy

SaaS is so ubiquitous that it has become an adage in the technology sector to
"focus on building what makes your product unique, buy the rest."

Building your own solution might be just another way of reinventing the wheel.

- advantages
  - The big reasons to buy your identity management platform is that you can get
    your solution up and running in no time.
  - Identity management companies are laser-focused on implementing secure
    solutions and are on top of their game when it comes to evolving standards.
- disadvantages
  - lose some control
  - identity data is stored on third party servers
  - introducing another dependency
  - vendor lock-in (vendors provide some non-standard features)
  - customization is limited
