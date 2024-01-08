# Chapter 3: Identity Protocols and Providers

- [Chapter 3: Identity Protocols and Providers](#chapter-3-identity-protocols-and-providers)
  - [Security Assertion Markup Language (SAML)](#security-assertion-markup-language-saml)
  - [WS-Federation](#ws-federation)
  - [OpenID Connect / OAuth](#openid-connect--oauth)
  - [Lightweight Directory Access Protocol (LDAP)](#lightweight-directory-access-protocol-ldap)
  - [Identity Providers](#identity-providers)
    - [Database / Local](#database--local)
    - [Microsoft - Active Directory, ADFS, Azure AD](#microsoft---active-directory-adfs-azure-ad)
    - [Social Providers](#social-providers)
    - [Other](#other)

There are many different ways in which SSO can be implemented.

## Security Assertion Markup Language (SAML)

- For a long time SAML was the defacto protocol for implementing SSO.
- The SAML protocol exchanges authorization and authentication data in XML
  format.
- The three components to this data exchange are
  - `user`: requests a resource from the `service provider`
  - `identity provider`: acts as the single source of truth, verifies the user's
    identity (through a set of credentials like username and password)
  - `service provider`: checks with the `identity provider` if the `user` should
    have access to this resource
- This exchange is facilitated by **assertions**.
  - The `service provider` makes request assertions to the `identity provider`.
  - The `identity provider` returns a response assertion with the `user` data if
    the credentials are valid.

- One of the major benefits of SAML is that the protocol is only concerned with
handing the exchange between the `identity provider` and `service provider`.
  - The authentication aspect is not defined in the protocol, so developers are
    free to choose how users authenticate.
- With SAML, you are not limited to the number of `identity` or
  `service providers`.
  - One `identity provider` can interact with many `service providers` and one
    `service provider` can interact with many `identity providers`.

## WS-Federation

WS-Federation or WS-Fed is another commonly found protocol used in Single Sign
On implementations. For the most part, it is very similar to SAML.

WS-Fed comes from the `WS-*` series of services, falling under WS-Security
branch. WS or Web Services aim to provide a standardized way of handling online
communications.

WS-Fed allows you to extend `WS-*`'s capabilities to Single Sign On scenarios
if `WS-*` services are already used.

WS-Fed is built on top of WS-Trust which uses the Security Token Services (STS)
model to facilitate the transfer of claims data between services. Like SAML, it
is built around the concept of an `Identity Provider` and `Service Provider`.

WS-Fed shares many benefits which SAML protocol also has. It was developed to
extend the capabilities of the existing WS-Security model (commonly found in
the Microsoft ecosystem).

## OpenID Connect / OAuth

OpenID Connect (OIDC) is an authentication protocol, based on the OAuth 2.0
family of specifications. It handles authentication via JSON Web Tokens (JWTs)
delivered via the OAuth 2.0 Protocol. OAuth 2.0 is concerned with resource
access and sharing.

OIDC is all about user authentication. It facilitates access through a
centralized identity provider.

A user wishing to gain access to an application utilizing OIDC, will

- first be redirected to the OIDC provider
- authenticate
- the identity provider returns the user's identity to the application

OpenID Connect is typically used by social networks that allow developers to use
them as identity providers. The flow for OpenID Connect is different from that
of SAML and WS-Federation.

With OIDC,

- an application sends a request to an `identity provider`
- the `identity provider` verifies the user
  - if succeeds, prompts the user to grant data access to the application that
    initiated the request
  - if the user agrees to share the data, the identity provider generates a
    token, called an `id_token` and returns it to the application.
    - this token contains user identity information and the application consumes
      this token and grants the user access
    - JSON Web Tokens are widely used in OAuth and OIDC.

For the purposes of OIDC, each token contains identity data for the user in the
form of claims.

- The OIDC spec defines a series of reserved claims, public claims and private
  claims.

OIDC is not as common in the enterprise environment as it is with consumer
facing applications.

## Lightweight Directory Access Protocol (LDAP)

The **Lightweight Directory Access Protocol (LDAP)** is an application protocol,
used for accessing and maintaining distributed directory information services
over an Internet Protocol (IP) network. It allows access to a centralized
directory of credentials which can be shared amongst multiple applications.

LDAP works by enabling access to an existing directory of users. It is typically
paired with Active Directory and allows admins to have a centralized locatoin
for user identity.

Application clients send requests to the LDAP server and in return the server
responds with information about user identity. There are a number of different
actions a client can request such as

- authenticating a user
- updating user information
- deleting users
- ...

LDAP based SSO is not common outside of company intranets.

## Identity Providers

Identity protocols dictate how the flow of Single Sign On works within an
organization. Identity providers are concerned with actually storing and
managing user identities.

### Database / Local

A common way of managing identity is through a local database which is only
concerned with users and their roles. Organizations requiring full control over
their data will often opt for this option for their identity provider.

Users typically log into the database via username and password authentication,
although organization do tend to enforce multifactor authentication and other
enhanced security measures.

### Microsoft - Active Directory, ADFS, Azure AD

Mostly used in Microsoft ecosystem.

### Social Providers

- Facebook
- Googld
- ...

### Other

- Auth0
- SSO Circle
- ...
