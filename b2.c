#include <stdio.h>
#include <string.h>

struct Product {
    int id;             
    char name[100];     
    float importPrice; 
    float sellPrice;    
    int quantity;       
};

// Hàm tìm sản phẩm theo tên
int findProductByName(struct Product *products, int size, const char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(products[i].name, name) == 0) {
            return i; 
        }
    }
    return -1; 
}

void addProduct(struct Product *products, int *size, float *revenue) {
    struct Product newProduct;
    printf("Nhập tên sản phẩm: ");
    getchar();
    fgets(newProduct.name, sizeof(newProduct.name), stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = '\0';

    int index = findProductByName(products, *size, newProduct.name);
    if (index != -1) {
        int additionalQuantity;
        printf("Sản phẩm đã tồn tại. Nhập số lượng cần thêm: ");
        scanf("%d", &additionalQuantity);
        products[index].quantity += additionalQuantity;
        *revenue -= additionalQuantity * products[index].importPrice;
        printf("Đã cập nhật số lượng sản phẩm.\n");
    } else {
        newProduct.id = *size + 1;
        printf("Nhập giá nhập: ");
        scanf("%f", &newProduct.importPrice);
        printf("Nhập giá bán: ");
        scanf("%f", &newProduct.sellPrice);
        printf("Nhập số lượng: ");
        scanf("%d", &newProduct.quantity);

        products[*size] = newProduct;
        (*size)++;
        *revenue -= newProduct.quantity * newProduct.importPrice;
        printf("Đã thêm sản phẩm mới.\n");
    }
}

void displayProducts(struct Product *products, int size) {
    printf("\nDanh sách sản phẩm:\n");
    for (int i = 0; i < size; i++) {
        printf("Mã: %d, Tên: %s, Giá nhập: %.2f, Giá bán: %.2f, Số lượng: %d\n",
               products[i].id, products[i].name, products[i].importPrice, products[i].sellPrice, products[i].quantity);
    }
}

void sellProduct(struct Product *products, int size, float *revenue) {
    char name[100];
    printf("Nhập tên sản phẩm cần bán: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int index = findProductByName(products, size, name);
    if (index == -1) {
        printf("Không tìm thấy sản phẩm \"%s\".\n", name);
        return;
    }

    if (products[index].quantity == 0) {
        printf("Sản phẩm \"%s\" đã hết hàng.\n", name);
        return;
    }

    int sellQuantity;
    printf("Nhập số lượng cần bán: ");
    scanf("%d", &sellQuantity);

    if (sellQuantity > products[index].quantity) {
        printf("Không đủ hàng để bán. Số lượng hiện có: %d\n", products[index].quantity);
    } else {
        products[index].quantity -= sellQuantity;
        *revenue += sellQuantity * products[index].sellPrice;
        printf("Đã bán %d sản phẩm \"%s\".\n", sellQuantity, name);
    }
}

void sortProductsByPrice(struct Product *products, int size, int ascending) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if ((ascending && products[i].sellPrice > products[j].sellPrice) ||
                (!ascending && products[i].sellPrice < products[j].sellPrice)) {
                struct Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
    printf("Đã sắp xếp danh sách sản phẩm theo giá.\n");
}

void searchProduct(struct Product *products, int size) {
    char name[100];
    printf("Nhập tên sản phẩm cần tìm: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int index = findProductByName(products, size, name);
    if (index == -1) {
        printf("Không tìm thấy sản phẩm \"%s\".\n", name);
    } else {
        printf("Tìm thấy: Mã: %d, Tên: %s, Giá nhập: %.2f, Giá bán: %.2f, Số lượng: %d\n",
               products[index].id, products[index].name, products[index].importPrice, products[index].sellPrice, products[index].quantity);
    }
}

int main() {
    struct Product products[100];
    int size = 0;
    float revenue = 0.0;
    int choice;

    do {
        printf("\n========== THỰC ĐƠN ==========\n");
        printf("1. Nhập sản phẩm số lượng và thông tin\n");
        printf("2. Hiển thị danh sách sản phẩm\n");
        printf("3. Nhập sản phẩm\n");
        printf("4. Sắp xếp sản phẩm theo giá\n");
        printf("5. Tìm kiếm sản phẩm\n");
        printf("6. Bán sản phẩm\n");
        printf("7. Doanh thu hiện tại\n");
        printf("8. Thoát\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(products, &size, &revenue);
                break;
            case 2:
                displayProducts(products, size);
                break;
            case 3:
                addProduct(products, &size, &revenue);
                break;
            case 4: {
                int subChoice;
                printf("1. Sắp xếp tăng dần theo giá\n");
                printf("2. Sắp xếp giảm dần theo giá\n");
                printf("Lựa chọn của bạn: ");
                scanf("%d", &subChoice);
                if (subChoice == 1) {
                    sortProductsByPrice(products, size, 1);
                } else if (subChoice == 2) {
                    sortProductsByPrice(products, size, 0);
                } else {
                    printf("Lựa chọn không hợp lệ.\n");
                }
                break;
            }
            case 5:
                searchProduct(products, size);
                break;
            case 6:
                sellProduct(products, size, &revenue);
                break;
            case 7:
                printf("Doanh thu hiện tại: %.2f\n", revenue);
                break;
            case 8:
                printf("Thoát chương trình.\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
        }
    } while (choice != 8);

    return 0;
}