#include<iostream>
#include<vector>

using namespace std;

class DSU{
    public:
        vector<int> parent;      //储存节点的根节点
        vector<int> rank;        //记录每个根节点的秩

        DSU(int n){
            parent.resize(n);
            for(int i=0;i<n;i++){   //初始化将每个节点的根节点设置为自身
                parent[i]=i;
            }
            rank.assign(n,0);       //初始化将秩设为0
        }

        int find(int i){
            if(parent[i]==i){       //若为根节点则返回
                return i;
            }
                return parent[i]=find(parent[i]);     //压缩路径
        }

        void unite(int i,int j){
            int root_i=find(i);
            int root_j=find(j);
            if(root_i!=root_j){
                if(rank[root_i]<rank[root_j]){       //利用秩估计集合的高度
                    parent[root_i]=root_j;
                }
                else if(rank[root_i]>rank[root_j]){  //将秩小的根节点连接到秩大的根节点
                    parent[root_j]=root_i;
                }
                else{           //若相同，则任意，并且一方秩增加
                    parent[root_j]=root_i;
                    rank[root_i]++;
                }
            }
        }

        bool check(int i,int j){
            int root_i=find(i);
            int root_j=find(j);
            return root_i==root_j;
        }
}