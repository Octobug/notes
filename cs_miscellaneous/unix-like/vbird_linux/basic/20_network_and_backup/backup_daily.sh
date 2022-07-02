#!/bin/bash
# =========================================================
# 請輸入，你想讓備份資料放置到那個獨立的目錄去
basedir=/backup/daily/ <==你只要改這裡就可以了！

# =========================================================
PATH=/bin:/usr/bin:/sbin:/usr/sbin
export PATH
export LANG=C
basefile1=$basedir/mysql.$(date +%Y-%m-%d).tar.bz2
basefile2=$basedir/cgi-bin.$(date +%Y-%m-%d).tar.bz2
[ ! -d "$basedir" ] && mkdir $basedir

# 1. MysQL (資料庫目錄在 /var/lib/mysql)
cd /var/lib
tar -jpc -f $basefile1 mysql

# 2. WWW 的 CGI 程式 (如果有使用 CGI 程式的話)
cd /var/www
tar -jpc -f $basefile2 cgi-bin
