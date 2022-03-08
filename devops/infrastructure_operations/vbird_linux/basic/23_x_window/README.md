# 第二十三章 X Window 设置介绍

> <https://linux.vbird.org/linux_basic/centos7/0590xwindow.php>

- [第二十三章 X Window 设置介绍](#第二十三章-x-window-设置介绍)
  - [23.1 什么是 X Window System](#231-什么是-x-window-system)
    - [23.1.1 X Window 的发展简史](#2311-x-window-的发展简史)
    - [23.1.2 主要元件：X Server/X Client/Window Manager/Display Manager](#2312-主要元件x-serverx-clientwindow-managerdisplay-manager)
    - [23.1.3 X Window 的启动流程](#2313-x-window-的启动流程)
    - [23.1.4 X 启动流程测试](#2314-x-启动流程测试)
    - [23.1.5 我是否需要启用 X Window](#2315-我是否需要启用-x-window)
  - [23.2 X Server 配置文件解析与设置](#232-x-server-配置文件解析与设置)
    - [23.2.1 解析 xorg.conf 设置](#2321-解析-xorgconf-设置)
    - [23.2.2 字体管理](#2322-字体管理)
    - [23.2.3 显示器参数微调](#2323-显示器参数微调)
  - [23.3 显卡驱动程序安装范例](#233-显卡驱动程序安装范例)
    - [23.3.1 NVidia](#2331-nvidia)
    - [23.3.2 AMD (ATI)](#2332-amd-ati)
    - [23.3.3 Intel](#2333-intel)
  - [23.4 重点回顾](#234-重点回顾)
  - [23.5 本章习题](#235-本章习题)
  - [23.6 参考资料与延伸阅读](#236-参考资料与延伸阅读)

Linux 的图形界面称为 X Window System，简称为 X 或 X11。X Window System 分为 X server
与 X client。

## 23.1 什么是 X Window System

### 23.1.1 X Window 的发展简史

- X Window 由 MIT 在 1984 年开发；
- 在 Unix Like 上面的圖形使用者介面 (GUI) 被稱為 X 或 X11；
- X11 是一個『軟體』而不是一個作業系統；
- X11 是利用網路架構來進行圖形介面的執行與繪製；
- 較著名的 X 版本為 X11R6 這一版，目前大部分的 X 都是這一版演化出來的 (包括 X11R7)；
- 現在大部分的 distribution 使用的 X 都是由 Xorg 基金會所提供的 X11 軟體；
- X11 使用的是 MIT 授權，為類似 GPL 的開放原始碼授權方式。

### 23.1.2 主要元件：X Server/X Client/Window Manager/Display Manager

- X Server (客户端机器): 硬件管理、屏幕绘制与提供字体功能
- X Client (服务端机器): 负责 X Server 要求的“事件”的处理
- X Window Manager: 特殊的 X Client，负责管理所有的 X Client 软件
  - 提供许多的控制元素，包括工作列、背景桌面的设置等
  - 管理虚拟桌面
  - 提供窗口控制参数，包括窗口大小、窗口重叠显示、窗口移动、窗口最小化等
  - 常见 Window Manager
    - GNOME (GNU Network Object Model Environment): <http://www.gnome.org/>
    - KDE (K Desktop Enviroment): <http://kde.org/>
    - twm (Tab Window Manager): <http://xwinman.org/vtwm.php>
    - XFCE (XForms Common Environment): <http://www.xfce.org/>
- Display Manager: 提供登录需求

### 23.1.3 X Window 的启动流程

- 在命令行启动 X: 通过 `startx` 命令（一个 shell script）
  - X Server
  - X Client
  - xinit
  - 启动 X Server 的文件: xserverrc
  - 启动 X Client 的文件: xinitrc
  - X 启动的端口

### 23.1.4 X 启动流程测试

### 23.1.5 我是否需要启用 X Window

## 23.2 X Server 配置文件解析与设置

### 23.2.1 解析 xorg.conf 设置

Xorg -configure 可以产生 `xorg.conf`，这个配置文件常見的 section name 主要有:

1. Module: 被載入到 X Server 當中的模組 (某些功能的驅動程式)；
2. InputDevice: 包括輸入的 1. 鍵盤的格式 2. 滑鼠的格式，以及其他相關輸入設備；
3. Files: 設定字型所在的目錄位置等；
4. Monitor: 監視器的格式， 主要是設定水平、垂直的更新頻率，與硬體有關；
5. Device: 這個重要，就是顯示卡晶片組的相關設定了；
6. Screen: 這個是在螢幕上顯示的相關解析度與色彩深度的設定項目，與顯示的行為有關；
7. ServerLayout: 上述的每個項目都可以重覆設定，這裡則是此一 X server
   要取用的哪個項目值的設定囉。

### 23.2.2 字体管理

- `/usr/share/X11/fonts/`
- `/usr/share/fonts/`
- `/etc/X11/fontpath.d/`

### 23.2.3 显示器参数微调

## 23.3 显卡驱动程序安装范例

### 23.3.1 NVidia

- 查询硬件与下载驱动程序
- 系统升级与取消 nouveau 模块的载入
- 安装驱动程序

### 23.3.2 AMD (ATI)

### 23.3.3 Intel

## 23.4 重点回顾

- Unix Like 作業系統上面的 GUI 使用的是最初由 MIT 所開發的 X window system，在 1987
  釋出 X11 版，並於 1994 更改為 X11R6 ，故此 GUI 介面也被稱為 X 或 X11
- X window system 的 X server 最初由 XFree86 計畫所開發，後來則由 Xorg
  基金會所持續開發；
- X window system 主要分為 X server 與 X client ，其中 X Server 在管理硬體，而 X
  Client 則是應用程式。
- 在運作上，X Client 應用程式會將所想要呈現的畫面告知 X Server ，最終由 X server
  來將結果透過他所管理的硬體繪製出來！
- 每一支 X client 都不知道對方的存在，必須要透過特殊的 X client ，稱為 Window Manager
  的， 來管理各視窗的重疊、移動、最小化等工作。
- 若有需要登入圖形介面，有時會有 Display Manager 來管理這方面的動作
- startx 可以偵測 X server / X client 的啟動腳本，並呼叫 xinit 來分別執行；
- X 可以啟動多個，各個 X 顯示的位置使用 -display 來處理，顯示位置為 :0, :1...
- Xorg 是一個 X server ，設定檔位於 /etc/X11/xorg.conf ，裡面含有 Module, Files,
  Monitor, Device 等設定階段。目前較新的設定中， 會將額外的設定放置於
  `/etc/X11/xorg.conf.d/*.conf`

## 23.5 本章习题

## 23.6 参考资料与延伸阅读
