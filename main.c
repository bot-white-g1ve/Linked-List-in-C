#include "mtll.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    char input[128];
    while (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;

        if (strncmp(input, "NEW ", 4) == 0) {
            int len;
            char after_number;
        if (sscanf(input + 4, "%d%c", &len, &after_number) == 1) {
                struct mtll* mtll1;
                mtll1 = mtll_create(len);
            } else {
                printf("INVALID COMMAND: NEW\n");
            }
        }
    }
}
