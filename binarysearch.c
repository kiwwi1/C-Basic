#include <stdio.h>

void findTriplets(int arr[], int n, int Q) {
    int i, left, right;
    int ans=0;

    for (i = 0; i < n - 2; i++) {
        left = i + 1;
        right = n - 1;

        while (left < right) {
            int currentSum = arr[i] + arr[left] + arr[right];

            if (currentSum == Q) {
                printf("%d %d %d\n", arr[i], arr[left], arr[right]);
                left++;
                right--;
                ans++;
            } else if (currentSum < Q) {
                left++;
            } else {
                right--;
            }
        }
    }
    if(ans==0) printf("Not found");
}

int main() {
    int n, Q;

    // Nhập số phần tử và giá trị Q
    scanf("%d %d", &n, &Q);

    // Khai báo mảng và nhập giá trị cho mảng
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sắp xếp mảng để sử dụng tìm kiếm nhị phân
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    findTriplets(arr, n, Q);

    return 0;
}
