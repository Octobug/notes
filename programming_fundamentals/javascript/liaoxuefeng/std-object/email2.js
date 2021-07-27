/**
 * Created by Administartor on 2016/11/2.
 */

'use strict';

var re = /^<([\w\s]+)>\s+([\w\.]+@\w+\.\w+)$/;
re = /^<(\w+\s\w+)>\s+(\w+@\w+\.\w+)$/;

// 测试:
var r = re.exec('<Tom Paris> tom@voyager.org');
if (r === null || r.toString() !== ['<Tom Paris> tom@voyager.org', 'Tom Paris', 'tom@voyager.org'].toString()) {
    alert('测试失败!');
}
else {
    alert('测试成功!');
}