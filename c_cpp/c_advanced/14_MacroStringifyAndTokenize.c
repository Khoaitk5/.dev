#include <stdio.h>
#include <stddef.h>

void action_start(void) {
    printf("He thong dang KHOI DONG...\n");
}

void action_stop(void) {
    printf("He thong dang DUNG LAI...\n");
}

// TODO 1: Viết macro PRINT_VAR(var, fmt) dùng toán tử # (Stringify) để in tên biến và giá trị
// - var: Biến cần in (tên biến được chuyển thành chuỗi)
// - fmt: Chuỗi định dạng của printf (vd: "%d", "%.1f", "%s")
// Kết quả in theo mẫu: "<tên_biến> = <giá_trị>\n"
#define PRINT_VAR(var, fmt) printf("%s = " fmt "\n", #var, var)

// TODO 2: Viết macro RUN_ACTION(name) dùng toán tử ## (Token Pasting) để gọi hàm theo tên
// - name: Phần hậu tố tên hành động (vd: start, stop)
// Tác dụng: Ghép với tiền tố "action_" để gọi hàm tương ứng (action_start hoặc action_stop)
#define RUN_ACTION(name) action_##name()

// TODO 3: Viết macro DEFINE_MAX_FUNC(type) sinh hàm generic tìm giá trị lớn hơn
// - type: Kiểu dữ liệu (vd: int, double)
// Tác dụng: Tự động sinh định nghĩa hàm max_<type>(type a, type b) trả về số lớn hơn
#define DEFINE_MAX_FUNC(type)       \
    type max_##type(type a, type b){ \
        return a > b ? a : b;       \
    }   

// TODO 4: Viết macro DEFINE_PRINT_ARRAY(type, fmt) kết hợp # và ## để sinh hàm in mảng generic
// - type: Kiểu dữ liệu phần tử (vd: int, float)
// - fmt: Chuỗi định dạng in 1 phần tử (vd: "%d", "%.1f")
// Tác dụng: Sinh hàm print_array_<type>(const type *arr, size_t size),
//           in nhãn kiểu dữ liệu bằng # rồi duyệt in các phần tử cách nhau 1 khoảng trắng
#define DEFINE_PRINT_ARRAY(type, fmt)                       \
    void print_array_##type(const type *arr, size_t size) { \
        if (arr == NULL) return;                            \
        printf("Mang [" #type "]: ");                       \
        for (size_t i = 0; i < size; i++) {                 \
            printf(fmt " ", arr[i]);                        \
        }                                                   \
        printf("\n");                                       \
    }

// Kích hoạt sinh các hàm generic từ macro đã viết ở TODO 3 và TODO 4:
DEFINE_MAX_FUNC(int)
DEFINE_MAX_FUNC(double)

DEFINE_PRINT_ARRAY(int, "%d")
DEFINE_PRINT_ARRAY(float, "%.1f")

int main(void) {
    printf("=== TEST 1: STRINGIFY (#) - IN DEBUG BIEN ===\n");
    int age = 21;
    float score = 9.5f;
    const char *role = "Embedded";
    PRINT_VAR(age, "%d");
    PRINT_VAR(score, "%.1f");
    PRINT_VAR(role, "%s");

    printf("\n=== TEST 2: TOKEN PASTING (##) - GHEP TEN HAM ===\n");
    RUN_ACTION(start);
    RUN_ACTION(stop);

    printf("\n=== TEST 3: GENERIC MAX FUNCTION (##) ===\n");
    printf("max_int(15, 42)        = %d\n", max_int(15, 42));
    printf("max_double(3.14, 2.71) = %.2f\n", max_double(3.14, 2.71));

    printf("\n=== TEST 4: GENERIC PRINT ARRAY (# VA ##) ===\n");
    int nums[] = {10, 20, 30, 40};
    float temps[] = {36.5f, 37.2f, 38.0f};
    print_array_int(nums, sizeof(nums) / sizeof(nums[0]));
    print_array_float(temps, sizeof(temps) / sizeof(temps[0]));

    return 0;
}

