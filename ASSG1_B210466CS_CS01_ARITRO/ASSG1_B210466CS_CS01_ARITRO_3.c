#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define printstr(s) printf("%s\n",s)
#define dpt(x) printf("%d\n",x)


struct node{
    int val;
    int sum;
    struct node * p;
    struct node * l;
    struct node * r;

};

struct BST{
    struct node * root; 
    int count;
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
    temp->sum=0;
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

int sumcalc(struct node * temp){
    if (temp==NULL){
        return 0;
    }
    else if (temp!=NULL){
        temp->sum=temp->val+sumcalc(temp->l)+sumcalc(temp->r);
        return temp->sum;
    }
}

void inorder(struct node * temp,struct BST * T,int x){
    if (temp!=NULL){
        inorder(temp->l,T,x);
        // printf("%d %d\n",temp->val,temp->sum);
        if (temp->sum==x) T->count++;
        inorder(temp->r,T,x);
    }
}





int main(){
    char input[100000];
    fgets(input,100000,stdin);
    struct BST * T=(struct BST*)malloc(sizeof(struct BST));
    T->root=NULL;
    T->count=0;
    input[strlen(input)-1]='\0';  
    T->root=buildtree(input);
    int x;
    scanf("%d",&x);
    sumcalc(T->root);
    inorder(T->root,T,x);
    printf("%d",T->count);
    return 0;
}
//( 1 ( 3 ( 5 ( ) ( ) ) ( 9 ( ) ( ) ) ) ( 6 ( 11 ( ) ( ) ) ( ) ) )
