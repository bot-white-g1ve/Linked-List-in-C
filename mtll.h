#ifndef MTLL_H
#define MTLL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    struct head** array;
    size_t size;
} DynamicArray;

typedef enum {
    INT,
    FLOAT,
    CHAR,
    STR,
    REFERENCE,
} ValueType;

typedef struct mtll {
    ValueType t;
    union {
        int i;
        float f;
        char c;
        char s[128];
        int r;
    } value;
    struct mtll* next;
} Mtll;

typedef struct head {
    bool isEmpty;
    int size;
    bool hasReference;
    bool beReferenced;
    struct mtll* next;
} Head;

// A few suggested function prototypes:
// Feel free to change or improve these as you need.

extern char* strip(char*);

extern int has_curly_brace(char*);

extern struct head *mtll_create(int len);

extern void mtll_free(struct head *);

extern void mtll_view(struct mtll *);

extern void mtll_view_all(struct head *);

extern void mtll_type(struct mtll *);

extern void mtll_type_all(struct head *);

extern void mtll_remove(struct mtll **, size_t, struct mtll *);

extern Mtll* mtll_node_create(char*, bool*, bool*);

extern Head* mtll_insert(struct head *, int, char*);

extern Head* mtll_delete(struct head *, int);

#endif
