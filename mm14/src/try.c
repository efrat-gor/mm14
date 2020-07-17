
#include "first_pass.h"
#define O_source_des(kind)O##kind;
#define M_source_des(kind)M##kind; 
extern symbol* head_symbol;

void free_all(void * s1,int nbites )
{
    char *temp ;
    temp=(char*)malloc(nbites);
    memcpy(temp,s1,nbites);
    free(temp);
}
 int main()
 {
     symbol * temp;
     temp=head_symbol;
    /*  char num[5]="efrt";
    //  printf("th number is %s",num);
    //  free_all(&num,5);
    //  printf("th number is %s",num);
    //  code_table[IC].regular.M_source_des(source)=3;
    discover_line("MAIN: add r3,#5");*/
    while (temp)
    {
        printf("%s",temp->symbol_name);
        temp=temp->next;
        
    }
    discover_line("MAIN: .string \"abc\"",0);
    
     return 0;

 }