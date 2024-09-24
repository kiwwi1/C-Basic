#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float price;
} Product;

int main() {
    FILE *file;
    char line[100];
    Product products[100];
    int count = 0;

    // Mở tập tin
    file = fopen("product.txt", "r");
    if (file == NULL) {
        printf("Không thể mở tập tin!\n");
        exit(1);
    }

    // Đọc từng dòng trong tập tin
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %[^\t] %s %[^\t] %.0f", &products[count].id, products[count].name, &products[count].price);
        count++;
    }

    // Đóng tập tin
    fclose(file);

    // Hiển thị nội dung mảng
    printf("No\t\tProduct Name\tPrice\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%.0f\n", products[i].id, products[i].name, products[i].price);
    }

    return 0;
}
