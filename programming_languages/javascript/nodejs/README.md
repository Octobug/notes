# Node.js

- [Node.js](#nodejs)
  - [Data Types](#data-types)
    - [Primitive Types](#primitive-types)
  - [Modules](#modules)
    - [CommonJS vs ESM](#commonjs-vs-esm)
    - [`global` keyword](#global-keyword)
  - [npm](#npm)
    - [npx](#npx)
    - [Creating Packages](#creating-packages)
    - [npm workspaces](#npm-workspaces)
    - [Others](#others)
  - [Error Handling](#error-handling)
    - [Error types](#error-types)
      - [Javascript Errors](#javascript-errors)
      - [System Errors](#system-errors)
      - [User Specified Errors](#user-specified-errors)
      - [Assertion Errors](#assertion-errors)
    - [Uncaught Exceptions](#uncaught-exceptions)
    - [Handling Async Errors](#handling-async-errors)
    - [Using debugger](#using-debugger)
  - [Asynchronous Programming](#asynchronous-programming)
    - [Promises](#promises)
    - [Async/Await](#asyncawait)
    - [Event Emitter](#event-emitter)
    - [Event Loop](#event-loop)
  - [Working with Files](#working-with-files)
    - [`fs` module](#fs-module)
    - [`path` module](#path-module)
    - [`process.cwd()`](#processcwd)
    - [`__dirname`](#__dirname)
    - [`__filename`](#__filename)
    - [Open Source Packages](#open-source-packages)
  - [Command Line Applications](#command-line-applications)
    - [Command line args](#command-line-args)
      - [`process.argv`](#processargv)
      - [Commander.js](#commanderjs)
      - [Environment variables](#environment-variables)
      - [Exiting and exit codes](#exiting-and-exit-codes)
      - [Taking input](#taking-input)
      - [Printing output](#printing-output)
  - [APIs](#apis)
    - [Making API Calls](#making-api-calls)
    - [HTTP Server](#http-server)
    - [Authentication](#authentication)
  - [Keeping Application Running](#keeping-application-running)
    - [Nodemon](#nodemon)
    - [node --watch](#node---watch)
    - [Template Engines](#template-engines)
  - [Working with Databases](#working-with-databases)
    - [Document Databases](#document-databases)
    - [Relational Databases](#relational-databases)
  - [Testing](#testing)
  - [Logging](#logging)
  - [Keepling App Running](#keepling-app-running)
  - [Threads](#threads)
    - [Child Process](#child-process)
    - [Cluster](#cluster)
    - [Worker Threads](#worker-threads)
  - [Streams](#streams)
  - [Advanced Debugging](#advanced-debugging)
    - [Why not to use console.log() for debugging](#why-not-to-use-consolelog-for-debugging)
    - [Memory Leaks](#memory-leaks)
      - [Garbage Collection](#garbage-collection)
    - [node --inspect](#node---inspect)
    - [Using APM (Application Performance Monitoring)](#using-apm-application-performance-monitoring)
  - [Common Built-in Modules](#common-built-in-modules)
  - [Topics](#topics)
  - [References](#references)

## Data Types

### Primitive Types

- `string`
- `number`
- `bigint`
- `boolean`
- `undefined`
- `null`
- [`Symbol`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Symbol)

## Modules

A module is nothing but a JavaScript file.

### CommonJS vs ESM

CommonJS and ES (EcmaScript) are module systems used in Node. CommonJS is the
default module system.

However, a new module system was recently added to NodeJS - ES modules.
CommonJS modules use the `require()` statement for module imports and
`module.exports` for module exports while it’s `import` and `export` for ES.

### `global` keyword

In browsers, the top-level scope is the `global` scope. This means that within
the browser `var` something will define a new global variable.

In Node.js this is different. The top-level scope is not the `global` scope;
`var` something inside a Node.js module will be local to that module.

## npm

`npm` is the standard package manager for Node.js.

- it is an online repository for the publishing of open-source Node.js projects;
- it is a command-line utility for interacting with repository that aids in
  package installation, version management, and dependency management.
  
### npx

`npx` lets you run code built with Node.js and published through the npm
registry.

### Creating Packages

> - <https://www.freecodecamp.org/news/how-to-make-a-beautiful-tiny-npm-package-and-publish-it-2881d4307f78/>
> - <https://snyk.io/blog/best-practices-create-modern-npm-package/>

- Private Packages
- Public Packages

### npm workspaces

> <https://docs.npmjs.com/cli/v10/using-npm/workspaces/>

### Others

- pnpm
- yarn

## Error Handling

The errors in Node.js can be either operation or programmer errors.

> - <https://sematext.com/blog/node-js-error-handling>
> - <https://blog.logrocket.com/error-handling-node-js/>

### Error types

> - <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Error>

#### Javascript Errors

JavaScript Errors are used by JavaScript to inform developers about various
issue in the script being executed. These issues can be syntax error where the
developer/programmer has used the wrong syntax, it can be due to some wrong
user input or some other problem.

JavaScript has **six** types of errors that may occur during the execution of
the script:

- `EvalError`
- `RangeError`
- `ReferenceError`
- `SyntaxError`
- `TypeError`
- `URIError`

#### System Errors

Node.js generates system errors when exceptions occur within its runtime
environment. These usually occur when an application violates an operating
system constraint.

Below are the system errors commonly encountered when writing a Node.js program

- `EACCES` - Permission denied
- `EADDRINUSE` - Address already in use
- `ECONNRESET` - Connection reset by peer
- `EEXIST` - File exists
- `EISDIR` - Is a directory
- `EMFILE` - Too many open files in system
- `ENOENT` - No such file or directory
- `ENOTDIR` - Not a directory
- `ENOTEMPTY` - Directory not empty
- `ENOTFOUND` - DNS lookup failed
- `EPERM` - Operation not permitted
- `EPIPE` - Broken Pipe
- `ETIMEDOUT` - Operation timed out

#### User Specified Errors

> [A Comprehensive Guide To Error Handling In Node.js](https://www.honeybadger.io/blog/errors-nodejs/)

User specified errors can be created by extending the base `Error` object, a
built-in error class. When creating errors in this manner, you should pass a
message string that describes the error. This message can be accessed through
the message property on the object. The Error object also contains a name and a
stack property that indicate the name of the error and the point in the code at
which it is created.

#### Assertion Errors

An `AssertionError` in Node.js is an error that is thrown when the `assert`
module determines that a given expression is not truthy. The `assert` module is
a built-in Node.js module that provides a simple set of assertion tests that
can be used to test the behavior of your code.

### Uncaught Exceptions

When a JavaScript error is not properly handled, an `uncaughtException` is
emitted. These suggest the programmer has made an error, and they should be
treated with the utmost priority.

The correct use of `uncaughtException` is to perform synchronous cleanup of
allocated resources (e.g. file descriptors, handles, etc) before shutting down
the process.

It is not safe to resume normal operation after `uncaughtException` because
system becomes corrupted. The best way is to let the application crash, log the
error and then restart the process automatically using `nodemon` or `pm2`.

### Handling Async Errors

> <https://www.mariokandut.com/handling-errors-in-asynchronous-functions-node-js/>

### Using debugger

Start Node.js with the `inspect` argument to debug:

```sh
node inspect main.js
```

## Asynchronous Programming

- `setTimeout`
- `clearTimeout`
- `setInterval`
- `clearInterval`
- `setImmediate`
- `process.nextTick`
- Callbacks

### Promises

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise>

### Async/Await

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/async_function>

### Event Emitter

> <https://www.digitalocean.com/community/tutorials/using-event-emitters-in-node-js>

In Node.js, an event can be described simply as a string with a corresponding
callback. An event can be “emitted” (or, in other words, the corresponding
callback be called) multiple times or you can choose to only listen for the
first time it is emitted.

### Event Loop

> <https://nodejs.org/en/docs/guides/event-loop-timers-and-nexttick#what-is-the-event-loop>

Node.js event loop vs. v8 event loop:

- <https://stackoverflow.com/a/61458912/7267801>
- <https://gist.github.com/andreybolonin/2413da76f088e2c5ab04df53f07659ea>

## Working with Files

### `fs` module

File System or `fs` module is a built in module in Node that enables
interacting with the file system using JavaScript. All file system operations
have **synchronous**, **callback**, and **promise-based** forms, and are
accessible using both CommonJS syntax and ES6 Modules.

### `path` module

The `path` module provides utilities for working with file and directory paths.

### `process.cwd()`

The `process.cwd()` method returns the current working directory of the Node.js
process.

### `__dirname`

The `__dirname` in a node script returns the path of the folder where the
current JavaScript file resides.

### `__filename`

The `__filename` in Node.js returns the filename of the executed code. It gives
the absolute path of the code file.

### Open Source Packages

- [glob](https://github.com/isaacs/node-glob)
- [Globby](https://github.com/sindresorhus/globby)
- [fs-extra](https://github.com/jprichardson/node-fs-extra)
- [Chokidar](https://github.com/paulmillr/chokidar)

## Command Line Applications

They are also called CLI (Command Line Interface) applications.

### Command line args

#### `process.argv`

`process.argv` is an array of parameters that are sent when you run a Node.js
file or Node.js process.

#### Commander.js

> <https://github.com/tj/commander.js>

Commander is a light-weight, expressive, and powerful command-line framework
for node.js. with Commander.js you can create your own command-line interface
(CLI).

#### Environment variables

- `process.env`: In Node.js, `process.env` is a global variable that is
  injected during runtime. It is a view of the state of the system environment
  variables. When we set an environment variable, it is loaded into
  `process.env` during runtime and can later be accessed.
- `dotenv`: dotenv is a zero-dependency module that loads environment variables
  from a `.env` file into `process.env`. Storing configuration in the
  environment separate from code is based on The
  [Twelve-Factor App methodology](https://12factor.net/config).

#### Exiting and exit codes

`Exiting` is a way of terminating a Node.js process by using node.js `process`
module.

#### Taking input

- `process.stdin`: a standard Readable stream which listens for user input and
  is accessible via the process module. It uses `on()` function to listen for
  input events.
- `readline` module
- third party packages
  - `prompts`: a higher level and user friendly interface built on top of
    Node.js’s inbuilt `Readline` module. It supports different type of prompts
    such as text, password, autocomplete, date, etc. It is an interactive
    module and comes with inbuilt validation support.
  - `Inquirer`: a collection of common interactive command line interfaces for
    taking inputs from user. It is `promise` based and supports chaining series
    of prompt questions together, receiving text input, checkboxes, lists of
    choices and much more.
  - `Enquirer`: same as `Inquirer`

#### Printing output

- `process.stdout`: an inbuilt application programming interface of the
  `process` module which is used to send data out of our program. A Writable
  Stream to `stdout`. It implements a `write()` method.
- `process.stderr`: an inbuilt application programming interface of `process`
  module which is used to returns a stream connected to `stderr`.
- third party packages
  - `Chalk`: a clean and focused library used to do string styling in terminal
    applications.
  - `Figlet`: aims to fully implement the `FIGfont` spec in JavaScript, which
    represents the graphical arrangement of characters representing larger
    characters. It works in the browser and with Node.js.
  - `Cli-Progress`: a package that provides a custom progress bar for CLI
    applications.

## APIs

### Making API Calls

- `http` module: You can make API calls using the `http` module in Node.js.
  - `http.get()` - Make http GET requests.
  - `http.request()` - Similar to `http.get()` but enables sending other types
    of http requests (GET requests inclusive).
- Axios: Axios is a promise-based HTTP Client for node.js and the browser. On
  the server-side it uses the native node.js `http` module, while on the client
  (browser) it uses `XMLHttpRequests`.
- `unfetch`: a tiny 500b fetch “barely-polyfill”
- `Got`: a lighter, human-friendly, and powerful HTTP request library
  explicitly designed to work with Node.js. It supports pagination, RFC
  compliant caching, makes an API request again if it fails, supports cookies
  out of the box, etc.

### HTTP Server

- `http` module
- `Express.js`: a node.js web application framework that provides broad features
  for building web and mobile applications.
- `NestJS`: a progressive Node.js framework for creating efficient and scalable
  server-side applications.
- `Fastify`: a web framework highly focused on providing the best developer
  experience with the least overhead and a powerful plugin architecture,
  inspired by `Hapi` and `Express`.

### Authentication

- JWT, or JSON-Web-Token: an open standard for sharing security information
  between two parties — a client and a server. Each JWT contains encoded JSON
  objects, including a set of claims. JWTs are signed using a cryptographic
  algorithm to ensure that the claims cannot be altered after the token is
  issued.
- `Passport.js`: a authentication middleware for Node.js. It makes implementing
  authentication in express apps really easy and fast. It is extremely flexible
  and modular. It uses "strategies" to support authentication using a username
  and password, Facebook, Twitter, and a lot of other sites.

## Keeping Application Running

### Nodemon

In Node.js, you need to restart the process to make changes take effect. This
adds an extra step to your workflow. You can eliminate this extra step by using
`nodemon` to restart the process automatically.

### node --watch

Since Node.js 18.11.0, you can run Node with the `--watch` flag to reload your
app everytime a file is changed. So you don’t need to use `nodemon` anymore.

### Template Engines

Template engine helps us to create an HTML template with minimal code. Also, it
can inject data into HTML template at client side and produce the final HTML.

- `EJS`: a templating language or engine that allows you to generate HTML markup
  with pure JavaScript. EJS template engine helps to easily embed JavaScript
  into your HTML template.
- `Pug` (formerly called Jade): a JavaScript template engine. It is a
  high-performance template engine heavily influenced by `HAML`.
- `Marko`: a fast and lightweight HTML-based templating engine that compiles
  templates to CommonJS modules and supports streaming, `async` rendering, and
  custom tags. It is HTML re-imagined as a language for building dynamic and
  reactive user interfaces.
- `Nunjucks`
- `Vash`
- `Handlebars`
- `HAML`

## Working with Databases

### Document Databases

A document database is a type of nonrelational database that is designed to
store and query data as JSON-like documents. Document databases make it easier
for developers to store and query data in a database by using the same
document-model format they use in their application code.

The flexible, semistructured, and hierarchical nature of documents and document
databases allows them to evolve with applications' needs.

- `Mongoose`: an Object Data Modeling (ODM) library for MongoDB and Node.js.
  Mongoose provides a straight-forward, schema-based solution to model your
  application data. It includes built-in type casting, validation, query
  building, business logic hooks and more, out of the box.
- `Prisma`: an open source next-generation ORM in the TypeScript ecosystem. It
  offers a dedicated API for relation filters. It provide an abstraction layer
  that makes you more productive compared to writing SQL. Prisma currently
  supports `PostgreSQL`, `MySQL`, `SQL Server`, `SQLite`, `MongoDB` and
  `CockroachDB`.
- `Native Drivers`: Another way to connect to different databases in Node.js is
  to use the official native drivers provided by the database.

### Relational Databases

- `Knex`: a "batteries included" SQL query builder, which designed to be
  flexible, portable, and fun to use.
- `TypeORM`: TypeORM supports both **Active Record** and **Data Mapper**
  patterns, unlike all other JavaScript ORMs currently in existence, which
  means you can write high quality, loosely coupled, scalable, maintainable
  applications the most productive way.
- `Sequelize`: Sequelize is an easy-to-use and promise-based Node.js ORM tool.
  It features solid transaction support, relations, eager and lazy loading,
  read replication and more.
- `Prisma`: Combined with its Data Platform developers gain reliability and
  visibility when working with databases.
- `Native drivers`: NativeDriver is an implementation of the WebDriver API
  which drives the UI of a native application rather than a web application. It
  extends the WebDriver API in a few key places, and re-interprets the existing
  API for native applications.
  - MySQL:
    - `mysql`
    - `mysql2`
  - MariaDB:
    - `mariadb`
  - PostgreSQL:
    - `pg`
  - Microsoft SQL Server:
    - `tedious`
    - `mssql`
  - Oracle:
    - `oracledb`

## Testing

The two most common testing approaches are **unit testing** and
**end-to-end testing**. In the first, we examine small snippets of code, in the
second, we test an entire user flow.

- `Jest`: a JavaScript Testing Framework with a focus on simplicity. It works
  with projects using: Babel, TypeScript, Node, React, Angular, Vue and more!
- `Mocha`: an open source JavaScript test framework running on Nodejs and in
  the browser, making asynchronous testing simple and fun, and it’s a great
  candidate for BDD (Behavior Driven Development).
- `Cypress`: a new front end testing tool built for the modern web. It enables
  you to write faster, easier and more reliable tests.

## Logging

Logging is an essential part of understanding the complete application life
cycle of the Node.js application.

We can much more easily and quickly fix errors by looking at logs throughout
the development process, from creating to debugging to designing new features.

`error`, `warn`, `info`, and `debug` are the four basic logging levels in
Node.js. Logging involves persistently collecting information about an
application’s runtime behaviour.

- `Morgan`: a NodeJS and express.js middleware to log the HTTP request and
  error, simplifying the debugging process. It provides flexibility in defining
  the format of log messages and helps override the output destination for your
  logs.
- `Winston`: designed to be a simple and universal logging library with support
  for multiple transports. A transport is essentially a storage device for your
  logs. Each winston logger can have multiple transports configured at
  different levels. For example, one may want error logs to be stored in a
  persistent remote location (like a database), but all logs output to the
  console or a local file.

## Keepling App Running

- `pm2`: <https://pm2.keymetrics.io/>
- `forever`: <https://github.com/foreversd/forever>
- `nohup`: the `nohup` shell command, short for "no hang up"

## Threads

> <https://alvinlal.netlify.app/blog/single-thread-vs-child-process-vs-worker-threads-vs-cluster-in-nodejs/>

Node.js is a single-threaded language and gives us ways to work parallelly to
our main process. Taking note of nowadays multicore system single threading is
very memory efficient.

### Child Process

The `child_process` module gives the node the ability to run the child process,
established through IPC (inter-process communication) by accessing operating
system commands.

Three main methods inside this module are:

- `child_process.spawn()`
- `child_process.fork()`
- `child_process.exec()`

### Cluster

The `cluster` module allows you to easily create child processes that each runs
simultaneously on their own single thread, to handle workloads among their
application threads.

### Worker Threads

Worker thread is a continuous parallel thread that runs and accepts messages
until it is explicitly closed or terminated. With worker threads, we can
achieve a much efficient application without creating a deadlock situation.

## Streams

Streams are a type of data handling methods and are used to read, write or
transform chunks of data piece by piece **without keeping it in memory** all at
once. There are four types of streams in Node.js:

- **Readable**: streams from which data can be read.
- **Writable**: streams to which we can write data.
- **Duplex**: streams that are both Readable and Writable.
- **Transform**: streams that can modify or transform the data as it is written
  and read.

Multiple streams can be chained together using `pipe()` method.

## Advanced Debugging

### Why not to use console.log() for debugging

Using `console.log` to debug the code generally dives into an infinite loop of
“stopping the app and adding a console.log, and start the app again”
operations.

Besides slowing down the development of the app, it also makes the writing
dirty and creates unnecessary code.

### Memory Leaks

A Node.js memory leak is an orphan block of memory on the Heap that is no
longer used by your app because it has not been released by the garbage
collector. It’s a useless block of memory.

#### Garbage Collection

> - <https://javascript.info/garbage-collection>
> - <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Memory_Management>

Memory management in JavaScript is performed automatically.
The main concept of memory management in JavaScript is reachability.

### node --inspect

> <https://medium.com/@paul_irish/debugging-node-js-nightlies-with-chrome-devtools-7c4a1b95ae27>

### Using APM (Application Performance Monitoring)

> <https://stackify.com/node-js-debugging-tips/>

In production, one of your tools would be to login to your remote server to
view the console logs, just as you would on local. But this can be a tedious
approach. Luckily, there are tools out there that perform what is called
**log aggregation**, such as **Stackify**.

These tools send your logs from your running application into a single
location. They often come with high-powered search and query utilities so that
you can easily parse your logs and visualize them.

## Common Built-in Modules

- `assert`
- `child_processes`
- `cluster`
- `console`
- `crypto`
- `events`
- `fs`
- `http`
- `net`
- `os`
- `path`
- `perf_hooks`
- `process`
- `querystring`
- `readline`
- `string_decoder`
- `tls`
- `url`
- `util`
- `Buffer`
- `DNS`
- `REPL`

## Topics

- [Reusing HTTP connection lead to no destroy triggered](https://github.com/nodejs/node/issues/19859)

## References

- [x] [Node.js Developer](https://roadmap.sh/nodejs)
