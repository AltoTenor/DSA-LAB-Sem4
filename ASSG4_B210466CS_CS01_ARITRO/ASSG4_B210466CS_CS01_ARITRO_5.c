#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int num;
    int d;
    struct node * p;
};


struct heap{
    struct node **arr;
    int heap_size;
};

void min_heapify(struct heap * H,int i){
    int l=2*i+1;
    int r=2*i+2;
    int smallest;
    if (l< H->heap_size && H->arr[i]->d > H->arr[l]->d) smallest=l;
    else smallest=i;
    if (r< H->heap_size && H->arr[smallest]->d > H->arr[r]->d) smallest=r;
    if (smallest!=i){
        struct node * temp=(struct node *)malloc(sizeof(struct node));
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

struct node* extractmin(struct heap * H){
    if (H->heap_size<1) return NULL;
    else {
        struct node*  mn=(struct node *)malloc(sizeof(struct node));
        *(mn)=*(H->arr[0]);
        *(H->arr[0])=*(H->arr[H->heap_size-1]);
        H->arr[H->heap_size-1]->d=1000000000;
        H->heap_size--;
        min_heapify(H,0);
        return mn;
    }
}

void heap_decrease_key(struct heap * H,int i,int key){
    if (key>H->arr[i]->d)return;
    H->arr[i]->d=key;
    while(i>0 && H->arr[(i-1)/2]->d > H->arr[i]->d){
        struct node* temp=(struct node *)malloc(sizeof(struct node));
        *temp=*(H->arr[(i-1)/2]);
        *(H->arr[(i-1)/2])=*(H->arr[i]);
        *(H->arr[i])=*temp;
        i=(i-1)/2;
    }
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

struct node * linearsearch(struct heap * H,int x){
    for (int i=0;i<H->heap_size;i++) if (H->arr[i]->num==x) return H->arr[i];
    return NULL;
}

int linearsearchind(struct heap * H,int x){
    for (int i=0;i<H->heap_size;i++) if (H->arr[i]->num==x) return i;
    return -1;
}

void djikstras_apsp(int ** adj,int n,int src){
    struct heap * H=(struct heap *)malloc(sizeof(struct heap));    
    H->arr=(struct node **)malloc(sizeof(struct node *)*n);
    for (int i=0;i<n;i++){
        H->arr[i]=(struct node *)malloc(sizeof(struct node));
        H->arr[i]->num=i;
        H->arr[i]->d=1000000000;
        H->arr[i]->p=NULL; 
    }
    H->arr[src]->d=0;
    H->heap_size=n;
    build(H);
    // printf("\n");
    // for (int i=0;i<n;i++){
    //     printf("%d with d: %d\n",H->arr[i]->num,H->arr[i]->d);
    // }
    // printf("\n");
    int * dist=(int *)malloc(4*n);
    for (int i=0;i<n;i++) printf("%d ",dist[i]);
    printf("\n");
    // printadj(adj,n);
    while(H->heap_size!=0){
        // printf("Before extracting---------------------------\n");
        // for (int i=0;i<n;i++){
        //     printf("%d with d: %d\n",H->arr[i]->num,H->arr[i]->d);
        // }
        // printf("\n");
        struct node * u=extractmin(H);
        dist[u->num]=u->d;
        // printf("On node %d with dist %d \n",u->num,u->d);
        for (int j=0;j<n;j++){
            struct node * v=linearsearch(H,j);
            if (adj[u->num][j]!=-20000 && v &&  v->d > u->d + adj[u->num][j]){
                // printf("U: %d to  V: %d\n",u->num,v->num);
                heap_decrease_key(H,linearsearchind(H,j),u->d + adj[u->num][j]);
            }
        }
    }
    for (int i=0;i<n;i++){
        if (dist[i]>=1000000000) printf("INF ");
        else printf("%d ",dist[i]);
    }
    printf("\n");
}

void djikstras_spsp(int ** adj,int n,int src,int dest){
    struct heap * H=(struct heap *)malloc(sizeof(struct heap));    
    H->arr=(struct node **)malloc(sizeof(struct node *)*n);
    for (int i=0;i<n;i++){
        H->arr[i]=(struct node *)malloc(sizeof(struct node));
        H->arr[i]->num=i;
        H->arr[i]->d=1000000000;
        H->arr[i]->p=NULL; 
    }
    H->arr[src]->d=0;
    H->heap_size=n;
    build(H);
    int * dist=(int *)malloc(4*n);
    // printadj(adj,n);
    while(H->heap_size!=0){
        // printf("Before extracting---------------------------\n");
        // for (int i=0;i<n;i++){
        //     printf("%d with d: %d\n",H->arr[i]->num,H->arr[i]->d);
        // }
        // printf("\n");
        struct node * u=extractmin(H);
        dist[u->num]=u->d;
        // printf("On node %d with dist %d \n",u->num,u->d);
        for (int j=0;j<n;j++){
            struct node * v=linearsearch(H,j);
            if (adj[u->num][j]!=-20000 && v &&  v->d > u->d + adj[u->num][j]){
                // printf("U: %d to  V: %d\n",u->num,v->num);
                heap_decrease_key(H,linearsearchind(H,j),u->d + adj[u->num][j]);
            }
        }
    }
    if (dist[dest]>=1000000000) printf("UNREACHABLE\n");
    else printf("%d\n",dist[dest]);
    
}


int main(){
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
        while(input[j]!='\0' && input[j]!='\n'){
            if (input[j]==' '){
                if (c>0){
                    int k=0;
                    while(adj[i][k]!=-20001) k++;
                    adj[i][k]=temp;
                    if (i<k)edgecount++;
                }
                temp=0;
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
            adj[i][k]=temp;
            if (i<k)edgecount++;
        }
        temp=0;
    }

    // printadj(adj,n);
    char input[30000];
    int src,dest;
    while(input[0]!='s' || input[1]!='t'){
        scanf("%s",input);
        // printf("%s",input);
        if (input[0]=='a' && input[1]=='p'){
            scanf("%d",&src);
            djikstras_apsp(adj,n,src);
        }
        if (input[0]=='s' && input[1]=='s'){
            scanf("%d",&src);
            scanf("%d",&dest);
            djikstras_spsp(adj,n,src,dest);
        }
    }
    
    
    
}