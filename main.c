#include<stdio.h>
#include"type.h"

int main()
{
    FILE *fp;                              //Take one file pointer and open that .c file 

    fp = fopen( "file.c" ,"r");            // In read mode open

    if (fp == NULL)
    {
        printf("\n File not open : ERROR");      // Check fle is opening or not 
    }
    else
    { 
        printf("\n File opened successfully\n");        

       // printf("\n The file is in %d" , ftell(fp));      // take ftell to check where the file is pointing

        char ch;

        fread(&ch , 1, 1, fp);

        printf("\n The content inside the file is %c\n", ch);   // just for our verification print the first char of file.c
   
         while(ch = fgetc(fp) != '\n');                               // skip the #include <stdio.h> line 

     //    fread(&ch ,1 , 1 , fp);

     //   printf("\n After skipping the  content are now in : %c\n ", ch);   // now check where the file pointer is in
        
     printf("\n The first line is skipped successfulyy");
     
        if (for_keyword_identfire(fp)== SUCCESS)
        {
            printf("\n The keywords and identfire are  seprated successfully\n");
        }
    }



}