#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_LINE 128

void usage(char *progname, int exit_status)
{
	printf("Usage: %s [options]\n", progname);
	puts("-f <in_file> Use in_file as an input instead of stdin");
	puts("-o <out_file> Redirect output to out_file");
	puts("-h Prints this help and exits");
	exit(exit_status);
}

void get_opcode(char *buf)
{
	if (buf[0] != ' ') {
		buf[0] = '\0';
		return;
	}
	int i = 1, j = 0;
	while (i < MAX_LINE && buf[i] != '\0' && buf[i] != '\t')
		i++;
	if (buf[i] == '\0') {
		buf[0] = '\0';
		return;
	}
	i++;
	while (i+1 < MAX_LINE && !(isspace(buf[i]) && isspace(buf[i+1]))) {
		if (isspace(buf[i])) {
			i++;
		} else {
			buf[j] = buf[i];
			j++;
			i++;
		}
	}
	buf[j] = '\0';
}

void print_output(FILE *in_file, FILE *out_file)
{
	char buf[MAX_LINE];
	char *s;
	int i;
	while (1) {
		s = fgets(buf, MAX_LINE, in_file);
		if (s != buf) {
			if (ferror(in_file)) {
				puts("Error occured while reading input\n");
				fclose(in_file);
				fclose(out_file);
				exit(EXIT_FAILURE);
			} else {
				break;
			}
		}
		get_opcode(buf);
		i = 0;
		while (i+1 < MAX_LINE && buf[i] != '\0') {
			fprintf(out_file, "\\x%c%c", buf[i], buf[i+1]);
			i += 2;
		}
	}
}

int main(int argc, char *argv[])
{
	char opt;
	char *in_path = NULL;
	char *out_path = NULL;
	FILE *in_file;
	FILE *out_file;
	opterr = 0;

	while ((opt = getopt(argc, argv, "hf:o:")) != -1) {
		switch (opt) {
		case 'f' :
			in_path = optarg;
			break;
		case 'o' :
			out_path= optarg;
			break;
		case 'h' :
			usage(argv[0], EXIT_SUCCESS);
			break;
		default :
			usage(argv[0], EXIT_FAILURE);
		}
	}
	if (argv[optind])
		usage(argv[0], EXIT_FAILURE);

	if ((in_file = fopen(in_path, "r")) == NULL)
		in_file = stdin;
	if ((out_file = fopen(out_path, "w")) == NULL) {
		if (!out_path) {
			out_file = stdout;
		} else {
			puts("Couldn't open file for write\n");
			exit(EXIT_FAILURE);
		}
	}
	print_output(in_file, out_file);
	fclose(in_file);
	fclose(out_file);
	return EXIT_SUCCESS;
}
