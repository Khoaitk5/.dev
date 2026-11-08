#include <stdio.h>
#include <string.h>

// 1. Định nghĩa con trỏ hàm so sánh
// Trả về 0 nếu 2 phần tử bằng nhau
typedef int (*CompareFunc)(const void *a, const void *b);

// 2. Struct dữ liệu mẫu để thử nghiệm
typedef struct {
    int id;
    char name[30];
    float score;
} Student;

// TODO 1: Cài đặt hàm tìm kiếm tổng quát
// - arr: Con trỏ trỏ đến đầu mảng
// - n: Số lượng phần tử trong mảng
// - elem_size: Kích thước của 1 phần tử (ví dụ: sizeof(int), sizeof(Student))
// - target: Con trỏ trỏ tới giá trị cần tìm
// - cmp: Hàm so sánh
// Trả về: con trỏ void* trỏ tới phần tử tìm thấy trong mảng, hoặc NULL nếu không thấy
void* generic_search(const void *arr, int n, size_t elem_size, const void *target, CompareFunc cmp) {

    for (int i = 0; i < n; i++) {
        // Gợi ý: Tính địa chỉ phần tử thứ i:
        // const void *current = (const char*)arr + i * elem_size;
        const void *current = (const char*)arr + i*elem_size;
        
        // TODO: Gọi hàm cmp để so sánh current với target
        // Nếu cmp trả về 0 -> tìm thấy! return con trỏ tới phần tử đó
        if(cmp(current, target) == 0) return (void*)current;
    }
    return NULL; // Không tìm thấy
}

// TODO 2: Viết hàm so sánh cho kiểu int
int cmp_int(const void *a, const void *b) {
    // Ép kiểu a và b về (const int*) rồi so sánh giá trị
    // Trả về 0 nếu bằng nhau, khác 0 nếu khác nhau
    // if(*(int*)a == *(int*)b) return 0;
    // return -1;
    return (*(int*)a)^(*(int*)b);
}

// TODO 3: Viết hàm so sánh Student theo ID
int cmp_student_by_id(const void *a, const void *b) {
    // Ép kiểu a và b về (const Student*)
    // So sánh id của 2 sinh viên
    const Student * std1 = (const Student*)a;
    const Student * std2 = (const Student*)b;
    return (std1->id)^(std2->id);
    // return ((const Student*)a)->id - ((const Student*)b)->id;
}

int main() {
    printf("=== TEST 1: TIM KIEM TRONG MANG INT ===\n");
    int numbers[] = { 10, 25, 40, 55, 70, 95 };
    int n_num = sizeof(numbers) / sizeof(numbers[0]);

    int key1 = 55;
    // Tìm kiếm số 55
    int *res1 = (int*)generic_search(numbers, n_num, sizeof(int), &key1, cmp_int);
    if (res1 != NULL) {
        printf("Tim thay: %d tai dia chi %p\n", *res1, (void*)res1);
    } else {
        printf("Khong tim thay %d\n", key1);
    }

    printf("\n=== TEST 2: TIM KIEM SINH VIEN THEO ID ===\n");
    Student students[] = {
        { 101, "Nguyen Van A", 8.5 },
        { 102, "Tran Thi B",   9.0 },
        { 103, "Le Van C",     7.2 }
    };
    int n_stu = sizeof(students) / sizeof(students[0]);

    Student key2;
    key2.id = 102; // Muốn tìm sinh viên có ID = 102

    Student *res2 = (Student*)generic_search(students, n_stu, sizeof(Student), &key2, cmp_student_by_id);
    if (res2 != NULL) {
        printf("Tim thay: ID=%d | Ten=%s | Diem=%.1f\n", res2->id, res2->name, res2->score);
    } else {
        printf("Khong tim thay sinh vien co ID = %d\n", key2.id);
    }

    return 0;
}