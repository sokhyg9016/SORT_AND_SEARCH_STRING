#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 50

//is equal to 'char** dec', when compile the function argument, compiler converts 'TYPE[]' to 'TYPE*'.
//So, 'char* dec[]' is converts to 'char** dec'.
//*it is 'decay'.

int binary_search(char* dec[], int left, int right, const char* x);
void clear_buffer();
void Error(const char* message);
int compare(const void* v1, const void* v2);
int read_line(char* str, int n);

int main()
{
	char** dec = NULL;
	char str[MAX_SIZE];
	int N, i, result;

	fputs("INPUT: ", stdout);
	
	if (scanf_s("%d", &N) == 1)
	{
		//Remove Enter
		clear_buffer();

		dec = (char**)malloc(sizeof(char*) * N);

		//Allocate space to store string and store string.
		for (i = 0; i < N; i++)
		{
			dec[i] = (char*)malloc(sizeof(char*) * MAX_SIZE);
			read_line(str, MAX_SIZE);
			strcpy_s(dec[i], MAX_SIZE, str);
		}

		//Quick Sort
		qsort((void*)dec, (size_t)N, sizeof(char*), compare);

		//Print the items after sorting.
		for (i = 0; i < N; i++)
		{
			printf("[%02d] = \'%s\'\n", i, dec[i]);
		}

		//Find the string that user inputed.
		read_line(str, MAX_SIZE);
		result = binary_search(dec, 0, N, str);

		if (result != -1)
			printf("binary_test:: dec[%d] = \"%s\"\n", result, dec[result]);
		else
			printf("no contents in directory.\n");

		
		for (i = 0; i < N; i++)
		{
			free(dec[i]);
		}
		free(dec);
	}
	else
	{
		Error("INPUT Error\n");
	}

	return 0;
}

int binary_search(char* dec[], int left, int right, const char* x)
{
	while (right >= 1)
	{
		int mid = (left + right) / 2;

		int result = strcmp(dec[mid], x);

		if (!result)
		{
			return mid;
		}
		else if (result > 0)
		{
			return binary_search(dec, left, mid - 1, x);
		}
		else
		{
			return binary_search(dec, mid + 1, right, x);
		}
	}
	return -1;
}

void clear_buffer()
{
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

void Error(const char* message)
{
	fprintf(stderr, message);
	exit(1);
}

int compare(const void* v1, const void* v2)
{
	return strcmp(*(char**)v1, *(char**)v2);
}

int read_line(char* str, int n)
{
	char ch;
	int i;

	i = 0;

	fputs("INPUT: ", stdout); 
	while ((ch = getchar()) != '\n')
	{
		if (i < n)
		{
			str[i++] = ch;
		}
	}
	str[i] = '\0';

	return i;
}