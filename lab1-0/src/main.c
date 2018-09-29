#include <stdio.h>
#include<string.h>

int main()
{
    char pattern[16];
    scanf("%16s", pattern);
    int len = strlen(pattern);
    int d [256];
    for (int i = 0; i < 256; ++i)
    {
        d[i] = len;
    }
    for (int i = len - 1; i >= 0; --i)
    {
            if (d[(int)pattern[i]] > len - i)
        {
            d[(int)pattern[i]] = i + 1;
        }
    }

    for (int i = 0; i + 1 < len; ++i)
    {
        if (d[(int)pattern[i]] > len - i - 1)
        {
            d[(int)pattern[i]] = len - i - 1;
        }
    }

    char text [1001];
    int pos = len - 1;
    //int shift = 0;
    //while (scanf("%s", text))
    //scanf("%s", text);
    fgets (text, 1000, stdin);
    scanf ("%[^\n]%*c", text);

    {
        //printf("***\n");
        int len_text = strlen(text);
        //printf("len = %d\nlen_text = %d\ntext = %s\n", len, len_text, text);
        while (pos <= len_text)
        {
            int concurrences = 0;
            while (text[pos - concurrences] == pattern[len - concurrences - 1] && len - concurrences - 1 >= 0)
            {
                printf("%d ", pos - concurrences + 1);
                ++concurrences;
            }
            if (concurrences != len)
            {
                printf("%d ", pos - concurrences + 1);
            }
            pos += d[(int)text[pos]];
            //printf("pos + len = %d\n", pos + len);
        }
        printf("\n");
    }
    return 0;

}
