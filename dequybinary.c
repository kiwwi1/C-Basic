#include<stdio.h>
int v,k,n,x[3];
void solution(){
    for(int i=1;i<=n;i++){
        printf("%d",x[i]);
    }
    printf("\n");
}
int check(int v,int k){
    return 1;
}
void try(int k){
    for(int v=0;v<=1;v++){
        if(check(v,k)){
            x[k]=v;
            if(k==n) solution();
             else try(k+1);
        }
    }
}
int main(){
    scanf("%d",&n);
    try(1);
}