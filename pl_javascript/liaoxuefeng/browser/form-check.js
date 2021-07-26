/**
 * Created by bITeMe on 2016/11/11.
 */
'use strict';
var checkRegisterForm = function () {

        // TODO:
    var username = document.querySelector('#username').value;
    var password = document.querySelector('#password').value;
    var password_2 = document.querySelector('#password-2').value;
    var error = document.querySelector('#test-error');

    if(/^\w{3,10}$/.test(username) == false){
        error.innerText = '用户名格式错误';
        return false;
    }
    if(/^[\@A-Za-z0-9\!\#\$\%\^\&\*\.\~]{6,10}$/.test(password) == false){
        error.innerText = '密码格式错误';
        return false;
    }
    if(password!=password_2){
        error.innerText = '两次密码不一致';
        return false;
    }
    return true;

    }

// 测试:
    ;
(function () {
    window.testFormHandler = checkRegisterForm;
    var form = document.getElementById('test-register');
    if (form.dispatchEvent) {
        var event = new Event('submit', {
            bubbles: true,
            cancelable: true
        });
        form.dispatchEvent(event);
    } else {
        form.fireEvent('onsubmit');
    }
})();