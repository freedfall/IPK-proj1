# IPKCPC Project Documentation

### Content structuring

  - [Introduction](#introduction)
  - [Project Overview](#project-overview)
  - [Theory and Concepts](#project-overview)
  - [Usage](#usage)
  - [Code structure](#code-structure)
     - [TCP client](#tcp-client)
     - [UDP client](#udp-client)
     - [Main Logic](#main-logic)
  - [Testing and validation](#testing-and-validation)
  - [Bibliography](#bibliography)

# Introduction

This document provides the documentation for the IPKCPC project, a simple command-line application that supports both TCP and UDP communication with a remote server.

# Project Overview

### The IPKCPC project is divided into three main components:

- TCP Client

- UDP Client

- Main Logic

These components work together to establish and maintain communication with a remote server using either the TCP or UDP protocol, depending on the user's choice.

# Theory and Concepts

The project is based on the TCP and UDP protocols, which are two of the most commonly used transport layer protocols in the Internet Protocol Suite. 

TCP provides reliable, connection-oriented communication, while UDP provides fast, connectionless communication. 

Both protocols are used for different purposes and have their advantages and disadvantages.

# Usage

### How to Use

In order to utilize the IPKCPC Client, you should be aware of the following information:

- The hostname or IP address of the remote server
- The port number that the server is listening on
- The communication method (TCP or UDP)

Execute the client by entering the command below:

    ./ipkcpc -h <host> -p <port> -m <mode>

Substitute <host> with the hostname or IP address of the server, <port> with the port number the server is using, and <mode> with either tcp or udp, based on the preferred communication protocol.

For instance, to establish a connection with a server at example.com on port 1234 utilizing TCP:

    ./ipkcpc -h example.com -p 1234 -m tcp

After connecting the client, you can input commands or expressions that will be transmitted to the server. Responses from the server will appear on your screen. To close the client, type the command BYE.

# Code Structure

### TCP Client

The TCP Client component is responsible for creating, managing, and running the TCP client to interact with the server. The following key functions are provided:

    create_TCPClient(): Creates a new TCPClient instance.

    destroy_TCPClient(): Cleans up and frees a TCPClient instance.

    run_TCPClient(): Runs the TCP client, connecting to the server, sending messages, and receiving responses.

### UDP Client

The UDP Client component is responsible for creating, managing, and running the UDP client to interact with the server. The following key functions are provided:

    create_UDPClient(): Creates a new UDPClient instance.

    destroy_UDPClient(): Cleans up and frees a UDPClient instance.

    run_UDPClient(): Runs the UDP client, sending messages to the server and receiving responses.


### Main Logic

The Main Logic component acts as the entry point for the application and is responsible for processing command line arguments and executing the appropriate client based on the provided mode (TCP or UDP). The following key functions are provided:

    print_usage(): Prints usage information for the application.

    main(): Entry point for the application, processes command line arguments, and runs the appropriate client (TCP or UDP).

# Testing and Validation

The IPKCPC project has been tested using the following steps:

### Unit testing for individual components (TCP Client, UDP Client).

Test 1: connecting to a remote server with tcp client (textual variant):

    $ ./ipkcpc -h 147.229.176.19 -p 10002 -m tcp
    HELLO
    HELLO
    BYE
    BYE

Test 2: functionality of calculator, receiving and sending with tcp connection:

    $ ./ipkcpc -h 147.229.176.19 -p 10002 -m tcp
    HELLO
    HELLO
    SOLVE -10 * 20
    RESULT -200
    SOLVE 2 - 1972932
    RESULT -1972930
    SOLVE 200 / 15
    RESULT 13.333333333333
    BYE
    BYE

Test 3: interrupt signal C-c (Ctrl+C) handling on tcp:

    $ ./ipkcpc -h 147.229.176.19 -p 10002 -m tcp
    HELLO
    HELLO
    ^C
    BYE
    BYE 

Test 4: functionality of udp connection:

    $ ./ipkcpc -h 147.229.176.19 -p 10002 -m udp
    (+ 1 2)
    OK:3
    (* 7 4)
    OK:28
    (/ 10209 4)
    OK:2552.25

Test 5: wrong input (tcp):

    $ ./ipkcpc -h 147.229.176.19 -p 10002 -m tcp
    HI
    BYE

Test 6: wrong input (udp):

    $ ./ipkcpc -h 147.229.176.19 -p 10002 -m udp
    HI
    ERR:Invalid expression: h j
    hello
    ERR:Invalid expression: h e l l o

Integration testing to ensure proper interaction between components.

The application has been proven to work correctly and reliably with both the TCP and UDP protocols.

# Bibliography

Stevens, W.R. and Fenner, B. UNIX Network Programming: Networking APIs: Sockets and XTI. Prentice Hall, 1994. ISBN-10: 013490012X

Tanenbaum, A.S. and Wetherall, D.J. Computer Networks. 5th ed. Prentice Hall, 2011. ISBN-10: 0132126958

Stack Overflow (Various threads for specific issues and examples) [online]. [cit. 2023-03-20]. Available at: https://stackoverflow.com/