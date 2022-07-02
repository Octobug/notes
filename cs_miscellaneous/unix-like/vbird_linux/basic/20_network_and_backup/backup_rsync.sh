#!/bin/bash
remotedir=/home/backup/
basedir=/backup/weekly
host=127.0.0.1
id=dmtsai

# 底下為程式階段！不需要修改喔！
rsync -av -e ssh $basedir ${id}@${host}:${remotedir}
