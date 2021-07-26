/**
 * Created by bITeMe on 2016/11/10.
 */

'use strict';

// sort list:
var list = document.getElementById('test-list');
var children = list.children;
var arr = [];
for (let i = 0; i < children.length; i++) {
    arr.push(children[i].innerText);
}
arr.sort();
for (let i = 0; i < children.length; i++) {
    children[i].innerText = arr[i];
}


// 测试:
;(function () {
    var
        arr, i,
        t = document.getElementById('test-list');
    if (t && t.children && t.children.length === 5) {
        arr = [];
        for (i = 0; i < t.children.length; i++) {
            arr.push(t.children[i].innerText);
        }
        if (arr.toString() === ['Haskell', 'JavaScript', 'Python', 'Ruby', 'Scheme'].toString()) {
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