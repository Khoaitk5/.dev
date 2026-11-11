#include <stdio.h>
#include <stdbool.h>

#define APP_VERSION 2026

// TODO 1: Viết 2 macro SQUARE(x) (tính bình phương x) và ADD(a, b) (tính tổng a + b)
// Lưu ý: Bọc dấu ngoặc hợp lý để tránh sai thứ tự ưu tiên toán tử khi truyền
//        biểu thức (vd: 1 + 2) hoặc đặt macro bên trong phép tính khác (vd: 100 / ADD(...))
#define SQUARE(x) ((x) * (x))
#define ADD(a, b) ((a) + (b))

// TODO 2: Viết hàm static inline safe_max(int a, int b) trả về giá trị lớn hơn
// - a, b: Hai số nguyên cần so sánh
// Lưu ý: Dùng hàm thay cho macro toán tử bậc 3 để tránh lỗi đánh giá kép
//        khi truyền vào biểu thức có tác dụng phụ (như m1++, m2++)
static inline int safe_max(int a, int b) {
    return (a > b) ? a : b;
}

// TODO 3: Viết macro SWAP_INT(a, b) hoán đổi giá trị của hai biến nguyên a và b
// Lưu ý: Dùng cấu trúc khối an toàn trong câu lệnh if/else (tránh lỗi dấu ;)
//        và đặt tên biến tạm sao cho không trùng với biến truyền vào (vd: biến tên 'tmp')
#define SWAP_INT(a, b) do { \
    (a) = (a) ^ (b);        \
    (b) = (a) ^ (b);        \
    (a) = (a) ^ (b);        \
} while (0)

// TODO 4: Viết cặp macro 2 tầng STR(x) và EXPAND_STR(x) để chuỗi hóa giá trị macro
// - STR(x): Biến x thành chuỗi nguyên bản (trả về tên macro nếu x là một macro)
// - EXPAND_STR(x): Mở rộng x lấy giá trị trước rồi mới biến thành chuỗi
#define STR(x) #x
#define EXPAND_STR(x) STR(x)

int main(void) {
    printf("=== TEST 1: BAY THU TU UU TIEN TOAN TU ===\n");
    printf("SQUARE(1 + 2)   = %d (Ky vong: 9)\n", SQUARE(1 + 2));
    printf("100 / ADD(2, 3) = %d (Ky vong: 20)\n", 100 / ADD(2, 3));

    printf("\n=== TEST 2: BAY DANH GIA KEP (SIDE EFFECTS) ===\n");
    int m1 = 5, m2 = 10;
    int max_val = safe_max(m1++, m2++);
    printf("Max = %d | m1 = %d, m2 = %d (Ky vong: Max=10, m1=6, m2=11)\n", max_val, m1, m2);

    printf("\n=== TEST 3: BAY KHOI LENH IF-ELSE VA TRUNG TEN BIEN ===\n");
    int x = 10, y = 20;
    bool need_swap = true;
    if (need_swap)
        SWAP_INT(x, y);
    else
        printf("Khong hoan doi\n");
    printf("Sau hoan doi: x = %d, y = %d\n", x, y);

    int tmp = 99, other = 55;
    SWAP_INT(tmp, other);
    printf("Hoan doi bien ten 'tmp': tmp = %d, other = %d\n", tmp, other);

    printf("\n=== TEST 4: BAY STRINGIZING (#) VOI MACRO LONG NHAU ===\n");
    printf("Ten macro : %s\n", STR(APP_VERSION));
    printf("Gia tri   : %s\n", EXPAND_STR(APP_VERSION));

    return 0;
}

