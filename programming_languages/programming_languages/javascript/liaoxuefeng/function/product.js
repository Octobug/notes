'use strict';

function product(arr) {
    return arr.reduce(function(x,y){
        return x * y;
    });

}

// 测试:
if (product([1, 2, 3, 4]) === 24 && product([0, 1, 2]) === 0 && product([99, 88, 77, 66]) === 44274384) {
    alert('测试通过!');
}
else {
    alert('测试失败!');
}