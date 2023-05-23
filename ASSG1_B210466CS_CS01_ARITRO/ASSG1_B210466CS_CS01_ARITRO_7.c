#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define printstr(s) printf("%s\n",s)
#define dpt(x) printf("%d\n",x)


struct node{
    int val;
    struct node * l;
    struct node * r;
    struct node * p;
};

struct BST{
    struct node * root; 
};

void substr(char str[],char substr[],int low,int high){
    int i=low;
    for (;i<=high;i++){
        substr[i-low]=str[i];
    }
    // printf("Substring is %s\n",substr);
    // substr[i]='\0';
}

struct node * create(int x){
    struct node * temp=(struct node *)malloc(sizeof(struct node));
    temp->val=x;
    temp->l=NULL;
    temp->r=NULL;
    return temp;
}

struct node * buildtree(char str[],struct node * parent){
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
    temp->p=parent;
    temp->l=buildtree(string_left,temp);
    temp->r=buildtree(string_right,temp);
    return temp;

}


void inorder(struct node * temp){
    if (temp!=NULL){
        inorder(temp->l);
        printf("%d ",temp->val);
        inorder(temp->r);
    }
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



int main(){
    char input[100000];
    fgets(input,100000,stdin);
    struct BST * T=(struct BST*)malloc(sizeof(struct BST));
    T->root=NULL;

    input[strlen(input)-1]='\0';  
    T->root=buildtree(input,NULL);
    
    // inorder(T->root);

    int key;
    scanf("%d",&key);
    struct node * t1=search(T,key);
    if (t1==NULL){
        printf("-1\n");
        return 0;
    }
    else if (t1->p==NULL){
        printf("-1\n");
        return 0;
    }
    while(t1->p!=NULL){
        t1=t1->p;
        printf("%d ",t1->val);
    }
    return 0;
}