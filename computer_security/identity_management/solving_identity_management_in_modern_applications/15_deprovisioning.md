# Chapter 15: Deprovisioning

> The boundaries which divide Life from Death are at best shadowy and vague.
> Who shall say where the one ends, and where the other begins?
>
> —Edgar Allan Poe, American author, from The Premature Burial (1844)

- [Chapter 15: Deprovisioning](#chapter-15-deprovisioning)
  - [Account Termination](#account-termination)
  - [Best Practices](#best-practices)
    - [Just Do It](#just-do-it)
    - [Provide a Soft Delete Technique](#provide-a-soft-delete-technique)
    - [Reserve Deprovisioned Identities](#reserve-deprovisioned-identities)
    - [Preserve Account Record](#preserve-account-record)
    - [Data Transfer](#data-transfer)
    - [Privacy Right to Erasure](#privacy-right-to-erasure)
    - [Certificate of Deletion](#certificate-of-deletion)
    - [Secure Delete](#secure-delete)
    - [Consider Reprovisioning Requirements](#consider-reprovisioning-requirements)
  - [Summary](#summary)
    - [Key Points](#key-points)

The final event in the life of an identity is deprovisioning, when an account
and associated identity attributes are deleted or disabled so they can no
longer be used. When an account is terminated, there are several design points
to consider related to

- how to delete or disable accounts
- what identity information to keep
- and for how long.

## Account Termination

Regardless of the reason, upon termination, it is necessary to render the
account so it can no longer be used to access resources. Simply deleting an
account may not be an appropriate solution for this.

## Best Practices

Processes for the deprovisioning of accounts and identity information should be
designed with several best practices in mind. These range from

- ensuring it gets done in a timely fashion
- protecting against accidental account deletion
- enabling customers to transfer data elsewhere to satisfying privacy rights
- requests for secure deletion
- ...

### Just Do It

The best practice for deprovisioning is to make sure it gets done in a timely
fashion. If an account is no longer needed, it should be immediately disabled
so it cannot be hijacked by an unauthorized user. Unfortunately, deprovisioning
is notoriously overlooked in settings that lack mature identity management. To
minimize the possibility of abandoned or unused accounts, you should implement
automation to trigger periodic account review and to deprovision accounts that
are unused or no longer appropriate.

Automation can detect accounts that have not been used for a long time and
privileges that are not aligned with a user’s profile. Even the best automation
fails at some point, however, so a periodic manual audit of existing accounts
is essential to find accounts and privileges that are no longer appropriate so
they can be deprovisioned.

In consumer-facing environments, it may be appropriate to consider
deprovisioning accounts which have had no activity for many years.

### Provide a Soft Delete Technique

You can make it harder to erroneously delete an account by implementing a soft
delete. This can take the form of a confirmation screen and marking an account
as deleted while providing a grace period before the account is truly deleted.
During the grace period, an “undelete account” capability should be available.
You can also send a confirmation email at the beginning of the grace period
explaining that the account is marked for removal and will be permanently
deleted at the end of the grace period. The email can include instructions for
how to reverse the account deletion if it was done in error. While not
foolproof, these ideas may prevent some accidental account removals and the
work to restore mistakenly deleted accounts.

If you implement a soft delete that delays the actual account deletion, privacy
compliance may require that you include in your site’s privacy notice and/or
Terms and Conditions an explanation that deleted accounts will not be deleted
immediately and why.

### Reserve Deprovisioned Identities

When deprovisioning accounts, it is best to preserve a list of deleted account
identifiers and prevent each `identifier` from being reused by a new owner in
the future.

- If this is not done, a new person could create an account with a previously
  used identifier and might be able to request a restore of historical data
  associated with that `identifier` to get data that belonged to the previous
  owner of the account.
- If a deleted account `identifier` was used in a single sign-on scenario and
  was used to access multiple applications, the owner of a new account with the
  same `identifier` might be able to access the previous person’s data in those
  applications. This is especially important if an email address is used as the
  sole `identifier` for an account.

By reserving previously used identifiers and checking all new identifiers for
uniqueness against both active and deprovisioned accounts, several issues can
be avoided.

### Preserve Account Record

You never know when unauthorized activity might be detected. It could be weeks
or even months after the fact. Because a fraud investigation may arise at any
time, even after an account has been closed, you need to consider whether
information about deleted accounts should be kept for some period of time,
including transactions, the time they were submitted, the accounts that
performed them, identity data linked to the accounts, and any other information
needed for forensic evidence. When an account is deleted, it may be appropriate
to preserve some account identity information along with the date, time, and
reason why an account was disabled or terminated. If an account is terminated
due to abuse, keeping sufficient records may help identify if a user attempts
to open another account, at least with the same identity data.

One caveat is that privacy regulations require that data be kept only as long
as needed for legitimate business purposes, and users have the right to request
that personal data about them be erased. These rights may conflict with the
need to have backups and audit logs. In practice, approaches are being worked
out to satisfy the intent of privacy rights as well as operational system
needs. Such approaches include

- minimizing data that is retained
- encrypting and restricting access to retained data
- following defined data retention policies and procedures
  - Such policies and procedures should be created with guidance from legal and
    privacy advisors to ensure alignment with best current practices.

### Data Transfer

For consumer users, the most scalable option is to provide a self-service means
to download customer-owned data. You should consider the data formats that will
be most useful to customers. For sensitive data, you should have a procedure to
validate the requestor before providing a data dump. Requiring step-up
authentication or at least reauthentication to obtain the data is one good
precaution. This protects a user’s data if they have walked away from their
keyboard without locking their screen.

For corporate or business customers, there are a few more points to consider. It
may make sense to require the involvement of two people from the customer in the
request process to prevent a lone actor from downloading sensitive corporate
data for unauthorized purposes. Once suitable customer validation is obtained
for the download request, it should be provided in the most direct,
self-service manner to minimize the `service provider`’s access to the
customer’s data. For example, if a data dump were done manually by the
`service provider`, it might be downloaded to a person’s laptop or transferred
to the customer by a channel that introduces risk.

For corporate customer data that involves user identities and passwords, the
passwords should have been stored in a hashed format and may not be usable
elsewhere if different hashing functions are used.

### Privacy Right to Erasure

When a user deletes their account, it may not be enough to simply delete data
your own service holds about a user.
[Article 17 of the General Data Protection Regulation (GDPR)](https://gdpr.eu/article-17-right-to-be-forgotten/)
provides consumers the right to erasure, commonly referred to as the right to
be forgotten, which enables a user to request that an organization delete the
data it has about the user. Under
[Article 19 of the GDPR](https://gdpr.eu/article-19-notification-obligation/),
data controllers are obligated to communicate an erasure request to any data
processors to whom they’ve given personal data.
[The California Consumer Privacy Act (CCPA)](https://oag.ca.gov/privacy/ccpa#sectione),
the [Virginia Consumer Data Protection Act (VCDPA)](https://lis.virginia.gov/cgi-bin/legp604.exe?211+sum+SB1392),
and the [Colorado Privacy Act (CPA)](https://leg.colorado.gov/sites/default/files/2021a_190_signed.pdf)
in the United States contain similar requirements, and future legislation
enacted by other US states will likely follow suit. Users who wish to delete
their account may wish to exercise their right to erasure, which may require
deleting data in an application’s user repository and possibly other data
processor services.

It should be noted that the right of erasure does not nullify other obligations
a business or organization may have that require keeping records, including
those which contain personal information. There are several exceptions to the
right to erasure. Article 17, paragraph 3, of the GDPR outlines several
situations where the right of erasure does not apply. These include the
fulfillment of legal obligations on the part of a data controller or processor,
supporting rights for freedom of information and establishing, exercising, or
defending legal claims. The CCPA, VCDPA, and CPA also provide for several
exceptions. Financial institutions may have legal obligations to retain records
with personal information for a period of time after an account is closed.
Healthcare organizations often are required to retain healthcare-related
records for a period after the date of service. Even small businesses have
legal obligations to retain employment and tax records for a period of time.

### Certificate of Deletion

In addition to having procedures for disabling and terminating individual user
accounts for privacy reasons, corporate customers that terminate their use of a
service may request that their corporate account be deleted. This can include
the user data of administrative users associated with the account, application
data related to the service, and user data. Customers may request a certificate
of deletion that states that all their data has been deleted. If sensitive data
is involved, including data about users, customers may request a certificate of
secure deletion. This demonstrates their due diligence to ensure data they’ve
given to vendors has been deleted when no longer needed, which helps protect
sensitive information.

### Secure Delete

It can be surprisingly complex to “completely delete” data. Simply issuing a
delete command in a database or to delete a file may not completely delete the
data. In some cases, such a delete simply removes pointers to the data, but
does not alter the space on the disk where it was stored, allowing specially
written tools to recover the data.

Various techniques have been employed to effect secure deletion. One approach
is to encrypt data and throw away the encryption key. This effectively deletes
the data because it can no longer be decrypted. This approach assumes the time
required to decrypt the data using brute force mechanisms is significantly
longer than the time during which the data is likely to be valuable to data
thieves. Since it is impossible to predict how long this assumption will be
true as well as the future value of data, this is not a reliable option.

Another method of deleting data from a disk or other magnetic storage media
involves degaussing a disk. Degaussing to remove only one customer’s data is
not feasible in a cloud service where many customers’ data resides on the same
disk.

When a disk stores data of many customers, one customer’s data can effectively
be erased by overwriting the data with random `0`s and `1`s. The question is
how many times the data must be overwritten in order to ensure that residual
magnetic traces do not allow data recovery. The US Department of Defense (DoD)
5220.22-M protocol has been cited for this. The 1995 version of this standard
indicated data should be overwritten three times.
[This is now considered obsolete however](www.dami.army.pentagon.mil/site/IndustSec/docs/5220.22m.pdf).
For specific sanitization details, it has been superseded by the National
[Institute of Standards and Technology’s (NIST) “Special Publication 800-88](https://csrc.nist.gov/publications/detail/sp/800-88/rev-1/final):
Guidelines for Media Sanitization” which indicates that for most of today’s
media, overwriting with a fixed pattern, such as all zeros, with at least one
pass is sufficient. This technique would require a service to create features
to perform the overwriting.

### Consider Reprovisioning Requirements

It may be worth considering the likelihood of requests from customers to
reprovision their previously deprovisioned account and establishing policies
for this. It would constitute a security breach if an account were
reprovisioned and given to someone other than the original authorized owner, so
one option is to not support reprovisioning. If reprovisioning is to be
supported, you’ll need procedures for validating that a requestor is an
authorized owner of the original account.

## Summary

### Key Points

- Deprovisioning deletes or disables an account and associated identity
  information so it can no longer be used to access protected resources.
- Deprovisioning may be initiated by either an account owner or the owners of a
  service where the account resides.
- Automation and periodic account review should be used to help identify
  accounts that are no longer needed.
- A soft delete feature can be used to reduce accidental account deletion.
- Identifiers for deprovisioned accounts should be reserved and not used for
  new accounts.
- Data retention policies and procedures should be developed in consultation
  with legal and privacy experts.
- Procedures may need to be created to enable customers to download their data
  for use elsewhere, as part of account deprovisioning.
- Privacy legislation often includes a right to erasure. There may be
  requirements for how requests are to be made, timeframes for responses, and
  whether confirmations are sent. There are also several exceptions describing
  situations where data should not be erased.
- It may be necessary to provide customers a certificate of deletion or to
  follow secure delete procedures as part of account deprovisioning.
- Policies should be created for whether reprovisioning of accounts is allowed
  and, if so, the procedures to follow.
