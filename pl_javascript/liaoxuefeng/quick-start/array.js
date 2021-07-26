'use strict';
var arr = ['小明', '小红', '大军', '阿黄'];

arr.sort();
alert(`欢迎${arr.slice(0,arr.length-1).join(',')}和${arr[arr.length-1]}同学!`);