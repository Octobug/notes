# Node.js

- [Node.js](#nodejs)
  - [Modules](#modules)
    - [CommonJS vs ESM](#commonjs-vs-esm)
    - [`global` keyword](#global-keyword)
  - [npm](#npm)
    - [npx](#npx)
  - [Error Handling](#error-handling)
    - [Error types](#error-types)
    - [Uncaught Exceptions](#uncaught-exceptions)
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

>>>>> progress

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
