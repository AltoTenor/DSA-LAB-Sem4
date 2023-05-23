#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    struct node * next;
};

struct LinkedList{
    struct node * head;
};

struct node * create(int key){
    struct node * temp=(struct node * )malloc(sizeof(struct node * ));
    temp->val=key;
    temp->next=NULL;
    return temp;
}

void insert(struct LinkedList * L,int val){
    struct node * ins=create(val);
    struct node * temp=L->head;
    
    if (temp==NULL){
        L->head=ins;
        return;
    }
    else if (val < temp->val){
        ins->next=temp;
        L->head=ins;
        return;
    }
    while ((temp->next!=NULL) && val > temp->val){
        temp=temp->next;
    }
    ins->next=temp->next;
    temp->next=ins;
    
    return;
}

int deleteandsum(struct LinkedList * L){
    int s=L->head->val+L->head->next->val;
    L->head=L->head->next->next;
    return s;
}

void print(struct LinkedList * L){
    struct node * tem=L->head;
    while(tem!=NULL){
        printf("%d ",tem->val);
        tem=tem->next;
    }
    printf("\n");
}

int main(){
    int n,temp;
    struct LinkedList * L = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    L->head=NULL;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&temp);
        insert(L,temp);
        
    }
    int s=0;
    while(L->head->next!=NULL){
        temp=deleteandsum(L);
        insert(L,temp);
        // print(L);
        s+=temp;
    }
    
    printf("%d",s);
}
