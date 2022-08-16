function version1() {
  class TrackingInformation {
    get shippingCompany() { return this._shippingCompany; }
    set shippingCompany(arg) { this._shippingCompany = arg; }

    get trackingNumber() { return this._trackingNumber; }
    set trackingNumber(arg) { this._trackingNumber = arg; }

    get display() {
      return `${this.shippingCompany}: ${this.trackingNumber}`;
    }
  }

  class Shipment {
    get trackingInfo() {
      return this._trackingInformation.display;
    }

    get trackingInformation() { return this._trackingInformation; }
    set trackingInformation(aTrackingInformation) {
      this._trackingInformation = aTrackingInformation;
    }
  }

  const request = { vendor: 'vendor' };
  const aShipment = new Shipment();
  aShipment.trackingInformation.shippingCompany = request.vendor;
}

function version2() {
  class TrackingInformation {
    get shippingCompany() { return this._shippingCompany; }
    set shippingCompany(arg) { this._shippingCompany = arg; }

    get trackingNumber() { return this._trackingNumber; }
    set trackingNumber(arg) { this._trackingNumber = arg; }

    get display() {
      return `${this.shippingCompany}: ${this.trackingNumber}`;
    }
  }

  class Shipment {
    get trackingInfo() {
      return this._trackingInformation.display;
    }

    get trackingInformation() { return this._trackingInformation; }
    set trackingInformation(aTrackingInformation) {
      this._trackingInformation = aTrackingInformation;
    }

    get shippingCompany() { return this._trackingInformation.shippingCompany; }
    set shippingCompany(arg) {
      this._trackingInformation.shippingCompany = arg;
    }

    get trackingNumber() { return this._trackingInformation.trackingNumber; }
    set trackingNumber(arg) { this._trackingInformation.trackingNumber = arg; }
  }

  const request = { vendor: 'vendor' };
  const aShipment = new Shipment();
  aShipment.shippingCompany = request.vendor;
}

function version3() {
  class Shipment {
    get trackingInfo() {
      return `${this.shippingCompany}: ${this.trackingNumber}`;
    }

    get shippingCompany() { return this._shippingCompany; }
    set shippingCompany(arg) {
      this._shippingCompany = arg;
    }

    get trackingNumber() { return this._trackingNumber; }
    set trackingNumber(arg) { this._trackingNumber = arg; }
  }

  const request = { vendor: 'vendor' };
  const aShipment = new Shipment();
  aShipment.shippingCompany = request.vendor;
}
