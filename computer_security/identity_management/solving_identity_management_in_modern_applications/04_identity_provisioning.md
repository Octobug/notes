# Chapter 4: Identity Provisioning

> The more identities a man has, the more they express the person they conceal.
>
> —John le Carré, from Tinker, Tailor, Soldier, Spy (1974)

- [Chapter 4: Identity Provisioning](#chapter-4-identity-provisioning)
  - [Provisioning Options](#provisioning-options)
    - [Self-Registration](#self-registration)
      - [Progressive Profiling](#progressive-profiling)
      - [Invite-Only Registration](#invite-only-registration)
    - [Identity Migration](#identity-migration)
      - [Support Legacy Hashing Algorithm](#support-legacy-hashing-algorithm)
      - [Bulk Identity Migration](#bulk-identity-migration)
      - [Gradual Migration of Users](#gradual-migration-of-users)
    - [Administrative Account Creation](#administrative-account-creation)
      - [Manual Account Creation](#manual-account-creation)
      - [Automated Account Creation](#automated-account-creation)
      - [Cross-Domain Account Creation](#cross-domain-account-creation)
    - [Leverage Existing Identity Service](#leverage-existing-identity-service)
  - [Selecting an External Identity Service](#selecting-an-external-identity-service)
    - [Self-Registered Identities](#self-registered-identities)
    - [Organization Identities](#organization-identities)
    - [Governments Identities](#governments-identities)
    - [Industry Consortium Identities](#industry-consortium-identities)
  - [Identity Provider Selection](#identity-provider-selection)
  - [Identity Proofing](#identity-proofing)
  - [Choosing and Validating Identity Attributes](#choosing-and-validating-identity-attributes)
    - [Attribute Usage](#attribute-usage)
    - [Validating Critical Attributes](#validating-critical-attributes)
  - [Consent Management](#consent-management)

Provisioning is the act of establishing identities and accounts for your
application. An identity includes at least one identifier and various
additional user profile attributes. An online account is associated with an
identity and can be used to access protected online resources.

The objective of the provisioning phase is the creation or selection of a
repository of user accounts and identity information that will be used in the
authentication and authorization of users as they access protected resources.

## Provisioning Options

A list of approaches to consider includes

- A user creates a new identity by filling out a self-registration form.
- A special case of self-registration is sending select users an invitation to
  sign up.
- User identities are transferred from a previously existing user repository.
- An identity service with an existing repository of user identities is
  leveraged.
- An administrator or automated process creates identities.

### Self-Registration

The sign-up form and process must be capable of scaling to the expected volume
of user sign-ups especially for a big, widely announced launch.

Self-registration also necessitates privacy notices about the information you
are collecting and obtaining the user’s consent for the planned use of the
information collected.

- Advantages
  - Ability to collect user attributes that don’t exist elsewhere.
  - Control over user registration experience.
  - Scalability through self-service.
- Disadvantages
  - May deter some prospective new users from signing up.
  - Liability associated with storing login credentials.

#### Progressive Profiling

With progressive profiling, a user is asked to provide minimal attributes when
they sign up. If the user later performs a transaction that requires more
information, it is collected at that time.

#### Invite-Only Registration

The registration page can lock the email address or phone number to that used in
the invitation so it cannot be changed at the time of registration. This
prevents an uninvited person from stealing someone else’s invitation and signing
up as themselves.

The link in the invitation can also have an expiration associated with it and
each invitation is usually tracked so it can only be used once.

An invite-only flow can also be used for situations where you need to create an
account in order to assign privileges to it before sending the invitation. An
administrator or automated process can create the account, assign it privileges,
and then trigger the sending of the invitation link to the new user.

The invite-only flow can additionally protect against registrations by hackers
and bots, unless, of course, they find a way to finagle an invitation.

- Advantages
  - Ability to collect user attributes not available from other sources.
  - Control over user registration experience.
  - Some protection against registration by hackers and bots.
  - Scalability through self-service if users invite others.
- Disadvantages
  - The work to implement the invitation mechanism and control access to it.
  - The work to issue invitations.
  - May deter some prospective new users from signing up.
  - Liability associated with storing login credentials.

### Identity Migration

While most user profile attributes can be extracted and moved, passwords
represent a challenge. Passwords are typically stored in a hashed format.

If two different systems use different hashing algorithms or different inputs
to the same algorithm, it is not possible to move a hashed password from one
system to the other and have it be usable by the new system. In such
circumstances, there are a few solutions to consider for migrating identities
to a new system.

#### Support Legacy Hashing Algorithm

One solution is to move the hashed passwords to the new system and update the
new system to support the hashing algorithm(s) used by the legacy system. This
will enable moving all identity data and hashed passwords from the legacy
system to the new system without requiring the users to reset a password.

- Advantages
  - Avoids need for password reset.
  - Transfers all accounts in a usable state.
- Disadvantages
  - Work to implement legacy hashing algorithm(s).
  - Liability associated with storing login credentials.
  - Inherits any weakness associated with legacy hashing algorithms.

#### Bulk Identity Migration

If it is not possible for the new system to support the legacy hashed
passwords, it may be possible to extract the users’ identity data, minus the
hashed passwords, from the legacy system and import it into the new system.

The new system would then need to send each user a unique password reset link to
establish a new password for their account in the new system.

This solution may also be useful if the passwords in the legacy system were not
stored in a hashed form and the new system requires newly reset, hashed
passwords for improved security. Users should be notified in advance about the
migration, so they will know to expect the password reset message and not view
it as an attempted phishing attack.

- Advantages
  - Transfers all users at once.
  - Enables immediate shutdown of legacy user repository.
  - No latency added at login time to check a legacy system for a user account.
  - Code to transfer identities can be independent of application code.
- Disadvantages
  - Transfers all accounts, even inactive accounts, unless they are filtered
    out during the transfer.
  - Requires all users to set new password via account recovery, unless the new
    system can support the legacy hashed passwords.
  - Migrating all users at once may cause an outage or delay the migration if
    things go wrong with the migration and there is no backout plan.
  - If multiple applications use the legacy repository, they must migrate at
    the same time if the legacy repository is to be shut off after migration.
  - Liability associated with storing login credentials.

#### Gradual Migration of Users

This requires a login mechanism that prompts users for credentials, validates
the credentials against the legacy repository, and, if validated, retrieves
identity information from the legacy repository and stores it along with the
entered credentials in the new repository.

A subset of users may not log in and therefore not have their identity
information migrated. You can set a cutoff date for the migration and decide
what to do about any identities that have not been migrated by that date.

- One possibility is to declare the unmigrated accounts inactive and abandon
  them.
- A common approach is to use the bulk move option on the inactive accounts so
  you can decommission the old system.
- You may want to migrate only a subset of identities. You should consider
  reserving the account identifiers of unmigrated identities to prevent them
  from being used by new accounts in the future.

Care should be taken to minimize exposure of login credentials, ideally by using
an identity provider service that implements such a migration. In this case, the
credentials are only exposed to the identity provider service that will handle
authentication with those credentials going forward.

A final consideration with the gradual migration option is that it may be
confusing for users if other applications are using the legacy identity store
and the user resets their password in the new application. If the new password
is not synchronized back to the legacy identity store, the user may have one
password for the applications continuing to use the legacy identity store and a
different password for the new application. Alternatively, clear differentiation
of the legacy and new login screens could reduce confusion to some extent.

- Advantages
  - Inactive accounts can be weeded out.
  - No password reset required
  - Spreads out risk of outages by migrating identities gradually
  - Can support continued use of previous sign-up mechanisms or applications
    that use the legacy identity repository during the gradual migration.
- Disadvantages
  - Requires that legacy identity store is accessible from new application’s
    authentication mechanism.
  - Legacy identity store must remain accessible until enough identities are
    transferred.
  - Transfer mechanism must be maintained throughout the gradual migration.
  - A user’s first login after migration starts may have some latency as
    identity data is transferred from the legacy system.
  - Potential for user confusion after password reset if other applications
    continue to use the legacy data store.
  - Potential for user confusion if users can make user profile updates in both
    legacy and new systems after migration.
  - Implementation work cannot be easily decoupled from the application team.
  - Liability associated with storing login credentials.

Any time identity data is moved from one system to another, it is important to
consider any changes that might occur during the transition.

- The easiest approach is to prohibit users from making changes to either the
  old or new system during the transition.
- If users are allowed to make changes to their identity information in the old
  system during an identity data migration, a plan is needed for how to
  identify and transfer such interim changes from the old system to the new
  system.
- In the case of a gradual identity migration, the user’s account in the old
  system can be disabled when the user’s account is migrated, preventing
  further changes in the old system. This assumes there are no other
  applications which will continue to use the old system.

### Administrative Account Creation

Yet another solution to consider for creating accounts and identities is to
have an administrator or automated process create them. The best approach for a
situation should take into account

- The size of an organization
- The frequency with which new users need to be added
- Whether provisioning needs to be done across domains

#### Manual Account Creation

For very small organizations, the work to implement account provisioning
automation may not be justified. In the absence of automation, written
procedures and checklists can be used to ensure necessary account provisioning
steps are consistently followed.

#### Automated Account Creation

This approach is often used for employee identities. When a new employee joins
a company, the company can automatically create an account for the employee
using identity information from a Human Resources (HR) system.

#### Cross-Domain Account Creation

Account provisioning may need to occur across domains. This can occur when

- Maintaining employee accounts in external SaaS (Software-as-a- Service)
  applications
- Maintaining partner accounts in corporate identity repositories or
  applications
- ...

Ideally, modern authentication protocols would convey user profile attributes
to applications in authentication tokens at the time of login, but provisioning
or synchronizing identity information across domains may still be needed if

- Applications are not designed to extract identity information from
  authentication tokens.
- The identity profile information is too large to convey in authentication
  tokens.
- User logins are not frequent enough to keep profile information sufficiently
  up to date.

When needed, the provisioning of accounts and identity information across
domains is still commonly done using proprietary solutions, but an industry
standard protocol, [SCIM 2.0 (System for Cross-domain Identity Management)](https://tools.ietf.org/html/rfc7644),
was defined in 2015 to provide a more standard approach to sending and updating
identity information from one domain to another.

SCIM 2.0 provides a standard REST API for one system to send requests to
another system for adding, modifying, or deleting user and group records. This
can be used to keep identity data synchronized between different systems. A
common use case is for a centralized identity repository to send user account
and profile updates, as well as account deactivation requests, to other service
provider systems.

- Advantages
  - User doesn’t fill out registration form.
  - Administrator can assign customized privileges for the account.
  - Can incorporate manual identity validation step if required by the
    organization creating account.
  - Can be automated via workflow or identity provisioning software.
- Disadvantages
  - Time-consuming if not automated.
  - Requires care to ensure that only the user knows the password for the
    account created.
  - Liability associated with storing login credentials if stored locally.

### Leverage Existing Identity Service

This allows users to employ an account they already have such as at a social
provider like Facebook or Google, a corporate identity provider service
operated by their employer, or a government identity service.

With this option, your application delegates responsibility for authenticating
users to an identity provider and receives back a security token with
information about the user’s authenticated session and, optionally, attributes
about the user.

- Advantages
  - Better user experience if it reduces the data required to sign up.
  - Easier for user to remember password if identity provider account is used
    frequently.
  - You may not have to implement a login form or account recovery mechanism if
    all users authenticate via the identity provider service.
  - Less risk if you do not store user passwords.
- Disadvantages
  - You may have to collect additional profile information not available from
    the identity provider service.
  - You need to evaluate the service and availability levels of the external
    identity service to ensure it meets your needs.
  - May require additional development or configuration work for each identity
    provider service to be used.
  - May require configuration work at each identity provider service for each
    application you have, unless you use an authentication broker service.
  - May require collaborative troubleshooting with another organization when
    issues occur.

## Selecting an External Identity Service

The strength of an identity is one factor in determining how much trust can be
placed in the identity, and several factors influence the strength of an
identity:

- The validation of the information used to establish the identity
- The identity’s implementation that prevents it from being forged or used by
  others
- Recognition of certain issuers of identities as authoritative for a
  particular domain

- Strong Identities
  - Linked to a real person, who can be held accountable for actions taken with
    the identity and associated accounts.
  - Identity attributes are validated during account issuance process.
  - Issued by entity recognized as authoritative for a particular context.
  - Contains mechanisms to protect against forgery or unauthorized use.
- Weak Identities
  - Anonymous, cannot be linked to a real person.
  - Little validation of identity attributes.
  - Issued by an entity with little recognized authority.
  - Few protections against forgery or unauthorized use.

### Self-Registered Identities

A self-registered identity, such as a basic Gmail or Yahoo email account, is an
example of a weak identity.

Self-registered accounts are typically not considered authoritative for
identity information due to the lack of validation.

Allowing users to authenticate via such providers gives users convenience and
the ability to reuse a common profile.

### Organization Identities

Many organizations, such as companies or universities, will issue an online
identity for their members. These identities meet some of the criteria for a
strong identity.

However, a user typically cannot log in via their corporate identity service
and access services outside the organization and its contracted SaaS services.

### Governments Identities

A government-issued online identity is an example of a stronger identity.

Government-issued identities provide more strongly validated identities, but
may be limited to users from one country and may be limited to use at the
issuing government’s services. Wider use would need international standards
similar to those for passports as well as a model for funding the incremental
service operation costs.

### Industry Consortium Identities

The Belgian Mobile ID project is a consortium of financial institutions and
mobile network operators to provide a strongly validated identity for anyone
with a Belgian-issued eID and a mobile phone.

The service includes a mobile application, “itsme,” which is used to
authenticate without the need for passwords.

## Identity Provider Selection

For employee-facing applications, it’s best to use an identity service where
the employing organization owns the accounts. An organization-controlled
identity service provides a single place at which the organization can provision
accounts as well as shut off accounts if an employee or member leaves the
organization.

It also gives a single point at which to enforce credential strength/policy and
deploy multi-factor authentication as well as log authentication activity.

There are several cloud vendors that offer an identity service on a subscription
basis. Cloud services such as Google Apps, Azure AD, Auth0, Amazon Cognito, and
Okta offer cloud-based identity services.

| Scenario                  | Common Type(s) of Identity Provider            |
| ------------------------- | ---------------------------------------------- |
| B2C: Business to consumer | Social Identity Providers2                     |
|                           | Azure AD, Auth0, ...                           |
|                           | Application-specific repository                |
| B2E: Business to employee | Google Apps, Azure AD, Auth0, ...              |
|                           | Any OIDC or SAML 2–compliant identity provider |
| B2B: Business to business | Google Apps, Azure AD, Auth0, ...              |
|                           | Business customer's OIDC or SAML 2 provider    |

## Identity Proofing

- Know Your Customer (KYC)
- Anti-Money Laundering (AML)

Many businesses may need to validate the identity of online users, and this
process is known as ***identity proofing***.

## Choosing and Validating Identity Attributes

Email:

- Advantages
  - Globally unique.
  - No need to hunt for a name that isn’t taken already.
  - May be easier to remember than a username.
  - Can double as a communication attribute, such as for password resets.
- Disadvantages
  - May need to be changed by a user.
  - May be reassigned by an email provider to a new user.
  - May be reassigned by a corporate provider to a new user.
  - Terminated by the employer if a user leaves.
  - Not all companies issue email addresses.
  - Children may not have email addresses.
  - Family members may share an email address.
  - May expose personal information (user’s name).
  - Exposure as display name may result in spam email.

Username:

- Advantages
  - Easier to set up multiple accounts at a site.
  - May be shorter to type on mobile devices.
  - Can be used in searches, allowing other attributes with personal data to be
    encrypted.
- Disadvantages
  - Only unique within an application domain.
  - Merging user repositories problematic after acquisitions.
  - May be harder for a user to remember which username was used at each site.
  - A user may want to change a username over time.
  - May expose personal information if used for display and it contains
    personal information.

Phone number:

- Advantages
  - Globally unique (with country code).
  - No need to hunt for a free identifier. Can double as a communication
    attribute, such as for password resets.
  - May be easier for a user to remember than a username.
- Disadvantages
  - Exposure as display name may cause spam calls.
  - Might be reassigned to a new user over time.
  - May involve a charge to obtain a phone number.
  - More difficult for a person to set up multiple accounts at the same site.
  - May be changed by a user for various reasons.
  - May be terminated by a phone provider.

### Attribute Usage

The following suggestions can avoid some of the disadvantages:

- Avoid exposing identifiers that may contain personal data.
  - Use an internal account identifier in log files to avoid directly exposing
    personal data in logs.
  - Use an internal account identifier in application records.
  - Allow users to specify a display name for use on screens/ printouts to
    protect privacy.
- Identifiers/attributes for logging in, display, and notification should be
  distinct and easily changeable by the user.
- Allow setting multiple attributes for notification purposes, such as a
  primary and secondary email, in case one becomes inoperable.
- Allowing usernames that are long, contain special characters, and that can be
  changed by users enables flexibility. A separate profile attribute besides
  the username should be used for display purposes and another for notification/
  contact information to decouple these different usages.

If your application will leverage an identity provider, and users will access
multiple applications through that identity provider, the use of
***Pairwise Pseudonymous Identifiers (PPIDs)*** reduces the ability for someone
to correlate the user’s activity across different applications.

For each user, a unique identifier is used between the identity provider and
each application. A given user might be identified with `a8h3` for one
application site and `c37j` for another. In practice, the identifiers would be
long, opaque, unguessable strings. Support for PPIDs may vary by identity
provider.

### Validating Critical Attributes

It is important to validate email addresses and other profile attributes if
used in activities that impact security and privacy. This includes attributes
used for

- Authorization decisions
- Account recovery
- Delivery of sensitive information to the user

If you import identities from elsewhere, you should ensure email addresses or
other critical attributes used for the listed functions have been validated
before accepting them so that you can rely on the profile attributes.

Security and privacy-related issues can arise with unvalidated attributes.
Validating email addresses also prevents accidental entry of an incorrect
address.

It is critical to decouple attributes for different purposes and validate any
email addresses or other profile attributes that are used in authorization
decisions, account recovery mechanisms, or to deliver sensitive information to
users.

## Consent Management

Privacy legislation varies by jurisdiction but typically requires that a site
provide privacy-related notification to users and have a legal basis for
collecting and using data about individuals. Such legal bases include

- obtaining user consent
- fulfilling a contract
- satisfying a legal obligation
- performing a task that is vital to a data subject

 in the public interest, or for a legitimate business purpose.

Consent management includes displaying privacy notice(s) that describes data
collection and processing practices, including the use of cookies and tracking
technologies.

You will need to keep a record of consent obtained from users. Consent records
should include information such as

- Who gave consent, in the form of an identifier, such as email address or
  other account identifier, or in more anonymous cases, a cookie or device ID
- When the consent was given, in the form of a timestamp
- The site for which consent was given
- The purposes of processing for which the user has consented
- The version of privacy/consent notice used at the time of consent
- Any subsequent changes or withdrawal of consent

It should be possible for users to view and update their consent choices over
time. User consent data may need to be accessible by applications to trigger
the execution of code which gathers data on user behavior, for feedback and
learning about users.

To support these requirements, user consent data should be centralized and
accessible by different business functions and systems.

A site may collect different types of data about users, including what is known
as zero-party data, first-party data, and third-party data.

- Zero-party data is a term coined by Forrester Research and refers to data
  that users provide themselves.
- First-party data is data collected by an application about a user. It can
  include observations of user behavior on a site and transactions the user
  submits.
- Third-party data is that collected or purchased from third parties, to
  augment data collected by an application.
