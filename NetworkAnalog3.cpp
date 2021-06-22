#include <string>
#include <cstring>
#include <iostream>
using namespace std;
#define MaxVertexnum 100
#define datasize 100
#define adresssize 32
#define datasize 100
#define YES 1
#define NO 0
typedef int state;
//typedef int address;
//typedef char VertexType;
typedef string address;
typedef string VertexType;
typedef int EdgeType;
//节点结构体定义
typedef struct Node{
    //string password;
    string name;
    VertexType data;
    address IP;
}Node;
//图结构体定义
typedef struct 
{
    string User;
    Node* VertexGateher[MaxVertexnum];
    EdgeType AdjacentMatrix[MaxVertexnum][MaxVertexnum];
    int Vertex,Edge;
}AdjacentMatrixGraph;

void getNext(int next[],char* target){
	int j,k;
    int temp = strlen(target);
	j=0;
    k=-1;
	next[0]=-1;//第一个字符前无字符串，给值-1
	while (j<temp-1){
	//因为next数组中j最大为t.length-1,而每一步next数组赋值都是在j++之后
	//所以最后一次经过while循环时j为t.length-2
		if (k==-1 || target[j]==target[k]) 	//k为-1或比较的字符相等时
		{	
			j++;k++;
			next[j]=k;
			//对应字符匹配情况下，s与t指向同步后移
			//通过字符串"aaaaab"求next数组过程想一下这一步的意义
			//printf("(1) j=%d,k=%d,next[%d]=%d\n",j,k,j,k);
       	}
       	else
		{
			k=next[k];
			//我们现在知道next[k]的值代表的是下标为k的字符前面的字符串最长相等前后缀的长度
			//也表示该处字符不匹配时应该回溯到的字符的下标
			//这个值给k后又进行while循环判断，此时t.data[k]即指最长相等前缀后一个字符**
			//为什么要回退此处进行比较，我们往下接着看。其实原理和上面介绍的KMP原理差不多
			//printf("(2) k=%d\n",k);
		}
	}
}

int KMP(char* txt,char* target){
    int s1 = strlen(target);
    int s2 = strlen(txt);
    int next[s1];
    cout<<target<<endl;
    getNext(next,target);
    int i=0,j=0;
	while (i<s2 && j<s1){
		if (j == -1 || txt[i]==target[j]) 
		{
			i++;j++;  			//i,j各增1
		}
		else j=next[j]; 		//i不变,j后退，现在知道为什么这样让子串回退了吧
    }
    if (j>=s1)
		return(i-s1);  	//返回匹配模式串的首字符下标
    else  
		return(-1);  

}

void ConnectByName(AdjacentMatrixGraph adj,string name){
    char* txt;
    txt = (char*)malloc(sizeof(adj.User.length()));
    char nameTarget[30];
    //strcpy  copy
    strcpy(nameTarget,name.c_str());
    //cout<<name<<endl;
    //printf("%s\n",nameTarget);
    int i = KMP(nameTarget,txt);
    
    
    return;
}
//用户连接节点函数
void pin(AdjacentMatrixGraph adj){
    string name;
    string IP;
    cout<<"可选择："<<endl;
    cout<<"1:搜索用户是否在此网络"<<endl;
    cout<<"2:按IP连接"<<endl;
    cout<<"其他按键退出"<<endl;
    int temp;
    cout<<"输入：";
    scanf("%d",&temp);
    if(temp == 1){
        char s[21];
        getchar();
        cin.getline(s,20);
        name.append(s);
        ConnectByName(adj,name);
        cout<<"success"<<endl;
        pin(adj);
    }
    else if(temp == 2){

    }
    else return;
}
//建立节点
Node* BulidNode(){
    Node* node =  (Node*)malloc(sizeof(Node));
    char s1[20] = "";
    char s2[20] = "";
    char s3[20] = "";
    //cout<<"s1:"<<s1<<endl;
    cout<<"输入用户名称";
    getchar();//吃掉之前的回车
    cin.getline(s3,50);
    cout<<endl;
    node->name.append(s3);

    cout<<"输入节点数据";
    
    cin.getline(s1,50);
    cout<<endl;
    node->data.append(s1);
    printf("%s",s1);

    cout<<"输入IP";
    
    cin.getline(s2,50);
    cout<<endl;
    printf("%s",s2);
    node->IP.append(s2);

    return node;
    
}
//增加节点
void AddNode(AdjacentMatrixGraph* adj){
    Node* node = BulidNode();
    adj->VertexGateher[adj->Vertex] = node;
    adj->Vertex++;
    int edge;
    cout<<"边的个数"<<endl;
    scanf("%d",&edge);
    for(int i=edge ;i > 0 ;i--){
        int q,m;
        cout<<"与网络中节点的关系"<<endl;
        scanf("%d,%d",&q,&m);
        adj->AdjacentMatrix[adj->Vertex-1][q-1] = m;
        adj->AdjacentMatrix[q-1][adj->Vertex-1] = m;
    }
    adj->User.append(node->name);
    return;
    
}
//删除节点的辅助功能
void DeleteChange(AdjacentMatrixGraph* adj,int m){
    for(int i=0;i<adj->Vertex;i++){
        adj->AdjacentMatrix[m-1][i] = adj->AdjacentMatrix[adj->Vertex-1][i];
    }

    for(int i=0;i<adj->Vertex;i++){
        adj->AdjacentMatrix[i][m-1] = adj->AdjacentMatrix[i][adj->Vertex-1];
    }

}
//kmp搜寻子串的删除操作
void UserDelete(string* txt,string target){
    //.data string类型转char*
    char* p = (char*) (*txt).data();
    char* q = (char*) target.data();
    int tar = KMP(p,q);
    cout<<"目标字符串下标"<<tar<<endl;
    cout<<target<<endl;
    cout<<p<<endl;
    cout<<q<<endl;
    if(tar == -1){
        cout<<"没有此用户名"<<endl;
    }
    else (*txt).erase(tar,target.length());
    /*
    int i=0;
    while(i<target.length()+2){
    }
    */
}
//删除节点
void DeleteNode(AdjacentMatrixGraph* adj){
    int m;//第m个元素
    cout<<"选择要删除的节点"<<endl;
    cin>>m;
    Node* temp = adj->VertexGateher[m-1];
    DeleteChange(adj,m);
    adj->VertexGateher[m-1] = adj->VertexGateher[adj->Vertex-1];
    for(int i= 0 ;i<adj->Vertex;i++){
        adj->AdjacentMatrix[adj->Vertex-1][i] = 0;
        adj->AdjacentMatrix[i][adj->Vertex-1] = 0;
    }

    temp->name.append(";");
    UserDelete(&(adj->User),temp->name);
    free(temp);
    adj->VertexGateher[adj->Vertex-1] = NULL;
    adj->Vertex--;

}
//成功进入某节点后功能选择
void OperateOption(AdjacentMatrixGraph* adj,string name){
    cout<<"欢迎进入"<<name<<endl;
    int option;
    while(1){
        printf("=======================\n");
        printf("Select your actions:\n");
        cout<<"1:连接用户"<<endl;
        cout<<"2:"<<endl;
        cout<<"3:"<<endl;
        printf("=======================\n");
        scanf("%d",&option);
        if(option == 0){
            break;
        }
        switch(option){
            case 3:break;
            case 2:break;
            case 1:pin(*adj);break;
            case 4:break;
        }
    }
    cout<<"退出用户"<<name<<endl;
}
//进入节点功能函数
void enterNode(AdjacentMatrixGraph* adj,string name){
    int temp = 0;
    for(int i=0;i<adj->Vertex;i++){
        cout<<"IP名称："<<adj->VertexGateher[i]->IP<<name<<endl;
        if(strcmp(adj->VertexGateher[i]->IP.c_str(),name.c_str())==0){temp=1;break;}
    }
    if(temp == 0){
        cout<<"没有此节点，进入失败"<<endl;
        return ;
    }
    else{
        OperateOption(adj,name);
    }
}
//显示网络信息
void ShowGraph(AdjacentMatrixGraph adj){
    for(int i = 0 ; i < adj.Vertex ; i++){
        cout<<"IP:"<<adj.VertexGateher[i]->IP<<endl;
        cout<<"data"<<adj.VertexGateher[i]->data<<endl;
        for(int j = 0 ;j < adj.Vertex ; j++){
           cout << adj.AdjacentMatrix[i][j];
        }
        cout << endl;
    }
}
//建立默认节点网络
Node* DefaultBulidNode(int n){
    Node* node =  (Node*)malloc(sizeof(Node));
    switch (n)
    {
    case 0:
        node->name = "LiYiLin";
        node->data = "my name is LYL";
        node->IP = "10.10.255.0";
        return node;
    case 1:
        node->name = "LiHongXiao";
        node->data = "my name is LHX";
        node->IP = "10.10.255.1";
        return node;
        
    case 2:
        node->name = "YangTianMing";
        node->data = "my name is YTM";
        node->IP = "10.10.255.2";
        return node;
    case 3:
        node->name = "ZhangShuo";
        node->data = "my name is ZS";
            node->IP = "10.10.255.3";
        return node;
    }
    return NULL;
}
//初始化网络
AdjacentMatrixGraph* start(){
    AdjacentMatrixGraph* A = (AdjacentMatrixGraph*)malloc(sizeof(AdjacentMatrixGraph));
    for(int i;i<MaxVertexnum;i++){
        for(int j;j<MaxVertexnum;j++){
            A->AdjacentMatrix[i][j] = 0;
        }
    }

    A->Edge = 4;
    A->Vertex = 4;
    
    for(int i = 0;i<A->Vertex;i++){
        Node *temp = DefaultBulidNode(i);
        if(temp)A->VertexGateher[i] = temp;
        A->User.append(A->VertexGateher[i]->name);
        A->User.append(";");
    }
    cout<<A->User<<endl;

    for(int i=0;i<A->Edge;i++){
        //A->AdjacentMatrix[i][i] = 0;
        for(int j = 0; j<i ;j++){
            A->AdjacentMatrix[j][i] = i - j;
            A->AdjacentMatrix[i][j] = i - j; 
        }
    }
    return A;
}

int main(){
    printf("=======================\n");
    printf("start network\n");
    printf("build network\n");
    AdjacentMatrixGraph* adj = start();
    printf("build finish\n");
    while(1){
        printf("=======================\n");
        printf("1:enter node\n");
        printf("2:delete node\n");
        printf("3:add node:\n");
        printf("4:show graph:\n");
        printf("0:exit\n");
        printf("=======================\n");
        int option;
        printf("Select your actions:\n");
        scanf("%d",&option);
        if(option == 0){
            break;
        }
        switch(option){
            case 3:AddNode(adj);break;
            case 2:DeleteNode(adj);break;
            case 1:enterNode(adj,"10.10.255.3");break;
            case 4:ShowGraph(*adj);break;
        }
    }
    return 0;
}



