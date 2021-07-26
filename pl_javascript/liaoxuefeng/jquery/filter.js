/**
 * Created by bITeMe on 2016/11/25.
 */

'use strict';
var json = null;

function form2json(formID) {
    var result = {};
    $(formID).serializeArray().forEach(
        data => {
            result[data.name] = data.value;
        }
    );
    return JSON.stringify(result);
}

json = form2json("#test-form");

// 显示结果:
if (typeof(json) === 'string') {
    alert(json);
}
else {
    alert('json变量不是string!');
}