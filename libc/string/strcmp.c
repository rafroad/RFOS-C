#include <string.h>

int strcmp(const char *str1, const char *str2) {
    if (str1 == str2) {
        return 0;
    }

    while (1) {
        unsigned char c1 = *str1;
        unsigned char c2 = *str2;

        if (c1 != c2) {
            return c1 - c2;
        }

        if (c1 == '\0') {
            return 0;
        }

        str1++;
        str2++;
    }
}
