# Appendixes

- [Appendixes](#appendixes)
  - [Appendix A: Glossary](#appendix-a-glossary)
  - [Appendix B: Resources for Further Learning](#appendix-b-resources-for-further-learning)
    - [B.1. OAuth 2 – Related Specifications](#b1-oauth-2--related-specifications)
    - [B.2. JWT](#b2-jwt)
    - [B.3. OIDC](#b3-oidc)
    - [B.4. SAML](#b4-saml)
    - [B.5. Multi-factor Authentication](#b5-multi-factor-authentication)
    - [B.6. Background Information](#b6-background-information)
    - [B.7. Privacy](#b7-privacy)
  - [Appendix C: SAML 2 Authentication Request and Response](#appendix-c-saml-2-authentication-request-and-response)
    - [C.1. SAML 2 Authentication Request](#c1-saml-2-authentication-request)
    - [C.2. SAML 2 Authentication Response](#c2-saml-2-authentication-response)
      - [C.2.1. Response](#c21-response)
        - [C.2.1.1. Authentication Assertion (Beginning)](#c211-authentication-assertion-beginning)
        - [C.2.1.2. Digital Signature for Authentication Assertion](#c212-digital-signature-for-authentication-assertion)
        - [C.2.1.3. Subject](#c213-subject)
        - [C.2.1.4. Conditions](#c214-conditions)
        - [C.2.1.5. Authentication Statement](#c215-authentication-statement)
        - [C.2.1.6. Attribute Statements](#c216-attribute-statements)
    - [C.3. Validation](#c3-validation)
  - [Appendix D: Public Key Cryptography](#appendix-d-public-key-cryptography)
  - [Appendix E: Troubleshooting Tools](#appendix-e-troubleshooting-tools)
    - [E.1. Capture an HTTP Trace](#e1-capture-an-http-trace)
    - [E.2. View a HAR File](#e2-view-a-har-file)
    - [E.3. Capture a Network Trace](#e3-capture-a-network-trace)
    - [E.4. View Security Tokens](#e4-view-security-tokens)
    - [E.5. Test APIs](#e5-test-apis)
  - [Appendix F: Privacy Legislation](#appendix-f-privacy-legislation)
    - [F.1. European Union](#f1-european-union)
    - [F.2. United States](#f2-united-states)
    - [F.3. Other Countries](#f3-other-countries)
    - [F.4. Notes](#f4-notes)
  - [Appendix G: Security Compliance Frameworks](#appendix-g-security-compliance-frameworks)
    - [G.1. General Security Frameworks](#g1-general-security-frameworks)
    - [G.2. US Frameworks](#g2-us-frameworks)
    - [G.3. SOC(Service Organization Control)](#g3-socservice-organization-control)
  - [Appendix A](#appendix-a)

## Appendix A: Glossary

- **Confidential Client** – In the context of OAuth 2 and OIDC, an application
  that runs on a protected server which enables it to securely store
  confidential secrets with which to authenticate itself to the authorization
  server.
- **Directory Server** – A repository for storing, managing, and organizing
  information about resources. Directory server products have often been
  optimized for storing information that is frequently read but infrequently
  modified and used to store information about entities such as users, access
  control privileges, application configurations, and network printers.
  Information in directory services has been used for authentication and
  authorization of users.
- **Public Client** – In the context of OAuth 2 and OIDC, an application that
  executes primarily on the user’s client device or in the client browser and
  cannot securely store secrets with which to authenticate itself to an
  authorization server.
- Security Domain – A security domain is a logical construct that defines the
  boundaries of one entity’s control or ownership.

## Appendix B: Resources for Further Learning

### B.1. OAuth 2 – Related Specifications

- OAuth 2.1 Authorization Framework (draft as of this writing) – Consolidates
  several OAuth-related specifications since the original OAuth 2.0
  specification: <https://datatracker.ietf.org/doc/html/draft-ietf-oauth-v2-1-06>
- OAuth 2.0 Authorization Framework (original specification): <https://tools.ietf.org/html/rfc6749>
- OAuth 2.0 Threat Model and Security Considerations: <https://tools.ietf.org/html/rfc6819>
- OAuth 2.0 for Browser-Based Apps (draft as of this writing): <https://datatracker.ietf.org/doc/html/draft-ietf-oauth-browser-based-apps>
- OAuth 2.0 for Native Apps: <https://tools.ietf.org/html/rfc8252>
- OAuth 2.0 Security Best Current Practice (draft as of this writing): <https://datatracker.ietf.org/doc/html/draft-ietf-oauth-security-topics>
- OAuth 2.0 Device Authorization Grant: <https://datatracker.ietf.org/doc/html/rfc8628>
- OAuth 2.0 Authorization Framework: Bearer Token Usage: <https://tools.ietf.org/html/rfc6750>
- Proof Key for Code Exchange by OAuth Public Clients: <https://tools.ietf.org/html/rfc7636>
- OAuth 2.0 Token Introspection: <https://tools.ietf.org/html/rfc7662>
- OAuth 2.0 Token Revocation: <https://tools.ietf.org/html/rfc7009>
- OAuth 2.0Pushed Authorization Requests (PAR): <https://datatracker.ietf.org/doc/html/rfc9126>
- OAuth 2.0Rich Authorization Requests(RAR): (draft as of this writing) <https://datatracker.ietf.org/doc/html/draft-ietf-oauth-rar>
- JWT-Secured Authorization Requests(JAR): <https://datatracker.ietf.org/doc/html/rfc9101>

### B.2. JWT

- JSON Web Token (JWT): <https://tools.ietf.org/html/rfc7519>
- JSON Web Encryption (JWE): <https://datatracker.ietf.org/doc/html/rfc7516/>
- JSON Web Signature (JWS): <https://datatracker.ietf.org/doc/html/rfc7515>

### B.3. OIDC

- OIDC Specifications: <https://openid.net/connect/>

### B.4. SAML

- SAML specifications. See especially the core, bindings, and profile
  specifications: <https://wiki.oasis-open.org/security/FrontPage>
- Security Assertion Markup Language (SAML) V2.0 Technical Overview: <https://www.oasis-open.org/committees/download.php/27819/sstc-saml-tech-overview-2.0-cd-02.pdf>
- SAML Security and Privacy Considerations for the OASIS Security Assertion
  Markup Language (SAML) V2.0: <http://docs.oasis-open.org/security/saml/v2.0/saml-sec-consider-2.0-os.pdf>
- SAML 2.0 ProfileforOAuth 2.0Client Authentication and Authorization Grants: <https://datatracker.ietf.org/doc/html/rfc7522>

### B.5. Multi-factor Authentication

- The FIDO Alliance: <https://fidoalliance.org/fido2/>
- WebAuthn: <www.w3.org/TR/2019/REC-webauthn-1-20190304/>

### B.6. Background Information

- An explanation of cookies, including security guidance: <https://developer.mozilla.org/en-US/docs/Web/HTTP/Cookies>
- Explanation of Cross-Origin Resource Sharing (CORS): <https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS>
- Brief outline of different approaches to authorization and access control: <https://nvlpubs.nist.gov/nistpubs/Legacy/IR/nistir7316.pdf>
- OWASP Top 10 – Critical security risks for web applications and how to avoid
  them: <www.owasp.org/index.php/Category:OWASP_Top_Ten_Project>
- OWASP SAML Cheat Sheet: <https://github.com/OWASP/CheatSheetSeries/blob/master/cheatsheets/SAML_Security_Cheat_Sheet.md>
- Two sites on open redirects:
  - <https://github.com/OWASP/CheatSheetSeries/blob/master/cheatsheets/Unvalidated_Redirects_and_Forwards_Cheat_Sheet.md>
  - <https://cwe.mitre.org/data/definitions/601.html>
- Checking for breached passwords – I’ve Just Launched “Pwned Passwords” V2: <https://www.troyhunt.com/ive-just-launched-pwned-passwords-version-2>

### B.7. Privacy

- A map showing the location and strength of privacy legislation around the world: <https://www.dlapiperdataprotection.com/>
- This website presents the articles of the GDPR in a convenient fashion: <https://gdpr-info.eu/>

## Appendix C: SAML 2 Authentication Request and Response

### C.1. SAML 2 Authentication Request

### C.2. SAML 2 Authentication Response

#### C.2.1. Response

##### C.2.1.1. Authentication Assertion (Beginning)

##### C.2.1.2. Digital Signature for Authentication Assertion

##### C.2.1.3. Subject

##### C.2.1.4. Conditions

##### C.2.1.5. Authentication Statement

##### C.2.1.6. Attribute Statements

### C.3. Validation

## Appendix D: Public Key Cryptography

With public key cryptography, there is a `private key` and a `public key`. The
`private key` is a long string of random characters. A `public key` is
generated from the `private key`. The two keys are called a `key pair`. The
owner of a `key pair` should keep the `private key` a secret, but the
`public key` is designed to be distributed to others and used as described in
the following.

- To encrypt a message or object, the sender uses the `public key` of the
  intended recipient to encrypt the message. Once it is encrypted, only the
  recipient, who holds the matching `private key`, can decipher the message.
- To digitally sign a message or object, the signer uses its `private key` to
  digitally sign the message. The recipient of the message uses the sender’s
  `public key` to verify the signature on the message.

## Appendix E: Troubleshooting Tools

### E.1. Capture an HTTP Trace

- Chrome
  - Open Developer Tools.
  - Click the Network tab.
  - Check the “Preserve Log” option, if not already checked.
  - After capturing a trace, click the Export `HAR` arrow button to save the
    trace in a `.har` file.
- Firefox
  - There is a nice extension called Live HTTP Headers that is handy with
    Firefox.
  - Reproduce the issue.
  - Right-click in the trace window and select “Save All As HAR.”
- Edge
  - Click the Network tab. Make sure the “Preserve log” option is checked.
  - Reproduce the issue.
  - Click the Export HAR button.
- Safari
  - In Safari Preferences, Advanced, turn on “Show Develop Menu in Menu bar.”
  - When viewing a site, use the Develop ➤ Show Web Inspector to view.
  - Click the Network tab.
  - Turn on Preserve Log. Reproduce the issue.
  - Use “Export” to save the HTTP trace to a .har file.

### E.2. View a HAR File

⚠️ Caution Remember that HTTP trace files may contain sensitive information
such as passwords or security tokens. You should remove sensitive content such
as passwords before sharing or uploading trace files, as well as reset
credentials and revoke any tokens, as appropriate.

- Chrome: The Chrome browser supports the ability to import a `.har` file.
  - Open the Chrome Developer Tools Network tab.
  - Drag and drop your .har file onto the tab.
- Google `.har` file analyzer:
  - Google provides a website which can be used to view HTTP Archive (`.har`)
    files:
  - <https://toolbox.googleapps.com/apps/har_analyzer/>
- Fiddler
  - Fiddler, another useful network trace tool, can also be used to view `.har`
    files:
  - <https://docs.telerik.com/fiddler/configure-fiddler/tasks/configurefiddler>

### E.3. Capture a Network Trace

- Fiddler: <https://docs.telerik.com/fiddler>
- Charles Proxy: <www.charlesproxy.com/>

### E.4. View Security Tokens

- <https://jwt.io>: Tool provided by Auth0 for viewing JWT tokens.
- <https://samltool.com>: Tool provided by OneLogin for viewing SAML tokens.
- <https://samltool.io>: Tool provided by Auth0 for viewing SAML tokens.

### E.5. Test APIs

- <https://getpostman.com>: Tool for learning, debugging, and testing API
  calls.
- <https://insomnia.rest/>: Tool for learning, debugging, and testing API calls.

## Appendix F: Privacy Legislation

### F.1. European Union

### F.2. United States

### F.3. Other Countries

### F.4. Notes

## Appendix G: Security Compliance Frameworks

### G.1. General Security Frameworks

### G.2. US Frameworks

### G.3. SOC(Service Organization Control)

## Appendix A
