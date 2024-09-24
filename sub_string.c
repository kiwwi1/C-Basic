#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_TABLE_SIZE 100 // Kích thước bảng băm

typedef struct BookingRequest {
    char requestCode[8];
    int numPeople;
    int numRooms;
    char hotelCode[8];
    char date[11]; // Thêm thành phần ngày tháng năm dưới dạng xâu kí tự
    int numChildren;
    struct BookingRequest* next;
}BookingRequest;

 BookingRequest* readBookingFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Không thể mở file");
        exit(EXIT_FAILURE);
    }

    int numRequests;
    fscanf(file, "%d", &numRequests);

 BookingRequest* head = NULL;
 BookingRequest* current = NULL;

    for (int i = 0; i < numRequests; ++i) {
         BookingRequest* newRequest = ( BookingRequest*)malloc(sizeof( BookingRequest));
        if (newRequest == NULL) {
            perror("Lỗi khi cấp phát bộ nhớ");
            exit(EXIT_FAILURE);
        }

        fscanf(file, "%s %d %d %s %s %d", newRequest->requestCode, &newRequest->numPeople, &newRequest->numRooms,
               newRequest->hotelCode, newRequest->date, &newRequest->numChildren);

        newRequest->next = NULL;

        if (head == NULL) {
            head = newRequest;
            current = newRequest;
        } else {
            current->next = newRequest;
            current = newRequest;
        }
    }

    fclose(file);

    return head;
}

void printNumRequests(BookingRequest* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }

    printf("So yeu cau doc duoc: %d\n", count);
}

void freeBookingList(BookingRequest* head) {
    while (head != NULL) {
         BookingRequest* temp = head;
        head = head->next;
        free(temp);
    }
}
void printBookingRequest(struct BookingRequest* request) {
    printf("Mã yêu cầu: %s\n", request->requestCode);
    printf("Số người: %d\n", request->numPeople);
    printf("Số phòng: %d\n", request->numRooms);
    printf("Mã khách sạn: %s\n", request->hotelCode);
    printf("Ngày đặt phòng: %s\n", request->date);
    printf("Số trẻ em: %d\n", request->numChildren);
}
struct BookingRequest* hashTable[HASH_TABLE_SIZE] = {NULL};

// Hàm băm đơn giản
unsigned int hashFunction(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }
    return hash % HASH_TABLE_SIZE;
}

// Hàm để thêm một yêu cầu đặt phòng vào bảng băm
void addToHashTable(struct BookingRequest* request) {
    unsigned int index = hashFunction(request->requestCode);

    request->next = hashTable[index];
    hashTable[index] = request;
}

// Hàm để tìm kiếm yêu cầu đặt phòng trong bảng băm
struct BookingRequest* searchInHashTable(const char* requestCode) {
    unsigned int index = hashFunction(requestCode);

    struct BookingRequest* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->requestCode, requestCode) == 0) {
            return current; // Tìm thấy yêu cầu
        }
        current = current->next;
    }

    return NULL; // Không tìm thấy yêu cầu
}
void updateInHashTable(const char* requestCode, struct BookingRequest* updatedRequest) {
    struct BookingRequest* current = searchInHashTable(requestCode);

    if (current != NULL) {
        // Cập nhật thông tin
        strncpy(current->requestCode, updatedRequest->requestCode, sizeof(current->requestCode));
        current->numPeople = updatedRequest->numPeople;
        current->numRooms = updatedRequest->numRooms;
        strncpy(current->hotelCode, updatedRequest->hotelCode, sizeof(current->hotelCode));
        strncpy(current->date, updatedRequest->date, sizeof(current->date));
        current->numChildren = updatedRequest->numChildren;

        printf("Yêu cầu đã được cập nhật.\n");
    } else {
        printf("Không tìm thấy yêu cầu cần cập nhật.\n");
    }
} 

void deleteInHashTable(const char* requestCode) {
    unsigned int index = hashFunction(requestCode);

    struct BookingRequest* current = hashTable[index];
    struct BookingRequest* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->requestCode, requestCode) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                hashTable[index] = current->next;
            }

            free(current);
            printf("Yêu cầu đã được hủy.\n");
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Không tìm thấy yêu cầu cần hủy.\n");
} 
void displayMenu() {
    printf("===== MENU =====\n");
    printf("1. Hiển thị thông tin yêu cầu theo mã\n");
    printf("2. Cập nhật thông tin yêu cầu\n");
    printf("3.Huy yeu cau\n");
    printf("4. Thoát\n");
    printf("================\n");
}

int main() {
    const char* filename = "booking.txt";
    struct BookingRequest* bookingList = readBookingFile(filename);

    struct BookingRequest* current = bookingList;
    while (current != NULL) {
        addToHashTable(current);
        current = current->next;
    }

    int choice;
    char searchCode[8];
    struct BookingRequest updatedRequest;

    do {
        displayMenu();
        printf("Nhập lựa chọn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhập mã yêu cầu cần tìm: ");
                scanf("%s", searchCode);
                struct BookingRequest* result = searchInHashTable(searchCode);
                if (result != NULL) {
                    printf("Thông tin yêu cầu:\n");
                    printBookingRequest(result);
                } else {
                    printf("Không tìm thấy yêu cầu.\n");
                }
                break;

            case 2:
                printf("Nhập mã yêu cầu cần cập nhật: ");
                scanf("%s", searchCode);
                result = searchInHashTable(searchCode);
                if (result != NULL) {
                    printf("Thông tin yêu cầu trước khi cập nhật:\n");
                    printBookingRequest(result);

                    printf("Nhập thông tin cập nhật:\n");
                    printf("Số người: ");
                    scanf("%d", &updatedRequest.numPeople);
                    printf("Số phòng: ");
                    scanf("%d", &updatedRequest.numRooms);
                    printf("Mã khách sạn: ");
                    scanf("%s", updatedRequest.hotelCode);
                    printf("Ngày đặt phòng (dd-mm-yyyy): ");
                    scanf("%s", updatedRequest.date);
                    printf("Số trẻ em: ");
                    scanf("%d", &updatedRequest.numChildren);

                    updateInHashTable(searchCode, &updatedRequest);

                    printf("Thông tin yêu cầu sau khi cập nhật:\n");
                    printBookingRequest(result);
                } else {
                    printf("Không tìm thấy yêu cầu cần cập nhật.\n");
                }
                break;

            case 3:
                printf("Nhập mã yêu cầu cần hủy: ");
                scanf("%s", searchCode);
                deleteInHashTable(searchCode);
                break;

            case 4:
                printf("Thoát chương trình.\n");
                break;

            default:
                printf("Lựa chọn không hợp lệ. Vui lòng chọn lại.\n");
                break;
        }

    } while (choice != 4);

    freeBookingList(bookingList);

    return 0;
}
