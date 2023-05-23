#include <stdio.h>
#include <stdlib.h>


struct node {
    int val;
   struct node * next; 
};

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
        while(temp!=NULL){
            printf("%d ",temp->val);
            temp=temp->next;
        }
        printf("\n");
    }
}

int main(){
    int n;
    scanf("%d",&n);
    struct Adjlist * L=(struct Adjlist *)malloc(sizeof(struct Adjlist));
    L->n=n;
    L->arr=(struct node **)malloc(L->n*sizeof(struct node *));
    for (int i=0;i<L->n;i++) L->arr[i]=NULL;


    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        mat[i] = (int*)malloc(n * sizeof(int));
    
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            scanf("%d",&mat[i][j]);
        }
    }

    for (int i=0;i<n;i++){
        insert(L,i,i);
        for(int j=0;j<n;j++){
            if (mat[i][j]!=0){
                insert(L,i,j);
            }
        }
    }
    print(L);
}

