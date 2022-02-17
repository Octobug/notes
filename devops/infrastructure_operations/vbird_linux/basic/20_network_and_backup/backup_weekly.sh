#!/bin/bash
# ====================================================================
# 使用者參數輸入位置：
# basedir=你用來儲存此腳本所預計備份的資料之目錄(請獨立檔案系統)
basedir=/backup/weekly <==您只要改這裡就好了！

# ====================================================================
# 底下請不要修改了！用預設值即可！
PATH=/bin:/usr/bin:/sbin:/usr/sbin
export PATH
export LANG=C

# 設定要備份的服務的設定檔，以及備份的目錄
named=$basedir/named
postfixd=$basedir/postfix
vsftpd=$basedir/vsftp
sshd=$basedir/ssh
sambad=$basedir/samba
wwwd=$basedir/www
others=$basedir/others
userinfod=$basedir/userinfo
# 判斷目錄是否存在，若不存在則予以建立。
for dirs in $named $postfixd $vsftpd $sshd $sambad $wwwd $others $userinfod; do
    [ ! -d "$dirs" ] && mkdir -p $dirs
done

# 1. 將系統主要的服務之設定檔分別備份下來，同時也備份 /etc 全部。
cp -a /var/named/chroot/{etc,var} $named
cp -a /etc/postfix /etc/dovecot.conf $postfixd
cp -a /etc/vsftpd/* $vsftpd
cp -a /etc/ssh/* $sshd
cp -a /etc/samba/* $sambad
cp -a /etc/{my.cnf,php.ini,httpd} $wwwd
cd /var/lib
tar -jpc -f $wwwd/mysql.tar.bz2 mysql
cd /var/www
tar -jpc -f $wwwd/html.tar.bz2 html cgi-bin
cd /
tar -jpc -f $others/etc.tar.bz2 etc
cd /usr/
tar -jpc -f $others/local.tar.bz2 local

# 2. 關於使用者參數方面
cp -a /etc/{passwd,shadow,group} $userinfod
cd /var/spool
tar -jpc -f $userinfod/mail.tar.bz2 mail
cd /
tar -jpc -f $userinfod/home.tar.bz2 home
cd /var/spool
tar -jpc -f $userinfod/cron.tar.bz2 cron at
