# Best practices for event logging and threat detection

> <https://www.cyber.gov.au/sites/default/files/2024-08/best-practices-for-event-logging-and-threat-detection.pdf>

- [Best practices for event logging and threat detection](#best-practices-for-event-logging-and-threat-detection)
  - [Executive summary](#executive-summary)
  - [Introduction](#introduction)
    - [Audience](#audience)
  - [Best practices](#best-practices)
    - [Enterprise-approved event logging policy](#enterprise-approved-event-logging-policy)
      - [Event log quality](#event-log-quality)
      - [Captured event log details](#captured-event-log-details)
        - [Operational Technology considerations](#operational-technology-considerations)
        - [Captured event log details - Additional resources](#captured-event-log-details---additional-resources)
      - [Content and format consistency](#content-and-format-consistency)
      - [Timestamp consistency](#timestamp-consistency)
        - [Timestamp consistency - Additional resources](#timestamp-consistency---additional-resources)
      - [Event log retention](#event-log-retention)
    - [Centralised log collection and correlation](#centralised-log-collection-and-correlation)
      - [Logging priorities for enterprise networks](#logging-priorities-for-enterprise-networks)
      - [Logging priorities for operational technology](#logging-priorities-for-operational-technology)
      - [Logging priorities for enterprise mobility using mobile computing devices](#logging-priorities-for-enterprise-mobility-using-mobile-computing-devices)
      - [Logging priorities for cloud computing](#logging-priorities-for-cloud-computing)
    - [Secure storage and event log integrity](#secure-storage-and-event-log-integrity)
      - [Secure transport and storage of event logs](#secure-transport-and-storage-of-event-logs)
      - [Protecting event logs from unauthorised access, modification and deletion](#protecting-event-logs-from-unauthorised-access-modification-and-deletion)
      - [Centralised event logging enables threat detection](#centralised-event-logging-enables-threat-detection)
      - [Timely ingestion](#timely-ingestion)
    - [Detection strategy for relevant threats](#detection-strategy-for-relevant-threats)
      - [Detecting living off the land techniques](#detecting-living-off-the-land-techniques)
        - [Case study – Volt Typhoon](#case-study--volt-typhoon)
        - [Cloud considerations](#cloud-considerations)
        - [Operational technology considerations](#operational-technology-considerations-1)

## Executive summary

Event logging supports the continued delivery of operations and improves the
security and resilience of critical systems by enabling network visibility.

An effective event logging solution aims to:

- send alerts to the network defenders responsible for monitoring when cyber
  security events such as critical software configuration changes are made or
  new software solutions are deployed
- identify cyber security events that may indicate a cyber security incident,
  such as malicious actors employing living off the land (LOTL) techniques or
  lateral movement post-compromise
- support incident response by revealing the scope and extent of a compromise
- monitor account compliance with organisational policies
- reduce alert noise, saving on costs associated with storage and query time
- enable network defenders to make agile and informed decisions based on
  prioritisation of alerts and analytics
- ensure logs and the logging platforms are useable and performant for analysts.

There are four key factors to consider when pursuing logging best practices:

1. enterprise-approved event logging policy
2. centralised event log access and correlation
3. secure storage and event log integrity
4. detection strategy for relevant threats.

## Introduction

### Audience

This guidance is technical in nature and is intended for those within medium to
large organisations. As such, it is primarily aimed at:

- senior information technology (IT) and OT decision makers
- IT and OT operators
- network administrators
- critical infrastructure providers.

## Best practices

### Enterprise-approved event logging policy

- The logging policy should take into consideration any shared responsibilities
  between service providers and the organisation.
- The policy should also include details of the events to be logged, event
  logging facilities to be used, how event logs will be monitored,
  event log retention durations, and when to reassess which logs are worthy of
  collection.

#### Event log quality

In the context of cyber security incident response and threat detection, event
log quality refers to the types of events collected rather than how well a log
is formatted.

📝 Capturing a large volume of well-formatted logs can be invaluable for
incident responders in forensics analysis scenarios.

However, organisations are encouraged to properly organise logged data into

- ‘hot’ data storage that is readily available and searchable, or
- ‘cold’ data storage that has deprioritised availability and is stored through
  more economical solutions - an important consideration when evaluating an
  organisation’s log storage capacity.

For more information on how to prioritise collection of high-quality event logs:
[Guidance for Implementing M-21-3: Improving the Federal Government’s Investigative and Remediation Capabilities](https://www.cisa.gov/sites/default/files/2023-02/TLP%20CLEAR%20-%20Guidance%20for%20Implementing%20M-21-31_Improving%20the%20Federal%20Governments%20Investigative%20and%20Remediation%20Capabilities_.pdf)

To strengthen detection of malicious actors employing LOTL techniques, some
relevant considerations for event logging include:

- On Linux-based systems, logs capturing the use of `curl`, `systemctl`,
  `systemd`, `python` and other common LOLBins leveraged by malicious actors.
- On Microsoft Windows-based systems, logs capturing the use of `wmic.exe`,
  `ntdsutil.exe`, `Netsh`, `cmd.exe`, `PowerShell`, `mshta.exe`, `rundll32.exe`,
  `resvr32.exe` and other common LOLBins leveraged by malicious actors. Ensure
  that logging captures command execution, script block logging and module
  logging for PowerShell, and detailed tracking of administrative tasks.
- For cloud environments, logging all control plane operations, including API
  calls and end user logins. The control plane logs should be configured to
  capture read and write activities, administrative changes, and authentication
  events.

#### Captured event log details

As a part of an organisation’s event logging policy, captured event logs should
contain sufficient detail to aid network defenders and incident responders.

A good baseline for what an event log should capture, if applicable:

- properly formatted and accurate timestamp (millisecond granularity is ideal)
- event type (status code)
- device identifier (MAC address or other unique identifier)
- session/transaction ID
- autonomous system number
- source and destination IP (includes both IPv4 and IPv6)
- status code
- response time
- additional headers (e.g. HTTP headers)
- the user ID, where appropriate
- the command executed, where appropriate
- a unique event identifier to assist with event correlation, where possible.

##### Operational Technology considerations

Out-of-band log communications, or generating logs based on error codes and the
payloads of existing communications, can account for embedded devices with
limited logging capabilities.

##### Captured event log details - Additional resources

The following resources include examples of details to be logged:

- ASD’s ACSC [Information Security Manual](https://www.cyber.gov.au/resources-business-and-government/essential-cyber-security/ism)
  (ISM) provides event log details to record in the
  [Guidelines for System Monitoring](https://www.cyber.gov.au/resources-business-and-government/essential-cyber-security/ism/cyber-security-guidelines/guidelines-system-monitoring).
- CISA’s [Guidance for Implementing M-21-31: Improving the Federal Government’s Investigative and Remediation Capabilities](https://www.cisa.gov/sites/default/files/2023-02/TLP%20CLEAR%20-%20Guidance%20for%20Implementing%20M-21-31_Improving%20the%20Federal%20Governments%20Investigative%20and%20Remediation%20Capabilities_.pdf)
  details another approach to prioritising log collection and is aimed at US
  federal civilian executive branch organisations.
- NIST has outlined OT considerations for event logging in their
  [Guide to Operational Technology (OT) Security](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-82r3.pdf).
- For examples of detection uses cases, consider visiting the MITRE ATT&CK®
  list of [data sources](https://attack.mitre.org/datasources/).

#### Content and format consistency

Since logs may vary in structure (or lack thereof), implementing a method of
automated log normalisation is recommended. This is an important consideration
for logs that can change over time or without notice such as software and
Software-as-a-Service (SaaS) logs.

#### Timestamp consistency

Where possible, organisations should use multiple accurate time sources in case
the primary time source becomes degraded or unavailable. Note that,
particularly in distributed systems, time zones and distance can influence how
timestamps read in relation to each other.

- Time servers should be synchronised and validated throughout all environments
  and set to capture significant events, such as device boots and reboots
- Using Coordinated Universal Time (UTC) has the advantage of no time zones as
  well as no daylight savings, and is the preferred time standard.
  - Implement ISO 8601 formatting, with the year listed first, followed by the
    month, day, hour, minutes, seconds, and milliseconds (e.g.
    2024-07-25T20:54:59.649Z).
- Timesharing should be unidirectional. The OT environment should sychronise
  time sync with the IT environment and not the other way around.
- Data historians may be implemented on some operational assets to record and
  store time-series data of industrial processes running on the computer system.
  These can provide an additional source of event log data for OT networks.

##### Timestamp consistency - Additional resources

- [Windows Event Logging and Forwarding](https://www.cyber.gov.au/resources-business-and-government/maintaining-devices-and-systems/system-hardening-and-administration/system-monitoring/windows-event-logging-and-forwarding)
- [CISA’s Logging Made Easy (LME)](https://www.cisa.gov/resources-tools/services/logging-made-easy)
  - [GitHub Page](https://github.com/cisagov/LME)
- The Joint SIGINT Cyber Unit (JSCU) of the AIVD and MIVD has published a
  repository on GitHub with a Microsoft Windows event logging and collections
  baseline focused on finding balance between forensic value and optimising
  retention: <https://github.com/JSCU-NL/logging-essentials>

#### Event log retention

- Organisations should ensure they retain logs for long enough to support cyber
  security incident investigations.
- When assessing the risks to a system, consider that in some cases, it can
  take up to 18 months to discover a cyber security incident and some malware
  can dwell on the network from 70 to 200 days before causing overt harm.
- Insufficient storage is a common obstacle to log retention.
- For effective security logging practices, organisations should implement data
  tiering such as hot and cold storage.

### Centralised log collection and correlation

#### Logging priorities for enterprise networks

ASD’s ACSC and co-authors recommend that organisations prioritise the following
log sources within their enterprise network:

1. critical systems and data holdings likely to be targeted
2. internet-facing services, including remote access, network metadata, and
   their underlying server operating system
3. identity and domain management servers
4. any other critical servers
5. edge devices, such as boundary routers and firewalls
6. administrative workstations
7. highly privileged systems such as configuration management, performance and
   availability monitoring (in cases where privileged access is used),
   Continuous Integration/Continuous Delivery (CI/CD), vulnerability scanning
   services, secret and privilege management
8. data repositories
9. security-related and critical software
10. user computers
11. user application logs
12. web proxies used by organisational users and service accounts
13. DNS services used by organisational users
14. email servers
15. DHCP servers
16. legacy IT assets (that are not previously captured in critical or
    internet-facing services)

ASD’s ACSC and co-authors recommend organisations monitor lower priority logs
as well. These include:

- underlying infrastructure, such as hypervisor hosts
- IT devices, such as printers
- network components such as application gateways.

#### Logging priorities for operational technology

ASD’s ACSC and co-authors recommend that organisations prioritise the following
log sources in their OT environment:

1. OT devices critical to safety and service delivery, except for air-gapped
   systems
2. internet-facing OT devices
3. OT devices accessible via network boundaries.

Note that in cases where OT devices do not support logging, device logs are not
available, or are available in a non-standard format, it is good practice to
ensure network traffic and communications to and from the OT devices are logged.

#### Logging priorities for enterprise mobility using mobile computing devices

Mobile device management (MDM) solutions allow organisations to manage the
security of their enterprise mobility, typically including logging
functionality. In the context of enterprise mobility, the aim of effective
event logging is to detect compromised accounts or devices; for example, due to
phishing or interactions with malicious applications and websites.

ASD’s ACSC and co-authors recommend organisations prioritise the following log
sources in their enterprise mobility solution:

1. web proxies used by organisational users
2. organisation operated DNS services
3. device security posture of organisationally managed devices
4. device behaviour of organisationally managed devices
5. user account behaviour such as sign-ins
6. VPN solutions
7. MDM and Mobile Application Management (MAM) events

Additional monitoring should be implemented in collaboration with the
telecommunications network provider. Such monitoring includes:

- signalling exploitation
- binary/invisible SMS
- CLI spoofing
- SIM/eSIM activities such as SIM swapping
- null cipher downgrade
- connection downgrade (false base station)
- network API/query against user
- roaming traffic protection
- roaming steering.

Organisations should obtain legal advice about what can be logged from any
personally owned mobile devices that are enrolled in an MDM solution. For
example, logging GPS location may be subject to restrictions.

#### Logging priorities for cloud computing

ASD’s ACSC and co-authors recommend organisations adjust event logging practices
in accordance with the cloud service that is administered, whether
Infrastructure-as-a-Service (IaaS), Platform-as-a-Service (PaaS), or SaaS are
implemented. For example,

- IaaS would include a significant amount of logging responsibility on the
  tenant, whereas
- SaaS would place a significant amount of the logging responsibility on the
  provider.

Therefore, organisations should coordinate closely with their cloud service
provider to understand the shared-responsibility model in place, as it will
influence their logging priorities. Logging priorities will also be influenced
by different cloud computing service models and deployment models (that is,
public, private, hybrid, community). Where privacy and data sovereignty laws
apply, logging priorities may also be influenced by the location of the cloud
service provider’s infrastructure. See NSA’s [Manage Cloud Logs for Effective
Threat Hunting guidance](https://media.defense.gov/2024/Mar/07/2003407864/-1/-1/0/CSI_CloudTop10-Logs-for-Effective-Threat-Hunting.PDF)
for additional information.

Organisations should prioritise the following log sources in their use of cloud
computing services:

1. critical systems and data holdings likely to be targeted
2. internet-facing services (including remote access) and, where applicable,
   their underlying server operating systems
3. use of the tenant’s user accounts that access and administer cloud services
4. logs for administrative configuration changes
5. logs for the creation, deletion and modification of all security principals,
   including setting and changing permissions
6. authentication success and/or failures to third party services (e.g.
   SAML/OAuth)
7. logs generated by the cloud services, including logs for cloud APIs, all
   network-related events, compliance events and billing events.

### Secure storage and event log integrity

Forwarding event logs to a centralised and secure storage capability prevents
the loss of logs once the local device’s storage is exhausted.

#### Secure transport and storage of event logs

- Transport Layer Security (TLS) 1.3 and methods of cryptographic verification
  to ensure the integrity of event logs in-transit and at rest.
- Organisations should prioritise securing and restricting access to event logs
  that have a justified requirement to record sensitive data.

#### Protecting event logs from unauthorised access, modification and deletion

Logs may contain sensitive data that is useful to a malicious actor. As a
result, users should only have access to the event logs they need to do their
job.

The storage of logs should be in a separate or segmented network with
additional security controls to reduce the risk of logs being tampered with in
the event of network or system compromise.

Events logs should also be backed up and data redundancy practices should be
implemented.

Organisations should consider filtering event logs before sending them to a
SIEM or XDR to ensure it is receiving the most valuable logs to minimise any
additional costs or capacity issues.

#### Centralised event logging enables threat detection

The aggregation of event logs to a central logging facility that a SIEM can
draw from enables the identification of:

- deviations from a baseline
  - A baseline should include installed tools and software, user account
    behaviour, network traffic, system intercommunications and other items, as
    applicable. Particular attention should be paid to privileged user accounts
    and critical assets such as domain controllers.
  - A baseline is derived by performing an analysis of normal behaviour of some
    user accounts and establishing ‘always abnormal’ conditions for those same
    accounts.
- cyber security events
  - For the purpose of this document, a cyber security event is an occurrence
    of a system, service or network state indicating a possible breach of
    security policy, failure of safeguards or a previously unknown situation
    that may be relevant to security.
- cyber security incidents
  - For the purpose of this document, a cyber security incident is an unwanted
    or unexpected cyber security event, or a series of such events, that either
    has compromised business operations or has a significant probability of
    compromising business operations.

#### Timely ingestion

Timely ingestion of event logs is important in the early detection of a cyber
security events and cyber security incidents.

### Detection strategy for relevant threats

#### Detecting living off the land techniques

Organisations consider implementing user and entity behavioural analytics
capabilities to enable automated detection of behavioural anomalies on networks,
devices, or accounts. SIEMs can detect anomalous activity by comparing event
logs to a baseline of business-as-usual traffic and activity. Behavioural
analytics plays a key role in detecting malicious actors employing LOTL
techniques.

##### Case study – Volt Typhoon

Volt Typhoon uses PowerShell, a command and scripting interpreter, to:

- discover remote systems
- identify associated user and computer account names using the command
  `Get-EventLog security –instanceid 4624`
- enumerate logs to search for successful logons using `wevtutil.exe` and the
  command `Get-EventLog Security`.

Volt Typhoon consistently obtains valid credentials by extracting the Active
Directory database file `NTDS.dit`. To do so, Volt Typhoon has been observed to:

- execute the Windows-native `vsssadmin` command to create a volume shadow copy
- use Windows Management Instrumentation Console (WMIC) commands to execute
  `ntdsutil.exe` to copy `NTDS.dit` and the SYSTEM registry from the volume
  shadow copy
- move laterally to the Microsoft Active Directory Domain Services (AD DS)
  domain controller via an interactive RDP session using a compromised user
  account with domain administrator privileges.

Other LOTL techniques that Volt Typhoon has been observed to use includes:

- accessing hashed credentials from the Local Security Authority SubSystem
  Service (LSASS) process memory space
- using `ntdsutil.exe` to create installation media from Microsoft AD DS domain
  controllers, either remote or locally, which contain username and password
  hashes
- using PowerShell, WMIC, and the `ping` command, to facilitate system discovery
- using the built-in `netsh portproxy` command to create proxies on compromised
  systems to facilitate access.

While Volt Typhoon uses LOTL techniques to make detection more difficult, the
behaviours that the malware exhibits would be considered abnormal compared to
business-as-usual activity and could be used to create detection use cases.

Examples of anomalous behaviour can include:

- a user logging in during unusual hours
- an account accessing services that it does not usually access
- a user logging in using an unusual device
- a high volume of access attempts
- instances of impossible travel or concurrent sign-ins from multiple
  geographic locations
- downloading or exporting a large volume of data
- network logins without defined computer access or physical access log
  validation
- a single IP address attempting to authenticate as multiple different users
- the creation of user accounts, or disabled accounts being re-enabled,
  especially accounts with administrative privileges
- netflow data indicating one device talking to other internal devices it
  normally does not connect to
- unusual script execution, software installation, or use of administrative
  tools
- unexpected clearing of logs
- an execution of the process from an unusual or suspicious path
- configuration changes to security software, such as Windows Defender, and
  logging management software.

To detect threats on endpoints such as user devices, organisations should
consider implementing an endpoint detection and response solution. These
solutions enable an organisation to monitor malicious activity, such as
malicious actors disabling security monitoring services, and process creation
events with enhanced detail and fidelity.

Organisations may also consider the following methods to increase the
effectiveness of detecting potential LOTL techniques:

- Always enable detailed logging that includes process creation events and
  command-line auditing. This enhances log visibility and facilitates threat
  hunting, if needed.
- Establish a baseline for the usage of legitimate binaries within the
  organisation and flag any anomalous behaviour.
- Create specific SIEM detection rules based on the evolving threat landscape
  for different operating systems. For example, `powershell.exe`, `cmd.exe`,
  `regedit.exe` for Microsoft Windows, or `curl`, `systemctl` and `python` for
  Linux, with encoded commands.

##### Cloud considerations

One point states that if machine learning-powered detection capabilities are
available within cloud provider security services, organisations should
consider leveraging these capabilities and provide log data in real time from
multiple sources to enhance log analysis. Using machine learning allows for the
detection of anomalous behaviours that may indicate malicious activity. These
include irregular API call patterns (especially those that involve changes to
security groups, configuration of cloud resources or access to sensitive data),
unusual cloud storage access and atypical network traffic.

##### Operational technology considerations

Network defenders should leverage real-time alerts to determine any abnormal
activity on an OT network. These alerts can include safety data, availability
data, logins, failed logins, configuration changes, and network access and
traffic. Organisations may need to consider whether alerts for OT environments
should be approached differently. For example, OT devices may be in remote or
hard-to-reach locations.

For detecting anomalous behaviour in OT environments, look for:

- unexpected use of engineering and configuration tools
- abnormal use of vendor or third-party accesses, maintenance methods, or
  remote monitoring
- unauthorised updates or changes to operating systems, software, firmware,
  configurations, or databases
- unexpected communication between the control system and external network or
  unusual communication between components that do not usually communicate
- execution of scripts that are not part of regular operations.

Intrusion detection and intrusion prevention systems (IDS/IPS) are often
designed with rules based on IT protocols; therefore, they may be more useful
in OT operation systems or the OT demilitarised zone (DMZ) than in supervisory
and process areas. Note, it is not recommended to deploy an IPS unless it is
tailored to the OT environment, or is outside of critical process control. IPS
risk interrupting critical OT devices.
