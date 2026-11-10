#include <stdio.h>

// 1. Định nghĩa enum mã lỗi
typedef enum {
    ERR_OK = 0,
    ERR_TIMEOUT,
    ERR_INVALID_PARAM,
    ERR_OUT_OF_MEMORY,
    ERR_DEVICE_BUSY,
    ERR_MAX // Phần tử cuối dùng làm kích thước của bảng
} ErrorCode;

// TODO 1: Khởi tạo bảng tra cứu chuỗi mô tả lỗi
// Gợi ý: Dùng cú pháp [ERR_OK] = "...", ...
static const char* error_lut[ERR_MAX] = {
    [ERR_OK] = "Thao tac thanh cong",
    // TODO: Điền tiếp chuỗi mô tả cho:
    // - ERR_TIMEOUT
    [ERR_TIMEOUT] = "Vuot qua thoi gian xu ly",
    // - ERR_INVALID_PARAM
    [ERR_INVALID_PARAM] = "Tham so khong hop le",
    // - ERR_OUT_OF_MEMORY
    [ERR_OUT_OF_MEMORY] = "Het bo nho",
    // - ERR_DEVICE_BUSY
    [ERR_DEVICE_BUSY] = "Thiet bi dang ban"

};

// TODO 2: Viết hàm lấy chuỗi mô tả lỗi
// - err: Mã lỗi cần tra cứu
// Trả về: Chuỗi mô tả tương ứng, hoặc "Loi khong xac dinh" nếu err không hợp lệ
const char* get_error_message(ErrorCode err) {
    // TODO: Kiểm tra err có nằm trong khoảng hợp lệ (>= 0 và < ERR_MAX) không
    // Nếu hợp lệ: trả về chuỗi tương ứng trong error_lut
    // Nếu không hợp lệ: trả về "Loi khong xac dinh"
    // printf("%s\n", error_lut[err]);
    // if(err >= 0 && err < ERR_MAX) return error_lut[err];
    if((unsigned int)err < ERR_MAX) return error_lut[err]; // giới hạn là -2.147.483.648 cho err
    return "Loi khong xac dinh";
}

int main() {
    printf("=== TEST: TRA CUU MA LOI ===\n");

    ErrorCode tests[] = {
        ERR_OK,
        ERR_TIMEOUT,
        ERR_INVALID_PARAM,
        ERR_OUT_OF_MEMORY,
        ERR_DEVICE_BUSY,
        (ErrorCode)99 // Test lỗi không hợp lệ
    };
    int n = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n; i++) {
        printf("Ma loi %2d: %s\n", tests[i], get_error_message(tests[i]));
    }

    return 0;
}