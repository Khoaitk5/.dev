#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// TODO 1: Định nghĩa enum ShapeType làm nhãn phân biệt (SHAPE_CIRCLE, SHAPE_RECTANGLE, SHAPE_TRIANGLE)
typedef enum {
    SHAPE_CIRCLE,
    SHAPE_RECTANGLE,
    SHAPE_TRIANGLE
} ShapeType;

// Struct chứa thông số riêng của từng hình
typedef struct {
    double radius;
} Circle;

typedef struct {
    double width;
    double height;
} Rectangle;

typedef struct {
    double base;
    double height;
} Triangle;

// TODO 2: Định nghĩa Tagged Union Shape
// Cấu trúc gồm 2 trường:
// - type: Kiểu ShapeType (lưu nhãn xem đây là hình gì)
// - data: Một union chứa 1 trong 3 đối tượng: Circle circle, Rectangle rect, Triangle triangle
typedef struct {
    ShapeType type;
    union {
        Circle circle;
        Rectangle rect;
        Triangle triangle;
    } data;
} Shape;

// TODO 3: Cài đặt các hàm khởi tạo (Factory Functions)
// Mục đích: Đóng gói thông số thành 1 Shape hoàn chỉnh:
//   1. Gán trường `type` tương ứng với loại hình
//   2. Gán dữ liệu vào union `data` của loại hình đó

// Tạo Shape hình tròn với bán kính radius
Shape make_circle(double radius) {
    Shape s;
    s.type = SHAPE_CIRCLE;
    s.data.circle.radius = radius;
    return s;
}

// Tạo Shape hình chữ nhật với width và height
Shape make_rectangle(double width, double height) {
    Shape s;
    s.type = SHAPE_RECTANGLE;
    s.data.rect.width = width;
    s.data.rect.height = height;
    return s;
}

// Tạo Shape hình tam giác với base và height
Shape make_triangle(double base, double height) {
    Shape s;
    s.type = SHAPE_TRIANGLE;
    s.data.triangle.base = base;
    s.data.triangle.height = height;
    return s;
}

// TODO 4: Tính diện tích dựa vào s->type và s->data tương ứng
// - Circle: PI * r * r
// - Rectangle: width * height
// - Triangle: 0.5 * base * height
// Trả về: diện tích tính được, hoặc 0.0 nếu type không hợp lệ
double calculate_area(const Shape *s) {
    switch(s->type){
        case SHAPE_CIRCLE:
            return M_PI * s->data.circle.radius * s->data.circle.radius;
            break;
        case SHAPE_RECTANGLE:
            return s->data.rect.width * s->data.rect.height;
            break;
        case SHAPE_TRIANGLE:
            return 0.5 * s->data.triangle.base * s->data.triangle.height;
            break;
        default:
            break;
    }
    return 0.0;
}

// TODO 5: In thông tin hình dựa vào s->type và gọi calculate_area(s)
// Ví dụ: "Hinh tron: r = %.2f, dien tich = %.2f\n"
void print_shape(const Shape *s) {
    double radius = calculate_area(s);
    switch(s->type){
        case SHAPE_CIRCLE:
            printf ("dien tich hinh tron: %.2f\n", radius);
            break;
        case SHAPE_RECTANGLE:
            printf ("dien tich hinh tron: %.2f\n", radius);
            break;
        case SHAPE_TRIANGLE:
            printf ("dien tich hinh tron: %.2f\n", radius);
        default:
            break;
    }
}

int main() {
    Shape shapes[] = {
        make_circle(5.0),
        make_rectangle(4.0, 6.0),
        make_triangle(3.0, 4.0),
        make_circle(2.5)
    };
    int count = sizeof(shapes) / sizeof(shapes[0]);

    printf("Kich thuoc 1 Shape: %zu bytes\n\n", sizeof(Shape));

    double total_area = 0.0;
    for (int i = 0; i < count; i++) {
        print_shape(&shapes[i]);
        total_area += calculate_area(&shapes[i]);
    }

    printf("\n=> Tong dien tich: %.2f\n", total_area);
    return 0;
}
