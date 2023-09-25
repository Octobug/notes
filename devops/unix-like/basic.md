# Basic

- [Basic](#basic)
  - [日期与时间设置](#日期与时间设置)
  - [语系设置](#语系设置)

## 日期与时间设置

- `timedatectl [SUBCMD]`:时区的显示与设置
  - `list-timezones`: 列出所有支持的时区
  - `set-timezone`: 设置时区
  - `set-time`: 设置时间，格式为 "yyyy-mm-dd HH:MM"
  - `set-ntp`: 设置网络校时系统
- `ntpdate`: 手动网络校时
- `hwclock`: 校正 BIOS 时间

## 语系设置

- localectl
