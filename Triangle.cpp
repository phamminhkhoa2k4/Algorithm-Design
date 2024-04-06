#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
int triangle[MAX_N][MAX_N];
int F[MAX_N][MAX_N];
void readData(const char* filename, int* n) {
    FILE* file = fopen(filename, "r");
    fscanf(file, "%d", n);
    for (int i = 0; i < *n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i == 0 && j == 0) {
                fscanf(file, "%d", &triangle[i][j]);
                F[i][j] = triangle[i][j];
            } else {
                fscanf(file, "%d", &triangle[i][j]);
                F[i][j] = -1;
            }
        }
    }
    fclose(file);
}

// Hàm tính toán giá trị lớn nhất của tam giác số và lưu vào F
int maxSum(int i, int j, int n) {
    if (F[i][j] != -1) return F[i][j];
    if (i == n - 1) {
        F[i][j] = triangle[i][j];
    } else {
        int maxChildSum = triangle[i][j] + (maxSum(i + 1, j, n), maxSum(i + 1, j + 1, n));
        F[i][j] = maxChildSum;
    }

    return F[i][j];
}

// Hiển thị tam giác số
void displayTriangle(int n) {
    printf("Tam giac so:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            printf("%d ", triangle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Hiển thị bảng số liệu F
void displayF(int n) {
    printf("Bang du lieu F:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            printf("%d ", F[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int n;
    readData("tam_giac_so.txt", &n);
//  readData("tam_giac_so1.txt", &n);
    maxSum(0, 0, n);

    displayTriangle(n);
    displayF(n);

    int maxPathSum = F[0][0];
    for (int j = 1; j < n; ++j) {
        if (F[0][j] > maxPathSum) {
            maxPathSum = F[0][j];
        }
    }
    printf("Tong gia tri cac so tren duong di tu dong dau den dong cuoi: %d\n", maxPathSum);

    return 0;

}
