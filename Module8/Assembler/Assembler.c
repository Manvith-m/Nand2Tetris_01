#include<stdio.h>
#include"common.h"
#include"table.h"
#include"preprocessor.h"
#include"encode.h"

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        printf("INFO : Invalid Number of arguments.\n");
        printf("INFO : Exiting");
        return e_failure;
    }
    Symbol_table Sym_table;
    Symbol_table JMP_Table;
    Symbol_table DEST_Table;
    Symbol_table COMP_Table;
    populate_tables(&Sym_table, &JMP_Table, &DEST_Table, &COMP_Table);
    File_Atributes fileattribs;
    fileattribs.file_name = argv[1];
    if(Check_Extension(argv[1]) == e_success)
    {
        if(Open_Asm_file(&fileattribs) == e_success)
        {
            create_s_file(&fileattribs);
            populate_vars_abd_labels(&fileattribs,&Sym_table); 

           read_and_encode_instr(&fileattribs,&Sym_table, &JMP_Table, &DEST_Table, &COMP_Table);
            // for(int i =0;i<MAX_TABLE_SIZE;i++)
            // {
            //     if(DEST_Table.symbol_Table[i] == NULL)
            //         continue;
            //     Symbol_Node * temp_node = DEST_Table.symbol_Table[i];
            //     while(temp_node != NULL)
            //     {
            //         printf("-- %d -- %s -- %s", i, temp_node->instruction_name,temp_node->instruction_code);
            //         temp_node = temp_node->next;
            //     }
                
            //     printf("\n");
            // }
        }
        
        return e_success;
    }


}