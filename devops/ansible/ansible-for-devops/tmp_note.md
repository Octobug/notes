# Notes

## 1.1 How Ansible Works

1. 通过 SSH 连接目标主机
2. 根据 palybook 指令在主机生成 Python 脚本
3. 在主机上执行脚本
4. 等待脚本完成执行

- Ansible 会并行执行每个 host 的任务
- Ansible 会等待每个 host 的任务执行完成才执行下一个任务（使用同一套 playbook）
- Ansible 根据 playbook 指定的顺序执行任务

## 1.2 What's So Great About Ansible

优点：

- 容易阅读的语法（YAML）
- 不需要在远程主机上面安装客户端（一切通过 SSH，需要 Python）
- 基于推送
  - 编辑 playbook
  - 执行 playbook
  - Ansible 连接主机执行任务

## 1.3 What Do I Need to Know ?

需要的基础：

- 基本的 Linux 使用，包括：
  - 使用 SSH 连接远程主机
  - bash 的基本使用（如管道、重定向）
  - 包管理
  - sudo
  - 文件权限
  - 开启、关闭服务
  - 环境变量配置
  - 基本的脚本编写
- YAML 、INI
- Jinja2 模板（例如写配置文件时，替换模板中的常量）

## 1.4 Installing Ansible

安装 Ansible 的方式：

1. 使用 apt 或 yum 之类的包管理工具安装

    ```sh
    sudo yum install ansible
    ```

2. 在 root 用户权限下使用 pip 安装

    ```sh
    sudo pip install ansible
    ```

3. 创建 virtualenv，再用 pip 安装

    ```sh
    virtualenv env
    source env/bin/activate
    pip install ansible
    ```

## 1.5 Setting Up a Server for Testing

- 需要目标主机的 root 权限（sudo）
- 开放 SSH 远程登录

配置从管理节点到远程主机之间基于key（无密码的方式）的SSH连接：

```sh
# 生成 ssh key
ssh-keygen
# 复制 ssh pub key 到远程主机，ssh 的时候就不需要输入密码了
ssh-copy-id remoteuser@remoteserver
# ssh的时候不会提示是否保存key
ssh-keyscan remote_servers >> ~/.ssh/kown_hosts
# 验证 SSH 配置：在管理节点执行下面的ssh命令
ssh remoteuser@remoteserver
```

以上步骤成功之后，Ansible 就可以使用公钥通过 ssh 登录到远程主机了，以下命令测试是否连接成功。

```sh
ansible <host_name> -i <inventory_file> -m ping
```

输出：

```sh
testserver | success >> {
    "changed": false,
    "ping": "pong"
}
```

changed: 是否改变服务器状态。

### ansible.cfg

ansible 按以下顺序查找 ansible.cfg 文件：

1. 环境变量 ANSIBLE_CONFIG 指定的路径
2. ./ansible.cfg （即当前目录，一般来说使用这种，这样可以把它也加到版本控制仓库里面）
3. ~/.ansible.cfg
4. /etc/ansible/ansible.cfg

例子：

```ini
# ansible.cfg
[defaults]
hostfile = hosts
remote_user = whoami
host_key_checking = False
# hosts
testserver ansible_ssh_host=192.168.56.101 ansible_ssh_port=22
```

## 2.1 Running the Playbook

### Gathering Facts

ansible 开始执行一个 play 时，第一件事是收集目标主机的操作系统、域名、IP、MAC 地址等信息，这些信息可以在后续 playbook 中使用。

```sh
ansible-playbook site.yml
# 如果没有使用 ansible.cfg 来指定默认的 hosts 文件。可以使用 -i 选项来指定
```

## 2.2 Playbooks Are YAML

hosts（inventory） 文件使用 ini 格式，playbook 使用 YAML

```yml
# 文件开头
---
# 字符串，双引号不是必须的
this is a string
# 布尔值
# 在 playbook 中，可以使用以下值
true, True, TRUE, yes, Yes, YES, on, On, ON, y, Y
false, False, FALSE, no, No, NO, off, Off, OFF, n, N
# 在 module 中，可以使用以下值
yes, on, 1, true
no, off, 0, false
# 建议在 playbooks 中使用 True/False，而指定 module 选项时使用 yes/no
# 列表
- a
- b
- c
# 也可以是行内格式
[a, b, c]
# 字典
k1: v1
k2: v2
# 折叠换行
# 当字符串过长时，可以使用大于号 ">" 来换行，"|" 可以保留换行符
sentence: >
    This is
    a sentence.
```

## 2.3 Anatomy of a Playbook

Playbook

Play：

- name（可选）
- sudo（可选，默认为 false）
- vars（可选）
- 若干 hosts
- 若干 tasks

Tasks：

- name（可选）
- module_name: arguments

Modules：

- apt
- copy
- file
- service
- ...

使用 `ansible-doc <module_name>` 可以查看模块的用法

### state

每个 ansible tasks 都可能改变目标主机的状态，ansible 模块会先检查是否将改变主机状态，
如果当前状态与目标状态一致，ansible 将不会做任何事情并返回 ok，否则将在完成动作之后返回
changed。

### Handlers

handlers 的结构类似 tasks，区别是当它被 task 通知（notify），并且该 task 执行后的状态是
changed 才会运行。所有 task 执行完成之后才开始执行 handler，handler 按照在 play
中出现的顺序执行，而不是按被通知的顺序。

## 3.1 Behavioral Inventory Parameters

一些由 ansible 默认配置的仓库变量，用于进行 ssh 连接，当需要修改这些参数时，可以在 inventory 文件中覆盖掉默认的变量

## 3.2 Hosts and Group Variables

### Hosts and Group Variables: Inside the Inventory

```ini
[all:vars]
# all 由 ansible 自动创建，包含所有 host
all_var = a

[production:vars]
pro_var = b

[staging:vars]
sta_var = c
```

### Host and Group Variables: In Their Own Files

host 变量文件和 group 变量文件分别放在 `host_vars` / `group_vars` 目录，ansible
默认会在存放 playbooks 或者 inventory 文件的目录下寻找这两个目录。而变量文件名应和相应的
host/group 名字一致。

例如：

- ansible 项目位于目录：/home/whoami/ansible
- inventory 文件：/home/whoami/ansible/inventory
- 则可以把 host_vars 或 group_vars 目录放在 /home/whoami/ansible

## 4.1 Defning Variables in Playbooks

在 playbook 中定义变量：

```yml
vars:
  a: aaa
  b: bbb
```

也可以使用

```yml
vars_files:
  - a.yml
  - b.yml
```

来引入其他 yml 文件中定义的变量

## 4.2 Registering Variables.md

当一个变量的值取决于某个 task 的返回值时，可以使用 register 来指定变量接收返回值。
这个返回值是一个字典，此时并不明确知道返回的字典结构是怎样的，这时可以借助 debug
来输出返回值。

访问 key 的方式：

{{ var.key_a }} 或 {{ var['key_a'] }}

`ignore_errors: True` 会让 ansible 在某个 task 失败的情况下继续执行下一个 task。

### 什么时候需要双引号？

当一个变量直接写在一个模块后面时，yaml 会错误地将变量解析为一个行内字典的开头。
例子：

```yml
# 错误，ansible 会尝试将 `{{ myapp }} -a foo` 中的 {{ myapp }} 解析为字典而不是字符串
- name: perform some task
  command: {{ myapp }} -a foo
# 正确
- name: perform some task
  command: "{{ myapp }} -a foo"
```

使用 debug 模块时，当字符串里面包含冒号，还需要：

```yml
- name: show a debug message
  debug: "msg='The debug module will print a message: neat, eh?'"
```

## 4.3 Facts

使用 setup 模块可以获取所有 facts 内容。

```sh
ansible hosts -m setup
```

使用 -a 'filter=<fact_name>' 可以指定输出某个 fact

## 4.4 Built-in Variables.md

### hostvars：字典，包含所有 host 的所有变量，使用 host 作为 key

例子：`{{ hostvars['db.example.com'].ansible_eth1.ipv4.address }}` 可以获取
db.example.com 的 eth1 网卡的 ipv4 地址，ansible 会以网卡名加上 ansible_
前缀来作为键名。同样地可以使用 debug 来输出需要的 hostvars 内容。

## 4.5 变量优先级

由低到高：

- role defaults
- inventory vars
- inventory group_vars
- inventory host_vars
- playbook group_vars
- playbook host_vars
- host facts
- registered vars
- set_facts
- play vars
- play vars_prompt
- play vars_files
- role and include vars
- block vars (only for tasks in block)
- task vars (only for the task)
- extra vars
- command line vars( -e var=<var_value>, or -e @<file_name>.yml)

## 6 Techniques.md

查看一个 playbook 包含什么 task

```sh
ansible-playbook --list-tasks <playbook_name>.yml 
```

```yml
- name: install apt packages
  apt: pkg={{ item }} update_cache=yes cache_valid_time=3600
  sudo: True
  with_items:
    - git
    - libjpeg-dev
    - libpq-dev
    - memcached
    - nginx
    - postgresql
    - python-dev
```

需要执行一些列相同动作时，比如批量安装一些依赖包。

有些模块会智能地使 ansible 将这些 items 一次性传给模块去处理，比如 apt，而 pip 模块就不会做这种处理。

### 敏感变量

可以放在某个 secret.yml 中，再用 vars_files 将变量包含进来。

## 7.1 Running a Task on the Other Machine

### 在控制机器运行任务：（local_action）

```yml
- name: wait for ssh server to be running
  local_action: command /usr/bin/add_back_to_pool {{ inventory_hostname }}
```

### 指派其他机器运行任务：（delegate_to）

## 7.2 Running on One Host at a Time.md

默认情况下，ansible 会并行地对每个 host 执行任务，有时想依次对一个 host 执行，可以使用
serial 语句，用数字做为参数指定一次运行几个 host 任务。当某个 host 的任务失败了，ansible
会继续执行下一个 host。可以使用 max_fail_percentage 语句来限制失败率，当失败率超这个数字ansible 将终止所有任务。

## 7.3 Dealing with Badly Behaved Commands: changed_when

failed_when: False （在任务失败时也不停止执行），可以在任务中使用 register 接收返回信息，并在后面继续一个 debug 任务用来查看失败信息

changed_when: 有些模块在运行某些未知命令时会一直返回 changed=false，这时就需要使用 changed_when 来自行进行判断，例如：

```yml
- name: initialize the database
  django_manage:
    command: createdb --noinput --nodata
    app_path: "{{ proj_path }}"
    virtualenv: "{{ venv_path }}"
  register: result
  changed_when: '"Creating tables" in result.out' 
# 即判断返回是否包含预期内容，从而任务的执行结果
```

## 7.4 Encrypting Sensitive Data with Vault

ansible-vault

加密文件的引入方法和普通文件一样，使用 vars_files 引入即可。但在执行 ansible-playbook
命令时需要加上 --ask-vault-pass 参数，或者指定存放密码的文件路径：`--vault-password-file <path_to_the_file>`。

## 7.5 Patterns for Specifying Hosts

ansible 支持以下模式匹配，和各种匹配的组合。

`ansible-playbook -l/--limit <host_pattern> playbook.yml` 可以指定运行某些  host

## 7.6 Filters.md

### The Default Filter

```yml
例如：
# 设置默认值
"HOST": "{{ database_host | default('localhost') }}" 
```

文件路径过滤器，可以用来获取一个路径中的目录、文件名等。

## 7.7 Lookups

从各种外部环境读取配置数据。

```tml
---
- hosts: all
  vars:
    contents: "{{ lookup('file', '/etc/foo.txt') }}"

  tasks:

    - debug: msg="the value of foo.txt is {{ contents }}"
```

## 7.8 More Complicated Loops.md

## 8.1 Basic Structure of a Role

roles 用于层次性、结构化地组织 playbook。 roles 能够根据层次型结构自动装载变量文件、tasks以及handlers等。

```dir
# Tasks
roles/database/tasks/main.yml
# Holds files to be uploaded to hosts
roles/database/fles/
# Holds Jinja2 template files
roles/database/templates/
# Handlers
roles/database/handlers/main.yml
# Variables that shouldn’t be overridden
roles/database/vars/main.yml
# Default variables that can be overridden
roles/database/defaults/main.yml
# Dependency information about a role
roles/database/meta/main.yml 
```

ansible 会在 playbook 同目录下寻找 roles 目录，也会在 /etc/ansible/roles（在 ansible.cfg 中设置） 中寻找。

## 8.2 Some Techniques

在调用 roles 的前后 执行某些任务

```yml
# pre_tasks / post_tasks
- name: deploy mezzanine on vagrant
  hosts: web
  vars_files:
    - secrets.yml
  pre_tasks:
    - name: update the apt cache
  apt: update_cache=yes
  roles:
    - role: ...
```

roles 中有两个地方可以定义变量，vars/main.yml 和 defaults/main.yml，前者优先级比在
play 中定义的变量高，这意味这 play 变量无法覆盖 vars/main.yml。defaults/main.yml
变量优先级比 play 变量低，当 roles 中的变量有改变的需要时，应该写在 defaults/main.yml 中

### task 在 play 和 role 中，使用 copy 或 template 模块的区别

在 role 里面时，ansible 会先从 `rolename/files` 或 `rolename/templates`
目录中寻找文件，这意味着在 play 中写的相对文件路径，在 role 中可以省掉目录前缀。

### ansible-galaxy

```sh
ansible-galaxy init -p playbooks/roles web
```

### Dependent Roles

当一些 role 有公共的任务时，可以把公共部分提取出来作为一个独立的 role，但当分别执行某些
role 时，可能忘了加入这个作为前提的公共 role，这时可以使用 依赖角色，写在
`roles/role_name/meta/main.yml` 里面

```yml
dependencies:
  - { role: ntp, ntp_server=ntp.ubuntu.com }
```

## 9 性能优化

- SSH 多路复用和持续控制
- 管道
- Facts 信息缓存
- 并行优化
- 加速模式
