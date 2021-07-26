/**
 * Created by bITeMe on 2016/11/13.
 */
'use strict';
var selected = null;

// 分别选择所有语言，所有动态语言，所有静态语言，JavaScript，Lua，C等:
selected = $('.test-selector li');
selected = $('.test-selector>ol');
selected = $('.test-selector>ul');
selected = $('.test-lang>.lang-javascript');
selected = $('.test-lang>.lang-lua');
selected = $('.test-lang>.lang-c');
// 高亮结果:
if (!(selected instanceof jQuery)) {
    alert('不是有效的jQuery对象!');
}
$('#test-jquery').find('*').css('background-color', '');
selected.css('background-color', '#ffd351');