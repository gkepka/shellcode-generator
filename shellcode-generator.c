#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <inttypes.h>

#define BUFFER_SIZE 4096

void usage(char *progname, int exit_status)
{
	printf("Usage: %s [options]\n", progname);
	puts("-f <File> Use File as an input instead of stdin");
	puts("-o <File> Redirect output to File");
	puts("-h Prints this help and exits");
	exit(exit_status);
}

void print_string(FILE *in_file, FILE *out_file)
{
	uint8_t buf[BUFFER_SIZE];
	size_t read;
	bool end = false;
	uint8_t c;
	while (!end) {
		read = fread((void *)buf, sizeof(int8_t), BUFFER_SIZE, in_file);
		if (read < sizeof(int8_t) * BUFFER_SIZE) {
			if (ferror(in_file)) {
				puts("Error occured while reading input\n");
				fclose(in_file);
				fclose(out_file);
				exit(EXIT_FAILURE);
			} else {
				end = true;
			}
		}
		for (unsigned int i = 0; i < read; i++) {
			c = buf[i];
			fprintf(out_file, "\\x%" PRIx8 , c);
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

	while ((opt = getopt(argc, argv, "f:o:")) != -1) {
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
	print_string(in_file, out_file);
	fclose(in_file);
	fclose(out_file);
	return EXIT_SUCCESS;
}
