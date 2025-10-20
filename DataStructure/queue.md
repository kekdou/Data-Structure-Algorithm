## queue

queue同样通过封装deque作为底层容器来提供受限的访问接口，具有以下特点：
- 单一访问点：所有操作集中在队列两端，队尾用于添加元素，队首用于移除元素，无法访问和修改队列中的其他元素  
- 先进先出（FIFO）：第一个添加的元素是第一个被移除的

queue默认使用deque作为底层容器，保证push()和pop()操作都是O(1)级别

### 定义

```C++
// 底层使用默认的std::deque<T>
std::queue<T> q1;
// 底层显式使用std::list<int>
std::queue<T, std::list<iT>> q2;
// 使用另一个队列拷贝构造
std::queue<T> q3(q1);
```

### 核心操作

std::queue的操作与stack基本相同，仅在访问上有所区别

|方法|说明|
|:---|:---|
|`.front()`|返回队首元素的引用|
|`.back()`|返回队尾元素的引用|

*同样，尝试对一个空队列调用front(),back(),或pop()会导致未定义行为，也不支持迭代器*  

---

## priority_queue

priority_queue默认使用vector作为底层容器，利用数据结构堆（heap）实现相关功能 

vector的连续内存非常适合实现堆，使得父子节点可以通过简单的数学运算来确定，而无需使用指针  

默认情况下，std::priority_queue始终保证最大(或优先级最高)的元素位于队列的顶部，即默认实现为最大堆   

std::priority_queue接受三个模板参数，但通常只需要提供第一个：

```C++
template <
    class T,
    class Container = std::vector<T>,  // 底层容器默认用vector
    class Compare = std::less<typename Container::value_type>  // 默认比较函数是std::less
> class priority_queue;
```

默认比较器std::less<T>会让大元素排在前面，less理解为递减，可以使用std::greater<T>来创建最小堆，greater理解为递增  

使用标准库中的std::less<T>(默认)和std::greater<T>需要`#include<functional>`

### 定义

```C++
std::priority_queue<T> pq1;
// 创建最小堆
std::priority_queue<T, vector<T>, std::greater<T>> pq2;
// 利用迭代器从范围构造
std::proority_queue<T> pq3(const_iterator first, const_iterator last);
```

*需要注意的是，如果使用了自定义对象(`std::priority_queue<MyObject>`)，必须重载`<`或者比较器函数*  

```C++
// 自定义比较器结构体
struct CustomMaxComparator {
    // 必须定义operator()，接受两个const引用，并返回bool
    // 如果'a'应该排在'b'后面(优先级低于'b')，则返回true
    bool operator()(const MyObject& a, const MyObject& b) const {
        return a.val < b.val;  // 实现最大堆，值小的排在后面
    }
}
std::priority_queue<MyObject, std::vector<MyObject>, CustomMaxComparator> pq;
```

而在类中，也可以重载小于操作符，std::less<T>会调用你重载的`operator<`  

```C++
class Person {
public:
    std::string name;
    int age;
    Person(std::string n, int a) : name(n), age(a) {}
    bool operator<(const Person& other) const {
        return age < other.age;
    }
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << p.name << "(" << p.age << ")";
    }
};
int main() {
    // 默认Max Heap(使用Person::operator<)
    std::priority_queue<Person> people;
    people.emplace("Alice", 30);
    people.emplace("Bob", 20);
    people.emplace("Charlie", 40);
    // Charlie(40岁)的优先级最高
    std::cout << "Top: " << people.top() << std::endl;
}
```

### 核心操作

与std::stack几乎一样，只不过std::priority_queue的`.top()`方法返回最高优先级元素的const引用，是**只读**的  
