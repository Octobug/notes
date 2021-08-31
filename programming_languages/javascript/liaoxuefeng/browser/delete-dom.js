/**
 * Created by bITeMe on 2016/11/10.
 */
'use strict';

var str = ['JavaScript', 'HTML', 'CSS'];
var list = document.querySelector('#test-list');
var children = list.children;
for (let i = children.length - 1; i >= 0; i--) {
    if (str.indexOf(children[i].innerText) === -1) {
        list.removeChild(children[i]);
    }
}
// 测试:
;(function () {
    var
        arr, i,
        t = document.getElementById('test-list');
    if (t && t.children && t.children.length === 3) {
        arr = [];
        for (i = 0; i < t.children.length; i++) {
            arr.push(t.children[i].innerText);
        }
        if (arr.toString() === ['JavaScript', 'HTML', 'CSS'].toString()) {
            alert('测试通过!');
        }
        else {
            alert('测试失败: ' + arr.toString());
        }
    }
    else {
        alert('测试失败!');
    }
})();