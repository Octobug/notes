class EventEmitter {
  eventMap = {};

  /**
   * @param {string} eventName
   * @param {Function} callback
   * @return {Object}
   */
  subscribe(eventName, callback) {
    this.eventMap[eventName] = this.eventMap[eventName] || [];
    const cbs = this.eventMap[eventName];
    cbs.push(callback);

    return {
      unsubscribe: () => {
        this.eventMap[eventName] = this.eventMap[eventName].filter(
          cb => cb != callback
        );
      }
    };
  }

  /**
   * @param {string} eventName
   * @param {Array} args
   * @return {Array}
   */
  emit(eventName, args = []) {
    const cbs = this.eventMap[eventName] || [];
    return cbs.map(cb => cb(...args));
  }
}

function main() {
  const emitter = new EventEmitter();

  // Subscribe to the onClick event with onClickCallback
  function onClickCallback() { return 99; }
  const sub = emitter.subscribe('onClick', onClickCallback);

  console.log(emitter.emit('onClick')); // [99]
  console.log(sub.unsubscribe()); // undefined
  console.log(emitter.emit('onClick')); // []
}

main();
