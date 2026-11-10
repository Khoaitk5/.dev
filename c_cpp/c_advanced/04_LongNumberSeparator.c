#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// Digit Separator (Dấu phân cách chữ số ')
// - Chuẩn hỗ trợ: C23 (ISO/IEC 9899:2024) và C++14 trở lên (lỗi ở C17 trở về trước).
// - Bản chất: Ở giai đoạn phân tích từ vựng (Lexical Analysis), trình biên dịch xóa
//   hoàn toàn mọi dấu ', không làm thay đổi giá trị, kiểu dữ liệu hay hiệu năng.
// - Quy tắc vàng: Dấu ' CHỈ được đứng giữa hai chữ số hợp lệ của hệ cơ số đó.
//
// Các trường hợp SAI CÚ PHÁP (không được viết):
//   '1000      (đứng đầu số)
//   1000'      (đứng cuối số)
//   1000'ULL   (đứng ngay trước hậu tố kiểu)
//   1''000     (hai dấu ' đứng liền kề)
//   0x'FF      (đứng ngay sau tiền tố 0x hoặc 0b)
//   3'.14      (đứng ngay trước hoặc ngay sau dấu chấm thập phân)
//   1'e6       (đứng cạnh ký hiệu mũ e/E hoặc p/P)

int main(void) {
    printf("--- 1. CHUNG MINH BAN CHAT BIEN DICH ---\n");
    int with_sep = 1'000'000;
    int without_sep = 1000000;
    printf("Gia tri giong nhau? : %s (%d)\n",
           (with_sep == without_sep) ? "Dung" : "Sai", with_sep);
    printf("Kich thuoc bang nhau?: sizeof(1'000'000ULL) = %zu, sizeof(1000000ULL) = %zu\n",
           sizeof(1'000'000ULL), sizeof(1000000ULL));

    printf("\n--- 2. AP DUNG TREN CAC HE CO SO NGUYEN ---\n");
    // Thập phân: có thể chia nhóm 3 số hoặc bất kỳ (vd: 4 số) để dễ đọc
    uint64_t ns_per_day = 86'400'000'000'000ULL;
    int wan_style = 1'0000'0000;

    // Thập lục phân: tách theo từng byte hoặc word (16-bit)
    uint32_t color_rgba = 0xFF'80'00'FF;
    uint32_t magic_word = 0xDEAD'BEEF;

    // Nhị phân: tách từng nibble (4-bit) rất trực quan khi viết bitmask thanh ghi
    uint16_t reg_mask = 0b1111'0000'1010'0101;

    // Bát phân: hợp lệ vì 0 vừa là tiền tố vừa là một chữ số bát phân
    int file_perm = 0'755;

    printf("Thap phan (64-bit)  : %" PRIu64 " | nhom 4 so: %d\n", ns_per_day, wan_style);
    printf("Thap luc phan (Hex) : 0x%08X | 0x%08X\n", color_rgba, magic_word);
    printf("Nhi phan (Binary)   : %u (0x%04X)\n", reg_mask, reg_mask);
    printf("Bat phan (Octal)    : 0%o\n", file_perm);

    printf("\n--- 3. AP DUNG TREN SO THUC (FLOATING-POINT) ---\n");
    double pi = 3.141'592'653'589;
    float flt_sep = 12'345.5f;
    double exp_sep = 2.5e1'0;
    double hex_flt = 0x1.800'000p1;

    printf("So thuc chuan       : %.12f\n", pi);
    printf("Float + hau to f    : %.1f\n", flt_sep);
    printf("Ky hieu khoa hoc    : %.2e\n", exp_sep);
    printf("Hex float           : %.2f\n", hex_flt);

    return 0;
}
