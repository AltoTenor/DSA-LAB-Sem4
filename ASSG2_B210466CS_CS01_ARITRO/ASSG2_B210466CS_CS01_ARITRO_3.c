#include <stdio.h>
#include<stdlib.h>
#include<string.h>



int main(){
    int n;
    scanf("%d",&n);
    int *arr=(int *)malloc(n*sizeof(int));
    int *arr1=(int *)malloc(n*sizeof(int));
    int mx=-1;
    for (int i=0;i<n;i++){
        scanf("%d",arr+i);
        // printf("%d ",arr[i]);
    }
    for (int i=0;i<n;i++){
        scanf("%d",arr1+i);
        // printf("%d ",arr1[i]);
    }
    for (int i=0;i<n;i++){
        if (mx<arr[i])mx=arr[i];
        if (mx<arr1[i])mx=arr1[i];
    }

    int hash[100001];
    for (int i=0;i<100001;i++){
        hash[i]=0;
    }
    for (int i=0;i<n;i++){
        hash[arr[i]]++;
    }

    int hash1[100001];
    for (int i=0;i<100001;i++){
        hash1[i]=0;
    }
    for (int i=0;i<n;i++){
        hash1[arr1[i]]++;
    }
    int flag=1;
    for (int i=0;i<100001;i++){
        if (hash[i]!=hash1[i])flag=0;
    }
    if (flag==1)printf("1\n");
    else printf("0\n");

}

