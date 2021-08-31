'use strict';

function get_primes(arr) {
    return arr.filter(function(s){
        var sqrtnum = Math.sqrt(s);
        var flag = true;
        if(s===1)
            return false;
        for(let i = 2; i <= sqrtnum; ++i){
            if(s % i === 0)
                flag = false;
        }
        return flag;
    });

}

// 测试:
var
    x,
    r,
    arr = [];
for (x = 1; x < 100; x++) {
    arr.push(x);
}
r = get_primes(arr);
if (r.toString() === [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97].toString()) {
    alert('测试通过!');
} else {
    alert('测试失败: ' + r.toString());
}