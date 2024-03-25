#include "mtll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void free_everything(DynamicArray* da){
    if (da == NULL) return;

    for (size_t i = 0; i < da->size; i++) {
        if (da->array[i] != NULL) {
            mtll_free(da->array[i], da);
        }
    }

    free(da->array);

    free(da);
}

/*
int main(int argc, char** argv) {
    char input[128];
    DynamicArray* list_of_mtlls = init_Dynamic_Array();

    while (fgets(input, sizeof(input), stdin) != NULL) {
        if (!strchr(input, '\n')) {
            // Ignore stdin larger than 128
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        input[strcspn(input, "\n")] = 0;

        if (strncmp(input, "NEW ", 4) == 0 || strcmp(input, "NEW") == 0) {
            int len;
            char after_number;
            if (sscanf(input + 4, "%d%c", &len, &after_number) == 1) {
                if (len < 0){
                    printf("INVALID COMMAND: NEW\n");
                    continue;
                }
                struct head* created_mtll = mtll_create(len, list_of_mtlls);
                if (created_mtll != NULL){
                    if (created_mtll->hasReference == 0){
                        printf("List %zu: ", list_of_mtlls->size);
                    }else {
                        printf("Nested %zu: ", list_of_mtlls->size);
                    }
                    mtll_view_all(created_mtll);
                    add_to_Dynamic_Array(list_of_mtlls, created_mtll);
                } 
            } else {
                printf("INVALID COMMAND: NEW\n");
            }
        }else if (strncmp(input, "VIEW ", 5) == 0 || strcmp(input, "VIEW") == 0) {
            int index;
            char after_number;
            if (sscanf(input + 5, "%d%c", &index, &after_number) == 1 && 
            index < list_of_mtlls->size) {
                struct head* target_mtll = get_from_Dynamic_Array(list_of_mtlls, index);
                // check if it is removed
                if (target_mtll != NULL) {  
                    mtll_view_all(target_mtll);
                }else{
                    printf("INVALID COMMAND: VIEW\n");
                } 
            } else if (strcmp(input, "VIEW ALL") == 0){
                int size_list_index_available = 0;
                int* list_index_available = count_Dynamic_Array(list_of_mtlls, &size_list_index_available);
                printf("Number of lists: %d\n", size_list_index_available);
                int idx;
                struct head* target_mtll;
                for (int i = 0; i < size_list_index_available; i++) {
                    idx = list_index_available[i];
                    target_mtll = get_from_Dynamic_Array(list_of_mtlls, idx);

                    if (target_mtll->hasReference == 0){
                        printf("List %d\n", idx);
                    }else {
                        printf("Nested %d\n", idx);
                    }
                }
                free(list_index_available);
            }else {
                printf("INVALID COMMAND: VIEW\n");
            }
        }else if (strncmp(input, "TYPE ", 5) == 0 || strcmp(input, "TYPE") == 0){
            int index;
            char after_number;
            if (sscanf(input + 5, "%d%c", &index, &after_number) == 1 && 
            index < list_of_mtlls->size) {
                struct head* target_mtll = get_from_Dynamic_Array(list_of_mtlls, index);
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
                struct head* target_mtll = get_from_Dynamic_Array(list_of_mtlls, index);
                if (target_mtll != NULL && target_mtll->beReferenced == 0) {
                    mtll_free(target_mtll, list_of_mtlls);
                    list_of_mtlls->array[index] = NULL; 
                    printf("List %d has been removed.\n\n", index);

                    int size_list_index_available = 0;
                    int* list_index_available = count_Dynamic_Array(list_of_mtlls, &size_list_index_available);
                    printf("Number of lists: %d\n", size_list_index_available);
                    int idx;
                    struct head* this_mtll;
                    for (int i = 0; i < size_list_index_available; i++) {
                        idx = list_index_available[i];
                        this_mtll = get_from_Dynamic_Array(list_of_mtlls, idx);

                        if (this_mtll->hasReference == 0){
                            printf("List %d\n", idx);
                        }else {
                            printf("Nested %d\n", idx);
                        }
                    }
                    free(list_index_available);
                } else {
                    printf("INVALID COMMAND: REMOVE\n");
                }
            } else {
                printf("INVALID COMMAND: REMOVE\n");
            }
        }else if (strncmp(input, "INSERT ", 7) == 0 || strcmp(input, "INSERT") == 0){
            int mtll_index;
            int list_index;
            char after_number;
            char insertInput[128];
            if (sscanf(input + 7, "%d %d%c", &mtll_index, &list_index, &after_number) == 3 && 
            mtll_index < list_of_mtlls->size && after_number == ' ') {
                //Find the second space
                char* restOfString = strchr(input + 7, ' ');
                restOfString = strchr(restOfString + 1, ' ');
                strncpy(insertInput, restOfString + 1, sizeof(insertInput) - 1);
                    
                struct head* target_mtll = get_from_Dynamic_Array(list_of_mtlls, mtll_index);
                if (target_mtll != NULL) {  
                    Head* newhead = mtll_insert(target_mtll, list_of_mtlls, list_index, insertInput);
                    if (newhead != NULL){
                        change_Dynamic_Array(list_of_mtlls, mtll_index, newhead);
                        if (target_mtll->hasReference == 0){
                            printf("List %d: ", mtll_index);
                        }else {
                            printf("Nested %d: ", mtll_index);
                        }
                        mtll_view_all(newhead);
                    } else if (newhead == NULL){
                        printf("INVALID COMMAND: INSERT\n");
                    }
                }else{
                    printf("INVALID COMMAND: INSERT\n");
                }
            } else {
                printf("INVALID COMMAND: INSERT\n");
            }
        }else if (strncmp(input, "DELETE ", 7) == 0 || strcmp(input, "DELETE") == 0){
            int mtll_index;
            int list_index;
            char after_number;
            if (sscanf(input + 7, "%d %d%c", &mtll_index, &list_index, &after_number) == 2 && 
            mtll_index < list_of_mtlls->size) {
                struct head* target_mtll = get_from_Dynamic_Array(list_of_mtlls, mtll_index);
                if (target_mtll != NULL) {  
                    Head* newhead = mtll_delete(target_mtll, list_index, list_of_mtlls);
                    if (newhead != NULL){
                        change_Dynamic_Array(list_of_mtlls, mtll_index, newhead);
                        if (target_mtll->hasReference == 0){
                            printf("List %d: ", mtll_index);
                        }else {
                            printf("Nested %d: ", mtll_index);
                        }
                        mtll_view_all(newhead);
                    } else if (newhead == NULL){
                        printf("INVALID COMMAND: DELETE\n");
                    }
                }else{
                    printf("INVALID COMMAND: DELETE\n");
                }
            } else {
                printf("INVALID COMMAND: DELETE\n");
            }
        }else if (strncmp(input, "VIEW-NESTED ", 12) == 0 || strcmp(input, "VIEW-NESTED") == 0){
            int index;
            char after_number;
            if (sscanf(input + 12, "%d%c", &index, &after_number) == 1 && 
            index < list_of_mtlls->size) {
                struct head* target_mtll = get_from_Dynamic_Array(list_of_mtlls, index);
                // check if it is removed
                if (target_mtll != NULL) {  
                    mtll_view_nested_all(target_mtll, list_of_mtlls);
                }else{
                    printf("INVALID COMMAND: VIEW-NESTED\n");
                } 
            } else {
                printf("INVALID COMMAND: VIEW-NESTED\n");
            }
        }else{
            printf("INVALID COMMAND: INPUT\n");
        }
    }

    //printf("Free Everything.\n");
    free_everything(list_of_mtlls);
    return 0;
}
*/

int main(int argc, char** argv) {
    char input[128];

    while (fgets(input, sizeof(input), stdin) != NULL) {
        printf("%s", input);
    }
}
