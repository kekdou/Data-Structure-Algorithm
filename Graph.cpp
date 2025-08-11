#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
#include<algorithm>

using namespace std;
//设置最大值为无穷
const int INF=numeric_limits<int>::max();
/*图的构建*/
//图的表示主要分为邻接矩阵与邻接表两种形式
//一般在算法中会将节点用数字表示，但在实际应用过程中可能为了方便可用map<string,vector<string>>表示
//但map会消耗更多的空间，因此在时间和空间，方便之间取舍
//边的结构体
struct Edge{
    int u,v,weight;
};
//邻接表法表示图
//添加无向边
void addEdge(vector<vector<int>>& adj,int u,int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}
//添加带权无向边
void addWeightedEdge(vector<vector<pair<int,int>>>& adj,int u,int v,int weight){
    adj[u].push_back({v,weight});
    adj[v].push_back({u,weight});
}
//邻接矩阵法表示图
//获得邻接矩阵，无向图
vector<vector<int>> getMatrix(int V){
    vector<vector<int>> adj(V,vector<int>(V,INF));
    for(int i=0;i<V;i++){
        adj[i][i]=0;
    }
    return adj;
}
//若为无权图则weight设置为1
void addWeightedEdge(vector<vector<int>>& adj,int u,int v,int weight=1){
    int V=adj.size();
    if(u>=0&&u<V&&v>=0&&v<V){
        adj[u][v]=weight;
        adj[v][u]=weight;
    }
}

/*搜索问题*/
//搜索问题主要分为广度优先与深度优先
//广度优先搜索
//可用于图的遍历以及无权图的最短路径问题
//时间复杂度：O(V+E)
//空间复杂度：O(V)
void BFS(const vector<vector<int>>& adj,int node){
    int V=adj.size();
    vector<bool> visited(V,0);
    queue<int> q;        //队列实现广度优先
    visited[node]=1;     //防止重复访问
    q.push(node);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cout<<u<<" ";
        for(int v:adj[u]){
            if(!visited[v]){
                visited[v]=1;
                q.push(v);
            }
        }
    }
    cout<<endl;
}
//深度优先搜索
//可用于图的遍历，连通性问题，拓扑排序
//分为递归与非递归形式
//时间复杂度：O(V+E)
//空间复杂度：O(V)
//非递归形式，适合处理大规模图，无栈溢出限制
void DFS(const vector<vector<int>>& adj,int node){
    int V=adj.size();
    vector<bool> visited(V,0);
    stack<int> s;          //栈实现深度优先
    visited[node]=1;
    s.push(node);
    while(!s.empty()){
        int u=s.top();
        s.pop();
        cout<<u<<" ";
        for(int v:adj[u]){
            if(!visited[v]){
                visited[v]=1;
                s.push(v);
            }
        }
    }
    cout<<endl;
}
//递归形式，代码简易
//辅助函数
void DFSUtil(const vector<vector<int>>& adj,int u,vector<bool> visited){
    visited[u]=1;
    cout<<u<<" ";
    for(int v:adj[u]){        //实际利用函数栈的性质
        if(!visited[v]){
            DFSUtil(adj,v,visited);
        }
    }
}

void DFS2(const vector<vector<int>>& adj,int node){
    int V=adj.size();
    vector<bool> visited(V,0);
    DFSUtil(adj,node,visited);
    cout<<endl;
}

/*最短路径问题*/
//迪杰斯特尔算法
//用于解决带权图单源最短路径问题，只适用于边权为非负数的情况
//时间复杂度：O(ElogV)
//空间复杂度：O(V+E)
void Dijkstra(const vector<vector<pair<int,int>>>& adj,int node){
    int V=adj.size();
    vector<int> dist(V,INF);         //初始距离设置为无穷
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;  //优先队列，先判断距离小的点
    dist[node]=0;
    pq.push({node,0});
    while(!pq.empty()){          //贪心算法的思想
        int u_dist=pq.top().second;
        int u=pq.top().first;
        pq.pop();
        if(u_dist>dist[u]){      //若到该点距离不为最小，则跳过
            continue;
        }
        for(const auto& edge:adj[u]){
            int v=edge.first;
            int weight=edge.second;
            if(dist[u]+weight<dist[v]){     //若比最小距离小，则更新dist
                dist[v]=dist[u]+weight;
                pq.push({v,dist[v]});
            }
        }
    }
    cout<<"从顶点"<<node<<"到其他节点的最短距离："<<endl;
    for(int i=0;i<V;i++){
        if(dist[i]==INF){
            cout<<"顶点"<<i<<": 无法到达"<<endl;
        }
        else{
            cout<<"顶点"<<i<<": "<<dist[i]<<endl;
        }
    }
}
//贝尔曼-福特算法
//解决单源最短路径问题,能够处理边权为负数的情况，可以检测负权环但无法处理
//时间复杂度：O(V*E)
//空间复杂度：O(V+E)
void Bellman_Ford(const vector<Edge>& edges,int node){
    int V=edges.size();
    vector<int> dist(V,INF);
    dist[node]=0;
    for(int i=0;i<V-1;i++){        //对所有边进行V-1次松弛操作
        for(const auto&edge:edges){
            int u=edge.u;
            int v=edge.v;
            int w=edge.weight;
            if(dist[u]!=INF&&dist[u]+w<dist[v]){     //此处Edge指u->v，有向
                dist[v]=dist[u]+w;
            }
        }
    }     //算法每次保证至少一条边上的最短路径被松弛到正确值
    for(const auto&edge:edges){     //在无负权环的图中，从源点到一个顶点的最短路径最多包含V-1条边
        int u=edge.u;
        int v=edge.v;
        int w=edge.weight; 
        if(dist[u]!=INF&&dist[u]+w<dist[v]){    //因此V-1次后若可以继续松弛，则说明存在负权环
            cout<<"图中存在负权环！"<<endl;
            return;
        }
    }
    cout<<"从顶点"<<node<<"到其他顶点的最短距离："<<endl;
    for(int i=0;i<V;i++){
        cout<<"顶点"<<i<<":";
        if(dist[i]==INF){
            cout<<"不可达"<<endl;
        }
        else{
            cout<<dist[i]<<endl;
        }
    }
}
//弗洛伊德算法
//用于解决所有顶点对之间的最短路径问题，可以处理带负权边的图，但不能处理负权环
//时间复杂度：O(V^3)
//空间复杂度：O(V^2)
void FloydWarshall(const vector<vector<int>>& adj){
    int V=adj.size();
    vector<vector<int>> dist=adj;
    for(int k=0;k<V;k++){              //三重循环，k是中间点
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                if(dist[i][k]!=INF&&dist[k][j]!=INF){       //确保不是无穷，防止溢出
                    if(dist[i][k]+dist[k][j]<dist[i][j]){   //松弛操作，通过k更新路径
                        dist[i][j]=dist[i][k]+dist[k][j];
                    }
                }
            }
        }
    }
    cout<<"所有顶点对的最短路径矩阵："<<endl;
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(dist[i][j]==INF){
                cout<<"INF\t";
            }
            else{
                cout<<dist[i][j]<<"\t";
            }
        }
        cout<<endl;
    }
}

/*最小生成树问题*/
//普里姆算法
//适用于带权连通无向图，用加点法获得最小生成树
//时间复杂度：O(ElogV)
//空间复杂度：O(V+E)
void PrimMST(const vector<vector<pair<int ,int>>>& adj,int node){
    int V=adj.size();
    vector<int> key(V,INF);
    vector<bool> inMST(V,0);      //最小生成树包含点
    int total=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;   //优先队列，每次先判断key值最小节点
    key[node]=0;
    pq.push({node,0});
    while(!pq.empty()){
        int u_weight=pq.top().second;
        int u=pq.top().first;
        pq.pop();
        if(inMST[u]){        //若已在树中，则跳过
            continue;
        }
        inMST[u]=1;
        total+=u_weight;
        for(auto& edge:adj[u]){
            int v=edge.first;
            int weight=edge.second;
            if(!inMST[v]&&weight<key[v]){    //遍历过程中逐步更新key值
                key[v]=weight;
                pq.push({v,key[v]});
            }
        }
    }
    cout<<"最小生成树的总权重为："<<total<<endl;
}
//克鲁斯卡尔算法
//适用于带权连通无向图，用加变法获得最小生成树
//时间复杂度：O(ElogE)
//空间复杂度：O(V+E)
//重载比较函数
bool compareEdges(const Edge& a,const Edge& b){
    return a.weight<b.weight;
}
//并查集
struct DSU{
    public:
        vector<int> parent;       //记录节点的根节点
        DSU(int n){
            parent.resize(n);
            for(int i=0;i<n;i++){ //先将每个节点的根节点初始化为自身
                parent[i]=i;
            }
        }

        int find(int i){         //获得节点i的根节点
            if(parent[i]==i){
                return i;        //根据初始化，根节点的i=parent[i]
            }
            return parent[i]=find(parent[i]);    //向上递归调用，直至找到根节点并赋值返回
        }

        void unite(int i,int j){      //合并节点i和j
            int root_i=find(i);
            int root_j=find(j);
            if(root_i!=root_j){
                parent[root_i] = root_j;     //将i的根节点设置为j  
            }
        }
};
//算法主函数
void KruskalMST(const vector<Edge>& edges){
    int V=edges.size();
    vector<Edge> sort_edges=edges;
    sort(sort_edges.begin(),sort_edges.end(),compareEdges);       //将边按权值排序，需要重载比较函数（struct型）
    DSU dsu(V);          //并查集用于记录根节点
    vector<Edge> mst;    //最小生成树所含边
    int total=0;
    for(const auto& edge:sort_edges){
        if(mst.size()==V-1){         //最小生成树所含边一定为V-1
            break;                   //已找齐则退出
        }
        if(dsu.find(edge.u)!=dsu.find(edge.v)){        //若未连接
            dsu.unite(edge.u,edge.v);
            mst.push_back(edge);
            total+=edge.weight;
        }
    }
    cout<<"最小生成树的总权重为："<<total<<endl;
    cout<<"最小生成树的边为："<<endl;
    for(const auto& edge:mst){
        cout<<edge.u<<"--"<<edge.v<<"(权重："<<edge.weight<<")"<<endl;
    }
}

/*拓扑排序问题*/
//拓扑排序只能运用于有向无环图，有两种实现方式
//基于入度的实现，能够快速检测途中是否存在环
//时间复杂度：O(V+E)
//空间复杂度：O(V)
vector<int> topologicalSort_Kahn(const vector<vector<int>>& adj){
    int V=adj.size();
    vector<int> inDegree(V,0);
    for(int u=0;u<V;u++){        //计算所有顶点的入度
        for(int v:adj[u]){
            inDegree[v]++;
        }
    }
    queue<int> q;
    for(int i=0;i<V;i++){        //将入度为0的点放入队列
        if(inDegree[i]==0){
            q.push(i);
        }
    }
    vector<int> result;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        result.push_back(u);
        for(int v:adj[u]){
            inDegree[v]--;       //遍历u的邻居，将u抹去，邻居入度减一
            if(inDegree[v]==0){  //入度减为0，放入队列
                q.push(v);
            }
        }
    }
    if(result.size()!=V){        //若结果数量不为V，说明存在环
        return {};
    }
    return result;
}
//基于DFS的实现，DFS有递归与非递归两种实现方式
//但值得注意的是利用DFS需要额外的环检测逻辑，此处假设输入均为DAG，因此程序能够正常运行
//基于非递归DFS实现拓扑排序
//时间复杂度：O(V+E)
//空间复杂度：O(V)
vector<int> topologicalSort_DFS(const vector<vector<int>>& adj){
    int V=adj.size();
    vector<bool> visited(V,0);     //状态数组
    vector<int> result;            //排序结果
    stack<int> s;
    for(int i=0;i<V;i++){
        if(!visited[i]){
            s.push(i);
            while(!s.empty()){
                int u=s.top();
                if(!visited[u]){         //标记搜索过节点
                    visited[u]=1;
                }
                bool key=0;
                for(int v:adj[u]){
                    if(!visited[v]){     //若找到一个未访问的邻居则继续向下搜索
                        s.push(v);
                        key=1;
                        break;           //退出循环，改为向下
                    }
                }
                if(!key){                //如果所有邻居都已访问，说明进入回溯
                    s.pop();
                    result.push_back(u);
                }
            }
        }
    }
    reverse(result.begin(),result.end());    //结果为反向的，需要反转
    return result;
}
//基于递归DFS实现拓扑排序
//DFS辅助函数
void DFSUtil_ToplogicalSort(int u,const vector<vector<int>>& adj,vector<bool>& visited,stack<int>& s){
    visited[u]=1;      //标记节点 
    for(int v:adj[u]){    //遍历邻居
        if(!visited[v]){
            DFSUtil_ToplogicalSort(v,adj,visited,s);
        }
    }
    s.push(u);      //相比于普通DFS多了stack用于回溯，将顶点压入栈
}

vector<int> topologicalSort_DFS2(const vector<vector<int>>& adj){
    int V=adj.size();
    vector<bool> visited(V,0);
    stack<int> s;
    for(int i=0;i<V;i++){       //对所有未标记节点进行DFS
        if(!visited[i]){
            DFSUtil_ToplogicalSort(i,adj,visited,s);
        }
    }
    vector<int> result;
    while(!s.empty()){      //将结果从stack转移到result
        result.push_back(s.top());
        s.pop();
    }
    return result;
}