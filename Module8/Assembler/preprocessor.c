#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"preprocessor.h"
#include"common.h"
#include"table.h"
#include"ctype.h"

void create_s_file(File_Atributes *fileattribs)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fileattribs->file_ptr)) != -1)
    {
        char *temp = line;

        // Skip blank or comment-only lines
        if (strlen(temp) <= 1 || temp[0] == '/' || temp[0] == '\n')
            continue;

        // Remove leading whitespace
        while (*temp == ' ' || *temp == '\t')
            temp++;

        // Remove trailing newline
        char *pos = strchr(temp, '\n');
        if (pos)
            *pos = '\0';

        // Remove inline comments
        pos = strstr(temp, "//");
        if (pos)
            *pos = '\0';

        // Trim trailing spaces
        int end = strlen(temp) - 1;
        while (end >= 0 && (temp[end] == ' ' || temp[end] == '\t'))
            temp[end--] = '\0';

        // Skip empty line after trimming
        if (strlen(temp) == 0)
            continue;

        // Write cleaned line to output file
        fputs(temp, fileattribs->clean_file_ptr);
        fputc('\n', fileattribs->clean_file_ptr);
    }

    free(line);
    rewind(fileattribs->clean_file_ptr);
}

void populate_labels(File_Atributes *fileattribs, Symbol_table *Sym_table)
{
    int count = 0;
    ssize_t read;
    char *next_line = NULL;
    size_t next_len = 0;
    while((read = getline(&next_line,&next_len,fileattribs->clean_file_ptr)) != -1)
    {
        char *temp = next_line+1;
        if(next_line[0] != '(')
            count+=1;
        else{
            temp[strlen(temp)-2] = '\0';
            char *count_string = dec_to_bin(count, 16);
            insert_symbol(Sym_table,temp,count_string);
        }
    }
    rewind(fileattribs->clean_file_ptr);
}

void populate_vars(File_Atributes *fileattribs, Symbol_table *Sym_table)
{
    uint int_addr = 16;
    char *trailing_ptr;
    ssize_t read;
    char *next_line = NULL;
    size_t next_len = 0;
    while((read = getline(&next_line,&next_len,fileattribs->clean_file_ptr)) != -1)
    {
        char *temp = next_line+1;
        temp = strtok(temp," \r\n");
        if(next_line[0] == '@' && (!isdigit(next_line[1])))
        {
            if(find_Symbol(Sym_table,temp)!= NULL)
                continue;
            char *addr_string = dec_to_bin(int_addr++, 16);
            insert_symbol(Sym_table,temp,addr_string);
        }
    }
    rewind(fileattribs->clean_file_ptr);
}
void populate_vars_abd_labels(File_Atributes *fileattribs, Symbol_table *Sym_table)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    populate_labels(fileattribs,Sym_table);
    populate_vars(fileattribs,Sym_table);
    
}

char* dec_to_bin(int decimal, int n) {
    char *binary_str = (char*)malloc(n + 1); // n bits + null terminator
    if (!binary_str) return NULL; // malloc failed

    binary_str[n] = '\0'; // null-terminate
    for (int i = n - 1; i >= 0; i--) {
        binary_str[i] = (decimal & 1) ? '1' : '0';
        decimal >>= 1;
    }
    return binary_str;
}

