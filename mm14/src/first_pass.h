
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "memory_map.c"

#define O_source_des(kind)O##kind;
#define M_source_des(kind)M##kind; 

extern symbol* head_symbol;
/*Index*/
extern int  IC;
extern int DC;
extern code  code_table[MAX_INSTRACTION_LENGTH];
extern data  data_table[MAX_DATA_LENGTH];

void discover_line(char *line,int index);
void string_to_data(char*line ,int index);
void label (char * line,int index,char name[MAX_LABEL_LENGTH]);
int exsist_symbol(char *name);
int is_label (char *line,int index);
void operation (char * line,int index,int len_op);
int operands(char *line,int index,char * kind);
int is_operation(char * str);
int advance_space (char *line,int index);
