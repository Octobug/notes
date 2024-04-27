# Distributed Locks with Redis

> <https://redis.io/docs/reference/patterns/distributed-locks/>

```js
const KEY = 'hname';

const locker = {
  /**
   * @param {String} field resource that should be accessed by one only process
   * @param {String} processName process name
   * @returns {Number} 1 if succeeded else 0
   */
  trySetFieldLock: async (field, processName) => {
    // hset is atomic
    return await redis.hsetnxAsync(KEY, field, processName);
  },

  getFieldLock: async (field) => {
    return await redis.hgetAsync(KEY, field);
  },

  releaseFieldLock: async (field) => {
    return await redis.hdelAsync(KEY, field);
  },

  /**
   * call this function on process startup
   * @param {String} processName 
   * @returns 
   */
  clearFieldsLocksByProc: async (processName) => {
    const locks = await redis.hgetallAsync(KEY);
    if (!locks) {
      return;
    }

    for (const [field, procName] of Object.entries(locks)) {
      if (procName !== processName) {
        delete locks[field];
      }
    }

    const locksToRelease = Object.keys(locks);

    if (locksToRelease.length === 0) {
      return;
    }
    return await redis.hdelAsync(KEY, locksToRelease);
  },
};
```
