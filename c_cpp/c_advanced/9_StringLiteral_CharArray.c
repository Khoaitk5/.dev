#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// TODO 1: Viết hàm kiểm tra xem 2 chuỗi có cùng trỏ tới 1 địa chỉ bộ nhớ hay không
// - s1, s2: Hai con trỏ chuỗi cần so sánh địa chỉ
// Trả về: true nếu s1 và s2 cùng địa chỉ (String Pooling trong .rodata), ngược lại false
bool is_same_address(const char *s1, const char *s2) {
    return s1==s2;
}

// TODO 2: Viết hàm viết hoa ký tự đầu tiên của chuỗi
// - str: Mảng ký tự có thể chỉnh sửa (Modifiable Char Array)
// Lưu ý: Nếu truyền String Literal vào hàm này sẽ gây lỗi Crash chương trình
void capitalize(char *str) {
    if (str != NULL && str[0] >= 'a' && str[0] <= 'z') {
        str[0] -= 32; // hoặc: str[0] = toupper((unsigned char)str[0]);
    }
}

// TODO 3: Viết hàm sao chép chuỗi an toàn từ nguồn vào bộ đệm đích
// - dest: Mảng ký tự đích nằm trên Stack
// - dest_size: Kích thước tối đa của mảng dest
// - src: Chuỗi nguồn (thường là String Literal)
void safe_copy(char *dest, size_t dest_size, const char *src) {
    if (dest && dest_size > 0) {
        // snprintf ghi tối đa (dest_size - 1) ký tự từ src vào dest và luôn
        // tự động thêm ký tự '\0' ở cuối, giúp chống tràn bộ nhớ (buffer overflow)
        snprintf(dest, dest_size, "%s", src);
    }
}

// TODO 4: Viết hàm trả về chuỗi mô tả trạng thái dựa theo status_code
// - code: 0 -> "Hoạt động", 1 -> "Tạm dừng", còn lại -> "Lỗi"
// Trả về: Con trỏ tới String Literal (vùng nhớ .rodata, an toàn khi return)
const char* get_status_name(int code) {
    switch(code) {
        case 0: return "Hoat dong";
        case 1: return "Tam dung";
        default: return "Loi";
    }
}

int main() {
    printf("=== TEST 1: VUNG NHO VA STRING POOLING ===\n");
    const char *lit1 = "Lap trinh C";
    const char *lit2 = "Lap trinh C";
    char arr1[] = "Lap trinh C";
    char arr2[] = "Lap trinh C";

    printf("lit1 va lit2 cung dia chi? %s\n", 
           is_same_address(lit1, lit2) ? "Dung (String Pooling)" : "Sai");
    printf("arr1 va arr2 cung dia chi? %s\n", 
           is_same_address(arr1, arr2) ? "Dung" : "Sai (Mang nam rieng tren Stack)");

    printf("\n=== TEST 2: KICH THUOC SIZEOF ===\n");
    printf("sizeof(lit1)  - Kich thuoc con tro: %zu bytes\n", sizeof(lit1));
    printf("sizeof(arr1)  - Kich thuoc mang (co \\0): %zu bytes\n", sizeof(arr1));

    printf("\n=== TEST 3: THAY DOI NOI DUNG CHUOI ===\n");
    // Chi co Char Array moi duoc phep thay doi noi dung:
    char greeting[] = "hello world";
    capitalize(greeting);
    printf("Chuoi sau khi viet hoa: %s\n", greeting);

    printf("\n=== TEST 4: SAO CHEP VA TRA VE CHUOI AN TOAN ===\n");
    char buffer[20];
    safe_copy(buffer, sizeof(buffer), "Embedded C");
    printf("Buffer sau khi copy: %s\n", buffer);

    printf("Trang thai 0: %s\n", get_status_name(0));
    printf("Trang thai 1: %s\n", get_status_name(1));
    printf("Trang thai 9: %s\n", get_status_name(9));

    return 0;
}