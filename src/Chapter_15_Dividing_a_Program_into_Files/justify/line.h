/*
 * Delcarations for working with output lines
*/


#ifndef LINE_H
#define LINE_H


#define LINE_SIZE 60


/* Return number of characters that can fit in the line */
int chars_left(void);


/* Make line an empty string. Return it */
char *clear_line(void);


/* Add word to line. No protection against out-of-bounds */
char *add_word(char *word);


/* Writes justified line to stdout */
void write_justified(void);


/* Writes line as it is to stdout */
void flush_line(void);


#endif /* #ifndef LINE_H */
