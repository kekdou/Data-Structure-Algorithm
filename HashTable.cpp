#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<type_traits>

using namespace std;

template<typename K,typename V>
struct Pair{
    K key;
    V val;
};
//解决哈希冲突常见两种方法
//1.链地址法(Separate Chaining)：在每个数组索引位置上储存一个链表
//2.开放寻址法(Open Addressing)：发生冲突时通过探测在数组中寻找下一个空位
template<typename K,typename V>
class HashTable{
    private:
        vector<list<Pair<K,V>>> table;      //采用链地址法
        int size;       //哈希表大小
        int num;        //元素数量           //其中num/size为负载因子，过高时易发生哈希冲突
        //哈希函数的实现，采用重载函数
        //int型
        size_t hashFunction(const int& key){
            return key%size;    //int型简单取模
        }
        //string型
        size_t hashFunction(const string& key){
            size_t hash_val=0;
            for(char ch:key){     //多项式滚动哈希，31是质数的位置，一般取31
                hash_val=(hash_val*31+ch)%size;    //多项式可以通过一个循环高效计算
            }
            return hash_val;
        }
    public:
        HashTable(int size=10){
            this->size=size;
            num=0;
            table.resize(this->size);
        }
        //扩充哈希表
        void resize(int new_size){
            HashTable<K,V> new_table(new_size);     //建立一个新哈希表
            for(const auto& bucket:table){
                for(const auto& p:bucket){
                    new_table.insert(p.key,p.val);  //极端情况下可能会在insert和reszie之间反复调用导致栈溢出
                }
            }
            *this=new_table;       //将旧表替换为新表
        }
        //插入键值对
        void insert(const K& key,const V& val){
            int index=hashFunction(key);
            for(auto& p:table[index]){      //若存在则更新值
                if(p.key==key){
                    p.val=val;
                    return;
                }
            }
            table[index].push_back({key,val});
            num++;         //若不存在则插入，num++
            if(static_cast<double>(num)/size>0.75){    //检查负载因子
                resize(size*2);
            }
        }
        //删除键值对
        void remove(const K& key){
            int index=hashFunction(key);
            auto& bucket=table[index];
            for(auto it=bucket.begin();it!=bucket.end();it++){
                if(it->key==key){
                    bucket.erase(it);
                    num--;
                    return;
                }
            }
        }
        //利用键查找值
        V& find(const K& key){
            int index=hashFunction(key);
            for(auto& p:table[index]){
                if(p.key==key){
                    return p.val;
                }
            }
            throw out_of_range("Key not found");
        }
        //打印哈希表
        void display(){
            for(int i=0;i<size;i++){
                cout<<"Bucket "<<i<<": ";
                for(const auto& p:table[i]){
                    cout<<"("<<p.key<<", "<<p.val<<")";
                }
                cout<<endl;
            }
            cout<<"Number of elements: "<<num<<endl;
            cout<<"Table size: "<<size<<endl;
            cout<<"Load factor: "<<static_cast<double>(num)/size<<endl;
            cout<<"--------------------"<<endl;
        }
};

int main(){
    HashTable<string,int> my_table;
    string key;
    cout<<"请输入键：";
    while(cin>>key){
        cout<<"请输入值：";
        int val;
        if(cin>>val){
            my_table.insert(key,val);
        }
        else{
            break;
        }
        cout<<"请输入键：";
    }
    cin.clear();
    cin.ignore();
    my_table.display();
    cout<<"请输入需要删除的键值：";
    cin>>key;
    my_table.remove(key);
    my_table.display();
    cin.clear();
    cout<<"请输入需要查找的键值：";
    cin>>key;
    cout<<my_table.find(key)<<endl;
    return 0;
}