// Bật chuẩn ANSI stdio trên MinGW/Windows để hỗ trợ đầy đủ %Lf, %b (C23) và %n
#if defined(__MINGW32__) && !defined(__USE_MINGW_ANSI_STDIO)
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <math.h>

// Công thức tổng quát của một đặc tả printf:
// %[flags][width][.precision][length]specifier

int main(void) {
    printf("--- 1. DAC TA SO NGUYEN (INTEGER SPECIFIERS) ---\n");
    int sig = -42;
    unsigned int unsig = 42U;
    printf("%%d (co dau)           : %d\n", sig);
    printf("%%i (giong %%d o printf): %i\n", sig);
    printf("%%u (khong dau)        : %u\n", unsig);
    printf("%%o (bat phan - Octal) : %o\n", unsig);
    printf("%%x (hex thuong)       : %x\n", 255U);
    printf("%%X (hex hoa)          : %X\n", 255U);
    printf("%%b (nhi phan - C23)   : %b\n", 10U);
    printf("%%B (nhi phan - C23)   : %B\n", 10U);

    printf("\n--- 2. DAC TA SO THUC (FLOATING-POINT SPECIFIERS) ---\n");
    double val = 123.456789;
    double inf_val = INFINITY;
    printf("%%f (thap phan chuan)  : %f\n", val);
    printf("%%F (INF/NAN chu hoa)  : %F\n", inf_val);
    printf("%%e (khoa hoc thuong)  : %e\n", val);
    printf("%%E (khoa hoc hoa)     : %E\n", val);
    printf("%%g (ngan gon tu dong) : %g | %g\n", 123.4500, 0.000012345);
    printf("%%G (ngan gon chu hoa) : %G\n", 0.000012345);
    printf("%%a (hex float thuong) : %a\n", 3.5);
    printf("%%A (hex float hoa)    : %A\n", 3.5);

    printf("\n--- 3. KY TU, CHUOI, CON TRO VA DAC BIET ---\n");
    char ch = 'A';
    const char *str = "Lap trinh C";
    int x = 100;
    int printed_count = 0;
    printf("%%c (ky tu)            : %c\n", ch);
    printf("%%s (chuoi)            : %s\n", str);
    printf("%%p (dia chi con tro)  : %p\n", (void *)&x);
    printf("%%%% (dau phan tram)    : 100%%\n");
    printf("%%n (dem so ky tu)     : Hello%n World -> ", &printed_count);
    printf("da in %d ky tu truoc '%%n'\n", printed_count);

    printf("\n--- 4. CO DINH DANG (FLAGS: -, +, space, #, 0) ---\n");
    printf("[%%8d]   mac dinh phai : [%8d]\n", 42);
    printf("[%%-8d]  can trai (-)  : [%-8d]\n", 42);
    printf("[%%+d]   hien dau (+)  : [%+d] | [%+d]\n", 42, -42);
    printf("[%% d]   cach so duong : [% d] | [% d]\n", 42, -42);
    printf("[%%05d]  dem so 0 (0)  : [%05d]\n", 42);
    printf("[%%#...] tien to (#)   : oct=%#o | hex=%#x | HEX=%#X | bin=%#b | float=%#.0f\n",
           42U, 42U, 42U, 10U, 5.0);

    printf("\n--- 5. DO RONG (WIDTH), DO CHINH XAC (.PRECISION) VA DONG (*) ---\n");
    printf("[%%.2f]   2 so le      : [%.2f]\n", 3.14159);
    printf("[%%.4g]   4 chu so nghia: [%.4g]\n", 123.456);
    printf("[%%.5d]   it nhat 5 so : [%.5d]\n", 42);
    printf("[%%.4s]   cat 4 ky tu  : [%.4s]\n", "Antigravity");
    printf("[%%*d]    width dong   : [%*d]\n", 8, 99);
    printf("[%%.*s]   cat chuoi dong: [%.*s]\n", 5, "Hello World");
    printf("[%%*.*f]  ca hai dong  : [%*.*f]\n", 10, 3, 3.1415926);

    printf("\n--- 6. BO NGU DO DAI (LENGTH MODIFIERS) VA INTTYPES ---\n");
    signed char sc = -120;
    unsigned char uc = 250;
    short sh = -30000;
    long lg = 1000000L;
    long long ll = 9000000000000LL;
    unsigned long long ull = 18000000000000000000ULL;
    size_t sz = sizeof(ull);
    int arr[5] = {10, 20, 30, 40, 50};
    ptrdiff_t diff = &arr[4] - &arr[1];
    intmax_t imax = INTMAX_MAX;
    long double ld = 3.141592653589793238L;
    uint64_t u64 = 0x123456789ABCDEF0ULL;

    printf("hh (char 8-bit)       : %hhd | %hhu\n", sc, uc);
    printf("h  (short 16-bit)     : %hd\n", sh);
    printf("l  (long)             : %ld\n", lg);
    printf("ll (long long 64-bit) : %lld | %llu\n", ll, ull);
    printf("z  (size_t)           : %zu bytes\n", sz);
    printf("t  (ptrdiff_t)        : %td phan tu\n", diff);
    printf("j  (intmax_t)         : %jd\n", imax);
    printf("L  (long double)      : %.15Lf\n", ld);
    printf("<inttypes.h>          : %" PRIu64 " (0x%" PRIX64 ")\n", u64, u64);

    return 0;
}

