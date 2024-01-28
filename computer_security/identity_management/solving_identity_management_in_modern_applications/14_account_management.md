# Chapter 14: Account Management

> And yet in our world, everybody thinks of changing humanity and nobody thinks
> of changing himself.
>
> —Leo Tolstoy, from “Three Methods of Reform”

- [Chapter 14: Account Management](#chapter-14-account-management)
  - [Identity Attributes](#identity-attributes)
    - [User Profile Attributes](#user-profile-attributes)
    - [Update Process](#update-process)
    - [Cached Identity Attributes](#cached-identity-attributes)
    - [Updated Identifiers](#updated-identifiers)
  - [Credential Reset](#credential-reset)
  - [Account Recovery](#account-recovery)
  - [Password Guidance](#password-guidance)
  - [Helpdesk Reset](#helpdesk-reset)
  - [Notification](#notification)
  - [Summary](#summary)
    - [Key Points](#key-points)

## Identity Attributes

### User Profile Attributes

A user’s identity information may change over time for multiple reasons. Some
updates will come from users themselves, and others may come from
administrators. Many privacy regulations, including
[Article 15 of the GDPR (EU General Data Protection Regulation)](https://gdpr.eu/article-15-right-of-access/),
mandate that users must be able to access and correct data about themselves
held by a data controller.

### Update Process

If your application delegates authentication to `social providers`, the user
may need to update some profile attributes at the `social provider`. Similarly,
if your application delegates authentication to an `enterprise provider`, the
user may need to update identity information there. In addition to updates made
by users themselves, administrators or automated administrative processes may
make updates to user identities. These updates often impact attributes that are
controlled by the owner of the `identity provider` instead of the user and may
involve attributes used for access control decisions in applications such as a
job level, department, and roles or group memberships.

If user profile data in your application comes from multiple sources, you must
make clear how and where to update each attribute. Your application may pull
some user attributes from an `identity provider` and augment that data with
additional data that is collected and managed by the application. In this case,
users need to know where to update different attributes. Any administrative or
support processes for your application will also need to know how and where to
update each attribute.

### Cached Identity Attributes

When user profile data from an `identity provider` is cached by an application,
the necessary frequency for updating the cache must be considered. When a user
authenticates, the application may receive user profile attributes in a token
or assertion from the authenticating `identity provider`. The application will
have the information during a user’s login session and may store the
information in its own repository for use when the user is offline. A cache,
however, will become stale if the user attribute information changes at the
`identity provider`.

Each time a user logs in to an application via an `identity provider`, the
application should receive user profile information from the provider that is
current at the time of the authentication. In an enterprise scenario, if a
user’s privileges, such as roles or group memberships are changed at the
`identity provider`, it may be problematic if an application has an `ID Token`
or SAML assertion with out-of-date profile information. The same issue holds
for self-contained `access tokens` that contain claims with stale user profile
attributes.

To mitigate the risk of outdated information, applications can request updated
profile information periodically or before executing sensitive transactions
which require up-to-date profile attributes. This has been done by issuing a
redirect to the `identity provider` with a parameter that suppresses active
interaction with the user for authentication. However, browser changes to
prevent tracking may impact the feasibility of this approach, especially for
single-page applications. Future browser changes may mitigate some of the
issues created by tracking prevention, but in the meantime, an alternate
approach is to use a `refresh token` to request new tokens.
`Refresh token rotation` should be used to mitigate the risk of compromised
`refresh tokens`.

Applications which obtain user profile information from identity providers and
store a copy in their own database have an additional challenge. If users do
not log in frequently, the user profile information in the application database
may get stale. This can be an issue for reports that include user profile data
if the reports are run by other users, such as administrators. If up-to-date
information is needed in between user logins, it may be possible for an
application to query an API at the `identity provider` for updated information.
Alternatively, if an `identity provider` supports a capability whereby a log
entry about an altered identity profile triggers a webhook, a webhook could be
written to push identity profile changes to another system. The feasibility of
such an approach may be impacted by firewalls and accessibility between the
systems involved. Otherwise, periodic synchronization may be needed.
Historically, such synchronization has been done with proprietary solutions,
but the [System for Cross-domain Identity Management (SCIM) protocol](https://tools.ietf.org/html/rfc7644)
was created to standardize the synchronization of identity updates across
domains, typically between corporate `identity providers` and `relying parties`.
Adoption of SCIM is not widespread and may not be supported for scenarios where
individual users own their accounts at `social providers`, but for enterprise
scenarios, SCIM may be worth considering over proprietary one-off solutions,
especially if an entity anticipates having many partners with which to
synchronize.

### Updated Identifiers

A special case to accommodate is the situation where a user needs to update the
attribute which serves as an `identifier` for their account at a remote
`identity provider`. If a remote `identity provider` identifier for a user is
changed, the next time the user logs in, the `application` will receive the new
`identifier`. If the `application` account or data is tied to the old
`identifier`, and the user logs in with a new `identifier`, the user may not be
able to access the application account or data associated with the old
`identifier`.

- The issue can be avoided if the `identity provider` delivers to applications
  an internal `identifier` that never changes, in addition to other user
  profile attributes.
- Alternatively, if explicit account linking is used, a user may be able to
  unlink the old identity before the change and relink to the new `identity`
  after the change, but this requires forethought on the part of a user which
  may not be realistic.

## Credential Reset

An application that delegates authentication to an `identity provider` does not
have to store credentials or implement credential reset functionality because
the credentials are at the `identity provider`. An `application` can simply
provide a link or instructions that point to the credential reset function at
the appropriate provider. If you use an identity provider service, you should
be sure to select one that supports self-service credential update and account
recovery.

## Account Recovery

In many cases, an `application` relying on an `identity provider` may be able
to leverage account recovery mechanisms provided by the `identity provider`. It
then becomes important to select provider(s) with reasonably secure
self-service account recovery mechanisms. Solutions that prompt a user for
answers to previously established security questions are problematic as the
answers can often be looked up or guessed. They also depend on the user
remembering the answers, which is not always the case. Schemes that require
users to download recovery codes rely on users saving the codes in a secure
place, which may not be dependable either.

A solution that sends a password reset link to an email address previously
registered with the account avoids the drawbacks of the previous schemes. This
depends, however, on the owner of the account being able to access the email
for the email address associated with the account. Sending a one-time code via
SMS to a previously registered cellphone number in the user’s profile relies on
the number being current and the security of SMS messages. There have also been
[SIM-swapping attacks](www.vice.com/en/article/d3n3am/att-and-verizon-employees-charged-sim-swapping-criminal-ring)
and other [demonstrated vulnerabilities](www.vice.com/en/article/y3g8wb/hacker-got-my-texts-16-dollars-sakari-netnumber)
that allowed phone numbers to be rerouted to phones controlled by attackers.
These attacks have not been widespread, but raise some questions about the
future security of using SMS messaging. Enabling users to set up a primary and
one or more backup authentication mechanisms may provide the best defense
against any one authentication mechanism becoming broken or compromised.

## Password Guidance

Interesting new research by NIST has examined the effectiveness of previous
[password guidelines](https://pages.nist.gov/800-63-3/sp800-63b.html#appA).
This research by NIST suggests that some elements of the past guidance may not
have been as effective as expected.

Their new guidance suggests that the size of a password matters more than the
password complexity as user-selected password complexity is somewhat
predictable, and rate limiting on failed password attempts may be a more
effective approach.

Users are recommended to select a long passphrase that consists of several
words but is not a common or guessable phrase. Users are recommended to change
a password if there is evidence it has been compromised, but rate limits on
failed passwords and checking for breached passwords may be more effective than
periodic forced password resets. Authentication services should implement rate
limiting on failed login attempts and check username/password combinations
against databases of known breached passwords to protect against brute force
attacks and compromised passwords.

## Helpdesk Reset

If done remotely, such as over the phone, it requires the helpdesk staff to
have knowledge of secret information with which to validate an account owner.

Examples of secrets that have been used in the past are a portion of a
government-issued identity number, information on recent transactions, or
answers to secret questions. This process has the advantage of providing human
assistance, but may expose sensitive information to risk of compromise. If the
sensitive information used to validate an account owner is used at other sites,
a compromise of the information at one site may allow a malicious actor to take
over a person’s accounts elsewhere.

If assisted credential reset is handled in person, account owner validation can
leverage government-issued identification documents, avoiding exposure of other
sensitive identity attributes.

Given the drawbacks with assisted credential reset, for both cost savings and
security, self-service credential reset capability should be preferred for most
scenarios.

## Notification

Whether a user is updating user profile attributes, resetting a password, or
performing other account management transactions, it is useful to send
notification of the changes to the previously registered email, phone number,
or address for the account.

Notifications can help users recognize if they’ve made an error, such as
accidentally making a change they did not intend. Notifications can also
provide an early warning system if an account has been taken over by an
unauthorized entity. The notification message should be sent using the prior
contact information when contact information has been changed and include
instructions on what to do if the user did not intend or initiate the changes.
To the extent that users pay attention to notifications, such messages can be a
useful tool to recognize and combat fraud.

## Summary

### Key Points

- User identity attributes may need to change over time.
- Privacy regulations may mandate a process for users to update identity
  information.
- Account management may be delegated to `identity providers` when the
  attributes to be changed reside at the `identity provider`.
- If a user changes their `identifier` at an `identity provider`, it may impact
  their ability to access application accounts tied to an old `identifier`
  unless a solution is provided for this scenario.
- Credential reset and account recovery may be delegated to `identity providers`
  for many common scenarios, but exceptional cases such as account takeover may
  need to involve application owners as well.
- Notification messages to confirm account changes should be sent to users,
  with instructions on what to do if they did not intend or initiate the
  changes.
