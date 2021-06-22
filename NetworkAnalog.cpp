
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
void ConnectByName(AdjacentMatrixGraph adj,string name){
    char* txt;
    txt = (char*)malloc(sizeof(adj.User.length()));
    char nameTarget[30];
    strcpy(nameTarget,name.c_str());
    cout<<name<<endl;
    printf("%s",nameTarget);
    //KMP(nameTarget,txt);
}
//用户连接节点函数
void pin(AdjacentMatrixGraph adj){
    string name;
    string IP;
    cout<<"选择连接目标用户的连接方式："<<endl;
    cout<<"1:按名字连接"<<endl;
    cout<<"2:按IP连接"<<endl;
    cout<<"其他按键退出"<<endl;
    int temp;
    scanf("%d",&temp);
    if(temp == 1){
        char s[21];
        getchar();
        cin.getline(s,20);
        name.append(s);
        ConnectByName(adj,name);
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
    //cout<<"s1:"<<s1<<endl;
    cout<<"输入节点数据";
    getchar();//吃掉之前的回车
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
    
    return;
    
}
void DeleteChange(AdjacentMatrixGraph* adj,int m){
    for(int i=0;i<adj->Vertex;i++){
        adj->AdjacentMatrix[m-1][i] = adj->AdjacentMatrix[adj->Vertex-1][i];
    }

    for(int i=0;i<adj->Vertex;i++){
        adj->AdjacentMatrix[i][m-1] = adj->AdjacentMatrix[i][adj->Vertex-1];
    }

}
void DeleteNode(AdjacentMatrixGraph* adj){
    int m;
    cout<<"选择要删除的节点"<<endl;
    cin>>m;
    DeleteChange(adj,m);
    adj->VertexGateher[m-1] = adj->VertexGateher[adj->Vertex-1];
    for(int i= 0 ;i<adj->Vertex;i++){
        adj->AdjacentMatrix[adj->Vertex-1][i] = 0;
        adj->AdjacentMatrix[i][adj->Vertex-1] = 0;
    }
    adj->VertexGateher[adj->Vertex-1] = NULL;
    adj->Vertex--;
}
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

void enterNode(AdjacentMatrixGraph* adj,string name){
    int temp = 0;
    for(int i=0;i<adj->Vertex;i++){
        cout<<"IP名称："<<adj->VertexGateher[i]->IP<<name<<endl;
        if(adj->VertexGateher[i]->IP.equal(name))break;
    }
    if(temp == 0){
        cout<<"没有此节点，进入失败";
        return ;
    }
    else{
        OperateOption(adj,name);
    }
}
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
Node* DefaultBulidNode(int n){
    Node* node =  (Node*)malloc(sizeof(Node));
    switch (n)
    {
    case 0:
        node->data = "my name is LYL";
            node->IP = "10.10.255.0";
        return node;
    case 1:
        node->data = "my name is LHX";
            node->IP = "10.10.255.1";
        return node;
        
    case 2:
        node->data = "my name is YTM";
            node->IP = "10.10.255.2";
        return node;
    case 3:
        node->data = "my name is ZS";
            node->IP = "10.10.255.3";
        return node;
    }
    return NULL;
}
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
    }
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
        printf("0:exit");
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



