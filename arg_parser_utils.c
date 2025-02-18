#include "arg_parser_utils.h"

static char *get_long_name(char *flag)
{
    char *long_name = calloc(strlen(flag) - 1, sizeof(char));

    for (size_t i = 2; i < strlen(flag); i++)
        long_name[i - 2] = flag[i];
    
    return long_name;
}

static return_type fill_flag_long_name_value(args *args, int argc, char **argv, int pos, char *long_name)
{
    for (size_t i = 0; i < args->nb_args; i++)
    {
        if (args->args[i].long_name && strcmp(args->args[i].long_name, long_name) == 0)
        {
            if (args->args[i].is_used && args->args[i].type != ARG_TYPE_BOOL)
            {
                fprintf(stderr, "parse_args error: multiple definitions of flag '-%c', '--%s'\n", args->args[i].short_name, args->args[i].long_name);
                return MULTIPLE_DEFINITIONS;
            }
            switch (args->args[i].type)
            {
                case ARG_TYPE_BOOL:
                    args->args[i].is_used = true;
                    return OK;
                
                case ARG_TYPE_INT:
                    if (pos + 1 >= argc)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '%s': expected int, got ''\n", argv[pos]);
                        return INVALID_VALUE;
                    }
                    if (!is_int(argv[pos + 1]))
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '%s': expected int, got '%s'\n", argv[pos], argv[pos + 1]);
                        return INVALID_VALUE;
                    }
                    args->args[i].is_used = true;
                    args->args[i].value.i = atoi(argv[pos + 1]);
                    return OK_SKIP;

                case ARG_TYPE_UINT:
                    if (pos + 1 >= argc)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '%s': expected unsigned int, got ''\n", argv[pos]);
                        return INVALID_VALUE;
                    }

                    unsigned res;
                    char *endptr;

                    res = strtoul(argv[pos + 1], &endptr, 10);
                    if (*endptr)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '%s': expected unsigned int, got '%s'\n", argv[pos], argv[pos + 1]);
                        return INVALID_VALUE;
                    }
                    args->args[i].is_used = true;
                    args->args[i].value.ui = res;
                    return OK_SKIP;

                case ARG_TYPE_FLOAT:
                    if (pos + 1 >= argc)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '%s': expected float, got ''\n", argv[pos]);
                        return INVALID_VALUE;
                    }

                    res = strtof(argv[pos + 1], &endptr);
                    if (*endptr)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '%s': expected float, got '%s'\n", argv[pos], argv[pos + 1]);
                        return INVALID_VALUE;
                    }
                    args->args[i].is_used = true;
                    args->args[i].value.f = res;
                    return OK_SKIP;

                case ARG_TYPE_DOUBLE:
                    if (pos + 1 >= argc)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '%s': expected double, got ''\n", argv[pos]);
                        return INVALID_VALUE;
                    }
                    if (!is_float(argv[pos + 1]))
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '%s': expected double, got '%s'\n", argv[pos], argv[pos + 1]);
                        return INVALID_VALUE;
                    }
                    args->args[i].is_used = true;
                    args->args[i].value.d = atof(argv[pos + 1]);
                    return OK_SKIP;

                case ARG_TYPE_STR:
                    if (pos + 1 >= argc)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '%s': expected string, got ''\n", argv[pos]);
                        return INVALID_VALUE;
                    }
                    args->args[i].is_used = true;
                    args->args[i].value.str = strdup(argv[pos + 1]);
                    return OK_SKIP;
            }
        }
    }

    fprintf(stderr, "parse_args error: invalid flag '%s'\n", argv[pos]);
    return INVALID_FLAG;
}

static return_type fill_flag_short_name_value(args *args, int argc, char **argv, int pos, char flag, bool is_last)
{
    for (size_t i = 0; i < args->nb_args; i++)
    {
        if (args->args[i].short_name == flag)
        {
            if (args->args[i].is_used && args->args[i].type != ARG_TYPE_BOOL)
            {
                fprintf(stderr, "parse_args error: multiple definitions of flag '-%c', '--%s'\n", args->args[i].short_name, args->args[i].long_name);
                return MULTIPLE_DEFINITIONS;
            }
            switch (args->args[i].type)
            {
                case ARG_TYPE_BOOL:
                    args->args[i].is_used = true;
                    return OK;
                
                case ARG_TYPE_INT:
                    if (!is_last)
                    {
                        fprintf(stderr, "parse_args error: invalid use of flag '-%c'\n", flag);
                        return INVALID_USE;
                    }
                    if (pos + 1 >= argc)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '-%c': expected int, got ''\n", flag);
                        return INVALID_VALUE;
                    }
                    if (!is_int(argv[pos + 1]))
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '%c': expected int, got '%s'\n", flag, argv[pos + 1]);
                        return INVALID_VALUE;
                    }
                    args->args[i].is_used = true;
                    args->args[i].value.i = atoi(argv[pos + 1]);
                    return OK_SKIP;

                case ARG_TYPE_UINT:
                    if (!is_last)
                    {
                        fprintf(stderr, "parse_args error: invalid use of flag '-%c'\n", flag);
                        return INVALID_USE;
                    }
                    if (pos + 1 >= argc)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '-%c': expected unsigned int, got ''\n", flag);
                        return INVALID_VALUE;
                    }

                    unsigned int res;
                    char *endptr;

                    res = strtoul(argv[pos + 1], &endptr, 10);
                    if (*endptr)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '-%c': expected unsigned int, got '%s'\n", flag, argv[pos + 1]);
                        return INVALID_VALUE;
                    }
                    args->args[i].is_used = true;
                    args->args[i].value.ui = res;
                    return OK_SKIP;

                case ARG_TYPE_FLOAT:
                    if (!is_last)
                    {
                        fprintf(stderr, "parse_args error: invalid use of flag '-%c'\n", flag);
                        return INVALID_USE;
                    }
                    if (pos + 1 >= argc)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '-%c': expected float, got ''\n", flag);
                        return INVALID_VALUE;
                    }

                    res = strtof(argv[pos + 1], &endptr);
                    if (*endptr)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '-%c': expected float, got '%s'\n", flag, argv[pos + 1]);
                        return INVALID_VALUE;
                    }
                    args->args[i].is_used = true;
                    args->args[i].value.f = res;
                    return OK_SKIP;

                case ARG_TYPE_DOUBLE:
                    if (!is_last)
                    {
                        fprintf(stderr, "parse_args error: invalid use of flag '-%c'\n", flag);
                        return INVALID_USE;
                    }
                    if (pos + 1 >= argc)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '-%c': expected double, got ''\n", flag);
                        return INVALID_VALUE;
                    }
                    if (!is_float(argv[pos + 1]))
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '-%c': expected double, got '%s'\n", flag, argv[pos + 1]);
                        return INVALID_VALUE;
                    }
                    args->args[i].is_used = true;
                    args->args[i].value.d = atof(argv[pos + 1]);
                    return OK_SKIP;

                case ARG_TYPE_STR:
                    if (!is_last)
                    {
                        fprintf(stderr, "parse_args error: invalid use of flag '-%c'\n", flag);
                        return INVALID_USE;
                    }
                    if (pos + 1 >= argc)
                    {
                        fprintf(stderr, "parse_args error: invalid value for flag '-%c': expected string, got ''\n", flag);
                        return INVALID_VALUE;
                    }
                    args->args[i].is_used = true;
                    args->args[i].value.str = strdup(argv[pos + 1]);
                    return OK_SKIP;
            }
        }
    }

    fprintf(stderr, "parse_args error: invalid flag '-%c'\n", flag);
    return INVALID_FLAG;
}

return_type fill_flag(args *args, int argc, char **argv, int pos)
{
    if (!args || !argv)
        return INVALID_ARGS;

    char *flag = argv[pos];
    if (flag[0] == '-' && strlen(flag) >= 2)
    {
        // long name
        if (flag[1] == '-')
        {
            char *long_name = get_long_name(flag);
            if (strlen(long_name) < 1)
            {
                fprintf(stderr, "parse_args error: invalid flag '--'\n");
                free(long_name);
                return INVALID_FLAG;
            }

            return_type ret = fill_flag_long_name_value(args, argc, argv, pos, long_name);
            free(long_name);
            return ret;
        }

        // short name
        else
        {
            if (strlen(flag) < 2)
            {
                fprintf(stderr, "parse_args error: invalid flag '-'\n");
                return INVALID_FLAG;
            }
            for (size_t i = 1; i < strlen(flag); i++)
            {
                bool is_last = (i < strlen(flag) - 1 ? false : true);
                return_type ret = fill_flag_short_name_value(args, argc, argv, pos, flag[i], is_last);
                if (ret != OK)
                    return ret;
            }
        }
    }
    else
    {
        fprintf(stderr, "parse_args error: invalid flag '-'\n");
        return INVALID_FLAG;
    }

    return OK;
}

void add_input(args *args, char *input)
{
    args->inputs = realloc(args->inputs, (args->nb_inputs + 2) * sizeof(char *));
    args->inputs[args->nb_inputs] = strdup(input);
    args->nb_inputs += 1;
}