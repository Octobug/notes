# 第十五章 例行性工作调度（crontab）

> <https://linux.vbird.org/linux_basic/centos7/0430cron.php>

- [第十五章 例行性工作调度（crontab）](#第十五章-例行性工作调度crontab)
  - [15.1 什么是例行性工作调度](#151-什么是例行性工作调度)
    - [15.1.1 Linux 工作调度的种类：at, cron](#1511-linux-工作调度的种类at-cron)
    - [15.1.2 CentOS Linux 系统上常见的例行性工作](#1512-centos-linux-系统上常见的例行性工作)
  - [15.2 仅执行一次的工作调度](#152-仅执行一次的工作调度)
    - [15.2.1 atd 的启动与 at 运行的方式](#1521-atd-的启动与-at-运行的方式)
    - [15.2.2 实际运行单一工作调度](#1522-实际运行单一工作调度)
  - [15.3 循环执行的例行性工作调度](#153-循环执行的例行性工作调度)
    - [15.3.1 用户的设置](#1531-用户的设置)
    - [15.3.2 系统的配置文件：/etc/crontab, /etc/cron.d/*](#1532-系统的配置文件etccrontab-etccrond)
    - [15.3.3 一些注意事项](#1533-一些注意事项)
  - [15.4 停机期间可唤醒的工作任务](#154-停机期间可唤醒的工作任务)
    - [15.4.1 什么是 anacron](#1541-什么是-anacron)
    - [15.4.2 anacron 与 /etc/anacrontab](#1542-anacron-与-etcanacrontab)
  - [15.5 重点回顾](#155-重点回顾)
  - [15.6 本章习题](#156-本章习题)

## 15.1 什么是例行性工作调度

### 15.1.1 Linux 工作调度的种类：at, cron

- `at`: 可以处理仅执行一次的就结束调度的命令，需要 `atd` 服务支持。
- `crontab`: 会一直循环的调度命令，需要 `crond` 服务支持。

### 15.1.2 CentOS Linux 系统上常见的例行性工作

- 日志文件的轮替 (logrotate)
- 日志文件分析的任务 (logwatch)
- 更新 locate 数据库 (updatedb)
- 更新 man page 数据库 (mandb)
- RPM 软件数据库的更新
- 移除暂存文件 (tmpwatch)
- 与网络服务有关的分析

## 15.2 仅执行一次的工作调度

### 15.2.1 atd 的启动与 at 运行的方式

- `systemctl enable atd`
- at 的运行方式
  - at 的待执行任务保存于 `/var/spool/at/` 目录内
  - 如果 `/etc/at.allow` 文件存在，则在其中的用户才能使用 at
  - 如果 `/etc/at.allow` 文件不存在，则寻找 `/etc/at.deny` 文件，只有 deny
    中的用户不能使用 at
  - 如果两个文件都不存在，则只有 root 能使用 at

### 15.2.2 实际运行单一工作调度

- `at -c JOBID`
- `at [-dlmv] TIME`
  - `-d`: 相当于 `atrm`，取消一个在 at 调度中的工作
  - `-l`: 相当于 `atq`，列出系统所有当前用户的 at 调度任务
  - `-m`: 在 at 完成工作后以 email 通知用户，即使没有任何输出信息
  - `-v`: 使用易读的时间格式列出 at 调度中的工作列表
- 例子
  
  ```sh
  范例一：再过五分钟后，将 /root/.bashrc 寄给 root 自己
  [root@www ~]# at now + 5 minutes  <==记得单位要加 s 喔！
  at> /bin/mail root -s "testing at job" < /root/.bashrc
  at> <EOT>   <==这里输入 [ctrl] + d 就会出现 <EOF> 的字样！代表结束！
  job 4 at 2009-03-14 15:38
  # 上面这行资讯在说明，第 4 个 at 工作将在 2009/03/14 的 15:38 进行！
  # 而运行 at 会进入所谓的 at shell 环境，让你下达多重命令等待运行！

  范例二：将上述的第 4 项工作内容列出来查阅
  [root@www ~]# at -c 4
  #!/bin/sh               <==就是透过 bash shell 的啦！
  # atrun uid=0 gid=0
  # mail     root 0
  umask 22
  ....(中间省略许多的环境变量项目)....
  cd /root || {           <==可以看出，会到下达 at 时的工作目录去运行命令
          echo 'Execution directory inaccessible' >&2
          exit 1
  }

  /bin/mail root -s "testing at job" < /root/.bashrc
  # 你可以看到命令运行的目录 (/root)，还有多个环境变量与实际的命令内容啦！

  范例三：由於机房预计於 2009/03/18 停电，我想要在 2009/03/17 23:00 关机？
  [root@www ~]# at 23:00 2009-03-17
  at> /bin/sync
  at> /bin/sync
  at> /sbin/shutdown -h now
  at> <EOT>
  job 5 at 2009-03-17 23:00
  # 您瞧瞧！ at 还可以在一个工作内输入多个命令呢！不错吧！
  ```

- at 在运行任务时会进入下达 at 任务的工作目录，因此任务的命令应优先使用绝对路径。
- at 任务执行时与终端机环境无关，stdout 与 stderr 只会输出到用户的 mailbox 中。
  可以将输出信息重定向到终端设备文件，如 `echo "Hello" > /dev/tty1`。
  在没有任何输出信息时，at 不会发送邮件通知。
- `at` 工作管理
  - `atq`
  - `atrm`
- `batch`: 系统空闲时才进行背景任务
  - CPU 负载小于 0.8 时才执行工作任务
  - 例子

    ```sh
    範例一：請執行 pi 的計算，然後在系統閒置時，執行 updatdb 的任務
    [root@study ~]# echo "scale=100000; 4*a(1)" | bc -lq &
    [root@study ~]# echo "scale=100000; 4*a(1)" | bc -lq &
    [root@study ~]# echo "scale=100000; 4*a(1)" | bc -lq &
    [root@study ~]# echo "scale=100000; 4*a(1)" | bc -lq &
    # 然後等待個大約數十秒的時間，之後再來確認一下工作負載的情況！
    [root@study ~]# uptime
    19:56:45 up 2 days, 19:54,  2 users,  load average: 3.93, 2.23, 0.96

    [root@study ~]# batch
    at> /usr/bin/updatedb
    at> <EOT>
    job 4 at Thu Jul 30 19:57:00 2015

    [root@study ~]# date;atq
    Thu Jul 30 19:57:47 CST 2015
    4       Thu Jul 30 19:57:00 2015 b root
    # 可以看得到，明明時間已經超過了，卻沒有實際執行 at 的任務！

    [root@study ~]# jobs
    [1]   Running                 echo "scale=100000; 4*a(1)" | bc -lq &
    [2]   Running                 echo "scale=100000; 4*a(1)" | bc -lq &
    [3]-  Running                 echo "scale=100000; 4*a(1)" | bc -lq &
    [4]+  Running                 echo "scale=100000; 4*a(1)" | bc -lq &
    [root@study ~]# kill -9 %1 %2 %3 %4
    # 這時先用 jobs 找出背景工作，再使用 kill 刪除掉四個背景工作後，慢慢等待工作負載的下降

    [root@study ~]# uptime; atq
    20:01:33 up 2 days, 19:59,  2 users,  load average: 0.89, 2.29, 1.40
    4       Thu Jul 30 19:57:00 2015 b root
    [root@study ~]# uptime; atq
    20:02:52 up 2 days, 20:01,  2 users,  load average: 0.23, 1.75, 1.28
    # 在 19:59 時，由於 loading 還是高於 0.8，因此 atq 可以看得到 at job 還是持續再等待當中喔！
    # 但是到了 20:01 時， loading 降低到 0.8 以下了，所以 atq 就執行完畢囉！
    ```

## 15.3 循环执行的例行性工作调度

### 15.3.1 用户的设置

- cron 的待执行任务保存于 `/var/spool/cron/` 目录内
- 如果 `/etc/cron.allow` 文件存在，则在其中的用户才能使用 cron
- 如果 `/etc/cron.allow` 文件不存在，则寻找 `/etc/cron.deny` 文件，只有 deny
  中的用户不能使用 at
- `crontab [-u USERNAME] [-elr]`
  - `-e`: 编辑 crontab 内容
  - `-l`: 列出 crontab 内容
  - `-r`: 移除所有 corntab 内容
  - `-u`: 指定用户
- `crontab -e` 格式: `m h dom mon dow  command`
  - m: minute, 0-59
  - h: hour, 0-23
  - dom: day of month, 1-31
  - mon: month, 1-12
  - dow: day of week, 0-7, 0 与 7 都是星期天
  - `*`: 任意时刻
  - `,`: 表示多个时间点，例如 `0 3,6 * * *` 表示 3 与 6 时每逢 0 分执行一次
  - `-`: 表示时段，例如 `0 3-6 * * *` 表示 3-6 时每逢 0 分执行一次
  - `/n`: 表示每隔 n 单位间隔，例如 `*/5 * * * *` 表示每 5 分钟执行一次

### 15.3.2 系统的配置文件：/etc/crontab, /etc/cron.d/*

系统的 cron 内容格式与用户不同

- `MAILTO=root`: 将执行输出信息发送到邮箱
- `PATH=...`: 可执行文件路径
- `m h dom mon dow  user command`: 可以指定用户
- `crond` 服务读取的配置文件路径
  - `/etc/crontab`
  - `/etc/cron.d/*`
  - `/var/spool/cron/*`

总结：

- 个人化的行为使用 `crontab -e`
- 系统级的行为使用 `vim /etc/crontab`
  - 每小时、每日、每周、每月等任务的可执行程序放在对应的 `/etc/cron.*` 目录中
- 对于软件开发者，其软件配套的 cron 使用 `/etc/cron.d/appname`

### 15.3.3 一些注意事项

- 资源分配不均：存在大量 cron 任务时，很容易出现该问题。此时需要精细化 cron 的执行时间
- 取消不必要的输出
- 安全检查：看 `/var/log/cron` 中是否有异常记录

## 15.4 停机期间可唤醒的工作任务

### 15.4.1 什么是 anacron

anacron 适用于不是 24 运行的 Linux 系统，用来执行已超时却未被执行的调度工作。

### 15.4.2 anacron 与 /etc/anacrontab

```sh
[root@study ~]# cat /etc/cron.hourly/0anacron
#!/bin/sh
# Check whether 0anacron was run today already
if test -r /var/spool/anacron/cron.daily; then
    day=`cat /var/spool/anacron/cron.daily`
fi
if [ `date +%Y%m%d` = "$day" ]; then
    exit 0;
fi
# 上面的語法在檢驗前一次執行 anacron 時的時間戳記！

# Do not run jobs when on battery power
if test -x /usr/bin/on_ac_power; then
    /usr/bin/on_ac_power >/dev/null 2>&1
    if test $? -eq 1; then
    exit 0
    fi
fi
/usr/sbin/anacron -s
# 所以其實也僅是執行 anacron -s 的指令！因此我們得來談談這支程式！
```

```sh
[root@study ~]# cat /etc/anacrontab
SHELL=/bin/sh
PATH=/sbin:/bin:/usr/sbin:/usr/bin
MAILTO=root
RANDOM_DELAY=45           # 隨機給予最大延遲時間，單位是分鐘
START_HOURS_RANGE=3-22    # 延遲多少個小時內應該要執行的任務時間

1         5        cron.daily         nice run-parts /etc/cron.daily
7        25        cron.weekly        nice run-parts /etc/cron.weekly
@monthly 45        cron.monthly       nice run-parts /etc/cron.monthly
天數     延遲時間  工作名稱定義       實際要進行的指令串
# 天數單位為天；延遲時間單位為分鐘；工作名稱定義可自訂，指令串則通常與 crontab 的設定相同！

[root@study ~]# more /var/spool/anacron/*
::::::::::::::
/var/spool/anacron/cron.daily
::::::::::::::
20150731
::::::::::::::
/var/spool/anacron/cron.monthly
::::::::::::::
20150703
::::::::::::::
/var/spool/anacron/cron.weekly
::::::::::::::
20150727
# 上面則是三個工作名稱的時間記錄檔以及記錄的時間戳記
```

我們拿 /etc/cron.daily/ 那一行的設定來說明好了。那四個欄位的意義分別是：

- 天數：anacron 執行當下與時間戳記 (/var/spool/anacron/ 內的時間紀錄檔) 相差的天數，
  若超過此天數，就準備開始執行，若沒有超過此天數，則不予執行後續的指令。
- 延遲時間：若確定超過天數導致要執行排程工作了，那麼請延遲執行的時間，
  因為擔心立即啟動會有其他資源衝突的問題吧！
- 工作名稱定義：這個沒啥意義，就只是會在 /var/log/cron 裡頭記載該項任務的名稱這樣！
  通常與後續的目錄資源名稱相同即可。
- 實際要進行的指令串：有沒有跟 0hourly 很像啊！沒錯！相同的作法啊！透過 run-parts
- 來處理的！

根據上面的設定檔內容，我們大概知道 anacron 的執行流程應該是這樣的 (以 cron.daily 為例)：

1. 由 /etc/anacrontab 分析到 cron.daily 這項工作名稱的天數為 1 天；
2. 由 /var/spool/anacron/cron.daily 取出最近一次執行 anacron 的時間戳記；
3. 由上個步驟與目前的時間比較，若差異天數為 1 天以上 (含 1 天)，就準備進行指令；
4. 若準備進行指令，根據 /etc/anacrontab 的設定，將延遲 5 分鐘 + 3 小時 (看
   START_HOURS_RANGE 的設定)；
5. 延遲時間過後，開始執行後續指令，亦即『 run-parts /etc/cron.daily 』這串指令；
6. 執行完畢後， anacron 程式結束。

最後，我們來總結一下本章談到的許多設定檔與目錄的關係吧！這樣我們才能了解 crond 與 anacron
的關係：

1. crond 會主動去讀取 /etc/crontab, /var/spool/cron/*, /etc/cron.d/* 等設定檔，
   並依據『分、時、日、月、周』的時間設定去各項工作排程；
2. 根據 /etc/cron.d/0hourly 的設定，主動去 /etc/cron.hourly/ 目錄下，
   執行所有在該目錄下的執行檔；
3. 因為 /etc/cron.hourly/0anacron 這個指令檔的緣故，主動的每小時執行 anacron ，並呼叫
   /etc/anacrontab 的設定檔；
4. 根據 /etc/anacrontab 的設定，依據每天、每週、每月去分析 /etc/cron.daily/,
   /etc/cron.weekly/, /etc/cron.monthly/ 內的執行檔，以進行固定週期需要執行的指令。

## 15.5 重点回顾

## 15.6 本章习题
