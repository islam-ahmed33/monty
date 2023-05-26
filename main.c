#include "monty.h"
bus_t bus = {NULL, NULL, NULL, 0};
/**
 * getline - Read a line from a file.
 * @lineptr: Pointer to the buffer storing the read line.
 * @n: Pointer to the size of the buffer.
 * @stream: File stream to read from.
 *
 * Return: The number of characters read, or -1 on failure or end of file.
 */

ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
        size_t bufsize = 0;
        size_t chars_read = 0;
        int c;
	char *newptr;

        if (lineptr == NULL || n == NULL || stream == NULL)
        {
                return (-1);
        }

        if (*lineptr == NULL || *n == 0)
        {
                bufsize = 128;
                *lineptr = (char *)malloc(bufsize);
                if (*lineptr == NULL)
                {
                        return (-1);
                }
                *n = bufsize;
        }

        while ((c = getc(stream)) != EOF)
        {
                if (chars_read >= *n - 1)
                {
                        bufsize *= 2;
                        newptr = (char *)realloc(*lineptr, bufsize);
                        if (newptr == NULL)
                        {
                                return (-1);
                        }
                        *lineptr = newptr;
                        *n = bufsize;
                }
                (*lineptr)[chars_read++] = (char)c;

                if (c == '\n')
                {
                        break;
                }
	   }

        if (chars_read == 0)
        {
                return (-1);
        }

        (*lineptr)[chars_read] = '\0';

        return (chars_read);
}

/**
* main - monty code interpreter
* @argc: number of arguments
* @argv: monty file location
* Return: 0 on success
*/
int main(int argc, char *argv[])
{
	char *content;
	FILE *file;
	size_t size = 0;
	ssize_t read_line = 1;
	stack_t *stack = NULL;
	unsigned int counter = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	bus.file = file;
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (read_line > 0)
	{
		content = NULL;
		read_line = getline(&content, &size, file);
		bus.content = content;
		counter++;
		if (read_line > 0)
		{
			execute(content, &stack, counter, file);
		}
		free(content);
	}
	free_stack(stack);
	fclose(file);
return (0);
}
