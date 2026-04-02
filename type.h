#ifndef TYPE_H

#define TYPE_H

typedef enum
{
    SUCCESS,
    FAILURE
}status;

status for_keyword_identfire(FILE *fp);

int is_keyword_or_identfire( char buffer[]);

void for_digit(int ch);

status error_checking(FILE *fp);


#endif