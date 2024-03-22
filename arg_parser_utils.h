#ifndef ARG_PARSER_UTILS_H
# define ARG_PARSER_UTILS_H

// Utils for arg parser. do not include in your project

# include "arg_parser.h"

return_type fill_flag(args *args, int argc, char **argv, int pos);
void        add_input(args *args, char *input);

// Checks

bool        is_int(char *val);
bool        is_float(char *val);
bool        is_flag(char *flag);
return_type check_arg(args *args, char short_name, char *long_name);

#endif