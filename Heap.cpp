#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<iomanip>

using namespace std;

class Minheap{
    private:
        vector<int> heap;

        void siftup(int index){
            while(index>0){
                int parent_index=(index-1)/2;
                if(heap[index]<heap[parent_index]){
                    swap(heap[index],heap[parent_index]);
                    index=parent_index;
                }
                else{
                    break;
                }
            }
        }

        void siftdown(int index){
            int smallest=index;
            int leftchild=2*index+1;
            int rightchild=2*index+2;
            int size=heap.size();
            if(leftchild<size&&heap[leftchild]<heap[smallest]){
                smallest=leftchild;
            }
            if(rightchild<size&&heap[rightchild]<heap[smallest]){
                smallest=rightchild;
            }
            if(smallest!=index){
                swap(heap[index],heap[smallest]);
                siftdown(smallest);
            }
        }

    public:
        void push(int value){
            heap.push_back(value);
            siftup(heap.size()-1);
        }

        void pop(){        //删除根节点
            if(heap.empty()){
                return;
            }
            heap[0]=heap.back();    //将根节点值变为最右侧叶节点值
            heap.pop_back();        //删除最右侧叶节点
            siftdown(0);            //平衡堆
        }

        int top()const{
            if(!heap.empty()){
                return heap[0];
            }
            else{
                cout<<"异常！"<<endl;
                return -1;
            }
        }

        void to_heap(vector<int>& arr){      //将任意数组化堆
            heap=arr;
            int size=arr.size();
            for(int i=size/2-1;i>=0;i--){
                siftdown(i);
            }
        }

        bool isEmpty()const{
            return heap.empty();
        }

        void display(){        //按树状打印堆
            if(heap.empty()){
                cout<<"heap is empty!"<<endl;
                return;
            }
            int size=heap.size();
            int level=0;
            while((1<<level)-1<size){
                level++;
            }
            int cur_level_node=1;
            int cur_level_index=0;
            cout<<"--------------------"<<endl;
            for(int i=0;i<level;i++){
                int indent=(1<<(level-i-1))*3;
                cout<<string(indent,' ');
                for(int j=0;j<cur_level_node&&cur_level_index<size;j++){
                    cout<<left<<setw(6)<<heap[cur_level_index++];     //最后一行缩进为3，宽度设置为6，为3的两倍，便于计算每行缩进
                    cout<<string(2*indent-6,' ');
                }
                cout<<endl;
                cur_level_node*=2;
            }
            cout<<"--------------------"<<endl;
        }
        
};

int main(){
    Minheap mh;
    int input;
    cout<<"请输入堆："<<endl;
    while(cin>>input){
        mh.push(input);
    }
    mh.display();
    cout<<mh.top()<<endl;
    mh.pop();
    mh.display();
    cin.clear();
    cin.ignore();
    vector<int> arr;
    cout<<"请输入数组："<<endl;
    while(cin>>input){
        arr.push_back(input);
    }
    mh.to_heap(arr);
    mh.display();
    return 0;
}