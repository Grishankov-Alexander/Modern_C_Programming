/*
 * Justifies output.
 *
 * Use Singly-linked list to store words in a line.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>


#define LINE_SIZE 20 /* 20 chars on the line */


struct node {
	void *data;
	struct node *next;
};


// Adds new node with data to the list. Return list head
struct node *addNode(struct node *list, void *data);

// Return pointer to last node in the list. Null if list is empty
struct node *lastNode(struct node *list);

// Remove all nodes from the list clearing the underlying data
// of each node with freeFunc.
void clearList(struct node *list, void (*freeFunc) (void *));

// Count number of nodes in the list
size_t countNodes(struct node *list);

// Create new string on heap
char *newStr(const char *str);

// Dealloc char *str
void freeString(void *str);

// Writes words from the list to stdout with justification
// with regard to number of empty spaces num_whitespaces.
// Clears the list.
void writeJust(struct node *wordList);

// Writes words from the list to stdout without justification.
// Clears the list.
void writeUnjust(struct node *wordList);


int main(void)
{
	int column;
	int word_i;
	char c;
	char word[LINE_SIZE + 1];
	struct node *wordList;

	column = 0;
	word_i = 0;
	word[word_i] = '\0';
	wordList = NULL;

	for ( ; ; ) {

		c = getchar();
		column++;

		if (c == EOF) {
			writeUnjust(wordList);
			wordList = NULL;
			printf("%s", word);
			return 0;
		}

		else if (isspace(c) && word_i) {
			wordList = addNode(wordList, newStr(word));
			word_i = 0;
			word[word_i] = '\0';
		}

		else if (isspace(c))
			;

		else {
			word[word_i++] = c;
			word[word_i] = '\0';
		}



		if (column == LINE_SIZE)
		{
			writeJust(wordList);
			wordList = NULL;
			column = 0;
		}

		if (strlen(word) == LINE_SIZE) {
			printf("%s\n", word);
			word_i = 0;
			word[word_i] = '\0';
			column = 0;
		}
	}
}


// Adds new node with data to the list. Return list head
struct node *addNode(struct node *list, void *data)
{
	struct node *new, *last;

	new = malloc(sizeof *new);
	new->data = data;
	new->next = NULL;

	last = lastNode(list);

	if (last)
		last->next = new;
	else
		list = new;

	return list;
}


// Return pointer to last node in the list. Null if list is empty
struct node *lastNode(struct node *list)
{
	struct node *last;

	for (last = list; last; last = last->next)
		if (!last->next)
			break;

	return last;
}

// Remove all nodes from the list clearing the underlying data
// of each node with freeFunc.
void clearList(struct node *list, void (*freeFunc) (void *))
{
	struct node *n;

	for ( ; list; list = n) {
		n = list->next;
		freeFunc(list->data);
		free(list);
	}
}


// Create new string on heap
char *newStr(const char *str)
{
	char *heapstr = malloc(strlen(str) + 1);
	strcpy(heapstr, str);
	return heapstr;
}


// free char *
void freeString(void *str)
{
	free(str);
}


// Writes words from the list to stdout with justification
// with regard to number of empty spaces num_whitespaces.
// Clears the list.
void writeJust(struct node *wordList)
{
	struct node *n;
	size_t spaces_to_insert;
	size_t num_words;
	size_t num_whitespaces;
	size_t num_characters = 0;

	for (n = wordList; n; n = n->next) {
		num_characters += strlen((char *) n->data);
	}

	num_whitespaces = LINE_SIZE - num_characters;

	num_words = countNodes(wordList);

	for (n = wordList; n; n = n->next) {
		num_words--;

		printf("%s", (char *) n->data);

		if (num_words) {
			spaces_to_insert = num_whitespaces / num_words;
			while (spaces_to_insert--)
				putchar(' ');
			num_whitespaces -= num_whitespaces / num_words;
		}

		else {
			while (num_whitespaces--)
				putchar(' ');
		}
	}

	if (wordList) putchar('\n');

	clearList(wordList, freeString);
}

// Writes words from the list to stdout without justification.
// Clears the list.
void writeUnjust(struct node *wordList)
{
	struct node *n;

	for (n = wordList; n; n = n->next) {
		printf("%s", (char *) n->data);
		if (n->next)
			printf(" ");
	}

	clearList(wordList, freeString);
}


size_t countNodes(struct node *list)
{
	struct node *n;
	size_t size = 0;

	for (n = list; n; n = n->next)
		size++;

	return size;
}
