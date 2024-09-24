#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

int TA[MAX_LEN]; // Mảng trung gian

// Hàm trộn
void merge(int A[], int L, int M, int R) {
// Trộn 2 dãy đã sắp thứ tự A[L...M] và A[M+1...R]
    int i = L; 
    int j = M+1;
    for(int k = L; k <= R; k++){
        if(i > M){ 
            TA[k] = A[j]; 
            j++;
        }
        else if(j > R){
            TA[k] = A[i]; 
            i++;
        }
        else{
            if(A[i] < A[j]){
                TA[k] = A[i]; 
                i++;
            }
            else {
                TA[k] = A[j]; 
                j++;
            }
        }	
    }
    
    for(int k = L; k <= R; k++) 
        A[k] = TA[k];
}

// Hàm sắp xếp trộn
void mergeSort(int A[], int L, int R) {
    if(L < R){
        int M = (L+R)/2;
        mergeSort(A,L,M);
        mergeSort(A,M+1,R);
        merge(A,L,M,R);
    }
}

// Hàm đổi vị trí
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Hàm chia mảng và trả về chỉ số của phần tử pivot
int partition(int A[], int L, int R, int indexPivot) {
    // Lưu giá trị phần tử trụ
    int pivot = A[indexPivot];
    // Đưa phần tử trụ đến vị trí phải nhất
    swap(&A[indexPivot], &A[R]);
    // Khởi tạo chỉ số của phần tử nhỏ
    int storeIndex = L;
    for(int i = L; i <= R-1; i++){
        // Nếu phần tử hiện tại nhỏ hơn phần tử trụ
        if(A[i] < pivot){
            swap(&A[storeIndex], &A[i]); // Đổi chỗ phần tử hiện tại với phẩn tử ở chỉ số nhỏ nhất
            storeIndex++; // Tăng chỉ số của phần tử nhỏ nhất
        }
    }
    swap(&A[storeIndex], &A[R]); // Đến đây storeIndex chứa chỉ số của phần tử lớn hơn phần tử trụ, nên 
    // đổi chỗ cho phần tử trụ đang lưu ở phần tử phải nhất, lúc này các phần tử đã được sắp xếp sao cho bên trái 
    // storeIndex thì nhỏ hơn còn bên phải storeIndex thì lớn hơn phần tư trụ 
    return storeIndex;
}

// Hàm sắp xếp nhanh
void quickSort(int A[], int L, int R) {
    if(L < R){
        // Chọn phần tử trụ là phần tử chính giữa mảng
        int index = (L + R)/2;
        // Lấy chỉ số của pivot sau khi sắp xếp lại mảng để các phần tử bên trái không lớn hơn và các phần 
        // tử bên phải không nhỏ hơn phần tử trụ
        index = partition(A, L, R, index);
        
        // Đệ quy sắp xếp các thành phần bên trái và bên phải phần tử trụ
        if(L < index)
            quickSort(A, L, index-1);
        if(index < R)
            quickSort(A, index+1, R);
    }
}

// Hàm vun đống
void heapify(int A[], int i, int N) {
    int L = 2*i; // Con trái của phần tử thứ i
    int R = 2*i+1; // Con phải của phần tử thứ i
    int max = i; // max lưu vị trí phần tử thứ i
    if(L <= N && A[L] > A[i]) // Nếu con trái của phần tử thứ i lớn hơn nó
        max = L; // Gán max lưu vị trí con trái
    if(R <= N && A[R] > A[max]) // Nếu con phải của phần tử thứ i lớn hơn nó hoặc lớn hơn con trái (lớn hơn cha)
        max = R; // Gán max lưu vị trí con phải
    if(max != i){ 
        swap(&A[i], &A[max]); // Đổi chỗ phần tử thứ i cho con lớn nhất của nó
        heapify(A,max,N); // Vun đống lại từ nút con này (lúc này đã chứa giá trị phần tử thứ i)
    }
}

// Hàm xây đống
void buildHeap(int A[], int N) {
    for(int i = N/2; i >= 1; i--) // Duyệt qua các nút trong
        heapify(A,i,N); // Vun đống cho các nút trong, tính từ các nút trong gần các nút lá nhất
}

// Hàm sắp xếp vun đống
void heapSort(int A[], int N) {
    // index tu 1 -> N
    buildHeap(A,N); // Xây đống
    for(int i = N; i > 1; i--) {
        swap(&A[1], &A[i]); // phần tử thứ nhất lúc này là lớn nhất nên chuyển xuống cuối, tạo thành dãy có thứ tự
        heapify(A, 1, i-1); // vun lại đống cho cây bắt đầu từ phần tử thứ 1 cho đến phần tử thứ i-1
    } 
}

// Hàm hiển thị mảng
void printArray(int A[], int N) {
    for (int i = 1; i <= N; i++)
        printf("%d ", A[i]);
    printf("\n");    
}

int main(){
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

    // Sắp xếp
    //selectionSort(A, count);
    //insertionSort(A, count);
    //bubleSort(A, count);

    //mergeSort(A, 1, count);
    //quickSort(A, 1, count);
    heapSort(A, count);

    printArray(A, count);

    return 0;
}