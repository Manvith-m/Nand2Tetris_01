#ifndef COMMON_H
#define COMMON_H

#define uint unsigned int

typedef enum {
    e_failure,
    e_success
}status;


typedef struct{
    char *file_name;
    FILE *file_ptr;

    char *clean_file_name;
    FILE *clean_file_ptr;

    char *hack_file_name;
    FILE *hack_file_ptr;
    char machine_code_buffer[16];
}File_Atributes;

status Check_Extension(char *argv);

status Open_Asm_file(File_Atributes *fileattribs);



#endif