#include <stdio.h>
#define MAX_LABEL_LENGTH 100
#define MAX_LINE_LENGTH 80
/*globals*/
int line_counter, error_flag,operation_index,symbol_flag;

typedef enum { FALSE, TRUE } boolean;


 typedef struct {
    unsigned  E:1;
    unsigned  R:1;
    unsigned  A:1;
    unsigned  funct:5;
    unsigned  Odestinition:3;
    unsigned  Mdestinition:2;
    unsigned  Osource:3;
    unsigned  Msource:3;
    unsigned  opcode:6;
}word;

typedef struct {
  unsigned  E:1;
  unsigned  R:1;
  unsigned  A:1; 
  unsigned  digit:21; 
}word_number;
typedef union 
{
    word regular;
    word_number number;
}code ;
typedef struct{
    unsigned ch:24
}data;

typedef struct{
    char system_source[3];
    char system_destination[3];
    int code;
    int funct;
    char* name_operation;
}table_operation;

static table_operation operation_table[16]=
{   {"13","013",0,0,"mov"},
    {"013","013",1,0,"cmp"},
    {"13","013",2,1,"add"},
    {"13","013",2,2,"sub"},
    {"13","1",4,0,"lea"},
    {"13","",5,1,"clr"},
    {"13","",5,2,"not"},
    {"13","",5,3,"inc"},
    {"13","",5,4,"dec"},
    {"12","",9,1,"jmp"},
    {"12","",9,2,"bne"},
    {"12","",9,3,"jsr"},
    {"13","",12,0,"red"},
    {"013","",13,0,"prn"},
    {"","",14,0,"rts"},
    {"","",15,0,"stop"}

};
typedef struct {

   char symbol_name[MAX_LABEL_LENGTH];
	unsigned address;
	boolean is_code;/*true-it is code false it is data*/
	boolean is_external;
    struct symbol* next;
}symbol;


