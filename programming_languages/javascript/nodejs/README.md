# Node.js

- [Node.js](#nodejs)
  - [Modules](#modules)
    - [CommonJS vs ESM](#commonjs-vs-esm)
    - [`global` keyword](#global-keyword)
  - [npm](#npm)
    - [npx](#npx)
  - [Error Handling](#error-handling)
    - [Error types](#error-types)
      - [Javascript Errors](#javascript-errors)
      - [System Errors](#system-errors)
      - [User Specified Errors](#user-specified-errors)
      - [Assertion Errors](#assertion-errors)
    - [Uncaught Exceptions](#uncaught-exceptions)
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
  - [Topics](#topics)
  - [References](#references)

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

npm is the standard package manager for Node.js.

- it is an online repository for the publishing of open-source Node.js projects;
- it is a command-line utility for interacting with said repository that aids
  in package installation, version management, and dependency management.
  
### npx

`npx` lets you run code built with Node.js and published through the npm
registry.

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

## Topics

- [Reusing HTTP connection lead to no destroy triggered](https://github.com/nodejs/node/issues/19859)

## References

- [ ] [Node.js Developer](https://roadmap.sh/nodejs)
- ORM
  - [Prisma](https://www.prisma.io/)
- Test
  - [Jest](https://jestjs.io/)
  - [Mocha](https://mochajs.org/)
  - [Sinon.JS](https://sinonjs.org/)
- Validator
  - [Superstruct](https://docs.superstructjs.org/)
