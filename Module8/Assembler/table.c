#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"table.h"

static Symbol_Node pre_defined_symbols[MAX_PRE_DEFINED_SYMBOLS] = {
    {"R0", "0000000000000000"},
    {"R1", "0000000000000001"},
    {"R2", "0000000000000010"},
    {"R3", "0000000000000011"},
    {"R4", "0000000000000100"},
    {"R5", "0000000000000101"},
    {"R6", "0000000000000110"},
    {"R7", "0000000000000111"},
    {"R8", "0000000000001000"},
    {"R9", "0000000000001001"},
    {"R10", "0000000000001010"},
    {"R11", "0000000000001011"},
    {"R12", "0000000000001100"},
    {"R13", "0000000000001101"},
    {"R14", "0000000000001110"},
    {"R15", "0000000000001111"},
    {"SP", "0000000000000000"},
    {"LCL", "0000000000000001"},
    {"ARG", "0000000000000010"},
    {"THIS", "0000000000000011"},
    {"THAT", "0000000000000100"},
    {"SCREEN", "0100000000000000"},
    {"KBD", "1100000000000000"}
};

static Symbol_Node JMP_symbol[MAX_JMP_INSTRUCTIONS] = {
    {"JGT", "001"},
    {"JEQ", "010"},
    {"JGE", "011"},
    {"JLT", "100"},
    {"JNE", "101"},
    {"JLE", "110"},
    {"JMP", "111"},
    {"null", "000"},
};
static Symbol_Node DEST_symbols[MAX_DEST_INSTRUCTIONS] = {
   {"M", "001"},
    {"D", "010"},
    {"A", "100"},
    {"MD", "011"},
    {"DM", "011"},
    {"AM", "101"},
    {"MA", "101"},
    {"AD", "110"},
    {"DA", "110"},
    {"AMD", "111"},
    {"ADM", "111"},
    {"MAD", "111"},
    {"MDA", "111"},
    {"DAM", "111"},
    {"DMA", "111"},
    {"null", "000"}

};

static Symbol_Node computation_symbols[MAX_COMPUTATION_INSTR] = {
    {"0",    "0101010"},
    {"1",    "0111111"},
    {"-1",   "0111010"},
    {"D",    "0001100"},
    {"A",    "0110000"},
    {"M",    "1110000"},
    {"!D",   "0001101"},
    {"!A",   "0110001"},
    {"!M",   "1110001"},
    {"-D",   "0001111"},
    {"-A",   "0110011"},
    {"-M",   "1110011"},
    {"D+1",  "0011111"},
    {"A+1",  "0110111"},
    {"M+1",  "1110111"},
    {"D-1",  "0001110"},
    {"A-1",  "0110010"},
    {"M-1",  "1110010"},
    {"D+A",  "0000010"},
    {"D+M",  "1000010"},
    {"D-A",  "0010011"},
    {"D-M",  "1010011"},
    {"A-D",  "0000111"},
    {"M-D",  "1000111"},
    {"D&A",  "0000000"},
    {"D&M",  "1000000"},
    {"D|A",  "0010101"},
    {"D|M",  "1010101"}
};


/* DJIB2 hash function to generate hash function on the strings*/
uint hash(const char *str)
{
    uint hash = 5381;
    int c;
    while((c = *str++))
    {
        hash  = ((hash<<5)+hash)+c;
    }
    return hash % MAX_TABLE_SIZE;
}

/* initialize the symbol table with all NULL values */
void initiate_sym_table(Symbol_table *Sym_table, int size)
{
    size = MAX_TABLE_SIZE;
    for(int i = 0;i<size;i++)
    {
        Sym_table->symbol_Table[i] = NULL;
    }
}
/* inserts a new symbol at the generated hash index
*   if empty insert at the same place
*   else create a linked list at the same place
*/
void insert_symbol(Symbol_table *Sym_table,const char *str1, const char *str2)
{
    if(find_Symbol(Sym_table,str1)!= NULL)
        return;
    uint idx = hash(str1) % MAX_TABLE_SIZE;
    Symbol_Node *new_symbol = malloc(sizeof(Symbol_Node));
    if(new_symbol == NULL)
        return;
    strcpy(new_symbol->instruction_name,str1);
    strcpy(new_symbol->instruction_code,str2);
    new_symbol->next = Sym_table->symbol_Table[idx];
    Sym_table->symbol_Table[idx] = new_symbol;
}

/* searches for the instruction and returns a struct pointer */
Symbol_Node *find_Symbol(Symbol_table *Sym_table,const char *str)
{
    uint idx = hash(str) % MAX_TABLE_SIZE;
    Symbol_Node * tempNode = Sym_table->symbol_Table[idx];
    while(tempNode)
    {
        if(strcmp(tempNode->instruction_name, str) == 0)
            return tempNode;
        tempNode = tempNode->next;
    }
    return NULL;
   
}

/*
*   Fill the table with the predefined values of the predefined symbols
*/
void populate_tables(Symbol_table *Sym_table,Symbol_table *Sym_table1,Symbol_table *Sym_table2,Symbol_table *Sym_table3)
{
    initiate_sym_table(Sym_table,MAX_PRE_DEFINED_SYMBOLS);
    for(int i =0;i<MAX_PRE_DEFINED_SYMBOLS;i++)
    {
        if(pre_defined_symbols[i].instruction_name == NULL || pre_defined_symbols[i].instruction_code == NULL)
            continue;
        printf("%s %s\n",pre_defined_symbols[i].instruction_name, pre_defined_symbols[i].instruction_code);
        insert_symbol(Sym_table,pre_defined_symbols[i].instruction_name, pre_defined_symbols[i].instruction_code);
    }

    initiate_sym_table(Sym_table1,MAX_JMP_INSTRUCTIONS);
    for(int i =0;i<MAX_JMP_INSTRUCTIONS;i++)
    {
        if(JMP_symbol[i].instruction_name == NULL || JMP_symbol[i].instruction_code == NULL)
            continue;
        printf("%s %s\n",JMP_symbol[i].instruction_name, JMP_symbol[i].instruction_code);
        insert_symbol(Sym_table1,JMP_symbol[i].instruction_name, JMP_symbol[i].instruction_code);
    }

    initiate_sym_table(Sym_table2,MAX_DEST_INSTRUCTIONS);
    for(int i =0;i<MAX_DEST_INSTRUCTIONS;i++)
    {
        if(DEST_symbols[i].instruction_name == NULL || DEST_symbols[i].instruction_code == NULL)
            continue;
        printf("%s %s\n",DEST_symbols[i].instruction_name, DEST_symbols[i].instruction_code);
        insert_symbol(Sym_table2,DEST_symbols[i].instruction_name, DEST_symbols[i].instruction_code);
    }

    initiate_sym_table(Sym_table3,MAX_COMPUTATION_INSTR);
    for(int i =0;i<MAX_COMPUTATION_INSTR;i++)
    {
        if(computation_symbols[i].instruction_name == NULL || computation_symbols[i].instruction_code == NULL)
            continue;
        printf("%s %s\n",computation_symbols[i].instruction_name, computation_symbols[i].instruction_code);
        insert_symbol(Sym_table3,computation_symbols[i].instruction_name, computation_symbols[i].instruction_code);
    }

}

