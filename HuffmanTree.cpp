#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<fstream>
#include<cctype>
#include<sstream>

using namespace std;
//创建节点
struct Node{
    char data;
    int weight;
    Node* left;
    Node* right;
    Node(char d,int w):data(d),weight(w),left(nullptr),right(nullptr){};
    ~Node(){
        delete left;
        delete right;
    }
};
//比较函数，用于将优先队列改为最小堆
//优先队列默认为最大堆，权值最大的在堆顶
struct CompareNode{
    bool operator()(Node* a,Node* b){
        return a->weight>b->weight;
    }
};
//创建哈夫曼树
Node* buildHuffmanTree(const map<char,int>& frequency){
    priority_queue<Node*,vector<Node*>,CompareNode> minHeap;     //创建优先队列
    for(auto const& pair:frequency){        //建立森林
        minHeap.push(new Node(pair.first,pair.second));
    }
    while(minHeap.size()>1){
        Node* left=minHeap.top();
        minHeap.pop();
        Node* right=minHeap.top();
        minHeap.pop();      //选出权值最小的两个节点
        Node* new_node=new Node('\0',left->weight+right->weight);  //建立新节点为它们的父节点，权值为它们之和
        new_node->left=left;
        new_node->right=right;
        minHeap.push(new_node);   //将父节点加入队列，重复操作
    }      //最后队列中只有1个节点，返回
    return minHeap.top();
}
//获得哈夫曼编码
void getCode(Node* root,const string& code,map<char,string>& huffmanCode){
    if(!root){
        return;
    }
    if(!root->left&&!root->right){
        huffmanCode[root->data]=code;     //如果为叶节点，则设置键值对
        return;
    }
    getCode(root->left,code+"0",huffmanCode);
    getCode(root->right,code+"1",huffmanCode);
}
//读取文档内容，转化为string
string getString(const string& filepath){
    ifstream fin(filepath);
    if(!fin.is_open()){
        cerr<<"错误：无法打开文件！"<<filepath<<endl;
        return "";
    }
    stringstream buffer;
    buffer<<fin.rdbuf();
    fin.close();
    return buffer.str();
}
//整理string，读取字符与空格部分，并转换为小写
string cleanText(const string& text){
    string clean_text;
    for(char c:text){
        if(isalpha(c)||isspace(c)){
            clean_text+=tolower(c);
        }
    }
    return clean_text;
}
//统计字符频率
map<char,int> countCharFrequency(const string& text){
    map<char,int> char_frequency;
    for(char c:text){
        if(isalpha(c)){
            char_frequency[c]++;
        }
    }
    return char_frequency;
}

int main(){
    string text=getString("hello.txt");
    string clean_text=cleanText(text);
    map<char,int> frequency=countCharFrequency(clean_text);
    Node* root=buildHuffmanTree(frequency);
    map<char,string> huffmanCode;
    getCode(root," ",huffmanCode);
    for(auto pair:huffmanCode){
        cout<<pair.first<<":"<<pair.second<<endl;
    }
    return 0;
}