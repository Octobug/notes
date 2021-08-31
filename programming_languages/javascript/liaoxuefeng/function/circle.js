'use strict';

function area_of_circle(r, pi) {
    if(pi === undefined){
        pi = 3.14
    }
    return pi*r*r;
}

// 测试:
if (area_of_circle(2) === 12.56 && area_of_circle(2, 3.1416) === 12.5664) {
    alert('测试通过');
} else {
    alert('测试失败');
}