#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char name[1000];
    char rollno[1000];
    int age;
    struct node * next;    
};

struct Linkedlist{
    int count;
    struct node * head;
    
};

struct node * create(char name[],char rollno[],int age){
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    strcpy(temp->name,name);
    strcpy(temp->rollno,rollno);
    temp->age=age;
    temp->next=NULL;
    // printf("ok");
    return temp;
}

void listinsert(char name[],char rollno[],int age,struct Linkedlist * L){
    L->count++;
    struct node * temp=create(name,rollno,age);
    struct node * it=L->head;
    if (it==NULL){
        L->head=temp;
        return;
    }
    while(it->next!=NULL)it=it->next;
    it->next=temp;
    return;
}

void print(struct Linkedlist *L){
    struct node * it=L->head;
    while(it!=NULL){
        printf("%s ",it->name);
        it=it->next;
    }
}

int hash(char str[],int age){
    int sum=0;
    for(int i=0;i<strlen(str);i++){
        sum+=str[i];
    }
    sum+=age;
    sum%=4;
    return sum;
}

void search(char dep[],struct Linkedlist * L){
    int f=0;
    struct node *it=L->head;
    while(it!=NULL){
        
        int x=strlen(it->rollno)-1;
        // printf("%c %c",it->rollno[strlen(it->rollno)-2],it->rollno[strlen(it->rollno)-1]);
        // printf("checking with: %c %c\n",dep[0],dep[1]);
        if ((it->rollno[x-1]==dep[0]||it->rollno[x-1]==dep[0]-32) && (it->rollno[x]==dep[1] || it->rollno[x]==dep[1]-32) ){
            f=1;
            printf("%s ",it->name);
        }
        it=it->next;
    }
    if (!f) printf("-1");
}



int main(){
    int n;
    scanf("%d",&n);
    struct Linkedlist * lol [4];
    for (int i=0;i<4;i++){
        lol[i]=malloc(sizeof(struct Linkedlist*));
        lol[i]->count=0;
        lol[i]->head=NULL;
    }
    char name_t[1000];
    char rollno_t[1000];
    int agetemp;
    for (int k=0;k<n;k++){
        scanf("%s",name_t);
        scanf("%s",rollno_t);
        scanf("%d",&agetemp);
        int x=hash(name_t,agetemp);
        // printf("The hash is %d\n",x);
        listinsert(name_t,rollno_t,agetemp,lol[x]);
    }   
    char op='x';
    int temp,extra;
    char dep[3];
    char m[1];
    while(op!='e'){
        scanf("\n%c",&op);
        if (op=='c'){
            scanf("%d",&temp);
            printf("%d ",lol[temp]->count);
            print(lol[temp]);
            printf("\n");
        }
        else if (op=='1' ||op=='2' ||op=='3'){
            scanf("%s",dep);
            int m=op-'0';
            search(dep,lol[m]);
            printf("\n");
        }
    }    
    
    
}