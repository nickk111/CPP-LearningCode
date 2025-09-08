# OOP经典设计模式

* * *

[TOC]

* * *

## 一、设计模式

设计模式是一种解决特定问题的预定义优秀代码框架，相较于自己摸索解决方案，它具有以下优点：

  1. **易维护** ：代码更易于维护，具有良好的可读性、复用性、可移植性和健壮性。

  2. **适应需求变化** ：设计模式的应用遵循 “开闭原则”（对修改关闭，对扩展开放），使得在需求变更或增加新功能时，能够灵活调整。

  3. **模块化设计** ：合理选择设计模式可以实现高内聚、低耦合的模块化设计，遵循软件设计的基本原则。

**设计模式的分类：**

  * **创建型模式** ：已关注于 **对象的创建** 过程，尝试将对象的创建与使用 **分离** ，以增加系统的灵活性和可维护性
  * **结构型模式** ：已关注于如何将 **类或对象组合** 成更大的结构，以解决更大的问题
  * **行为型模式** ：已关注于 **对象之间** 的交互和职责分配，以实现更好的系统行为和更灵活的协作

**23种设计模式：**

  * **创建型模式（5种）** ：单例模式（Singleton）、工厂方法模式（Factory Method）、抽象工厂模式（Abstract Factory）、建造者模式（Builder）、原型模式（Prototype）
  * **结构型模式（7种）** ：适配器模式（Adapter）、桥接模式（Bridge）、装饰器模式（Decorator）、组合模式（Composite）、外观模式（Facade）、享元模式（Flyweight）、代理模式（Proxy）
  * **行为型模式（11种）** ：模板方法模式（Template Method）、命令模式（Command）、迭代器模式（Iterator）、观察者模式（Observer）、中介者模式（Mediator）、备忘录模式（Memento）、访问者模式（Visitor）、状态模式（State）、策略模式（Strategy）、职责链模式（Chain of Responsibility）、解释器模式（Interpreter）

## 二、单例模式（创建型模式）

**单例模式** ：一个类不管创建多少次对象，永远只能得到该类类型的唯一一个实例对象，那么设计一个单例就必须要满足下面几个条件：

  1. **构造函数私有化** ：通过将构造函数私有化，防止外部直接创建实例，从而控制实例的创建
  2. **定义该类的唯一实例** ：在类内部定义一个该类的静态实例，并确保只有一个实例被创建
  3. **通过静态方法返回唯一实例** ：提供一个静态方法用于访问或获取这个唯一实例，确保每次调用返回相同的实例
  4. **删除拷贝构造和赋值运算符重载** ：防止通过拷贝构造函数或赋值操作符创建新的实例

**单例模式分类：**

  1. **饿汉式单例模式** ：
     - **特点** ：实例在 **类加载时就被创建** ，无论是否需要使用实例（实例对象是一个静态的成员变量，进程内存在数据段上，数据段的初始化在函数调用之前）
     - **优点** ：天然 **线程安全** ，因为实例在类加载过程中创建，不存在多线程访问问题
     - **缺点** ：即使没有使用实例，资源也会被占用，可能导致资源浪费

  2. **懒汉式单例模式** ：
     - **特点** ：实例在 **第一次访问时才被创建** ，采用延迟加载机制
     - **优点** ：延迟实例化，只有在需要时才创建实例，节省资源
     - **缺点** ： **线程不安全** ，需要处理多线程环境中的同步问题，以确保实例的唯一性，可能影响性能

**单例模式的应用场景举例：**

  * **日志模块** ：整个应用通常只需要一个日志模块实例，以统一管理日志的输出
  * **数据库模块** ：在客户端和服务器端之间进行通信时，使用单例模式可以确保只有一个数据库连接实例，从而减少资源消耗和连接管理的复杂性
  * **配置管理** ：应用程序中配置数据通常是全局的，并且需要统一访问，可以使用单例模式来管理
  * **线程池** ：使用单例模式可以确保只有一个线程池实例，便于统一管理和调度线程
  * **缓存** ：单例模式可以用于实现应用的全局缓存，以提高访问速度和性能

### 1.1 饿汉式单例模式

代码示例：
```C++
class Singleton
{
            
public:
	// 3. 提供一个静态方法返回唯一实例的引用
	static Singleton* getInstance() {  return &instance; }

private:
	static Singleton instance;	// 2. 定义该类的唯一实例对象（使用静态变量，在数据段上）
	Singleton() {  cout << "Singleton()" << endl; }	// 1.构造函数私有化
	~Singleton() {cout << "~Singleton()" << endl; }

	// 4. 删除拷贝构造和赋值函数
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

Singleton Singleton::instance;	// 类外初始化静态成员变量
```


测试用例：
```C++
int main()
{
            
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	Singleton* p3 = Singleton::getInstance();
	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	return 0;
}
```


测试结果：
```C++
Singleton()
B5E1C8
B5E1C8
B5E1C8
~Singleton()
```


可以看到，该程序通过饿汉式单例模式实现了单例的创建和管理，确保了整个程序中`Singleton`类只有一个实例。程序输出验证了单例模式的正确性，所有获取的引用都指向同一个实例

### 1.2 懒汉式单例模式

代码示例：
```C++
class Singleton
{
            
public:
	// 3. 提供一个静态方法返回唯一实例的引用
	static Singleton* getInstance()
	{
            
		if (nullptr == instance)
			instance = new Singleton();
		return instance;
	}
	// 提供一个方法用于销毁实例
	static void destroyInstance()
	{
            
		if (instance != nullptr)
		{
            
			delete instance;
			instance = nullptr;
		}
	}
private:
	static Singleton* instance;	// 2. 定义该类的唯一实例对象（使用静态变量）
	Singleton() {  cout << "Singleton()" << endl; }	// 1.构造函数私有化
	~Singleton() {  cout << "~Singleton()" << endl; }

	// 4. 删除拷贝构造和赋值函数
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

Singleton* Singleton::instance = nullptr;	// 类外初始化静态成员变量
```


测试用例：
```C++
int main()
{
            
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	Singleton* p3 = Singleton::getInstance();
	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	// 在程序结束前销毁实例
	Singleton::destroyInstance();
	return 0;
}
```


测试结果：
```C++
Singleton()
FC3E0
FC3E0
FC3E0
~Singleton()
```


### 1.3 线程安全的懒汉式单例模式

上面实现的懒汉式单例模式是有问题的，其中`getInstance`函数 **不是** 可重入函数，会有线程安全的问题

`getInstance`有三个步骤：开辟内存、构造对象、给`instance`赋值（编译器翻译成汇编指令的顺序或者也可以是开辟内存、给`instance`赋值、构造对象）

无论两种情况中的哪种，只要是线程一在给`instance`赋值之前，如果有线程二进入此函数，就会造成线程不安全。

临界区代码段我们要对其保证原子操作，改进一下：
```C++
std::mutex mtx;

class Singleton
{
            
public:
	// 3. 提供一个静态方法返回唯一实例的引用
	static Singleton* getInstance()
	{
            
		std::lock_guard<std::mutex> lock(mtx);
		if (nullptr == instance)
			instance = new Singleton();
		return instance;
	}
	...
};
```


这里还是有一些不妥，因为我们只考虑了多线程，没有考虑单线程的情况。现在锁的粒度就太大了，单线程的环境下也要频繁的加锁解锁

再次改进一下：
```C++
static Singleton* getInstance()
{     
	if (nullptr == instance)
	{
		// 锁 + 双重判断
		std::lock_guard<std::mutex> lock(mtx);
		if (nullptr == instance)
			instance = new Singleton();
	}
	return instance;
}
```


同时要注意，因为`instance`是一个指针在数据段，是同一个进程多个线程共享的内存，CPU在执行线程指令的时候为了加快指令的执行，会让线程把共享内存中的值拷贝到自己的线程缓存中

所以要给`instance`加一个`volatile`，这是给指针加的（不是给指针的指向加的）。好处是当一个线程对`instance`赋值时，其他线程马上均能看到`instance`的改变。因为线程现在已经不对共享变量进行缓存了，大家看的都是其原始内存中的值
```C++
class Singleton
{
            
private:
	static Singleton* volatile instance;
};

Singleton* volatile Singleton::instance = nullptr;	// 类外初始化静态成员变量
```


**再来看一种线程安全的懒汉式单例模式，这次不用互斥锁**

代码示例：
```C++
class Singleton
{
            
public:
	// 3. 提供一个静态方法返回唯一实例的引用
	static Singleton* getInstance()
	{
            
		static Singleton instance;	// 2. 定义该类的唯一实例对象（使用静态变量）
		return &instance;
	}
private:
	Singleton() {
             cout << "Singleton()" << endl; }	// 1.构造函数私有化
	~Singleton() {
             cout << "~Singleton()" << endl; }

	// 4. 删除拷贝构造和赋值函数
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};
```


**分析** ：静态对象第一次初始化是在第一次运行到它的时候，也就是当我们没有调用`getInstance`之前对象都不会构造的。而且通过在Linux中`g++ -o main main.cpp -g`调试到`getInstance`函数，观察底层汇编指令，我们可以发现， **函数静态局部变量的初始化在汇编指令上已经自动添加线程互斥指令了** ，也就是已经线程安全了！

测试用例：
```C++
int main()
{
            
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	Singleton* p3 = Singleton::getInstance();
	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	return 0;
}
```


测试结果：
```C++
Singleton()
C0E201
C0E201
C0E201
~Singleton()
```


## 三、工厂模式（创建型模式）

**工厂模式** 是一个比较常用的 **创建型** 设计模式，主要是封装了对象的创建，其中可以细分为三种： **简单工厂模式（Simple Factory）、工厂方法模式（Factory Method）、抽象工厂模式（Abstract Factory）**

  * **简单工厂模式：**

    * **定义** ：简单工厂模式只有一个工厂类，通过该工厂类的 **静态方法** 来创建具体的产品对象。工厂类根据不同的参数决定实例化哪一个产品类（简单工厂模式不属于标准OOP设计模式中的一项）
    * **适用场景** ：适用于 **产品种类较少且不经常扩展** 的场合。可以快速创建不同的产品对象，但扩展性有限
  * **工厂方法模式：**

    * **定义** ：工厂方法模式由一个抽象工厂类和多个具体工厂类组成。每个具体工厂类负责创建 **一个** 具体产品对象。通过继承抽象工厂类的方法，可以多态地创建不同的具体产品
    * **适用场景** ：适用于 **某个产品种类中包含多个具体产品** 的情况。能够通过增加新的工厂类来扩展产品系列
  * **抽象工厂模式：**

    * **定义** ：抽象工厂模式由一个抽象工厂类和多个具体工厂类组成，同时 **有 多个产品接口或抽象类**。每个具体工厂类可以 **创建一组相关的产品对象**
    * **适用场景** ：适用于涉及多个产品种类的复杂系统，可以创建一组相关或依赖的产品对象。适合于需要创建多个系列产品的情况

**工厂方法与抽象工厂区别** ：工厂方法模式只有一个抽象产品类，而抽象工厂模式有多个。 工厂方法模式的具体工厂类只能创建一个具体产品类的实例，而抽象工厂模式可以创建多个。因此， **工厂方法模式可以被视为抽象工厂模式的一个特例或简化形式**

### 3.1 简单工厂模式


```C++
class Car
{
            
public:
	Car(string name) : _name(name) { }
	virtual void show() = 0;
protected:
	string _name;
};

class Bmw : public Car
{
            
public:
	Bmw(string name) : Car(name) { }
	void show() override {cout << "宝马：" << _name << endl; }
};

class Audi : public Car
{
            
public:
	Audi(string name) : Car(name) {  }
	void show() override { cout << "奥迪：" << _name << endl; }
};

enum CarType
{        
	BMW, AUDI
};

class SimpleFactory
{       
public:
	static Car* createCar(CarType ct)
	{   
		switch (ct)
		{
		case BMW:
			return new Bmw("X3");
		case AUDI:
			return new Audi("A8");
		default:
			cerr << "传入参数不正确" << endl;
			return nullptr;
		}
	}
};

int main()
{
            
	// Car* p1 = SimpleFactory::createCar(BMW);
	// Car* p2 = SimpleFactory::createCar(AUDI);
	// if (p1) p1->show();
	// if (p2) p2->show();
	// delete p1;
	// delete p2;

	// 改成智能指针，自动释放资源
	unique_ptr<Car> p1(SimpleFactory::createCar(BMW));
	unique_ptr<Car> p2(SimpleFactory::createCar(AUDI));
//
unique_ptr<SimpleFactory> factory (new SimpleFactory());
unique_ptr<Car> p1 (factory->createCar(BMW));
unique_ptr<Car> p2 (factory->createCar(AUDI)); 
 //
	if (p1) p1->show();
	if (p2) p2->show();

	return 0;
}
```


现在，简单工厂模式就实现了，但是这种方法有一些缺陷，因为同一个工厂不会又造宝马又造奥迪，又造手机又造键盘的，这一般不符合实际的情况，而且最重要的是这个工厂 **不符合“开闭原则”** ，如果我们要增删车辆，就要修改接口，这样很不好。

基于这样的缺陷，接下来看看工厂方法模式

### 3.2 工厂方法模式


```C++
// 产品和上面一样
class Car {  ... };
class Bmw : public Car  {  ... };
class Audi : public Car  {   ... };

// 工厂方法
class Factory
{
            
public:
	virtual Car* createCar(string name) = 0; // 工厂方法
};
// 宝马工厂
class BMWFactory : public Factory
{
            
public:
	Car* createCar(string name) override {return new Bmw(name); }
};
// 奥迪工厂
class AudiFactory : public Factory
{
            
public:
	Car* createCar(string name) override { return new Audi(name); }
};

int main()
{
            
	unique_ptr<Factory> bmwfty(new BMWFactory());
	unique_ptr<Factory> audifty(new AudiFactory());

	unique_ptr<Car> p1(bmwfty->createCar("X6"));
	unique_ptr<Car> p2(audifty->createCar("A8"));
	p1->show();
	p2->show();

	return 0;
}
```


现在 **符合“开闭原则”** ，如果现在想加一个奔驰工厂，直接增加`BenzFactory`类就行了

### 3.3 抽象工厂模式


```C++
class Car {
            
public:
	virtual void show() = 0;
};

class Engine {
            
public:
	virtual void type() = 0;
};
// ===================================================
class BMWCar : public Car {
            
public:
	void show() override { cout << "BMW car" << endl; }
};

class BMWEngine : public Engine {
            
public:
	void type() override { cout << "BMW engine" << endl; }
};
// ===================================================
class AudiCar : public Car {
            
public:
	void show() override { cout << "Audi car" << endl; }
};

class AudiEngine : public Engine {
            
public:
	void type() override { cout << "Audi engine" << endl; }
};
// ===================================================
class AbstractFactory {
            
public:	// 产品簇
	virtual Car* createCar() = 0;
	virtual Engine* createEngine() = 0;
};

class BMWFactory : public AbstractFactory {
            
public:
	Car* createCar() override { return new BMWCar(); }
	Engine* createEngine() override { return new BMWEngine(); }
};

class AudiFactory : public AbstractFactory {
            
public:
	Car* createCar() override { return new AudiCar(); }
	Engine* createEngine() override { return new AudiEngine(); }
};
// ===================================================
int main()
{
            
	// 创建具体工厂
	unique_ptr<AbstractFactory> bmwfty(new BMWFactory());
	unique_ptr<AbstractFactory> audifty(new AudiFactory());

	// 使用工厂创建产品
	unique_ptr<Car> bmwCar(bmwfty->createCar());
	unique_ptr<Engine> bmwEngine(bmwfty->createEngine());
	unique_ptr<Car> audiCar(audifty->createCar());
	unique_ptr<Engine> audiEngine(audifty->createEngine());

	// 调用产品方法
	if (bmwCar) bmwCar->show();
	if (bmwEngine) bmwEngine->type();
	if (audiCar) audiCar->show();
	if (audiEngine) audiEngine->type();

	return 0;
}
```


## 四、代理模式（结构型模式）

**代理模式** ：通过一个代理对象来控制实际对象的访问权限

> 例如： **客户 ↔ 助理（代理）↔ 老板（委托类：实际对象）**

**代码示例：**

```C++
// 抽象类：视频站点
class VideoSite
{
            
public:
	virtual void freeMovie() = 0;	// 免费电影
	virtual void vipMovie() = 0;	// VIP电影
	virtual void ticketMovie() = 0; // 用券观看电影
	virtual ~VideoSite() = default; // 虚析构函数以确保派生类正确析构
};

// 委托类：实际对象（IQIYI 视频站点）
class IQIYIVideoSite : public VideoSite
{
            
public:
	virtual void freeMovie() { cout << "观看免费电影" << endl; }
	virtual void vipMovie() { cout << "观看VIP电影" << endl; }
	virtual void ticketMovie() { cout << "用券观看电影" << endl; }
};

// 代理类：免费用户代理
class FreeProxy : public VideoSite
{
            
public:
	FreeProxy() {  Video = new IQIYIVideoSite(); }
	~FreeProxy() {  delete Video; }

	// 通过代理类中重写的方法，来访问真正委托类的方法
	virtual void freeMovie() { Video->freeMovie(); }
	virtual void vipMovie() {  cout << "您目前只是普通游客，需要升级成VIP，才能观看VIP电影" << endl; }
	virtual void ticketMovie() {cout << "您目前没有券，需要购买电影券，才能观看电影" << endl; }
private:
	VideoSite* Video; // 持有实际对象的指针
};

// 代理类：VIP用户代理
class VipProxy : public VideoSite
{
            
public:
	VipProxy() {  Video = new IQIYIVideoSite(); }
	~VipProxy() { delete Video; }

	// 通过代理类中重写的方法，来访问真正委托类的方法
	virtual void freeMovie() {  Video->freeMovie(); }
	virtual void vipMovie() {  Video->vipMovie(); }
	virtual void ticketMovie() { cout << "您目前没有券，需要购买电影券，才能观看电影" << endl; }
private:
	VideoSite* Video; // 持有实际对象的指针
};

// 代理类：使用电影券用户代理
class TicketProxy : public VideoSite 
{
            
public:
	TicketProxy() { Video = new IQIYIVideoSite(); }
	~TicketProxy() { delete Video; }

	// 通过代理类中重写的方法，来访问真正委托类的方法
	virtual void freeMovie() {  Video->freeMovie(); }
	virtual void vipMovie() { Video->vipMovie(); }
	virtual void ticketMovie() { Video->ticketMovie(); }
private:
	VideoSite* Video; // 持有实际对象的指针
};

// 这些都是通用的API接口，使用的都是基类的指针或者引用
void watchMovie(unique_ptr<VideoSite>& ptr) 
{      
	ptr->freeMovie();
	ptr->vipMovie();
	ptr->ticketMovie();
}

int main() {
            
	unique_ptr<VideoSite> p1(new FreeProxy);   // 创建免费用户代理对象
	unique_ptr<VideoSite> p2(new VipProxy);    // 创建VIP用户代理对象
	unique_ptr<VideoSite> p3(new TicketProxy); // 创建使用电影券用户代理对象

	watchMovie(p1); // 观看电影，使用免费用户代理
	cout << "===================" << endl;
	watchMovie(p2); // 观看电影，使用VIP用户代理
	cout << "===================" << endl;
	watchMovie(p3); // 观看电影，使用电影券用户代理

	return 0;
}
```

**运行结果：**

```shell
观看免费电影
您目前只是普通游客，需要升级成VIP，才能观看VIP电影
您目前没有券，需要购买电影券，才能观看电影
===================
观看免费电影
观看VIP电影
您目前没有券，需要购买电影券，才能观看电影
===================
观看免费电影
观看VIP电影
用券观看电影
```


## 五、装饰器模式（结构型模式）

**装饰器模式** ：可以动态地添加行为到对象中，而不需要修改类的定义

**目的** ： 为了增强现有类的功能

为了增强现有类的功能，通过实现子类的方式，重写接口，是可以完成功能扩展的，但是代码中有太多的子类添加进来了。

**关键参与者：**

  * **Component（组件）** ：定义一个对象接口，可以给这些对象动态地添加职责
  * **ConcreteComponent（具体组件）** ：实现了组件接口的类
  * **Decorator（装饰器）** ：持有一个组件对象的引用或指针，定义一个与组件接口一致的接口，并且将所有请求委托给该组件对象
  * **ConcreteDecorator（具体装饰器）** ：扩展装饰器功能的类，实现额外的行为

**代码示例（普通指针版本）：**

```C++
// 抽象基类（组件）
class Car
{      
public:
    virtual void show() = 0;
    virtual ~Car() = default; // 虚析构函数
};

// 三种汽车（具体组件）
class Bmw : public Car
{
            
public:
    void show() override { cout << "这是一辆宝马汽车，配置有：基本配置"; }
};

class Audi : public Car
{
            
public:
    void show() override { cout << "这是一辆奥迪汽车，配置有：基本配置"; }
};

class Benz : public Car
{        
public:
    void show() override { cout << "这是一辆奔驰汽车，配置有：基本配置"; }
};
// 装饰器基类
class CarDecorator : public Car
{       
public:
    CarDecorator(Car* car) : pCar(car) {  }
    virtual ~CarDecorator() { delete pCar; } // 确保释放被装饰的对象
protected:
    Car* pCar;
};
// 装饰器1：定速巡航
class CruiseControl : public CarDecorator
{       
public:
    CruiseControl(Car* car) : CarDecorator(car) {  }
    void show() override
    {     
        pCar->show();
        cout << ", 定速巡航";
    }
};

// 装饰器2：自动刹车
class AutoBrake : public CarDecorator
{       
public:
    AutoBrake(Car* car) : CarDecorator(car) {  }
    void show() override
    {    
        pCar->show();
        cout << ", 自动刹车";
    }
};
// 装饰器3：车道偏离
class LaneDepartureWarning : public CarDecorator
{        
public:
    LaneDepartureWarning(Car* car) : CarDecorator(car) {  }
    void show() override
    {    
        pCar->show();
        cout << ", 车道偏离";
    }
};

int main()
{       
    Car* bmw = new Bmw();
    Car* p1 = new CruiseControl(bmw);
    p1 = new AutoBrake(p1);
    p1 = new LaneDepartureWarning(p1);
    p1->show();
    cout << endl;
    delete p1; // 确保释放内存

    Car* audi = new Audi();
    Car* p2 = new AutoBrake(audi);
    p2->show();
    cout << endl;
    delete p2; // 确保释放内存

    Car* benz = new Benz();
    Car* p3 = new LaneDepartureWarning(benz);
    p3->show();
    cout << endl;
    delete p3; // 确保释放内存

    return 0;
}
```

**代码示例（智能指针版本）：**

```C++
// 抽象基类（组件）
class Car
{
            
public:
	virtual void show() = 0;
	virtual ~Car() = default; // 添加虚析构函数
};

// 三种汽车（具体组件）
class Bmw : public Car
{
            
public:
	void show() override {cout << "这是一辆宝马汽车，配置有：基本配置"; }
};

class Audi : public Car
{
            
public:
	void show() override { cout << "这是一辆奥迪汽车，配置有：基本配置"; }
};

class Benz : public Car
{
            
public:
	void show() override { cout << "这是一辆奔驰汽车，配置有：基本配置"; }
};

// 装饰器基类
class CarDecorator : public Car
{
            
public:
	CarDecorator(shared_ptr<Car> car) : pCar(car) { }
	virtual void show() = 0; // 纯虚函数，必须由子类实现
protected:
	shared_ptr<Car> pCar;
};

// 装饰器1：定速巡航
class CruiseControl : public CarDecorator
{
            
public:
	CruiseControl(shared_ptr<Car> car) : CarDecorator(car) { }
	void show() override
	{  
		pCar->show();
		cout << ", 定速巡航";
	}
};

// 装饰器2：自动刹车
class AutoBrake : public CarDecorator
{
            
public:
	AutoBrake(shared_ptr<Car> car) : CarDecorator(car) {}
	void show() override
	{  
		pCar->show();
		cout << ", 自动刹车";
	}
};

// 装饰器3：车道偏离
class LaneDepartureWarning : public CarDecorator
{
            
public:
	LaneDepartureWarning(shared_ptr<Car> car) : CarDecorator(car) { }
	void show() override
	{   
		pCar->show();
		cout << ", 车道偏离";
	}
};

int main()
{
            
	shared_ptr<Car> p1 = make_shared<CruiseControl>(make_shared<Bmw>());
	p1 = make_shared<AutoBrake>(p1);
	p1 = make_shared<LaneDepartureWarning>(p1);
	p1->show();
	cout << endl;

	shared_ptr<Car> p2 = make_shared<AutoBrake>(make_shared<Audi>());
	p2->show();
	cout << endl;

	shared_ptr<Car> p3 = make_shared<LaneDepartureWarning>(make_shared<Benz>());
	p3->show();
	cout << endl;

	return 0;
}
```

**运行结果：**

```shell
这是一辆宝马汽车，配置有：基本配置, 定速巡航, 自动刹车, 车道偏离
这是一辆奥迪汽车，配置有：基本配置, 自动刹车
这是一辆奔驰汽车，配置有：基本配置, 车道偏离
```


## 六、适配器模式（结构型模式）

**适配器模式** ：使不兼容的接口能够一起工作

电源转换插头、HDMI转VGA的线，这些都是适配器模式在生活中的例子

**代码示例：**

```C++
// VGA 接口类
class VGA
{
            
public:
	virtual void play() = 0;
	virtual ~VGA() = default;
};

// 具体的 VGA 投影仪
class VGAProjector : public VGA
{
            
public:
	void play() override {  cout << "通过 VGA 接口连接投影仪，进行视频播放" << endl; }
};

// HDMI 接口类
class HDMI
{
            
public:
	virtual void play() = 0;
	virtual ~HDMI() = default;
};

// 具体的 HDMI 投影仪
class HDMIProjector : public HDMI
{
            
public:
	void play() override { cout << "通过 HDMI 接口连接投影仪，进行视频播放" << endl; }
};

// 适配器类，将 VGA 接口转换为 HDMI 接口
class VGAToHDMIAdapter : public VGA
{
            
public:
	VGAToHDMIAdapter(HDMI* p) : pHdmi(p) { }
//该方法相当于转换头，做不同接口的信号的转换的
	void play() override {pHdmi->play(); }
private:
	HDMI* pHdmi;
};

// 电脑类，只支持 VGA 接口
class Computer
{
            
public:
//由于电脑只支持VGA接口，所以该方法参数也只能支持VGA接口的指针/引用
	void playVideo(VGA* pVGA) {  pVGA->play(); }
};

int main() {
            
	// 创建 Computer 对象
	Computer* computer = new Computer();

	// 通过 VGA 接口连接投影仪
	VGAProjector* vgaProjector = new VGAProjector();
	computer->playVideo(vgaProjector);

	// 通过 HDMI 接口连接投影仪，使用适配器
	HDMIProjector* hdmiProjector = new HDMIProjector();
	VGAToHDMIAdapter* adapter = new VGAToHDMIAdapter(hdmiProjector);
	computer->playVideo(adapter);

	// 手动释放所有动态分配的内存
	delete adapter;
	delete hdmiProjector;
	delete vgaProjector;
	delete computer;

	return 0;
}
```

**运行结果：**

```shell
通过 VGA 接口连接投影仪，进行视频播放
通过 HDMI 接口连接投影仪，进行视频播放
```

### 桥接模式

桥接模式是设计模式中的一种结构型模式。它的主要目的是将抽象部分与其实现部分分离，使它们可以独立地变化。这种模式通过提供一个桥接结构，将抽象和实现分别放在两个不同的类层次中，这样在抽象层中可以避免因实现细节的变化而改变。

## 七、观察者模式（行为型模式）

**观察者模式** ，又名 **发布-订阅模式** 或 **事件监听器模式** ，主要已关注对象之间的 **一对多** 依赖关系。当一个对象（称为主题或被观察者）的状态发生改变时，所有依赖于它的对象（称为观察者）都会收到通知并自动更新

**代码示例：**

```C++
// 观察者抽象类
class Observer
{         
public:
	// 处理消息的接口
	virtual void handle(int msgid) = 0;
	virtual ~Observer() = default;
};

// 第一个观察者实例：对消息1和消息2感兴趣
class Observer1 : public Observer
{
            
public:
	void handle(int msgid) override
	{
            
		switch (msgid)
		{
            
		case 1:
			cout << "Observer1 received message 1" << endl;
			break;
		case 2:
			cout << "Observer1 received message 2" << endl;
			break;
		default:
			cout << "Observer1 received unknown message" << endl;
			break;
		}
	}
};

// 第二个观察者实例：对消息2感兴趣
class Observer2 : public Observer
{
            
public:
	void handle(int msgid) override
	{   
		if (msgid == 2)
		{
			cout << "Observer2 received message 2" << endl;
		}
		else {
			cout << "Observer2 received unknown message" << endl;
		}
	}
};
// 第三个观察者实例：对消息1和消息3感兴趣
class Observer3 : public Observer
{
            
public:
	void handle(int msgid) override
	{
            
		switch (msgid)
		{
            
		case 1:
			cout << "Observer3 received message 1" << endl;
			break;
		case 3:
			cout << "Observer3 received message 3" << endl;
			break;
		default:
			cout << "Observer3 received unknown message" << endl;
			break;
		}
	}
};

// 主题类
class Subject {
            
public:
	// 添加观察者
	void addObserver(Observer* observer, int msgid)
	{     		observers[msgid].push_back(observer);
    auto it = _subMap.find(msgid);
     if(it != _subMap.end())
     {
         it->second.push_back(obser);
     }
     else
     {
         list<Observer*> lis;
         lis.push_back(obser);
         _subMap.insert({msgid,lis});
     }
	}

	// 通知观察者
	void notifyObservers(int msgid)
	{   
		auto it = observers.find(msgid);
		if (it != observers.end())
			for (Observer* observer : it->second)
				observer->handle(msgid);

	}

private:
	unordered_map<int, list<Observer*>> observers; // 观察者列表，按消息ID分类
};

int main() {
            
	Subject subject;
	Observer* p1 = new Observer1();
	Observer* p2 = new Observer2();
	Observer* p3 = new Observer3();

	// 注册观察者到不同的消息ID
	subject.addObserver(p1, 1);
	subject.addObserver(p1, 2);
	subject.addObserver(p2, 2);
	subject.addObserver(p3, 1);
	subject.addObserver(p3, 3);

	int msgid = 0;

	while (true)
	{
            
		cout << "输入消息ID (-1 退出): ";
		cin >> msgid;
		if (msgid == -1)
			break;
		subject.notifyObservers(msgid);
	}

	// 清理内存
	delete p1;
	delete p2;
	delete p3;

	return 0;
}
```

**运行结果：**

```shell
输入消息ID (-1 退出): 1
Observer1 received message 1
Observer3 received message 1
输入消息ID (-1 退出): 2
Observer1 received message 2
Observer2 received message 2
输入消息ID (-1 退出): 3
Observer3 received message 3
输入消息ID (-1 退出): -1
```



---

