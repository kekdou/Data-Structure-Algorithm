#include<iostream>

using namespace std;

/*方便起见用int表示，可用模板表示任意数据类型*/
struct Node{
    int data;
    struct Node* next;
    Node(int val=0):data(val),next(nullptr){};
    ~Node(){
        delete next;
    }
};

/*创建节点*/
Node* create_node(int data){
    Node* new_node=new Node(data);
    return new_node;
}

/*利用类的成员作为哨兵头节点，并且记为第0个节点*/
/*也可以在类中设置一个size成员，用于快速获得链表长度*/
class SinglyList{
    private:
        Node* head;
    public:
        SinglyList();
        Node* getHead();
        void insert_begin(Node* new_node);
        void insert_tail(Node* new_node);
        int getLength();
        int search_data(int data);
        int search_index(int index);
        void add_node(int index,Node* new_node);
        void del_node(int index);
        void modify_node(int index,int data);
        void display_node(int index);
        void display_List();
        void change_node(int index1,int index2);
        void sort_List();
        void reverse_List();
        void combine_List(SinglyList& othearList);
        ~SinglyList();
};

/*构造函数*/
SinglyList::SinglyList(){
    head=new Node();
}

/*获得头节点*/
Node* SinglyList::getHead(){
    return head;
}

/*头插法*/
void SinglyList::insert_begin(Node* new_node){
    new_node->next=head->next;
    head->next=new_node;
}

/*尾插法*/
void SinglyList::insert_tail(Node* new_node){
    Node* cur_node=head;
    while(cur_node->next!=nullptr){
        cur_node=cur_node->next;
    }
    cur_node->next=new_node;
}

/*获得长度*/
int SinglyList::getLength(){
    int length=0;
    Node* cur_node=head;
    while(cur_node->next!=nullptr){
        length++;
        cur_node=cur_node->next;
    }
    return length;
}

/*查找节点*/
//分为利用索引值查找数据和利用数据查找索引值
int SinglyList::search_data(int data){
    Node* cur_node=head;
    int index=0;
    while(cur_node->next!=nullptr){
        index++;
        cur_node=cur_node->next;
        if(cur_node->data==data){
            return index;
        }
    }
    return -1;
}

int SinglyList::search_index(int index){
    Node* cur_node=head;
    if(index<1){
        cout<<"索引值需为正数！"<<endl;
        return -1;
    }
    int data=-1;
    for(int i=0;i<index;i++){
        if(cur_node->next==nullptr){
            cout<<"索引值错误！"<<endl;
            return -1;
        }
        cur_node=cur_node->next;
    }
    data=cur_node->data;
    return data;
}

/*增加节点*/
void SinglyList::add_node(int index,Node* new_node){
    if(index<1){
        cout<<"索引值需为正数！"<<endl;
        delete new_node;
        return;
    }
    Node* cur_node=head;
    for(int i=0;i<index;i++){
        if(cur_node->next==nullptr&&i!=(index-1)){
            cur_node->next=new_node;
            cout<<"索引值超出列表范围，已自动添加在列表末尾"<<endl;
            return;
        }
        cur_node=cur_node->next;
    }
    Node* next_node=cur_node->next;
    cur_node->next=new_node;
    new_node->next=next_node;
    cout<<"已添加至第"<<(index+1)<<"个节点"<<endl;
}

/*删除节点*/
void SinglyList::del_node(int index){
    if(index<1){
        cout<<"索引值需为正数！"<<endl;
        return;
    }
    Node* cur_node=head;
    if(head->next==nullptr){
        cout<<"链表为空！"<<endl;
        return;
    }
    for(int i=1;i<index;i++){
        cur_node=cur_node->next;
        if(cur_node->next==nullptr){
            cout<<"索引值不存在！"<<endl;
            return;
        }
    }
    Node* next_node=cur_node->next;
    cur_node->next=next_node->next;
    delete next_node;
}

/*修改节点*/
void SinglyList::modify_node(int index,int data){
    if(index<1){
        cout<<"索引值需为正数！"<<endl;
        return;
    }
    Node* cur_node=head;
    for(int i=0;i<index;i++){
        if(cur_node->next==nullptr){
            cout<<"索引值不存在！"<<endl;
            return;
        }
        cur_node=cur_node->next;
    }
    cur_node->data=data;
}

/*打印节点*/
void SinglyList::display_node(int index){
    if(index<1){
        cout<<"索引值需为正数！"<<endl;
        return;
    }
    Node* cur_node=head;
    for(int i=0;i<index;i++){
        if(cur_node->next==nullptr){
            cout<<"索引值不存在！"<<endl;
        }
        cur_node=cur_node->next;
    }
    cout<<"第"<<index<<"个节点为："<<cur_node->data<<endl;
}

/*打印链表*/
void SinglyList::display_List(){
    Node* cur_node=head;
    while(cur_node->next!=nullptr){
        cur_node=cur_node->next;
        cout<<cur_node->data<<"->";
    }
    cout<<"NULL"<<endl;
}

/*交换节点*/
void SinglyList::change_node(int index1,int index2){
    if(index1==index2){
        cout<<"请输入不同的索引值！"<<endl;
        return;
    }
    if(index1<1||index2<1){
        cout<<"索引值需为正数！"<<endl;
    }
    Node* cur_node1=head;
    Node* cur_node2=head;
    for(int i=0;i<index1;i++){
        if(cur_node1->next==nullptr){
            cout<<"索引值错误！"<<endl;
            return;
        }
        cur_node1=cur_node1->next;
    }
    for(int i=0;i<index2;i++){
        if(cur_node2->next==nullptr){
            cout<<"索引值错误！"<<endl;
            return;
        }
        cur_node2=cur_node2->next;
    }
    int temp=cur_node1->data;
    cur_node1->data=cur_node2->data;
    cur_node2->data=temp;
}

/*链表排序*/
//利用冒泡排序实现，采用记录最后一次交换位置和是否交换标志进行优化
void SinglyList::sort_List(){
    int length=getLength();
    if(length<2){
        return;
    }
    int last_index=length;
    int cur_end=length;
    Node* cur_node=head->next;
    Node* next_node=cur_node->next;
    while(cur_end>1){
        last_index=1;
        cur_node=head->next;
        next_node=cur_node->next;
        for(int i=1;i<cur_end;i++){
            if((cur_node->data)>(next_node->data)){
                int temp=cur_node->data;
                cur_node->data=next_node->data;
                next_node->data=temp;
                last_index=i;
            }
            cur_node=next_node;
            if(next_node->next!=nullptr){
                next_node=cur_node->next;
            }
        }
        cur_end=last_index;
        if(cur_end==1){
            break;
        }
    }
}

/*逆转链表*/
void SinglyList::reverse_List(){
    Node* pre_node=nullptr;
    Node* cur_node=head->next;
    Node* next_node=nullptr;
    if(cur_node==nullptr){
        cout<<"链表为空！"<<endl;
    }
    while(cur_node!=nullptr){
        next_node=cur_node->next;
        cur_node->next=pre_node;
        pre_node=cur_node;
        cur_node=next_node;
    }
    head->next=pre_node;
}

/*合并链表*/
void SinglyList::combine_List(SinglyList& otherList){
    if(otherList.getHead()->next==nullptr){
        cout<<"需合并列表为空！"<<endl;
        return;
    }
    Node* cur_node=head;
    while(cur_node->next!=nullptr){
        cur_node=cur_node->next;
    }
    cur_node->next=otherList.getHead()->next;
    otherList.getHead()->next=nullptr;
}

/*析构函数*/
SinglyList::~SinglyList(){
    Node* cur_node=head;
    while(cur_node!=nullptr){
        Node* next_node=cur_node->next;
        delete cur_node;
        cur_node=next_node;
    }
    head=nullptr;
}

/*测试程序*/
int main(){
    SinglyList List;
    for(int i=0;i<3;i++){
        List.insert_tail(create_node(i));
    }
    List.display_List();
    for(int i=0;i<3;i++){
        List.insert_begin(create_node(i));
    }
    List.display_List();
    List.add_node(3,create_node(4));
    int index=List.search_data(4);
    List.display_node(index);
    List.del_node(index);
    List.display_List();
    int index1=List.search_data(2);
    int index2=List.search_data(1);
    List.change_node(index1,index2);
    List.display_List();
    List.reverse_List();
    List.display_List();
    List.sort_List();
    List.display_List();
    return 0;
}