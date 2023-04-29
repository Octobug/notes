# Upgrade Node.js

## Prerequisite Knowledge

- [x] [Node.js Releases](https://nodejs.org/en/about/releases/): "***Production
  applications should only use Active LTS or Maintenance LTS releases***."
- [x] [node.green](https://node.green/): ***Node.js ECMAScript compatibility
  tables.***
- [x] [Update Now! Node.js 8 is Not Supported from 2020](https://blog.risingstack.com/update-nodejs-8-end-of-life-no-support/):
  "***Node.js versions are mostly backward compatible.***"

## Check List

- Only adopt LTS versions.
- Do NOT change any version of any dependencies during upgrading, unless any
  dependencies require that.
- Different environments should use exactly the same version of Node.js
  - When upgrading, adopt the new version in this order:
    `development` -> `staging` -> `production`
  - There should not be any difference of the code base between different
    environments.
- For huge project, conservatively upgrade to a consecutive LTS version.
- For small project with good test coverage, try to upgrade to the active LTS
  if you're confident with it.
  A consecutive LTS version is OK as well.
- Environments:
  - `Development`:
    1. Switch to the desired Node.js version.
    2. `npm ci`
    3. `npm test`, `npm build`, etc.
  - `Staging`:
    1. Switch to the desired Node.js version.
    2. `npm ci --production`
    3. Make sure that all features work fine.
  - `Production`:
    1. Switch to the desired Node.js version.
    2. `npm ci --production`
