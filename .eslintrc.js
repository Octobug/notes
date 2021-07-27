module.exports = {
  'env': {
    'es6': true,
    'browser': true,
    'node': true,
    'jquery': true
  },
  'parser': '@babel/eslint-parser',
  'extends': 'eslint:recommended',
  'parserOptions': {
    'ecmaVersion': 2018,
    'sourceType': 'module',
    'requireConfigFile': false
  },
  'rules': {
    'indent': [
      'error',
      2,
      { 'SwitchCase': 1 }
    ],
    'linebreak-style': [
      'error',
      'unix'
    ],
    'semi': [
      'error',
      'always'
    ],
    'quotes': [
      'error',
      'single'
    ],
  }
};
