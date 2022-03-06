/**
 * Created by bITeMe on 2016/11/10.
 */
'use strict';

// 选择<p>JavaScript</p>:
var js = document.getElementById('test-p');

// 选择<p>Python</p>,<p>Ruby</p>,<p>Swift</p>:
var arr = document.getElementsByClassName('c-red c-green')[0].getElementsByTagName('p');

// 选择<p>Haskell</p>:
var haskell = document.getElementsByClassName('c-green')[1].lastElementChild;

// 测试:
if (!js || js.innerText !== 'JavaScript') {
    alert('选择JavaScript失败!');
} else if (!arr || arr.length !== 3 || !arr[0] || !arr[1] || !arr[2] || arr[0].innerText !== 'Python' || arr[1].innerText !== 'Ruby' || arr[2].innerText !== 'Swift') {
    alert('选择Python,Ruby,Swift失败!');
} else if (!haskell || haskell.innerText !== 'Haskell') {
    alert('选择Haskell失败!');
} else {
    alert('测试通过!');
}