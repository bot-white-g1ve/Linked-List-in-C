#include "mtll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* strip(char* str){
    char* end;

    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = 0;

    return str;
}

struct mtll *mtll_create(int len) {
    struct mtll* head = NULL;
    struct mtll* temp = NULL;

    char input[128];

    for (int i = 0; i < len; i++) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        struct mtll* newNode = malloc(sizeof(struct mtll));
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            temp->next = newNode;
        }
        temp = newNode;

        char *end_index_of_transfering;
        char* input_no_space = strip(input);
        long intVal = strtol(input_no_space, &end_index_of_transfering, 10);
        if (input_no_space != end_index_of_transfering && *end_index_of_transfering == '\0') {
            newNode->t = INT;
            newNode->value.i = intVal;
            continue;
        } else {
            double floatVal = strtod(input_no_space, &end_index_of_transfering);
            if (input_no_space != end_index_of_transfering && *end_index_of_transfering == '\0') {
                newNode->t = FLOAT;
                newNode->value.f = (float)floatVal;
                continue;
            } else {
                char charVal;
                if (sscanf(input, "%c", &charVal) == 1 && input[1] == '\0' && isprint((unsigned char)charVal)){
                    newNode->t = CHAR;
                    newNode->value.c = input[0];
                    continue;
                }else {
                    newNode->t = STR;
                    strncpy(newNode->value.s, input, sizeof(newNode->value.s) - 1);
                    newNode->value.s[sizeof(newNode->value.s) - 1] = '\0';
                    continue;
                }
            }
        }
    }
    return head;
}

void mtll_view(struct mtll* m) {
    switch (m->t) {
        case INT:
            printf("%d", m->value.i);
            break;
        case FLOAT:
            printf("%.2f", m->value.f);
            break;
        case CHAR:
            printf("%c", m->value.c);
            break;
        case STR:
            printf("%s", m->value.s);
            break;
        default:
            printf("Unknown type of mtll.\n");
    }
}

void mtll_view_all(struct mtll* m){
    mtll_view(m);

    struct mtll* temp;
    temp = m;

    while (temp->next != NULL){
        printf(" -> ");
        temp = temp->next;
        mtll_view(temp);
    }
    printf("\n");
}

void mtll_type(struct mtll* m){
    switch (m->t) {
        case INT:
            printf("int");
            break;
        case FLOAT:
            printf("float");
            break;
        case CHAR:
            printf("char");
            break;
        case STR:
            printf("string");
            break;
        default:
            printf("Unknown type of mtll.\n");
    }
}

void mtll_type_all(struct mtll* m){
    mtll_type(m);

    struct mtll* temp;
    temp = m;

    while (temp->next != NULL){
        printf(" -> ");
        temp = temp->next;
        mtll_type(temp);
    }
    printf("\n");
}

void mtll_free(struct mtll* m) {
    struct mtll* temp_pointer = m;
    struct mtll* temp_next = NULL;
    
    while (temp_pointer != NULL) {
        temp_next = temp_pointer->next;
        free(temp_pointer);
        temp_pointer = temp_next;
    }

    m = NULL;
}

//TODO: all other functions