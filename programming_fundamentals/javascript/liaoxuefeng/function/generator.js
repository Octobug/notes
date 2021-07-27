/**
 * Created by bITeMe on 2016/11/2.
 */

'use strict';
function* next_id() {
    var i = 1;
    while (true){
        yield i++;
    }
}

// 测试:
var
    x,
    pass = true,
    g = next_id();
for (x = 1; x < 100; x ++) {
    if (g.next().value !== x) {
        pass = false;
        alert('测试失败!');
        break;
    }
}
if (pass) {
    alert('测试通过!');
}