#include <stdio.h>
#include<stdlib.h>
#define R 10000
#define printi(x) printf("%d ",x)


struct node{
    struct node *parent;
    int val;
    int rank;  
};

struct dsu{
    struct node * arr[R];
    int count;
};

void makeset(struct dsu * D,int x){
    struct node * temp=(struct node * )malloc(sizeof(struct node));
    temp->parent=temp;
    temp->val=x;
    temp->rank=0;
    D->arr[x]=temp;
    D->count++;
}

void link_with_rank(struct node * x,struct node * y){
    if (x->rank > y->rank){
        y->parent=x;
    }
    else if (x->rank < y->rank){
        x->parent=y;
    }
    else{
        
        y->parent=x;
        x->rank++;
    }
}

struct node * find_set_with_PC(struct node * x,struct dsu * D){
    if (x->parent!=x){
        x->parent=find_set_with_PC(x->parent,D);
    }
    return x->parent;
}

void union_set_with_PC_and_rank(struct node *x,struct node *y,struct dsu * D){
    struct node * t1=find_set_with_PC(x,D);
    struct node * t2=find_set_with_PC(y,D);
    if (t1==t2) return;
    link_with_rank(t1,t2);
    D->count--;
    return;
}

int main(){
    struct dsu * D=(struct dsu *)malloc(sizeof(struct dsu));
    for (int i=0;i<R;i++)D->arr[i]=NULL;
    D->count=0;
    int temp,temp1;
    char op='x';
    while(op!='e'){
        scanf("%c",&op);
        if (op=='t'){
            scanf("%d",&temp);
            scanf("%d",&temp1);
            if (D->arr[temp]==NULL) makeset(D,temp);
            if (D->arr[temp1]==NULL) makeset(D,temp1);
            union_set_with_PC_and_rank(D->arr[temp],D->arr[temp1],D);
        }
        if (op=='T'){
            printf("%d\n",D->count);
        }
        if (op=='d'){
            int c=0;
            for (int i=0;i<R;i++){
                for (int j=i+1;j<R;j++){
                    if (D->arr[i]!=NULL && D->arr[j]!=NULL && find_set_with_PC(D->arr[i],D)!=find_set_with_PC(D->arr[j],D))c++;
                }
            }
            if (c) printf("%d\n",c);
            else printf("-1\n");
        }
        if (op=='v'){
            scanf("%d",&temp);
            scanf("%d",&temp1);
            if (temp<temp1 && D->arr[temp]!=NULL && D->arr[temp1]!=NULL && find_set_with_PC(D->arr[temp],D)!=find_set_with_PC(D->arr[temp1],D)) printf("1\n");
            else printf("-1\n");
        }
    }
}