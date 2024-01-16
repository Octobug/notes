# Chapter 1: The Hydra of Modern Identity

- [Chapter 1: The Hydra of Modern Identity](#chapter-1-the-hydra-of-modern-identity)
  - [Identity Challenges](#identity-challenges)
    - [Who Are Your Users? And Will They Authenticate?](#who-are-your-users-and-will-they-authenticate)
    - [Level of Authentication Strength](#level-of-authentication-strength)
    - [Simplifying Access for Users](#simplifying-access-for-users)
    - [Migrating Users from Legacy Applications](#migrating-users-from-legacy-applications)
    - [Regulatory Requirements](#regulatory-requirements)
    - [User Experience Constraints](#user-experience-constraints)
  - [Objective](#objective)
  - [Sample Application](#sample-application)
  - [Design Questions](#design-questions)

## Identity Challenges

There isn't a master solution we can provide that fits every use case.

### Who Are Your Users? And Will They Authenticate?

- Social logins:
  - Apple
  - Google
- Single sign-on, enterprise federation, or enterprise login

### Level of Authentication Strength

Applications need to accommodate for additional threat vectors, such as
authentication tokens being lost or stolen, credentials being breached, and
scripts that mimic user activity in order to brute-dorce their access into user
accounts.

### Simplifying Access for Users

Single sign-on is considered great security hygiene as it offers a single place
to control authentication policy, reduces the number of passwords that users
have to remember.

### Migrating Users from Legacy Applications

This involves

- migrating existing users along with their credentials
- merging duplicate users in a secure manner
- ensuring uptime for the existing applications during the migration
- migrating some apps while ensuring other systems can stay in place

### Regulatory Requirements

- GDPR (General Data Protection Regulation) in the European Union
- California’s CCPA (California Consumer Privacy Act)
- ...

### User Experience Constraints

## Objective

- OAuth2
- OIDC
- SAML 2

An identity management solution can

- simplify overall architecture
- allow your application to delegate some identity-related responsibilities to
  other components
- provide a single view of the user and unify access control to simplify access
  issues
- provide critical auditing capabilites
- ...

## Sample Application

## Design Questions

- Who are your users: employees, consumers, or a business?
- How will users log in? Is there an existing account available to them that
  they would like to reuse?
- Can your application be used anonymously or is authentication needed?
- What kind of delivery – Web or native – does your application intend to
  provide?
- Will your application need to call any APIs? If so, who owns the data that
  your application will retrieve?
- How will your application interact with APIs, both public APIs and your
  trusted subsystems?
- How sensitive is the data that your application handles?
- What access control requirements are needed?
- How long should a user stay logged in?
- Is there more than one application in your system? If so, will users benefit
  from single sign-on? (Don’t forget a support forum!)
- What should happen when users log out?
- Are there any compliance requirements associated with this data?
