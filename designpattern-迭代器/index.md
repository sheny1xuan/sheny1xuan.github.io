# DesignPattern-迭代器




### 迭代器模式

+ 对于一个容器提供一种方法顺序访问容器中的各个元素，而不必暴露该对象的内部表示。
+ 常常使用的方法有:`next()`下一个元素，`hasNext()`是否有下一个元素，`isend()`是否遍历完成，`Current()`当前元素等等方法。
+ 如果抽象基类的虚函数没有被完全实现的话，不能定义派生类函数，否则会报错`invalid new-expression of abstract class type`

+ 一个简单的以`vector`为容器的`string `迭代器。

``` cpp
/*
 * @Descripttion: Iterator
 * @version: 
 * @Author: Stonex
 * @Date: 2021-10-05 15:06:04
 * @LastEditTime: 2021-10-05 16:04:47
 */
#include <iostream>
#include <vector>

/**
 * @name: base class
 */
class Iterator {
    public:
        Iterator() {};
        ~Iterator() {};

        virtual std::string First() = 0;
        virtual std::string Next() = 0;
        virtual std::string Current() = 0;
        virtual bool isEnd() = 0;
};

/**
 * @name: base Objuct
 */
class Object {
    public:
        Object() {};
        ~Object() {};
    virtual Iterator* createIterator() = 0;
    virtual int Count() = 0;
    virtual void Push(std::string) = 0;
    virtual std::string Get(int) = 0;
};

class subIterator: public Iterator {
    public:
        subIterator(Object* obj_):Iterator(), obj(obj_), cur(0){}
        ~subIterator() {}
        std::string First() {
            return obj->Get(0);
        }
        std::string Next() {
            if(cur < obj->Count() - 1) {
                cur += 1;
                return obj->Get(cur);
            }else {
                return nullptr;
            }
        }
        std::string Current() {
            return obj->Get(cur);
        }
        bool isEnd() {
            if(cur == obj->Count() - 1){
                return true;
            }else {
                return false;
            }
        }
        
    private:
        Object* obj;
        int cur;
};

class subObject: public Object {
    public:
        subObject() {}
        subObject(std::vector<std::string> data_) {
            data.assign(data_.begin(), data_.end());
        }
        Iterator* createIterator() {
            // TODO: memory leak
            return new subIterator(this);
        }
        ~subObject() {}
        std::string Get(int x) {
            if(x >= 0 && x < this->Count() ) {
                return data[x];
            }else {
                return nullptr;
            }
        }

        int Count() {
            return data.size();
        }

        void Push(std::string s) {
            data.push_back(s);
        }
    private:
        std::vector<std::string> data;
};

int main() {
    subObject obj;
    obj.Push("tom");
    obj.Push("bob");

    auto it = obj.createIterator();
    std::cout << it->First() << std::endl;
    while (!it->isEnd()) {
        std::cout << it->Next() << std::endl;
    }
}
```







### 参考资料

+ modern-cpp-tutorial
+ https://www.zhihu.com/question/35614219
