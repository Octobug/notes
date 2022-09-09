/* eslint-disable no-unused-vars */
const aDocument = [];
const LocalDate = {};
const catalog = {};

function version1() {
  class CatalogItem {
    constructor(id, title, tags) {
      this._id = id;
      this._title = title;
      this._tags = tags;
    }

    get id() { return this._id; }
    get title() { return this._title; }
    hasTag(arg) { return this._tags.includes(arg); }
  }

  const ChronoUnit = {};
  class Scroll extends CatalogItem {
    constructor(id, title, tags, dateLastCleaned) {
      super(id, title, tags);
      this._lastCleaned = dateLastCleaned;
    }

    needsCleaning(targetDate) {
      const threshold = this.hasTag('revered') ? 700 : 1500;
      return this.daysSinceLastCleaning(targetDate) > threshold;
    }
    daysSinceLastCleaning(targetDate) {
      return this._lastCleaned.until(targetDate, ChronoUnit.DAYS);
    }
  }

  const scrolls = aDocument
    .map(record => new Scroll(
      record.id,
      record.catalogData.title,
      record.catalogData.tags,
      LocalDate.parse(record.lastCleaned)));
}

function version2() {
  class CatalogItem {
    constructor(id, title, tags) {
      this._id = id;
      this._title = title;
      this._tags = tags;
    }

    get id() { return this._id; }
    get title() { return this._title; }
    hasTag(arg) { return this._tags.includes(arg); }
  }

  const ChronoUnit = {};
  class Scroll {
    constructor(id, title, tags, dateLastCleaned) {
      this._catalogItem = new CatalogItem(id, title, tags);
      this._lastCleaned = dateLastCleaned;
    }

    get id() { return this._catalogItem.id; }
    get title() { return this._catalogItem.title; }
    hasTag(aString) { return this._catalogItem.hasTag(aString); }

    needsCleaning(targetDate) {
      const threshold = this.hasTag('revered') ? 700 : 1500;
      return this.daysSinceLastCleaning(targetDate) > threshold;
    }
    daysSinceLastCleaning(targetDate) {
      return this._lastCleaned.until(targetDate, ChronoUnit.DAYS);
    }
  }

  const scrolls = aDocument
    .map(record => new Scroll(
      record.id,
      record.catalogData.title,
      record.catalogData.tags,
      LocalDate.parse(record.lastCleaned)));
}

function version3() {
  class CatalogItem {
    constructor(id, title, tags) {
      this._id = id;
      this._title = title;
      this._tags = tags;
    }

    get id() { return this._id; }
    get title() { return this._title; }
    hasTag(arg) { return this._tags.includes(arg); }
  }

  const ChronoUnit = {};
  class Scroll {
    constructor(id, title, tags, dateLastCleaned, catalogID, catalog) {
      this._id = id;
      this._catalogItem = catalog.get(catalogID);
      this._lastCleaned = dateLastCleaned;
    }

    get id() { return this._id; }
    get title() { return this._catalogItem.title; }
    hasTag(aString) { return this._catalogItem.hasTag(aString); }

    needsCleaning(targetDate) {
      const threshold = this.hasTag('revered') ? 700 : 1500;
      return this.daysSinceLastCleaning(targetDate) > threshold;
    }
    daysSinceLastCleaning(targetDate) {
      return this._lastCleaned.until(targetDate, ChronoUnit.DAYS);
    }
  }

  const scrolls = aDocument
    .map(record => new Scroll(
      record.id,
      record.catalogData.title,
      record.catalogData.tags,
      LocalDate.parse(record.lastCleaned),
      record.catalogData.id,
      catalog));
}

function version4() {
  class CatalogItem {
    constructor(id, title, tags) {
      this._id = id;
      this._title = title;
      this._tags = tags;
    }

    get id() { return this._id; }
    get title() { return this._title; }
    hasTag(arg) { return this._tags.includes(arg); }
  }

  const ChronoUnit = {};
  class Scroll {
    constructor(id, dateLastCleaned, catalogID, catalog) {
      this._id = id;
      this._catalogItem = catalog.get(catalogID);
      this._lastCleaned = dateLastCleaned;
    }

    get id() { return this._id; }
    get title() { return this._catalogItem.title; }
    hasTag(aString) { return this._catalogItem.hasTag(aString); }

    needsCleaning(targetDate) {
      const threshold = this.hasTag('revered') ? 700 : 1500;
      return this.daysSinceLastCleaning(targetDate) > threshold;
    }
    daysSinceLastCleaning(targetDate) {
      return this._lastCleaned.until(targetDate, ChronoUnit.DAYS);
    }
  }

  const scrolls = aDocument
    .map(record => new Scroll(
      record.id,
      LocalDate.parse(record.lastCleaned),
      record.catalogData.id,
      catalog));
}
