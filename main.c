#include "mtll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    struct mtll** array;
    size_t size;
} DynamicArray;

DynamicArray* init_Dynamic_Array(){
    DynamicArray* da = malloc(sizeof(DynamicArray));
    da->array = NULL;
    da->size = 0;
    return da;
}

void add_to_Dynamic_Array(DynamicArray* da, struct mtll* m){
    da->size += 1;
    da->array = realloc(da->array, da->size * sizeof(struct mtll));
    if (da->array == NULL){
        printf("Dynamic Array realloc fail\n");
        exit(1);
    }
    da->array[da->size-1] = m;
}

struct mtll* get_from_Dynamic_Array(DynamicArray* da, int idx){
    return da->array[idx];
}

int* count_Dynamic_Array(DynamicArray* da){
    int lists_available[da->size];
    int counter = 0;
    for (index = 0; index < da->size; index++){
        if (da->array[index] != NULL){
            lists_available[counter] = index;
            counter++;
        }
    }

    return lists_available;
}

void free_everything(DynamicArray* da){
    if (da == NULL) return;

    for (size_t i = 0; i < da->size; i++) {
        if (da->array[i] != NULL) {
            mtll_free(da->array[i]);
        }
    }

    free(da->array);

    free(da);
}

int main(int argc, char** argv) {
    char input[128];
    DynamicArray* list_of_mtlls = init_Dynamic_Array();

    while (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;

        if (strncmp(input, "NEW ", 4) == 0 || strcmp(input, "NEW") == 0) {
            int len;
            char after_number;
            if (sscanf(input + 4, "%d%c", &len, &after_number) == 1) {
                struct mtll* created_mtll = mtll_create(len);
                printf("List %zu: ", list_of_mtlls->size);
                mtll_view_all(created_mtll);
                add_to_Dynamic_Array(list_of_mtlls, created_mtll);
            } else {
                printf("INVALID COMMAND: NEW\n");
            }
        }else if (strncmp(input, "VIEW ", 5) == 0 || strcmp(input, "VIEW") == 0) {
            int index;
            char after_number;
            if (sscanf(input + 5, "%d%c", &index, &after_number) == 1 && 
            index < list_of_mtlls->size) {
                struct mtll* target_mtll = get_from_Dynamic_Array(list_of_mtlls, index);
                // check if it is removed
                if (target_mtll != NULL) {  
                    mtll_view_all(target_mtll);
                }else{
                    printf("INVALID COMMAND: VIEW\n");
                } 
            } else {
                printf("INVALID COMMAND: VIEW\n");
            }
        }else if (strncmp(input, "TYPE ", 5) == 0 || strcmp(input, "TYPE") == 0){
            int index;
            char after_number;
            if (sscanf(input + 5, "%d%c", &index, &after_number) == 1 && 
            index < list_of_mtlls->size) {
                struct mtll* target_mtll = get_from_Dynamic_Array(list_of_mtlls, index);
                // check if it is removed
                if (target_mtll != NULL) {  
                    mtll_type_all(target_mtll);
                }else{
                    printf("INVALID COMMAND: TYPE\n");
                }
            } else {
                printf("INVALID COMMAND: TYPE\n");
            }
        }else if (strncmp(input, "REMOVE ", 7) == 0 || strcmp(input, "REMOVE") == 0){
            int index;
            char after_number;
            if (sscanf(input + 7, "%d%c", &index, &after_number) == 1 && 
            index < list_of_mtlls->size) {
                struct mtll* target_mtll = get_from_Dynamic_Array(list_of_mtlls, index);
                if (target_mtll != NULL) {  
                    mtll_free(target_mtll);
                    list_of_mtlls->array[index] = NULL; 
                    printf("List %d has been removed.\n", index);
                }else{
                    printf("INVALID COMMAND: REMOVE\n");
                }
            } else {
                printf("INVALID COMMAND: REMOVE\n");
            }
        }else if ()
        else{
            printf("INVALID COMMAND: INPUT\n");
        }
    }

    //printf("Free Everything.\n");
    free_everything(list_of_mtlls);
    return 0;
}
