# Conventional Changelog

> <https://github.com/conventional-changelog>

- [Conventional Changelog](https://github.com/conventional-changelog/conventional-changelog)
- [Standard Version](https://github.com/conventional-changelog/standard-version)

## Configuaration

### `.versionrc.js` Example

```js
// https://github.com/conventional-changelog/conventional-changelog-config-spec/tree/master/versions/2.1.0

module.exports = {
  types: [
    { type: "feat", "section": "Features" },
    { type: "fix", "section": "Bug Fixes" },
    { type: "test", "section": "Tests", "hidden": true },
    { type: "build", "section": "Build System", "hidden": true },
    { type: "ci", "hidden": true }
  ],
  issuePrefixes: ['#'],
};
```
