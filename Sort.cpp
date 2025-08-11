#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<random>
#include<chrono>
#include<list>

using namespace std;

/*冒泡排序*/
//时间复杂度（平均/最坏）：O(N^2)/O(N^2)
//空间复杂度：O(1)
void bubble_Sort(vector<int>& arr){
    int n=arr.size();
    for(int i=0;i<n-1;i++){      //每次将较大的数向右边移动
        for(int j=0;j<n-i-1;j++){     //内外循环，消除所有逆序对
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}
//加入标志符
//如果一轮循环没有发生交换则意味排序完成，提前终止
void bubble_Sort_flag(vector<int>& arr){
    int n=arr.size();
    bool swapped=0;      //标志
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                swapped=1;
            }
        }
        if(!swapped){       //一次遍历后若为发生交换，说明有序
            break;
        }
    }
}
//记录最后一次交换位置
//进一步缩小比较范围
void bubble_Sort_lastSwap(vector<int>& arr){
    int n=arr.size();
    int last_swap_pos=n-1;
    int cur_boundary=n-1;
    while(cur_boundary>0){      //边界右边已排好序
        last_swap_pos=0;
        for(int j=0;j<cur_boundary;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                last_swap_pos=j;
            }
        }
        cur_boundary=last_swap_pos;
        if(last_swap_pos==0){     //同样的标志
            break;
        }
    }
}


/*选择排序*/
//时间复杂度（平均/最坏）：O(N^2)/O(N^2)
//空间复杂度：O(1)
void select_Sort(vector<int>& arr){
    int n=arr.size();
    for(int i=0;i<n-1;i++){
        int min_idx=i;
        for(int j=i+1;j<n;j++){     //每次遍历选择最小值
            if(arr[j]<arr[min_idx]){
                min_idx=j;
            }
        }
        if(min_idx!=i){      //将最小值放在左边
            swap(arr[i],arr[min_idx]);
        }
    }
}
//同时选出最大值和最小值
void select_Sort_twoway(vector<int>& arr){
    int n=arr.size();
    int left=0;
    int right=n-1;
    while(left<right){
        int min_idx=left;
        int max_idx=right;
        for(int i=left;i<right;i++){
            if(arr[i]<arr[min_idx]){
                min_idx=i;
            }
            if(arr[i]>arr[max_idx]){
                max_idx=i;
            }
        }
        if(min_idx!=left){
            swap(arr[left],arr[min_idx]);
        }
        if(max_idx!=right){
            swap(arr[right],arr[max_idx]);
        }
        left++;       //逐步缩小比较范围
        right--;
    }
}


/*插入排序*/
//时间复杂度（平均/最坏）：O(N^2)/O(N^2)
//空间复杂度：O(1)
void insert_Sort(vector<int>& arr){
    int n=arr.size();
    for(int i=1;i<n;i++){    //从第二个元素开始插入
        int key=arr[i];      
        int j=i-1;
        while(j>=0&&arr[j]>key){     //像扑克一样，将牌逐步插入到有序列中
            arr[j+1]=arr[j];         //即只需找出需要插入的位置
            j--;
        }
        arr[j+1]=key;
    }
}
//优化查找方式，利用二分查找寻找key值位置
void insert_Sort_binary(vector<int>& arr){
    int n=arr.size();
    for(int i=1;i<n;i++){
        int key=arr[i];
        auto it=upper_bound(arr.begin(),arr.begin()+i,key);  //返回[begin，begin+i)中都一个大于等于key迭代器
        int pos=distance(arr.begin(),it);   //返回begin和it之间的元素数量
        if(pos<i){
            for(int j=i;j>pos;j--){
                arr[j]=arr[j-1];
            }
            arr[pos]=key;
        }
    }
}
//对于插入排序的移动问题
//每次移动一个元素，若很小的元素出现在数组末尾，需要大量的比较和移动
//希尔排序通过使用更大的增量，能先将小元素进行快速移动，提升有序程度
//因而提高效率，时间复杂度在O(N^1~2)之间
void shell_Sort(vector<int>& arr){
    int n=arr.size();
    for(int gap=n/2;gap>0;gap/=2){    //将增量设置为一半
        for(int i=gap;i<n;i++){
            int temp=arr[i];
            int j;
            for(int j=i;j>=gap&&arr[j-gap]>temp;j-=gap){
                arr[j]=arr[j-gap];    //逐步进行插入排序
            }
            arr[j]=temp;
        }
    }
}


/*快速排序*/
//时间复杂度（平均/最坏）：O(NlogN)/O(N^2)
//空间复杂度：O(logN)
//分区，找到一个基准，使得基准左边值都小于基准值，右边值都大于基准值
int partition(vector<int>& arr,int low,int high){
    int pivot=arr[high];     //每次选取最右边数为基准值
    int i=low-1;
    for(int j=low;j<high;j++){
        if(arr[j]<=pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}
//优化方案可以从基准值的选取入手
//如随机选取基准值或者从low，mid，high中选取中间值作为基准值
int partition_random(vector<int>& arr,int low,int high){
    random_device rd;    //randon_device是非确定性随机数生成器，为随机引擎提供高质量种子
    mt19937 eng(rd());   //mt19937是伪随机引擎，eng为创建的引擎对象，用于生成随机数
    uniform_int_distribution<int> int_dist(low,high);    //均匀整数分布，相应还有real，实数分布
    int idx=int_dist(eng);
    int privot=arr[idx];
    int i=low-1;
    for(int j=low;j<=high;j++){
        if(arr[j]<=privot){
            i++;
            swap(arr[j],arr[i]);
        }
    }
    swap(arr[i+1],arr[idx]);
    return i+1;
}

int partition_mid(vector<int>& arr,int low,int high){
    int mid=(low+high)/2;
    int idx=arr[low]>arr[mid]?low:mid;
    idx=arr[idx]<arr[high]?idx:high;
    int privot=arr[idx];
    int i=low-1;
    for(int j=low;j<=high;j++){
        if(arr[j]<privot){
            i++;
            swap(arr[j],arr[i]);
        }
    }
    swap(arr[i+1],arr[idx]);
    return i+1;
}
//递归实现，逐步分区至只有一个元素后停止
//若每次基准能找到中位数，最快只需logN
//若基准值每次选取最值，则为最坏情况，需N^2
void quick_Sort(vector<int>& arr,int low,int high){
    if(low<high){
        int pi=partition(arr,low,high);
        quick_Sort(arr,low,pi-1);
        quick_Sort(arr,pi+1,high);
    }
}
//此外，若数组中有大量重复元素，可以分为大于，等于，小于三个区
//只对大于和小于两个区进行递归也可以提升效率
void partition_three_way(vector<int>& arr,int low,int high,int& lt,int& gt){
    int pivot=arr[low];      //此处仍用最左边值为基准，可进一步优化
    lt=low;
    gt=high;     //双指针
    int i=low+1;
    while(i<=gt){
        if(arr[i]<pivot){
            swap(arr[lt++],arr[i++]);
        }
        else if(arr[i]>pivot){
            swap(arr[gt--],arr[i]);
        }
        else{
            i++;
        }
    }
}

void quick_Sort_three_way(vector<int>& arr,int low,int high){
    if(low<high){
        int lt,gt;
        partition_three_way(arr,low,high,lt,gt);
        quick_Sort_three_way(arr,low,lt-1);
        quick_Sort_three_way(arr,gt+1,high);
    }
}


/*归并排序*/
//时间复杂度（平均/最坏）：O(NlogN)/O(NlogN)
//空间复杂度：O(N)
//将数组不断细分，将子数组合并成有序数组，再将有序数组合并完成排序
void merge(vector<int>& arr,int left,int mid,int right){
    int n1=mid-left+1;
    int n2=right-mid;
    vector<int> L;
    vector<int> R;
    for(int i=0;i<n1;i++){
        L.push_back(arr[left+i]);
    }
    for(int i=0;i<n2;i++){
        R.push_back(arr[mid+1+i]);
    }
    int i=0;
    int j=0;
    int k=left;
    while(i<n1&&j<n2){
        if(L[i]<=R[j]){
            arr[k++]=L[i++];
        }
        else{
            arr[k++]=R[j++];
        }
    }
    while(i<n1){
        arr[k++]=L[i++];
    }
    while(j<n2){
        arr[k++]=R[j++];
    }
}

void merge_Sort(vector<int>& arr,int left,int right){
    if(left<right){
        int mid=left+(right-left)/2;
        merge_Sort(arr,left,mid);
        merge_Sort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}


/*堆排序*/
//时间复杂度（平均/最坏）：O(NlogN)/O(NlogN)
//空间复杂度：O(1)
void heapify(vector<int>& arr,int n,int i){
    int largest=i;     //子堆的根节点
    int left=2*i+1;    //左子节点
    int right=2*i+2;   //右子节点
    if(left<n&&arr[left]>arr[largest]){
        largest=left;
    }
    if(right<n&&arr[right]>arr[largest]){
        largest=right;
    }
    if(largest!=i){
        swap(arr[i],arr[largest]);
        heapify(arr,n,largest);     //发生交换后要对子树进行重新堆化
    }
}

void heap_Sort(vector<int>& arr){
    int n=arr.size();
    for(int i=n/2-1;i>=0;i--){     //从最后一个非叶子节点开始构建最大堆
        heapify(arr,n,i);
    }
    for(int i=n-1;i>0;i--){        //建成最大堆后，最大值位于根节点
        swap(arr[0],arr[i]);       //将根节点逐步放入末尾
        heapify(arr,i,0);          //重新堆化
    }
}


/*计数排序*/
//时间复杂度：O(N+K)
//空间复杂度：O(N+K)
//在数据范围K不大的情况下，时间复杂可达线性，总体是用空间换时间
//且只能排序非负整数
void counting_Sort(vector<int>& arr){
    int max_val=*max_element(arr.begin(),arr.end());
    vector<int> count_arr(max_val+1,0);        //创建数组，并初始化为0
    for(int num:arr){
        count_arr[num]++;      //统计每个元素出现的次数
    }
    for(int i=1;i<=max_val;i++){
        count_arr[i]+=count_arr[i-1];      //确定每个元素的最终位置
    }
    vector<int> output_arr(arr.size());
    for(int i=arr.size()-1;i>=0;--i){      //从后开始遍历数组，将元素放在正确的位置
        int cur_val=arr[i];
        int pos=count_arr[cur_val]-1;
        output_arr[pos]=cur_val;
        count_arr[cur_val]--;
    }
    arr=output_arr;
}


/*桶排序*/
//时间复杂度（平均/最坏）：O(N+K)/O(N^2)
//空间复杂度：O(N+K)
//将元素分配到不同桶中，在将各个桶排序合并结果
void sort_for_list(list<float>& bucket){   //由于每个桶内的数据一般不大，此处采用插入排序
    vector<float> temp_arr(bucket.begin(),bucket.end());    //list为双向链表，在读取方面不佳，故建立临时vector
    int n=temp_arr.size();      
    for(int i=1;i<n;i++){
        float key=temp_arr[i];
        int j=i-1;
        while(j>=0&&temp_arr[j]>key){
            temp_arr[j+1]=temp_arr[j];
            j--;
        }
        temp_arr[j+1]=key;
    }
    bucket.assign(temp_arr.begin(),temp_arr.end());
}
//之所以选择list作为桶，是在内存与插入方面综合考虑的结果
//同时，桶排序的性能取决于桶的数量
//若N=K，此时性能最好，即一个桶中仅有一个元素，与计数排序效果相同
void bucket_Sort(vector<int>& arr){
    int n=arr.size();
    float max_val=*max_element(arr.begin(),arr.end());
    float min_val=*min_element(arr.begin(),arr.end());
    if(max_val==min_val){
        return;
    }
    const int num_bucket=10;        //简单选择10个桶
    vector<list<float>> bucket(num_bucket);       //创建桶
    for(float val:arr){
        int index_bucket=static_cast<int>(num_bucket*(val-min_val)/(max_val-min_val));     //计算桶索引
        if(index_bucket==num_bucket){       //防止数组越界，将最大值放入最后一个桶
            index_bucket--;
        }
        bucket[index_bucket].push_back(val);
    }
    for(int i=0;i<num_bucket;i++){      //将每个桶进行排序
        sort_for_list(bucket[i]);
    }
    int index=0;
    for(int i=0;i<num_bucket;i++){      //合并结果
        for(float val:bucket[i]){       //注意，后一个桶中的数值一定比前一个大
            arr[index++]=val;
        }
    }
}


/*基数排序*/
//时间复杂度：O(d*(N+K))    d是最大元素的位数
//空间复杂度：O(N+K)
//通过位数来划分元素，利用其他算法对逐位进行排序，从而实现排序
//但同样适用于整数
int getDigit(int num,int exp){     //获得指定位数上的数
    return (num/exp)%10;
}

void sort_for_digit(vector<int>& arr,int exp){
    int n=arr.size();
    vector<int> output(n);
    vector<int> count(10,0);      //采用计数排序对每一位进行排序
    for(int i=0;i<n;i++){
        int digit=getDigit(arr[i],exp);
        count[digit]++;
    }
    for(int i=1;i<10;i++){
        count[i]+=count[i-1];
    }
    for(int i=n-1;i>=0;i--){
        int digit=getDigit(arr[i],exp);
        output[count[digit]-1]=arr[i];
        count[digit]--;
    }
    arr=output;
}

void radix_Sort(vector<int>& arr){
    int max_val=*max_element(arr.begin(),arr.end());   //利用最大值计算出计数排序次数
    for(int exp=1;max_val/exp>0;exp*=10){
        sort_for_digit(arr,exp);
    }
}


int main(){
    while(1){
        cout<<"--------------------"<<endl;
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<int> int_dist(0,100);
        vector<int> arr;
        for(int i=0;i<10;i++){
            arr.push_back(int_dist(eng));
        }
        for(int i=0;i<arr.size();i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
        int choice=0;
        cout<<"欢迎使用排序算法！"<<endl;
        cout<<"0.quit"<<endl;
        cout<<"1.bubble_sort"<<endl;
        cout<<"2.select_sort"<<endl;
        cout<<"3.insert_sort"<<endl;
        cout<<"4.quick_sort"<<endl;
        cout<<"5.merge_sort"<<endl;
        cout<<"6.heap_sort"<<endl;
        cout<<"7.count_sort"<<endl;
        cout<<"8.bucket_sort"<<endl;
        cout<<"9.radix_sort"<<endl;
        cin>>choice;
        switch(choice){
            case 0:{
                return 0;
            }
            case 1:{
                int choice2=0;
                cout<<"1.bubble_Sort"<<endl;
                cout<<"2.bubble_Sort_flag"<<endl;
                cout<<"3.bubble_Sort_lastSwap"<<endl;
                cin>>choice2;
                switch(choice2){
                    case 1:{
                        bubble_Sort(arr);
                        break;
                    }
                    case 2:{
                        bubble_Sort_flag(arr);
                        break;
                    }
                    case 3:{
                        bubble_Sort_lastSwap(arr);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case 2:{
                int choice2=0;
                cout<<"1.select_Sort"<<endl;
                cout<<"2.select_Sort_twoway"<<endl;
                cin>>choice2;
                switch(choice2){
                    case 1:{
                        select_Sort(arr);
                        break;
                    }
                    case 2:{
                        select_Sort_twoway(arr);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case 3:{
                int choice2=0;
                cout<<"1.insert_Sort"<<endl;
                cout<<"2.insert_Sort_binary"<<endl;
                cout<<"3.shell_Sort"<<endl;
                cin>>choice2;
                switch(choice2){
                    case 1:{
                        insert_Sort(arr);
                        break;
                    }
                    case 2:{
                        insert_Sort_binary(arr);
                        break;
                    }
                    case 3:{
                        shell_Sort(arr);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case 4:{
                int choice2=0;
                cout<<"1.quick_Sort"<<endl;
                cout<<"2.quick_Sort_three_way"<<endl;
                cin>>choice2;
                switch(choice2){
                    case 1:{
                        quick_Sort(arr,0,9);
                        break;
                    }
                    case 2:{
                        quick_Sort_three_way(arr,0,9);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case 5:{
                merge_Sort(arr,0,9);
                break;
            }
            case 6:{
                heap_Sort(arr);
                break;
            }
            case 7:{
                counting_Sort(arr);
                break;
            }
            case 8:{
                bucket_Sort(arr);
                break;
            }
            case 9:{
                radix_Sort(arr);
                break;
            }
            default:
                break;
        }
        for(int i=0;i<arr.size();i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}