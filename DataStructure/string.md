## string

### 定义和初始化

```C++
std::string s1;
std::string s2 = "Hello";
std::string s3 = s2;
// 创建一个包含count个字符ch的字符串
std::string s4(size_type n, char ch);
// 拷贝str中从pos开始的count个字符
std::string s5(const std::string& str, size_type pos, size_type count = npos);
// 拷贝迭代器范围[first, last)中的字符
std::string s6(InputIt first, InputIt last);
```
### 核心操作

与vector基本相同，额外有替换：

一般可以直接使用`[]`和`.at()`进行替换，因为返回的是引用

|方法|说明|
|:---|:---|
|`.replace(size_type pos, size_type count, const std::string& str)`|从pos索引开始，替换count个字符，替换为整个str|

```C++
std::string s = "Hello World!";
std::string target = "C++";
// 替换"World"，pos = 6(W的位置), count = 5(World的长度)
s.replace(6, 5, target);
std::cout << s << std::endl; // 输出: Hello C++!
```

### 查找

`std::string::npos`是一个静态常量，表示未找到或最大值  
即如果未find到目标，会返回npos

|方法|说明|
|:---|:---|
|`.find(const std::string& str, size_type pos = 0)`|从pos开始，返回str第一次出现的位置|
|`.rfind(const std::string& str, size_type pos = npos)`|从pos向前(反向)，返回str最后一次出现的位置|
|`.find_first_of(const std::string& str, size_type pos = 0)`|从pos开始，返回str中任意字符第一次出现的位置|
|`.find_last_of(const std::string& str, size_type pos = npos)`|从pos向前(反向)，返回str中任意字符最后一次出现的位置|
|`.substr(size_type pos = 0, size_type count = npos)`|从pos开始，返回长度为count的子串|

```C++
// info.txt格式
// name age sex
std::ifstream fin("info.txt")
if (!fin.is_open()) {
    std::cerr << "error" << std::endl;
    return;
}
while (std::getline(fin, line)) {
    std::string name, age, sex;
    size_t pos = line.find(" ");
    if (pos != std::string::npos) {
        name = line.substr(0, pos);
        size_t pos2 = line.find(" ", pos + 1);
        if (pos2 != std::string::npos) {
            age = line.substr(pos + 1, pos2 - pos - 1);
            sex = line.substr(pos2 + 1);
        }
    }
}
```

### 转换

```C++
// 数字转字符串
std::string s_int = std::to_string(num_int);
std::string s_double = std::to_string(num_double);
std::string s_ll = std::to_string(num_ll);
// 字符串转数字(string to int)
int num_int = stoi(str);
double num_double = stod(str);
long long num_ll = stoll(str);
```
