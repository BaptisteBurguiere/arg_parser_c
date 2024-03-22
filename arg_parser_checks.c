#include "arg_parser_utils.h"

bool is_int(char *val)
{
    if (!val)
        return false;

    size_t i = 0;
    if (val[0] == '-')
        i++;
    
    while (i < strlen(val))
    {
        if (!isdigit(val[i]))
            return false;
        i++;
    }
    return true;
}

bool is_float(char *val)
{
    if (!val)
        return false;
    
    bool dot = false;
    for (size_t i = 0; i < strlen(val); i++)
    {
        if (!isdigit(val[i]))
        {
            if (val[i] == '.' && !dot)
                dot = true;
            else
                return false;
        }
    }
    return true;
}

bool is_flag(char *flag)
{
    if (!flag)
        return false;

    if (flag[0] == '-')
        return true;
    return false;
}

return_type check_arg(args *args, char short_name, char *long_name)
{
    if (!args)
    {
        fprintf(stderr, "add_arg error: args is NULL\n");
        return INVALID_ARGS;
    }
    if (!isalpha(short_name))
    {
        fprintf(stderr, "add_arg error: short_name is not digit\n");
        return INVALID_SHORT_NAME;
    }
    if (long_name && strlen(long_name) < 1)
    {
        fprintf(stderr, "add_arg error: long_name must be NULL or >= 1 character long\n");
        return INVALID_LONG_NAME;
    }

    for (size_t i = 0; i < args->nb_args; i++)
    {
        if (args->args[i].short_name == short_name)
        {
            fprintf(stderr, "add_arg error: multiple definitions for short_name '-%c'\n", short_name);
            return MULTIPLE_DEFINITIONS;
        }
        else if (strcmp(args->args[i].long_name, long_name) == 0)
        {
            fprintf(stderr, "add_arg error: multiple definitions for long_name '--%s'\n", long_name);
            return MULTIPLE_DEFINITIONS;
        }
    }

    return OK;
}