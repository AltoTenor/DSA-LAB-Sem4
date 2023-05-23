#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int val;
    int color;
    struct node * left;
    struct node * right;
};

struct node * create(int x){
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    temp->val=x;
    temp->color=1;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

struct node * leftrotate(struct node * x){
    struct node * y=x->right;
    struct node * T=y->left;

    y->left=x;
    x->right=T;

    return y;
}

struct node * rightrotate(struct node * x){
    struct node * y=x->left;
    struct node * T=y->right;

    y->right=x;
    x->left=T;


    return y;
}



struct node * rbtinsert(struct node * root,struct node * x){
    if (root==NULL){
        return x;
    }
    else if (x->val < root->val){
        root->left=rbtinsert(root->left,x);
        if (root->left!=NULL && root->left->color==1){
            if ((root->left->left!=NULL && root->left->left->color==1) || (root->left->right!=NULL && root->left->right->color==1)){
                if (root->right!=NULL && root->right->color==1){
                    root->color=1;
                    root->right->color=0;
                    root->left->color=0;
                    return root;
                }
                else{
                    if (root->left->right!=NULL && root->left->right->color==1 ){
                        root->left=leftrotate(root->left);
                    }
                    root=rightrotate(root);
                    if (root->right!=NULL)root->right->color=1;
                    root->color=0;
                    return root;
                }
            }
        }
        else return root;
    }
    else if (x->val > root->val){
        root->right=rbtinsert(root->right,x);
        if (root->right!=NULL && root->right->color==1){
            if ((root->right->right!=NULL && root->right->right->color==1) || (root->right->left!=NULL && root->right->left->color==1)){
                if (root->left!=NULL && root->left->color==1){
                    root->color=1;
                    root->right->color=0;
                    root->left->color=0;
                    return root;
                }
                else{
                    if (root->right->left!=NULL && root->right->left->color==1 ){
                        root->right=rightrotate(root->right);
                    }
                    root=leftrotate(root);
                    if (root->left!=NULL)root->left->color=1;
                    root->color=0;
                    return root;
                }
            }
        }
        else return root;
    }
    return root;
}

void print(struct node * root){
    if (root!=NULL){
        printf("( %d ",root->val);
        if (root->color==1)printf("R ");
        else printf("B ");
        print(root->left);
        printf(" ");
        print(root->right);
        printf(" )");
    }
    else{
        printf("( )");
    }
}

int main(){
    char input[100];
    scanf("%s",input);
    struct node * root=(struct node *)malloc(sizeof(struct node));
    root=NULL;
    while(input[0]!='t'){
        int x=atoi(input);
        // printf("%d\n",x);
        struct node * inp=create(x);
        root=rbtinsert(root,inp);
        root->color=0;
        print(root);
        printf("\n");
        scanf("%s",input);

    }
}