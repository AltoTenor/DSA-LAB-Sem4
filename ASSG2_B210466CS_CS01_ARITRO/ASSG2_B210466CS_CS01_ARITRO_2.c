#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char firstname[1000];
    char lastname[1000];
    char name[1000];
    float CGPA;
    struct node * p;
    struct node * l;
    struct node * r;
};

struct BST{
    struct node * root; 
};

struct node * create(float x,char fn[],char ln[]){
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    strcpy(temp->firstname,fn);
    strcpy(temp->lastname,ln);
    strcpy(temp->name,fn);
    strcat(temp->name,ln);
    // printf(":%s:\n",temp->name);
    temp->CGPA=x;
    temp->l=NULL;
    temp->r=NULL;
    temp->p=NULL;
    return temp;
}

struct node * search(char fn[],char ln[],struct BST *T){
    struct node * temp=T->root;
    char name[1000];
    strcpy(name,fn);
    strcat(name,ln);
    
    while(temp!=NULL &&  strcmp(name,temp->name)!=0){
        // printf("Name: %s Tempname: %s\n",name,temp->name);
        if (strcmp(name,temp->name)>0) temp=temp->r;
        else temp=temp->l;
    }
    return temp;
}

void locate(char fn[],char ln[],struct BST *T,int h1){
    struct node * temp=T->root;
    char name[1000];
    strcpy(name,fn);
    strcat(name,ln);
    char ans[1000];
    
    for (int i=0;i<1000;i++) ans[i]='\0';
    while(temp!=NULL &&  strcmp(name,temp->name)!=0){
        // printf("Name: %s Tempname: %s\n",name,temp->name);
        if (strcmp(name,temp->name)>0){ 
            temp=temp->r;
            strcat(ans,"R");
        }
        else{ 
            temp=temp->l;
            strcat(ans,"L");
        }
    }
    if (temp==NULL)printf("-1\n"); 
    else printf("%d-%s\n",h1,ans);
}

int update(char fn[],char ln[],float cgpa,struct BST *T){
    struct node * temp=T->root;
    char name[1000];
    strcpy(name,fn);
    strcat(name,ln);
    int c=0;
    while(temp!=NULL &&  strcmp(name,temp->name)!=0){
        // printf("Name: %s Tempname: %s\n",name,temp->name);
        c++;
        if (strcmp(name,temp->name)>0) temp=temp->r;
        else temp=temp->l;
    }
    if (temp==NULL) return -1;
    temp->CGPA=cgpa;
    return c;
}

int searchforind(char fn[],char ln[],struct BST *T){
    struct node * temp=T->root;
    char name[1000];
    strcpy(name,fn);
    strcat(name,ln);
    int c=0;
    while(temp!=NULL &&  strcmp(name,temp->name)!=0){
        c++;
        if (strcmp(name,temp->name)>0) temp=temp->r;
        else temp=temp->l;
    }
    if (temp==NULL) return -1;
    return c;
}

void insert(float cgpa,char fn[],char ln[],struct BST * T){
    struct node * z=create(cgpa,fn,ln);
    int c=0;
    struct node * x=T->root;
    struct node *y=NULL;
    while(x!=NULL){
        c++;
        y=x;
        if (strcmp(x->name,z->name)<0){
            x=x->r;
        }
        else x=x->l;
    }
    z->p=y;
    if (y==NULL) {T->root=z;c=0;}
    else if (strcmp(y->name,z->name)<0){
        y->r=z;
    }
    else y->l=z;
    printf("%d\n",c);
}

void inorder(struct node * temp){
    if (temp!=NULL){
        inorder(temp->l);
        printf("%s %0.2f\n",temp->name,temp->CGPA);
        inorder(temp->r);
    }
}

struct node * min1(struct node * root){
    struct node * temp=root;
    while(temp->l!=NULL){
        temp=temp->l;
    }
    return temp;
}

void transplant (struct BST * T,struct node * u,struct node * v){
    if (u->p==NULL)T->root=v;
    else if(u==u->p->l)u->p->l=v;
    else u->p->r=v;
    if (v!=NULL) v->p=u->p;
}

void delete(struct BST * T,struct node * temp){
    if (temp==NULL) return;
    else if (temp->r==NULL) transplant(T,temp,temp->l);
    else if (temp->l==NULL) transplant(T,temp,temp->r);
    else{
        struct node * y=min1(temp->r);
        if (y->p==temp){
            transplant(T,y,y->r);
            y->r=temp->r;
            y->r->p=y;
        }
        transplant(T,temp,y);
        y->l=temp->l;
        y->l->p=y;        
    }
}




int hash(char fn[]){
    return (fn[0]-65);
}

int main(){
    struct BST * T[26];
    for (int i=0;i<26;i++){ 
        T[i]=(struct BST *)malloc(sizeof(struct BST));
        T[i]->root=NULL;
    }
    char op='x';
    char fn[1000];
    char ln[1000];
    char gender[2];
    char dob[12];
    char dep[5];
    float cgpa;
    while(op!='e'){
        for (int i=0;i<1000;i++){fn[i]='\0';ln[i]='\0';}
        scanf("%c",&op);
        if (op=='i'){  
            scanf("%s",fn);
            scanf("%s",ln);
            scanf("%s",gender);
            scanf("%s",dob);
            scanf("%s",dep);
            scanf("%f",&cgpa);
            // printf("fn %s ",fn);
            // printf("ln :%s: ",ln);
            // printf("gender %s ",gender);
            // printf("dob %s ",dob);
            // printf("dep %s " ,dep);
            // printf("cgpa %0.2f \n",cgpa);
            int h1=hash(fn);
            insert(cgpa,fn,ln,T[h1]);

        }
        else if (op=='p'){
            inorder(T[17]->root);
        }
        else if (op=='u'){
            scanf("%s",fn);
            scanf("%s",ln);
            scanf("%f",&cgpa);
            int h1=hash(fn);
            int x=update(fn,ln,cgpa,T[h1]);
            printf("%d\n",x);
            // inorder(T[0]->root);
        }
        else if (op=='l'){
            scanf("%s",fn);
            scanf("%s",ln);
            int h1=hash(fn);
            // printf("%d-",h1);
            locate(fn,ln,T[h1],h1);
            // inorder(T[0]->root);
        }
        else if (op=='d'){
            scanf("%s",fn);
            scanf("%s",ln);
            int h1=hash(fn);
            struct node* temp=search(fn,ln,T[h1]);
            int x=searchforind(fn,ln,T[h1]);
            if (temp==NULL) printf("-1\n");
            else{
                delete(T[h1],temp);
                printf("%d\n",x);
            }
        }
    }
}