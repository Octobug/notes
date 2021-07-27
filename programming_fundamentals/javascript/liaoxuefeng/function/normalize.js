'use strict';

function normalize(arr) {
    return arr.map(function(x){
        var head = x[0].toUpperCase();
        var tail = x.substring(1).toLowerCase();
        return head + tail;
    });

}

// 测试:
if (normalize(['adam', 'LISA', 'barT']).toString() === ['Adam', 'Lisa', 'Bart'].toString()) {
    alert('测试通过!');
}
else {
    alert('测试失败!');
}

小明希望利用map()把字符串变成整数，他写的代码很简洁：
'use strict';

var arr = ['1', '2', '3'];
var r;

alert('[' + r[0] + ', ' + r[1] + ', ' + r[2] + ']');