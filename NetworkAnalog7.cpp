#include <string>
#include <cstring>
#include <iostream>
#include<stdlib.h>
#include <time.h> 

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
    string password;
    string name;
    VertexType data;
    address IP;
    int secret_key;
    int public_key;

    int generatekey();
    int generate_secret_key(int secret_key);
}Node;

//图结构体定义
typedef struct 
{
    string User;
    Node* VertexGateher[MaxVertexnum];
    EdgeType AdjacentMatrix[MaxVertexnum][MaxVertexnum];
    int Vertex,Edge;
}AdjacentMatrixGraph;


int generatekey(){
    srand((unsigned)time( NULL)); 
    return rand()%100;
}
//欧几里得算法求d：（提供两种算法求d，下面还有qiud()函数）
int olg(int e, int h)    //h=e*a[0]+r[0]  辗转相除法
{
    int i;
    int k=1;//计算商的个数
    int d;
    int a[50] = { 0 }, r[50] = { 0 }, b[50] = { 0 };//a 商 r 余
    a[0] = h/e;   //取第一个商 
    r[0] = h%e;   //取第一个余数                                                  
    a[1] = e/r[0];//取第二个商 
    r[1] = e%r[0];//取第二个余数 
    for (i=2;;i++){
        a[i]=r[i-2]/r[i-1];
        r[i]=r[i-2]%r[i-1];
        if(r[i]==0)break;
        k++;
    }
    b[0] = a[k];
    b[1] = b[0]*a[k-1]+1;
    for (i = 2; i <= k; i++){
        b[i] = a[k-i] * b[i-1] + b[i-2];
    }
    if ((k-1)%2!=0)  // 计算商的时候最后一个余数为零的商除去
        d = h-b[k]; //当K-1为奇数时
    if ((k-1)%2==0) 
        d = b[k];  //当k-1为偶数时
    return d;
}

//利用i循环自增满足 ab mod φ(n) = 1 的条件得到d
int qiud(int a, int b) { 
    int i = 1;
    for (; ((a * i) % b) != 1;) {  //  ab mod φ(n) = 1   
        i++;
    }
    return i;
}

int generate_secret_key(int i){
    int q = 5;
    int p = 7;
    int n = p * q; //计算n
    int h = (p - 1) * (q - 1); // 计算Eular函数值φ(n)

    //return qiud(e, h); // 计算d的值，两种算法都可以
    return olg(i, h); //这里用欧几里得算法求d
}


/*
typedef struct{
    char IPAdressSecter[4];
    int Top;
}IPStack;
*/

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


//搜索IP
char* trans(char* str_new){
    string str_n = "";
    str_n.append(str_new);
    char* str = (char*)str_n.data();
    cout<<str<<endl;
    const char *split = ".";
    string Target;
    char *p2 = strtok(str,split);
    int temp[4];
    int i=0;
    while( p2 != NULL ){
        //cout<<p2<<endl;
        temp[i]= atoi(p2);//字符串转数字的函数
        p2 = strtok(NULL,split);
        i++;
    }

    //转换，采用栈或者用除法形成单个数值也可以
    //cout<<"字符串转换:";
    for(i=3;i>=0;i--){
        int tempint = temp[i];
        int i = 8;
        while(tempint > 0){
            int newtemp = tempint % 2;
            tempint = tempint / 2;
            char tempstr[32] = "";
            sprintf(tempstr,"%d",newtemp);

            Target.insert(0,tempstr);
            i--;
        }
        while(i>0){
            Target.insert(0,"0");
            i--;
        }   
    }
    //cout<<"Target:"<<Target<<endl;
    char* q = (char*) Target.data();
    return q;
}


int SearchIP(AdjacentMatrixGraph adj,char* target){
    //question 返回指针的函数 多次调用会使之前调用的返回值跟着改变
    char* trans_target = trans(target);
    string x;
    x.append(trans_target);

    char* new_x = (char*)x.data();
    cout<<"Target:"<<trans_target<<endl;
    for(int i = 0;i<adj.Vertex;i++){
        char* IP_temp=(char*)adj.VertexGateher[i]->IP.data();
        char* trans_IP = trans(IP_temp);
        cout<<"注意："<<trans_IP<<trans_target<<endl;
        if(strcmp(new_x,trans_IP) == 0){
            return i;
        }
    }
    return -1;

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
/*
void hashcode(Node* self){
    char* psw = (char*)self->password.data();
    int i = p.length(self->password);
    for(int m = 0;m<i;m++){
        
    }
}
*/
string hashcode(string self){
    char* psw = (char*)self.data();
    int i = strlen(psw);
    string target;
    int temp;
    char temp_psw[58] = {};
    char a[3] = "";
    for(int m = 0;m < i;m++){
        temp = (int)psw[m]*(int)psw[m];
        temp = (temp % (122-65)) + 65;
        while(temp_psw[temp-65] != '\0'){
            temp = 2 * m * temp;
            temp = (temp % 57) +65;
        }
            sprintf(a,"%c",temp);
            temp_psw[temp-65] = a[0];    
    }
    for(int q=0;q<57;q++){
            if(temp_psw[q] != ' '){
                a[0] = temp_psw[q];
                target.append(a);
            }
        }
    //cout<<target<<endl;
    return target;
    //char* tar = (char*)target.data();
    //return tar;
}

void sendmessage(Node* self,Node* temp1){
    temp1->data.append("\n");
    temp1->data.append(self->name);
    temp1->data.append("发来消息:");
    temp1->data.append(self->data);
    return;
}

int rsa(int b, int a, int c) { 
    int i = 1;
    while (a != 0) {
        i = i * b;
        i = i % c;
        a--;  //*一次 %一次 
    }
    return i;
}

string code(int e,string message_new,int n){
    //cout<<message_new<<endl;
    char* message = (char*)message_new.data();
    int i = strlen(message);
    int m=0;
    for(m=0;m < i;m++){
        message[m] = rsa(message[m],e,n);
    }

    string str;
    str.append(message);
    cout<<str<<endl;
    return str;
}



void send(Node* self,Node* temp1){
    cout<<"请输入要发送的消息:"<<endl;
    char message[50] = "";
    cin.getline(message,49);
    //string str;
    //str.append(message);
    cout<<"正在加密"<<endl;
    int n = temp1->public_key;
    string message_target;
    message_target.append(message);
    message_target = code(temp1->public_key,message_target,5*7);
    cout<<"加密完成，发送加密文件"<<endl;
    cout<<"加密后："<<message_target<<endl;


    temp1->data.append("\n");
    temp1->data.append(self->name);
    temp1->data.append("发来消息:");
    cout<<"解密后："<<code(temp1->secret_key,message_target,5*7)<<endl;
    temp1->data.append(code(temp1->secret_key,message_target,5*7));
    return;
}


//通信建立后操作
void connect(Node* self,Node* temp1){
    cout<<self->name<<"和"<<temp1->name<<"已连接"<<endl;
    int option;
    while(1){
        printf("=======================\n");
        printf("Select your actions:\n");
        cout<<"1:传输本地消息"<<endl;
        //cout<<"2:实时加密发送"<<endl;
        cout<<"0:断开连接"<<endl;
        printf("=======================\n");
        scanf("%d",&option);
        getchar();
        if(option == 0){
            break;
        }
        switch(option){
            case 2:send(self,temp1);break;
            case 1:sendmessage(self,temp1);break;
        }
    }
    cout<<"断开连接"<<endl;
}

//用户连接节点函数
void pin(AdjacentMatrixGraph adj,Node* self){
    string name;
    string IP;
    cout<<"可选择："<<endl;
    cout<<"1:搜索用户是否在此网络"<<endl;
    cout<<"2:按IP连接"<<endl;
    cout<<"其他按键退出"<<endl;
    int temp;
    cout<<"输入：";
    scanf("%d",&temp);
    getchar();
    if(temp == 1){
        char s[21];
        cout<<"输入用户昵称:";
        cin.getline(s,20);
        name.append(s);
        char* txt = (char *)adj.User.data();
        if(KMP(txt,s) != -1)cout<<"successfully find:"<<s<<endl;
        else cout<<"not find"<<endl;
        pin(adj,self);
    }
    else if(temp == 2){
        char s4[21];
        //getchar();
        cout<<"输入要连接的IP"<<endl;
        cin.getline(s4,20);
        int index = SearchIP(adj,s4);
        if(index == -1){cout<<"不存在此IP"<<endl; pin(adj,self);}
        else{
            Node* temp1 = adj.VertexGateher[index];
            connect(self,temp1);
        }
    }
    else return;
}

//建立节点
Node* BulidNode(){
    Node* node =  (Node*)malloc(sizeof(Node));
    char s1[20] = "";
    char s2[20] = "";
    char s3[20] = "";
    char s4[20] = "";
    char s5[20] = "";
    node->name = "";
    node->IP = "";
    node->password = "";
    node->data = "";
    //question：不能使用node->generatekey 原因有待继续研究
    node->public_key = generatekey();
    node->secret_key = generate_secret_key(node->public_key);

    //cout<<"s1:"<<s1<<endl;
    cout<<"输入用户名称";
    //getchar();//吃掉之前的回车
    cin.getline(s3,50);
    cout<<endl;
    node->name.append(s3);


    cout<<"输入节点数据";    
    cin.getline(s1,50);
    cout<<endl;
    node->data.append(s1);


    cout<<"输入IP";
    cin.getline(s2,50);
    cout<<endl;
    node->IP.append(s2);
    int i=3;
    while(i){
    cout<<"设定密码"; 
    scanf("%s",s4);
    getchar();
    cout<<endl;
    cout<<"确认密码";
    scanf("%s",s5);
    getchar();
    if(strcmp(s4,s5)!=0){
        cout<<"两次密码不一致，请重新设定"<<endl;
        i--;
        }
    else{
        node->password.append(s4);
        break;
    }
    }
    node->public_key = generatekey();
    node->secret_key = generate_secret_key(node->public_key);
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
    getchar();
    for(int i=edge ;i > 0 ;i--){
        int q,m;
        cout<<"与网络中节点的关系"<<endl;
        scanf("%d,%d",&q,&m);
        getchar();
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
    if(m > adj->Vertex || m <= 0)
    {
        cout<<"没有此节点"<<endl;
        return;
    }

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
    temp = NULL;
    adj->VertexGateher[adj->Vertex-1] = NULL;
    adj->Vertex--;

}


void changepsw(Node* node){
    char s4[20] = "";
    char s5[20] = "";
    int i=3;
    while(i){
    cout<<"设定密码"; 
    scanf("%s",s4);
    getchar();
    cout<<endl;
    cout<<"确认密码";
    scanf("%s",s5);
    getchar();
    if(strcmp(s4,s5)!=0){
        cout<<"两次密码不一致，请重新设定"<<endl;
        i--;
        }
    else{
        node->password = "";
        node->password.append(s4);
        cout<<"密码修改成功"<<endl;
        break;
    }
    }
}


void nodeshow(Node* node){
    cout<<"用户名称："<<node->name<<endl;
    cout<<"用户IP："<<node->IP<<endl;
    cout<<"节点储存信息："<<node->data<<endl;
    //cout<<"用户密码"<<node->password<<endl;
}

//成功进入某节点后功能选择
void OperateOption(AdjacentMatrixGraph* adj,int i){
    string name = adj->VertexGateher[i]->name;
    cout<<"欢迎进入"<<name<<endl;
    int option;
    while(1){
        printf("=======================\n");
        printf("Select your actions:\n");
        cout<<"1:连接用户"<<endl;
        cout<<"2:节点信息查询"<<endl;
        cout<<"3:修改密码"<<endl;
        cout<<"0:退出登陆"<<endl;
        printf("=======================\n");
        scanf("%d",&option);
        getchar();
        if(option == 0){
            break;
        }
        switch(option){
            case 3:changepsw(adj->VertexGateher[i]);break;
            case 2:nodeshow(adj->VertexGateher[i]);break;
            case 1:pin(*adj,adj->VertexGateher[i]);break;

        }
    }
    cout<<"退出用户"<<name<<endl;
}

//进入节点功能函数
void enterNode(AdjacentMatrixGraph* adj,string name){
    int temp = -1;
    for(int i=0;i<adj->Vertex;i++){
        cout<<"IP名称："<<adj->VertexGateher[i]->IP<<name<<endl;
        if(strcmp(adj->VertexGateher[i]->IP.c_str(),name.c_str())==0){
            temp=i;
            int m=3;
            while(m){
            cout<<"请输入用户密码：";
            char psw[20] = "";
            scanf("%s",psw);
            getchar();
            string psw1 = hashcode(psw);
            string psw2 = hashcode(adj->VertexGateher[i]->password);
            //cout<<"注意："<<psw1<<"   "<<psw2<<endl;

            if(psw1.compare(psw2) == 0){
                cout<<"密码正确"<<endl;
                break;
            }
            else{cout<<"密码错误"<<endl;m--;}
            }
            if(temp != -1) break;
            
            }
    }
    if(temp == -1){
        cout<<"没有此节点，进入失败"<<endl;
        return ;
    }
    else{
        OperateOption(adj,temp);
    }
}

//显示网络信息
void ShowGraph(AdjacentMatrixGraph adj){
    for(int i = 0 ; i < adj.Vertex ; i++){
        cout<<"name:\t"<<adj.VertexGateher[i]->name<<endl;
        cout<<"IP:\t"<<adj.VertexGateher[i]->IP<<endl;
        cout<<"data:\t"<<adj.VertexGateher[i]->data<<endl;
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
        node->password = "Shxy";
        node->public_key = generatekey();
        node->secret_key = generate_secret_key(node->public_key);
        return node;
    case 1:
        node->name = "LiHongXiao";
        node->data = "my name is LHX";
        node->IP = "10.10.255.1";
        node->password = "Shxy";
        node->public_key = generatekey();
        node->secret_key = generate_secret_key(node->public_key);
        return node;
        
    case 2:
        node->name = "YangTianMing";
        node->data = "my name is YTM";
        node->IP = "10.10.255.2";
        node->password = "Shxy";
        node->public_key = generatekey();
        node->secret_key = generate_secret_key(node->public_key);
        return node;
    case 3:
        node->name = "ZhangShuo";
        node->data = "my name is ZS";
        node->IP = "10.10.255.3";
        node->password = "Shxy";
        node->public_key = generatekey();
        node->secret_key = generate_secret_key(node->public_key);
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
        getchar();
        if(option == 0){
            break;
        }
        switch(option){
            case 3:AddNode(adj);break;
            case 2:DeleteNode(adj);break;
            case 1:{
                cout<<"输入要进入节点的IP"<<endl;
                char temp[17] = "";
                //getchar();
                cin.getline(temp,16);
                string IP;
                IP.append(temp);
                enterNode(adj,IP);break;
            }
            case 4:ShowGraph(*adj);break;
        }
    }
    return 0;
}






