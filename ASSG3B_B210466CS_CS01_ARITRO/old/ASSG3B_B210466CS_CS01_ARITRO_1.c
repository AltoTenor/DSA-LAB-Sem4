#include <stdio.h>
#include<stdlib.h>
#define printi(x) printf("%d ",x);
#define INT_MAX 10000000
#define INT_MIN -10000000

struct Queue{
    struct node * arr[100];
    int head;
    int tail;
};

int isEmpty(struct Queue * Q){
    if (Q->head==Q->tail)return 1;
    else return 0;
}

void push(struct Queue * Q,struct node * key){
    Q->arr[Q->tail]=key;
    Q->tail=(Q->tail+1)%100;
}

struct node * pop(struct Queue * Q){
    struct node * temp=Q->arr[Q->head];
    Q->head=(Q->head+1)%100;
    return temp;
}

struct node{
    struct node *parent;
    int val;
    int degree;
    struct node * leftmostchild;
    struct node * rightsibling;  
};

struct node * create_node(int x){   //MALLOCING HEAP node
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    temp->val=x;
    temp->degree=0;
    temp->leftmostchild=NULL;
    temp->parent=NULL;
    temp->rightsibling=NULL;
    return temp;
}

struct binomial_heap{  //LINKED LIST
    struct node * head;
};

void print_bfs(struct binomial_heap * H){
    struct Queue * Q=(struct Queue *)malloc(sizeof(struct Queue));
    Q->head=0;
    Q->tail=0;
    struct node* root=H->head;
    while(root!=NULL){
        push(Q,root);
        root=root->rightsibling;
    }
    while(isEmpty(Q)==0){
        struct node * f=pop(Q);
        printf("%d ",f->val);
        struct node * lc=f->leftmostchild;
        while(lc!=NULL){
            push(Q,lc);
            lc=lc->rightsibling;
        }
    }

}

void print_root_list(struct binomial_heap * H){
    struct node* root=H->head;
    while(root!=NULL){
        printf("%d ",root->val);
        root=root->rightsibling;
    }
}



struct node * merge_lists(struct binomial_heap * H1,struct binomial_heap * H2){
    struct node * newroot=(struct node *)malloc(sizeof(struct node));
    newroot=NULL;

    struct node * temp=newroot;
    struct node * temp1=H1->head;
    struct node * temp2=H2->head;
    // printf("merging here %p and %p to %p",temp1,temp2,temp);
    while(temp1!=NULL || temp2!=NULL){
        // printf("here %p",temp1);
        if (temp2!=NULL && (temp1==NULL || temp2->degree <= temp1->degree)){
            if (temp==NULL){
                newroot=temp2;
                temp=newroot;
                temp2=temp2->rightsibling;
            }
            else{
                temp->rightsibling=temp2;
                temp2=temp2->rightsibling;
                temp=temp->rightsibling;
            }
        }
        else if  (temp1!=NULL && (temp2==NULL || temp2->degree > temp1->degree)){
            if (temp==NULL){
                newroot=temp1;
                temp=newroot;
                temp1=temp1->rightsibling;
            }
            else{
                temp->rightsibling=temp1;
                temp1=temp1->rightsibling;
                temp=temp->rightsibling;
            }
        }
    }
    return newroot;
}



struct binomial_heap * make_binomial_heap(){  //MALLOCING LINKED LIST
    struct binomial_heap * H=(struct binomial_heap *)malloc(sizeof(struct binomial_heap));
    H->head=NULL;
    return H;
} 


void binomial_link(struct node * y,struct node * z){
    y->parent=z;
    y->rightsibling=z->leftmostchild;
    z->leftmostchild=y;
    z->degree++;
}



struct binomial_heap * binomial_heap_union(struct binomial_heap * H1,struct binomial_heap * H2){
    struct binomial_heap* H=make_binomial_heap();
   
    H->head=merge_lists(H1,H2);
    
    // print(H->head);
    // printf("\n");
    if (H->head==NULL) return H;
    struct node * x=H->head;
    struct node * x_prev=NULL;
    struct node * x_next=x->rightsibling;
    while(x_next!=NULL){
        // CASE 1: deg(x)!=deg(next_x)        CASE 2: deg(x)=deg(next_x)=deg(sib_next_x)
        if ( (x->degree != x_next->degree) || (x_next->rightsibling!=NULL && x_next->rightsibling->degree==x->degree) ){
            x_prev=x;
            x=x_next;
        }
        else if (x->val < x_next->val){ //CASE 3 deg(x)=deg(next_x) != deg(sib_next_x)
            x->rightsibling=x_next->rightsibling;
            binomial_link(x_next,x);
        }
        else if (x_prev==NULL){ //CASE 4
            H->head=x_next;
            binomial_link(x,x_next);
            x=x_next;
        }
        else{
            x_prev->rightsibling=x_next;
            binomial_link(x,x_next);
            x=x_next;
        }
        x_next=x->rightsibling;
    }
    // printi(x->val);
    return H;
    

}

struct binomial_heap * binomial_heap_insert(struct binomial_heap * H,int k){
    struct node * x=create_node(k);
    struct binomial_heap * H1=make_binomial_heap();
    H1->head=x;
    
    H=binomial_heap_union(H,H1);
    // printi(H->head->val);
    return H;
}



struct node * binomial_heap_min(struct binomial_heap * H){
    struct node * y=NULL;
    struct node * x=H->head;
    int min=INT_MAX;
    while(x!=NULL){
        if (x->val < min){
            min=x->val;
            y=x;
        }
        x=x->rightsibling;
    }
    return y;

}

struct node * recurhelper(struct binomial_heap * H,struct node * root){
    if (root==NULL) H->head=NULL;
    else if (root->rightsibling==NULL){ 
        H->head=root;
        root->parent=NULL;
    }
    else{
        root->parent=NULL;
        // printf("%d ",root->val );
        struct node * ret=recurhelper(H,root->rightsibling);
        ret->rightsibling=root;
    }
    return root;
}

int binomial_heap_extract_min(struct binomial_heap * H){
    struct node * t=binomial_heap_min(H);
    struct node * temp=H->head;
    // printi(temp->val);
    if (temp->val==t->val) H->head=t->rightsibling;
    else{
        while(temp->rightsibling!=t){
            temp=temp->rightsibling;
        }
        temp->rightsibling=t->rightsibling;
    }
    
    struct binomial_heap * H1=make_binomial_heap();
    struct node * t_left=recurhelper(H1,t->leftmostchild);

    if (t_left!=NULL) t_left->rightsibling=NULL;
     
    H->head=binomial_heap_union(H,H1)->head;
    
    return t->val;
}

struct node * search(struct node* root,int x){
    if (root!=NULL){
        if (x==root->val)return root;
        struct node * t1=search(root->leftmostchild,x);
        struct node * t2=search(root->rightsibling,x);
        if (t1!=NULL) return t1;
        if (t2!=NULL) return t2;
    }
}


void binomial_decrease_key(struct binomial_heap * H,int key_before,int key_after){
    if (key_after >key_before )return;
    struct node * x=search(H->head,key_before);

    x->val=key_after;
    struct node * y=x;
    struct node * z=y->parent;
    while(z!=NULL && y->val < z->val){
        
        int temp=y->val;
        y->val=z->val;
        z->val=temp;
        y=z;
        z=y->parent;
    }
}


void binomial_delete(struct binomial_heap * H,int key){
    binomial_decrease_key(H,key,INT_MIN);
    binomial_heap_extract_min(H);
}

int main(){
    struct binomial_heap* H1=make_binomial_heap();
    H1->head=NULL;
    struct binomial_heap* H2=make_binomial_heap();
    H2->head=NULL;
    char po='x';
    int temp,temp1;
    while(po!='e'){
        scanf("%c",&po);
        if (po=='i'){
            scanf("%d",&temp);
            H1=binomial_heap_insert(H1,temp);
        }
        if (po=='j'){
            scanf("%d",&temp);
            H2=binomial_heap_insert(H2,temp);
        }
        if (po=='d'){
            scanf("%d",&temp);
            struct node * x=search(H1->head,temp);
            if (x==NULL)printf("-1\n");
            else{
                binomial_delete(H1,temp);
                printf("%d\n",temp);
            }
        }
        if (po=='p'){
            scanf("%d",&temp);
            if (temp==1){
                print_root_list(H1);
                // printf("--");
                // print_bfs(H1);
                // printf("\n");
            }
            if (temp==2){
                print_root_list(H2);
                // printf("--");
                // print_bfs(H2);
                // printf("\n");
            }
            printf("\n");
        }
        if (po=='m'){
            if (H1->head==NULL)printf("-1\n");
            else{
                struct node * y=binomial_heap_min(H1);
                printf("%d\n",y->val);
            }
        }
        if (po=='x'){
            if (H1->head==NULL)printf("-1\n");
            else{
                int y=binomial_heap_extract_min(H1);
                printf("%d\n",y);
            }
        }
        if (po=='r'){
            scanf("%d",&temp);
            scanf("%d",&temp1);
            struct node * x=search(H1->head,temp);
            if (x==NULL || temp<temp1)printf("-1\n");
            else{
                binomial_decrease_key(H1,temp,temp1);
                printf("%d\n",temp1);
            }
        }
        if (po=='u'){
            struct binomial_heap * H=binomial_heap_union(H1,H2);
            print_root_list(H);
            printf("\n");
            // H1->head=NULL;
            // H2->head=NULL;
        }
        // 

    }
    return 0;
}
