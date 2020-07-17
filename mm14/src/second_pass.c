
void operation (char * line,int index,int len_op)
{
    if(table_operation[operation_index].code>=0&&table_operation[operation_index].code<=13)
    {
        operands(line,index,"source");/*send for the first time*/
    }
    code_table[IC]regular.funct=table_operation[operation_index].funct;
    code_table[IC]regular.opcode=table_operation[operation_index].code;
    /*destenation -2 operands*/
    if(table_operation[operation_index].code>=0&&table_operation[operation_index].code<=4)
    {
         index=advance_space(line,index++);
        if(*(line+index++)!=',')
        {
            printf("WARNING! in line %d : missing comma.\n",line_counter);
            error_flag=1;
        }
        else
        {
            operands(line,index,"destenation");/*if there are 2 operands*/
        }
    }
}

/*function that built the words n the memory-code*/

/*the function check what kind of miun fitthe code and insert to the cose_table
this function is caled 2 times
the firat is for the source the second is for the destenation 
surely only when there is operation with two operands*/
void operands(char *line,int index,char * kind)
{
    index=advance_space(line+index+len_op)
    if(*(line+index)=='r')
    { 
        if(*(line+ ++index)<0||*(line+index)>7)
        {
           printf("WARNING in line %d: not exsisting such a register.\n",line_counter);
           error_flag=1;
        }
        else{
           /*send to the makro for known if it is first or second time*/
           code_table[IC].regular.O_source_des(kind)=*(line+index);
           code_table[IC].regular.M_source_des(kind)=3;

        }
    }
    /*need another word*/
    else if(*(line+index)=='#')
    {
        ode_table[IC]regular.A=1;
        code_table[IC]regular.M_source_des(kind)=0;
        IC++/*two lines of instruction are needded*/
        if(*(line+ ++index)=='-')
        {/*negetive number*/
           number=atoi(*(line+ ++index));
           code_table[IC].number//to opposite the negative number with a mask
        }
        else if(*(line+index)=='+'&& isdigit(*(line+index+1))||isdigit(*(line+index)))
        { 
            if(*(line+index)=='+')
                index++;
            number=atoi(*(line+ index));
            code_table[IC].number.digit=number;
                     

        }
        else{
            printf("WARNNIG !in line %d : not a number after #.\n",line_counter);
            error_flag=1;
        }
        
    }
    else if(*(line+index)=='&')/*second system*/
    {
        
        code_table[IC].regular.A=1;
        code_table[IC].regular.Mdestenation=2; 
        IC++;
        if(table_operation[operation_index].code!=9)/*thissystem fit only for operation that their opcode is 9*/
        {
            printf("WARNING ! in line %d: cant prefore & after such a operation.\n",line_conter);
            error_flag=1;
            break;
        }
        
        /*code_table[IC].number==/*only in the second pass we will be able to complete this because we still dont know if this label is exsist already*/
 
    }
    else/*label*/
    { 
       
       /*send to the makro for known if it is first or second time*/
       code_table[IC].regular.M_source_des(kind)=1;
       IC++;
    }
}