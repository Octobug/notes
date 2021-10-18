# Chapter 1. Introduction

## 1.1 Introduction

### Network application: client and server.

![Network application: client and server](images/1_1.png)

### Server handling multiple clients at the same time.

![Server handling multiple clients at the same time](images/1_2.png)

### Client and server on the same Ethernet communicating using TCP.

![Client and server on the same Ethernet communicating using TCP](images/1_3.png)

The actual flow of information between the client and server goes down the
protocol stack on one side, across the network, and up the protocol stack on the
other side. And the client and server are typically user processes, while the
TCP and IP protocols are normally part of the protocol stack within the kernel.

### Client and server on different LANs connected through a WAN.

![Client and server on different LANs connected through a WAN](images/1_4.png)

*The largest WAN today is the Internet.*

## 1.2 A Simple Daytime Client

> progress
