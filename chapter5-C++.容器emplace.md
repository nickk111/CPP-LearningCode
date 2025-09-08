# C++11容器emplace方法原理剖析

* * *

本文讲解C++11中的`emplace`

**直接来看代码：** 有一个自定义的`Test`类

```C++
class Test
{
            
public:
	Test(int) {   cout << "Test(int)" << endl; }
	Test(int, int) { cout << "Test(int, int)" << endl; }
	~Test() {  cout << "~Test()" << endl; }
	Test(const Test&) {  cout << "Test(const Test&)" << endl; }
	Test(Test&&) { cout << "Test(Test&&)" << endl; }
};
```


直接插入对象，两个是没有区别的
```C++
int main()
{    
	Test t1(10);
	vector<Test> vec;
	vec.reserve(10);

	// 直接插入对象，两个是没有区别的
	cout << "=================" << endl;
	// 匹配的是带左值引用参数的拷贝构造函数
	vec.push_back(t1);
	vec.emplace_back(t1);
	cout << "=================" << endl;
	// 匹配的是带右值引用参数的拷贝构造函数
	vec.push_back(Test(20));
	vec.emplace_back(Test(20));
	cout << "=================" << endl;

	return 0;
}
```


运行结果：
```C++
Test(int)
=================
Test(const Test&)
Test(const Test&)
=================
Test(int)
Test(Test&&)
~Test()
Test(int)
Test(Test&&)
~Test()
=================
~Test()
~Test()
~Test()
~Test()
~Test()
```


上面些操作看起来这两种方法没什么区别，那现在直接传入所要构建对象的构造函数的参数试试：
```C++
int main()
{         
	vector<Test> vec;
	vec.reserve(10);

	cout << "=================" << endl;
	vec.push_back(20);
	// vec.push_back(20, 30);	// 报错了，push_back没有提供接受可变参的模板
	cout << "=================" << endl;
	vec.emplace_back(20);
	vec.emplace_back(20, 30);
	cout << "=================" << endl;

	return 0;
}
```


运行结果：
```C++
=================
Test(int)
Test(Test&&)
~Test()
=================
Test(int)
Test(int, int)
=================
~Test()
~Test()
~Test()
```


现在可以看出来有什么区别了吧！给`emplace`传入`Test`对象构造所需要的参数，会直接在容器底层构造，不会产生构造和析构临时对象的额外花销，效率大大提高。其余容器同理

* * *

**现在来实现一下其底层原理：**

```C++
class Test
{
            
public:
	Test(int) { cout << "Test(int)" << endl; }
	Test(int, int) { cout << "Test(int, int)" << endl; }
	~Test() { cout << "~Test()" << endl; }
	Test(const Test&) { cout << "Test(const Test&)" << endl; }
	Test(Test&&) { cout << "Test(Test&&)" << endl; }
};
// 空间配置器
template<typename T>
class MyAllocator
{        
public:
	// 内存开辟、释放
	T* allocate(size_t size) { return (T*)malloc(sizeof(T) * size); }
	void deallocate(void* p) { free(p); }

	// 对象构造、析构
	template<typename... Ty>
	void construct(T* p, Ty&&... args)
	{ 
		// 本例中是Test对象，args会完美转发，选择调用Test对象中不同的构造方式
		new (p) T(std::forward<Ty>(args)...);
	}
	void destroy(T* p) {  p->~T(); }
};

template<typename T, typename Alloc = MyAllocator<T>>
class vector
{
            
public:
	vector() :_vec(nullptr), _size(0), _idx(0) { }
	// 预留内存空间
	void reserve(size_t size)
	{
		_vec = _allocator.allocate(size);
		_size = size;
	}
	// push_back
	template<typename Ty>
	void push_back(Ty&& val)
	{  
		_allocator.construct(_vec + _idx, std::forward<Ty>(val));
		++_idx;
	}
//实参传一个左值 。你是不能用一个右值引用变量来引用一个左值的，  编辑器是不允许的
	// emplace_back   引用折叠、模板参数包
	template<typename... Ty>
	void emplace_back(Ty&&... args)
	{   
		_allocator.construct(_vec + _idx, std::forward<Ty>(args)...);
		++_idx;
	}
private:
	T* _vec;
	int _size;
	int _idx;
	Alloc _allocator;
};
```


`vector`中其余的功能，例如析构之类的没有实现，可以自己实现一下，这里主要写的是`emplace_back`方法和空间配置器中的`construct`方法，具体可以看上述代码，还是比较好理解的

此时再运行之前的两段`main`函数代码，可以看到构造的输出结果和预期的完全一致！
