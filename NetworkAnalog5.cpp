#include <string>
#include <cstring>
#include <iostream>
#include<stdlib.h>

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

//�ڵ�ṹ�嶨��
typedef struct Node{
    string password;
    string name;
    VertexType data;
    address IP;
}Node;

//ͼ�ṹ�嶨��
typedef struct 
{
    string User;
    Node* VertexGateher[MaxVertexnum];
    EdgeType AdjacentMatrix[MaxVertexnum][MaxVertexnum];
    int Vertex,Edge;
}AdjacentMatrixGraph;

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
	next[0]=-1;//��һ���ַ�ǰ���ַ�������ֵ-1
	while (j<temp-1){
	//��Ϊnext������j���Ϊt.length-1,��ÿһ��next���鸳ֵ������j++֮��
	//�������һ�ξ���whileѭ��ʱjΪt.length-2
		if (k==-1 || target[j]==target[k]) 	//kΪ-1��Ƚϵ��ַ����ʱ
		{	
			j++;k++;
			next[j]=k;
			//��Ӧ�ַ�ƥ������£�s��tָ��ͬ������
			//ͨ���ַ���"aaaaab"��next���������һ����һ��������
			//printf("(1) j=%d,k=%d,next[%d]=%d\n",j,k,j,k);
       	}
       	else
		{
			k=next[k];
			//��������֪��next[k]��ֵ��������±�Ϊk���ַ�ǰ����ַ�������ǰ��׺�ĳ���
			//Ҳ��ʾ�ô��ַ���ƥ��ʱӦ�û��ݵ����ַ����±�
			//���ֵ��k���ֽ���whileѭ���жϣ���ʱt.data[k]��ָ����ǰ׺��һ���ַ�**
			//ΪʲôҪ���˴˴����бȽϣ��������½��ſ�����ʵԭ���������ܵ�KMPԭ����
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
			i++;j++;  			//i,j����1
		}
		else j=next[j]; 		//i����,j���ˣ�����֪��Ϊʲô�������Ӵ������˰�
    }
    if (j>=s1)
		return(i-s1);  	//����ƥ��ģʽ�������ַ��±�
    else  
		return(-1);  

}

//����IP
char* trans(char* str){
    cout<<str<<endl;
    const char *split = ".";
    string Target;
    char *p2 = strtok(str,split);
    int temp[4];
    int i=0;
    while( p2 != NULL ){
        //cout<<p2<<endl;
        temp[i]= atoi(p2);//�ַ���ת���ֵĺ���
        p2 = strtok(NULL,split);
        i++;
    }

    //ת��������ջ�����ó����γɵ�����ֵҲ����
    cout<<"�ַ���ת��:";
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
    cout<<Target<<endl;
    char* q = (char*) Target.data();
    return q;
}


int SearchIP(AdjacentMatrixGraph adj,char* target){
    char* trans_target = trans(target);
    for(int i = 0;i<adj.Vertex;i++){
        char* IP_temp=(char*)adj.VertexGateher[i]->IP.data();
        char* trans_IP = trans(IP_temp);
        if(strcmp(trans_target,trans_IP) == 0){
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


void sendmessage(){

}

//ͨ�Ž��������
void connect(Node* self,Node* temp1){
    cout<<self->name<<"��"<<temp1->name<<"������"<<endl;
    int option;
    while(1){
        printf("=======================\n");
        printf("Select your actions:\n");
        cout<<"1:������Ϣ"<<endl;
        cout<<"2:���ܴ���"<<endl;
        cout<<"0:�Ͽ�����"<<endl;
        printf("=======================\n");
        scanf("%d",&option);
        if(option == 0){
            break;
        }
        switch(option){
            case 2:;break;
            case 1:sendmessage();break;

        }
    }
    cout<<"�Ͽ�����"<<endl;
}

//�û����ӽڵ㺯��
void pin(AdjacentMatrixGraph adj,Node* self){
    string name;
    string IP;
    cout<<"��ѡ��"<<endl;
    cout<<"1:�����û��Ƿ��ڴ�����"<<endl;
    cout<<"2:��IP����"<<endl;
    cout<<"���������˳�"<<endl;
    int temp;
    cout<<"���룺";
    scanf("%d",&temp);
    if(temp == 1){
        char s[21];
        getchar();
        cout<<"�����û��ǳ�:";
        cin.getline(s,20);
        name.append(s);
        char* txt = (char *)adj.User.data();
        if(KMP(txt,s) != -1)cout<<"successfully find:"<<s<<endl;
        else cout<<"not find"<<endl;
        pin(adj,self);
    }
    else if(temp == 2){
        char s4[21];
        getchar();
        cout<<"����Ҫ���ӵ�IP"<<endl;
        cin.getline(s4,20);
        int index = SearchIP(adj,s4);
        if(index == -1){cout<<"�����ڴ�IP"<<endl; pin(adj,self);}
        else{
            Node* temp1 = adj.VertexGateher[index];
            connect(self,temp1);
        }
    }
    else return;
}

//�����ڵ�
Node* BulidNode(){
    Node* node =  (Node*)malloc(sizeof(Node));
    char s1[20] = "";
    char s2[20] = "";
    char s3[20] = "";
    char s4[20] = "";
    char s5[20] = "";
    //cout<<"s1:"<<s1<<endl;
    cout<<"�����û�����";
    getchar();//�Ե�֮ǰ�Ļس�
    cin.getline(s3,50);
    cout<<endl;
    node->name.append(s3);


    cout<<"����ڵ�����";    
    cin.getline(s1,50);
    cout<<endl;
    node->data.append(s1);


    cout<<"����IP";
    cin.getline(s2,50);
    cout<<endl;
    node->IP.append(s2);
    int i=3;
    while(i){
    cout<<"�趨����"; 
    scanf("%s",s4);
    cout<<endl;
    cout<<"ȷ������";
    scanf("%s",s5);
    if(strcmp(s4,s5)!=0){
        cout<<"�������벻һ�£��������趨"<<endl;
        i--;
        }
    else{
        node->password.append(s4);
        break;
    }
    }
    return node;
    
}

//���ӽڵ�
void AddNode(AdjacentMatrixGraph* adj){
    Node* node = BulidNode();
    adj->VertexGateher[adj->Vertex] = node;
    adj->Vertex++;
    int edge;
    cout<<"�ߵĸ���"<<endl;
    scanf("%d",&edge);
    for(int i=edge ;i > 0 ;i--){
        int q,m;
        cout<<"�������нڵ�Ĺ�ϵ"<<endl;
        scanf("%d,%d",&q,&m);
        adj->AdjacentMatrix[adj->Vertex-1][q-1] = m;
        adj->AdjacentMatrix[q-1][adj->Vertex-1] = m;
    }
    adj->User.append(node->name);
    return;
    
}

//ɾ���ڵ�ĸ�������
void DeleteChange(AdjacentMatrixGraph* adj,int m){
    for(int i=0;i<adj->Vertex;i++){
        adj->AdjacentMatrix[m-1][i] = adj->AdjacentMatrix[adj->Vertex-1][i];
    }

    for(int i=0;i<adj->Vertex;i++){
        adj->AdjacentMatrix[i][m-1] = adj->AdjacentMatrix[i][adj->Vertex-1];
    }

}

//kmp��Ѱ�Ӵ���ɾ������
void UserDelete(string* txt,string target){
    //.data string����תchar*
    char* p = (char*) (*txt).data();
    char* q = (char*) target.data();
    int tar = KMP(p,q);
    cout<<"Ŀ���ַ����±�"<<tar<<endl;
    cout<<target<<endl;
    cout<<p<<endl;
    cout<<q<<endl;
    if(tar == -1){
        cout<<"û�д��û���"<<endl;
    }
    else (*txt).erase(tar,target.length());
    /*
    int i=0;
    while(i<target.length()+2){
    }
    */
}

//ɾ���ڵ�
void DeleteNode(AdjacentMatrixGraph* adj){
    int m;//��m��Ԫ��
    cout<<"ѡ��Ҫɾ���Ľڵ�"<<endl;
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


void changepsw(Node* node){
    char s4[20] = "";
    char s5[20] = "";
    int i=3;
    while(i){
    cout<<"�趨����"; 
    scanf("%s",s4);
    cout<<endl;
    cout<<"ȷ������";
    scanf("%s",s5);
    if(strcmp(s4,s5)!=0){
        cout<<"�������벻һ�£��������趨"<<endl;
        i--;
        }
    else{
        cout<<"�����޸ĳɹ�"<<endl;
        node->password.append(s4);
        break;
    }
    }
}


void nodeshow(Node* node){
    cout<<"�û����ƣ�"<<node->name<<endl;
    cout<<"�û�IP��"<<node->IP<<endl;
    cout<<"�ڵ㴢����Ϣ��"<<node->data<<endl;
}

//�ɹ�����ĳ�ڵ����ѡ��
void OperateOption(AdjacentMatrixGraph* adj,int i){
    string name = adj->VertexGateher[i]->name;
    cout<<"��ӭ����"<<name<<endl;
    int option;
    while(1){
        printf("=======================\n");
        printf("Select your actions:\n");
        cout<<"1:�����û�"<<endl;
        cout<<"2:�ڵ���Ϣ��ѯ"<<endl;
        cout<<"3:�޸�����"<<endl;
        cout<<"0:�˳���½"<<endl;
        printf("=======================\n");
        scanf("%d",&option);
        if(option == 0){
            break;
        }
        switch(option){
            case 3:changepsw(adj->VertexGateher[i]);break;
            case 2:nodeshow(adj->VertexGateher[i]);break;
            case 1:pin(*adj,adj->VertexGateher[i]);break;

        }
    }
    cout<<"�˳��û�"<<name<<endl;
}

//����ڵ㹦�ܺ���
void enterNode(AdjacentMatrixGraph* adj,string name){
    int temp = -1;
    for(int i=0;i<adj->Vertex;i++){
        cout<<"IP���ƣ�"<<adj->VertexGateher[i]->IP<<name<<endl;
        if(strcmp(adj->VertexGateher[i]->IP.c_str(),name.c_str())==0){
            temp=i;
            int m=3;
            while(m){
            cout<<"�������û����룺";
            char psw[20] = "";
            scanf("%s",psw);
            if(strcmp(psw,adj->VertexGateher[i]->password.data())==0){
                cout<<"������ȷ"<<endl;
                break;
            }
            else{cout<<"�������"<<endl;m--;}
            }
            if(temp != -1) break;
            
            }
    }
    if(temp == -1){
        cout<<"û�д˽ڵ㣬����ʧ��"<<endl;
        return ;
    }
    else{
        OperateOption(adj,temp);
    }
}

//��ʾ������Ϣ
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

//����Ĭ�Ͻڵ�����
Node* DefaultBulidNode(int n){
    Node* node =  (Node*)malloc(sizeof(Node));
    switch (n)
    {
    case 0:
        node->name = "LiYiLin";
        node->data = "my name is LYL";
        node->IP = "10.10.255.0";
        node->password = "Shxy";
        return node;
    case 1:
        node->name = "LiHongXiao";
        node->data = "my name is LHX";
        node->IP = "10.10.255.1";
        node->password = "Shxy";
        return node;
        
    case 2:
        node->name = "YangTianMing";
        node->data = "my name is YTM";
        node->IP = "10.10.255.2";
        node->password = "Shxy";
        return node;
    case 3:
        node->name = "ZhangShuo";
        node->data = "my name is ZS";
        node->IP = "10.10.255.3";
        node->password = "Shxy";
        return node;
    }
    return NULL;
}

//��ʼ������
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
                cout<<"����Ҫ����ڵ��IP"<<endl;
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




