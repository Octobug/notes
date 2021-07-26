/**
 * Created by bITeMe on 2016/11/12.
 */

'use strict';

var selected = null;

selected = $('#para-1');
selected = $('.color-red.color-green');
selected = $('.color-red');
selected = $('[class^="color-"]');
selected = $('input[name="name"]');
selected = $('input[name="name"],input[name="email"]');

// 高亮结果:
if (!(selected instanceof jQuery)) {
    alert('不是有效的jQuery对象!');
}
$('#test-jquery').find('*').css('background-color', '');
selected.css('background-color', '#ffd351');