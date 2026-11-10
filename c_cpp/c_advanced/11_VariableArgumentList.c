#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// TODO 1: Tính trung bình cộng của 'count' số thực truyền vào
// - count: Số lượng phần tử cần tính (int)
// - ...: Danh sách các số thực (lưu ý quy tắc thăng hạng kiểu khi truyền vào ...)
// Trả về: Giá trị trung bình kiểu double (trả về 0.0 nếu count <= 0)
double calc_average(int count, ...) {
    if(count <= 0) return 0.0;

    va_list ap;
    va_start(ap, count);
    
    double sum = 0;
    for(int i = 0; i < count; i++){
        sum += va_arg(ap, double);
    }

    va_end(ap);
    return sum/count;
}

// TODO 2: Tính tổng độ dài các chuỗi truyền vào cho đến khi gặp lính canh NULL
// - first: Chuỗi đầu tiên (đóng vai trò mốc neo cho va_start)
// - ...: Các chuỗi tiếp theo kiểu const char*, kết thúc danh sách bằng NULL
// Trả về: Tổng độ dài của tất cả chuỗi cộng lại (trả về 0 nếu first là NULL)
size_t total_length(const char *first, ...) {
    if(first == NULL) return 0;

    va_list ap;
    va_start(ap, first);
    
    size_t len = 0;
    const char *s = first;
    while (s != NULL) {
        len += strlen(s);
        s = va_arg(ap, const char *);
    }

    va_end(ap);
    return len;
}

// TODO 3: Viết hàm in log đơn giản hỗ trợ chuỗi định dạng giống printf
// - fmt: Chuỗi định dạng hỗ trợ các đặc tả %d, %f, %c, %s; ký tự thường in nguyên vẹn
// - ...: Danh sách các đối số tương ứng theo thứ tự trong chuỗi fmt
void mini_log(const char *fmt, ...) {
    if (fmt == NULL) return;
    
    va_list ap;
    va_start(ap, fmt);

    for (int i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%' && fmt[i + 1] != '\0') {
            i++; // Tiến sang ký tự đặc tả (d, f, c, s)
            switch (fmt[i]) {
                case 'd':
                    printf("%d", va_arg(ap, int));
                    break;
                case 'f':
                    printf("%f", va_arg(ap, double));
                    break;
                case 'c':
                    printf("%c", va_arg(ap, int));
                    break;
                case 's':
                    printf("%s", va_arg(ap, const char *));
                    break;
                default:
                    putchar('%');
                    putchar(fmt[i]);
                    break;
            }
        } else {
            putchar(fmt[i]);
        }
    }
    va_end(ap);
}
// TODO 4: Đếm số lượng phần tử lớn hơn giá trị trung bình của chính dãy số đó
// - count: Số lượng số nguyên truyền vào (int)
// - ...: Danh sách 'count' số nguyên kiểu int
// Lưu ý: Cần duyệt qua danh sách 2 lượt (sử dụng va_copy để sao lưu trước khi duyệt lượt 1)
// Trả về: Số lượng phần tử lớn hơn giá trị trung bình (trả về 0 nếu count <= 0)
int count_above_average(int count, ...) {
    if(count <= 0) return 0;

    va_list ap;
    va_list apc;
    
    va_start(ap, count);
    va_copy(apc, ap);

    int sum = 0;
    for(int i = 0; i < count; i++){
        sum += va_arg(ap, int);
    }

    double avg = (double)sum/count;
    int rs = 0;
    for(int i = 0; i < count; i++){
        if(va_arg(apc, int) > avg) rs++;
    }

    va_end(ap);

    return rs;
}

int main() {
    printf("=== TEST 1: TRUNG BINH CONG (DEFAULT PROMOTION) ===\n");
    float f1 = 2.5f, f2 = 3.5f;
    printf("Trung binh (2.5f, 3.5f, 6.0): %.2f\n", calc_average(3, f1, f2, 6.0));
    printf("Trung binh rong (count = 0): %.2f\n", calc_average(0));

    printf("\n=== TEST 2: TONG DO DAI CHUOI (SENTINEL NULL) ===\n");
    printf("Tong do dai (\"Hello\", \" \", \"C!\"): %zu\n",
           total_length("Hello", " ", "C!", NULL));
    printf("Danh sach rong (NULL): %zu\n", total_length(NULL));

    printf("\n=== TEST 3: MINI LOG (FORMAT STRING) ===\n");
    char grade = 'A';
    float score = 9.5f;
    mini_log("Hoc vien: %s | Tuoi: %d | Diem: %f | Xep loai: %c\n",
             "Minh", 20, score, grade);

    printf("\n=== TEST 4: DEM SO LON HON TRUNG BINH (VA_COPY) ===\n");
    printf("So luong > TB trong {10, 20, 30, 40, 50}: %d\n",
           count_above_average(5, 10, 20, 30, 40, 50));
    printf("So luong > TB trong {2, 2, 2, 10}: %d\n",
           count_above_average(4, 2, 2, 2, 10));

    return 0;
}