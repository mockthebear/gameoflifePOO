#ifndef RULES
#define RULES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct rule{
        int id;
        int amnt;
        int *cellToDie;
        int cellToLive;
        int color[3];
        struct rule *next;
};

class RuleReader{
    FILE *fp;
    char *file;
    int size;
    public:
        RuleReader();
        void parseRules(struct rule *r);
};

#endif
