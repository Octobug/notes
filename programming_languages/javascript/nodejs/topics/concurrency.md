# Concurrency Control

```js
const events = require('events');
const { NamedError } = require('./errors');


class ConcurrencyLimitError extends NamedError { }

class Concurrency {
  /**
   * Init concurrency by given limit
   * @param {Number} limit 
   */
  constructor(limit) {
    if (!Number.isInteger(limit)) {
      throw new Error('limit must be an integer');
    }
    this._limit = limit;
    this._count = 0;
    this._emiter = new events.EventEmitter();
    this._eventHash = 'random_string';
  }

  _inc() {
    if (this._count >= this._limit) {
      throw new ConcurrencyLimitError(
        `reached limit: ${this._limit}`
      );
    }
    this._count++;
  }

  _dec() {
    if (this._count <= 0) {
      this._count = 0;
    } else {
      this._count--;
    }
    this._emiter.emit(this._eventHash);
  }

  run(promise, argv) {
    let asyncFunc = promise;

    if (promise.constructor.name !== 'AsyncFunction') {
      asyncFunc = async (a) => promise(a);
    }

    this._inc();

    return new Promise((resolve, reject) => {
      asyncFunc(argv).then(res => {
        this._dec();
        resolve(res);
      }).catch(err => {
        this._dec();
        reject(err);
      });
    });
  }

  wait() {
    return new Promise((resolve) => {
      const resolveIfAvailable = () => {
        if (this._count < this._limit) {
          resolve();
        }
      };

      this._emiter.on(this._eventHash, () => {
        // do something else
        resolveIfAvailable();
      });
      resolveIfAvailable();
    });
  }
}


module.exports = {
  Concurrency,
  ConcurrencyLimitError,
};

```
