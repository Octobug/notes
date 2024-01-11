# Chapter 2: Identity for the Modern World

- [Chapter 2: Identity for the Modern World](#chapter-2-identity-for-the-modern-world)
  - [Authentication](#authentication)
  - [Authorization](#authorization)
  - [Identity Management](#identity-management)
  - [Single Sign On and Modern Identity Management Go Hand in Hand](#single-sign-on-and-modern-identity-management-go-hand-in-hand)

Modern identity management is concerned with **authentication**,
**authorization**, and **management** of users within a system or organization.

## Authentication

Authentication deals with verifying user identity.

Since in an SSO implementation there is a single source of identity, IT
administrators can have a central system for enforcing password requirements,
spotting authentication anomalies, and so on.

## Authorization

Authorization deals with ensuring that users have the correct levels of access
within a system. Once a user is successfully authenticated, they are given
certain permissions for what they can do within an application.

Ensuring the right level of access is very important and is difficult to do in a
non-SSO implementation. Different applications present different levels of
granularity when it comes to user permissions which makes authorization more
difficult.

Single Sign On aims to solve the authorization component of modern identity by
providing a centralized source of truth for each individual user. Once a user is
authenticated, the identity provider can send each application the users
identity and permissions for each application.

## Identity Management

Identity management is concerned with creating, updating, and deleting users as
they move throughout an organization.

In an SSO environment, the employee is provided with a set of credentials that
are mapped to a user account in a centralized database.

When the user leaves, their access to all of the organization resources can be
disabled easily.

## Single Sign On and Modern Identity Management Go Hand in Hand

- Managing access to incoming and outgoing employees can be very challenging
  without a centralized locatoin for user identity.
- Through identity federation, an IT admin can provision and deprovision user
  accounts once.
- Single Sign On can solve an organization's identity and user management woes.
