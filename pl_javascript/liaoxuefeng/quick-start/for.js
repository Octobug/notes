'use strict';
var x = 1;
var i;
for (i=1;i<=10;++i)
    x *= i;
if (x === 3628800) {
    alert('1 x 2 x 3 x ... x 10 = ' + x);
}
else {
    alert('计算错误');
}