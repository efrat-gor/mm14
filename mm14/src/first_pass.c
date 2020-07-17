#include "first_pass.h"
int symbol_flag=0;


/*Kבדוק לגבי השליחה לפונקציות את האינדקס אם לא צריך לשלוח אותו בתור כתוהת כדאי שישתנה ויתקדם אחכ לשאר הפונקציות*/


void discover_line(char *line,int index)
{   int len_op=0,i;
    index=advance_space(line,index);
    i=index;
    while(*(line+i))
      printf("%c",*(line+ i++));
    printf("\n");
    if(!strncmp(".entry",line+index,6))
    {

    }
    if(!strncmp(".extern",line+index,7))
    {

    }
    if(!strncmp(".string",line+index,7))
    {
        string_to_data (line,index+7);
        

    }
    if(!strncmp(".data",line+index,5))
    {

    }
    /*if it a symbol*/
    if(is_label(line,index))
    {
        return;
    }
    else if(len_op=is_operation(line+index))  /*operation*/
    {
        operation(line,index,len_op);
        return;
    }

}
/*the function insert the string to the data_table by asci */
void string_to_data(char*line ,int index)
{  int i=0;/**remve after*/
    index=advance_space(line,index);
    if(*(line+index)!='\"')
    {
        printf("WARNING . in line %d :missing %c before the string ",line_counter,'"');
        error_flag=1;
    }
    index++;
    /*till the string get finshis  insert the asci to the data table*/
    while(*(line+index)&&*(line+index)!='\"')
    {printf("i am here\n");/**remve after*/
      data_table[DC++].ch=*(line+index++);
    }
    data_table[DC++].ch=0;/*last word of every string is 0 (to know that the string get finish)*/
    while (data_table[i].ch)
    {
       printf("%c",data_table[i++].ch);
    }
    
}

/*the function analized the label and built the right things forthe label(check if  belong to codr/data*/
void label (char * line,int index,char name[MAX_LABEL_LENGTH])
{
    
    symbol* temp;
    index= advance_space(line,index);
    temp = (symbol*)malloc(sizeof(symbol));
	if (!temp)
	{
     printf("no memmory\n");
     error_flag=1;
	 return;
    }
    if(!exsist_symbol(name))
    {
    temp->next=head_symbol;
    head_symbol=temp;
    strcpy(head_symbol->symbol_name,name);
    if (*(line+index) == '.')
			{  
				/*If its guide statement*/
				head_symbol->address = DC;
				head_symbol->is_code = FALSE;
				head_symbol->is_external =FALSE;/*to check why i did that*/
				if (!strncmp(line+index, ".entry", 6)){
					printf("WARNING!! line %d: A label defined at the beginig of entry statement is ignored\n" ,line_counter);
                    error_flag=1;}
				else if (!strncmp(line+index, ".extern", 7)){
					printf("WARNING!! line %d: A label defined at the beginig of extern statement is ignored.\n", line_counter);
                    error_flag=1;}
				else
					/*Sends again to analize to find out if its string or data*/
					discover_line(line,index);  
			}
            
	else if(is_operation(line+index))
			{  
				/*If this is a statement of instruction*/
				head_symbol->address = IC;
				head_symbol->is_code =TRUE;
				head_symbol->is_external = FALSE;
				/*Go again to analize to find out which instruction statement*/
				discover_line(line,index);
			}
            else
            {
                printf("WARNING line %d: there are extranous text after label.\n",line_counter);
                error_flag=1;
            }
    }
     else{
         printf("WARNING line %d: this label is exsisitng in the data already.\n",line_counter);
         error_flag=1;
     }       

}
/*check if a symbol is already exsist in the list ofsymbol-that won't be duplicates symbols*/
 int exsist_symbol(char *name)
{
    symbol *temp;
    temp=head_symbol;
    while(temp)
    {
        if( strcmp(temp->symbol_name,name))
           return 1;
    }
    return 0;
}
int is_label (char *line,int index)
{
    char symbol_name[MAX_LABEL_LENGTH];
    int length=index;
    for(;index< MAX_LINE_LENGTH;index++)
    {
        if(*(line+index)==':')
        {  strncpy(symbol_name,line+length,index-length);
           label(line,++index,symbol_name);
           return 1;
        }
        else{

        }
    }
    return 0;
}


void operation (char * line,int index,int len_op)
{
    if(operation_table[operation_index].code>=0&&operation_table[operation_index].code<=13)
    {
        index=operands(line,index+len_op,"source");/*send for the first time*/
    }
    /*destenation -2 operands*/
    if(operation_table[operation_index].code>=0&&operation_table[operation_index].code<=4)
    {
        index=advance_space(line, ++index);
        if(*(line+ index)!=',')
        {
            printf("WARNING! in line %d : missing comma.\n",line_counter);
            error_flag=1;
        }
        else
        {
           index= operands(line,index+len_op,"destenation");/*if there are 2 operands*/
        }
    }
}
/*the function check and count how many words the operatiom take */
int operands(char *line,int index,char * kind)
{
    index=advance_space(line,index);
    if(*(line+index)=='r')
    { printf("%c\n",*(line+ index));/*remove this ine after*/
        index++;
        printf("%c\n",*(line+index));/*remove this ine after*/
        if(!( (*(line+index)) >0 && (*(line+index)) <= 7  ))
        {
           printf("%c\n",*(line+index));/*remove this ine after*/
           printf("WARNING in line %d: not exsisting such a register.\n",line_counter);
           error_flag=1;
        }

    }
    /*need another word*/
    else if(*(line+index)=='#')
    {    
        IC++;/*two lines of instruction are needded*/
        if(*(line+index)=='+'&& !(isdigit(*(line+index+1)))&& !(isdigit(*(line+index)))&& (*(line+ ++index)=='-'&& !(isdigit(*(line+index+1)))))
         { 
            printf("WARNNIG !in line %d : not a number after #.\n",line_counter);
            error_flag=1;                  
         }
        
    }
    else if(*(line+index)=='&')/*second system*/
    {
        IC++;
        if(operation_table[operation_index].code!=9)/*thissystem fit only for operation that their opcode is 9*/
        {
            printf("WARNING ! in line %d: cant prefore & after such a operation.\n",line_counter);
            error_flag=1;
            
        }
        
        /*code_table[IC].number==/*only in the second pass we will be able to complete this because we still dont know if this label is exsist already*/
 
    }
    else if(isalpha(*(line+index)))/*label*/
    { 
       IC++;
    }
    else/*could be extranous tabs after operation or variables*/
    { if(!strncmp(kind,"source",6)){
        printf("WARNING ! in line %d : extranous text after operation\n",line_counter);}
      else /*destenation*/
       { printf("WARNING ! in line %d : extranous text after variable\n",line_counter);}
      error_flag=1;
       /*advanse the index to the rest of the line that we want meet any more the extarnous text for countinue checkong the rest of the line*/
       while (!isalpha(*(line+index)))
       {
           index++;
       }
      index=operands(line,index,kind);/*send to checking again the same line(check if it is label or register and more...*/
    }
    return index;
}
/* the function check if the order is from the table_operation*/
int is_operation(char * str)
{ 
    int i;
    for(i=0;i<15;i++)
    {
        if(!strncmp(str,operation_table[i].name_operation,3))
        {
            operation_index=i;
            return 3;

        }

    }
    /*if it "stop"*/
    if(!strncmp(str,operation_table[i].name_operation,4))
    {
         operation_index=i;
         return 4;
    }

  return 0;

}
int advance_space (char *line,int index)
{
    while(isspace(*(line+index)))
    {
        index++;
    }
    return index;
}
/*void free_all(void * s1,int nbites )
{

}*/