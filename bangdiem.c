#include<stdio.h>
#include<math.h>
float tinhdiem(float cc,float kt,float ck){
    float diem=cc*0.1+kt*0.4+ck*0.5;
    return diem;
}
int main(){
      int n;
      printf("Nhap so sinh vien: \n");
      scanf("%d",&n);
      char hoten[n][20],masv[n][10];
      int namsinh[5];
      float cc[n],kt[n],ck[n];
      for(int i=1;i<=n;i++){
        printf("Nhap cho sinh vien thu %d \n:",i);
        printf("Ho va ten: ");fflush(stdin);
        gets(hoten[i]);
        printf("Ma sv:");
        gets(masv[i]);
        printf("Nam sinh:");
        scanf("%d",&namsinh[i]);
        printf("Diem: ");
        scanf("%f%f%f",&cc[i],&kt[i],&ck[i]);
        
        printf("%.2f %.2f %.2f",cc[i],kt[i],ck[i]);
      }
}
    