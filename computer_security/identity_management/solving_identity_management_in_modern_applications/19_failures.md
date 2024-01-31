# Chapter 19: Failures

> Those who cannot remember the past are condemned to repeat it.
>
> —George Santayana, Spanish philosopher, poet, and novelist, from The Life of
> Reason, vol. 1 (1905)

- [Chapter 19: Failures](#chapter-19-failures)
  - [Pay Attention to Process](#pay-attention-to-process)
  - [Beware of Phishy Emails](#beware-of-phishy-emails)
  - [Use Multi-factor Authentication](#use-multi-factor-authentication)
  - [Stay on Top of Patches](#stay-on-top-of-patches)
  - [Secure Your Cloud Storage](#secure-your-cloud-storage)
  - [Encrypt Sensitive Data](#encrypt-sensitive-data)
  - [Do Not Store Cleartext Passwords](#do-not-store-cleartext-passwords)
  - [Provide Security Training to Developers](#provide-security-training-to-developers)
  - [Vet Your Partners](#vet-your-partners)
  - [Insider Threat](#insider-threat)
  - [Summary](#summary)
    - [Key Points](#key-points)

Hacking, malware, human error, and social engineering topped
[the lists in the 2020](https://www.verizon.com/business/resources/reports/2020-data-breach-investigations-report.pdfx),
[2021](https://www.verizon.com/business/resources/reports/2021-data-breach-investigations-report.pdfx)
and [2022](https://www.verizon.com/business/resources/reports/2022/dbir/2022-data-breach-investigations-report-dbir.pdf)
reports.

## Pay Attention to Process

In 2015, Edward Hornsey, an enterprising young businessman, hit upon the idea
of buying used iPhones, many of which were stolen, and returning them to Apple
to take advantage of their liberal return policy. He received shiny new
replacement phones in exchange, which he was then able to sell at a handsome
profit. Surprisingly, he managed to do this 51 times before Apple caught on.

If you handle any identity information, avoid printing sensitive information
except where absolutely necessary. In addition, provide shredders and train all
staff regularly on data protection procedures, including shredding printouts
with sensitive information.

## Beware of Phishy Emails

## Use Multi-factor Authentication

## Stay on Top of Patches

## Secure Your Cloud Storage

## Encrypt Sensitive Data

If you handle sensitive data, and identity data is by definition considered
sensitive, you should encrypt the data at rest and in transit. This protection
should extend to backups and log files. In addition, logs should be scanned to
ensure sensitive data isn’t leaked to log files.

## Do Not Store Cleartext Passwords

## Provide Security Training to Developers

A good place to start for advice on secure coding practices is the most recent
version of the Open Web Application Security Project (OWASP) Top 10 security
and coding guidance.

- [OWASP Top 10](https://owasp.org/Top10/)

To reduce vulnerabilities in application code, ensure that developers are
thoroughly trained on the current OWASP Top 10 application security risks and
how to prevent them. In addition, to mitigate the risk of human error,
institute code reviews and automated software vulnerability scanning to
identify vulnerabilities in your application code.

## Vet Your Partners

## Insider Threat

- The first is to implement the classic security principle of granting each
  person the least privilege required to do their job and to design access
  models to enforce segregation of duties.
- A second protection is to encrypt data at rest and in transit and implement
  adequate protection of the encryption keys.
- A third technique is to employ security monitoring software that can detect
  anomalous activity (especially high-volume data retrieval and exfiltration).
- Data loss prevention (DLP) solutions, which are designed to prevent
  exfiltration of data by detecting anomalous traffic out of a network or
  device, can also be used.

## Summary

### Key Points

- Processes, in addition to infrastructure, should be analyzed for
  vulnerabilities.
- Train users to recognize and avoid phishing attacks to reduce risk of malware.
- Use multi-factor authentication to mitigate the risk of compromised passwords.
- Monitor for software vulnerabilities and apply patches when vulnerabilities
  are announced. Leverage automation and tools for this process where possible.
- Follow secure configuration guidelines for all cloud-hosted components such
  as Amazon S3 buckets and cloud databases such as Elasticsearch, Firebase, and
  MongoDB.
- Encrypt sensitive data at rest and in transit, including backups and log
  files.
- Avoid storing cleartext passwords.
- Provide security and secure coding training for developers.
- Vet partners by checking certifications and conducting due diligence
  evaluation of security practices.
- Mitigate the risk of insider threat by granting minimum needed privileges and
  frequently reviewing access grants as well as logs.
