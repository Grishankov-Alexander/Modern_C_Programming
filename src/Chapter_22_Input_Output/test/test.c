/*
 * Outline and test chapter concepts.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


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
	 * Character Input/Output
	*/
	{
		/*
		 * Character Input Functions:
		 *
		 * int getc(FILE *stream)
		 * 	Macro to get character from stream
		 * int fgetc(File *stream)
		 * 	Function to get character from stream
		 * int getchar(void)
		 * 	Same as getc(stdin)
		 *
		 * Return character on success.
		 * Return EOF when End-Of-File is reached. Set EOF stream indicator.
		*/


		/*
		 * Character Output Functions:
		 *
		 * int putc(int c, FILE *stream)
		 * 	Macro to output character c to stream.
		 * int fputc(int c, File *stream)
		 * 	Function to output character c to stream
		 * int putchar(int c)
		 * 	Same as putc(c, stdout)
		 * int ungetc(int c, FILE *stream)
		 * 	Put character c back to stream. Clear EOF stream indicator.
		 *
		 * Return c on success.
		 * Return EOF on Error and set stream error indicator.
		*/


		PRINT_TOPIC();

		int c;
		const char *fn = "formatted.txt";
		const char *fn2 = "copy.txt";
		FILE *fp = fopen(fn, "rb");
		FILE *fp2 = fopen(fn2, "wb");

		while ((c = fgetc(fp)) != EOF)
			if (c == fputc(c, fp2))
			{}	// Success

		fclose(fp);
		fclose(fp2);
	}


	/*
	 * Line Input/Output
	*/
	{
		/*
		 * Line Input Functions
		 *
		 * char *gets(char *s)
		 *	Read a line from stdin until \n is encountered.
		 *	Store line with \0 without \n in s.
		 * 	Return s on success.
		 * 	Return NULL on read error. Set StreamError indicator.
		 * 	Return NULL on EOF. Set EOF stream indicator.
		 *
		 * char *fgets(char *s, int n, FILE *stream)
		 *	Read n - 1 characters from stream until \n is encountered.
		 *	Store line with \0 with \n in s.
		 * 	Return s on success.
		 * 	Return NULL on read error. Set StreamError indicator.
		 * 	Return NULL on EOF. Set EOF stream indicator.
		*/


		/*
		 * Line Output Functions
		 *
		 * int puts(const char *s)
		 *	Write s with \n to stdout.
		 *	Return positive integer on success.
		 *	Return EOF on write error. Set StreamError indicator.
		 *
		 * int fputs(const char *s, FILE *stream)
		 *	Write s to stream.
		 *	Return positive integer on success.
		 *	Return EOF on write error. Set StreamError indicator.
		*/

		char line[64];
		const char *fn = "copy.txt";
		FILE *fp = fopen(fn, "a+");

		// Store last line in line
		while (fgets(line, sizeof(line), fp) != NULL)
			;
		// Duplicate last line
		fputs(line, fp);
		fclose(fp);
	}


	/*
	 * Block Input/Output
	*/
	{
		/*
		 * size_t fread(void *dest, size_t szmemb, szie_t nmemb, FILE *stream);
		 * 	Read nmemb objects of size szmemb from stream into dest
		 * 	Return number of objects read.
		 *
		 * size_t fwrite(const void *src, size_t szmemb, szie_t nmemb, FILE *stream);
		 * 	Write nmemb objects of size szmemb from src into stream.
		 * 	Return number of objects written.
		*/


		const char *fn = "backup";
		FILE *fp = fopen(fn, "wb+");
		size_t num_members = 2;

		struct {
			char str[3];
			int i;
		} a[num_members];

		if (fread(a, sizeof(*a), sizeof(a) / sizeof(*a), fp) != num_members) {
			clearerr(fp);
			memcpy(a, "AB\0\0" "C\0\0\0" "DE\0\0" "F\0\0\0", sizeof(a));
			fwrite(a, sizeof(*a), sizeof(a) / sizeof(*a), fp);
		}
	}


	/*
	 * File Positioning
	*/
	{
		/*
		 * int fseek(FILE *stream, long offset, int whence);
		 * 	Change stream File Position to whence + offset.
		 *
		 * 	offset - possibly negative byte count.
		 * 	whence - can have values:
		 * 		1) SEEK_SET - beginning of the file
		 * 		2) SEEK_CUR - current position
		 * 		3) SEEK_END - End of File
		 *
		 * 	Return 0 on success.
		 * 	Return !0 on error.
		 *
		 * 	Examples:
		 * 	fseek(fp, 0L, SEEK_SET)		- Return to the file beginning.
		 * 	fseek(fp, 0L, SEEK_END)		- Return to the file end.
		 * 	fseek(fp, -10L, SEEK_CUR)	- Move back 10 bytes from current position.
		 * 	
		 *
		 * long ftell(FILE *stream);
		 * 	Return current file position.
		 * 	Return -1L on error.
		 *
		 * 	Examples:
		 * 	long file_pos = ftell(fp)	- Save current position
		 * 		...
		 * 	fseek(fp, file_pos, SEEK_SET)	- Return to saved position
		 *
		 *
		 * void rewind(FILE *stream)
		 * 	Clear stream error indicator and set position to the beginning.
		*/


		/*
		 * For handling large files:
		 *
		 * int fgetpos(FILE *stream, fpos_t *pos);
		 * 	Store current position of stream into *pos.
		 * 	Return 0 on success.
		 *
		 * int fsetpos(FILE *stream, const fpos_t *pos);
		 * 	Set position of stream to *pos.
		 * 	Return 0 on success.
		 *
		 * Examples:
		 * 	fpos_t file_pos;
		 * 	fgetpos(fp, &file_pos);
		 * 		...
		 * 	fsetpos(fp, &file_pos);
		*/
	}


	/*
	 * String Input/Output
	*/
	{
		/*
		 * int sprintf(char *s, const char *format, ...)
		 * 	Write format with \0 into s.
		 * 	Return number of characters written.
		 * 	Return negative value on encoding error.
		 *
		 * int snprintf(char *s, size_t n, const char *format, ...)
		 * 	Write n - 1 characters from format into s. Add \0 at the end.
		 * 	Return number of characters written.
		 *	Return negative value on encoding error.
		*/

		/*
		 * int sscanf(const char *s, const char *format, ...)
		 * 	Read formatted input from s.
		 *
		 * 	Return number of items read.
		 * 	Return EOF if not all items were read.
		*/


		char hello[] = "Hello";
		char world[] = "World";
		char s[sizeof(hello) - 1 + sizeof(world) - 1 + 3];

		if (snprintf(s, sizeof(s), "%s, %s", hello, world) == sizeof(s) - 1)
			fprintf(stdout, "%s\n", s);

		if (sscanf(s, "%[^,] %*[, ] %s", hello, world) == 2)
			fprintf(stdout, "%s, %s\n", hello, world);
	}


	/*
	 * Stream Redirection
	*/
	{
		if (freopen("stdoutfile", "w", stdout))
			printf("Redirected stdout to stdoutfile\n");
	}


	return 0;
}
