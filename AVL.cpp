#include<iostream>
#include<algorithm>

using namespace std;

template<typename T>
struct Node{
    T data;
    Node* left;
    Node* right;
    int height;
    Node(T val):data(val),left(nullptr),right(nullptr),height(1){}
    ~Node(){
        delete left;
        delete right;
    }
};

template<typename T>
class AVL{
    private:
        Node<T>* root;
        //获得高度
        int getHeight(Node<T>* node){
            if(!node){
                return 0;
            }
            return node->height;
        }
        //获得平衡因子
        int getBalanceFactor(Node<T>* node){       //平衡因子为-1，0，1则平衡
            if(!node){
                return 0;
            }
            return getHeight(node->left)-getHeight(node->right);
        }
        //更新高度
        void updateHeight(Node<T>* node){
            if(node){
                node->height=1+max(getHeight(node->left),getHeight(node->right));
            }
        }
        //这两种旋转方式操作后仍然满足二叉树性质，中序遍历上是等价的
        //右旋
        Node<T>* rightRotate(Node<T>* y){
            Node<T>* x=y->left;
            Node<T>* T2=x->right;
            x->right=y;        //将失衡节点变为左子节点的右子节点
            y->left=T2;        //若左子节点存在右子节点，则将其变为失衡节点的左子节点
            updateHeight(y);   //更新高度
            updateHeight(x);
            return x;          //重新连接x节点
        }
        //左旋
        Node<T>* leftRotate(Node<T>* x){
            Node<T>* y=x->right;
            Node<T>* T2=y->left;
            y->left=x;         //将失衡节点变为右子节点的左子节点
            x->right=T2;       //若右子节点存在左子节点，则将其变为失衡节点的右子节点
            updateHeight(x);   //更新高度
            updateHeight(y);
            return y;          //重新连接y节点
        }
        //插入节点
        Node<T>* insertNode(Node<T>* node,T val){
            if(!node){      //插入到叶节点
                return new Node<T>(val);
            }
            if(val<node->data){
                node->left=insertNode(node->left,val);
            }
            else if(val>node->data){
                node->right=insertNode(node->right,val);
            }
            else{       //若已存在该值节点，则不插入
                return node;
            }
            updateHeight(node);     //更新高度，并且由递归很好的将每一个受影响的节点高度更新
            int balance=getBalanceFactor(node);      //由递归对每一个受影响的节点进行平衡因子检查
            if(balance>1&&val<node->left->data){     //LL型
                return rightRotate(node);
            }
            if(balance<-1&&val>node->right->data){   //RR型
                return leftRotate(node);
            }
            if(balance>1&&val>node->left->data){     //LR型 
                node->left=leftRotate(node->left);
                return rightRotate(node);
            }
            if(balance<-1&&val<node->right->data){   //RL型
                node->right=rightRotate(node->right);
                return leftRotate(node);
            }
            return node;
        }
        //辅助函数，获得最小值节点，用于删除
        Node<T>* findMin(Node<T>* node){
            Node<T>* cur_node=node;
            while(cur_node->left){
                cur_node=cur_node->left;
            }
            return cur_node;
        }
        //删除节点
        Node<T>* deleteNode(Node<T>* node,T key){
            if(!node){       //目标节点不存在
                return node;
            }
            if(key<node->data){
                node->left=deleteNode(node->left,key);
            }
            else if(key>node->data){
                node->right=deleteNode(node->right,key);
            }
            else{           //找到目标节点
                if(!node->left||!node->right){      //若目标节点只有一个子树
                    Node<T>* temp=node->left?node->left:node->right;
                    if(!temp){
                        temp=node;
                        node=nullptr;
                    }
                    else{
                        *node=*temp;       //与二叉树不同，不能直接返回temp，因为还要回溯检查平衡
                    }
                    delete temp;
                }
                else{
                    Node<T>* temp=findMin(node->right);
                    node->data=temp->data;
                    node->right=deleteNode(node->right,temp->data);
                }
            }
            if(!node){
                return node;
            }
            updateHeight(node);
            int balance=getBalanceFactor(node);     //同样，因为递归对每一个进入过函数的节点进行平衡因子检查
            if(balance>1&&getBalanceFactor(node->left)>=0){        //LL型
                return rightRotate(node);
            }
            if(balance<-1&&getBalanceFactor(node->right)<=0){      //RR型
                return leftRotate(node);
            }
            if(balance>1&&getBalanceFactor(node->left)<0){         //LR型
                node->left=leftRotate(node->left);
                return rightRotate(node);
            }
            if(balance<-1&&getBalanceFactor(node->right)>0){       //RL型
                node->right=rightRotate(node->right);
                return leftRotate(node);
            }
            return node;
        }
        //中序遍历
        void in_order(Node<T>* node){
            if(node){
                in_order(node->left);
                cout<<node->data<<" ";
                in_order(node->right);
            }
        }
        //清楚树
        void destoryNode(Node<T>* node){
            if(node){
                destoryNode(node->left);
                destoryNode(node->right);
                delete node;
            }
        }

    public:
        AVL():root(nullptr){}

        ~AVL(){
            destoryNode(root);
        }
        //提供一系列公共接口
        void insert(T val){
            root=insertNode(root,val);
        }

        void remove(T val){
            root=deleteNode(root,val);
        }

        void display(){
            in_order(root);
            cout<<endl;
        }
};

int main(){
    AVL<int> tree;
    int data;
    cout<<"请输入插入平衡树的值：";
    while(cin>>data){
        tree.insert(data);
    }
    cin.clear();
    cin.ignore();
    tree.display();
    cout<<"请输入需要删除的值：";
    cin>>data;
    tree.remove(data);
    tree.display();
    return 0;
}