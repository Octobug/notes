# Chapter 18: Less Common Requirements

> Two roads diverged in a wood, and I — I took the one less traveled by, And
> that has made all the difference.
>
> —Robert Frost, American poet, from “The Road Not Taken” (1916)

- [Chapter 18: Less Common Requirements](#chapter-18-less-common-requirements)
  - [People](#people)
    - [Family Accounts](#family-accounts)
    - [Temporary Positions](#temporary-positions)
    - [Status Transition](#status-transition)
    - [No Email Address](#no-email-address)
    - [Identity Defederation](#identity-defederation)
  - [Accounts](#accounts)
    - [Mergers and Acquisitions](#mergers-and-acquisitions)
    - [Account Linking](#account-linking)
    - [Progressive Profiling](#progressive-profiling)
    - [Impersonation](#impersonation)
    - [Delegation](#delegation)
  - [Environment](#environment)
    - [Shared Workstations](#shared-workstations)
    - [Identity Provider Discovery](#identity-provider-discovery)
    - [Multitenant Applications](#multitenant-applications)
  - [Summary](#summary)
    - [Key Points](#key-points)

## People

### Family Accounts

For accountability purposes, it is often better to allow the association of
different user accounts, each with their own login credential(s), with a family
or shared account rather than encouraging multiple users to log in with the
same user account.

### Temporary Positions

A best practice is to set an expiration date for temporary accounts and require
the manager of a temporary worker to periodically approve renewal of the
temporary account. If the account is not renewed, it should be disabled.

### Status Transition

If temporary workers are registered and administered separately from employees,
but all sources feed into one identity provider, it might be possible for two
accounts for the same person to exist at the same time which might cause
ambiguity at best or unauthorized access at worst. If a person can transition
from one status to another, processes should be designed to avoid duplicate
accounts for the same person.

### No Email Address

- Some businesses do not issue email addresses to employees who have no need to
  read email on the job.
- Parents of younger children may not allow them to have an email address.
- Some organizations may provide their users an email address but have privacy
  guidelines that prohibit the use of email addresses as account identifiers.

Applications may need to accommodate users who do not have email addresses or
restrictions on where an email address can be used.

### Identity Defederation

For example, when a person terminates their relationship with an employer, they
may need to use a personal account to access resources that they previously
accessed via an account at the employer’s `identity provider`. If a company
provides to employees a pension program, employees might sign in to the
external pension website via their employer’s chosen `identity provider`. If an
employee quits their job, their account at the corporate `identity provider`
will cease to exist. The user will need their account at the pension system to
be defederated from their employer’s `identity provider` so they can log in
with an individual account local to the pension system, or perhaps federated to
another `identity provider` operated by a government entity or a social
provider.

In general, defederation is needed when a user can sever a relationship with an
organization, but is still entitled to access resources there that they
previously accessed via a federated identity operated by that organization.

## Accounts

### Mergers and Acquisitions

When a company acquires or merges with another company, it is common for the
identity repositories of the two companies to be merged, which may require
resolving duplicate usernames to achieve username uniqueness in the new merged
entity.

Changing usernames to eliminate duplicates may impact applications. When a user
is authenticated by a centralized identity provider, an identifier for the user
is passed to applications. If an application maintains a user profile or data
records that contain the user’s identifier, the identifier passed to the
application from an identity provider must match the identifier for the user in
the application. If a user’s identifier is changed as part of a merger,
(`mary@domain1.com` becomes `mary@domain2.com` or `mary` becomes `mary.smith`),
an identity provider may need to translate identifiers so the user can
authenticate with a new identifier but have their former identifier passed to
legacy applications still using the old identifier.

Alternatively, user identifier changes can be implemented in applications. This
should be done with care, however, as it may require updating data records
within the application besides the user’s profile. This can become complicated,
so it may be easiest to have an identity provider pass old usernames to legacy
applications until the legacy systems are replaced.

This scenario demonstrates why it is a bad idea to use a user’s email address
(or other attributes which might change) as an account identifier throughout an
application’s data records. It is **better to use an internal account
identifier** throughout the application’s data records and treat the user’s
email address as a user profile attribute that is used for communication
purposes. This way, if the user’s email address or external identity needs to
change, it can be changed in the user profile without impacting the rest of the
application.

### Account Linking

This requirement can come about for several reasons, including

- An application has a legacy data store of identities but wants to offer users
  the convenience of logging in via a remote identity provider, most commonly a
  social identity provider.
- A user wants to try out a new application without granting the application
  access to their profile at a social identity provider. If they like the
  application, the user would later want to leverage their social identity
  provider account to log in to the application.

For example, a local application account with identifier `mary@gmail.com` is a
different account than an account at a remote identity provider that uses the
same identifier. If a user signs up for an application account using identifier
`mary@gmail.com` and then logs in with the identifier and credentials specified
at sign-up, she will access the local application account created as a result
of her sign-up. However, if Mary then signs in to the application via a social
`identity provider`, the application will receive a security token with various
claims about Mary. The claims might include an internal identifier specific to
that provider and a claim about her email address. However, Mary might have
used a different identifier or email address at the social provider. Unless the
application has a way to associate the social provider account attributes with
the user’s local account, the user won’t be able to access their existing
application account when they sign in via the `social provider`.

It is risky for an application to make an automatic association between
accounts based simply on matching attributes because a remote account may not
have validated user profile data. Therefore, it is best for any linking between
accounts to be made explicitly using a process such as the following, which
requires a user to authenticate to both accounts to prove ownership of each,
before the accounts are linked:

- The user logs in to a local `application` account, proving ownership of that
  account.
- The local application provides a list of remote `identity providers`
  supported for linking.
- The user selects the remote `identity provider` for a second account to be
  linked, such as a social provider.
- The application triggers an authentication request to the remote
  `identity provider` to authenticate the user.
- The user authenticates to the remote `identity provider`, proving ownership
  of their account at the provider.
- The `application` receives a security token from the remote
  `identity provider` with claims about the user.
- The `application` uses claims in the security token to associate an
  identifier for the remote account with the local account for the user. It may
  add a user identifier from the security token to the local account’s user
  profile as a secondary identifier.
- When a user authenticates, if the user selects local authentication, the
  application searches through the primary account identifier, and if the user
  logs in via a remote provider, the application searches through any
  secondary, linked identifiers in the user profiles to find the appropriate
  account for the user.

It’s important to note that automatic linking of accounts that have the same
value for a profile attribute such as email address, without the explicit dual
authentication step, should be avoided, to prevent the possibility of
unauthorized account takeover. If automatic account linking is done between
accounts with unvalidated attributes, such as an email address, accounts could
be erroneously linked that belong to different people.

### Progressive Profiling

Progressive profiling can be used to avoid having to collect a lot of
information from a user at once. A user can sign up for an `application` account
with minimal information, and progressive profiling can then add to that data
over time. The gathering of additional profile attributes can be done upon
subsequent uses of the application or when it is needed for a specific type of
transaction. A user can even sign in to an `application` using a remote
`identity provider`, and the `application` can create a local account for them
with information from the remote provider. A user can then be prompted to
supply additional profile attributes either before or after they are redirected
to that `identity provider`, with information from both sources merged into the
local application’s profile for the user.

### Impersonation

Impersonation is defined as the ability of one person to log in to an
`application` as if they were another person and perform any task as that
person. The most common use case is the need for support personnel to log in to
an `application` as another user and see what the user experiences in order to
troubleshoot an issue. Unfortunately, such a capability has the potential to be
abused, and it can be challenging to retrofit secure, restricted impersonation
capabilities into an existing application. Rather than building impersonation
capabilities directly into a primary application accessible by your entire user
population, you can reduce risk and liability by creating a separate
application with a subset of features needed by the impersonators and making it
only accessible to such users.

For example, to reduce the risk of unauthorized or accidental activity by
support staff impersonating real users, a separate troubleshooting application
can be created that is restricted to viewing only the data needed for
troubleshooting. It could provide view access to customer account configuration
and data, for troubleshooting, but not the ability to modify customer data or
initiate transactions. The troubleshooting application should log all activity
for audit purposes. In addition, automatic monitoring of logs for anomalous
activity should be implemented.

### Delegation

Another use case sometimes referred to as delegation is when one user needs to
grant another user the ability to act on their behalf, for a specific subset of
tasks or data. A busy executive, for example, may delegate some chores to an
executive assistant. The executive’s assistant would be granted access to
perform tasks on their behalf. A variant of this is when an employee goes on
vacation and needs to delegate ownership of their tasks (such as support
tickets) to another person while they are away. In both cases, one user needs
to be granted access to perform specific actions on behalf of another user.
Such capabilities are best designed into an application as the granting of
delegation privileges is quite application specific. For example, an executive
may wish to delegate to an assistant the ability to approve expense reports,
but only up to a certain amount. Application logging should be delegation-aware
so that all activity done by delegates is logged and shows both the delegating
and delegated identities involved, for a full audit trail. The task-specific
nature of delegation and need for audit logging makes it best implemented
within an application itself.

## Environment

### Shared Workstations

Such environments provide a shared device that is used by many users. Examples
can be found on manufacturing shop floors, medical offices, and point-of-sale
systems. With the same device used by multiple people, it is important to have
each user log in when they start a session and log off when they complete a
session.

In some environments, such as food service, it may be necessary to support a
very fast transition between users where users simply enter a four-digit PIN to
begin a session. Such PINs share the weaknesses of short passwords. Requiring
users to remember and enter long passwords may be infeasible, and issuing users
a badge with a stronger credential requires them to remember to bring the badge
to work each day, which may also be infeasible. In environments that experience
high employee turnover, issuing and decommissioning such badges could be
expensive. Biometric solutions may be too expensive for businesses with low
margins and involve the risk of a biometric factor being compromised or
spoofed.

Having users log in at the beginning of a session is easy enough, but ensuring
that a user logs out is more challenging because users may get distracted and
forget to log out before walking away. Implementing a session timeout after a
short period of inactivity can help protect users. Bank ATM machines provide a
good example, asking after every transaction if the user wants to do another,
and if there is no response within a short period of time, the session is
immediately terminated. For applications that run in a browser, it is helpful
to use a browser that supports ephemeral sessions and to set browser policy to
force ephemeral sessions so that information from previous users’ sessions is
cleaned up. If your application may be used on shared devices, it’s also
important to consider if information could be leaked through other means, such
as temporary files, and mitigate any risks found.

### Identity Provider Discovery

In other scenarios, such as a multitenant application used by many businesses,
each business may have its own `identity provider` configured, and the
`application` may need to determine the appropriate `identity provider` for a
user needing to log in. This has been called `identity provider discovery` or
home realm discovery. When there are multiple possible `identity providers`,
mechanisms to identify which to use for each user include

- The user selects the appropriate `identity provider` from a list.
- The user selects or enters information about their organization, and a lookup
  is performed to determine the correct `identity provider`.
- Derive the `identity provider` from an environment factor such as the
  originating application or domain.
- Obtain the `identity provider` from information in a browser cookie, if
  available, and revert to one of the previous methods if not.

### Multitenant Applications

> 多租户

Multitenant applications serve multiple tenants with a single running instance
of the application, where a tenant is a group of related users sharing access
to a group of resources managed by the application. Users are typically
authorized to access specific tenants. Scenarios where a user might need to
access multiple tenants include consultants working for multiple corporate
clients or administrative employees needing access to test and production
tenants of a corporate application.

If a given user is authorized to access multiple tenants, the appropriate
tenant can be determined by mechanisms such as

- Requiring users to have a different identity for each tenant
- Providing a tenant selection mechanism before or after login

The first option may not be very convenient for users. The second option is
often achieved by including the tenant name in the URL by which a user accesses
the application or by providing a tenant selection mechanism for the user.
Obviously, there needs to be an access check so that only authorized users can
select or access a tenant.

In addition to routing a user to a specific tenant, there may be a requirement
to enable different authentication policies across tenants. For a
business-facing application, it may be necessary to allow the administrators
for each tenant to configure different identity-related preferences, such as
password strength requirements, the `identity provider(s)` by which to
authenticate users, or the allowed length of single sign-on sessions. It may
also be necessary to support the ability of customers to retrieve log data but
only for their tenant. In short, a multitenant application has to satisfy all
the usual identity-related requirements, but may have to provide the ability
for each tenant to have their own identity-related configuration settings as
well as access to identity-related log data for their tenant.

## Summary

### Key Points

- Applications may need to accommodate family relationships, temporary
  accounts, users changing status, and users who may need to defederate their
  identity.
- Users in some scenarios may not have email accounts.
- Merging of identity repositories during company mergers may require changing
  usernames and supporting legacy applications’ need for old usernames.
- Account linking allows users to link multiple remote identities to one local
  account and authenticate with any of them to use that account.
- Progressive profiling enables an application to build up user profiles over
  time.
- Impersonation for support purposes has potential for abuse which can be
  mitigated with customized troubleshooting applications.
- If an application supports multiple identity providers, a discovery mechanism
  is needed to determine the correct identity provider to use for each user.
