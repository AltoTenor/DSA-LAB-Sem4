#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define printstr(s) printf("%s\n",s)
#define dpt(x) printf("%d\n",x)


struct node{
    int val;
    struct node * p;
    struct node * l;
    struct node * r;
};

struct BT{
    struct node * root; 
};

void substr(char str[],char substr[],int low,int high){
    int i=low;
    for (;i<=high;i++){
        substr[i-low]=str[i];
    }
}

struct node * create(int x){
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    temp->val=x;
    temp->l=NULL;
    temp->r=NULL;
    temp->p=NULL;
    return temp;
}

struct node * buildtree(char str[]){
    char string_left[10000];
    char string_right[10000];
    char string_for_num[10000];
    for (int i=0;i<10000;i++) {string_right[i]='\0';string_left[i]='\0';string_for_num[i]='\0';}
    // printf("Inside Buildtree for ");
    // printf("%s\n",str);
    if (str[0]=='(' && str[2]==')') {return NULL;}
    int index_of_first_space;
    int i;
    for (i=2;i<strlen(str);i++) if (str[i]==' '){index_of_first_space=i;break;}
    
    int numstartindex;
    if (str[1]==' ')numstartindex=2;
    else numstartindex=1;

    substr(str,string_for_num,numstartindex,index_of_first_space-1);
    
    int num=atoi(string_for_num);

    int stack=1;
    int left_child_ending_bracket;
    i+=2;
    for (;i<strlen(str);i++){
        if (str[i]=='(')stack++;
        else if (str[i]==')')stack--;
        if (stack==0){
            left_child_ending_bracket=i;
            break;
        }
    }
    // dpt(left_child_ending_bracket);
    substr(str,string_left,index_of_first_space+1,left_child_ending_bracket);
    substr(str,string_right,left_child_ending_bracket+2,strlen(str)-3);

    struct node * temp=create(num);
    
    // printf("the num is %d\n",num);
    temp->l=buildtree(string_left);
    temp->r=buildtree(string_right);
    return temp;

}

void inorder(struct node * temp){
    if (temp!=NULL){
        inorder(temp->l);
        printf("%d ",temp->val);
        inorder(temp->r);
    }
}

struct node * search(struct node * temp,int k){
    if (temp!=NULL && temp->val==k){
        return temp;
    }
    else if (temp!=NULL){
        struct node * t1=search(temp->l,k);
        struct node * t2=search(temp->r,k);
        if (t1!=NULL) return t1;
        if (t2!=NULL) return t2;
    }
    else return NULL;
}

void print(struct node * temp,int c){
    if (temp==NULL){ return;}
    else if (c==0){
        printf("%d ",temp->val);
        return;
    }
    else{
        print(temp->l,c-1);
        print(temp->r,c-1);
    }
}


int main(){
    char input[100000];
    fgets(input,100000,stdin);
    struct BT * T=(struct BT*)malloc(sizeof(struct BT));
    T->root=NULL;
    input[strlen(input)-1]='\0';  
    T->root=buildtree(input);
    int k,x;
    scanf("%d",&x);
    scanf("%d",&k);
    struct node * t1=search(T->root,x);

    print(t1,k);
    return 0;
}