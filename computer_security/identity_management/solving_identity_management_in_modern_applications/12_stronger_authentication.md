# Chapter 12: Stronger Authentication

> Come, let us hasten to a higher plane, Where dyads tread the fairy fields of
> Venn, Their indices bedecked from one to n, Commingled in an endless Markov
> chain!
>
> —Stanislaw Lem, Polish author of science fiction, philosophy, and satire,
> from The Cyberiad (1965)

- [Chapter 12: Stronger Authentication](#chapter-12-stronger-authentication)
  - [The Problem with Passwords](#the-problem-with-passwords)
  - [Stronger Forms of Authentication](#stronger-forms-of-authentication)
    - [Multi-factor Authentication](#multi-factor-authentication)
    - [Step-Up Authentication](#step-up-authentication)
    - [Multi-factor Authentication and SSO](#multi-factor-authentication-and-sso)
  - [Session Timeouts](#session-timeouts)
  - [Requesting Authentication Mechanisms](#requesting-authentication-mechanisms)
    - [SAML 2](#saml-2)
    - [OIDC](#oidc)
  - [Step-Down Authentication](#step-down-authentication)
  - [Deployment](#deployment)
  - [Summary](#summary)
    - [Key Points](#key-points)

The static passwords that still enable access to many Internet services are
considered a relatively weak authentication mechanism.

## The Problem with Passwords

## Stronger Forms of Authentication

- one-time password (OTP)
- Another approach involves the use of a pair of cryptographic keys.
  - A private key is securely encapsulated in a device such as a smartcard,
    hardware authentication device, or mobile phone.
  - The entity wishing to authenticate the user sends a challenge nonce to the
    authenticator device.
  - The secret key encapsulated in the device is used to sign the challenge
    nonce.
  - With some multi-factor authenticator devices, the user has to enter a PIN or
    provide a biometric factor to unlock the device before it will sign the
    challenge nonce, providing a layer of protection against theft of the
    device.
  - The authenticating entity receives a message back from the device with the
    signed challenge nonce and validates the signature, using a public key that
    corresponds to the private key on the device.
    - The public key would have been previously registered during a setup step.
  - If the signature is valid, this process indicates that the user (subject)
    attempting to log in possesses the authenticator device associated with the
    account.

With this approach, authentication is based on possession of the device with
the key as well as a factor (such as a PIN or fingerprint) to unlock the device.

An industry standard was defined for such hardware security keys called
[Fast Identity Online (FIDO) Universal Second Factor (U2F)](https://fidoalliance.org/specifications/).
This initial protocol has since been extended with newer protocols that add
additional features, known collectively as FIDO2. Yubico provides many types of
security keys compliant with FIDO U2F and FIDO2 and is a well-established
vendor of such products. Newer offerings are also available from vendors such
as Google (Titan key), Thetis, TrustKey, and Feitian.

Biometric factors such as

- fingerprints
- facial scans
- retinal scans
- voiceprints

can serve as stronger forms of identification.

It’s worth noting that `knowledge-based authentication (KBA)`, which involves
answering security questions, has similar risks to passwords. Answers can be
guessed, sourced from public information, or stolen and then used by a remote
entity without the owner’s knowledge. The strength of authentication methods
can be classified, and one example classification scheme is the
[NIST 800-63 Security standard](https://pages.nist.gov/800-63-3/sp800-63b.html)
which defines criteria for three levels of authenticator assurance.

### Multi-factor Authentication

These typically include something you know as well as something you have and/or something you are.

- The something you know can be a password or passphrase.
- The something you have may be a device such as a mobile phone or a hardware
  security device used for one of the authentication mechanisms.
- The something you are can be a biometric factor such as a fingerprint,
  voiceprint, or facial scan.

[Section 6.2 of NIST publication 800-63-3](https://pages.nist.gov/800-63-3/sp800-63-3.html#sec6)
shows one example of how to approach the selection of an appropriate
authenticator assurance level for a deployment.
([NIST Special Publication 800-63B](https://pages.nist.gov/800-63-3/sp800-63b.html)
has the accompanying list of types of authentication for each authentication
assurance level.)

### Step-Up Authentication

Step-up authentication is the process of authenticating with a stronger form of
authentication in order to elevate the authentication assurance level of an
existing authentication session.

Applications with features that vary in sensitivity can use step-up
authentication to require stronger authentication for more sensitive
transactions. Step-up authentication facilitates a model where the strength of
the authentication mechanism required for a situation is commensurate with the
risk inherent in the protected resources involved.

### Multi-factor Authentication and SSO

The use of multi-factor authentication can impact the user experience with
single sign-on. If a user first accesses an application that only requires
password authentication, and then moves on to a second application that uses
the same `identity provider` as the first but requires a stronger form of
authentication, such as entering a one-time code sent to their phone, the user
will be prompted to satisfy that stronger authentication requirement.
Therefore, when rolling out single sign-on deployments where applications may
require different levels of authentication strength, you should avoid wording
such as “login once, access everything” because users may in fact have to
authenticate again with a stronger mechanism to access more sensitive
applications. You can reduce user confusion by warning users in advance if a
particular action requires stronger authentication. Don’t make such notices
intrusive, however, or they will create more exasperation than they avoid.

## Session Timeouts

Shorter session timeouts for more privileged sessions reduce the chances of
highly privileged sessions being hijacked for malicious purposes and align with
the security principle of least privilege.

## Requesting Authentication Mechanisms

Applications may need a way to request an identity provider use a particular
class of authentication mechanism to achieve a desired level of authentication
assurance. This can be done with an authentication context class reference. An
authentication context involves several factors, such as the identification
processes used to create an account, the protections against credential
compromise, and the authentication mechanism used. An
`authentication context class` represents a set of authentication methods. An
`authentication context class reference` is an identifier for an
`authentication context class`. Authentication context classes and class
references are often defined by an `identity provider`, but may be worked out
by a `service provider` in conjunction with an `identity provider`. The
following sections explain how applications can request a particular
`authentication context class` and how `identity providers` can provide claims
to convey the `authentication context class reference` and/or authentication
mechanism(s) used.

### SAML 2

A SAML 2 authentication request can specify an application’s desired
`authentication context class` using the `<RequestedAuthnContext>` element. A
SAML 2 authentication response will show the `authentication context class` used
to authenticate a user in the `<AuthnContext>` element of the authentication
assertion, if the `identity provider` provides this information.

The application (`service provider`) and `identity provider` must establish in
advance the definitions for different `authentication context classes`. The
document [Authentication Context for the OASIS Security Assertion Markup Language (SAML) V2.0](https://docs.oasis-open.org/security/saml/v2.0/saml-authn-context-2.0-os.pdf)
lists several predefined authentication context classes which may be used.

### OIDC

OIDC clients can request one or more `authentication context classes`, in order
of preference, using the following parameter to the authentication request:

- `acr_values` – Authentication context class reference

An `ID Token` issued to an application can contain the following parameters to
convey the `authentication context class` and authentication methods used to
authenticate the user (subject) referenced in the `ID Token`.

- `acr` – Authentication context class reference, an identifier for an
  `authentication context class`
- `amr` – Authentication method reference, the identifiers for one or more
  methods used to authenticate a user

The `application` and `OpenID Provider` must establish the values and meaning
for `acr` and `amr` values used. There are specifications for standard values
for these claims. The draft specification for
[OpenID Connect Extended Authentication Profile (EAP) ACR Values 1.0](https://openid.net/specs/openid-connect-eap-acr-values-1_0.html)
lists `acr` values, and the
[RFC8176 specification for Authentication Method Reference Values](https://datatracker.ietf.org/doc/html/rfc8176)
lists `amr` values.

## Step-Down Authentication

To align with the security principle of "least privilege", a user should
operate at the minimum privilege level necessary for a particular task. In an
environment where sessions can exist with different assurance levels or
authentication contexts, with higher-level sessions that enable access to more
sensitive resources, users would ideally be able to "step down" their session’s
authentication assurance level when they no longer need the elevated
privileges.

This reduces the damage that can be done if a session is hijacked as well as
the risk from simple human error when operating at a higher privilege level.
It is probably more practical to simply rely on short session timeouts for more
privileged sessions as well as user logout for immediate termination of a
session.

## Deployment

Security, usability, maintainability, cost, and recovery are all factors to
consider when choosing one or more forms of MFA (multi-factor authentication)
for your project.

The security of SMS codes sent to phones is threatened by several types of
attacks.

- In a SIM-swapping attack, an attacker impersonates a cellular customer and
  requests that the victim’s phone number be associated with a new SIM card
  possessed by the attacker. This enables the attacker to intercept the
  victim’s calls and SMS messages.
- Other attacks have intercepted voice and SMS communications on cellular
  networks by targeting Signaling System No. 7 (SS7), a protocol layer in the
  infrastructure that provides connectivity between mobile phone networks.
  
Such attacks are not yet widespread, but may increase in the future. One
approach to mitigate this risk is to require the user to re-enter their
password when they enter the code, but users may find this annoying, especially
if they do not understand the purpose. Your projects should evaluate the
current status of SMS attacks before deciding to rely on SMS codes for
multi-factor authentication.

Using an application on a user’s mobile phone to generate a one-time password
avoids the drawbacks associated with SMS messages and specialized authenticator
tokens, but has other issues. If a user’s phone is broken, lost, or stolen, the
user may temporarily lose the ability to log in while they get a new phone,
install the generator apps on their new phone and go through an administrative
process at each website they use to authenticate them through other means,
remove the old phone, and reenroll with their new phone.

Authentication devices with cryptographic keys are becoming more common. The
authentication secret in this case, a private key, never leaves the device. This
means a user cannot be phished or tricked into revealing it.

In the past, a given website may have only supported specific security keys or
keys from a specific vendor, potentially requiring a user to have more than one
across different websites. The `FIDO2` protocols and interoperability testing
should help alleviate this issue by facilitating interoperability between
different vendors’ security keys and different websites needing to authenticate
users.

With OTP-generating apps on phones or hardware authentication devices, an
administrative process is required to deregister an old device and associate a
new device with a user’s account. If the old device is available and
functioning, the user can authenticate with it in order to perform this
administrative step themselves. If, however, the device is not available, a
user cannot authenticate. Some sites provide the ability to download a set of
backup codes for this scenario. The backup codes are system-generated so they
are typically long, unique to a particular site, and can only be used once. The
use of backup codes, however, relies on the user safely storing the backup
codes, noting the site they are for, and having them readily available if their
primary authentication device is no longer usable. If a user does not have
their backup codes, it is necessary to authenticate them through another means
before registering a new device. This is to prevent hackers from bypassing
multi-factor authentication by calling up and claiming to be the user and that
they’ve lost their phone.

Biometric factors have the drawback that if used for authentication and
compromised or damaged, they cannot be reissued. In other words, a person cannot
be issued a new finger if a hacker is able to capture their fingerprint and use
it with biometric fingerprint authentication. If a biometric authentication
factor is compromised, it is necessary to either change the factors used or
change what the authentication algorithm looks for in the existing factors.

Beyond security considerations, be sure to consider usability and ongoing
maintenance requirements.

- Testing multi-factor authentication mechanisms and the use of step-up
  authentication with users who are representative of the target user
  population is valuable to identify any usability issues before widespread
  rollout.
- Be sure to test failure (unsuccessful) cases as well as successful cases.
- For every failure case, consider what a user would need to do to recover from
  the situation and make sure it is reasonable.
- Evaluate authentication devices for their durability as well as likely
  battery life if applicable to avoid unexpected costs for replacing
  broken/dead hardware devices.
- Depending on the type of authenticator chosen, you may have to budget for
  replacing lost and damaged devices. When replacement is necessary, you’ll
  also need a process for quickly but securely replacing lost or damaged
  devices to restore a user’s ability to log in.
  
Be sure to plan for secure distribution, replacement, and revocation of
authentication mechanisms as part of any deployment.

## Summary

Both OIDC and SAML 2 allow `applications` to request that an `identity provider`
authenticate a user with a particular `authentication context class` of
authentication mechanisms and to receive information about the
`authentication context class` and/or `authentication method(s)` used to
authenticate a user. You should also plan to terminate higher-level sessions in
a timely manner via shorter session timeouts or logout.

### Key Points

- Static passwords are considered a weak form of authentication.
- The compromise of a static password may not be noticed until damage is done.
- It is harder for remote hackers to impersonate a user when authentication
  requires physical devices in the user’s possession.
- Multi-factor authentication relies on multiple factors, such as something you
  know, something you have, and/or something you are.
- Step-up authentication involves authenticating with a stronger form of
  authentication to elevate the authentication assurance level of a session.
- Both SAML 2 and OIDC allow an `application` to request an `identity provider`
  use a specified `authentication context class` when authenticating users.
- To support the principle of least privilege, it may be desirable to have
  shorter session timeouts for elevated sessions required to access sensitive
  resources.
- Multi-factor authentication provides greater authentication assurance, but
  involves considerations of usability, maintenance, cost, and how to securely
  recover when a user’s multi-factor authentication device is lost, broken, or
  stolen.
