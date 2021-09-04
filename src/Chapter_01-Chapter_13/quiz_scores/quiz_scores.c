/*
 * Program that computes total and avg score
 * for each student and low, hith, and avg score for each quiz.
*/


#include <stdio.h>


int main(void)
{
	int num_students, num_quizes;
	int i, j;
	int s, low, high;

	printf("Enter number of students: ");
	(void)scanf("%d", &num_students);
	printf("Enter number of quizes: ");
	(void)scanf("%d", &num_quizes);

	int scores[num_students][num_quizes];

	for (i = 0; i < num_students; i++) {
		printf("\nEnter scores for student %d: ", i + 1);
		for (j = 0; j < num_quizes; j++)
			(void)scanf("%d", &scores[i][j]);
	}

	for (i = 0; i < num_students; i++) {
		s = 0;
		for (j = 0; j < num_quizes; j++)
			s += scores[i][j];
		printf("\nStudent %d: Total=%d, Average=%d", i + 1, s, s / j);
	}

	for (j = 0; j < num_quizes; j++) {
		s = 0;
		low = (unsigned) ~0 >> 1;
		high = (unsigned) ~0 >> 1 ^ ~0;
		for (i = 0; i < num_students; i++) {
			s += scores[i][j];
			low = low < scores[i][j] ? low : scores[i][j];
			high = high < scores[i][j] ? scores[i][j] : high;
		}
		printf("\nQuiz %d: Low=%d, High=%d, Avg=%d", j + 1, low, high, s / i);
	}

	printf("\n");

	return 0;
}
