#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    STATUS_POISONED = 1 << 0, // 0b00000001
    STATUS_BURNING  = 1 << 1, // 0b00000010
    STATUS_FROZEN   = 1 << 2, // 0b00000100
    STATUS_STUNNED  = 1 << 3, // 0b00001000
    STATUS_SHIELDED = 1 << 4  // 0b00010000
} StatusEffect;

// TODO: Cài đặt các hàm dưới đây
void add_status(uint8_t *flags, uint8_t status) {
    *flags |= status;
}

void remove_status(uint8_t *flags, uint8_t status) {
    *flags &= ~status;
}

void toggle_status(uint8_t *flags, uint8_t status) {
    *flags ^= status;
}

bool has_status(uint8_t flags, uint8_t status) {
    return flags&status;
}

void print_all_statuses(uint8_t flags) {
    printf("Trang thai hien tai (0x%02X):\n", flags);
    if (flags == 0) {
        printf("  - Binh thuong (Khong co hieu ung)\n");
        return;
    }
    if (flags & STATUS_POISONED) printf("%s\n", "POISONED");
    if (flags & STATUS_BURNING) printf("%s\n", "BURNING");
    if (flags & STATUS_FROZEN) printf("%s\n", "FROZEN");
    if (flags & STATUS_STUNNED) printf("%s\n", "STUNNED");
    if (flags & STATUS_SHIELDED) printf("%s\n", "SHIELDED");
}

int main() {
    uint8_t hero_status = 0; // Ban đầu không có hiệu ứng gì

    printf("=== 1. Nhan vat dinh doc va bi chay ===\n");
    add_status(&hero_status, STATUS_POISONED | STATUS_BURNING);
    print_all_statuses(hero_status);

    printf("\n=== 2. Kiem tra xem co bi choang khong? ===\n");
    if (has_status(hero_status, STATUS_STUNNED)) {
        printf("Nhan vat dang bi choang!\n");
    } else {
        printf("Nhan vat KHONG bi choang.\n");
    }

    printf("\n=== 3. Uong thuoc giai doc (Xoa STATUS_POISONED) ===\n");
    remove_status(&hero_status, STATUS_POISONED);
    print_all_statuses(hero_status);

    printf("\n=== 4. Bat/Tat khien chan (Toggle SHIELDED) ===\n");
    toggle_status(&hero_status, STATUS_SHIELDED);
    print_all_statuses(hero_status);

    printf("\n=== 5. Tat tiep khien chan (Toggle SHIELDED lan 2) ===\n");
    toggle_status(&hero_status, STATUS_SHIELDED);
    print_all_statuses(hero_status);

    return 0;
}