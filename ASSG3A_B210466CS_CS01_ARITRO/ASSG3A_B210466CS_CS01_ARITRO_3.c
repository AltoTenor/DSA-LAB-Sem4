#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct heap{
    int *arr;
    int heap_size;
};

void max_heapify(struct heap * H,int i){
    int l=2*i+1;
    int r=2*i+2;
    int largest;
    if (l< H->heap_size && H->arr[i] < H->arr[l]) largest=l;
    else largest=i;
    if (r< H->heap_size && H->arr[largest] < H->arr[r]) largest=r;
    if (largest!=i){
        int temp=H->arr[largest];
        H->arr[largest]=H->arr[i];
        H->arr[i]=temp;
        max_heapify(H,largest);
    }
}

void build(struct heap * H){
    for (int i=H->heap_size;i>=0;i--){
        max_heapify(H,i);
    }
}

int mostmax(struct heap * H){
    if (H->heap_size < 1) return -1;
    else return H->arr[0];
}

int extractmax(struct heap * H){
    if (H->heap_size<1) return -1;
    else {
        int mx=H->arr[0];
        H->arr[0]=H->arr[H->heap_size-1];
        H->heap_size--;
        max_heapify(H,0);
        return mx;
    }
}

void print(struct heap * H){
    for (int i=0;i<H->heap_size;i++){
        printf("%d ",H->arr[i]);
    }
}

void solve(){
    int n,k;
    scanf("%d",&n);
    struct heap * H = (struct heap *)malloc(sizeof(struct heap));
    H->arr=(int *)malloc(sizeof(int)*n);
    H->heap_size=n;
    for (int i=0;i<n;i++)scanf("%d",&H->arr[i]);
    build(H);
    scanf("%d",&k);
    while(k--){
        // print(H);
        printf("%d ",extractmax(H));
    }
    printf("\n");
}

int main(){
    int t;
    scanf("%d",&t);
    
    while(t--)solve();
    
}

