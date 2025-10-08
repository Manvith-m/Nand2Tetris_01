#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include"common.h"
#include"table.h"

void create_s_file(File_Atributes *fileattribs);

void populate_vars_abd_labels(File_Atributes *fileattribs, Symbol_table *Sym_table);

void populate_labels(File_Atributes *fileattribs, Symbol_table *Sym_table);

char* dec_to_bin(int decimal, int n); 

#endif