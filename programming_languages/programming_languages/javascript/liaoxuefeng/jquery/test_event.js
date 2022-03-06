/**
 * Created by bITeMe on 2017/2/21.
 */
'use strict';

var
    form = $('#test-form'),
    langs = form.find('[name=lang]'),
    selectAll = form.find('label.selectAll :checkbox'),
    selectAllLabel = form.find('label.selectAll span.selectAll'),
    deselectAllLabel = form.find('label.selectAll span.deselectAll'),
    invertSelect = form.find('a.invertSelect');

// 重置初始化状态:
form.find('*').show().off();
form.find(':checkbox').prop('checked', false).off();
deselectAllLabel.hide();
// 拦截form提交事件:
form.off().submit(function (e) {
    e.preventDefault();
    alert(form.serialize());
});

// TODO:绑定事件
selectAll.click(function (e) {
    selectAllLabel.toggle();
    deselectAllLabel.toggle();
    langs.prop('checked', $(this).prop('checked'));
});

langs.change(function () {
    if (langs.size() == $('input[name=lang]:checked').size()) {
        selectAll.prop('checked', true);
        selectAllLabel.hide();
        deselectAllLabel.show();
    } else {
        selectAll.prop('checked', false);
        selectAllLabel.show();
        deselectAllLabel.hide();
    }
});

invertSelect.click(function () {
    langs.each(function () {
        $(this).prop('checked', !$(this).prop('checked'));
        langs.change();
    })
});

// 测试:
alert('请测试功能是否正常。');