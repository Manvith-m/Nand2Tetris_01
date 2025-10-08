#ifndef ENCODE_H
#define ENCODE_H
#include"common.h"
#include"table.h"


status read_and_encode_instr(File_Atributes *fileattribs,Symbol_table *Sym_table,Symbol_table *Sym_table1,Symbol_table *Sym_table2,Symbol_table *Sym_table3);

status encode_A_isntruction(const char *str,File_Atributes *fileattribs);

status encode_var(char *str,Symbol_table *Sym_table,File_Atributes *fileattribs);

status encode_C_isntruction(char *str, Symbol_table *Sym_table1,Symbol_table *Sym_table2,Symbol_table *Sym_table3,File_Atributes *fileattribs);

status encode_type4_C_instruction(char *str, Symbol_table *Sym_table1,Symbol_table *Sym_table2,Symbol_table *Sym_table3,File_Atributes *fileattribs);

status encode_type3_C_instruction(char *str, Symbol_table *Sym_table1, Symbol_table *Sym_table3,File_Atributes *fileattribs);

status encode_type2_C_instruction(char *str, Symbol_table *Sym_table2, Symbol_table *Sym_table3,File_Atributes *fileattribs);

status encode_type1_C_instruction(char *str, Symbol_table *Sym_table3,File_Atributes *fileattribs);


#endif