#include "mtll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

DynamicArray* init_Dynamic_Array(){
    DynamicArray* da = malloc(sizeof(DynamicArray));
    da->array = NULL;
    da->size = 0;
    return da;
}

int add_to_Dynamic_Array(DynamicArray* da, struct head* m){
    da->size += 1;
    da->array = realloc(da->array, da->size * sizeof(struct mtll));
    if (da->array == NULL){
        printf("Dynamic Array realloc fail\n");
        exit(1);
    }
    da->array[da->size-1] = m;
    return da->size-1;
}

struct head* get_from_Dynamic_Array(DynamicArray* da, int idx){
    return da->array[idx];
}

// use a new parameter size to return the size of list_availiable
int* count_Dynamic_Array(DynamicArray* da, int* size){
    int* lists_available = malloc(sizeof(int) * da->size);
    int counter = 0;
    for (int index = 0; index < da->size; index++){
        if (da->array[index] != NULL){
            lists_available[counter] = index;
            counter++;
        }
    }

    *size = counter; 

    return lists_available;
}

void change_Dynamic_Array(DynamicArray* da, int idx, Head* new){
    da->array[idx] = new;
    return;
}

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
    int value;
    char after;
    if (sscanf(str, "{%d}%c", &value, &after) == 1) {
        return value;
    }
    return -1;
}

struct head *mtll_create(int len, DynamicArray* a) {
    if (len != 0){
        bool has_curly_brace_variable = false;

        struct head* head = malloc(sizeof(struct head));
        head->next = NULL;
        head->isEmpty = false;
        head->hasReference = 0;
        head->beReferenced = 0;
        head->idx = -1;
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

            struct mtll* newNode = mtll_node_create(input, a, &has_curly_brace_variable, head);

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
        head->hasReference = 0;
        head->beReferenced = 0;
        head->idx = -1;
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
        case REFERENCE:
            printf("{List %d}", m->value.r);
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
        case REFERENCE:
            printf("reference");
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

void mtll_free(struct head* m, DynamicArray* a, bool free_everything) {
    struct mtll* temp_pointer = m->next;
    struct mtll* temp_next = NULL;
    
    while (temp_pointer != NULL) {
        temp_next = temp_pointer->next;
        if (!free_everything){
            if (temp_pointer->t == REFERENCE) {
                Head* referenced_mtll = get_from_Dynamic_Array(a, temp_pointer->value.r);
                if (referenced_mtll != NULL){
                    referenced_mtll->beReferenced -= 1;
                }
            }
        }
        free(temp_pointer);
        temp_pointer = temp_next;
    }

    free(m);
    m = NULL;
}

Mtll* mtll_node_create(char* input, DynamicArray* a, bool* has_curly_brace_variable, Head* for_mtll) {
    Mtll* newNode = (Mtll*)malloc(sizeof(Mtll));
    //check allocation failure
    if (!newNode) return NULL;

    int num_of_reference = is_reference_format(input);
    if (num_of_reference != -1){
        if (num_of_reference < a->size && for_mtll->beReferenced == 0 && num_of_reference != for_mtll->idx){
            Head* nested_mtll = get_from_Dynamic_Array(a, num_of_reference);
            if (nested_mtll == NULL || nested_mtll->hasReference != 0){
                *has_curly_brace_variable = true;
            } else {
                for_mtll->hasReference += 1;
                nested_mtll->beReferenced += 1;
            }
        } else {
            *has_curly_brace_variable = true;
        }
        newNode->t = REFERENCE;
        newNode->value.r = num_of_reference;
        newNode->next = NULL;
        return newNode;
    }

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

    newNode->next = NULL;

    return newNode;
}

Head* mtll_insert(struct head* m, DynamicArray* a, int index, char* input){
    if (!m) return NULL;

    bool has_curly_brace_variable = false;
    Mtll* newNode = mtll_node_create(input, a, &has_curly_brace_variable, m);

    if (has_curly_brace_variable == true){
        return NULL;
    }

    if (m->isEmpty == true){
        if (index == 0 || index == -1){
            m->next = newNode;
            m->isEmpty = false;
            return m;
        }else{
            return NULL;
        }
    } else if (m->isEmpty == false){
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
            newNode->next = m->next;
            m->next = newNode;
            return m;
        } else{
            Mtll* current = m->next;
            Mtll* previous = NULL;

            int currentPosition = 0;
            while (current != NULL && currentPosition < index) {
                previous = current;
                current = current->next;
                currentPosition++;
            }

            if (currentPosition == index) {
                newNode->next = previous->next;
                previous->next = newNode;
                return m;
            }
        }
        
    }
    
    return NULL;
}

Head* mtll_delete(Head* m, int index, DynamicArray* a){
    if (!m) return NULL;

    if (m->isEmpty == true){
        return NULL;
    } else if (m->isEmpty == false){
        if (m->next->next == NULL && (index == 0 || index == -1)){
            if (m->next->t == REFERENCE){
                m->hasReference -= 1;
                Head* referenced_mtll = get_from_Dynamic_Array(a, m->next->value.r);
                referenced_mtll->beReferenced -= 1;
            }
            free(m->next);
            m->next = NULL;
            m->isEmpty = true;
            return m;
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

        Mtll* current = m->next;
        Mtll* previous = NULL;

        int currentPosition = 0;
        while (current->next != NULL && currentPosition < index) {
            previous = current;
            current = current->next;
            currentPosition++;
        }

        if (currentPosition == index) {
            Mtll* temp_next = current->next;
            if (current->t == REFERENCE){
                m->hasReference -= 1;
                Head* referenced_mtll = get_from_Dynamic_Array(a, current->value.r);
                referenced_mtll->beReferenced -= 1;
            }
            free(current);
            if (previous == NULL){
                m -> next  = temp_next;
            } else {
                previous->next = temp_next;
            }
            return m;
        }
    }

    return NULL;
}

void mtll_view_nested(struct mtll* m, DynamicArray* da) {
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
        case REFERENCE:
            printf("{");
            Head* nested_mtll = get_from_Dynamic_Array(da, m->value.r);
            mtll_view_all_without_nextLine(nested_mtll);
            printf("}");
            break;
        default:
            printf("Unknown type of mtll.\n");
    }
}

void mtll_view_nested_all(struct head* m, DynamicArray* da){
    if (!m){
        printf("this pointer is NULL.\n");
        return;
    }
    
    if (m->isEmpty == false){
        struct mtll* temp;
        temp = m->next;

        mtll_view_nested(temp, da);

        while (temp->next != NULL){
            printf(" -> ");
            temp = temp->next;
            mtll_view_nested(temp, da);
        }
        printf("\n");
    }else if (m->isEmpty == true){
        printf("\n");
    }
}

void mtll_view_all_without_nextLine(struct head* m){
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
        //printf("\n");
    }else if (m->isEmpty == true){
        //printf("\n");
    }
}

//TODO: all other functions