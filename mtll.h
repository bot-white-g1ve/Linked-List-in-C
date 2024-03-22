#ifndef MTLL_H
#define MTLL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    INT,
    FLOAT,
    CHAR,
    STR,
    EMPTY,
} ValueType;

typedef struct mtll {
    ValueType t;
    union {
        int i;
        float f;
        char c;
        char s[128];
    } value;
    struct mtll* next;
} Mtll;

// A few suggested function prototypes:
// Feel free to change or improve these as you need.

extern char* strip(char*);

extern struct mtll *mtll_create(int len);

extern void mtll_free(struct mtll *);

extern void mtll_view(struct mtll *);

extern void mtll_view_all(struct mtll *);

extern void mtll_type(struct mtll *);

extern void mtll_type_all(struct mtll *);

extern void mtll_remove(struct mtll **, size_t, struct mtll *);

extern Mtll* mtll_node_create(char*);

extern Mtll* mtll_insert(struct mtll *, int, char*);

extern Mtll* mtll_delete(struct mtll *, int);

#endif
