#include<stdio.h>
#include"type.h"
#include<string.h>
#include<ctype.h>

int is_keyword_or_identfire( char buffer[])
{
   char inbuild_keywords[32][32] ={"int" , "char" , "float" ,"double" , "extern","signed" ,"unsigned","short","long","const","volatile","for",
    "while" , "do" , "goto" , "break" ,"continue" ,"if" ,"else if", "else", "switch case","default" , "auto", "register" , "static", "struct",
     "union" , "enum" ,"typedef","void" ,"return","sizeof"};

     for ( int i =0; i < 32; i++)
     {
           if (strcmp(buffer ,  inbuild_keywords[i]) ==0)
            {
                return 1;                                  // if it is keyword return 1 
            }

     }

    return 0;                                                // if it is identifire return 0
}

void for_digit(int ch)
{
  printf("\n %-10d--------> Numeric constant\n" , ch-'0');     // it is function for printing the digits that is numeric constant
}

int is_operator(int ch)
{
    if ( ch == '+' || ch == '-' || ch == '*' || ch == '/'|| ch =='=' )     // For opertor  checking function
    {
       return 1;
    }
    return 0;
}

int is_symbol(int ch)                                           // for symbol checking function
{
       
    if ( ch == '(' || ch == ')' || ch == '{' || ch == '}'|| ch == '!'  || ch == '@' || ch =='$' || ch =='%' || ch ==';' )
    {
      return 1;
    }
    return 0;  
     
}


status for_keyword_identfire ( FILE *fp)
{
    int count =0;

    char buffer[20];

    int ch;

    int i=0;
    
    int count2=0;
    int count3=0;
    int flag = 0;   
    
    // literally take one buffer and read the char one by one in that file if it is alphabet mneans store it in buffer 

    // when it reach space that is gap means put \0 and send to is_keyword function

     while (( ch =  fgetc(fp) )!= EOF)
     {
           if (isalpha(ch))
            {
               buffer[i] = ch;                         // going to the END OF THE FILE
               i++;
               count++;
            }
            else if (isdigit(ch))                     // If the ch is alpha or not check here
            {
                //  STORE DIGIT ALSO 

                buffer[i] = ch;
                i++;
            }
            else if (is_operator(ch))                    //  this is own written function for oprators checking
            {
                 printf("\n %-10c ---------->Operator\n" , ch);
            }

            else if ( is_symbol(ch))                      // this is also own wriiten function for symbols checking
           {

              printf("\n %-10c -----------> Symbol\n" , ch);

              // here do error check

              // first for {} bracket
            
              if (ch == '{')
                {
                    count2++;        // if one found means cout =1 
                }

              else if ( ch =='}')
               {
                  count2--;    // next found means count = 0;
                
                    if(count2<0)
                     {
                         printf("\nERROR : EXTRA FOUND{}\n");

                        return 0;
                     }
                }

              // chehcking for () this bracket

                 if ( ch== '(')
                 {
                     count3++;
                 }

                 else if (ch == ')')
                 {
                    count3--;                
              
                        if (count3<0)
                          {
                              printf("\n ERROR : EXTRA BRACKET FOUND\n");

                              return 0;
                          }
                 }

                
           }

        // for printing literals and " is not found means put error
        
           else if ( ch == '"')     
          {
              char buffer [20];

              int i=0;

              while ((ch = fgetc(fp)) != '"' && ch!= '\n')
              {
                  buffer[i] = ch;
                  i++;
              }
              buffer[i] ='\0';

              if(ch == '"')
         {
              printf("\n %-10s ---------->LiLterals \n" ,buffer);
         }
         else
         {
            printf("\n EROR : DOUBLE QUOTES   NOT CLOSED PROPERLY\n ");
            return 0;
         }
              // error check
                                         

         }
           else
         {
            if (i>0)              // this condition is for gab like if space came it entre here
            {
              buffer[i] = '\0'; 

              count=0;

              int num;
              num = is_keyword_or_identfire(buffer);

              if ( num ==1)
                {
                   printf("\n %-10s --------> keyword\n" , buffer); 
                   
                   // AFTER PRINTING KEYWORD 

                   // here starting error checkinh part 

                   // CHECK FOR HEXA OCATL BINARY ANA VARAIABE STARTS WITH NUMBERS

                   if(strcmp(buffer,"int") ==0|| strcmp(buffer,"char")==0 || 

                      strcmp(buffer , "float")==0 || strcmp(buffer,"double")==0)    //here check for erros for that numbers in variable
                   {
                       flag =1;   //  set flag
                   }
                }
               else
               {
                    //  ERROR CHECK FIRST 
                    if (flag)
                    {
                        if (!isalpha(buffer[0]) && buffer[0]!= '_')
                        {
                            printf("\n ERROR : THE VARIABLE SHOULD NOT START WITH NUMBERS\n");
                            return 0;
                        }
                        flag = 0;   // reset after checking
                    }

                    // here  i write for hexa binary octal

                        if ( isdigit(buffer[0]))
                        {
                            // may be it is hexa or binary or octal

                            // if it starts with 0x means it is hexa decimal

                            int i =1;

                            int info=0;

                            char ch;

                           if (buffer[0] == '0' && ( buffer[1] == 'x'|| buffer[1]=='X'))
                            {
                                 // it is hexa decimal skip 0x
                                i = 2;

                                // takw while loop and run untill \0 amd check each adn every ch

                                while (buffer[i] != '\0')   
                                {
                                    ch = buffer[i];

                                    if( ( ch >= 'A' && ch <= 'F')|| (ch >= 'a' && ch <= 'f') || (ch >= '0' && ch <= '9'))
                                    {
                                         info =1;  
                                    }
                                    else
                                    {
                                        info =0;
                                        break;
                                    }
                                    i++;
                                    
                                }

                                if(info ==1)
                                {
                                    //printf("\n It is within the range");
                                }
                                else{
                                    printf("\n THE HEXA DECIMAL VALUE SHOULD BE WITHIN 0-9 , A-F , a-f\n");
                                    return 0;
                                }
                            
                            }
                            // what if it is binary

                         else   if (buffer[0] == '0' && buffer[1] == 'b' )
                            {
                                // it is binary

                                i =2;       // because first adn second index are 0 and b

                                while(buffer[i]!= '\0')
                                {
                                    ch = buffer[i];

                                    if ( ch == '1'|| ch =='0')
                                    {
                                        info =1;
                                    }
                                    else
                                    {
                                        info =0;
                                        break;
                                    }
                                    i++;
                                }

                                if ( info ==1)
                                {
                                    // printf("\n no problem\n");
                                }
                                else
                                {
                                    printf("\n ERROR :: THE BINARY NUMBERS SHOULD CONTAIN ONLY 0s AND 1s\n");
                                    return 0;
                                }
                            }

                            // what if it is octal

                            // else if ( buffer[0] == '0' && buffer[1] != 'X' && buffer[1]!= 'x'&& buffer[1] != 'b')

                            else if (buffer[0] == '0' && isdigit(buffer[1]) && buffer[1] != 'x' && buffer[1] != 'X' && buffer[1] != 'b' && buffer[1] != 'B')
                            {
                                //it is octal 
                                i =1;

                                while (buffer[i]!= '\0')
                                {
                                    ch = buffer[i];

                                    if ( ch >= '0' && ch <= '7')
                                    {
                                        info =1;
                                    }
                                    else
                                    {
                                        info=0;
                                        break;
                                    }
                                    i++;
                                }
                                if ( info ==1)
                                {
                                    // no problem 
                                }
                                else
                                {
                                    printf("\n ERROR : THE OCTAL VALUE SHOULD BE WITHIN THE RANGE OF 0 -7\n");
                                    return 0;
                                }
                            }

                            
                        }
                        
                    
                    if (isdigit(buffer[0]))
                    {
                        printf("\n %-10s --------> Numeric constant\n" , buffer);
                    }
                    else
                    {
                        printf("\n %-10s --------> identifire\n" , buffer);  // print identifires
                    }
               }

               i=0;    // reset i value to 0 ..
            }
              // this is checked for () \n is reached means count value check
               if (ch == '\n')
               {
                   if (count3 > 0)
                       {
                              printf("\n ERROR : () NOT CLOSED IN SAME LINE\n");
                              
                                 return 0;
                       }
                     count3 = 0; // reset for next line
                }
        }
     }

        // see here  if inacse another ( not found means count is 1 so , >0 so error come , if both found count = 0 only                                                            

     if (count2>0)
     {
        printf("\nERROR : {} not closed properly\n");
        return 0;
     }

    return SUCCESS;
}