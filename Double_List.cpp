#include<iostream>

using namespace std;

template<typename T>
struct Node{
    T data;
    Node* prev;
    Node* next;
    Node(T val):data(val),prev(nullptr),next(nullptr){};
    ~Node(){
        delete prev;
        delete next;
    }
};

template<typename T>
class DoublyList{
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
    public:
        DoublyList();
        int getSize()const;
        Node<T>* getHead()const;
        Node<T>* getTail()const;
        void insert_head(T data);
        void insert_tail(T data);
        void add_node(int index,T data);
        void del_node(int index);
        void display_head();
        void display_tail();
        ~DoublyList();
};

template<typename T>
DoublyList<T>::DoublyList(){
    this->head=new Node<T>(T());
    this->tail=new Node<T>(T());
    head->next=tail;
    tail->prev=head;
    this->size=0;
}

template<typename T>
int DoublyList<T>::getSize() const{
    return size;
}

template<typename T>
Node<T>* DoublyList<T>::getHead() const{
    return head;
}

template<typename T>
Node<T>* DoublyList<T>::getTail() const{
    return tail;
}

template<typename T>
void DoublyList<T>::insert_head(T data){
    Node<T>* new_node=new Node<T>(data);
    Node<T>* cur_node=head->next;
    head->next=new_node;
    new_node->prev=head;
    new_node->next=cur_node;
    cur_node->prev=new_node;
    size++;
}

template<typename T>
void DoublyList<T>::insert_tail(T data){
    Node<T>* new_node=new Node<T>(data);
    Node<T>* cur_node=tail->prev;
    cur_node->next=new_node;
    new_node->prev=cur_node;
    new_node->next=tail;
    tail->prev=new_node;
    size++;
}

template<typename T>
void DoublyList<T>::add_node(int index,T data){
    if(index<1){
        cout<<"索引值需为正数！"<<endl;
        return;
    }
    Node<T>* new_node=new Node<T>(data);
    Node<T>* cur_node=head;
    Node<T>* next_node=head;
    for(int i=0;i<index;i++){
        if(cur_node->next==tail->prev){
            cout<<"索引值不存在！"<<endl;
            delete new_node;
            return;
        }
        cur_node=cur_node->next;
    }
    next_node=cur_node->next;
    cur_node->next=new_node;
    new_node->prev=cur_node;
    new_node->next=next_node;
    next_node->prev=new_node;
    size++;
}

template<typename T>
void DoublyList<T>::del_node(int index){
    if(index<1){
        cout<<"索引值需为正数！"<<endl;
        return;
    }
    Node<T>* cur_node=head;
    for(int i=0;i<index;i++){
        if(cur_node->next==tail->prev){
            cout<<"索引值不存在！"<<endl;
            return;
        }
        cur_node=cur_node->next;
    }
    Node<T>* prev_node=cur_node->prev;
    Node<T>* next_node=cur_node->next;
    prev_node->next=next_node;
    next_node->prev=prev_node;
    size--;
}

template<typename T>
void DoublyList<T>::display_head(){
    if(size<1){
        cout<<"链表为空！"<<endl;
        return;
    }
    Node<T>* cur_node=head;
    cout<<"head<-->";
    while(cur_node->next!=tail){
        cur_node=cur_node->next;
        cout<<cur_node->data<<"<-->";
    }
    cout<<"tail"<<endl;
}

template<typename T>
void DoublyList<T>::display_tail(){
    if(size<1){
        cout<<"链表为空！"<<endl;
        return;
    }
    Node<T>* cur_node=tail;
    cout<<"tail<-->";
    while(cur_node->prev!=head){
        cur_node=cur_node->prev;
        cout<<cur_node->data<<"<-->";
    }
    cout<<"head"<<endl;
}

template<typename T>
DoublyList<T>::~DoublyList(){
    Node<T>* cur_node=head;
    while(cur_node->next!=tail){
        Node<T>* next_node=cur_node->next;
        delete cur_node;
        cur_node=next_node;
    }
    head=nullptr;
    tail=nullptr;
}

int main(){
    DoublyList<int> List;
    for(int i=0;i<3;i++){
        List.insert_tail(i);
    }
    List.display_head();
    for(int i=0;i<3;i++){
        List.insert_head(i);
    }
    List.display_head();
    List.add_node(3,4);
    List.display_tail();
    List.del_node(4);
    List.display_head();
}