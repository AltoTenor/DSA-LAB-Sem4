#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int val;
    struct node * l;
    struct node * r;
    struct node * p;

};

struct BST{
    struct node * root; 
};

struct node * create(int x){
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    temp->val=x;
    temp->l=NULL;
    temp->r=NULL;
    return temp;
}

void insert(struct BST * T,int val){
    struct node * z=create(val);
    struct node * x=T->root;
    struct node * y=NULL;
    while(x!=NULL){
        y=x;
        if (z->val>x->val) x=x->r;
        else x=x->l;
    }
    z->p=y;
    if (y==NULL) T->root=z;
    else if (y->val < z->val) y->r=z;
    else y->l=z;
}

struct node* search(struct BST * T,int x){
    struct node * temp=T->root;
    while (temp!=NULL && temp->val!=x)
    {
        if (x<temp->val) temp=temp->l;
        else temp=temp->r;
    }
    return temp;
    
}


struct node * minimum(struct node * temp){
    while(temp->l!=NULL){
        temp=temp->l;
    }
    return temp;
}

struct node * maximum(struct node * temp){
    while(temp->r!=NULL){
        temp=temp->r;
    }
    return temp;
}

struct node * predecessor(struct node * temp){
    if (temp->l!=NULL){
        return maximum(temp->l);
    }
    struct node * y=temp->p;
    while(y!=NULL && temp==y->l){
        temp=y;
        y=y->p;
    }
    return y;
}

struct node * successor(struct node * temp){
    if (temp->r!=NULL){
        return minimum(temp->r);
    }
    struct node * y=temp->p;
    while(y!=NULL && temp==y->r){
        temp=y;
        y=y->p;
    }
    return y;
}


void transplant(struct BST * T,struct node * u,struct node * v){
    if (u->p==NULL){
        T->root=v;
    }
    else if (u->p->l==u){
        u->p->l=v;
    }
    else if (u->p->r==u){
        u->p->r=v;
    }
    if (v!=NULL){
        v->p=u->p;
    }
}

void delete(struct BST * T,struct node * z){
    if (z->l==NULL){
        transplant(T,z,z->r);
    }
    else if (z->r==NULL){
        transplant(T,z,z->l);
    }
    else{
        struct node * y=minimum(z->r);
        if (y->p!=z){
            transplant(T,y,y->r);
            y->r=z->r;
            y->r->p=y;
        }
        transplant(T,z,y);
        y->l=z->l;
        y->l->p=y;
    }
}

void inorder(struct node * temp){
    if (temp!=NULL){
        inorder(temp->l);
        printf("%d ",temp->val);
        inorder(temp->r);
    }
}

void preorder(struct node * temp){
    if (temp!=NULL){
        printf("%d ",temp->val);
        preorder(temp->l);
        preorder(temp->r);
    }
}

void postorder(struct node * temp){
    if (temp!=NULL){
        postorder(temp->l);
        postorder(temp->r);
        printf("%d ",temp->val);
    }
}


int level(struct BST * T,int x){
    struct node * temp=T->root;
    int c=1;
    while (temp!=NULL && temp->val!=x)
    {
        if (x<temp->val) temp=temp->l;
        else temp=temp->r;
        c++;
    }
    if (temp==NULL) c=-1;
    return c;
}


int main(){
    struct BST * T=(struct BST *)malloc(sizeof(struct BST));
    T->root=NULL;
    int temp;
    char op='x';
    while(op!='e'){
        scanf("%c",&op);
        if (op=='a'){
            scanf("%d",&temp);
            insert(T,temp);
        }
        else if (op=='d'){
            scanf("%d",&temp);
            struct node * check=search(T,temp);
            if (check==NULL){printf("-1\n");continue;}
            else{
                delete(T,check);
            }
            
        }
        else if (op=='s'){
            scanf("%d",&temp);
            if (search(T,temp)!=NULL) printf("1\n");
            else printf("-1\n");
        }
        else if (op=='l'){
            scanf("%d",&temp);
            printf("%d\n",level(T,temp));
        }
        else if (op=='m'){
            printf("%d\n",minimum(T->root)->val);
        }
        else if (op=='x'){
            printf("%d\n",maximum(T->root)->val);
        }
        else if (op=='r'){
            scanf("%d",&temp);
            struct node * check=search(T,temp);
            if (check==NULL){printf("-1\n");continue;}
            else{
                printf("%d\n",predecessor(check)->val);
            }
        }
        else if (op=='u'){
            scanf("%d",&temp);
            struct node * check=search(T,temp);
            if (check==NULL){printf("-1\n");continue;}
            else{
                printf("%d\n",successor(check)->val);
            }
        }
        else if (op=='i'){
            inorder(T->root);
            printf("\n");
        }
        else if (op=='p'){
            preorder(T->root);
            printf("\n");
        }
        else if (op=='t'){
            postorder(T->root);
            printf("\n");
        }

        
    }

}

// a 25
// a 13
// a 50
// a 45
// a 55
// a 18
// l 50
// l 19
// m
// x
// r 25
// u 30
// u 25
// i
// p
// t
// s 10
// s 25
// d 55
// d 13
// d 10
// d 25
// i
// s 25
// e