#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAX_LEN 100
void printArray(int A[], int N){
    for (int i = 1; i <= N; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// Hàm sắp xếp lựa chọn
void selectionSort(int A[], int N) {
    // index tu 1 -> N
    for(int k = 1; k <= N; k++){
        int min = k;
        for(int j = k+1; j <= N; j++){
            if(A[min] > A[j]) min = j;
        }
        int tmp = A[min]; 
        A[min] = A[k]; 
        A[k] = tmp;

        printArray(A, N);
    }
}
// Hàm sắp xếp chèn
void insertionSort(int A[], int N) {
    // index tu 1 -> N
    for(int k = 2; k <= N; k++){
        int last = A[k];
        int j = k;
        while(j > 1 && A[j-1] > last){
            A[j] = A[j-1];
            j--;
        }
        A[j] = last;

        printArray(A, N);
    }
}

// Hàm sắp xếp nổi bọt
void bubleSort(int A[], int N) {
    // index tu 1 den N
    int swapped;
    do{
        swapped = 0;
        for(int i = 1; i < N; i++){
            if(A[i] > A[i+1]){
                int tmp = A[i]; 
                A[i] = A[i+1];
                A[i+1] = tmp;
                swapped = 1;
            }
        }

        printArray(A, N);
    }while(swapped == 1); 
}
    int main() {
    char buff[MAX_LEN];
    int A[MAX_LEN], count = 0;
    
    // Đọc dãy số vào bộ đệm
    fgets(buff, MAX_LEN, stdin);

    // Sử dụng strtok() để tách xâu bằng dấu khoảng cách
    char *token = strtok(buff, " ");

    // Nhập vào mảng
    while (token != NULL) {
        count++;
        A[count] = atoi(token); // Lấy số hiện tại
        token = strtok(NULL, " "); // Lấy số tiếp theo
    }
    selectionSort(A,count);
}