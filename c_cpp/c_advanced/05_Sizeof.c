#include <stdio.h>

// 1. Macro đếm số phần tử của mảng
// Lấy tổng kích thước mảng chia cho kích thước của 1 phần tử
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// 2. Tự chế sizeof bằng số học con trỏ (Pointer Arithmetic)
// - &(var) + 1: Dịch chuyển con trỏ đi đúng 1 đơn vị kiểu dữ liệu của var
// - Ép kiểu về (char*) rồi trừ nhau để ra số bytes chênh lệch
// - size_t là kiểu dữ liệu chuẩn với sizeof
#define MY_SIZEOF_VAR(var) ((size_t)((char*)(&(var) + 1) - (char*)&(var)))

// - (type*)0 + 1: Coi địa chỉ 0 là con trỏ kiểu type*, cộng 1 sẽ nhảy đến vị trí = sizeof(type)
#define MY_SIZEOF_TYPE(type) ((size_t)((type*)0 + 1))

// 3. Struct chưa tối ưu (32 bytes)
// Do các trường xen kẽ nhau làm phát sinh nhiều khoảng đệm (padding)
struct BadOrder {
    char flag1;     // 1 byte  + 7 bytes padding (để double nằm ở địa chỉ chia hết cho 8)
    double price;   // 8 bytes (offset 8..15)
    char flag2;     // 1 byte  + 3 bytes padding (để int nằm ở địa chỉ chia hết cho 4)
    int id;         // 4 bytes (offset 20..23)
    char flag3;     // 1 byte  + 7 bytes padding cuối (để tổng kích thước chia hết cho 8)
}; // Tổng cộng: 32 bytes

// 4. Struct đã tối ưu (16 bytes)
// Sắp xếp theo thứ tự kích thước giảm dần (8 -> 4 -> 1 -> 1 -> 1)
struct GoodOrder {
    double price;   // 8 bytes (offset 0..7)
    int id;         // 4 bytes (offset 8..11)
    char flag1;     // 1 byte  (offset 12)
    char flag2;     // 1 byte  (offset 13)
    char flag3;     // 1 byte  (offset 14)
                    // 1 byte padding cuối (offset 15 để tổng là 16, chia hết cho 8)
}; // Tổng cộng: 16 bytes (tiết kiệm 50% RAM)

int main() {
    // Test 1: Đo kích thước kiểu dữ liệu và biến bằng macro tự chế
    printf("=== Test my_sizeof ===\n");
    double x = 3.14;
    printf("my_sizeof(double): %zu\n", MY_SIZEOF_TYPE(double)); // 8 bytes
    printf("my_sizeof(x):      %zu\n", MY_SIZEOF_VAR(x));      // 8 bytes

    // Test 2: So sánh kích thước struct trước và sau khi tối ưu
    printf("\n=== Struct Optimization ===\n");
    printf("BadOrder size:  %zu bytes\n", sizeof(struct BadOrder));   // In ra 32
    printf("GoodOrder size: %zu bytes\n", sizeof(struct GoodOrder));  // In ra 16

    // Test 3: Đếm số phần tử mảng bằng macro ARRAY_SIZE
    printf("\n=== Array Size vs Pointer ===\n");
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    printf("Array elements: %zu\n", ARRAY_SIZE(nums)); // In ra 7

    return 0;
}
