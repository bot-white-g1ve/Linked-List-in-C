#include "mtll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

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

int has_curly_brace(char* str){
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '{' || str[i] == '}') {
            return 1;
        }
    }
    return 0;
}

int is_reference_format(char* str){
    if (str[0] != '{') return 0;
    int i = 1;
    if (!isdigit(str[i])) return 0;
    while (isdigit(str[i])) i++;
    if (str[i] != '}' || str[i+1] != '\0') return 0;
    return 1;
}

struct head *mtll_create(int len) {
    if (len != 0){
        bool has_curly_brace_variable = false;

        struct head* head = malloc(sizeof(struct head));
        head->next = NULL;
        head->isEmpty = false;
        struct mtll* temp = NULL;

        char input[128];

        for (int i = 0; i < len; i++) {
            if (!fgets(input, sizeof(input), stdin)) {
                return NULL;
            }
            if (!strchr(input, '\n')) {
                // Ignore stdin larger than 128
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
            input[strcspn(input, "\n")] = 0;

            struct mtll* newNode = mtll_node_create(input, &has_curly_brace_variable);

            if (head->next == NULL) {
                head->next = newNode;
            } else{
                temp->next = newNode;
            }
            temp = newNode;
        }

        if (has_curly_brace_variable == false) {
            return head;
        }else{
            printf("INVALID COMMAND: NEW\n");
            return NULL;
        }
    } else if (len == 0) {
        Head* head = (Head*)malloc(sizeof(Head));
        head -> next = NULL;
        head -> isEmpty = true;

        return head;
    }

    return NULL;
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

void mtll_view_all(struct head* m){
    if (!m){
        printf("this pointer is NULL.\n");
        return;
    }
    
    if (m->isEmpty == false){
        struct mtll* temp;
        temp = m->next;

        mtll_view(temp);

        while (temp->next != NULL){
            printf(" -> ");
            temp = temp->next;
            mtll_view(temp);
        }
        printf("\n");
    }else if (m->isEmpty == true){
        printf("\n");
    }
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

void mtll_type_all(struct head* m){
    if (!m){
        printf("this pointer is NULL.\n");
        return;
    }
    
    if (m->isEmpty == false){
        struct mtll* temp;
        temp = m->next;

        mtll_type(temp);

        while (temp->next != NULL){
            printf(" -> ");
            temp = temp->next;
            mtll_type(temp);
        }
        printf("\n");
    }else if (m->isEmpty == true){
        printf("\n");
    }
}

void mtll_free(struct head* m) {
    struct mtll* temp_pointer = m->next;
    struct mtll* temp_next = NULL;
    
    while (temp_pointer != NULL) {
        temp_next = temp_pointer->next;
        free(temp_pointer);
        temp_pointer = temp_next;
    }

    free(m);
    m = NULL;
}

Mtll* mtll_node_create(char* input, bool* has_curly_brace_variable) {
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
            if (has_curly_brace(input) == 1){
                *has_curly_brace_variable = true;
            }

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

Head* mtll_insert(struct head* m, int index, char* input){
    if (!m) return NULL;

    bool has_curly_brace_variable;

    if (m->isEmpty == true){
        if (index == 0 || index == -1){
            Mtll* newNode =mtll_node_create(input, &has_curly_brace_variable);
            m->next = newNode;
            return m;
        }else{
            return NULL;
        }
    }

    //deal with negative index
    int length = 0;
    Mtll* temp = m->next;
    while (temp) {
        length++;
        temp = temp->next;
    }
    if (index < 0) {
        index = length + 1 + index;
        if (index < 0) return NULL;
    }

    if (index == 0) {
        Mtll* newNode =mtll_node_create(input, &has_curly_brace_variable);
        if (!newNode) return NULL;

        newNode->next = m->next;
        m->next = newNode;
        return m;
    }

    Mtll* current = m->next;
    Mtll* previous = NULL;

    int currentPosition = 0;
    while (current != NULL && currentPosition < index) {
        previous = current;
        current = current->next;
        currentPosition++;
    }

    if (currentPosition == index) {
        Mtll* newNode = mtll_node_create(input, &has_curly_brace_variable);
        if (!newNode) return 0; // Allocation failure

        newNode->next = previous->next;
        previous->next = newNode;
        return m;
    }

    return NULL;
}

Head* mtll_delete(Head* m, int index){
    if (!m) return NULL;

    if (m->next->next == NULL){
        if (m->isEmpty == false && (index == 0 || index == -1)){
            m->isEmpty = true;
            free(m->next);
            m->next = NULL;
            return m;
        }else{
            return NULL;
        }
    }

    //deal with negative index
    int length = 0;
    Mtll* temp = m->next;
    while (temp) {
        length++;
        temp = temp->next;
    }
    if (index < 0) {
        index = length + index;
        if (index < 0) return NULL;
    }

    if (index == 0 && m->next->next != NULL) {
        Mtll* newHead = m->next->next;
        free(m->next);
        m->next = newHead;
        return m;
    }

    Mtll* current = m->next;
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