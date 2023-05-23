#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct heap{
    int *arr;
    int heap_size;
};

void min_heapify(struct heap * H,int i){
    int l=2*i+1;
    int r=2*i+2;
    int smallest;
    if (l< H->heap_size && H->arr[i] > H->arr[l]) smallest=l;
    else smallest=i;
    if (r< H->heap_size && H->arr[smallest] > H->arr[r]) smallest=r;
    if (smallest!=i){
        int temp=H->arr[smallest];
        H->arr[smallest]=H->arr[i];
        H->arr[i]=temp;
        min_heapify(H,smallest);
    }
}

void build(struct heap * H){
    for (int i=H->heap_size/2;i>=0;i--){
        min_heapify(H,i);
    }
}

int mostmin(struct heap * H){
    if (H->heap_size < 1) return -1;
    else return H->arr[0];
}

int extractmin(struct heap * H){
    if (H->heap_size<1) return -1;
    else {
        int mn=H->arr[0];
        H->arr[0]=H->arr[H->heap_size-1];
        H->heap_size--;
        min_heapify(H,0);
        return mn;
    }
}

void heap_decrease_key(struct heap * H,int i,int key){
    if (key>H->arr[i])return;
    H->arr[i]=key;
    while(i>0 && H->arr[(i-1)/2]>H->arr[i]){
        int temp=H->arr[(i-1)/2];
        H->arr[(i-1)/2]=H->arr[i];
        H->arr[i]=temp;
        i=(i-1)/2;
    }
}

void heap_insert(struct heap * H,int key){
    H->heap_size++;
    H->arr[H->heap_size-1]=1000001;
    heap_decrease_key(H,H->heap_size-1,key);
}

int heap_delete(struct heap * H,int key){
    int f=-1000001;
    for (int i=0;i<H->heap_size;i++){
        
        if (H->arr[i]==key){
            f=i;
            heap_decrease_key(H,i,-1000001);
            extractmin(H);
        }
    }
    if (f==-1000001)return -1;
    else return key;

}

void print(struct heap * H){
    for (int i=0;i<H->heap_size;i++){
        printf("%d ",H->arr[i]);
    }
}

int main(){
    struct heap * H = (struct heap *)malloc(sizeof(struct heap));
    H->arr=(int *)malloc(sizeof(int)*10000);
    H->heap_size=0;
    char op='x';
    int temp,z,y;
    while(op!='e'){
        scanf("%c",&op);
        if (op=='i'){
            scanf("%d",&temp);
            heap_insert(H,temp);
        }
        else if (op=='d'){
            scanf("%d",&temp);
            int p=heap_delete(H,temp);
            printf("%d",p);
            printf("\n");

        }
        else if (op=='p'){
            print(H);
            printf("\n");

        }
        else if (op=='x'){
            extractmin(H);
            print(H);
            printf("\n");
            
        }
        else if (op=='r'){
            scanf("%d",&y);
            scanf("%d",&z);
            int f=1000001;
            for (int i=0;i<H->heap_size;i++){
                if (H->arr[i]==y){
                    f=z;
                    heap_decrease_key(H,i,z);
                }
            }
            if (f==1000001)printf("-1");
            printf("%d",f);
            printf("\n");

        }
        else if (op=='g'){
            int p=mostmin(H);
            printf("%d",p);
            printf("\n");
        }
    }
    
}

