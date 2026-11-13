#include <stdio.h>
#include <stddef.h>
#include <math.h>

// TODO 1: Định nghĩa kiểu Vector2D sử dụng Anonymous Union và Anonymous Struct
// Cho phép truy cập 2 tọa độ x, y theo 2 cách trực tiếp (truy cập phẳng):
//   - Cách 1: v.x và v.y (kiểu float)
//   - Cách 2: v.raw[0] và v.raw[1] (mảng float raw[2])
typedef struct {
    union {
        struct {
            float x;
            float y;
        };
        float raw[2];
    };
} Vector2D;

// TODO 2: Cài đặt hàm tính khoảng cách Euclid giữa 2 Vector2D
// - a, b: Hai điểm tọa độ trong mặt phẳng
// Trả về: Căn bậc hai của ((a.x - b.x)^2 + (a.y - b.y)^2)
float calc_distance(Vector2D a, Vector2D b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}

// TODO 3a: Cài đặt hàm tính tổng các phần tử trong mảng số nguyên
// - arr: Con trỏ trỏ tới mảng int
// - n: Số lượng phần tử
// Trả về: Tổng các phần tử (0 nếu arr là NULL hoặc n == 0)
int sum_array(const int *arr, size_t n) {
    if (arr == NULL || n == 0) return 0;
    int total = 0;
    for (size_t i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

// TODO 3b: Viết macro SUM_INT(...) sử dụng Anonymous Array (Compound Literal)
// Tự động đóng gói các đối số truyền vào thành mảng tạm (int[]){...}
// và tự tính kích thước mảng bằng sizeof để truyền vào hàm sum_array
#define SUM_INT(...) sum_array((int[]){__VA_ARGS__}, sizeof((int[]){__VA_ARGS__}) / sizeof(int))

// TODO 4: Chuẩn hóa vector v về độ dài 1 (Unit vector)
// - v: Con trỏ trỏ tới Vector2D cần chuẩn hóa
// Chia cả x và y cho độ dài (length = sqrt(x^2 + y^2)) nếu length > 0
void normalize_vector(Vector2D *v) {
    if (v == NULL) return;
    float len = sqrtf(v->x * v->x + v->y * v->y);
    if (len > 0.0f) {
        v->x /= len;
        v->y /= len;
    }
}

int main(void) {
    printf("=== TEST 1: ANONYMOUS STRUCT & UNION (FLAT ACCESS) ===\n");
    Vector2D v1;
    v1.x = 3.0f;
    v1.y = 4.0f;
    printf("Truy cap qua .x, .y   : (%.1f, %.1f)\n", v1.x, v1.y);
    printf("Truy cap qua .raw[]   : (%.1f, %.1f)\n", v1.raw[0], v1.raw[1]);

    printf("\n=== TEST 2: COMPOUND LITERAL STRUCT (TRUYEN TRUC TIEP) ===\n");
    // Truyền trực tiếp 2 struct ẩn danh mà không cần khai báo biến tạm
    float dist = calc_distance((Vector2D){.x = 0.0f, .y = 0.0f},
                               (Vector2D){.x = 6.0f, .y = 8.0f});
    printf("Khoang cach giua (0,0) va (6,8): %.2f (Ky vong: 10.00)\n", dist);

    printf("\n=== TEST 3: COMPOUND LITERAL ARRAY & MACRO TU DEM ===\n");
    // Gọi hàm tính tổng không cần khai báo biến mảng trung gian
    printf("Tong {10, 20, 30, 40}  : %d (Ky vong: 100)\n", SUM_INT(10, 20, 30, 40));
    printf("Tong {1, 2, 3, 4, 5, 6}: %d (Ky vong: 21)\n", SUM_INT(1, 2, 3, 4, 5, 6));

    printf("\n=== TEST 4: CHINH SUA TREN COMPOUND LITERAL (LVALUE) ===\n");
    // Lấy địa chỉ và chuẩn hóa trực tiếp một anonymous struct
    Vector2D *ptr = &(Vector2D){.x = 3.0f, .y = 4.0f};
    normalize_vector(ptr);
    printf("Vector don vi sau khi chuan hoa: (%.2f, %.2f) (Ky vong: 0.60, 0.80)\n",
           ptr->x, ptr->y);

    return 0;
}
