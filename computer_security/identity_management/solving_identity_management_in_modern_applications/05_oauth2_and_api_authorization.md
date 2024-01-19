# Chapter 5: OAuth 2 and API Authorization

> The possession of great power necessarily implies great responsibility.
>
> —William Lamb, British Member of Parliament, Home Secretary, and Prime
> Minister. From a speech in the House of Commons, 1817

- [Chapter 5: OAuth 2 and API Authorization](#chapter-5-oauth-2-and-api-authorization)
  - [API Authorization](#api-authorization)
  - [OAuth 2](#oauth-2)
  - [Terminology](#terminology)
    - [Roles](#roles)
    - [Confidential and Public Clients](#confidential-and-public-clients)
    - [Client Profiles](#client-profiles)
    - [Tokens and Authorization Code](#tokens-and-authorization-code)
  - [How It Works](#how-it-works)
    - [Authorization Code Grant](#authorization-code-grant)
    - [Authorization Code Grant Type + PKCE](#authorization-code-grant-type--pkce)
      - [The Authorization Request](#the-authorization-request)
      - [Response](#response)
      - [Calling the Token Endpoint](#calling-the-token-endpoint)
    - [Client Credentials Grant](#client-credentials-grant)
      - [Client Credentials Grant: The Authorization Request](#client-credentials-grant-the-authorization-request)
    - [Implicit Grant (Removed in OAuth 2.1)](#implicit-grant-removed-in-oauth-21)
    - [Resource Owner Password Credentials Grant (Removed from OAuth 2.1)](#resource-owner-password-credentials-grant-removed-from-oauth-21)
    - [Device Authorization Grant](#device-authorization-grant)

If an application wants to call an API on a user’s behalf to access resources
owned by the user, it needs the user’s consent. In the past, a user often had
to share their credentials with the application to enable such an API call on
their behalf. This gave the application an unnecessary amount of access, not to
mention the responsibility of safeguarding the credential.

## API Authorization

An application may need to call an API on behalf of a user, to access content
owned by the user, or on its own behalf if the application owns the desired
content:

- User-Based Flow: the request must be made on behalf of the user.
- Client-Based Flow: the application only needs to be a registered client
  authorized to call the API.
  
## OAuth 2

The OAuth 2 Authorization Framework was designed to enable an application to
obtain authorization to call third-party APIs. With OAuth 2, an application can
obtain a user’s consent to call an API on their behalf, without needing the
user’s credentials for the API site. An application can also obtain
authorization to call an API on its own behalf if it owns the content to be
accessed.

The primary use case involves a user, called a `resource owner`, who wishes to
allow an application to access a protected resource, owned by the resource
owner, at a logically separate site, known as the `resource server`.

Before OAuth 2, the usual solution involved some risks. The user had to give the
application their credentials at the `resource server` so the application could
retrieve their data at the `resource server`. There was no way for the user to
restrict what the application could do.

![without oauth](https://upload.wikimedia.org/wikipedia/commons/b/b6/Without-oauth.svg)

> <https://commons.wikimedia.org/wiki/File:Without-oauth.svg>

If the application were compromised, and the password decryption key or
cleartext passwords stolen, the user’s data at the `resource server` would be at
risk.

The user also had no way of revoking the application's access to the
`resource server` except by changing their credentials. Unfortunately, changing
credentials to revoke one application’s access would effectively revoke access
for any other applications using the credentials to access `resource server` on
their behalf.

With OAuth 2, when an application needs to call an API on behalf of a user, it
sends an authorization request to an `authorization server` for the API. An
authorization server handles access requests for an API and returns a security
token that can be used by the application to access the API.

![oauth flow](https://upload.wikimedia.org/wikipedia/commons/f/f0/Mediawiki_oauth_2_flow_with_pkce.svg)

> <https://commons.wikimedia.org/wiki/File:Mediawiki_oauth_2_flow_with_pkce.svg>

![oauth abstract](https://upload.wikimedia.org/wikipedia/commons/b/b8/Abstract-flow.svg)

> <https://commons.wikimedia.org/wiki/File:Abstract-flow.svg>

1. In the authorization request, the application gives an indication of what it
   wants to request from the API.
2. The `authorization server` evaluates the request and, if authorized, returns
   a token to the application.
3. If the application asks for content owned by the user, the API’s
   authorization server authenticates the user and then asks the user to give
   their consent for the application to access the requested data.
4. The authorization server uses details in the application’s authorization
   request to prompt the user for their consent.
5. If the user consents to the requested access, the application receives a
   token to call the API on the user’s behalf. The token is called an
   `access token`, and it enables the application to make API requests within
   the scope of what the user authorized when they gave their consent for the
   request.

This solution eliminates the need for the user to share credentials with the
application and gives the user more control over what the application can
access.

The OAuth 2 access token is only intended for API access and not to convey
information about the authentication event or the user. The use of OAuth 2 is
therefore appropriate for authorizing API calls but not as an authentication
solution.

## Terminology

### Roles

OAuth 2 defines four roles involved in an authorization request:

- `Resource Server`: A service (with an API) storing protected resources to be
  accessed by an application.
- `Resource Owner`: A user or other entity that owns protected resources at the
  `resource server`.
- `Client`: An application which needs to access resources at the
  `resource server`, on the resource owner’s behalf or on its own behalf.
- `Authorization Server`: A service trusted by the `resource server` to
  authorize applications to call the `resource server`. It authenticates the
  `application` or `resource owner` and requests consent from the
  `resource owner` if the `application` will make requests on the
  `resource owner`’s behalf. With OAuth 2, the `resource server` (API) is a
  relying party to the `authorization server`. The `authorization server` and
  resource server may be operated by the same entity.

### Confidential and Public Clients

OAuth 2 defines two client types:

- `Confidential Client` (removed from OAuth 2.1): An application that can
  securely store confidential secrets with which to authenticate itself to an
  `authorization server` or use another secure authentication mechanism for
  that purpose. `Confidential clients` typically execute primarily on a
  protected server.
- `Public Client`: An application that can neither securely store a secret or
  credentials to authenticate itself to an `authorization server` nor use
  another secure authentication mechanism for that purpose. `Public clients`
  typically execute primarily on the user’s client device or in the client
  browser.

### Client Profiles

OAuth 2 defines three profiles for client applications based on application
topologies:

- `Web Application`: A `confidential client` with code executing on a
  protected, back-end server. The server can securely store any secrets needed
  for the client to authenticate itself as well as any tokens it receives from
  the authorization server. Such credentials and tokens are not exposed to the
  `resource owner`.
- `Browser-Based Application`: Assumed to be a `public client` with code
  executing in the user’s browser. Such an application is assumed to be
  incapable of adequately securing credentials with which to authenticate
  itself to an authorization server.
- `Native Application`: Assumed to be a `public client` that is installed and
  executed on the user’s device, such as a mobile application or desktop
  application.

### Tokens and Authorization Code

OAuth 2 defines two security tokens and an intermediary authorization code:

- `Authorization Code`: An intermediary, opaque code returned to an application
  and used to obtain an `access token` and optionally a `refresh token`. Each
  authorization code is used once.
- `Access Token`: A token used by an application to access an API. It
  represents the application’s authorization to call an API and has an
  expiration.
- `Refresh Token`: An optional token that can be used by an application to
  request a new `access token` when a prior access token has expired.

## How It Works

The OAuth 2 Authorization Framework defines different methods by which an
`application` interacts with an `authorization server` to obtain authorization
to call an API. Each method uses a credential to represent the authorization.
These credentials are known as `authorization grants` and are used by an
application to obtain an `access token` with which to call an API. The type of
`authorization grant` to use depends on the use case.

The following authorization grant types are defined:

- `Authorization code`
- `Client credentials`
- `Refresh token`

In OAuth 2.0, there were two additional authorization grant types that were
removed in OAuth 2.1. These obsolete grant types are

- `Implicit` (removed)
- `Resource owner password credentials` (removed)

An additional authorization grant type has been designed for devices which have
limited capabilities for user interaction. This grant type is not part of the
core OAuth 2.1 specification (at the time of writing) but is useful to include
as it is designed for scenarios involving devices that make up the Internet of
Things (IoT). This grant type is

- `Client device`

### Authorization Code Grant

The `authorization code grant` type uses two requests from the application to
the `authorization server` to obtain an `access token`.

- In the first request, the user’s browser is redirected to the authorization
  endpoint at the `authorization server` with a request to authorize an API
  call to be made on the user’s behalf.
  - The browser redirect enables the `authorization server` to interact with the
    user to authenticate them and obtain their consent for the authorization
    request.
- After obtaining the user’s consent, the `authorization server` redirects the
  user’s browser back to the `application` with an `authorization code`.
- The `application` uses the authorization code to send a second, back-channel
  request to the `authorization server`’s token endpoint to obtain an
  `access token`.
- The `authorization server` responds with an `access token` issued to the
  `application` which it can use to call the API.

```mermaid
sequenceDiagram
  participant User
  participant Browser
  participant Application
  participant Authorization Server
  participant Resource Server

  User->>Application: 1. to

  Application->Browser: 2. redirects Browser
  activate Browser
  Browser->>Authorization Server: with [Code challenge][Code challenge method] to
  Note over Authorization Server: /authorize

  Authorization Server->>User: 3. asks to login

  User->>Authorization Server: 4. login with [Login credentials]

  Authorization Server->Browser: 5. redirects Browser with [Authorization code]
  activate Browser
  Browser->>Application: to
  Note over Application: /callback

  Application->>Authorization Server: 6. [Authorization code][Code verifier]
  Note over Authorization Server: /token

  Authorization Server->>Application: 7. [Access token][Refresh token]

  Application->>Resource Server: 8. with [Access token] to
  Note over Resource Server: /api endpoint
```

1. The user (`resource owner`) accesses the `application`.
2. The `application` redirects the browser to the `authorization server`’s
   authorize endpoint (defined in the OAuth 2 specification) with an
   authorization request.
3. The `authorization server` prompts the user for authentication and consent.
    - The mechanism by which a user is authenticated to provide consent is
      outside the scope of the OAuth 2 specifications.
4. The user authenticates and provides consent for the request.
5. The `authorization server` redirects the user’s browser back to the
   `application`’s callback URL (defined in the OAuth 2 specification) with an
   `authorization code`.
6. The `application` calls the `authorization server`’s token endpoint (defined
   in the OAuth 2 specification), passing the `authorization code`.
    - `Code verifier` works with `PKCE`
7. The `authorization server` responds with an `access token` (and optionally a
   `refresh token`).
8. The `application` calls the `resource server` (API), using the
   `access token`.

The `authorization code grant` type was originally optimized for
`confidential clients`.

- The first (authorization) request redirects the user to the authorization
  server so it can interact with the user.
- The second request (`6.`) could be made by the application’s back end
  directly to the `authorization server`’s token endpoint.
  - This enables an `application` back end, which is assumed to be capable of
    securely managing an authentication secret, to authenticate itself to the
    `authorization server` when exchanging the `authorization code` for the
    `access token`.
  - It also means that the response with the `access token` can be delivered to
    the `application` back end, which will make the subsequent API calls.
  - An added side benefit is that the tokens are returned via secure
    back-channel response.
  - However, while originally optimized for `confidential clients`, the
    addition of PKCE enables other client types to use this grant type as well.

### Authorization Code Grant Type + PKCE

The `authorization code` grant type diagram shows the use of
`Proof Key for Code Exchange (PKCE)`. PKCE is a mechanism that can be used with
authorization and token requests to prevent a malicious process, especially on
mobile devices and with `public clients`, from intercepting an
`authorization code` and using it to get an `access token`.

`PKCE` does not authenticate clients. Rather, it ensures that the application
that requested an authorization code is the same application that uses the
`authorization code` to obtain an `access token`.

`PKCE` was defined after OAuth 2.0, but has been incorporated into the core
OAuth 2.1 specification for use with the `authorization code grant` type.

- To use `PKCE`, the application creates a cryptographically random string,
  called a `code verifier`, that is long enough to provide sufficient protection
  against guessing.
- The application then computes a derived value, called a `code challenge`, from
  the `code verifier`. This derived value is typically a hash of the
  `code verifier`. It should not be possible to compute the `code verifier`
  from the derived value in a time period that would enable compromising the
  transaction.
- When the application sends an authorization request in step 2 in the diagram,
  it includes the `code challenge`, along with the `method` used to derive it.
- When the application sends the `authorization code` to the
  `authorization server`’s token endpoint to get the `access token` in step 6,
  it includes the `code verifier`.
- The `authorization server` transforms the `code verifier` value using the
  `code challenge method` received in the authorization request and checks that
  the result matches the `code challenge` sent with the authorization request.
- This enables an `authorization server` to detect if a malicious application
  is trying to use a stolen `authorization code`.
- Only the legitimate application will know the `code verifier` to pass in step
  6 that will match the `code challenge` passed in step 2.

The `PKCE` specification lists two transform methods that can be used to derive
the `code challenge` from the `code verifier`, namely, `“plain”` and `“S256.”`
With the `“plain”` method, the `code challenge` and `code verifier` are
identical, so there is no protection against the `code challenge` being
compromised. Applications using the `authorization code` grant with `PKCE`
should use the `S256` transform method which uses a base64 URL encoded `SHA256`
hash of the `code verifier` to protect it.

#### The Authorization Request

A sample application’s API authorization request with `PKCE`. It would be
directed to an `authorization server`’s authorization endpoint:

```http
GET /authorize?
response_type=code
& client_id=<client_id>
& state=<state>
& scope=<scope>
& redirect_uri=<callback uri>
& resource=<API identifier>
& code_challenge=<PKCE code_challenge>
& code_challenge_method=S256 HTTP/1.1
Host: authorizationserver.com
```

- `response_type`: Indicates the OAuth 2 grant type. `“code”` is used for the
  `authorization code grant` type.
- `client_id`: Identifier for the application, assigned when it registered with
  the `authorization server`.
- `state`: A nonguessable string, unique for each call, opaque to the
  `authorization server`, and used by the client to track state between a
  corresponding request and response to mitigate the risk of CSRF attacks.
  - It should contain a value that associates the request with the user’s
    session.
  - This could be done by including a hash of the session cookie or other
    session identifier concatenated with an additional unique-per-request
    component.
  - When a response is received, the client should ensure the state parameter
    in the response matches the state parameter for a request it sent from the
    same browser. This parameter should not include any sensitive information
    in plain text.
- `scope`: Indicates the scope of access privileges for which authorization is
  requested. For example: `“get:documents”`. This parameter should not include
  any sensitive information in plain text.
- `redirect_uri`: The `authorization server` sends its response with the
  `authorization code` to this callback URL at the application. The specified
  URI must exactly match the callback URI previously registered at the
  `authorization server` for the client application.
  - An exception to the exact match requirement is noted for the port number in
    local host redirect URLs in native applications.
- `resource`: Identifier for a specific API registered at the
  `authorization server` for which the `access token` is requested. Some
  implementations may use other names, such as `“audience”`. Primarily used in
  deployments with custom APIs. This parameter isn’t needed unless there are
  multiple possible APIs.
- `code_challenge`: `PKCE` `code challenge` derived from the `PKCE`
  `code verifier` using the `code challenge method` specified in the
  `code_challenge_method` parameter.
- `code_challenge_method`: `“S256”` or `“plain”`. Applications capable of using
  `S256` must use it.

While OAuth 2.0 allowed the URI registered with the `authorization server` to
contain wildcards, OAuth 2.1 now disallows the use of wildcards in the redirect
URI registered for a client `application`. This change reduces the possibility
of open redirect attacks.

The `resource` parameter was not in the original OAuth 2.0 specification. Since
that time, `authorization servers` have been written to handle requests for
multiple APIs and, in such cases, may support an additional parameter to
indicate a specific API for an authorization request. This parameter is defined
in the `Resource Indicators` for OAuth 2.0 extension. This parameter may be
called the `“resource”` or `“audience”` depending on the `authorization server`
implementation.

#### Response

The `authorization server` sends a response to the application’s callback,
specified in the `redirect_uri` parameter of the authorization request:

```http
HTTP/1.1 302 Found
Location: https://clientapplication.com/callback?
code=<authorization code>
& state=<state>
```

- `code`: The `authorization code` to be used by the `application` to request
  an `access token`.
- `state`: The state value, unmodified, sent in the authorization request. The
  `application` must validate that the state value in the response matches the
  state value sent with the initial request.

#### Calling the Token Endpoint

After receiving an `authorization code`, the application uses it in a second
request to the `authorization server`’s token endpoint to obtain the
`access token`.

```http
POST /token HTTP/1.1
Host: authorizationserver.com
Authorization: Basic <encoded application credentials>

Content-Type: application/x-www-form-urlencoded
grant_type=authorization_code
& code=<authorization_code>
& client_id=<client id>
& code_verifier=<code verifier>
& redirect_uri=<callback URI>
```

- `grant_type`: Must be `“authorization_code”` for the authorization code grant.
- `code`: The `authorization code` received in response to the authorization
  call.
- `client_id`: Identifier for the application, assigned when it registered with
  the `authorization server`.
- `code_verifier`: The `PKCE` `code verifier` value from which the
  `code challenge` was derived. It should be an unguessable, cryptographically
  random string between `43` and `128` characters in length, inclusive, using
  the characters A–Z, a–z, 0–9, “-”, “.”, “_”, and “~”.
- `redirect_uri`: The callback URI for the `authorization server`’s response.
  Should match the `redirect_uri` value passed in the authorization request to
  the authorize endpoint.

The response from the token endpoint will be similar:

```http
HTTP/1.1 200 OK
Content-Type: application/json;charset=UTF-8
Cache-Control: no-store
Pragma: no-cache
  {
    "access_token":"<access_token_for_API>",
    "token_type":"Bearer",
    "expires_in":<token expiration>,
    "refresh_token":"<refresh_token>"
  }
```

- `access_token`: The `access token` to use in calling the API. Different
  `authorization servers` may use different formats for `access tokens`.
- `token_type`: Type of token issued. `“Bearer”` for example.
- `expires_in`: How long the token will be valid.
- `refresh_token`: A `refresh token` is optional. It is up to an
  `authorization server`’s discretion whether to return a `refresh token` or
  not.

An `authorization server` may include an additional parameter `“scope”` to
indicate the actual scope of access granted with the issued `access token`.

- This is necessary when an `authorization server` issues an `access token` for
  a more restrictive scope than requested by the client.

There are different types of `access tokens` in use. Some
`authorization servers` issue an opaque `access token` in the form of an
encoded string. A `resource server` receiving such an `access token` can call a
token introspection endpoint at the issuing `authorization server` to obtain
information about the token, such as

- the client that requested the token
- the intended audience (`resource server`) for the token
- the token expiration
- whether the token has been revoked
- the scopes included in the token

The OAuth 2.0 Token Introspection specification defines the token introspection
endpoint and how `resource servers` can use it to obtain information about
opaque tokens issued by `authorization servers`.

Another common format for `access tokens` is a JSON Web Token (JWT). This is a
structured format that is cryptographically signed and contains various claims
about the token such as

- the client that requested the token
- the intended audience (`resource server`)
- when the token expires
- the scopes authorized for the token

With self-contained tokens, a `resource server` can obtain the claims directly
from the token without having to call a token endpoint at an
`authorization server`. The JSON Web Token (JWT) Profile for OAuth 2.0 Access
Tokens defines this type of token along with a set of mandatory and optional
claims.

The documentation for your authorization server should indicate the type of
`access token` it issues and the steps a `resource server` should take to
validate the token and obtain the claims represented by the token.

### Client Credentials Grant

The `client credentials grant` type is used when an application calls an API to
access resources the `application` owns. The application uses the
`client credentials grant` type and authenticates to the `authorization server`
with its own credentials to obtain an `access token`. The use of this grant
type requires that the `application` have the ability to maintain confidential
secrets (or use another secure mechanism) to authenticate itself.

```mermaid
sequenceDiagram
  participant Application
  participant Authorization Server
  participant Resource Server

  Application->>Authorization Server: 1. [Client credential]
  Note over Authorization Server: /token

  Authorization Server->>Application: 2. [Access token]

  Application->>Resource Server: 3. [Access token]

  Application->>Authorization Server: 4. [Client credential]
  Note over Authorization Server: /token

  Authorization Server->>Application: 5. [Access token]

  Application->>Resource Server: 6. [Access token]
```

1. The `application` sends an authorization request including the application’s
   credentials to the `authorization server`.
2. The `authorization server` validates the credentials and responds with an
   `access token`.
3. The `application` calls the `resource server` using the `access token`.
4. The steps repeat if the `access token` has expired by the next time the
   `application` calls the API.

No end-user interaction with the `authorization server` is required for this
flow. The application credentials serve as the authorization for the
`application` and are used to request an `access token` from the token
endpoint. Usually it uses a `client ID` and `client secret` obtained when the
application registered with the `authorization server`.

#### Client Credentials Grant: The Authorization Request

A sample token request for the client credentials grant type follows, with
parameter definitions the same as those for the previous grant type but with
the `grant_type` set to `“client_credentials”`.

```http
POST /token HTTP/1.1
Host: authorizationserver.com
Authorization: Basic <encoded application credentials>
Content-Type: application/x-www-form-urlencoded
grant_type=client_credentials
& scope=<scope>
& resource=<API identifier>
```

A successful `client credentials grant` request will result in a response from
the token endpoint with an `access token`.

### Implicit Grant (Removed in OAuth 2.1)

OAuth 2.0 defined an `implicit grant` type which was optimized for use with
`public clients` such as single-page applications. The use of this grant type
returned an `access token` to an `application` in one request. It was designed
at a time when the **CORS (Cross-Origin Resource Sharing)** standard was not
widely supported in browsers so that web pages could only “phone home.” In
other words, they could only make calls to the domain from which the page was
loaded which meant they couldn’t call an `authorization server`’s token
endpoint. To compensate for this limitation, the `implicit grant` type had the
`authorization server` respond to an authorization request by returning tokens
to the `application` in a redirect with a URL hash fragment.

```mermaid
sequenceDiagram
  participant User
  participant Browser
  participant Application
  participant Authorization Server
  participant Resource Server

  User->>Application: 1. to

  Application->Browser: 2. redirects Browser
  activate Browser
  Browser->>Authorization Server: to
  Note over Authorization Server: /authorize

  Authorization Server->>User: 3. asks to login

  User->>Authorization Server: 4. login with [Login credentials]

  Authorization Server->Browser: 5. redirects Browser with [Access token]
  activate Browser
  Browser->>Application: to
  Note over Application: /callback

  Application->>Resource Server: 6. with [Access token] to
  Note over Resource Server: /api endpoint
```

1. The user (`resource owner`) accesses the `application`.
2. The `application` redirects the browser to the `authorization server`’s
   authorize endpoint with an authorization request.
3. The `authorization server` prompts the user to authenticate and provide
   consent.
4. The user authenticates and provides consent for the authorization request.
5. The `authorization server` redirects back to the `application`’s callback
   URL with an `access token`.
6. The `application` uses the `access token` to call the `resource server`
   (API).

Since the OAuth 2.0 specification was originally published, CORS has become
supported by most browsers. Consequently, the `implicit grant` type isn’t
needed anymore for its original purpose. Furthermore, returning an
`access token` in a URL hash fragment exposes the `access token` to potential
leakage via browser history or referer headers. The OAuth 2.0 `implicit grant`
type has therefore been removed from OAuth 2.1. The `authorization code` grant
type with `PKCE` should be used instead.

New applications should avoid the use of the `implicit grant` type. Existing
applications should migrate to the `authorization code grant` type with `PKCE`
to reduce the risk from leaked tokens and align with OAuth 2.1.

### Resource Owner Password Credentials Grant (Removed from OAuth 2.1)

With the OAuth 2.0 `resource owner password credentials grant type`, the
application collected the user’s credentials directly instead of redirecting
the user to the `authorization server`. The `application` passed the collected
credentials to the `authorization server` for validation as part of its request
to get an `access token`. This grant type was intended to support situations
where an `application` was trusted to handle end-user credentials and no other
grant type was possible.

```mermaid
sequenceDiagram
  participant User
  participant Browser
  participant Application
  participant Authorization Server
  participant Resource Server

  User->>Application: 1. to
  
  Application->>User: 2. prompts for credentials

  User->>Application: 3. with [Login credentials] to

  Application->>Authorization Server: 4. with [Login credentials] to
  Note over Authorization Server: /token

  Authorization Server->Application: 5. with [Access token][Refresh token] to

  Application->>Resource Server: 6. with [Access token] to
  Note over Resource Server: /api endpoint
```

1. The user (`resource owner`) accesses the `application`.
2. The `application` prompts the user for their credentials.
3. The `user` provides their credentials to the `application`.
4. The `application` sends a token request to the `authorization server`’s
   token endpoint, with the user’s credentials.
5. The `authorization server` responds with an `access token` (and optionally a
   `refresh token`).
6. The `application` calls the `resource server`, using the `access token`.

The use of this grant type was not actively encouraged for several reasons.

1. it exposed the user’s credentials to the application.
2. there was also no specification for how to extend this grant to provide
    multi-factor authentication, so applications might have added multi-factor
    authentication capabilities in custom ways that might not have received
    adequate security review.
3. this grant type did not involve a user consent step, so an application could
   request any access it wished using the user’s credentials. The user had no
   way to prevent abuse of their credentials.

This grant type has been used for mobile apps, legacy embedded login pages, and
user migration scenarios. Some mobile applications used this grant type when
calling first-party APIs. This was often done because login flows that
redirected via browsers on mobile devices were originally perceived as
cumbersome.

OAuth 2.1 has incorporated the guidance of RFC 8252, OAuth 2.0 for Native Apps
to use the `authorization code grant`, combined with `PKCE`, for native
applications using the system browser.

This grant type was also used when login fields were embedded within an
application page. This was often done to conform to corporate user interface
standards or simply a desire to have an embedded login screen rather than the
disruption of a browser redirect.

For this grant type has been removed from OAuth 2.1, Applications should
redirect users to the `authorization server` using the
`authorization code grant type` with `PKCE`, rather than collect user
credentials themselves.

Another scenario for this grant type was user migration use cases. When users
needed to be migrated from one identity repository to another with incompatible
password hashes, the new system could prompt a user for their credentials, use
the `resource owner password grant` to validate them against the old system,
and, if valid, retrieve the user profile from the old system and store it and
the credentials in the new system. This avoided the necessity for large-scale
forced password resets when migrating identity information.

To mitigate some of the risk associated with this grant type, the client was
supposed to throw away the user credentials as soon as it had obtained the
`access token`, to reduce the possibility of compromised credentials. This
guidance, however, only addresses one aspect of the risk associated with this
grant type. With other risks remaining, the
`resource owner password credentials grant type` has been removed from
OAuth 2.1.

New applications should avoid the use of this grant type. Existing applications
should migrate to the `authorization code grant type` with `PKCE` to reduce the
risk from credentials exposed to client applications.

### Device Authorization Grant

>>>>> progress
