
#include<stdio.h>
#include<string.h>
#include"common.h"

status Check_Extension(char *argv)
{
    
    char *p1 = argv;
    char *ptr = strstr(argv,".asm");
    printf("debug : %s %s\n",ptr+3, p1+(strlen(argv)-1));
    if((ptr+3) == (p1+(strlen(argv)-1)))
        return e_success;
    else
        return e_failure;
    
}

status Open_Asm_file(File_Atributes *fileattribs)
{
    fileattribs->file_ptr = fopen(fileattribs->file_name,"r");
    if(fileattribs->file_ptr == NULL)
    {
        printf("INFO: Files are missing..\n");
        printf("INFO: Exiting..\n");
        return e_failure;
    }

    fileattribs->clean_file_name = strtok(fileattribs->file_name,".");
    fileattribs->clean_file_name = strcat(fileattribs->clean_file_name,".s");
    printf("debug : %s\n",fileattribs->clean_file_name);
    fileattribs->clean_file_ptr = fopen(fileattribs->clean_file_name,"w+");
    if(fileattribs->clean_file_ptr == NULL)
    {
        printf("INFO: Files are missing..\n");
        printf("INFO: Exiting..\n");
        return e_failure;
    }

    fileattribs->hack_file_name = strtok(fileattribs->file_name,".");
    fileattribs->hack_file_name = strcat(fileattribs->hack_file_name,".hack");
    printf("debug : %s\n",fileattribs->hack_file_name);
    fileattribs->hack_file_ptr = fopen(fileattribs->hack_file_name,"w");
    if(fileattribs->hack_file_ptr == NULL)
    {
        printf("INFO: Files are missing..\n");
        printf("INFO: Exiting..\n");
        return e_failure;
    }

    return e_success;
}

