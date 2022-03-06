'use strict';
var arr = ['Bart', 'Lisa', 'Adam'];
var i;

//for
for (i in arr)
    alert(`Hello, ${arr[i]}!`);

//while
var i=0;
while(i<arr.length)
{
    alert(`Hello, ${arr[i]}!`);
    i++;
}