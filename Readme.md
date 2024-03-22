# Arg parser for C

Simple argument parser for your projects in C.

## Installation

At the root of your project:

```bash
git clone git@github.com:BaptisteBurguiere/arg_parser_c.git
```

Go in the parser directory and Make:

```bash
cd arg_parser_c
make
```

## Include the library to your project

Add flags to the compilation:

```bash
<CC> -Iarg_parser_c -Larg_parser_c -larg_parser <SRCS> -o <OUTPUT_FILE>
```

Add the header in your file:

```c
#include <arg_parser.h>
```

## Usage

Types:

```c
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
```

Functions description:

```c
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
```

## Example

```c
#include <arg_parser.h>

int main(int argc, char **argv)
{
	args args = init_args();

	add_arg(&args, 'b', "bool", ARG_TYPE_BOOL);
	add_arg(&args, 'i', "int", ARG_TYPE_INT);
	add_arg(&args, 'u', "uint", ARG_TYPE_UINT);
	add_arg(&args, 'f', "float", ARG_TYPE_FLOAT);
	add_arg(&args, 'd', "double", ARG_TYPE_DOUBLE);
	add_arg(&args, 's', "string", ARG_TYPE_STR);

	parse_args(&args, argc, argv);

	void *val;

	if (!(val = get_arg_value(&args, 'b')))
		printf("flag '-b' not used\n");
	else
		printf("flag '-b': true\n");
	free(val);
	
	if (!(val = get_arg_value(&args, 'i')))
		printf("flag '-i' not used\n");
	else
		printf("flag '-i': %d\n", *((int *)val));
	free(val);
	
	if (!(val = get_arg_value(&args, 'u')))
		printf("flag '-u' not used\n");
	else
		printf("flag '-u': %u\n", *((unsigned int *)val));
	free(val);
	
	if (!(val = get_arg_value(&args, 'f')))
		printf("flag '-f' not used\n");
	else
		printf("flag '-f': %f\n", *((float *)val));
	free(val);
	
	if (!(val = get_arg_value(&args, 'd')))
		printf("flag '-d' not used\n");
	else
		printf("flag '-d': %lf\n", *((double *)val));
	free(val);
	
	if (!(val = get_arg_value(&args, 's')))
		printf("flag '-s' not used\n");
	else
		printf("flag '-s': %s\n", (char *)val);
	free(val);

	destroy_args(args);
}
```

```bash
./a.out -b --int 45 -s "test test"
```

Output:

```
flag '-b': true
flag '-i': 45
flag '-u' not used
flag '-f' not used
flag '-d' not used
flag '-s': test test
```

You can access the program input with args.inputs:

```c
#include <arg_parser.h>

int main(int argc, char **argv)
{
	args args = init_args();

	add_arg(&args, 'b', "bool", ARG_TYPE_BOOL);
	add_arg(&args, 'i', "int", ARG_TYPE_INT);
	add_arg(&args, 'u', "uint", ARG_TYPE_UINT);
	add_arg(&args, 'f', "float", ARG_TYPE_FLOAT);
	add_arg(&args, 'd', "double", ARG_TYPE_DOUBLE);
	add_arg(&args, 's', "string", ARG_TYPE_STR);

	parse_args(&args, argc, argv);

	void *val;

	if (!(val = get_arg_value(&args, 'b')))
		printf("flag '-b' not used\n");
	else
		printf("flag '-b': true\n");
	free(val);
	
	if (!(val = get_arg_value(&args, 'i')))
		printf("flag '-i' not used\n");
	else
		printf("flag '-i': %d\n", *((int *)val));
	free(val);
	
	if (!(val = get_arg_value(&args, 'u')))
		printf("flag '-u' not used\n");
	else
		printf("flag '-u': %u\n", *((unsigned int *)val));
	free(val);
	
	if (!(val = get_arg_value(&args, 'f')))
		printf("flag '-f' not used\n");
	else
		printf("flag '-f': %f\n", *((float *)val));
	free(val);
	
	if (!(val = get_arg_value(&args, 'd')))
		printf("flag '-d' not used\n");
	else
		printf("flag '-d': %lf\n", *((double *)val));
	free(val);
	
	if (!(val = get_arg_value(&args, 's')))
		printf("flag '-s' not used\n");
	else
		printf("flag '-s': %s\n", (char *)val);
	free(val);
	
	for (size_t i = 0; i < args.nb_inputs; i++)
		printf("%s\n", args.inputs[i]);

	destroy_args(args);
}
```

```c
./a.out -b input1 --int 45 input2 -s "test test" input3 input4
```

Output:

```
flag '-b': true
flag '-i': 45
flag '-u' not used
flag '-f' not used
flag '-d' not used
flag '-s': test test
input1
input2
input3
input4
```