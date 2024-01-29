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

>>>>> progress
