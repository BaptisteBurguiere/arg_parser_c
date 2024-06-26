#ifndef ARG_PARSER_H
# define ARG_PARSER_H

// Main header file to include in projects

# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <ctype.h>

// Return types of some functions to manage errors
typedef enum return_type
{
    OK,
    OK_SKIP,
    ERROR,
    INVALID_ARGS,
    INVALID_FLAG,
    INVALID_SHORT_NAME,
    INVALID_LONG_NAME,
    INVALID_VALUE,
    MULTIPLE_DEFINITIONS,
    INVALID_USE,
}   return_type;

// All types for defining a flag
// Note: If a type you need is not defined, use ARG_TYPE_STR to get the raw
//       input and manage it later
typedef enum arg_type
{
    ARG_TYPE_BOOL,
    ARG_TYPE_INT,
    ARG_TYPE_UINT,
    ARG_TYPE_FLOAT,
    ARG_TYPE_DOUBLE,
    ARG_TYPE_STR
}   arg_type;

typedef struct arg
{
    char        short_name;
    char        *long_name;
    arg_type    type;
    bool        is_used;
    union
    {
        int             i;
        unsigned int    ui;
        float           f;
        double          d;
        char            *str;
    }           value;
}   arg;

typedef struct args
{
    arg     *args;
    size_t  nb_args;
    char    **inputs;
    size_t  nb_inputs;
}   args;


// Returns a new instance of args
args        init_args(void);

// Add a flag definition
return_type add_arg(args *args, char short_name, char *long_name, arg_type type);

// Start parsing the programm input to fill args with flags and inputs
return_type parse_args(args *args, int argc, char **argv);

// Returns a pointer to a copy of the value. NULL if the flag is not used.
// Cast the result to the correct type to use.
void        *get_arg_value(args *args, char short_name);

// Free args
void        destroy_args(args args);



#endif