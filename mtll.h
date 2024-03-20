#ifndef MTLL_H
#define MTLL_H

typedef enum {
    INT,
    FLOAT,
    CHAR,
    STR,
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

extern struct mtll *mtll_create(int len);

extern void mtll_free(struct mtll *);

extern void mtll_view(struct mtll *);

extern void mtll_view_all(struct mtll **, size_t);

extern void mtll_remove(struct mtll **, size_t, struct mtll *);

// You will likely need other functions for Parts 2 and 3,
// And for general input / output management


#endif
