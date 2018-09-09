#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<string.h>

double pow_int (int a, int b)
{
    double ans = 1;
    if (b == 0)
        return 1;

    for (int i = 0; i < b; ++i)
        ans *= (double)a;

    for (int i = 0; i > b; --i)
        ans /= (double)a;

    return ans;
}

int main() {
    int b1, b2;
    scanf("%d %d\n", &b1, &b2);
    char X[13];
    scanf("%s", X);

    int len = 0;
    int power = 0;
    int flag_point = 1;

    while (X[len] != '\0') {
        if (X[len] == '.' && flag_point)
        {
            flag_point = 0;
            if (X[len + 1] == '\0' || len == 0)
            {
                printf("bad input\n");
                return 0;
            }
        }
        else if (X[len] == '.')
        {
            printf("bad input\n");
            return 0;
        }
        power += flag_point;
        ++len;
    }
    --power;

    double number = 0;

    for (int i = 0; i < len; ++i) {
        if (X[i] >= 'a' && X[i] <= 'z') {
            X[i] = toupper(X[i]);
            if (b1 <= 10 || X[i] > ('A' + b1 - 11)) {
                printf("bad input\n");
                return 0;
            }
        }
        if ((b1 <= 10 && isalpha(X[i])) || (isalpha(X[i]) && X[i] > ('A' + b1 - 11)) || (b1 <= 10 && X[i] - '0' >= b1) || (b1 < 2) || (b2 < 2) || (b1 > 16) || (b2 > 16))
        {
            printf("bad input\n");
            return 0;
        }

        if (isalpha(X[i])) {
            number += (double)((X[i] - 'A' + 10) * pow_int(b1, power));
        } else if (X[i] != '.') {
            number += (double)((double)(X[i] - '0') * pow_int(b1, power));
        }
        power -= X[i] != '.';
    }

    double fraction = modf(number, &number);
    long long whole = (long long)number;
    char whole_str[50];
    int i = 0;

    if (whole == 0)
        printf("0");

    while (whole != 0)
    {
        int digit = whole % b2;
        if (digit <= 9)
            whole_str[i] = '0' + digit;
        else
            whole_str[i] = 'A' + digit - 10;
        ++i;
        whole /= b2;
    }
    --i;

    while (i >= 0)
    {
        printf("%c", whole_str[i]);
        --i;
    }

    if (fraction > 0.0)
    {
        printf(".");
        for (int i = 0; i < 12; ++i)
        {
            double digit_double;
            fraction = (modf(fraction * b2, &digit_double));
            int digit = (int)digit_double;
            if (digit <= 9)
                printf("%d", digit);
            else
                printf("%c", 'A' + digit - 10);
        }
    }
    printf("\n");
    return 0;
}