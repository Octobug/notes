# Process

- [Process](#process)
  - [Life Cycle](#life-cycle)
    - [进程终止的三种方式](#进程终止的三种方式)
      - [自然死亡](#自然死亡)
      - [自杀](#自杀)
      - [他杀](#他杀)

## Life Cycle

### 进程终止的三种方式

#### 自然死亡

通过 `return` 语句结束 `main` 函数。这种方法最安全也最优雅。

#### 自杀

进程自身调用某些 API 自我退出，如

- `exit()` (温和)
- `abort()` (激进)
- `terminate()` (默认调用 `abort()`)
- `unexpected()` (默认调用 `terminate()`)

#### 他杀

进程被其他进程杀死。通常是通过外部命令（如 `kill`） 实现。
