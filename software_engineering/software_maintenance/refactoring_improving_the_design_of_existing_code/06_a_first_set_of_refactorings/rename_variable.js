function version1() {
  let tpHd = 'untitled';

  let result = '';
  result += `<h1>${tpHd}</h1>`;

  const obj = {};
  tpHd = obj['articleTitle'];
}

function version2() {
  let result = '';
  result += `<h1>${title()}</h1>`;

  const obj = {};
  setTitle(obj['articleTitle']);

  let _title = 'untitled';
  function title() { return _title; }
  function setTitle(arg) { _title = arg; }
}

function version3() {
  const cpyNm = 'Acme Gooseberries';
}

function version4() {
  const companyName = 'Acme Gooseberries';
  const cpyNm = companyName;
}
