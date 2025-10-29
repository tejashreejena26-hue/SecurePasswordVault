#include <string.h>
#include "encryption.h"

void encrypt(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = str[i] + 3; // simple Caesar cipher shift
    }
}

void decrypt(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = str[i] - 3;
    }
}
