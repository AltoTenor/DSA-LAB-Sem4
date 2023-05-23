#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#typedef xx struct node *

int max21(int a,int b){
    return (a>b)?(a):(b);
} 

struct node {
    int val;
    int height;
    struct node * l;
    struct node * r;
};

struct node * create(int key){
    struct node * temp=(struct node *)malloc(sizeof(struct node *));
    temp->val=key;
    temp->height=1;
    temp->l=NULL;
    temp->r=NULL;
    return temp;
}

int height(struct node * x){
    if (x==NULL)return 0;
    else return x->height;
}

int BF(struct node * x){
    if (x==NULL) return 0;
    else return (height(x->l)-height(x->r));
}


struct node * lrotate(struct node * x){
    struct node * y=x->r;
    struct node * T=y->l;

    y->l=x;
    x->r=T;

    x->height=1+(max21(height(x->l),height(x->r)));
    y->height=1+(max21(height(y->l),height(y->r)));

    return y;
}

struct node * rrotate(struct node * x){
    struct node * y=x->l;
    struct node * T=y->r;

    y->r=x;
    x->l=T;

    x->height=1+(max21(height(x->l),height(x->r)));
    y->height=1+(max21(height(y->l),height(y->r)));

    return y;
}



struct node * insert(struct node * x,int key){
    
    if (x==NULL) return create(key);
    else if (x->val < key) x->r=insert(x->r,key);
    else if (x->val > key) x->l=insert(x->l,key);
    // else return x;
    
    x->height=1+max21(height(x->l),height(x->r));
    int bal=BF(x);
    
    if (bal>1 && x->l->val > key){
        return rrotate(x);
    }
    
    if (bal>1 && x->l->val < key){
        x->l=lrotate(x->l);
        return rrotate(x);
    }

    if (bal<-1 && x->r->val < key){
        return lrotate(x);
    }

    if (bal<-1 && x->r->val > key){
        x->r=rrotate(x->r);
        return lrotate(x);
    }
    return x;
}

struct node * minvalue(struct node* h)
{
    struct node* current = h;
 
    /* loop down to find the leftmost leaf */
    while (current->l != NULL)
        current = current->l;
 
    return current;
}

struct node * delete(struct node * root,int key){
    if (root==NULL) return root;
    else if (root->val > key) root->l=delete(root->l,key);
    else if (root->val < key) root->r=delete(root->r,key);
    else{
        if (root->r==NULL ||root->l==NULL ){
            struct node * temp= (root->l)?(root->l):(root->r);
            if (temp==NULL)root=NULL;
            else *root=*temp;
        }
        else{
            struct node * min=minvalue(root->r);
            root->val=min->val;
            root->r=delete(root->r,min->val);
            
        }
    }
    if (root==NULL) return root;
    root->height=1+max21(height(root->l),height(root->r));
    int bal=BF(root);

    if (bal>1 && BF(root->l)>=0){
        return rrotate(root);
    }

    if (bal>1 && BF(root->l)<0){
        root->l=lrotate(root->l);
        return rrotate(root);
    }

    if (bal<-1 && BF(root->l)<=0){
        return lrotate(root);
    }

    if (bal<-1 && BF(root->l)>0){
        root->r=rrotate(root->r);
        return lrotate(root);
    }
    return root;
}

void inorder(struct node * t){
    if (t!=NULL){
        printf("%d ",t->val);
        inorder(t->l);
        inorder(t->r);
    }
}

int main()
{
    struct node *root = NULL;

    /* Constructing tree given in the above figure */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    root=delete(root,30);

    /* The constructed AVL Tree would be
                30
            / \
            20 40
            / \	 \
        10 25 50
    */

    printf("Preorder traversal of the constructed AVL"
            " tree is \n");
    inorder(root);

    return 0;
}