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
	/*
	 * Temporary Files and Names
	*/
	{
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


	/*
	 * File Buffering
	*/
	{
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


	/*
	 * File Removal and Renaming
	*/
	{
		if (remove("./buf"))
			printf("Remove Failed\n");
		if (rename("buffered", "../test/buf"))
			printf("Renaming Failed\n");
	}


	{
		PRINT_TOPIC(fprintf, fscanf);


		FILE *fp;
		const char *fn = "formatted.txt";

		int wrote_total, read_total;
		int wrote_so_far, read_so_far;
		int n1, n2;
		n1 = n2 = 0xABC;

#		define FIELD_WIDTH		6
#		define FIELD_PRECISION		4

		{
			fp = fopen(fn, "w");
			wrote_total = fprintf(	// Return number of characters written
				fp,
				"%#*.*X"	// # - Begin hex numbers with 0X.
						// * - Obtain Field Width and Precision from arguments
				"%n"		// Store number of characters written so far in argument
						// of type int *
				"%*X"
				"\n"
				, FIELD_WIDTH, FIELD_PRECISION, n1
				, & wrote_so_far
				, FIELD_WIDTH, n2
			);
			fprintf(
				fp,
				"wrote_total: %d\n"
				"wrote_so_far: %d\n"
				, wrote_total, wrote_so_far
			);
			fclose(fp);
		}

		{
			char skipped_string[FIELD_WIDTH + 1];

			fp = fopen(fn, "r");
			read_total = fscanf(	// Return number of stored scans
				fp,
				"%*X"		// * - Don't store this scan
				"%[^\n]"	// Scan any character that doesn't belong to the set.
						// (Scan until newline)
				"%n"		// Store number of characters read so far
				" %*13c"	// Skip whitespaces/newlines,
						// scan 13 characters
						// Don't store this scan
				"%2d"		// Scan 2 digits
				, skipped_string
				, &read_so_far
				, &wrote_total
			);
			fprintf(
				stdout,
				"read_total: %d\n"
				"skipped_string: %s\n"
				"read_so_far: %d\n"
				"wrote_total: %d\n"
				, read_total
				, skipped_string
				, read_so_far
				, wrote_total
			);
			fclose(fp);
		}
	}


	/*
	 * File Errors
	*/
	{
		/*
		 * Search a file for a line that begins with an integer.
		 *
		 * Return integer on success
		 * Return error code on FAILURE
		*/
		const char *fn = "formatted.txt";
		FILE *fp;
		int n;

#		define END_OF_FILE	-1
#		define FILE_ERROR	-2
#		define NO_SUCH_FILE	-3


		if (!(fp = fopen(fn, "r"))) {
			n = NO_SUCH_FILE;
			goto ROUTINE_END;
		}

		while (!(fscanf(fp, "%d", &n))) {
			if (ferror(fp)) {
				n = FILE_ERROR;
				goto ROUTINE_END;
			}
			else if (feof(fp)) {
				n = END_OF_FILE;
				goto ROUTINE_END;
			}
			(void) (fscanf(fp, "%*[^\n]") + 1);
		}

		ROUTINE_END:
		if (fp) {
			clearerr(fp);	// Clear End-Of-File and File-Error indicators
			fclose(fp);
		}
	}


	/*
	 * Attaching file to a stream
	*/
	{
		if (freopen("stdoutfile", "w", stdout))
			printf("Redirected stdout to stdoutfile\n");
	}

	return 0;
}
