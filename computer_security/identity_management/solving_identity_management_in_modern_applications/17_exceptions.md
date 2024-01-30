# Chapter 17: Exceptions

> An ounce of prevention is worth a pound of cure.
>
> —Benjamin Franklin, American founding father, inventor, politician, diplomat,
> scientist, and printer, from a letter to The Pennsylvania Gazette (1735)
>
> 预防胜于治疗。治病不如防病。

- [Chapter 17: Exceptions](#chapter-17-exceptions)
  - [Accounts](#accounts)
    - [Data Restore](#data-restore)
    - [Account Decommission](#account-decommission)
    - [Orphaned Account](#orphaned-account)
    - [Account Takeover](#account-takeover)
    - [Phone Lost, Damaged, or Stolen](#phone-lost-damaged-or-stolen)
  - [Identity Providers](#identity-providers)
    - [Account Recovery Requests](#account-recovery-requests)
    - [Brute Force Attacks](#brute-force-attacks)
    - [Breached Passwords](#breached-passwords)
  - [System Outages](#system-outages)
    - [Authentication System Outage](#authentication-system-outage)
    - [Admin Access](#admin-access)
    - [Provisioning Systems](#provisioning-systems)
  - [Cybersecurity Threats](#cybersecurity-threats)
    - [Compromised Personal Data](#compromised-personal-data)
    - [Compromised Credentials](#compromised-credentials)
    - [Compromised Secrets](#compromised-secrets)
  - [Summary](#summary)
    - [Key Points](#key-points)

## Accounts

### Data Restore

A customer may inadvertently delete their account data and then regret it. The
likelihood of this occurring can be reduced by requiring confirmation before
deleting data and implementing a soft delete. If you support requests to
restore deleted accounts, you should develop policies and secure practices for
such requests so they don’t provide an opportunity for a social engineering
exploit. Procedures should include

- evaluating the requestor
- the timing of the request
- the nature of the request

Requests made weeks or months after the data was deleted or to restore data
into different accounts with different owners probably need higher scrutiny
than a request made only minutes after data was deleted.

### Account Decommission

For consumer-facing accounts, a self-service account decommission feature may
be sufficient. Such a feature may be needed as part of supporting privacy
requirements as well. For corporate accounts with multiple administrators, it
may be useful to require a request by two authorized administrators or
implement a delay coupled with confirmation notices to all administrators in
order to prevent an unauthorized, malicious delete action by one disgruntled
employee.

It's also needed to reserve the account identifier for accounts which have been
decommissioned. It should not be possible for someone to create a new account
with the same `identifier` as a previously deleted account and then request the
restoration of data from a time when the original account existed. The use of
an email address as account identifier does not mitigate the risk because
[email addresses have been recycled by some providers in the past](https://thenextweb.com/news/microsoft-can-recycle-your-outlook-com-email-address-if-your-account-becomes-inactive).
Reserving the account identifier for a decommissioned account for a period
longer than the data retention period for backups of deleted account data
mitigates this risk at least for the local system.

### Orphaned Account

Be sure to obtain requests in writing, validate the authenticity and
authorization of requestors through independent channels, and keep records of
all requests, validation steps, and actions.

### Account Takeover

If a user calls your helpdesk and claims their account has been taken over by
someone else, you will need a process for determining the legitimate owner of
the account, bearing in mind that an unauthorized user could have viewed
account details and changed user profile information as well as passwords after
taking over the account. In this case, the legitimate owner may look like an
imposter because they won’t know the current password or profile information.
Maintaining a history of past profile information such as addresses or phone
numbers, especially if not displayed in the application user interface, may
help in validating a locked-out, legitimate account owner, though further
validation will probably be required. Encouraging the use of multi-factor
authentication can reduce the chances of account takeover happening.

### Phone Lost, Damaged, or Stolen

If a user’s phone is stolen and open at the time of the theft, the user’s
account may be accessible by the thief. For this case, you’ll need a process to
help the legitimate owner of an account terminate the phone’s access to their
account.

## Identity Providers

### Account Recovery Requests

- One option is sending a “magic link” to a previously registered email address
  for the account.
  - The use of a magic link can be combined with a confirmation email
    indicating a credential was reset, with instructions for what to do if this
    action was not taken by the legitimate account owner.
- Sending one-time codes via Short Message Service (SMS) text messages to a
  user’s previously registered phone number has been a common solution.
  - There have been [some successful attacks based on SIM swapping](https://www.pcmag.com/news/fcc-to-create-rules-to-stop-sim-swapping-attacks),
    [rerouting phone numbers to unauthorized phones](www.vice.com/en/article/y3g8wb/hacker-got-my-texts-16-dollars-sakari-netnumber),
    and [intercepting SMS messages](https://usa.kaspersky.com/blog/ss7-hacked/17099/)
    - <www.theguardian.com/technology/2016/apr/19/ss7-hack-explained-mobile-phone-vulnerability-snooping-texts-calls>
- Other approaches use a mobile app or a specialized device to generate a
  one-time code.

An `identity provider`’s account recovery mechanism can open up other risks,
depending on how it is implemented.

- A password reset link which immediately invalidates the current account
  password could enable a person to lock someone else out of their account.
  If the legitimate owner of the account has not kept their email address up to
  date, they will not receive the password reset link and be locked out of
  their account.
- A password reset link could even be used by pranksters to trigger an account
  recovery SMS message or phone call in the middle of the night to wake someone
  up.
- If a user’s email account has been compromised, a hacker could use a password
  reset feature to trigger password reset emails and gain control of the user’s
  accounts that use that email address.
  
Approaches to mitigating these risks include requiring some information from
the user before triggering an account recovery action, reminding users to keep
their notification information current and not invalidating a current
credential until a reset link has been activated.

### Brute Force Attacks

An identity provider can reduce the chances of brute force attacks succeeding
by detecting a series of many successive failed login attempts or failed
password reset attempts against one account from the same IP address. If either
of these situations occurs, an `identity provider` can slow down an attacker by
techniques such as blocking an account for a short time period or asking for
multi-factor authentication (if configured). An alert can be sent to the site
administrator and an email sent to the owner of the account to alert them about
the attack. The email can indicate why the account was blocked and provide a
link for unblocking the account immediately in case the failed logins were
caused by the legitimate account owner.

If an identity provider detects a series of failed logins or failed password
reset attempts hitting multiple accounts from a single IP address, this is more
suspicious, and it may be appropriate to simply block that IP address
immediately. However, corporate customers with many users whose traffic comes
from the same IP address due to network address translation (NAT) are an
exception. Allowlisting IP addresses for environments using NAT helps avoid
false alarms for brute force attacks in this case.

One additional caution involves environments with an automated system that will
access a user’s account using their credentials. If the user changes their
password, but the update is not provided to the automated system, it could
trigger the brute force attack response.

### Breached Passwords

Breached passwords are being aggregated into massive databases that can be
exploited by hackers, including one discovered by
[breached identity curator 4iQ containing 1.4 billion breached, cleartext passwords](https://medium.com/4iqdelvedeep/1-4-billion-clear-text-credentials-discovered-in-a-single-database-3131d0a1ae14).
Fortunately, there are databases on the Internet containing information on
breached passwords, such as [have i been pwned](https://haveibeenpwned.com)
created by Troy Hunt. An application or an `identity provider` can check a
user’s password against such databases when they sign up for an account or
reset their password. An application or identity provider can perform such
checks when a password is initially set, at password reset, and periodically
when users log in to detect if a password has been compromised after being set.

## System Outages

### Authentication System Outage

It may be desirable to use the same authentication service for your primary
website and a support site, so users have single sign-on (SSO) across the
sites. However, if the authentication service is unavailable, users will be
locked out of both sites. If you have this scenario, you should plan for how to
handle support in the event of an outage to your authentication system.

- One approach is to rely on proactive outbound communication during an outage.
- Some mechanisms to consider include a support phone number with a recorded
  message to acknowledge the issue and provide updated information or a public
  community support forum or status page where outage updates can be posted.
- In designing processes for business continuity during an outage of an
  authentication system, you’ll want to ensure that alternate processes do not
  rely on the primary authentication system.

### Admin Access

If single sign-on is used as a primary access mechanism for administrative
access, such access could be blocked during a failure of the SSO system. You
may need alternate authentication mechanisms to access critical administrative
functions during an outage. This includes

- administrative access to your service
- monitoring and alerting infrastructure
- the ability to post outage updates to your customers

### Provisioning Systems

Provisioning processes and systems may be less critical during an outage than
authentication systems, but if you have time-critical account provisioning or
deprovisioning processes, it may be necessary to define alternate processes for
use during an outage of a provisioning system. Once service is restored, it may
be necessary to validate that all in-flight transactions at the time of the
outage were completed, especially account removal or privilege removal
transactions. A routine check after an outage for incomplete deprovisioning
transactions can help prevent incorrect access privileges.

## Cybersecurity Threats

Your application could experience any of a wide variety of cybersecurity
threats

- denial-of-service (DoS)
- ransomware attacks
- data breach
- suddenly being notified of a vulnerability in a code library leveraged by
  your application’s code

An incident response plan should minimally include

- The owner accountable for leading the response
- The response team and responsibilities of each member
- Clear priorities and required timeframes for the response effort
- The steps to take, including preventing further damage, preserving required
  evidence, assessing the damage, documenting all findings and decisions, and
  identifying and fixing the root cause as well as related damage
- Reporting and notification requirements
- Follow-up actions to prevent the incident from happening again

In addition, there may be aggressive timeframes within which you must notify
regulators, law enforcement, or users if a breach occurs, so it is imperative
to have a thorough response plan defined in advance that includes such
responsibilities.

### Compromised Personal Data

In addition to a general incident response plan, your plan for responding to a
breach of personal data should additionally define

- When and how to engage law enforcement, if appropriate
- When and how to engage insurers
- The process to follow for user and regulatory notification
- The process to follow for public relations communications

If personal data is compromised, many privacy regulations require notification
to regulatory agencies within a certain time period. For organizations subject
to the General Data Protection Regulation (GDPR), Article 33 specifies that
notification should be made within 72 hours of becoming aware of a breach.
Notification may be required to multiple government organizations, law
enforcement, and users.

### Compromised Credentials

Relying on users calling a support center is costly and difficult to scale and
requires a secret the legitimate user and the support staff know that the thief
won’t know. Sending a password reset link to the user’s registered email
address or phone number may not work if significant time has passed between the
breach and its discovery because the thief may have altered authentication
credentials and user profile information, including notification attributes
such as a user’s email address and phone number. You need a secure and scalable
account recovery process worked out in advance so that you can act in a timely
manner if this happens.

### Compromised Secrets

A related scenario is the compromise of other “secrets” such as OAuth 2.0
client secrets or private keys used in the signing or decryption of security
tokens. This can happen as a result of human error, so it is wise to prepare
for this possibility. An inventory should be maintained of all such secrets
used in your operations, how each is used, and recovery steps needed if any are
compromised.

Your application can facilitate recovery by dynamically retrieving the public
keys used to validate security tokens. This makes it easier to rotate them but
may create issues for caching. If your application caches dynamically retrieved
public keys for performance reasons, and invalidates the cache anytime a
signature validation fails, this could enable a denial-of-service (DoS) attack
by someone sending counterfeit security tokens with fake signatures. If caching
is needed, it may be possible to reduce this risk using a periodic refresh and
by having applications only invalidate their cache upon a validation failure
once per a certain time period, rather than for each failure, and triggering an
alert for human intervention if a lot of invalid tokens are received.

If your solution includes the use of SAML 2 with other organizations and a
private key used to sign or decrypt SAML 2 messages is compromised, you need to
update configurations with new keys. If there is no dynamic mechanism to update
federation metadata, you may need to synchronize updates with another
organization. You should work out recovery processes in advance for the secrets
in your environment so you can execute quickly if needed.

## Summary

### Key Points

- It’s essential to plan for what can go wrong in an environment.
- You may need a process for restoring accidentally deleted data.
- You need a process for customers who wish to decommission their account.
- You should have a process to handle an orphaned account.
- Users may forget or lose credentials and need an account recovery mechanism.
- You need a process to check for and fix accounts whose password has been
  compromised.
- You need a process to identify the legitimate account owner if account
  takeover has occurred.
- If your support system or administrative access depends on a single sign-on
  system, you should plan for how to handle an outage to the single sign-on
  system.
- You should have an incident response plan in place for responding to
  cybersecurity threats, including compromised personal data, user credentials,
  or private keys.
- In planning how to handle exceptional events, be sure to consider logging
  data that could facilitate your response or records to keep of your response
  actions to demonstrate proper handling of an event.
