# Upgrade Node.js

- [Upgrade Node.js](#upgrade-nodejs)
  - [Prerequisite Knowledge](#prerequisite-knowledge)
  - [Check List](#check-list)
  - [How to upgrade Node.js and dependencies. Results.](#how-to-upgrade-nodejs-and-dependencies-results)
    - [How-to](#how-to)
      - [Check your dependencies](#check-your-dependencies)
        - [Remove unused dependencies](#remove-unused-dependencies)
        - [Update dependencies for your Node.js version](#update-dependencies-for-your-nodejs-version)
        - [Update vulnerable dependencies](#update-vulnerable-dependencies)
        - [Update dependencies to the latest version](#update-dependencies-to-the-latest-version)
        - [Make some strategic choices](#make-some-strategic-choices)
      - [Give it time](#give-it-time)
    - [Comparing the performance of Node.js 8 and Node.js 12](#comparing-the-performance-of-nodejs-8-and-nodejs-12)
      - [Weekly SLA (Service Level Agreement)](#weekly-sla-service-level-agreement)
      - [GC (Garbage Collector) pause time](#gc-garbage-collector-pause-time)
      - [GC pause frequency](#gc-pause-frequency)
      - [Memory usage](#memory-usage)
      - [Maximum CPU time per tick](#maximum-cpu-time-per-tick)

## Prerequisite Knowledge

- [x] [Node.js Releases](https://nodejs.org/en/about/releases/): "***Production
  applications should only use Active LTS or Maintenance LTS releases***."
- [x] [node.green](https://node.green/): ***Node.js ECMAScript compatibility
  tables.***
- [x] [Update Now! Node.js 8 is Not Supported from 2020](https://blog.risingstack.com/update-nodejs-8-end-of-life-no-support/):
  "***Node.js versions are mostly backward compatible.***"

## Check List

- Only adopt LTS versions.
  - **Important** ‼️ Always pick the latest minor version because it has the most non-breaking-change features and fixes.
  - e.g, You're upgrading from `16.16.0` to `18`, and the newest v18 is `18.18.1`, then you should pick `18.18.1`.
- Do NOT change any version of any dependencies during upgrading, unless any
  dependencies require that.
- Different environments should use exactly the same version of Node.js
  - When upgrading, adopt the new version in this order:
    `development` -> `staging` -> `production`
  - Ideally, there should not be any difference of the code base between different
    environments.
- For big projects, conservatively upgrade to a consecutive LTS version.
- For small projects with good test coverage, try to upgrade to the latest LTS
  if you're confident with it.
  - A consecutive LTS version is OK as well.
- Environments:
  - `Development`:
    1. Switch to the desired Node.js version.
    2. `npm ci`
    3. `npm test`, `npm build`, etc.
  - `Staging`:
    1. Switch to the desired Node.js version.
    2. `npm ci --production`
  - `Production`:
    1. Switch to the desired Node.js version.
    2. `npm ci --production`
  - Run all automated tests.
  - Do smoke testing for important features.

## How to upgrade Node.js and dependencies. Results.

> <https://dev.to/animir/how-to-upgrade-node-js-and-dependencies-results-2i2c>

### How-to

#### Check your dependencies

Most of these are optional.

##### Remove unused dependencies

Tools:

- [depcheck](https://github.com/depcheck/depcheck)

##### Update dependencies for your Node.js version

Set `engines` section of `package.json`

##### Update vulnerable dependencies

`npm audit`

##### Update dependencies to the latest version

##### Make some strategic choices

Set `resolutions` section of `package.json`: [NPM Force Resolutions](https://github.com/rogeriochaves/npm-force-resolutions#readme)

#### Give it time

⚠️ I don't think this is necessary or it would work because once you use some
of the new features from the new version Node engine, the staging might just go
well but the production would be broken if the features are incompatible
between 2 Node engine versions.

### Comparing the performance of Node.js 8 and Node.js 12

#### Weekly SLA (Service Level Agreement)

#### GC (Garbage Collector) pause time

#### GC pause frequency

#### Memory usage

#### Maximum CPU time per tick

If you don't know what is tick in Node.js, you may read about
[event loop and ticks here](https://nodejs.org/en/docs/guides/event-loop-timers-and-nexttick/)
