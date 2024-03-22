#include "arg_parser.h"

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