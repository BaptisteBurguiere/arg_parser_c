#include "arg_parser.h"
#include "arg_parser_utils.h"

args init_args(void)
{
    args args;
    args.nb_args = 0;
    args.args = calloc(1, sizeof(arg));
    args.nb_inputs = 0;
    args.inputs = calloc(1, sizeof(char *));

    return args;
}

return_type add_arg(args *args, char short_name, char *long_name, arg_type type)
{
    return_type ret = check_arg(args, short_name, long_name);
    if (ret != OK)
        return ret;

    arg new_arg;

    new_arg.short_name = short_name;
    if (long_name)
        new_arg.long_name = strdup(long_name);
    else
        long_name = NULL;
    new_arg.type = type;
    new_arg.is_used = false;

    args->args = realloc(args->args, (args->nb_args + 2) * sizeof(arg));
    args->args[args->nb_args] = new_arg;
    args->nb_args += 1;

    return OK;
}

return_type parse_args(args *args, int argc, char **argv)
{
    if (!args)
        return INVALID_ARGS;

    for (int i = 1; i < argc; i++)
    {
        if (is_flag(argv[i]))
        {
            return_type ret = fill_flag(args, argc, argv, i);
            switch (ret)
            {
                case OK_SKIP:
                    i++;
                    break;
                case OK:
                    break;
                default:
                    return ret;
            }
        }
        else
            add_input(args, argv[i]);
    }

    return OK;
}

void *get_arg_value(args *args, char short_name)
{
    if (!args)
    {
        fprintf(stderr, "get_arg_value error: args is NULL\n");
        return NULL;
    }
    for (size_t i = 0; i < args->nb_args; i++)
    {
        if (args->args[i].short_name == short_name)
        {
            if (!args->args[i].is_used)
                return NULL;
            
            switch (args->args[i].type)
            {
                case ARG_TYPE_BOOL:;
                    bool *retb = calloc(1, sizeof(bool));
                    *retb = true;
                    return retb;
                
                case ARG_TYPE_INT:;
                    int *reti = calloc(1,sizeof(int));
                    *reti = args->args[i].value.i;
                    return reti;

                case ARG_TYPE_UINT:;
                    unsigned int *retui = calloc(1,sizeof(unsigned int));
                    *retui = args->args[i].value.ui;
                    return retui;

                case ARG_TYPE_FLOAT:;
                    float *retf = calloc(1,sizeof(float));
                    *retf = args->args[i].value.f;
                    return retf;

                case ARG_TYPE_DOUBLE:;
                    double *retd = calloc(1,sizeof(double));
                    *retd = args->args[i].value.d;
                    return retd;

                case ARG_TYPE_STR:;
                    char *rets = strdup(args->args[i].value.str);
                    return rets;
            }
        }
    }
    
    fprintf(stderr, "get_arg_value error: flag '-%c' undefined", short_name);
    return NULL;
}

void destroy_args(args args)
{
    for (size_t i = 0; i < args.nb_args; i++)
    {
        free(args.args[i].long_name);
        if (args.args[i].type == ARG_TYPE_STR && args.args[i].is_used)
            free(args.args[i].value.str);
    }
    free(args.args);

    for (size_t i = 0; i < args.nb_inputs; i++)
        free(args.inputs[i]);
    free(args.inputs);
}