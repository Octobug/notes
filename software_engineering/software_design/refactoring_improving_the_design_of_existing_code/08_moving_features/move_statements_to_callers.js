function version1() {
  function renderPerson(outStream, person) {
    outStream.write(`<p>${person.name}</p>\n`);
    renderPhoto(outStream, person.photo);
    emitPhotoData(outStream, person.photo);
  }

  function listRecentPhotos(outStream, photos) {
    photos
      .filter(p => p.date > recentDateCutoff())
      .forEach(p => {
        outStream.write('<div>\n');
        emitPhotoData(outStream, p);
        outStream.write('</div>\n');
      });
  }

  function renderPhoto() { }
  function recentDateCutoff() { }

  function emitPhotoData(outStream, photo) {
    outStream.write(`<p>title: ${photo.title}</p>\n`);
    outStream.write(`<p>date: ${photo.date.toDateString()}</p>\n`);
    outStream.write(`<p>location: ${photo.location}</p>\n`);
  }
}

function version2() {
  function renderPerson(outStream, person) {
    outStream.write(`<p>${person.name}</p>\n`);
    renderPhoto(outStream, person.photo);
    emitPhotoData(outStream, person.photo);
  }

  function listRecentPhotos(outStream, photos) {
    photos
      .filter(p => p.date > recentDateCutoff())
      .forEach(p => {
        outStream.write('<div>\n');
        emitPhotoData(outStream, p);
        outStream.write('</div>\n');
      });
  }

  function renderPhoto() { }
  function recentDateCutoff() { }

  function emitPhotoData(outStream, photo) {
    zztmp(outStream, photo);
    outStream.write(`<p>location: ${photo.location}</p>\n`);
  }

  function zztmp(outStream, photo) {
    outStream.write(`<p>title: ${photo.title}</p>\n`);
    outStream.write(`<p>date: ${photo.date.toDateString()}</p>\n`);
  }
}

function version3() {
  function renderPerson(outStream, person) {
    outStream.write(`<p>${person.name}</p>\n`);
    renderPhoto(outStream, person.photo);
    zztmp(outStream, person.photo);
    outStream.write(`<p>location: ${person.photo.location}</p>\n`);
  }

  function listRecentPhotos(outStream, photos) {
    photos
      .filter(p => p.date > recentDateCutoff())
      .forEach(p => {
        outStream.write('<div>\n');
        emitPhotoData(outStream, p);
        outStream.write('</div>\n');
      });
  }

  function renderPhoto() { }
  function recentDateCutoff() { }

  function emitPhotoData(outStream, photo) {
    zztmp(outStream, photo);
    outStream.write(`<p>location: ${photo.location}</p>\n`);
  }

  function zztmp(outStream, photo) {
    outStream.write(`<p>title: ${photo.title}</p>\n`);
    outStream.write(`<p>date: ${photo.date.toDateString()}</p>\n`);
  }
}

function version4() {
  function renderPerson(outStream, person) {
    outStream.write(`<p>${person.name}</p>\n`);
    renderPhoto(outStream, person.photo);
    zztmp(outStream, person.photo);
    outStream.write(`<p>location: ${person.photo.location}</p>\n`);
  }

  function listRecentPhotos(outStream, photos) {
    photos
      .filter(p => p.date > recentDateCutoff())
      .forEach(p => {
        outStream.write('<div>\n');
        zztmp(outStream, p);
        outStream.write(`<p>location: ${p.location}</p>\n`);
        outStream.write('</div>\n');
      });
  }

  function renderPhoto() { }
  function recentDateCutoff() { }

  function emitPhotoData(outStream, photo) {
    zztmp(outStream, photo);
    outStream.write(`<p>location: ${photo.location}</p>\n`);
  }

  function zztmp(outStream, photo) {
    outStream.write(`<p>title: ${photo.title}</p>\n`);
    outStream.write(`<p>date: ${photo.date.toDateString()}</p>\n`);
  }
}

function version5() {
  function renderPerson(outStream, person) {
    outStream.write(`<p>${person.name}</p>\n`);
    renderPhoto(outStream, person.photo);
    emitPhotoData(outStream, person.photo);
    outStream.write(`<p>location: ${person.photo.location}</p>\n`);
  }

  function listRecentPhotos(outStream, photos) {
    photos
      .filter(p => p.date > recentDateCutoff())
      .forEach(p => {
        outStream.write('<div>\n');
        emitPhotoData(outStream, p);
        outStream.write(`<p>location: ${p.location}</p>\n`);
        outStream.write('</div>\n');
      });
  }

  function renderPhoto() { }
  function recentDateCutoff() { }

  function emitPhotoData(outStream, photo) {
    outStream.write(`<p>title: ${photo.title}</p>\n`);
    outStream.write(`<p>date: ${photo.date.toDateString()}</p>\n`);
  }
}

function version6() {
  function renderPerson(outStream, person) {
    outStream.write(`<p>${person.name}</p>\n`);
    renderPhoto(outStream, person.photo);
    emitPhotoData(outStream, person.photo);
    outStream.write(`<p>location: ${person.photo.location}</p>\n`);
  }

  function listRecentPhotos(outStream, photos) {
    photos
      .filter(p => p.date > recentDateCutoff())
      .forEach(p => {
        outStream.write('<div>\n');
        emitPhotoData(outStream, p);
        outStream.write('</div>\n');
      });
  }

  function renderPhoto() { }
  function recentDateCutoff() { }

  function emitPhotoData(outStream, photo) {
    outStream.write(`<p>title: ${photo.title}</p>\n`);
    outStream.write(`<p>date: ${photo.date.toDateString()}</p>\n`);
  }
}
