#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// TODO 1: Định nghĩa struct Bit Fields nén thông tin Ngày / Tháng / Năm
// - day: 5 bit (giá trị 1 - 31)
// - month: 4 bit (giá trị 1 - 12)
// - year: 12 bit (giá trị 0 - 4095)
// Sử dụng kiểu unsigned int cho tất cả các trường
typedef struct {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 12;
} CompactDate;

// TODO 2: Định nghĩa union đóng gói thanh ghi điều khiển thiết bị (DeviceRegister)
// Kích thước mong muốn: đúng 1 byte (uint8_t)
// Gồm 2 thành phần:
//   - raw: Kiểu uint8_t để truy cập toàn bộ 8 bit cùng lúc
//   - bits: Struct bit field gồm:
//       + is_on      : 1 bit (0: Tắt, 1: Bật)
//       + mode       : 2 bit (Chế độ: 0: Low, 1: Medium, 2: High, 3: Turbo)
//       + has_error  : 1 bit (0: Bình thường, 1: Lỗi)
//       + reserved   : 4 bit (Dự phòng, không dùng)
typedef union {
    uint8_t raw; // Dùng để truy cập cả 8 bit cùng lúc
    struct {
        uint8_t is_on     : 1; // Bit 0
        uint8_t mode      : 2; // Bit 1-2
        uint8_t has_error : 1; // Bit 3
        uint8_t reserved  : 4; // Bit 4-7
    } bits;      // Tên struct này là `bits`
} DeviceRegister;

// TODO 3: Cài đặt hàm in thông tin ngày tháng
// Định dạng: "Ngay: %02u/%02u/%04u\n"
void print_date(const CompactDate *d) {
    printf("Ngay: %02u/%02u/%04u\n", d->day, d->month, d->year);
}

// TODO 4: Cài đặt hàm hiển thị trạng thái thiết bị từ DeviceRegister
// In ra: Nguon (ON/OFF), Mode (0-3), Error (YES/NO), va gia tri Hex cua raw
void print_device_status(DeviceRegister dev) {
    const char *nguon = dev.bits.is_on&1 ? "ON" : "OFF";
    const char *loi = dev.bits.has_error&1 ? "YES" : "NO";
    printf("raw 0x%02X | Nguon: %s | Mode: %d | Loi: %s\n", dev.raw, nguon, dev.bits.mode);
}

int main() {
    printf("=== TEST 1: COMPACT DATE (BIT FIELDS) ===\n");
    CompactDate today;
    printf("Kich thuoc struct CompactDate: %zu bytes\n", sizeof(CompactDate));

    today.day = 9;
    today.month = 11;
    today.year = 2026;
    print_date(&today);

    printf("\n=== TEST 2: DEVICE REGISTER (UNION + BIT FIELDS) ===\n");
    DeviceRegister dev;
    printf("Kich thuoc struct DeviceRegister: %zu byte\n", sizeof dev);
    dev.raw = 0x00; // Xóa sạch 8 bit về 0

    // Bật nguồn và đặt mode High (2)
    dev.bits.is_on = 1;
    dev.bits.mode = 2;
    dev.bits.has_error = 0;

    print_device_status(dev);

    printf("\n=== TEST 3: GHI TRUC TIEP QUA RAW (GIA LAP NHAN PACKET) ===\n");
    // Giả sử nhận được 1 byte từ phần cứng: 0b00001101 (raw = 0x0D)
    // Bit 0: is_on = 1
    // Bit 1-2: mode = 2 (0b10)
    // Bit 3: has_error = 1
    dev.raw = 0x0D;
    print_device_status(dev);

    return 0;
}