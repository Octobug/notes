# Chapter 9: Sessions

> Everything measurable passes, everything that can be counted has an end. Only
> three things are infinite: the sky in its stars, the sea in its drops of
> water, and the heart in its tears.
>
> —Gustave Flaubert, French novelist, from The Letters of Gustave Flaubert
> (1980)

- [Chapter 9: Sessions](#chapter-9-sessions)
  - [Application Sessions](#application-sessions)
  - [Identity Provider Sessions](#identity-provider-sessions)
  - [Multiple Sessions](#multiple-sessions)
  - [Session Duration](#session-duration)
  - [Session Renewal](#session-renewal)
  - [Token Renewal](#token-renewal)
  - [Reconstituted Sessions](#reconstituted-sessions)
  - [Summary](#summary)
    - [Key Points](#key-points)

A user’s interaction with an application over a period of time is known as a
***session***.

An application needs a way to track that a user has been authenticated. Data
about whether, when, and how a user has authenticated may be tracked by an
application along with other information it maintains during a user’s session.
Sessions and session state may be handled differently for web applications,
single-page applications, and applications that run natively on a device, such
as mobile applications.

## Application Sessions

An application may need to track session information such as the identity of
the user, the user’s in-flight transactions, or how long the user’s session can
continue. This is usually accomplished via the creation of a unique
`session identifier` that represents session activity. This identifier can be
used to refer to additional details that may be stored in memory, a filesystem,
a database, or a shared service like Redis.

- For web applications, the session identifier and session information is
  usually stored in a `cookie` set by the application server, which is then
  sent by the browser with each request to the application server. When a
  request is received, the server can use the session identifier from the
  cookie to retrieve the user’s session information and process the request.
  Sometimes, if the session data is small enough, the entire data may be stored
  in the cookie, eliminating the need for server-side storage.
- For native applications and single-page web apps, storing data on the client
  side in memory or local persistent storage is a common strategy. When doing
  so, special care should be taken so as to not leave sensitive user data on
  the device.

With single-page applications and stateless back-end APIs, server-side sessions
for users are no longer required, but the concept of a session timeout persists
for other reasons. As applications increasingly leverage `identity providers`,
a user’s reauthentication can renew an `identity provider` session leveraged by
many applications. As a result, a user would not have to actively
reauthenticate to every application. Periodic reauthentication to the
`identity provider` is less onerous than having to reauthenticate to every
application.

Native applications often use stateless APIs, resulting in little server-side
cost for allowing a user’s native application session to continue for an
extended period of time. Sensitive applications, such as banking applications,
often still implement a session timeout on mobile devices.

In some cases, in order to improve user experience, mobile applications store
a refresh token in the device’s native storage system, such as Apple’s
Keychain, and enforce a check like requiring the user to provide a PIN or
Biometric factor to unlock the device. This validation, however, requires the
user to have access to the device and have previously enrolled their PIN or
Biometric factor to the device.

## Identity Provider Sessions

`Identity providers` also need to maintain a session for a user as a mechanism
to remember and recognize an authenticated user across multiple requests.

One solution is to create a session object with a session identifier and
attributes such as an identifier for the user, the authentication mechanism
used, the time of authentication, and when the session will expire. An
`identity provider` can create a cookie in the user’s browser that contains all
the session information or just a session identifier that maps to a server-side
session data store. The browser then sends the identity provider cookie with
every request to the `identity provider`. When a user is redirected to the
`identity provider`, it uses data from the cookie to detect if a user already
has an authenticated session.

After successfully authenticating a user, the identity provider sets or updates
in the user’s browser a cookie with session information and returns a security
token to the application. The application may then create or update its own
application session for the user. When the application session expires, the
application can check the status of the user’s session at the
`identity provider`. It may do this by redirecting the user’s browser to the
`identity provider`. Such a request will include any cookies set previously by
the `identity provider`, which contain the user’s session information. If the
user’s session at the identity provider is still valid, the `identity provider`
returns a new security token to the application without forcing the user to
authenticate again. Some `identity providers` may support alternative
mechanisms for checking the status of the user’s session at the
`identity provider` which can enable an application to avoid a browser redirect
when the user’s `identity provider` session is still valid.

## Multiple Sessions

```diagram
Model 1: [Application] (session)

Model 2: [Application] (session) --> [Identity Provider] (session)

Model 3: [Application] (session) --> [Authentication Broker] (session) -->
[Identity Provider] (session)
```

## Session Duration

With an idle session timeout, if a user takes certain types of actions tracked
by the application, the idle session timer gets reset, which extends the
session. Activity in an application may reset an application session’s idle
timer, but not be visible to an `identity provider` and consequently not reset
an idle timeout at the `identity provider`. The `identity provider`’s idle
timeout is typically only reset by requests visible to it, such as an
authentication request from an application.

If an application enforces an idle session timeout, it can be disruptive to a
user to suddenly lose an application session, especially if the user was in the
middle of entering a lot of data for a transaction. An application can mitigate
the potential for bad user experience by tracking the session duration,
providing a warning to users before the session times out, and resetting the
idle timeout if the user indicates they wish to continue. Alternatively, an
application can store the user’s progress locally and request the user to
reauthenticate when the session times out. Once the user has reauthenticated,
the application can retrieve the session data, allow the user to continue
working, and submit the user’s work to the back end, depending on where the
user left off.

For a maximum session timeout, it may help to evaluate how frequently or
infrequently the user should reauthenticate to confirm they are still in
control of the session as well as how frequently user profile information might
need refreshing.

With many ways for sessions to terminate, and multiple sessions in the mix, it
is important for application designers to specify or understand the impact on
other sessions when any session is terminated. For example:

- if an application session expires, should the application request the
  termination of the user’s session at an `identity provider`?
- If a user’s `identity provider` session is terminated, should that trigger
  the immediate termination of a session in other applications using the same
  `identity provider`?
  
The options to consider may be constrained by `identity provider` policy when
an `identity provider` is controlled by an external party, but designs should
still enumerate what happens for different session termination scenarios.

An application may want to periodically check the status of a user’s session at
an `identity provider`. This may be done so the application can terminate its
own session when the `identity provider`’s session has ended. This may also be
done when an application’s session for a user has timed out, with the
application checking the state of the user’s `identity provider` session as
part of its own session renewal process.

## Session Renewal

When an application’s session for a user expires, the application may wish to
enable the user to renew the session. It can do this by redirecting the user
back to the `identity provider`. The `identity provider` can authenticate the
user if it doesn’t have a valid session for them and return new security tokens
to the application per the parameters in the application’s authentication
request. If the user’s `identity provider` session is still valid, the user
would not need to reauthenticate, and the application would receive new
security tokens based on the user’s existing session. The application can then
use information in the new security tokens to renew the user’s application
session.

Applications can use parameters in an authentication request to suppress or
force active authentication. It may be desirable, for example, to have
reauthentication occur if a certain amount of time has passed since the user
last actively authenticated. With OIDC, the optional `prompt` parameter can be
added to an authentication request to force or suppress authentication at the
`OpenID Provider`. The optional `max_age` parameter can be used to control how
long a user can go without actively reauthenticating. Applications using
`max_age` should still check the `auth_time` claim in the `ID Token` to ensure
the requested `max_age` was followed. The use of `max_age` and `auth_time` is
useful if an `OpenID Provider` has a relatively long maximum or idle timeout,
and a particular application requires more frequent authentication.

With SAML 2, applications can use the `ForceAuthn` attribute of the
authentication request to force the `identity provider` to actively
authenticate the user. An application can check the `AuthnInstant` element of
the SAML response to see when authentication occurred. Such authentication
request parameters give applications some measure of control over whether the
user is actively reauthenticated when they are redirected to the
`identity provider`. The `auth_time` claim in an `ID Token` and the
`AuthnInstant` claim in a SAML response also provide information back to
applications that can be used in subsequent security decisions.

`Identity providers` may support alternative methods for checking the status of
a user’s session at the `identity provider`. If a user has a valid session at
an `identity provider`, such methods may enable renewing an application session
without requiring a browser redirect. On the other hand, if a user’s
`identity provider` session is no longer valid, the user can be redirected to
renew the `identity provider` session.

## Token Renewal

In addition to renewing a session, an application may need to periodically
renew a security token. The application may have received an `ID Token` and
possibly an `access token` to call an API. An application may need to
periodically request a new `ID Token` to ensure it has up-to-date claims for an
authenticated user. An application may wish to request a new `access token`
because it needs to call an API and the `access token` it requested previously
has expired. It is considered a best practice in many cases, and especially
with `public clients`, to issue `access tokens` with short expiration times and
renew the `tokens when` needed. As a result, the need for new tokens may occur
throughout a session’s existence.

Traditional web applications and native applications may be able to obtain a
`refresh token` for use in renewing `ID Tokens` and/or `access tokens`, but
they are not required to do so. Using a `refresh token` to renew tokens avoids
the need to interrupt the user experience, but back-channel requests with a
`refresh token` may not update the `identity provider`’s session cookie,
resulting in a faster idle timeout.

Single-page applications implemented as `public clients` cannot securely store
and handle `refresh tokens`. They should use an approach that doesn’t rely on
`refresh tokens` unless their `authorization server` implements measures
against leaked `refresh tokens` such as `refresh token rotation` or
[sender-constrained refresh tokens](https://datatracker.ietf.org/doc/html/draft-ietf-oauth-security-topics-21#section-2.2.2).
Applications that do not receive `refresh tokens` can redirect the user to the
`OpenID Provider` when new tokens are needed. If the user has a valid session,
the application will receive new tokens. If the user does not have a valid
session, the request will trigger authentication and consent as needed, before
new tokens are issued. Even applications with `refresh tokens` may want to use
the redirect approach periodically to update the `identity provider`’s session
cookie and idle timeout.

Redirecting the user to the `OpenID Provider` and back, however, involves
challenges as it can interrupt the user experience. With single-page
applications, this can result in the loss of a user’s work unless the
application saves the user’s application state and restores it after the return
from the `OpenID Provider`.

One alternative has been to do the redirect using a hidden iframe in the
application and setting the `prompt` parameter to `none` to avoid interrupting
the user experience. If the user had a valid session, the application would
receive new tokens. If not, the application would receive an error response and
could redirect the user again without the `prompt=none` option to trigger
authentication. However, technology changes such as Apple’s Intelligent
Tracking Protection (ITP) have made the hidden iframe redirect option less
viable.

## Reconstituted Sessions

An application that needs a session timeout and falls in this category may want
to provide an improved user experience by offering a session that can be
reconstituted after session timeout. With this scheme, upon session timeout,
the system invalidates the session for further use, but retains a memory of the
session and the identity associated with it, so that the session state can be
restored to its former state if the user actively reauthenticates. Such a
session is terminated and permanently deleted by an active user logout, not a
session timeout. That said, it is still desirable to have a limit for how long
a session stays in a dormant state, to reduce backward compatibility issues and
to avoid storing session data forever for sessions orphaned when a user deletes
their session cookies.

## Summary

### Key Points

- A user’s interaction with an application for a duration of time is a session.
- Session state may contain data about the user and authentication event.
- In solutions with single sign-on, a user may have multiple authentication
  sessions.
- Sessions may be subject to an idle and maximum timeout.
- Session duration is typically based on the sensitivity of the resources
  accessible from the session, the application delivery platform, and the type
  of application.
- A continuous authentication session can be used to remember and reconstitute
  user sessions which have expired.
