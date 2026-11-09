#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// TODO 1: Khai báo 4 biến hằng số biểu diễn cùng một giá trị 42 ở các hệ cơ số khác nhau
// - val_dec: Hệ thập phân (Decimal)
// - val_hex: Hệ thập lục phân (Hexadecimal, tiền tố 0x)
// - val_oct: Hệ bát phân (Octal, tiền tố 0)
// - val_bin: Hệ nhị phân (Binary, tiền tố 0b)
// Trả về: true nếu cả 4 giá trị trên bằng nhau, ngược lại false
bool verify_same_number(void) {
    // TODO: Khai báo 4 biến theo đúng cú pháp literal và so sánh
    int val_dec = 42;
    int val_hex = 0x2A;
    int val_oct = 052;
    int val_bin = 0b00101010;
    return (val_dec == val_hex && val_hex == val_oct && val_oct == val_bin);
}

// TODO 2: Tính tổng số microgiây (microseconds) từ số ngày (days)
// - days: Số ngày cần quy đổi (uint32_t)
// Lưu ý: 1 ngày = 24 * 60 * 60 * 1,000,000 microgiây.
// Cần sử dụng đúng hậu tố literal để tránh bị tràn số nguyên 32-bit trong quá trình tính toán.
// Trả về: Kết quả tính theo kiểu uint64_t
uint64_t days_to_microseconds(uint32_t days) {
    // TODO: Viết biểu thức nhân an toàn với hậu tố ULL
    return (uint64_t)days * 24ULL * 60ULL * 60ULL * 1'000'000ULL;
}

// TODO 3: Tạo mặt nạ bit (bitmask) với bit thứ 'pos' được bật lên 1 (kiểu 64-bit)
// - pos: Vị trí bit cần bật (0 đến 63)
// Lưu ý: Tránh lỗi Undefined Behavior khi pos >= 32 do số 1 mặc định mang kiểu 32-bit int.
// Trả về: Giá trị uint64_t với duy nhất bit tại pos mang giá trị 1
uint64_t create_bitmask_64(int pos) {
    // TODO: Dịch bit an toàn với hậu tố ULL
    return 1ULL << pos;
}

// TODO 4: Chuyển đổi nhiệt độ từ độ Celsius (°C) sang Fahrenheit (°F)
// - celsius: Nhiệt độ theo thang đo Celsius (float)
// Công thức: F = C * (9 / 5) + 32
// Lưu ý: Sử dụng đúng float literal để tránh phép chia số nguyên (9 / 5 = 1)
//        và tránh bị ép kiểu ngầm định lên double (dùng hậu tố f).
// Trả về: Nhiệt độ theo thang Fahrenheit kiểu float
float celsius_to_fahrenheit(float celsius) {
    // TODO: Viết biểu thức chuyển đổi với float literal
    return celsius * (9.0f / 5.0f) + 32.0f;
}

int main() {
    printf("=== TEST 1: HE CO SO VA KICH THUOC LITERAL ===\n");
    printf("4 gia tri co bang nhau khong: %s\n", 
           verify_same_number() ? "Dung (deu la 42)" : "Sai");
    printf("sizeof(42)   : %zu bytes (int)\n", sizeof(42));
    printf("sizeof(42LL) : %zu bytes (long long)\n", sizeof(42LL));
    printf("sizeof(3.14) : %zu bytes (double)\n", sizeof(3.14));
    printf("sizeof(3.14f): %zu bytes (float)\n", sizeof(3.14f));

    printf("\n=== TEST 2: TRAN SO KHI NHAN HANG SO ===\n");
    uint32_t days = 100;
    printf("%u ngay doi sang microgiay: %llu us\n", days, (unsigned long long)days_to_microseconds(days));

    printf("\n=== TEST 3: DICH BIT AN TOAN 64-BIT ===\n");
    int bit_pos = 40;
    printf("Bitmask tai vi tri bit %d: 0x%016llX\n", bit_pos, (unsigned long long)create_bitmask_64(bit_pos));

    printf("\n=== TEST 4: HANG SO THUC FLOAT VA DOUBLE ===\n");
    float c1 = 25.0f;
    float c2 = 100.0f;
    printf("%.1f do C sang do F: %.2f F\n", c1, celsius_to_fahrenheit(c1));
    printf("%.1f do C sang do F: %.2f F\n", c2, celsius_to_fahrenheit(c2));

    return 0;
}

