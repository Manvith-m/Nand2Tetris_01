#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"common.h"
#include"table.h"
#include"encode.h"
#include"preprocessor.h"

status read_and_encode_instr(File_Atributes *fileattribs,Symbol_table *Sym_table,Symbol_table *Sym_table1,Symbol_table *Sym_table2,Symbol_table *Sym_table3)
{
    
    
    int count = 0;
    ssize_t read;
    char *next_line = NULL;
    size_t next_len = 0;
    rewind(fileattribs->clean_file_ptr);
    while((read = getline(&next_line,&next_len,fileattribs->clean_file_ptr)) != -1)
    {
        // printf("%s", next_line+1);
        if(next_line[0] == '(') continue;
        char *temp = next_line;
        // temp = strtok(temp," \r\n");
        if(temp[0] == '@' && isdigit(temp[1]))
            encode_A_isntruction(temp+1,fileattribs);
        else if(temp[0] == '@' && !(isdigit(temp[1])))
            encode_var(temp+1,Sym_table,fileattribs);
        else
            encode_C_isntruction(temp,Sym_table1,Sym_table2,Sym_table3,fileattribs);
    }
    return e_success;
}

status encode_A_isntruction(const char *str,File_Atributes *fileattribs)
{
    printf("INFO : ENCODING A INSTRUCTION ");
    printf("%s\n",str);
    char *sym = dec_to_bin(atoi(str),16);
    fputs(sym,fileattribs->hack_file_ptr);
    fputs("\n",fileattribs->hack_file_ptr);
    printf("%s\n",sym);
    return e_success;
}

status encode_var(char *str,Symbol_table *Sym_table,File_Atributes *fileattribs)
{
    // printf("INFO : ENCODING A VARIABLE ");
    char * temp = strtok(str," \n");
    printf("-%s'\n",temp);
    char *sym = (find_Symbol(Sym_table, temp))->instruction_code;
    fputs(sym,fileattribs->hack_file_ptr);
    fputs("\n",fileattribs->hack_file_ptr);
    printf("%s\n",sym);
    return e_success;
}



status encode_C_isntruction(char *str,Symbol_table *Sym_table1,Symbol_table *Sym_table2,Symbol_table *Sym_table3,File_Atributes *fileattribs)
{
    char * temp = strtok(str," \n");
    printf("%s'\n",str);
    if(strchr(temp, '=') && strchr(temp,';'))
        encode_type4_C_instruction(temp,Sym_table1,Sym_table2,Sym_table3,fileattribs);
    else if(strchr(temp,'='))
        encode_type2_C_instruction(temp,Sym_table2,Sym_table3,fileattribs);
    else if(strchr(temp,';'))
        encode_type3_C_instruction(temp,Sym_table1,Sym_table3,fileattribs);
    else 
        encode_type1_C_instruction(temp,Sym_table3,fileattribs);
    return e_success;
}

status encode_type4_C_instruction(char *str, Symbol_table *Sym_table1,Symbol_table *Sym_table2,Symbol_table *Sym_table3,File_Atributes *fileattribs)
{
    char bin_val[16] = "111";
    char *temp = str;
    char *comp;
    char *jmp;
    char *block = strtok(temp,"=;\0");
    char * memloc = find_Symbol(Sym_table2, block)->instruction_code;
    for(int i = 0;i < 2; i++)
    {
        char *block = strtok(NULL,"=;\0");
        if(i)
            jmp = find_Symbol(Sym_table1, block)->instruction_code;
        else
            comp = find_Symbol(Sym_table3, block)->instruction_code;
        // printf("-%s-\n",com
    }
    strcat(bin_val,comp);
    strcat(bin_val,memloc);
    strcat(bin_val,jmp);
    fputs(bin_val,fileattribs->hack_file_ptr);
    fputs("\n",fileattribs->hack_file_ptr);    
    printf("%s\n",bin_val);
    return e_success;
}

status encode_type2_C_instruction(char *str, Symbol_table *Sym_table2, Symbol_table *Sym_table3,File_Atributes *fileattribs)
{
    char bin_val[16] = "111";
    char *temp = str;
    char *block = strtok(temp,"=\0");
    char * memloc = find_Symbol(Sym_table2, block)->instruction_code;
    for(int i = 0;i < 1; i++)
    {
        char *block = strtok(NULL,"=\0");
        strcat(bin_val,(find_Symbol(Sym_table3, block))->instruction_code);
    }
    strcat(bin_val,memloc);
    strcat(bin_val,"000");
    fputs(bin_val,fileattribs->hack_file_ptr);
    fputs("\n",fileattribs->hack_file_ptr);
    printf("%s\n",bin_val);
    return e_success;
}

status encode_type3_C_instruction(char *str, Symbol_table *Sym_table1, Symbol_table *Sym_table3,File_Atributes *fileattribs)
{
    char bin_val[16] = "111";
    char *temp = str;
    char *block = strtok(temp,";\0");
    strcat(bin_val,(find_Symbol(Sym_table3, block))->instruction_code);
    strcat(bin_val,"000");
    for(int i = 0;i < 1; i++)
    {
        char *block = strtok(NULL,";\n");
        strcat(bin_val,(find_Symbol(Sym_table1, block))->instruction_code);
    } 
    fputs(bin_val,fileattribs->hack_file_ptr);
    fputs("\n",fileattribs->hack_file_ptr);
    printf("%s\n",bin_val);
    return e_success;
}

status encode_type1_C_instruction(char *str, Symbol_table *Sym_table3,File_Atributes *fileattribs)
{
    char bin_value[16] = "111";
    char *temp = str;
    strcat(bin_value,(find_Symbol(Sym_table3, temp))->instruction_code);
    strcat(bin_value,"000000");
    fputs(bin_value,fileattribs->hack_file_ptr);
    fputs("\n",fileattribs->hack_file_ptr);
    printf("%s\n",bin_value);
    return e_success;
}