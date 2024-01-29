# Chapter 16: Troubleshooting

> When you have eliminated the impossible, whatever remains, however
> improbable, must be the truth.
>
> —Sir Arthur Conan Doyle, British author, from The Sign of the Four (1890)

- [Chapter 16: Troubleshooting](#chapter-16-troubleshooting)
  - [Get Familiar with the Protocols](#get-familiar-with-the-protocols)
  - [Prepare Your Tools](#prepare-your-tools)
    - [Test Environment](#test-environment)
    - [Independent Browser Windows](#independent-browser-windows)
    - [Capture HTTP Traces](#capture-http-traces)
    - [View HTTP Traces](#view-http-traces)
    - [Make API Calls](#make-api-calls)
    - [View API Calls](#view-api-calls)
    - [View JWT and SAML 2 Tokens](#view-jwt-and-saml-2-tokens)
  - [Check the Simple Things](#check-the-simple-things)
  - [Gather Information](#gather-information)
    - [How Many Users Impacted?](#how-many-users-impacted)
    - [Contributing Environmental Factors?](#contributing-environmental-factors)
    - [Which Applications Impacted?](#which-applications-impacted)
    - [Consistent or Intermittent Issue?](#consistent-or-intermittent-issue)
    - [Worked Previously?](#worked-previously)
    - [Where Does Failure Occur?](#where-does-failure-occur)
    - [Replicate the Problem](#replicate-the-problem)
  - [Analyzing an HTTP/Network Trace](#analyzing-an-httpnetwork-trace)
    - [Capture a Trace](#capture-a-trace)
    - [Check Sequence of Interaction](#check-sequence-of-interaction)
    - [Check Parameters in Requests](#check-parameters-in-requests)
    - [Check HTTP Status Codes](#check-http-status-codes)
    - [Check Security Token Contents](#check-security-token-contents)
    - [Check for Security Token Validation Errors](#check-for-security-token-validation-errors)
  - [Collaborating with Others](#collaborating-with-others)

## Get Familiar with the Protocols

It is particularly helpful to know

- The sequence of interaction for different scenarios
- The parameters expected by each protocol endpoint
- The responses and error codes returned by each endpoint

Vendors may extend a specification when they implement a protocol.

## Prepare Your Tools

The following tools will help you debug an issue:

- An environment where you can duplicate a problem and test
- Two independent browser windows
- Tools to capture and view HTTP traces
- A tool with which to test API calls
- Tools to capture and view network traces of back-end API calls
- Tools for viewing and creating JWT and SAML 2.0 tokens

### Test Environment

### Independent Browser Windows

### Capture HTTP Traces

If you are collaborating with others, it is convenient to be able to dump the
HTTP trace to an HTTP Archive format file (`.har` file). Note, however, that a
`.har` file will capture everything, including the cleartext value of any
secret (client secret, password, API key, etc.) entered or transmitted during
the capture. If you can’t avoid capturing a secret by limiting a trace to only
a part of the interaction, you should edit the files to remove any sensitive
information and/or reset any secrets after capture so you don’t expose valid
secret(s). If you ask another person to send you a `.har` file, be sure to have
them take these precautions to reduce your liability from exposure to secrets
in the file.

### View HTTP Traces

A list of HTTP trace and `.har` file viewers as well as other useful debugging
tools is included in Appendix E.

### Make API Calls

Appendix E lists some current tools in this category.

### View API Calls

Appendix E lists a few tools for this purpose.

### View JWT and SAML 2 Tokens

A tool to decode and view the security tokens received by your application is
essential. Appendix E lists a few sites which are useful for viewing JWTs and
SAML 2 requests/ responses. These tools will allow you to inspect the contents
of the tokens. They may also provide you with a way to create test tokens for
sending to APIs for tests.

## Check the Simple Things

- Check the `identity provider` is accessible and not experiencing an outage.
- Check the credentials supplied are correct for the environment (test vs.
  production).
- Check the login account and credentials are not disabled or expired at the
  `identity provider`. You can do this by logging in to another application
  that uses the same `identity provider`.
- Check the application is using the correct URL for the `identity provider`.
- Check the client ID in the application matches that registered in the
  `identity provider`.
- Check the redirect/callback URL for the application exactly matches the URL
  registered in the `identity provider`.
- Check whether any certificates or cryptographic keys have expired.
- Check for any error messages logged by the application or `identity provider`
  to see if they provide valuable clues.

## Gather Information

The following questions will give you useful information to replicate the
problem and/or narrow down the possible source of an issue.

### How Many Users Impacted?

### Contributing Environmental Factors?

Testing with different browsers, devices, locations, and platforms can identify
if there are any environmental factors contributing to the issue.

Authentication and single sign-on can be impacted by browser settings for
third-party cookies and tracking prevention, so you should check browser
settings related to those features.

### Which Applications Impacted?

If only one or some applications experience the issue, it is probably caused by
the application code/configuration or the configuration for the application(s)
at the `identity provider`.

### Consistent or Intermittent Issue?

### Worked Previously?

If so, check for recent changes, such as the following:

- `Identity provider` outage
- Change to the `identity provider` API or API used by the failing application
- Network connectivity issue
- User password expired
- Recent software upgrades
- Recent browser or device configuration changes
- Certificate expiration or key rotation
- Servers with incorrect time due to NTP not running

These are common causes of failures of previously working systems.

### Where Does Failure Occur?

### Replicate the Problem

## Analyzing an HTTP/Network Trace

### Capture a Trace

A trace of HTTP and API calls will be one of the most valuable debugging aids. Using a debugger or other tracing tool, perform the failing authentication, authorization, or logout transaction starting from the beginning and going as far as you can through the sequence. When done, stop the trace to minimize the capture of irrelevant data. If you receive a trace captured by someone else, use a suitable tool to view it.

### Check Sequence of Interaction

For OIDC or OAuth 2, look first for a call to an “authorize” endpoint on the
`authorization server`. For SAML 2, look for a “SAMLRequest” message to the SSO
URL of the `identity provider`. Then look for the requests to prompt the user
to log in and for a redirect or response back to the application after the user
has authenticated. For OIDC/ OAuth 2, this will be to one of the callback URLs
configured in the `authorization server`. For SAML 2, this will be a
SAMLResponse message to the ACS (Assertion Consumer Service) URL configured in
the `identity provider`. If you do not see the complete sequence of expected
calls and responses, the place where the interaction started to deviate from
normal is a clue for where to start looking for issues.

Symptoms and possible causes:

- User never redirected to `identity provider`.
  - Application has incorrect URL for `identity provider`.
- User redirected to `identity provider` but no login prompt.
  - Application sent malformed request.
  - Incorrect `client ID` or `client secret`.
  - Error in `identity provider` login page configuration.
- User prompted to log in but receives error.
  - User error. Test with a different account.
  - User password has expired.
  - Wrong password for environment.
  - User account does not exist.
  - `Identity provider` lost connection to data store.
  - Misconfigured login page at `identity provider`.
- User logs in without error, but not redirected back to application.
  - Incorrect or invalid callback URL for application at `authorization server`
    (OAuth 2/OIDC).
  - Incorrect Assertion Consumer Service URL for application at
    `identity provider` (SAML 2).
  - Misconfigured extensibility feature at `identity provider`.
- User redirected back to application but receives authorization error, or
  application content doesn’t display.
  - Tokens or assertions returned to application are malformed or do not
    contain information expected by application.
  - Exchange of `authorization code` for token fails. Application not granted
    necessary scopes.
  - User does not have sufficient privileges in application.

### Check Parameters in Requests

Check the parameters in a request. For OAuth 2 or OIDC, check the following:

- The request is sent to the correct endpoint at the `authorization server`.
- Correct `response_type` used for the desired grant type or flow.
- The `scope` parameter value is adequate for the requested action.
- The callback URL matches what is registered in the `authorization server`.
- A `state` parameter value is specified, if required by `authorization server`.

For SAML 2 requests, check the following:

- The request is sent to the correct URL at the `identity provider`.
- The request specifies the binding for a response, if required.
- The correct certificates and public keys have been configured.

### Check HTTP Status Codes

Some common HTTP status codes for error scenarios and some possible causes:

- `400`: Malformed request. Check your request has the correct parameters and
  valid values for them.
- `401`: Unauthorized. Check the application or user has the necessary
  privileges for the request.
- `403`: Forbidden. Check the application or user has the necessary privileges
  for the request.
- `500`: Internal Server Error. Check the configuration at the authorization
  server or identity provider.
- `503`: Service Unavailable. Check if the authorization server or identity
  provider service is running and reachable.

### Check Security Token Contents

If the HTTP status code does not indicate there is an error, check the security
token(s) returned. Appendix E lists tools for viewing the contents of these
security tokens. Check the relevant security tokens to see if they are
formatted correctly and they contain the requisite information.

For ID Tokens, check

- The `ID Token` contains the correct user information in the “sub” claim.
- The `ID Token` contains any other claims expected by the application.

For `Access Tokens` that can be viewed, check

- Scopes granted to the application are adequate for the request.
- The `access token` contains any claims needed by an API.
- Audience for the token is correct for the intended recipient API.
- The `access token` is valid and has not expired.

For SAML 2 `SAMLResponse` messages:

- Subject element’s name `identifier` (`nameid`) element contains a user
  `identifier` expected by the application.
- Additional attribute statements expected by the application exist.

An `application` may need information for authorization conveyed in custom
claims. If such authorization data is missing from an `ID Token` or
`SAML 2 assertion`, the user may get an “unauthorized” message or possibly a
blank screen. If the `access tokens` are in JWT format, they can be viewed in a
JWT viewer. If they are opaque strings, however, you may need to use an
introspection endpoint on the `authorization server` to get information about
the token.

### Check for Security Token Validation Errors

The security tokens returned by OIDC and SAML 2 are digitally signed. They may
also be digitally encrypted. If an application cannot validate the signature on
a security token (or decrypt it if encrypted), it should log an error. Checking
application logs for such errors can help identify if this type of issue
exists. You can also check whether signing keys are being properly retrieved
and managed as incorrect key management can contribute to token validation
errors.

Errors with security tokens can also occur at `identity providers`. One
`identity provider` may delegate authentication for a user to another
`identity provider`. If the first `identity provider` does not receive a valid
authentication token from the remote provider, it should log the authentication
failure. `Identity provider` logs should be consulted if errors seem to
originate at the `identity provider` as these logs will often have the most
useful information.

## Collaborating with Others

A `.har` file or network trace can show interactions between an application and
an identity provider as well as an API if used. This can include the requests
made, the parameters, the timing of such interactions, and the responses
received. Such traces are extremely useful for debugging issues with
authentication, SSO, and authorization. When you receive a trace file, you’ll
need a viewer suitable for the type of trace captured. Appendix E includes a
few such tools.

You should remember that a trace may capture sensitive data, including a
username and password typed by a user or sensitive security tokens returned to
applications. If someone sends you a trace file, you may wish to warn them
about this so they can reset a captured password or invalidate any sensitive
tokens. This can reduce your liability. Furthermore, invalidating any
long-lived tokens captured and deleting trace files when you are done
troubleshooting is another good practice.
