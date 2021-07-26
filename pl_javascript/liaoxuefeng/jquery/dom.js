/**
 * Created by bITeMe on 2017/1/1.
 */

'use strict';

var words = ['Pascal', 'Lua', 'Ruby', 'Python', 'Swift', 'Javascript'].sort();
var ul = $('#test-div>ul');
ul.find('li').remove();
words.map((x) => ul.append('<li><span>' + x + '</span></li>'));

// 测试:
;(function () {
    var s = $('#test-div>ul>li').map(function () {
        return $(this).text();
    }).get().join(',');
    if (s === 'JavaScript,Lua,Pascal,Python,Ruby,Swift') {
        alert('测试通过!');
    } else {
        alert('测试失败: ' + s);
    }
})();