#ifndef TABLE_H
#define TABLE_H

#include"common.h"


#define MAX_TABLE_SIZE 101
#define MAX_PRE_DEFINED_SYMBOLS 23
#define MAX_JMP_INSTRUCTIONS 8
#define MAX_DEST_INSTRUCTIONS 16
#define MAX_COMPUTATION_INSTR 28


typedef struct node
{
    char instruction_name[50];
    char instruction_code[50];
    struct node *next;
}Symbol_Node;

typedef struct{
    Symbol_Node *symbol_Table[MAX_TABLE_SIZE];
}Symbol_table;

/* DJIB2 hash function to generate hash function on the strings */
uint hash(const char *str);

/* initialize the symbol table with all NULL values */
void initiate_sym_table(Symbol_table *Sym_table, int size);

/* inserts a new symbol at the generated hash index
*   if empty insert at the same place
*   else create a linked list at the same place
*/
void insert_symbol(Symbol_table *Sym_table,const char *str1, const char *str2);

/* looks for the label to return address to struct of node */
Symbol_Node *find_Symbol(Symbol_table *Sym_table,const char *str);
/*
*   Fill the table with the predefined values of the predefined symbols
*/
void populate_tables(Symbol_table *Sym_table,Symbol_table *Sym_table1,Symbol_table *Sym_table2,Symbol_table *Sym_table3);

#endif