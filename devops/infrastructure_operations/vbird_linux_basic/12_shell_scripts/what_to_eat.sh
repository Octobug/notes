#!/bin/bash
# Program:
#   Try to tell you what you may eat.
# History:
# 2015/07/17  VBird First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

eat[1]="麦当劳"
eat[2]="肯德基"
eat[3]="小女当家"
eat[4]="大米先生"
eat[5]="津味源"
eat[6]="猪脚饭"
eat[7]="老碗会"
eat[8]="萨莉亚"
eat[9]="711"
eatnum=9 # 可用餐厅数

check=$((${RANDOM} * ${eatnum} / 32767 + 1))
echo "you may eat ${eat[${check}]}"
