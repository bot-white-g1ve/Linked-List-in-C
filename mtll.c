#include "mtll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct mtll *mtll_create(int len) {
    struct mtll *mtll_created;
    char input[128];

    for (int i = 0; i < len; i++) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        // try to transfer to int, float and char
        char *end_index_of_transfering;
        long intVal = strtol(input, &end_index_of_transfering, 10);
        if (end_index_of_transfering != input && *end_index_of_transfering == '\0') {
            printf("这是一个整数: %ld\n", intVal);
        } else {
            double floatVal = strtod(input, &end_index_of_transfering);
            if (end_index_of_transfering != input && *end_index_of_transfering == '\0') {
                printf("这是一个浮点数: %f\n", floatVal);
            } else {
                char charVal;
                if (sscanf(input, "%c", &charVal) == 1 && input[1] == '\0' && isprint((unsigned char)charVal)){
                    printf("这是一个可打印的字符: %c\n", charVal);
                }else {
                    printf("这是一个字符串: %s\n", input);
                }
            }
        }
    }
    return mtll_created;
}

void mtll_free(struct mtll *) {
    //TODO
}

//TODO: all other functions