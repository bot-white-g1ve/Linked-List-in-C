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
        if (!strchr(input, '\n')) {
            // Ignore stdin larger than 128
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        input[strcspn(input, "\n")] = 0;

        struct mtll* newNode = malloc(sizeof(struct mtll));
        //check allocation failure
        if (!newNode) return NULL;
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
        case EMPTY:
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
        case EMPTY:
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

Mtll* mtll_node_create(char* input){
    Mtll* newNode = (Mtll*)malloc(sizeof(Mtll));
    //check allocation failure
    if (!newNode) return NULL;

    newNode->next = NULL;
    char *end_index_of_transfering;
    char* input_no_space = strip(input);
    long intVal = strtol(input_no_space, &end_index_of_transfering, 10);
    if (input_no_space != end_index_of_transfering && *end_index_of_transfering == '\0') {
        newNode->t = INT;
        newNode->value.i = intVal;
    } else {
        double floatVal = strtod(input_no_space, &end_index_of_transfering);
        if (input_no_space != end_index_of_transfering && *end_index_of_transfering == '\0') {
            newNode->t = FLOAT;
            newNode->value.f = (float)floatVal;
        } else {
            char charVal;
            if (sscanf(input, "%c", &charVal) == 1 && input[1] == '\0' && isprint((unsigned char)charVal)){
                newNode->t = CHAR;
                newNode->value.c = input[0];
            }else {
                newNode->t = STR;
                strncpy(newNode->value.s, input, sizeof(newNode->value.s) - 1);
                newNode->value.s[sizeof(newNode->value.s) - 1] = '\0';
            }
        }
    }

    return newNode;
}

Mtll* mtll_insert(struct mtll* m, int index, char* input){
    if (!m) return NULL;

    if (m->t == EMPTY){
        if (index == 0 || index == -1){
            Mtll* newNode =mtll_node_create(input);
            free(m);
            return newNode;
        }else{
            return NULL;
        }
    }

    int length = 0;
    Mtll* temp = m;
    while (temp) {
        length++;
        temp = temp->next;
    }

    if (index < 0) {
        index = length + 1 + index;
        if (index < 0) return NULL;
    }

    if (index == 0) {
        Mtll* newNode =mtll_node_create(input);
        if (!newNode) return NULL;

        newNode->next = m;
        m = newNode;
        return m;
    }

    Mtll* current = m;
    Mtll* previous = NULL;

    int currentPosition = 0;
    while (current != NULL && currentPosition < index) {
        previous = current;
        current = current->next;
        currentPosition++;
    }

    if (currentPosition == index) {
        Mtll* newNode = mtll_node_create(input);
        if (!newNode) return 0; // Allocation failure

        newNode->next = previous->next;
        previous->next = newNode;
        return m;
    }

    return NULL;
}

Mtll* mtll_delete(Mtll* m, int index){
    if (!m) return NULL;

    if (m->next == NULL){
        if (m->t != EMPTY && (index == 0 || index == -1)){
            m->t = EMPTY;
            return m;
        }else{
            return NULL;
        }
    }

    int length = 0;
    Mtll* temp = m;
    while (temp) {
        length++;
        temp = temp->next;
    }

    if (index < 0) {
        index = length + index;
        if (index < 0) return NULL;
    }

    if (index == 0 && m->next != NULL) {
        Mtll* newHead = m->next;
        free(m);
        return newHead;
    }

    Mtll* current = m;
    Mtll* previous = NULL;

    int currentPosition = 0;
    while (current != NULL && currentPosition < index) {
        previous = current;
        current = current->next;
        currentPosition++;
    }

    if (currentPosition == index) {
        Mtll* temp_next = current->next;
        free(current);
        previous->next = temp_next;
        return m;
    }

    return NULL;
}

//TODO: all other functions