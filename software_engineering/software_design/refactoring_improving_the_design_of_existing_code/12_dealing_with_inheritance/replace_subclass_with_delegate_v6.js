/* eslint-disable no-unused-vars */
/* eslint-disable no-prototype-builtins */
class Booking {
  constructor(show, date) {
    this._show = show;
    this._date = date;
  }

  get hasTalkback() {
    return (this._premiumDelegate)
      ? this._premiumDelegate.hasTalkback
      : this._show.hasOwnProperty('talkback') && !this.isPeakDay;
  }

  get basePrice() {
    return (this._premiumDelegate)
      ? this._premiumDelegate.basePrice
      : this._privateBasePrice;
  }

  _bePremium(extras) {
    this._premiumDelegate = new PremiumBookingDelegate(this, extras);
  }

  get _privateBasePrice() {
    let result = this._show.price;
    if (this.isPeakDay) {
      result += Math.round(result * 0.15);
    }
    return result;
  }
}

class PremiumBooking extends Booking {
  constructor(show, date, extras) {
    super(show, date);
    this._extras = extras;
  }

  get hasDinner() {
    return this._extras.hasOwnProperty('dinner') && !this.isPeakDay;
  }
}

class PremiumBookingDelegate {
  constructor(hostBooking, extras) {
    this._host = hostBooking;
    this._extras = extras;
  }

  get hasTalkback() {
    return this._host._show.hasOwnProperty('talkback');
  }

  get basePrice() {
    return Math.round(this._host._privateBasePrice + this._extras.premiumFee);
  }
}

function createBooking(show, date) {
  return new Booking(show, date);
}

function createPremiumBooking(show, date, extras) {
  const result = new PremiumBooking(show, date, extras);
  result._bePremium(extras);
  return result;
}

const show = {};
const date = {};
const extras = {};
const aBooking = createBooking(show, date);
const aPremiumBooking = createPremiumBooking(show, date, extras);
