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

>>>>> progress
