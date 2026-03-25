
#include "utils.h"

int manualStrLen(const char* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void manualStrCpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int manualStrCmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

int manualStrStr(const char* text, const char* query) {
    int tLen = manualStrLen(text);
    int qLen = manualStrLen(query);
    int i, j;

    if (qLen == 0) return 1;

    for (i = 0; i <= tLen - qLen; i++) {
        for (j = 0; j < qLen; j++) {
            char tc = text[i + j];
            char qc = query[j];
            if (tc >= 'A' && tc <= 'Z') tc += 32;
            if (qc >= 'A' && qc <= 'Z') qc += 32;
            if (tc != qc) break;
        }
        if (j == qLen) return 1;
    }
    return 0;
}
