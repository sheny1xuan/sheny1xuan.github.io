# ModernCpp-右值引用




## 右值引用：延长临时变量的生命周期，解决将亡值的问题

### 认识右值引用

+ 考虑如下一种情况，下面这样情况，由于x是一个临时变量，在代码块结束后，因为该变量生命周期结束，再使用其地址将会不安全，这里直接会出现segement fault，因为引用了错误的地址。
+ 这里解决方法有两个，可以选择将x定义在堆上，或者直接返回值。定义在堆上，如果管理不慎会出现内存泄露的问题。返回返回值又会产生额外的开销。

``` cpp
int& func1() {
    // x 是左值
    int x = 100;

    return x;
}
```

+ 所以cpp对左值和右值进行了区分。
  + 左值简单理解就是等号左边可以赋值的值，代表变量对内存有所有权(变量是内存的别名)，表达式结束后使用该变量的地址是安全的。
  + 右值是临时变量，表达式结束后就不存在的临时变量。右值又分为`将亡值`和`纯右值`。
  + 纯右值指的是纯粹字面量，求值的临时变量，匿名变量等等。注意字符串在类中是纯右值，普通函数中是左值。
  + `将亡值`是指的代码段结束后，即将被销毁，但是可以被移动的值，左值会在代码段结束后转换为将亡值。`func1`中的x在函数代码块运行中是一个左值，但是在函数结束后，他就是一个将亡值，代码段结束后他即将被销毁。将亡值只是一个概念，并不存在真正的将亡值，如果需要这个这个左值延长生命周期，则通过`std::move()`将左值转换为右值进行引用。

+ 通过右值引用可以延长`func1`中`x`的生命周期，但是需要通过`std::move()`将x转换为右值使用。这里`std::move()`只是将左值转换为右值，并没有智能指针中转交所有权的意思，被转换的变量仍可以调用这块内存。

``` cpp
int func2() {
    // x是左值
    int x = 100;

    return x;	
}

int&& y = func2();	// y会捕获x的将亡值，延长其生命周期
```

+ `右值引用`只可以引用右值，`std::move()`可以将左值转换为右值，从而延长临时变量的生命周期。左值会在代码段结束后变为将亡值。
+ `非常量左值引用`只能引用左值，`常量左值引用`可以引用右值。
+ 需要注意的是，一个变量虽然引用的是右值，但这个变量仍是一个左值，它不是一个临时对象，也不是纯粹的字面量。

``` cpp
    // 注意这里a和b虽然都是引用的右值，但是他们是左值
    int&& a = 2;

    const int& b = 2;
	int& b = 2; // error
```

### 实例

+ 两个string对象相加会产生临时的string对象。
+ 这里`std::move()`只是将左值转换为右值，并没有智能指针中转交所有权的意思，被转换的变量仍可以调用这块内存。

``` cpp
int main() {
    std::string lv1 = "string";     // 左值

    std::string&& rv1 = std::move(lv1);   // 临时lv1转换为右值，之后lv1仍是一个左值。
    // lv1与rv1共享内存

    lv1[0] = 'a';

    std::cout << rv1 << '\n';
    std::cout << lv1 << '\n';

    std::string&& lv2 = lv1 + lv1;  // lv1 + lv1 是一个右值，lv2可以引用右值。
    const std::string& lv3 = lv1 + lv2;   // 常量左值引用可以引用右值

    return 0;    
}

output:
    atring
    atring
```

### 右值引用与移动构造函数

+ 在C++11之前，对象存在构造函数主要有三种，默认构造函数，拷贝构造函数，赋值构造函数，但是这三种构造函数都不支持对临时值的引用。移动构造函数就是通过右值引用，使用临时对象构造新的对象，减少内存分配与释放的次数。

``` cpp
#include <iostream>
#include <vector>
#include <string.h>

class A {
    public:
        A(){
            std::cout << "A construct..." << std::endl;
            ptr_ = new int(100);
        }

        A(const A & a){
            std::cout << "A copy construct ..." << std::endl;
            ptr_ = new int();
            memcpy(ptr_, a.ptr_, sizeof(int));
        }
    
        A(A && a){
            std::cout << "A move construct ..." << std::endl;
            ptr_ = a.ptr_;
            // must set prev nullptr
            // prevent double free.
            a.ptr_ = nullptr;
        }

        ~A(){
            std::cout << "A deconstruct ..." << std::endl;
            if(ptr_){
                delete ptr_;
            }
        }

        A& operator=(const A & a) {
            std::cout << " A operator= ...." << std::endl;
            return *this;
        }

        int * getVal(){
            return ptr_;
        }
    private:
        int *ptr_;
};

int main(int argc, char *argv[]){
    std::vector<A> vec;
    vec.push_back(A());
}
```

### 右值引用的返回问题

##### 标准

``` cpp
std::vector<int> return_vector(void)
{
    std::vector<int> tmp {1,2,3,4,5};
    return tmp;
}

std::vector<int> rval_ref = return_vector(); // RVO/通过移动构造函数，构造一个新的对象。
```

+ 不需要将返回值转换为右值，在这个函数结束时，它将通过编译器优化为一个右值。
+ 不需要引用返回值。返回值首先会通过RVO进行优化，如果编译器不支持RVO，之后会调用移动构造函数，如果也不存在移动构造函数的话，则会调用拷贝构造函数构造该对象。

### 万能引用

+ 万能引用（Universal Reference）：可以接收左值也可以接收右值。
+ 它存在两种使用条件：一种是模板，另外一种是auto(auto也是也是模板)。**只有发生类型推导的时候，T&&才表示万能引用；** 否则，表示右值引用。

``` cpp
template<typename T>
void f(T&& param){
    std::cout << "the value is "<< param << std::endl;
}

for (auto&& x: v) {
    // 如果要修改值
}

for (const auto& x: v) {
    // 如果不修改值
}
```

### std::move

+ 强制类型转换：将左值转换为右值

```cpp
template <typename T>
typename remove_reference<T>::type&& move(T&& t) // 万能引用，可以引用左值，也能引用右值
{
    return static_case<typename remove_reference<T>::type&&>(t);
}
```

### 引用折叠

- `int & &` 折叠为 `int&`
- `int & &&` 折叠为 `int&`
- `int && &` 折叠为 `int&`
- `int && &&` 折叠为 `int &&`

### std::forward

+ 进行参数多次引用的传递，std::forward可以将原来传递的参数是左引用还是右引用进行区分。

### 参考资料:

+ modern-cpp-tutorial

+ [右值引用返回]:https://stackoverflow.com/questions/4986673/c11-rvalues-and-move-semantics-confusion-return-statement?utm_source=wechat_session&utm_medium=social&utm_oi=792314251669823488


+ [C++高阶知识：深入分析移动构造函数及其原理](http://avdancedu.com/a39d51f9/)
+ [C++中的万能引用和完美转发](https://shuntan.github.io/posts/%E5%AE%8C%E7%BE%8E%E8%BD%AC%E5%8F%91)
+ https://stackoverflow.com/questions/13130708/what-is-the-advantage-of-using-forwarding-references-in-range-based-for-loops
+ https://stackoverflow.com/questions/8399417/why-vectorboolreference-doesnt-return-reference-to-bool
+ https://zhuanlan.zhihu.com/p/161039484

