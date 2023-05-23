#include <stdio.h>
#include<stdlib.h>
#define R 100000
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

struct node * makeset(struct dsu * D,int x){
    struct node * temp=(struct node * )malloc(sizeof(struct node));
    temp->parent=temp;
    temp->val=x;
    temp->rank=0;
    D->arr[x]=temp;
    return temp;
}

int link_with_rank(struct node * x,struct node * y){
    if (x->rank > y->rank){
        y->parent=x;
        return x->val;
    }
    else if (x->rank < y->rank){
        x->parent=y;
        return y->val;
    }
    else{
        
        y->parent=x;
        x->rank++;
        return x->val;
    }
}

int link_WO_rank(struct node * x,struct node * y){
    y->parent=x;
    return x->val;
}

struct node * find_set_with_PC(struct node * x,struct dsu * D){
    D->count++;
    if (x->parent!=x){
        x->parent=find_set_with_PC(x->parent,D);
    }
    return x->parent;
}

struct node * find_set_WO_PC(struct node * x,struct dsu * D){
    D->count++;
    if (x->parent!=x){
        
        return find_set_WO_PC(x->parent,D);
    }
    return x->parent;
} 

int union_set_with_PC_and_rank(struct node *x,struct node *y,struct dsu * D){
    struct node * t1=find_set_with_PC(x,D);
    struct node * t2=find_set_with_PC(y,D);
    if (t1==t2) return t1->val;
    return link_with_rank(t1,t2);
}

int union_set_WO_PC_with_rank(struct node *x,struct node *y,struct dsu * D){
    struct node * t1=find_set_WO_PC(x,D);
    struct node * t2=find_set_WO_PC(y,D);
    if (t1==t2) return t1->val;
    return link_with_rank(t1,t2);
}

int union_set_WO_PC_OR_rank(struct node *x,struct node *y,struct dsu * D){
    struct node * t1=find_set_WO_PC(x,D);
    struct node * t2=find_set_WO_PC(y,D);
    if (t1==t2) return t1->val;
    return link_WO_rank(t1,t2);
}

int union_set_with_PC_WO_rank(struct node *x,struct node *y,struct dsu * D){
    struct node * t1=find_set_with_PC(x,D);
    struct node * t2=find_set_with_PC(y,D);
    if (t1==t2) return t1->val;
    return link_WO_rank(t1,t2);
}

void print(struct dsu * D){
    for (int i=0;i<R;i++){
        if (D->arr[i]!=NULL){
            if (D->arr[i]->parent!=NULL)printf("%d with parent -> %d and rank->%d\n",D->arr[i]->val,D->arr[i]->parent->val,D->arr[i]->rank);
        }
    }
}

int main(){
    struct dsu * D1=(struct dsu *)malloc(sizeof(struct dsu));
    for (int i=0;i<R;i++)D1->arr[i]=NULL;
    D1->count=0;
    struct dsu * D2=(struct dsu *)malloc(sizeof(struct dsu));
    for (int i=0;i<R;i++)D2->arr[i]=NULL;
    D2->count=0;
    struct dsu * D3=(struct dsu *)malloc(sizeof(struct dsu));
    for (int i=0;i<R;i++)D3->arr[i]=NULL;
    D3->count=0;
    struct dsu * D4=(struct dsu *)malloc(sizeof(struct dsu));
    for (int i=0;i<R;i++)D4->arr[i]=NULL;
    D4->count=0;

    int temp,temp1;
    char op='x';
    while(op!='s'){
        scanf("%c",&op);
        if (op=='m'){
            scanf("%d",&temp);
            if (D1->arr[temp]!=NULL){
                printf("-1\n");
                continue;
            }
            printf("%d\n",temp);   
            makeset(D1,temp);
            makeset(D2,temp);
            makeset(D3,temp);
            makeset(D4,temp);
        }
        if (op=='u'){
            scanf("%d",&temp);
            scanf("%d",&temp1);
            if (D1->arr[temp]==NULL ||D1->arr[temp1]==NULL ){
                printf("-1\n");
                continue;   
            }
            printf("%d ",union_set_WO_PC_OR_rank(D1->arr[temp],D1->arr[temp1],D1));
            printf("%d ",union_set_WO_PC_with_rank(D2->arr[temp],D2->arr[temp1],D2));
            printf("%d ",union_set_with_PC_WO_rank(D3->arr[temp],D3->arr[temp1],D3));
            printf("%d ",union_set_with_PC_and_rank(D4->arr[temp],D4->arr[temp1],D4));
            printf("\n");
        }
        if (op=='f'){
            scanf("%d",&temp);
            if (D1->arr[temp]==NULL){
            	printf("-1 -1 -1 -1\n");
            	D1->count++;
            	D2->count++;
            	D3->count++;
            	D4->count++;
            	}
            else{
                int f1=find_set_WO_PC(D1->arr[temp],D1)->val;
                int f2=find_set_WO_PC(D2->arr[temp],D2)->val;
                int f3=find_set_with_PC(D3->arr[temp],D3)->val;
                int f4=find_set_with_PC(D4->arr[temp],D4)->val;
                printf("%d %d %d %d\n",f1,f2,f3,f4);
            }
            
        }
        // 
    }
    printf("%d %d %d %d\n",D1->count,D2->count,D3->count,D4->count);
    // print(D2);


    
}



