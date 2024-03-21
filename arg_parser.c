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