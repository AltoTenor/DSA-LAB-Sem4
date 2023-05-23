#include <stdio.h>
#include<stdlib.h>
#include<string.h>

void linear_probe(int *arr,int n,int cnt){
    int * hash=(int *)malloc(n*sizeof(int));
    for (int i=0;i<n;i++){
        hash[i]=-1;
    }
    int f=0;
    int col=0;
    for (int i=0;i<cnt;i++){
        f=0;
        int j=0;
        // printf("Arr[i]: %d\n",arr[i]);
        int key=arr[i]%n;
        while(!f){
            if (hash[key]==-1){
                hash[key]=arr[i];
                printf("%d ",key);
                f=1;
            }
            else{ 
                j++;
                key=((arr[i]%n)+j)%n;
                // printf("arr[i]: %d J: %d\n",arr[i],j);
                col++;
            }
        }
        // printf("Collisions till now: %d\n",col);
    }
    printf("\n%d\n",col);
}


void quad_probe(int *arr,int n,int cnt){
    int * hash=(int *)malloc(n*sizeof(int));
    for (int i=0;i<n;i++){
        hash[i]=-1;
    }
    int f=0;
    int col=0;
    for (int i=0;i<cnt;i++){
        f=0;
        int j=0;
        // printf("Arr[i]: %d\n",arr[i]);
        int key=arr[i]%n;
        while(!f && j<n){
            if (hash[key]==-1){
                hash[key]=arr[i];
                printf("%d ",key);
                f=1;
            }
            else{ 
                j++;
                key=((arr[i]%n)+j*j)%n;
                // printf("arr[i]: %d J: %d\n",arr[i],j);
                col++;
            }
        }
        if (f==0) printf("E ");
        // printf("Collisions till now: %d\n",col);
    }
    printf("\n%d\n",col);
}

void double_hash(int *arr,int n,int cnt,int R){
    int * hash=(int *)malloc(n*sizeof(int));
    for (int i=0;i<n;i++){
        hash[i]=-1;
    }
    int f=0;
    int col=0;
    for (int i=0;i<cnt;i++){
        f=0;
        // printf("Arr[i]: %d\n",arr[i]);
        int h1=arr[i]%n;
        int h2=R-(arr[i]%R);
        int key=h1;
        int j=0;
        while(!f && j<n){
            if (hash[key]==-1){
                hash[key]=arr[i];
                printf("%d ",key);
                f=1;
            }
            else{ 
                j++;
                key=(h1+j*h2)%n;
                col++;
            }
        }
        if (f==0) printf("E ");
        // printf("Collisions till now: %d\n",col);
    }
    printf("\n%d\n",col);
}


int prime(int n){
    if (n==1 || n==2)return 1;
    for (int i=n-1;i>2;i--){
        int f=1;
        for (int j=2;j<i;j++){
            if (i%j==0)f=0;
        }
        if (f)return i;
    }
}

int main(){
    int n;
    scanf("%d\n",&n);
    int * arr=(int *)malloc(n*sizeof(int));
    char input[1000];
    fgets(input,1000,stdin);
    int temp=0,k=0;
    for (int i=0;input[i]!='\n';i++){
        if (input[i]==' '){
            arr[k]=temp;
            k++;
            temp=0;
        }
        else{
            temp*=10;
            temp+=(input[i]-'0');
        }
    }
    arr[k]=temp;
    // for (int i=0;i<k+1;i++) printf("%d ",arr[i]);
    int R=prime(n);
    linear_probe(arr,n,k+1);
    quad_probe(arr,n,k+1);
    // if (n==1)printf("0\n0\n");
    double_hash(arr,n,k+1,R);
}