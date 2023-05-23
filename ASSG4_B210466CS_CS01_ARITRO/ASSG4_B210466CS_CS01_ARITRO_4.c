#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define printi(a) printf("%d\n",a)
#define R 100000

struct triplet{
    int w;
    int u;
    int v;
};


struct node{
    struct node *parent;
    int val;
    int rank;  
};

struct dsu{
    struct node * arr[R];
    int count;
};

struct node * makeset(struct dsu * D,int x){
    struct node * temp=(struct node * )malloc(sizeof(struct node));
    temp->parent=temp;
    temp->val=x;
    temp->rank=0;
    D->arr[x]=temp;
    return temp;
}

int link_with_rank(struct node * x,struct node * y){
    if (x->rank > y->rank){
        y->parent=x;
        return x->val;
    }
    else if (x->rank < y->rank){
        x->parent=y;
        return y->val;
    }
    else{
        
        y->parent=x;
        x->rank++;
        return x->val;
    }
}


struct node * find_set_with_PC(struct node * x){
    if (x->parent!=x){
        x->parent=find_set_with_PC(x->parent);
    }
    return x->parent;
}

int union_set_with_PC_and_rank(struct node *x,struct node *y){
    struct node * t1=find_set_with_PC(x);
    struct node * t2=find_set_with_PC(y);
    if (t1==t2) return t1->val;
    return link_with_rank(t1,t2);
}

void printadj(int ** adjmat,int n){
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (adjmat[i][j]!=-20000)printf(" %d",adjmat[i][j]);
            else printf("  x");
        }
        printf("\n");
    }
}



void printrips(struct triplet ** T,int ec){
    for (int i=0;i<ec;i++){
        printf("( %d %d w: %d ) , ",T[i]->u,T[i]->v,T[i]->w);
    }
    printf("\n");
}


void kruskals(){
    int n;
    scanf("%d\n",&n);
    int **adj=(int **)malloc(sizeof(int *)*n);
    for (int i=0;i<n;i++){
        adj[i]=(int *)malloc(n*sizeof(int));
        for(int j=0;j<n;j++)adj[i][j]=-20000;
    }

    // printadj(adj,n);

    for (int i=0;i<n;i++){  //Taking adjlist input into adjmatrix
        char input[1000];
        fgets(input,1000,stdin);
        int j=0;
        int temp=0;
        while(input[j]!='\0' && input[j]!='\n'){
            
            if (input[j]==' '){
                // printi(temp);
                if (temp!=i){
                    adj[i][temp]-=1;
                }
                temp=0;
            }
            else{
                temp*=10;
                temp+=(input[j]-'0');
            }
            j++;
        }
        // printi(temp);
        if (temp!=i){
            adj[i][temp]-=1;
        }

    }


    // printadj(adj,n);
    int edgecount=0;

    for (int i=0;i<n;i++){  //Adding Weights
        char input[1000];
        fgets(input,1000,stdin);
        int j=0;
        int temp=0;
        int c=0;
        int mc=0;
        while(input[j]!='\0' && input[j]!='\n'){
            if (input[j]=='-'){
                mc=1;
            }
            else if (input[j]==' '){
                if (c>0){
                    int k=0;
                    while(adj[i][k]!=-20001) k++;
                    if (mc) adj[i][k]=-temp;
                    else adj[i][k]=temp;
                    if (i<k)edgecount++;
                }
                temp=0;
                c++;
                mc=0;
            }
            else{
                temp*=10;
                temp+=(input[j]-'0');
            }
            j++;
        }
        if (c>0){
            int k=0;
            while(adj[i][k]!=-20001) k++;
            // printi(k);
            if (mc) adj[i][k]=-temp;
            else adj[i][k]=temp;
            if (i<k)edgecount++;
        }
        temp=0;
    }

    // printadj(adj,n);
    // printi(edgecount);
    struct triplet ** T=(struct triplet **)malloc(sizeof(struct triplet *)*(edgecount));
    for (int i=0;i<edgecount;i++) T[i]=(struct triplet*)malloc(sizeof(struct triplet));


    int ind=0;
    for (int i=0;i<n;i++){
        for (int j=i+1;j<n;j++){
            if (adj[i][j]!=-20000){
                // printi(ind);
                T[ind]->u=i;
                T[ind]->v=j;
                T[ind]->w=adj[i][j];
                ind++;
            }
        }
    }

    // printrips(T,edgecount);
    //INPUTING DONE


    for (int i=0;i<edgecount;i++){  //Making triplets
        for (int j=0;j<edgecount-i-1;j++){
            if (T[j]->w > T[j+1]->w){
                struct triplet * temp=(struct triplet *)malloc(sizeof(struct triplet));
                (*temp)=(*T[j]);
                *T[j]=*T[j+1];
                *T[j+1]=*temp;
            }
        }
    }

    // printrips(T,edgecount);

    struct dsu * D=(struct dsu *)malloc(sizeof(struct dsu));
    for (int i=0;i<R;i++)D->arr[i]=NULL;
    for (int i=0;i<n;i++){
        makeset(D,i);
    }
    int ans=0;
    for (int i=0;i<edgecount;i++){
        if (find_set_with_PC(D->arr[T[i]->u])!=find_set_with_PC(D->arr[T[i]->v])){
            ans+=T[i]->w;
            union_set_with_PC_and_rank(D->arr[T[i]->u],D->arr[T[i]->v]);
        }
    }
    printi(ans);
    
}



struct note{
    int num;
    int key;
    struct note* p;
};



struct heap{
    struct note **arr;
    int heap_size;
};

void min_heapify(struct heap * H,int i){
    int l=2*i+1;
    int r=2*i+2;
    int smallest;
    if (l< H->heap_size && H->arr[i]->key > H->arr[l]->key) smallest=l;
    else smallest=i;
    if (r< H->heap_size && H->arr[smallest]->key > H->arr[r]->key) smallest=r;
    if (smallest!=i){
        struct note * temp=(struct note *)malloc(sizeof(struct note));
        *temp=*(H->arr[smallest]);
        *(H->arr[smallest])=*(H->arr[i]);
        *(H->arr[i])=*temp;
        min_heapify(H,smallest);
    }
}

void build(struct heap * H){
    
    for (int i=H->heap_size/2;i>=0;i--){
        min_heapify(H,i);
    }
}


struct note* extractmin(struct heap * H){
    if (H->heap_size<1) return NULL;
    else {
        struct note*  mn=(struct note *)malloc(sizeof(struct note));
        *(mn)=*(H->arr[0]);
        *(H->arr[0])=*(H->arr[H->heap_size-1]);
        H->arr[H->heap_size-1]->key+=5;
        H->heap_size--;
        min_heapify(H,0);
        return mn;
    }
}

void heap_decrease_key(struct heap * H,int i,int key){
    if (key>H->arr[i]->key)return;
    H->arr[i]->key=key;
    while(i>0 && H->arr[(i-1)/2]->key > H->arr[i]->key){
        struct note* temp=(struct note *)malloc(sizeof(struct note));
        *temp=*(H->arr[(i-1)/2]);
        *(H->arr[(i-1)/2])=*(H->arr[i]);
        *(H->arr[i])=*temp;
        i=(i-1)/2;
    }
}



struct note * linearsearch(struct heap * H,int x){
    for (int i=0;i<H->heap_size;i++) if (H->arr[i]->num==x) return H->arr[i];
    return NULL;
}

int linearsearchind(struct heap * H,int x){
    for (int i=0;i<H->heap_size;i++) if (H->arr[i]->num==x) return i;
    return -1;
}


void prims(){
    int n;
    scanf("%d\n",&n);
    int **adj=(int **)malloc(sizeof(int *)*n);
    for (int i=0;i<n;i++){
        adj[i]=(int *)malloc(n*sizeof(int));
        for(int j=0;j<n;j++)adj[i][j]=-20000;
    }

    // printadj(adj,n);

    for (int i=0;i<n;i++){  //Taking adjlist input into adjmatrix
        char input[1000];
        fgets(input,1000,stdin);
        int j=0;
        int temp=0;
        while(input[j]!='\0' && input[j]!='\n'){
            
            if (input[j]==' '){
                // printi(temp);
                if (temp!=i){
                    adj[i][temp]-=1;
                }
                temp=0;
            }
            else{
                temp*=10;
                temp+=(input[j]-'0');
            }
            j++;
        }
        // printi(temp);
        if (temp!=i){
            adj[i][temp]-=1;
        }

    }


    // printadj(adj,n);
    int edgecount=0;

    for (int i=0;i<n;i++){  //Adding Weights
        char input[1000];
        fgets(input,1000,stdin);
        int j=0;
        int temp=0;
        int c=0;
        int mc=0;
        while(input[j]!='\0' && input[j]!='\n'){
            if (input[j]=='-'){
                mc=1;
            }
            else if (input[j]==' '){
                if (c>0){
                    int k=0;
                    while(adj[i][k]!=-20001) k++;
                    if (mc) adj[i][k]=-temp;
                    else adj[i][k]=temp;
                    if (i<k)edgecount++;
                }
                temp=0;
                mc=0;
                c++;
            }
            else{
                temp*=10;
                temp+=(input[j]-'0');
            }
            j++;
        }
        if (c>0){
            int k=0;
            while(adj[i][k]!=-20001) k++;
            // printi(k);
            if (mc) adj[i][k]=-temp;
            else adj[i][k]=temp;
            if (i<k)edgecount++;
        }
        temp=0;
    }

    // printadj(adj,n);


    struct heap * H=(struct heap *)malloc(sizeof(struct heap));    
    H->arr=(struct note **)malloc(sizeof(struct note *)*n);
    for (int i=0;i<n;i++) {
        H->arr[i]=(struct note *)malloc(sizeof(struct note));
        H->arr[i]->num=i;
        if (i==0)H->arr[i]->key=0;
        else H->arr[i]->key=100000;
        H->arr[i]->p=NULL;
    }

    
    H->heap_size=n;
    build(H);

    // for (int i=0;i<n;i++){
    //     printf("%d with key: %d\n",H->arr[i]->num,H->arr[i]->key);
    // }
    int ans=0;
    while(H->heap_size!=0){
        printf("\nBefore extracting:-----\n");
        for (int i=0;i<H->heap_size;i++){
            printf("%d with key: %d\n",H->arr[i]->num,H->arr[i]->key);
        }
        printf("\n");

        struct note * temp=extractmin(H);

        printf("Node : %d adding: %d\n",temp->num,temp->key);
        ans+=temp->key;
        for (int i=0;i<n;i++){
            struct note * v=linearsearch(H,i);
            
            if (adj[temp->num][i]!=-20000 && v && adj[temp->num][i] < v->key){
                printf("%d %d V: %p\n",temp->num,i,v);
                v->p=temp;
                heap_decrease_key(H,linearsearchind(H,i),adj[temp->num][i]);
                        printf("\n");
                        for (int i=0;i<n;i++){
                            printf("%d with key: %d\n",H->arr[i]->num,H->arr[i]->key);
                        }
                        printf("\n");
            }
        }
    }

    printi(ans);

}


int main(){
    char x;
    scanf("%c",&x);
    if (x=='a'){
        kruskals();
    }
    if (x=='b'){
        prims();
    }
}

/*
b
7
0 1 2
1 0 2 3 5
2 0 1 4 5
3 1 5 6
4 2 5 6
5 1 2 3 4 6
6 3 4 5
0 5000 2000
1 5000 6000 2000 8000
2 2000 6000 1000 4000
3 2000 -9000 7000
4 1000 -6000 2000
5 8000 4000 -9000 -6000 1000
6 7000 2000 1000
*/