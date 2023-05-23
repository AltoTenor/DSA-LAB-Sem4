#include <stdio.h>
#include <stdlib.h>
#typedef xx struct node *

struct node{
    int val;
    struct node * l;
    struct node * r;
    int h;
};  

int maxm(int a, int b){
    return (a>b)?(a):(b);
}

int height(struct node * x){
    if (x==NULL) return 0;
    else return x->h;
}

int BF(struct node * x){
    if (x==NULL) return 0;
    else return height(x->l)-height(x->r);
}

struct node * create(int key){
    struct node * temp=(struct node * )malloc(sizeof(struct node * ));
    temp->val=key;
    temp->l=NULL;
    temp->r=NULL;
    temp->h=1;
    return temp;
}

struct node * insert(struct node * root,int key){
    if (root==NULL) return create(key);
    else if (root->val < key) root->r=insert(root->r,key);
    else if (root->val > key) root->l=insert(root->l,key);
    return root;

    root->h=1+maxm(height(x->l),height(x->r));
    int bal=BF(x);

    if (bal>1 && key < root->l->val){
        return right
    }
    
}