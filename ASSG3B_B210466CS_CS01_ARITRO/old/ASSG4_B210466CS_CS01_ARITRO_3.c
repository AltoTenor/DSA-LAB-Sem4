#include <stdio.h>
#include <stdlib.h>
#include <string.h>





struct node {
    int val;
    struct node * next; 
    int vis;
};


struct Queue{
    int * arr;
    int head;
    int tail;
};

int isEmpty(struct Queue * Q){
    if (Q->head==Q->tail)return 1;
    else return 0;
}

void push(struct Queue * Q,int key){
    Q->arr[Q->tail]=key;
    Q->tail=(Q->tail+1)%100;
}

int pop(struct Queue * Q){
    int temp=Q->arr[Q->head];
    Q->head=(Q->head+1)%100;
    return temp;
}



struct Adjlist{
    int n;
    struct node ** arr;
};

struct node * create(int x){
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    temp->next=NULL;
    temp->val=x;
    return temp;
}

void insert(struct Adjlist * L,int x,int y){
    struct node * temp=L->arr[x];
    struct node * ins=create(y);
    if (temp==NULL) {
        L->arr[x]=ins;
        return;
    }
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=ins;
    return;
}

void print(struct Adjlist * L){
    for (int i=0;i<(L->n);i++){
        struct node * temp=L->arr[i];
        printf("%d : ",i);
        while(temp!=NULL){
            printf("%d ",temp->val);
            temp=temp->next;
        }
        printf("\n");
    }
}

void dfsrec(struct Adjlist * L,int x,int * vis){
    vis[x]=1;
    printf("%d ",x);
    struct node * temp=L->arr[x];
    while(temp!=NULL){
        if (vis[temp->val]==0){
            dfsrec(L,temp->val,vis);
        }
        temp=temp->next;
    }
    
}


void dfs(struct Adjlist * L){
    int * vis=(int *)malloc((L->n)*sizeof(int));
    for (int i=0;i<L->n;i++) vis[i]=0;

    // for (int i=0;i<L->n;i++){
    //     if (vis[i]==0){
    //         dfsrec(L,i,vis);
    //     }
    // }
    dfsrec(L,0,vis);
}



int main(){
    int n;
    scanf("%d\n",&n);
    struct Adjlist * L=(struct Adjlist *)malloc(sizeof(struct Adjlist));
    L->n=n;
    L->arr=(struct node **)malloc(L->n*sizeof(struct node *));
    for (int i=0;i<L->n;i++){ 
        L->arr[i]=NULL;
    }

    char input[1000];
    for (int i=0;i<n;i++){
        fgets(input,1000,stdin);
        int temp=0;
        for (int k=0;k<strlen(input);k++){
            if (input[k]==' ' || input[k]=='\n'){
                // printf("%d-",temp);
                insert(L,i,temp);
                temp=0;
            }
            else{
                temp*=10;
                temp+=(input[k]-'0');
            }
        }
    }
    // print(L);
    dfs(L);
}

