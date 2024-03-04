# Singleton

- [Singleton](#singleton)
  - [CoolShell](#coolshell)
    - [Singleton 的教学版本](#singleton-的教学版本)
    - [Singleton 的实际版本](#singleton-的实际版本)
    - [Singleton 的简化版本](#singleton-的简化版本)
    - [Singleton 优雅版本](#singleton-优雅版本)
    - [Singleton 的其它问题](#singleton-的其它问题)

这个设计模式的目的是使整个系统中只能出现一个类的实例。

## CoolShell

> <https://coolshell.org/articles/265.html>

### Singleton 的教学版本

```java
// version 1.0
public class Singleton {
    private static Singleton singleton = null;
    private Singleton() { }
    public static Singleton getInstance() {
        if (singleton == null) {
            singleton = new Singleton();
        }
        return singleton;
    }
}
```

1. 私有的构造函数，表明这个类不可能形成实例。
2. 需要一个静态的方式让其形成实例：`getInstance()`。这个方法是在 `new` 自己，因为其可以访问私有的构造函数。
3. 在 `getInstance()` 中，先做判断是否已形成实例，如果已形成则直接返回，否则创建实例。
4. 所形成的实例保存在自己类中的私有成员中。
5. 取实例时，只需要使用 `Singleton.getInstance()` 就行了。

### Singleton 的实际版本

上面这个程序存在比较严重的问题，因为是全局性的实例，所以，在多线程情况下，所有全局共享的东西都会变得非常危险。如果多个线程同时调用 `getInstance()` 的话，可能会有多个线程同时通过
`(singleton == null)` 的条件检查而创建多个实例出来，并且很可能造成内存泄露问题。“我们需要线程互斥或同步”：

```java
// version 1.1
public class Singleton
{
    private static Singleton singleton = null;
    private Singleton() { }
    public static Singleton getInstance() {
        if (singleton == null) {
            synchronized (Singleton.class) {
                singleton = new Singleton();
            }
        }
        return singleton;
    }
}
```

但是，这还是有问题！如果有多个线程同时通过 `(singleton == null)` 的条件检查，`synchronized` 只是帮助我们同步所有的线程，让并行的线程变成串行的一个一个去 `new`，因此同样会出现很多实例。看来，还得把 `(singleton == null)` 也同步起来：

```java
// version 1.2
public class Singleton
{
    private static Singleton singleton = null;
    private Singleton() { }
    public static Singleton getInstance() {
        synchronized (Singleton.class) {
            if (singleton== null) {
                singleton = new Singleton();
            }
        }
        return singleton;
    }
}
```

这个版本在多线程下的确没有问题了，因为同步了所有的线程。然而，本来只是想让 `new` 这个操作并行，现在，只要是进入 `getInstance()` 的线程都得同步。创建对象的动作只有一次，后面的动作全是读取那个成员变量，而理想情况下这些读取动作不应该线程同步。

在线程同步前加一个 `(singleton == null)` 的条件判断，如果对象已经创建了，那么就不需要线程的同步了：

```java
// version 1.3
public class Singleton
{
    private static Singleton singleton = null;
    private Singleton() { }
    public static Singleton getInstance() {
        if (singleton == null) {
            synchronized (Singleton.class) {
                if (singleton == null) {
                    singleton= new Singleton();
                }
            }
        }
        return singleton;
    }
}
```

这个版本又叫“双重检查”Double-Check。

1. 如果实例创建了，那就不需要同步了，直接返回实例。
2. 否则开始同步线程。
3. 如果被同步的线程中，有一个线程创建了对象，那么别的线程就不用再创建了。

然而，还是存在问题：`singleton = new Singleton()` 并非是一个原子操作，事实上在 JVM 中这句话大概做了下面 3 件事情：

1. 给 `singleton` 分配内存
2. 调用 `Singleton` 的构造函数来初始化成员变量，形成实例
3. 将 `singleton` 对象指向分配的内存空间

在 JVM 的即时编译器中存在指令重排序的优化，也就是说上面的第二步和第三步的顺序是不能保证的，最终的执行顺序可能是 1-2-3 也可能是 1-3-2。如果是后者，则在 3 执行完毕、2 未执行时，被线程二抢占了，这时 `instance` 已经是非 `null` 了（但却没有初始化），所以线程二会直接返回 `instance`，然后使用，然后顺理成章地报错。

对此，需要把 `singleton` 声明成 `volatile`：

```java
// version 1.4
public class Singleton
{
    private volatile static Singleton singleton = null;
    private Singleton() { }
    public static Singleton getInstance() {
        if (singleton == null) {
            synchronized (Singleton.class) {
                if (singleton == null)  {
                    singleton = new Singleton();
                }
            }
        }
        return singleton;
    }
}
```

使用 `volatile` 有两个功用：

1. 这个变量不会在多个线程中存在复本，直接从内存读取。
2. 这个关键字会禁止指令重排序优化。也就是说，在 `volatile` 变量的赋值操作后面会有一个内存屏障，读操作不会被重排序到内存屏障之前。

但是，这个特性仅在 Java 1.5 版后有用，1.5 版之前用这个变量也有问题，因为老版本的 Java 的内存模型是有缺陷的。

### Singleton 的简化版本

单例的实例可以被声明成 static 和 final 变量，在第一次加载类到内存中时就会初始化，所以创建实例本身是线程安全的。

```java
// version 1.5
public class Singleton
{
    private volatile static Singleton singleton = new Singleton();
    private Singleton()  { }
    public static Singleton getInstance() {
        return singleton;
    }
}
```

当这个类被加载的时候，`new Singleton()` 这句话就会被执行，就算是 `getInstance()` 没有被调用，类也被初始化了。

这个可能会与我们想要的行为不一样。比如，在类的构造函数中，有一些事可能需要依赖于别的类，我们希望它能在第一次 `getInstance()` 时才被真正创建。这样可以控制真正的类创建的时刻，而不是把类的创建委托给类装载器。

下面的 1.6 版是老版《Effective Java》中推荐的方式。

```java
// version 1.6
public class Singleton {
    private static class SingletonHolder {
        private static final Singleton INSTANCE = new Singleton();
    }
    private Singleton (){ }
    public static final Singleton getInstance() {
        return SingletonHolder.INSTANCE;
    }
}
```

这种方式使用 JVM 本身机制保证了线程安全问题；由于 `SingletonHolder` 是私有的，除了 `getInstance()` 之外没有办法访问它，因此它只有在 `getInstance()` 被调用时才会真正创建；同时读取实例的时候不会进行同步，没有性能缺陷；也不依赖 JDK 版本。

### Singleton 优雅版本

```java
public enum Singleton {
   INSTANCE;
}
```

通过 `Singleton.INSTANCE` 来访问，这比调用 `getInstance()` 方法简单多了。

默认枚举实例的创建是线程安全的，所以不需要担心线程安全的问题。但是在枚举中的其他任何方法的线程安全由程序员自己负责。还有防止上面的通过反射机制调用私用构造器。

这个版本基本上消除了绝大多数的问题。这也是新版的《Effective Java》中推荐的模式。

### Singleton 的其它问题

其一、`Class Loader` 是 Java 动态性的核心。顾名思义，类装载器是用来把类装载进 JVM 的。JVM 规范定义了两种类型的类装载器：

- 启动内装载器 (bootstrap)
- 用户自定义装载器 (user-defined class loader)

在一个 JVM 中可能存在多个 `ClassLoader`，每个 `ClassLoader` 拥有自己的 `NameSpace`。一个 `ClassLoader` 只能拥有一个 `class` 对象类型的实例，但是不同的 `ClassLoader` 可能拥有相同的 `class` 对象实例，这时可能产生致命的问题。

如 `ClassLoaderA`，装载了类 `A` 的实例 `A1`，而 `ClassLoaderB`，也装载了类 `A` 的实例 `A2`。逻辑上讲 `A1 = A2`，但是由于 `A1` 和 `A2` 来自于不同的 `ClassLoader`，它们实际上是完全不同的，如果 `A` 中定义了一个静态变量 `c`，则 `c` 在不同的 `ClassLoader` 中的值是不同的。

于是，Singleton 1.3 版本如果面对着多个 `Class Loader` 会怎么样？多个实例同样会被多个`Class Loader` 创建出来。

其二、序例化。如果 Singleton 类是一个关于程序配置信息的类。我们需要它有序列化的功能，那么，当反序列化的时候，将无法控制别人不多次反序列化。不过，可以利用 `Serializable` 接口的
`readResolve()` 方法，比如：

```java
public class Singleton implements Serializable
{
    ......
    ......
    protected Object readResolve()
    {
        return getInstance();
    }
}
```

其三、多个 Java 虚拟机。如果程序运行在多个 Java 的虚拟机中，比如 EJB 或 RMI 之流的东西。要在这种环境下避免多实例，只能通过良好的设计或非技术来解决了。

其四，`volatile` 变量。关于 `volatile` 这个关键字所声明的变量可以被看作是一种“程度较轻的同步 `synchronized`”；与 `synchronized` 块相比，`volatile` 变量所需的编码较少，并且运行时开销也较少，但是它所能实现的功能也仅是 `synchronized` 的一部分。

其五、关于继承。继承于 Singleton 后的子类也有可能造成多实例的问题。不过，因为 Singleton 的构造函数声明成了私有的，所以也就杜绝了继承这种事情。

其六，关于代码重用。系统中可能有很多个类需要用到这个模式，是否可以使用一种方法，把这具模式抽象出去？在 C++ 下是很容易的，因为有模板和友元，还支持栈上分配内存，所以比较容易一些。程序如下：

```cpp
template class Singleton
{
    public:
        static T& Instance()
        {
            static T theSingleInstance; // 假设 T 有一个 protected 默认构造函数
            return theSingleInstance;
        }
};

class OnlyOne: public Singleton
{
    friend class Singleton;
    int example_data;

    public:
        int GetExampleData() const {return example_data;}
    protected:
        OnlyOne(): example_data(42) {}   // 默认构造函数
        OnlyOne(OnlyOne&) {}
};

int main( )
{
    cout << OnlyOne::Instance().GetExampleData() << endl;
    return 0;
}
```
