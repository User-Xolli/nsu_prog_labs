#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#define MAX_LEN_NUMBER 15

double pow_int (int a, int b);

double pow_int(int a, int b)
{
    double ans = 1;

    if (b == 0) return 1;
    if (a == 0) return 0;

    for (int i = 0; i < b; ++i) ans *= (double)a;

    for (int i = 0; i > b; --i) ans /= (double)a;

    return ans;
}

int power_number (char *X, int len);

int power_number(char *X, int len)
{
    int ans = 0;
    int is_integer_part = 1;

    for (int i = 0; i < len; ++i)
    {
        if (X[i] == '.' && is_integer_part)
        {
            is_integer_part = 0;
            if (X[i + 1] == '\0' || i == 0) return -1;
        }
        else if (X[i] == '.') return -1;

        ans += is_integer_part;
    }
    return ans - 1;
}

int bad_digit(char x, int base);

int bad_digit(char x, int base)
{
    return (base <= 10 && isalpha(x)) || //Если осн. СС <= 10 и в записи числа есть буква то bad input
        (isalpha(x) && x > ('A' + base - 11)) || //(base - 11) - сдвиг максимально возможной буквы в СС с осн. base относительно 'A'
        (base <= 10 && x - '0' >= base); // (x - '0') перевод цифры x из строки в число
}

void print_whole(long long x, int base);

void print_whole(long long x, int base)
{
    int i = 0;
    char x_str[50]; // макс длина числа меньше 50 т.к. при переводе числа с 12 цифрами и точкой из СС с осн. 16
                    // в СС с осн. 2 получим число длиной 12 * 4 + 1 = 49

    if (x == 0) printf("0");

    while (x != 0)
    {
        int digit = (int)(x % base);

        if (digit <= 9) x_str[i] = (char)('0' + digit);

        else x_str[i] = (char)('A' + digit - 10);

        ++i;
        x /= base;
    }
    --i;

    for (; i >= 0; --i) printf("%c", x_str[i]);
}

void print_fraction(double x, int base);

void print_fraction(double x, int base)
{
    if (x > 0.0)
    {
        printf(".");
        for (int i = 0; i < 12; ++i)
        {
            double digit_double;
            x = (modf(x * base, &digit_double));

            int digit = (int)digit_double;

            if (digit <= 9) printf("%d", digit);

            else printf("%c", 'A' + digit - 10); // ('A' + digit - 10) символ цифры digit, если digit > 9
        }
    }
}

int main()
{
    int b1, b2;
    scanf("%d %d\n", &b1, &b2);
    char X[MAX_LEN_NUMBER];
    scanf("%14s", X);

    int len = (int)strlen(X);
    int power = power_number(X, len);

    if (power == -1 ||
        b1 < 2 ||
        b2 < 2 ||
        b1 > 16 ||
        b2 > 16)
    {
        printf("bad input\n");
        return 0;
    }

    double number = 0;

    for (int i = 0; i < len; ++i)
    {
        X[i] = (char)(toupper(X[i]));

        if (bad_digit(X[i], b1))
        {
            printf("bad input\n");
            return 0;
        }

        if (isalpha(X[i])) number += ((X[i] - 'A' + 10) * pow_int(b1, power)); // (X[i] - 'A' + 10) -
                                                                               // перевод цифры X[i] из строки в число в случае если X[i] это буква

        else if (X[i] != '.') number += ((X[i] - '0') * pow_int(b1, power)); // (X[i] - '0') - перевод цифры X[i] из строки в число

        power -= (X[i] != '.');
    }

    double fraction = modf(number, &number);
    long long whole = (long long)number;

    print_whole (whole, b2);
    print_fraction (fraction, b2);

    printf("\n");
    return 0;
}
