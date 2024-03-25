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
    int hasReference;
    int beReferenced;
    struct mtll* next;
} Head;

// A few suggested function prototypes:
// Feel free to change or improve these as you need.

extern DynamicArray* init_Dynamic_Array();

extern void add_to_Dynamic_Array(DynamicArray*, struct head*);

extern struct head* get_from_Dynamic_Array(DynamicArray*, int);

extern int* count_Dynamic_Array(DynamicArray*, int*);

extern void change_Dynamic_Array(DynamicArray*, int, Head*);

extern char* strip(char*);

extern int has_curly_brace(char*);

extern struct head *mtll_create(int len, DynamicArray*);

extern void mtll_free(struct head *, DynamicArray*);

extern void mtll_view(struct mtll *);

extern void mtll_view_all(struct head *);

extern void mtll_type(struct mtll *);

extern void mtll_type_all(struct head *);

extern void mtll_remove(struct mtll **, size_t, struct mtll *);

extern Mtll* mtll_node_create(char*, DynamicArray*, bool*, Head*);

extern Head* mtll_insert(struct head *, DynamicArray*, int, char*);

extern Head* mtll_delete(struct head *, int, DynamicArray*);

extern void mtll_view_nested(struct mtll *, DynamicArray*);

extern void mtll_view_nested_all(struct head *, DynamicArray*);

extern void mtll_view_all_without_nextLine(struct head*);

#endif
