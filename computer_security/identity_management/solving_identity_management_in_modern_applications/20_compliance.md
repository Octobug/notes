# Chapter 20: Compliance

> “Compliance” is just a subset of “governance” and not the other way around.
>
> —Pearl Zhu, from Digitizing Boardroom (2016)

- [Chapter 20: Compliance](#chapter-20-compliance)
  - [What Is Compliance?](#what-is-compliance)
    - [Government-Mandated Compliance](#government-mandated-compliance)
    - [Industry Compliance](#industry-compliance)
    - [Elective Compliance Frameworks](#elective-compliance-frameworks)
  - [Why Compliance](#why-compliance)
    - [Data Protection](#data-protection)
    - [Competitive Advantage](#competitive-advantage)
    - [Reduce Penalties](#reduce-penalties)
    - [Efficiency](#efficiency)
  - [Compliance Landscape](#compliance-landscape)
    - [Security Compliance](#security-compliance)
    - [Privacy Compliance](#privacy-compliance)
    - [Assessment and Certification](#assessment-and-certification)
  - [How to Proceed](#how-to-proceed)
  - [Summary](#summary)
    - [Key Points](#key-points)

## What Is Compliance?

Compliance is conforming to a rule, such as a specification, policy, standard,
or law. Organizations set goals for, and aspire to achieve, compliance to
ensure that their policies and practices are in conformance with relevant laws,
policies, and regulations or relevant standards. One way of categorizing
different types of compliance is

- Compliance required by legislation
- Compliance required by an industry
- Elective compliance

### Government-Mandated Compliance

Perhaps the most well known is the [GDPR (General Data Protection Regulation)](https://ec.europa.eu/commission/priorities/justice-and-fundamental-rights/data-protection/2018-reform-eu-data-protection-rules_en).

The California Privacy Rights Act (CPRA) adds to and amends the CCPA. It adds,
among other things, a right for consumers to correct inaccurate personal
information about themselves and a right to limit the use and disclosure of
sensitive personal information.

At the US federal level, the
[Federal Trade Commission (FTC) Fair Information Practice Principles (FIPP)](https://www.fpc.gov/resources/fipps/)
is designed to ensure that the practice of collecting information is fair and
provides adequate information privacy protection. It is based on the principles
of

- Notice/Awareness
- Choice/Consent
- Access/Participation
- Integrity/Security
- Enforcement/Redress

The FTC gives recommendations for maintaining privacy-friendly,
consumer-oriented data collection practices which are self-regulated.

Similarly, [HIPAA (Health Insurance Portability and Accountability)](www.hhs.gov/hipaa/for-professionals/index.html)
and [HITECH (Health Information Technology for Economic and Clinical Health](www.hhs.gov/hipaa/for-professionals/special-topics/hitech-act-enforcement-interim-final-rule/index.html)
are US legislation which apply to the handling of healthcare-related data.
These frameworks may apply to you if you process, store, or transmit any
electronic healthcare data for your customers.

### Industry Compliance

The payment card industry requires all organizations that handle payment card
data, including credit and debit cards, to comply with a set of standards,
known as [PCI DSS (Payment Card Industry Data Security Standard)](www.pcisecuritystandards.org/).
This set of security standards was created by the PCI Security Standards
Council, which was founded by five international credit card companies
([AMEX, Discover, JCP, Mastercard, and Visa](https://www.pcisecuritystandards.org/about_us/)).

The PCI DSS controls apply to systems which process, store, or transmit
cardholder data or authentication credentials and also apply to any systems
connected to an environment that directly contains or processes such cardholder
data. If your organization accepts, handles, or stores any type of payment card
data, or if you outsource payment processing to a third-party vendor but can
impact the security of the payment transactions in some way, you likely have
obligations under PCI DSS.

### Elective Compliance Frameworks

There are other security-related standards for which compliance is elective.
Companies can choose to be audited against these standards to demonstrate their
practices and operations follow the standard. For example, a company can elect
to comply with the [ISO 27000 (International Organization for Standardization
27000 family of standards for information security management systems)](https://www.iso.org/isoiec-27001-information-security.html).
Another elective security standard is from the
[CSA STAR (Cloud Security Alliance Security Trust Assurance and Risk) Program](https://cloudsecurityalliance.org/star/#_overview). The CSA STAR program
provides a comprehensive list of controls known as the Cloud Controls Matrix
(CCM).

## Why Compliance

If your project falls under the jurisdiction of legislation which requires
compliance, you must comply. Elective compliance, however, is a choice. There
are several reasons why companies choose to be certified against a set of
security or privacy standards:

- Protect the sensitive data they process or hold
- Use certification as a competitive sales tool
- Show due diligence to minimize penalties in the event of a breach
- Cost savings and efficiency in handling customer audit requests

### Data Protection

The first reason for pursuing compliance with an elective standard is to ensure
your organization is doing its due diligence to protect the data for which you
are under contract to protect. This is essentially the “sleep well at night”
argument for compliance.

### Competitive Advantage

A second reason to obtain a compliance certification is because it can be used
as a competitive sales tool.

### Reduce Penalties

Another good reason to obtain certification is to reduce penalties in the event
of a breach. For example, with the GDPR, the existence of a previously earned
certification is one factor taken into account when a fine is levied on an
organization related to a compromise of personal data. A certification is no
guarantee against a breach, but if you have audit evidence of due diligence in
implementing best practices, you may receive lower fines than if you do not
have a certification in place.

### Efficiency

A final impetus to earn certification is efficiency and cost reduction. In
order to provide a secure service to customers, a company must ensure that
every third party it uses protects the data it shares with them. The challenge
is how to obtain such assurance efficiently from the vendors.

In the absence of any standards for privacy and security, each company would
need to define privacy and security standards and examine each of its vendors
against them.

The field work for such an audit can take a week or more. It would be very
costly for a company to conduct its own audits of every vendor it uses. From a
vendor’s perspective, it would be time-consuming to provide such evidence
individually to each of their customers. In the absence of standards, different
customers would request different data and perhaps in different formats, making
the work to provide evidence to every customer unmanageable.

Security- and privacy-related standards provide a standard list of practices
and a consistent expectation for evidence to demonstrate compliance with the
standard. This enables a company to hire an independent third-party auditor to
conduct a review and certify the company’s practices against a standard.

## Compliance Landscape

Compliance frameworks are often divided into `privacy` and `security`
categories, but `privacy` frameworks typically include some form of `security`
requirements because security is a prerequisite for privacy.

### Security Compliance

Compliance with PCI DSS is required for the payment card industry. Compliance
with HIPAA and HITECH security rules is required in the United States for the
healthcare industry. FISMA (Federal Information Security Management Act) is
required for US government agencies and FedRAMP (Federal Risk and Authorization
Management Program) for cloud providers providing services to US government
agencies. A list of some security- related compliance frameworks is provided in
Appendix G.

### Privacy Compliance

Privacy legislation often differentiates between the responsibilities of a
`data controller` and a `data processor`.

- A `data controller` controls how personal data is used as documented in a
  contractual agreement or policy. The data controller collects data from end
  users and has obligations such as providing privacy notices, obtaining user
  consent for the use of their data, and providing users with certain access to
  their data as well as the ability to correct it.
- A `data processor` processes data in accordance with instructions from a data
  collector in a data processing agreement.

It is also important to determine privacy obligations early in the project
cycle, because they can impact the application design in order to give notice
about the purposes of data collection, obtain and record consent for how data
is used, manage data retention, and implement data correction and erasure
features.

### Assessment and Certification

Some standards rely on self-assessment, but most require an audit by an
independent third-party organization certified to conduct the particular type
of audit.

- Self-assessment requires an organization to examine their policies and
  practices against the standard and remedy any gaps.
  - The CSA STAR framework’s first level of compliance is one example that
    involves self-assessment.
- For many other standards, an independent, third-party audit of policies,
  practices, and operations against the standard is a requirement.

## How to Proceed

Once you’ve identified relevant compliance frameworks for your project, you
need to plan the work required to implement and demonstrate compliance:

- Identify the national, state, or industry-specific privacy legislation
  applicable for the regions in which your business operates.
- Research privacy and security requirements for the countries or regions in
  which your users reside.
- Identify cybersecurity requirements applicable for your industry.
- If you supply services to public sector organizations or process government
  data, check for applicable government requirements.
- Identify elective security standards which may be beneficial to demonstrate
  your security practices to prospective customers.
- Consult with legal, privacy, or security experts if you have any questions
  about which legislation or security requirements apply.
- Create a data map that describes the data elements of all data repositories
  and data flows for all data you handle.
- Note all data elements in the map which involve personal data.
- Document the reason for collecting the data and the data processing
  activities to be performed with the data.
- Review data processing to ensure your application collects the minimum data
  required in accordance with your privacy statement.
- If available, use a self-assessment tool for a compliance standard to
  identify gaps that must be mitigated before an official audit.
- Retain a secondary auditor for advice on what to expect or an informal
  assessment before an official audit to help you meet audit requirements
  without wasting time on unnecessary tasks.
- Know the scope of evidence required for an audit. For some certifications, a
  year’s worth of past evidence is required.
- Make a list of audit evidence required, and identify owners within your
  organization for each category of evidence.
- Periodically check that owners understand the evidence required and their
  teams are generating the evidence needed for an audit.
- Select a reputable third-party auditor with experience in your domain and who
  will provide both an official audit result and an internal report on
  recommended improvement activities.
- Prior to an audit, get the official list from the auditor of evidence
  required. Work with owners to obtain the requested evidence.
- During the audit, additional information is often requested. Have parties
  ready to gather additional evidence.
- Conduct a postaudit assessment after an audit to identify what went well and
  how to improve the process for the next audit.
- Focus on one certification at a time.

## Summary

### Key Points

- Compliance involves assessing and demonstrating adherence to a set of
  controls.
- Privacy- and security-related compliance may be required by legislation or
  industry.
- Security-related compliance can be chosen for security and business advantage
  in scenarios where it is not mandatory.
- Privacy-related legislation is mandatory for entities which meet the criteria
  set out in the legislation.
- Over 100 countries have enacted privacy-related legislation.
- In the United States, privacy-related legislation is being enacted by many
  states as well as industry sectors.
- Certification against privacy- and security-related compliance frameworks
  - Demonstrates due diligence in protecting data you manage
  - Can be used as a competitive sales tool
  - May lessen fines in the event of a breach
  - Is an efficient way to respond to audit needs of individual customers
- A critical first step for compliance is building an inventory of systems and
  the data they contain, along with the reason for collecting any personal data
  and how the data is processed.
- The Cloud Security Alliance’s Cloud Controls Matrix provides a useful mapping
  of controls across different security-related compliance frameworks.
