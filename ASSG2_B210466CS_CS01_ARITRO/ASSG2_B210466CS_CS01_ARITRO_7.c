#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define printstr(s) printf("%s\n",s)
#define dpt(x) printf("%d\n",x)


struct node{
    int val;
    int height;
    int balance;
    struct node * p;
    struct node * l;
    struct node * r;

};

struct BST{
    struct node * root; 
    int count;
};

struct node * create(int x){
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    temp->val=x;
    temp->height=0;
    temp->balance=0;
    temp->l=NULL;
    temp->r=NULL;
    temp->p=NULL;
    return temp;
}




void inordercount(struct node * temp,struct BST *T,int x){
    if (temp!=NULL){
        inordercount(temp->l,T,x);
        if (temp->val>x)T->count++;
        inordercount(temp->r,T,x);
    }
}

void inorderprint(struct node * temp,struct BST *T,int x){
    if (temp!=NULL){
        inorderprint(temp->l,T,x);
        if (temp->val>x)printf("%d ",temp->val);
        inorderprint(temp->r,T,x);
    }
}

void preorder(struct node * temp){
    if (temp!=NULL){
        printf("( %d ",temp->val);
        preorder(temp->l);
        preorder(temp->r);
        printf(") ");
    }
    else printf("( ) ");
}

int heightcalc(struct node * temp){
	int h1=0,h2=0;
	if (temp->l==NULL && temp->r==NULL){
		temp->height=0;
		return 0;
	}
	else if (temp->l==NULL){
		temp->height=1+heightcalc(temp->r);
	}
	else if (temp->r==NULL){
		temp->height=1+heightcalc(temp->l);
	}
	else{
		h1=heightcalc(temp->l);
		h2=heightcalc(temp->r);
		if (h1>=h2) temp->height=h1+1;
		else temp->height=h2+1;
	}
	return temp->height;

	
}


struct node * lrotate(struct node * x){
	struct node *y=x->r;
	struct node *t2=y->l;
	y->l=x;
	x->r=t2;
	x->height=heightcalc(x);
	y->height=heightcalc(y);
	return y;
}

struct node * rrotate(struct node * x){
	struct node *y=x->l;
	struct node *t2=y->r;
	y->r=x;
	x->l=t2;
	x->height=heightcalc(x);
	y->height=heightcalc(y);
	return y;

}

int balancefactor(struct node * temp){
	int x,y;
	if (temp->l!=NULL) x=(temp->l->height);
	else x=-1;
	if (temp->r!=NULL) y=(temp->r->height);
	else y=-1;
	temp->balance=x-y;
	return temp->balance;
}





struct node * insert(struct node * root,int v){
	if (root==NULL) return create(v);
	if (v< root->val) root->l=insert(root->l,v);
	else if (v> root->val) root->r=insert(root->r,v);
	else return root;
	heightcalc(root);
	balancefactor(root);
	int balance=root->balance;
	if (v==6){
		//printf("%d %d\n",root->balance,root->val);
	}
	if (balance>1 && v < root->l->val){
		return rrotate(root);
	}
	if (balance<-1 && v > root->r->val){
		// printf("%d\n",root->val);
		return lrotate(root);
	}
	if (balance>1 && v > root->l->val){
		root->l=lrotate(root->l);
		return rrotate(root);
	}
	if (balance<-1 && v < root->r->val){
		root->r=rrotate(root->r);
		return lrotate(root);
	}
	return root;
}

struct node * search(struct BST * T,int x){
    struct node * temp=T->root;
    while(temp!=NULL && temp->val!=x){
        if (temp->val > x) temp=temp->l;
        else temp=temp->r;
    }
    return temp;
}



int main(){
	struct BST * T=(struct BST*)malloc(sizeof(struct BST));
	T->root=NULL;
    char op='x';
    int t;
    while(op!='e'){
        scanf("%c",&op);
        if (op=='p') {preorder(T->root);printf("\n");}
        else if(op=='i'){
            scanf("%d",&t);
            T->root=insert(T->root,t);
        }
        else if (op=='c'){
            scanf("%d",&t);
            T->count=0;
            inordercount(T->root,T,t);
            printf("%d\n",T->count);
            inorderprint(T->root,T,t);
            printf("\n");
        }
    }
}




