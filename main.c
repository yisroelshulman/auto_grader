#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "File.h"

typedef enum
{
    SUBMIT,
    CHECK,
    PRACTICE,
    HELP,
    ERROR
} OP;

OP get_op(char* op);
OP match_op(char* op, int len, const char *rest, OP type);

int main(int argc, char *argv[])
{

    switch (argc)
    {
        case 1:
            // error
            printf("error no args\n");
            exit(1);
        case 2:
            switch (get_op(argv[1]))
            {
                case HELP:
                    printf("help\n");
                    break;
                default:
                    printf("error\n");
                    break;
            }
            break;
        case 3:
            switch (get_op(argv[1]))
            {
                case SUBMIT:
                {
                    File sourcecode;

                    if (init_file(&sourcecode, argv[2]))
                    {
                        print_file(&sourcecode);
                        printf("compilable\n");
                        compile_file(&sourcecode);
                    }
                    else
                    {
                        print_file(&sourcecode);
                        printf("[%s] can't compile.\n", argv[2]);
                    }
                    printf("submit\n");
                    break;
                }
                case CHECK:
                        printf("check\n");
                        break;
                case HELP:
                        printf("help\n");
                        break;
                default:
                        printf("error\n");
                        break;
            }
            break;
        default:
            switch (get_op(argv[1]))
            {
                case HELP:
                    printf("help\n");
                    break;
                case PRACTICE:
                    printf("practice\n");
                    break;
                default:
                    printf("error\n");
                    break;
            }
            break;
    }
    exit(0);

}

OP match_op(char* op, int len, const char* rest, OP type)
{
    if (memcmp(op + 1, rest, len) == 0) return type;

    return ERROR;
}

OP get_op(char* op)
{
    switch(op[0])
    {
        case 's':   return match_op(op, 6, "ubmit\0", SUBMIT);
        case 'c':   return match_op(op, 5, "heck\0", CHECK);
        case 'p':   return match_op(op, 8, "ractice\0", PRACTICE);
        case 'h':   return match_op(op, 4, "elp\0", HELP);
    }

    return ERROR;
}