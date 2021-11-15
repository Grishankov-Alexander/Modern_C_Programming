/*
 * Outline and test chapter concepts.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


#define PRINT_TOPIC(...)				\
	printf("\n\n" #__VA_ARGS__ "\n==========\n")


int main(int argc, char **argv)
{
	{
		PRINT_TOPIC(Reading filename from program arguments);

		FILE *f;

		if (argc < 2) {
			printf("Usage: ./test filename\n");
			goto SECOND_TOPIC;
		}

		if ((f = fopen(argv[1], "r"))) {
			printf("File \"%s\" exists.\n", argv[1]);
			fclose(f);
		} else
			printf("File \"%s\" does not exist.\n", argv[1]);
	}


SECOND_TOPIC:
	{
		PRINT_TOPIC(Temporary Files and Names);

		FILE *tfp;
		char filename[L_tmpnam];
		char *filename2;

		tfp = tmpfile();
		if (tmpnam(filename))
			fputs(filename, tfp);
		fputs("\n", tfp);
		if ((filename2 = tmpnam(NULL)))
			fputs(filename2, tfp);
	}


	{
		PRINT_TOPIC(File Buffering);

		FILE *fp;
		char *buf;
		char *name;

		buf = malloc(BUFSIZ);
		if (!buf)
			exit(EXIT_FAILURE);

		name = "buffered";
		fp = fopen(name, "w+");
		if (!fp)
			exit(EXIT_FAILURE);

		setvbuf(fp, NULL, _IONBF, 0); // No Buffering
		setvbuf(fp, buf, _IOFBF, BUFSIZ); // Full Buffering

		fputs(name, fp); // Writes to buffer
		fputs("\n", fp);
		if (fflush(fp)) // Writes buffer to file
			printf("Flushing error.\n");
		fclose(fp); // Flushes automatically

		free(buf);
	}


	{
		PRINT_TOPIC(File Removal and Renaming);

		if (remove("./buf"))
			printf("Remove Failed\n");
		if (rename("buffered", "../test/buf"))
			printf("Renaming Failed\n");
	}


	{
		PRINT_TOPIC(Attaching file to a stream);

		if (freopen("stdoutfile", "w", stdout))
			printf("Redirected stdout to stdoutfile\n");
	}

	return 0;
}
