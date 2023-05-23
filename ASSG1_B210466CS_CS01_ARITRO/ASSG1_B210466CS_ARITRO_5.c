#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define printstr(s) printf("%s\n",s)
#define dpt(x) printf("%d\n",x)


struct node{
    int val;
    int sum;
    char path[100];
    struct node * l;
    struct node * r;
};

struct BST{
    struct node * root; 
    int max;
    char answer[100];
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

void sumcalc(struct node * temp,int sum){
    temp->sum=temp->val+sum;
    if (temp->l!=NULL) sumcalc(temp->l,temp->sum);
    if (temp->r!=NULL) sumcalc(temp->r,temp->sum);

}

void append(char str[],char a){
    int n=strlen(str);
    str[n]=a;
    str[n+1]='\0';
}

void pathcalc(struct node * temp,char x[],int child){
    append(x,child);
    strcpy(temp->path,x);
    char temp1[1000];
    strcpy(temp1,x);
    if (temp->l!=NULL) pathcalc(temp->l,temp1,'L');

    if (temp->r!=NULL) pathcalc(temp->r,x,'R');

}

void inorder(struct node * temp){
    if (temp!=NULL){
        inorder(temp->l);
        printf("%s ",temp->path);
        printf("%d\n",temp->val);
        inorder(temp->r);
    }
}

void answercalc(struct BST * T,struct node * temp){
    if (temp!=NULL){
        answercalc(T,temp->l);
        if (temp->l==NULL && temp->r==NULL){
            
            if ((temp->sum > T->max)||(temp->sum==T->max && strlen(temp->path)<strlen(T->answer))){
                
                strcpy(T->answer,temp->path);
                T->max=temp->sum;
                // printf("After %d %d %s\n",temp->val,T->max,T->answer);
                
                
            }
        }
        answercalc(T,temp->r);
    }
}

void remove1(char x[]){
    for (int i=1;i<=strlen(x);i++){
        x[i-1]=x[i];
    }
}


int main(){
    char input[100000];
    fgets(input,100000,stdin);
    struct BST * T=(struct BST*)malloc(sizeof(struct BST));
    T->root=NULL;
    T->max=-1;
    input[strlen(input)-1]='\0';  
    T->root=buildtree(input);
    sumcalc(T->root,0);
    
    char path[1000];
    path[0]='\0';

    pathcalc(T->root,path,'x');
    // inorder(T->root);
    answercalc(T,T->root);
    remove1(T->answer);
    if (T->answer[0]=='\0')printf("%d",T->max);
    else printf("%s %d",T->answer,T->max);
    return 0;
}