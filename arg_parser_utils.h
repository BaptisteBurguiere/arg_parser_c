#ifndef ARG_PARSER_UTILS_H
# define ARG_PARSER_UTILS_H

// Utils for arg parser. do not include in your project

# include "arg_parser.h"

bool        is_flag(char *flag);
return_type fill_flag(args *args, int argc, char **argv, int pos);
return_type fill_flag_long_name_value(args *args, int argc, char **argv, int pos, char *long_name);
char        *get_long_name(char *flag);
void        add_input(args *args, char *input);
return_type check_arg(args *args, char short_name, char *long_name);

#endif