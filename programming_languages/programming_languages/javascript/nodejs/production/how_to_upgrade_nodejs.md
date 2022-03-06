# How to upgrade Node.js and dependencies. Results.

> <https://dev.to/animir/how-to-upgrade-node-js-and-dependencies-results-2i2c>

## How-to

### Check your dependencies

Most of these are optional.

#### Remove unused dependencies

Tools:

- [depcheck](https://github.com/depcheck/depcheck)

#### Update dependencies for your Node.js version

Set `engines` section of `package.json`

#### Update vulnerable dependencies

`npm audit`

#### Update dependencies to the latest version

#### Make some strategic choices

Set `resolutions` section of `package.json`: [NPM Force Resolutions](https://github.com/rogeriochaves/npm-force-resolutions#readme)

### Give it time

⚠️ I don't think this is necessary or it would work because once you use some
of the new features from new Node engine, the staging might just go well but the
production would be broken if the features are incompatible between 2 Node
engine versions.

## Comparing the performance of Node.js 8 and Node.js 12

### Weekly SLA (Service Level Agreement)

### GC (Garbage Collector) pause time

### GC pause frequency

### Memory usage

### Maximum CPU time per tick

If you don't know what is tick in Node.js, you may read about
[event loop and ticks here](https://nodejs.org/en/docs/guides/event-loop-timers-and-nexttick/)
