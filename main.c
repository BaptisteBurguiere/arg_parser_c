#include "arg_parser.h"

int main(int argc, char **argv)
{
    args args = init_args();
    add_arg(&args, 't', "test", ARG_TYPE_BOOL);
    add_arg(&args, 't', "test", ARG_TYPE_BOOL);
    parse_args(&args, argc, argv);
    
    destroy_args(args);
}