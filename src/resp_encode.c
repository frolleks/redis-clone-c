#include "resp_encode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *encode_simple_string(const char *str) {
    int len = strlen(str) + 3;
    char *encoded = malloc(len + 3);
    if (!encoded)
        return NULL;
    sprintf(encoded, "+%s\r\n", str);
    return encoded;
}

const char *encode_bulk_string(const char *str) {
    int len = strlen(str);
    int total_len = snprintf(NULL, 0, "$%d\r\n%s\r\n", len, str) + 1;
    char *encoded = malloc(total_len);
    if (!encoded)
        return NULL;
    sprintf(encoded, "$%d\r\n%s\r\n", len, str);
    return encoded;
}

const char *encode_integer(int num) {
    int total_len = snprintf(NULL, 0, ":%d\r\n", num) + 1;
    char *encoded = malloc(total_len);
    if (!encoded)
        return NULL;
    sprintf(encoded, ":%d\r\n", num);
    return encoded;
}

const char *encode_array(const char *arr[], int size) {
    int total_len = snprintf(NULL, 0, "*%d\r\n", size);
    for (int i = 0; i < size; i++) {
        int len = strlen(arr[i]);
        total_len += snprintf(NULL, 0, "$%d\r\n%s\r\n", len, arr[i]);
    }

    char *encoded = malloc(total_len + 1);
    if (!encoded)
        return NULL;

    int offset = sprintf(encoded, "*%d\r\n", size);
    for (int i = 0; i < size; i++) {
        offset += sprintf(encoded + offset, "$%d\r\n%s\r\n",
                          (int)strlen(arr[i]), arr[i]);
    }
    return encoded;
}

const char *encode_error(const char *str) {
    int total_len = snprintf(NULL, 0, "-%s\r\n", str) + 1;
    char *encoded = malloc(total_len);
    if (!encoded)
        return NULL;
    sprintf(encoded, "-%s\r\n", str);
    return encoded;
}
