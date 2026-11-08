#include <stdio.h>
#include <stdbool.h>

// TODO 1: Định nghĩa typedef cho con trỏ hàm so sánh CompareFunc
typedef bool (*CompareFunc)(int, int);

void print_array(int *arr, int size, const char *msg) {
    printf("%s: [ ", msg);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// TODO 2: Cài đặt hàm sắp xếp linh hoạt nhận con trỏ hàm
void flexible_sort(int *arr, int size, CompareFunc cmp) {
    for(int i = 0; i < size-1; i++){
        for(int j = 0; j < size-1; j++){
            if(cmp(arr[j], arr[j+1])){
                arr[j] = arr[j] ^ arr[j+1];
                arr[j+1] = arr[j] ^ arr[j+1];
                arr[j] = arr[j] ^ arr[j+1];
            }
        }
    }
}

// TODO 3: Viết hàm so sánh tăng dần
bool sort_ascending(int a, int b) {
    return a > b;
}

// TODO 4: Viết hàm so sánh giảm dần
bool sort_descending(int a, int b) {
    return a < b;
}

// TODO 5: Viết hàm ưu tiên số chẵn đứng trước số lẻ
bool sort_even_first(int a, int b) {
    if((a^b)&1) return a&1;
    return a > b;
}

int main() {
    int arr1[] = { 7, 2, 9, 4, 1, 6, 8, 3 };
    int size = sizeof(arr1) / sizeof(arr1[0]);

    print_array(arr1, size, "Mang ban dau");

    flexible_sort(arr1, size, sort_ascending);
    print_array(arr1, size, "Sap xep tang dan");

    flexible_sort(arr1, size, sort_descending);
    print_array(arr1, size, "Sap xep giam dan");

    flexible_sort(arr1, size, sort_even_first);
    print_array(arr1, size, "Chan truoc, le sau");

    return 0;
}