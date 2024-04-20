function version1() {
  class Order {
    constructor(data) {
      this.priority = data.priority;
    }
  }

  const orders = [new Order({ priority: 'high' })];
  const highPriorityCount = orders.filter(
    o => 'high' === o.priority || 'rush' === o.priority
  ).length;
}

function version2() {
  class Order {
    constructor(data) {
      this.priority = data.priority;
    }

    get priority() { return this._priority; }
    set priority(aString) { this._priority = aString; }
  }

  const orders = [new Order({ priority: 'high' })];
  const highPriorityCount = orders.filter(
    o => 'high' === o.priority || 'rush' === o.priority
  ).length;
}

function version3() {
  class Priority {
    constructor(value) { this._value = value; }
    toString() { return this._value; }
  }

  class Order {
    constructor(data) {
      this.priority = data.priority;
    }

    get priority() { return this._priority.toString(); }
    set priority(aString) { this._priority = new Priority(aString); }
  }

  const orders = [new Order({ priority: 'high' })];
  const highPriorityCount = orders.filter(
    o => 'high' === o.priority || 'rush' === o.priority
  ).length;
}

function version4() {
  class Priority {
    constructor(value) { this._value = value; }
    toString() { return this._value; }
  }

  class Order {
    constructor(data) {
      this.priority = data.priority;
    }

    get priorityString() { return this._priority.toString(); }
    set priority(aString) { this._priority = new Priority(aString); }
  }

  const orders = [new Order({ priority: 'high' })];
  const highPriorityCount = orders.filter(
    o => 'high' === o.priorityString || 'rush' === o.priorityString
  ).length;
}

function version5() {
  class Priority {
    constructor(value) { this._value = value; }
    toString() { return this._value; }
  }

  class Order {
    constructor(data) {
      this.priority = data.priority;
    }

    get priorityString() { return this._priority.toString(); }
    get priority() { return this.priority; }
    set priority(aString) { this._priority = new Priority(aString); }
  }

  const orders = [new Order({ priority: 'high' })];
  const highPriorityCount = orders.filter(
    o => 'high' === o.priorityString || 'rush' === o.priorityString
  ).length;
}

function version6() {
  class Priority {
    constructor(value) {
      if (value instanceof Priority) {
        return value;
      }

      if (Priority.legalValues().includes(value)) {
        this._value = value;
      } else {
        throw new Error(`<${value}> is invalid for Priority`);
      }
    }

    static legalValues() { return ['low', 'normal', 'high', 'rush']; }

    toString() { return this._value; }
    get _index() {
      return Priority.legalValues().findIndex(s => s === this._value);
    }

    equals(other) { return this._index === other._index; }
    higherThan(other) { return this._index > other._index; }
    lowerThan(other) { return this._index < other._index; }
  }

  class Order {
    constructor(data) {
      this.priority = data.priority;
    }

    get priorityString() { return this._priority.toString(); }
    get priority() { return this.priority; }
    set priority(aString) { this._priority = new Priority(aString); }
  }

  const orders = [new Order({ priority: 'high' })];
  const highPriorityCount = orders.filter(
    o => o.priority.higherThan(new Priority('normal'))
  ).length;
}
