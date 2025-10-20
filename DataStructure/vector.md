## vector

vector内部使用一块 **连续的内存** 来存储元素，内部由三个指针（或迭代器）维护  
1. `start`：指向我内存块的起始位置
2. `finish`：指向最后一个元素的下一个位置
3. `end_of_storage`：指向最后一个可容纳元素的下一个位置

采用左闭右开的方式[start,end_of_storage)，这在STL中十分常见，简化了许多计算

这三个指针共同定义了vector的大小（size）和容量（capacity）
- `size`：当前vector中实际储存的元素数量，等于 `finish`-`start`
- `capacity`：vector在不重新分配内存的情况下可以容纳的最大元素数，等于 `end_of_storage-start`

当vector添加新元素时：
- 容量未满：size < capacity，新元素在finish指向的内存位置构造新元素，然后finish指针向后移动一位
- 容量已满：如果size = capacity，vector必须重新分配内存
	1. 分配一块更大的新内存块，通常是当前容量的2倍
	2. 将旧内存块中所有元素拷贝到新内存块中
	3. 释放旧内存
	4. 在新内存块添加新元素

重新分配内存的操作相对昂贵，涉及到内存分配、元素拷贝和内存释放，因此vector采用加倍扩容以减少重新分配的次数   

### 定义和初始化

```C++
template <typename T>
std::vector<T> v1;
std::vector<T> v2(size_type n, T& val = default);
std::vector<T> v3 = {val1, val2, val3, val4};
// 使用另一个vector拷贝构造
std::vector<T> v4(std::vector& other);
// 使用迭代器构造
std::vector<T> v5(InputIt first, InputIt last);
```

### 元素访问

|方法|说明|
|:---|:---|
|`[size_type n]`|不进行边界检查，速度最快|
|`.at(size_type n)`|进行边界检查，若越界抛出std::out_of_range异常|
|`.front()`|返回第一个元素的引用|
|`.back()`|返回最后一个元素的引用|

### 大小和容量

|方法|说明|
|:---|:---|
|`.size()`|返回vector中实际元素数量|
|`.empty()`|检查vector是否为空，返回true或false|
|`.capacity()`|返回vector当前已分配空间可容纳元素总数|
|`.reserve(size_type new_cap = 0)`|预留至少new_cap个元素的空间，用于避免多次内存重新分配|
|`.resize(size_type n, const value_type& val = default)`|改变vector的元素数量，若n更大，新元素为val|

### 增删元素

|方法|说明|
|:---|:---|
|`.push_back(const value_type& val)`|在vector末尾添加元素|
|`.pop_back()`|移除vector末尾元素|
|`.emplace(const_iterator position, Args& args)`|在指定位置原地构造并插入元素|
|`.emplace_back(Args& args)`|在vector末尾原地构造并插入元素|
|`.clear()`|移除所有元素，size变为0但capacity不变|
|`.swap(std::vector& other)`|交换两个vector内容(只交换内部指针，不拷贝数据)|

关于emplace方法的原地构造：使用其他插入方式，需要先构造一个新对象，再将对象拷贝到指定位置，而emplace可以在指定位置处调用构造函数，避免了额外操作

|方法|说明|
|:---|:---|
|`.insert(const_iterator position, const value_type& val)`|在指定位置插入元素|
|`.insert(const_iterator position, size_type n, const value_type& val)`|在指定位置插入n个相同的元素|
|`.insert(const_iterator position, initializer_list<T> il)`|在指定位置插入一个初始化列表{...}中的所有元素|
|`.insert(const_iterator position, InputIt first, InputIt last)`|在指定位置插入迭代器定义的范围[first, last)内元素|
|`.erase(const_iterator position);`|删除指定位置的元素|
|`.erase(const_iterator first, const_iterator last)`|删除范围[first, last)内元素|

*在使用insert和erase时要注意迭代器失效问题*  

### 迭代器

|方法|说明|
|:---|:---|
|`.begin()`|指向第一个元素位置的迭代器|
|`.end()`|指向最后一个元素之后位置的迭代器|
|`.cbegin()`|**const**迭代器，不能修改元素|
|`.cend()`|**const**迭代器，不能修改元素|
|`.rbegin()`|指向**反向**第一个元素(即原容器最后一个元素)的反向迭代器
|`.rend()`|指向**反向**最后一个元素之前位置的反向迭代器(即原容器第一个元素之前)|

### 遍历

```C++
// 1. 下标遍历(最快)
for (size_t n = 0; i < v.size(); i++) {
    cout << v[i] << " ";
}
// 2. 迭代器遍历(STL通用)
for (auto it = v.begin(); it != v.end(); it++) {
    cout << *it << " ";
}
// 3. 范围 for 循环(C++11 推荐)
for (int element : v) {
    cout << element << " ";
}
```