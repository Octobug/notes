# Chapter 3: Evolution of Identity

> Progress is not an illusion; it happens, but it is slow and invariably
> disappointing.
>
> —George Orwell, from Inside the Whale and Other Essays (1940)

- [Chapter 3: Evolution of Identity](#chapter-3-evolution-of-identity)
  - [Identity Management Approaches](#identity-management-approaches)
    - [Per-Application Identity Silo](#per-application-identity-silo)
    - [Centralized User Repository](#centralized-user-repository)
    - [Early SSO Servers](#early-sso-servers)
    - [Federated Identity and SAML 2](#federated-identity-and-saml-2)
    - [WS-Fed](#ws-fed)
    - [OpenID](#openid)
    - [OAuth 2](#oauth-2)
    - [OpenID Connect (OIDC)](#openid-connect-oidc)
    - [OAuth 2.1](#oauth-21)
  - [Standard Protocols](#standard-protocols)
  - [Summary](#summary)
    - [Key Points](#key-points)
  - [Notes](#notes)

## Identity Management Approaches

### Per-Application Identity Silo

In the Stone Age of computer applications, each application often implemented
its own identity repository, authentication, authorization, and access control.

Each application often had its own dedicated database or other storage in which
user identities, credentials, and user profile data were stored, and each
application prompted the user to log in and then validated the user’s
credentials against its own repository of user information.

This siloed approach is still used today in many consumer-facing scenarios
where a user signs up by providing an application-specific username and
password. If a user reuses the same password across multiple sites, a
compromise at any one site could put the user’s data at other sites at risk.

### Centralized User Repository

Many companies implemented **directory services** to house and centralize user
identity information. Directory services are optimized for information that is
frequently read but infrequently modified, which is often the case for user
identity data. Applications used a directory service to store user data and
credentials.

Large, on-site commercial business applications targeted to enterprise
environments often included support for this approach. This centralized
approach offered a significant improvement over the siloed, per-application
approach.

The centralization of identity administration and access with a directory
service provided many advantages.

- Directory replication capabilities enabled applications to leverage the same
  identity information, eliminating data inconsistency issues. The same
  username and password could be used across applications.
- A centralized directory service also provided a single point of control at
  which to implement password policy or quickly terminate an identity if
  necessary.
  
As a result, directory services became widely adopted, at least in larger
companies. Directory services also had some disadvantages:

- A directory service by itself did not maintain any sort of session for a
  user.
- A user had only one username and password to remember, but the user still had
  to enter the credentials into each application’s login screen because each
  application needed to validate them using the directory service (in the
  absence of additional technology such as single sign-on servers and
  proprietary OS features).
  - It exposed the user’s password to the applications. A compromise at one
    application might put other applications at risk.
  
### Early SSO Servers

Several types of what became known as **identity and access management (IAM)**
or single sign-on (SSO) servers provided further improvement.

Early SSO servers leveraged the identity information in a directory service,
but provided a layer on top of the directory service that maintained a session
to remember users that had already authenticated.

In a typical approach, an application could redirect a user’s browser to an SSO
server to have the user authenticated there, and the application would receive
the authentication results in a secure, predetermined fashion. If a user
accessed a second application, shortly after they authenticated for the first
application, the second application redirected the user’s browser to the SSO
server, and the SSO server would detect the user’s existing session and
redirect them back to the application with a success status without prompting
the user for credentials again.

The introduction of single sign-on servers offered many advantages over
directory services.

- Users benefited from the ability to access multiple applications with a
  single authentication.
- Security teams appreciated that the user’s static directory password was only
  exposed to the SSO server, instead of to each application the user accessed.
- IT departments were happy because it gave them a single place to implement
  authentication policy and stronger authentication mechanisms.

There were some disadvantages with early SSO servers in practice:

- The interaction between applications and SSO servers was somewhat
  proprietary, and SSO products were often time-consuming to implement.
- Single sign-on relied on cookies which, due to browser restrictions on cookie
  access, meant the solutions worked within one Internet domain such as
  `www.mycompany.com`. As many companies were becoming interested in external
  Software-as-a-Service (SaaS) applications, this was a limiting restriction.
  - <https://stackoverflow.com/questions/77832231/why-does-directory-service-and-cookies-based-sso-only-work-within-one-internet>
  - <https://www.fusionspan.com/blog/synchronizing-single-sign-on-sso-with-a-domain-cookie-part-1-an-overview/>

### Federated Identity and SAML 2

Unfortunately, there was often no good way to manage employee identities in
SaaS applications. It was difficult for a company to track accounts its
employees created in SaaS systems, and users once again had to remember a
password for every application. The single sign-on they enjoyed across internal
applications didn’t extend to external SaaS applications in other domains.

Fortunately, a new industry standard,
***SAML 2 (Security Assertion Markup Language)***, had been published in 2005.
It provided a solution for web single sign-on *across domains* and federated
identity.

Although the SAML 2 technical overview focused on a consumer-facing use case`?`,
SAML 2 provided an excellent solution for enterprises needing better control
over employee identities in SaaS applications.

With SAML 2, SaaS applications could redirect corporate users back to a
corporate authentication service, known as an ***identity provider (IdP)***,
for authentication. Identity federation provided a way to link an identity used
in an application with an identity at the identity provider.

- Companies could have the advantages of single sign-on with both internal and
  SaaS applications.
- Users benefited by having a single username/password to remember.
- The enterprise had a centralized control point for both internal and external
  identities and could shut off access quickly at the corporate identity
  provider.
- Password policy and multi-factor authentication could be implemented in a
  single place.
  
Despite being widely adopted, however, SAML 2 was no silver bullet:

- The protocol was designed to cover many scenarios, making it complex to
  configure and implement.
- While SAML 2 became widely adopted within enterprise environments, there was
  no viable business model for it to address consumer-facing scenarios.
- Another limitation was that SAML 2 only solved the problem of authentication.
- Applications were evolving to architectures based on APIs. As typically
  implemented, SAML 2 solved the problem of authenticating users but didn’t
  help with API authorization.

### WS-Fed

The ***Web Services Federation Language (WS-Fed)*** federation framework was
created by an industry coalition as part of a larger set of protocols known as
the `WS-∗` specifications. The WS-Fed 1.2 specification was published as an
OASIS standard in 2009 and provided mechanisms whereby “authorized access to
resources managed in one realm can be provided to security principals whose
identities are managed in other realms.”

It was taken up in many enterprise environments and, like SAML 2, is still in
use today in many corporate settings.

### OpenID

With SAML 2 only adopted in employee-facing scenarios`?`, consumer users were
still forced to register anew at each consumer-facing website. A new industry
group formed to create a solution for what it termed “user-centric” identity,
and this gave rise to a protocol called OpenID.

In addition to organization-controlled identity providers commonly used with
SAML 2 and WS-Fed, OpenID included the idea of user-controlled identity for the
consumer use case.

Consumer users could even set up their own identity provider and point
applications to it for authentication.
  
The original OpenID protocol didn’t become widely used, but it did highlight
the need for user-centric identity solutions and laid the groundwork for
another protocol named OpenID Connect.

### OAuth 2

With Web 2.0 and the rise of social media, many consumer-facing websites were
created that allowed users to upload content such as pictures. This gave rise
to use cases where an application needed to retrieve such content on the user’s
behalf.

A solution was needed that would allow a user to authorize an application at
one website to retrieve their content from another website’s API, without the
user having to expose their credentials to the first site.

The ***OAuth*** protocol provided a solution for this use case. The OAuth 2.0
version of the specification allows a user to authorize one application, known
as a client, to send a request to an API, known as a **resource server**, on
the user’s behalf to retrieve data at the resource server owned by the user.

To do this, the application interacts with an `authorization server` which
authenticates a user as part of obtaining their consent for the application to
access their resources. The application receives a token which enables it to
call the `resource server` on the user’s behalf.

OAuth 2 solved an important API authorization use case. Given the lack of a
consumer-facing authentication solution like SAML 2 and WS-Fed, and the fact
that `authorization servers` might need to authenticate users as part of
obtaining the user’s authorization consent, it may have been tempting to some
to want to use it for more than this.

- Google
- LinkedIn
- ...

Social media providers already had to authenticate users for access to their
site and when an OAuth 2 authorization request was received that required
authenticated user consent.

If they were to provide a general authentication service, it might attract more
users to their platform. There was one slight problem, however. OAuth 2 was not
designed as a general authentication service and could not securely be used for
this purpose, at least without proprietary additions to the pure OAuth 2
features.

Another solution standard was needed.

### OpenID Connect (OIDC)

***OpenID Connect (OIDC)*** was designed to provide a key feature needed for an
authentication service. Even if OAuth 2 authorization servers were capable of
authenticating users, the framework did not provide a standard way to securely
convey the identity of an authenticated user to an application. OIDC provided a
solution for this need.

OIDC was devised as a layer on top of the OAuth 2 protocol to provide
information in a standard format to applications about the identity of an
authenticated user.

This provided a solution for applications for user authentication as well as
API authorization. The implementation of OIDC by widely used social
media/service providers like Google, PayPal, and Yahoo provided a solution for
consumer-facing authentication services, but there was nothing in the protocol
to limit it to consumer-facing scenarios.

OIDC offers benefits to users, application developers, and identity providers.

- Website developers can delegate the work of implementing authentication and
  password reset logic to an OIDC provider.
- Users benefit because they can leverage one account to log in to many sites
  without exposing their account credentials to those other sites.
- Providers may benefit if OIDC support attracts more users to their platform.

OIDC provides the web single sign-on benefits that were attractive in SAML 2
and, when combined with OAuth 2, provides a solution with authentication as
well as the API authorization capabilities needed by modern applications.

### OAuth 2.1

A new draft OAuth 2.1 authorization framework specification document has been
published to consolidate, reconcile, and merge several earlier OAuth 2–related
specifications and best practice recommendation documents. The OAuth 2.1
specification document is meant to replace the OAuth 2.0 specification
document.

The new version includes updates for:

- native applications
- browser-based applications
- several security-related updates
- removes some elements included in the original OAuth 2.0 specification which
  are no longer recommended
  
## Standard Protocols

Why use an industry standard protocol?

1. As open standards, these protocols have been scrutinized for flaws by many
   people, so they are less likely to have vulnerabilities than something you’d
   invent yourself.
2. These protocols are widely used, providing interoperability between your
   application and service providers which support the protocols.
3. If you wish to access user profile data from services such as Google, you
   will have to use the standard protocols as implemented by these services.
   Similarly, if your application will be used by enterprises, the enterprise
   may expect your application to use one of these protocols.
4. The protocols designed for authentication support single sign-on which
   represents convenience for your users.
5. Using an existing protocol can save you time as many programming languages
   offer SDKs that support them.

## Summary

### Key Points

- Centralization of identity data with directory services enabled a single
  identity and credential, but this had to be entered by a user into each
  application (in the absence of other complementary technology).
- Single sign-on servers provided session management so users could log in once
  and access multiple applications, within the same domain, with one
  authentication.
- SAML 2 and WS-Fed provide single sign-on and federated identity across
  domains.
- OAuth 2 provides a solution for authorizing applications to call APIs.
- OIDC provides a layer on top of OAuth 2 for authenticating users and
  returning information to applications in a standard format about the
  authenticated user.
- OAuth 2.1, currently in draft form, consolidates several OAuth 2-related
  specifications and best practice documents released after the publication of
  the original OAuth 2.0 authorization framework specification.

## Notes

1. <http://saml.xml.org/saml-specifications>
2. <http://docs.oasis-open.org/wsfed/federation/v1.2/os/ws-federation-1.2-spec-os.html>
3. <http://docs.oasis-open.org/wsfed/federation/v1.2/os/ws-federation-1.2-spec-os.html>
4. <https://openid.net/specs/openid-authentication-1_1.html>
5. <https://tools.ietf.org/html/rfc6749>
6. <https://openid.net/specs/openid-connect-core-1_0.html>
7. <https://oauth.net/2.1/>
