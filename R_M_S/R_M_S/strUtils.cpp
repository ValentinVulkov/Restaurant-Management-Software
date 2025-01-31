#include <iostream>

#include "strUtils.h"

int myStoi(const char* str) {
    int number = 0;
    int i = 0;

    // Loop through the string and convert digits to integer, ignoring non-numeric characters
    while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9') {
        number = number * 10 + (str[i] - '0');
        i++;
    }

    return number;
}

void myStrcpy(char* dest, const char* source) {
    while (*source) {
        *dest = *source;
        dest++;
        source++;
    }
    *dest = '\0';
}

bool compareStrings(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return false;
        }
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}

void myStrCat(char* dest, const char* src) {
    // Find the end of the destination string
    while (*dest != '\0') {
        dest++;
    }

    // Copy the source string to the end of the destination string
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    // Add the null terminator
    *dest = '\0';
}

void intToString(int value, char* buffer) {
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    int i = 0;
    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    // Reverse the string
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    buffer[i] = '\0';
}