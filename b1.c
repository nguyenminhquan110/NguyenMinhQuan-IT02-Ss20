#include <stdio.h>
#include <string.h>

struct Book {
    int id;            
    char name[100];   
    char author[100];  
    float price;      
    char category[50];  
};

void inputBooks(struct Book *books, int *size) {
    printf("Nhập số lượng sách: ");
    scanf("%d", size);
    getchar(); 

    for (int i = 0; i < *size; i++) {
        books[i].id = i + 1; 
        printf("Nhập thông tin sách thứ %d:\n", i + 1);

        printf("Tên sách: ");
        fgets(books[i].name, sizeof(books[i].name), stdin);
        books[i].name[strcspn(books[i].name, "\n")] = '\0';

        printf("Tác giả: ");
        fgets(books[i].author, sizeof(books[i].author), stdin);
        books[i].author[strcspn(books[i].author, "\n")] = '\0';

        printf("Giá tiền: ");
        scanf("%f", &books[i].price);
        getchar();

        printf("Thể loại: ");
        fgets(books[i].category, sizeof(books[i].category), stdin);
        books[i].category[strcspn(books[i].category, "\n")] = '\0';

        printf("\n");
    }
}

void displayBooks(struct Book *books, int size) {
    printf("\nDanh sách sách:\n");
    for (int i = 0; i < size; i++) {
        printf("Mã sách: %d, Tên sách: %s, Tác giả: %s, Giá: %.2f, Thể loại: %s\n",
               books[i].id, books[i].name, books[i].author, books[i].price, books[i].category);
    }
}

void addBookAtPosition(struct Book *books, int *size, int position, struct Book newBook) {
    if (position < 0 || position > *size || *size >= 100) {
        printf("Vị trí không hợp lệ hoặc danh sách đã đầy.\n");
        return;
    }

    for (int i = *size; i > position; i--) {
        books[i] = books[i - 1];
    }

    books[position] = newBook;
    (*size)++;
    printf("Đã thêm sách thành công.\n");
}

void deleteBookById(struct Book *books, int *size, int id) {
    int found = 0;
    for (int i = 0; i < *size; i++) {
        if (books[i].id == id) {
            found = 1;
            for (int j = i; j < *size - 1; j++) {
                books[j] = books[j + 1];
            }
            (*size)--;
            printf("Đã xóa sách với mã %d.\n", id);
            break;
        }
    }

    if (!found) {
        printf("Không tìm thấy sách với mã %d.\n", id);
    }
}

void updateBookById(struct Book *books, int size, int id) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (books[i].id == id) {
            found = 1;
            printf("Nhập tên sách mới: ");
            getchar();
            fgets(books[i].name, sizeof(books[i].name), stdin);
            books[i].name[strcspn(books[i].name, "\n")] = '\0';

            printf("Nhập tác giả mới: ");
            fgets(books[i].author, sizeof(books[i].author), stdin);
            books[i].author[strcspn(books[i].author, "\n")] = '\0';

            printf("Nhập giá tiền mới: ");
            scanf("%f", &books[i].price);
            getchar();

            printf("Nhập thể loại mới: ");
            fgets(books[i].category, sizeof(books[i].category), stdin);
            books[i].category[strcspn(books[i].category, "\n")] = '\0';

            printf("Đã cập nhật thông tin sách thành công.\n");
            break;
        }
    }

    if (!found) {
        printf("Không tìm thấy sách với mã %d.\n", id);
    }
}

void sortBooksByPrice(struct Book *books, int size, int ascending) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if ((ascending && books[i].price > books[j].price) ||
                (!ascending && books[i].price < books[j].price)) {
                struct Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
    printf("Đã sắp xếp danh sách sách theo giá.\n");
}

void searchBookByName(struct Book *books, int size, const char *name) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (strstr(books[i].name, name)) {
            printf("Tìm thấy: Mã sách: %d, Tên sách: %s, Tác giả: %s, Giá: %.2f, Thể loại: %s\n",
                   books[i].id, books[i].name, books[i].author, books[i].price, books[i].category);
            found = 1;
        }
    }

    if (!found) {
        printf("Không tìm thấy sách với tên \"%s\".\n", name);
    }
}

int main() {
    struct Book books[100];
    int size = 0;
    int choice;

    do {
        printf("\n========== THỰC ĐƠN ==========\n");
        printf("1. Nhập số lượng và thông tin sách\n");
        printf("2. Hiển thị danh sách thông tin sách\n");
        printf("3. Thêm sách vào vị trí\n");
        printf("4. Xóa sách theo mã sách\n");
        printf("5. Cập nhật thông tin sách theo mã sách\n");
        printf("6. Sắp xếp danh sách theo giá\n");
        printf("7. Tìm kiếm sách theo tên\n");
        printf("8. Thoát\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputBooks(books, &size);
                break;
            case 2:
                displayBooks(books, size);
                break;
            case 3: {
                struct Book newBook;
                int position;
                printf("Nhập vị trí cần chèn (0 đến %d): ", size);
                scanf("%d", &position);
                getchar();
                newBook.id = size + 1;
                printf("Nhập tên sách: ");
                fgets(newBook.name, sizeof(newBook.name), stdin);
                newBook.name[strcspn(newBook.name, "\n")] = '\0';

                printf("Nhập tác giả: ");
                fgets(newBook.author, sizeof(newBook.author), stdin);
                newBook.author[strcspn(newBook.author, "\n")] = '\0';

                printf("Nhập giá tiền: ");
                scanf("%f", &newBook.price);
                getchar();

                printf("Nhập thể loại: ");
                fgets(newBook.category, sizeof(newBook.category), stdin);
                newBook.category[strcspn(newBook.category, "\n")] = '\0';

                addBookAtPosition(books, &size, position, newBook);
                break;
            }
            case 4: {
                int id;
                printf("Nhập mã sách cần xóa: ");
                scanf("%d", &id);
                deleteBookById(books, &size, id);
                break;
            }
            case 5: {
                int id;
                printf("Nhập mã sách cần cập nhật: ");
                scanf("%d", &id);
                updateBookById(books, size, id);
                break;
            }
            case 6: {
                int subChoice;
                printf("1. Sắp xếp tăng dần theo giá\n");
                printf("2. Sắp xếp giảm dần theo giá\n");
                printf("Lựa chọn của bạn: ");
                scanf("%d", &subChoice);
                if (subChoice == 1) {
                    sortBooksByPrice(books, size, 1);
                } else if (subChoice == 2) {
                    sortBooksByPrice(books, size, 0);
                } else {
                    printf("Lựa chọn không hợp lệ.\n");
                }
                break;
            }
            case 7: {
                char name[100];
                printf("Nhập tên sách cần tìm: ");
                getchar();
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                searchBookByName(books, size, name);
                break;
            }
            case 8:
                printf("Thoát chương trình.\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
        }
    } while (choice != 8);

    return 0;
}