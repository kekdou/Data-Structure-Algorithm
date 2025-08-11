#include<iostream>
#include<queue>
#include<algorithm>
#include<stack>

using namespace std;
//二叉树是指仅有两个子节点的树
//二叉搜索树对节点值有所要求，左子树所有节点小于根节点值，右子树所有节点大于根节点值
//平衡二叉树在此基础上防止有序导致堆化为链表的情形，要求左子树和右子树高度差不超过1
//完全二叉树指除了最后一层必须满节点，且最后一层节点从左到右排列，不得空缺
//因此完全二叉树可以由数组表示，而普通二叉树可能存在空缺不行
//堆是完全二叉树，但对于节点数据有所要求，每个根节点的数值必须大于子节点，成为最大堆，或反之称为最小堆
//哈夫曼树是一种二叉树，要求最小化所有叶节点的带权路径长度之和
struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int val):data(val),left(nullptr),right(nullptr){};
    ~Node(){
        delete left;
        delete right;
    }
};

class BinarySearchTree{
    private:
        Node* root;

        Node* insertNode(Node* node,int key){
            if(!node){
                return new Node(key);
            }
            if(key<node->data){
                node->left=insertNode(node->left,key);     //递归插入
            }
            else if(key>node->data){
                node->right=insertNode(node->right,key);    //特性就是不断往叶节点插入
            }
            return node;
        }

        Node* deleteNode(Node* node,int key){
            if(!node){
                return node;
            }
            if(key<node->data){
                node->left=deleteNode(node->left,key);
            }
            else if(key>node->data){
                node->right=deleteNode(node->right,key);
            }
            else{       //查找到目标节点，data=key
                if(!node->left){      //若无左节点，直接拼接右子树即可
                    Node* temp=node->right;
                    delete node;
                    return temp;
                }
                else if(!node->right){     //若无右节点，直接拼接左子树即可
                    Node* temp=node->left;
                    delete node;
                    return temp;
                }
                Node* temp=findMin(node->right);    //若同时有左右节点，需要处理保证二叉树性质
                node->data=temp->data;         //找出右子树的最小值为替身，根据性质一定会大于其根节点，复制值
                node->right=deleteNode(node->right,temp->data);       //删去替身
            }
            return node;    //在删除的过程中一直维持二叉树的性质
        }
        //找出最小值节点
        Node* findMin(Node* node){
            while(node&&node->left){
                node=node->left;
            }
            return node;
        }
        //找出最大值节点
        Node* findMax(Node* node){
            while(node&&node->right){
                node=node->right;
            }
            return node;
        }

        void destoryTree(Node* node){
            if(node){
                destoryTree(node->left);
                destoryTree(node->right);
                delete node;
            }
        }
        //深度优先遍历，分为前序，中序，后序三种
        //递归前序遍历
        void pre_order(Node* node){      //前序遍历：根->左->右
            if(node){                    //即要求每一个子树都是先输出根节点值，而后左节点，而后右节点，下同
                cout<<node->data<<" ";
                pre_order(node->left);
                pre_order(node->right);
            }
        }
        //非递归前序遍历
        void pre_order2(Node* node){
            if(!node){
                return;
            }
            stack<Node*> s;
            s.push(node);
            while(!s.empty()){
                Node* current=s.top();
                s.pop();
                cout<<current->data<<" ";
                if(current->right){
                    s.push(node->right);
                }
                if(current->left){
                    s.push(current->left);
                }
            }
        }
        //递归中序遍历
        void in_order(Node* node){       //中序遍历：左->根->右(有序输出)
            if(node){
                in_order(node->left);
                cout<<node->data<<" ";
                in_order(node->right);
            }
        }
        //非递归中序遍历
        void in_order2(Node* node){
            if(!node){
                return;
            }
            stack<Node*> s;
            Node* current=node;
            while(current||!s.empty()){
                while(current){
                    s.push(current);
                    current=current->left;
                }
                current=s.top();
                s.pop();
                cout<<current->data<<" ";
                current=current->right;
            }
        }
        //递归后序遍历
        void post_order(Node* node){     //后序遍历：左->右->根
            if(node){
                post_order(node->left);
                post_order(node->right);
                cout<<node->data<<" ";
            }
        }
        //非递归后序遍历
        void post_order2(Node* node){
            if(!node){
                return;
            }
            stack<Node*> s1;
            stack<Node*> s2;
            s1.push(node);
            while(!s1.empty()){
                Node* current=s1.top();
                s1.pop();
                s2.push(current);
                if(current->left){
                    s1.push(current->left);
                }
                if(current->right){
                    s1.push(current->right);
                }
            }
            while(!s2.empty()){
                Node* current=s2.top();
                s2.pop();
                cout<<current->data<<" ";
            }
        } 
        //广度优先遍历
        void level_order(Node* node){
            if(!node){
                return;
            }
            queue<Node*> q;
            q.push(node);
            while(!q.empty()){      //保证将每一个高度遍历完，再遍历下一个高度
                Node* current=q.front();
                q.pop();
                cout<<current->data<<" ";
                if(current->left){
                    q.push(current->left);
                }
                if(current->right){
                    q.push(current->right);
                }
            }
        }
        //查找目标值节点
        Node* search(Node* node,int key){
            if(!node||node->data==key){
                return node;
            }
            if(key<node->data){
                return search(node->left,key);
            }
            else{
                return search(node->right,key);
            }
        }
        //计算二叉树高度
        int treeHeight(Node* node){
            if(!node){
                return 0;
            }
            int leftHeight=treeHeight(node->left);
            int rightHeight=treeHeight(node->right);
            return max(leftHeight,rightHeight)+1;
        }
        //计算二叉树节点数
        int countNode(Node* node){
            if(!node){
                return 0;
            }
            return 1+countNode(node->left)+countNode(node->right);
        }

    public:    //提供接口
        BinarySearchTree():root(nullptr){};

        ~BinarySearchTree(){
            destoryTree(root);
        }

        void insert(int key){
            root=insertNode(root,key);
        }

        void remove(int key){
            root=deleteNode(root,key);
        }

        void pre_order_traversal(){
            pre_order(root);
            cout<<endl;
        }

        void pre_order_traversal2(){
            pre_order2(root);
            cout<<endl;
        }

        void in_order_traversal(){
            in_order(root);
            cout<<endl;
        }

        void in_order_traversal2(){
            in_order2(root);
            cout<<endl;
        }

        void post_order_traversal(){
            post_order(root);
            cout<<endl;
        }

        void post_order_traversal2(){
            post_order2(root);
            cout<<endl;
        }
        
        void level_order_traversal(){
            level_order(root);
            cout<<endl;
        }

        Node* search_node(int key){
            return search(root,key);
        }

        Node* get_Min(){
            return findMin(root);
        }

        Node* get_Max(){
            return findMax(root);
        }

        int tree_height(){
            return treeHeight(root);
        }

        int count_node(){
            return countNode(root);
        }

};

int main() {
    BinarySearchTree bst;
    int val;
    cout<<"请输入二叉树需插入值：";
    while(cin>>val){
        bst.insert(val);
    }
    cin.clear();
    cin.ignore();
    cout<<"深度优先遍历："<<endl;
    cout<<"前序遍历：";
    bst.pre_order_traversal();
    cout<<"中序遍历：";
    bst.in_order_traversal();
    cout<<"后序遍历：";
    bst.post_order_traversal();
    cout<<"请输入需删去节点值：";
    cin>>val;
    bst.remove(val);
    cout<<"广度优先遍历："<<endl;
    bst.level_order_traversal();
    cout<<"最大值为：";
    cout<<bst.get_Max()->data<<endl;
    cout<<"最小值为：";
    cout<<bst.get_Min()->data<<endl;
    cout<<"节点数为：";
    cout<<bst.count_node()<<endl;
    cout<<"树高为：";
    cout<<bst.tree_height()<<endl;
    return 0;
}
