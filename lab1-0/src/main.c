#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define K 4
#define SIZE (2 << K)

struct RingBuffer
{
	unsigned int write_count;
	unsigned int mask; //mask = 2^k - 1
	char *data;
};

static void write(struct RingBuffer *buff, const char *value, int len_value);

static void write(struct RingBuffer *buff, const char *value, int len_value)
{
	for (int i = 0; i < len_value; ++i)
	{
		buff->data[buff->write_count & buff->mask] = value[i];
		++buff->write_count;
	}
}

static char get_elem(const struct RingBuffer *buff, unsigned int i);

static char get_elem(const struct RingBuffer *buff, unsigned int i)
{
	return buff->data[i & buff->mask];
}

static void check_null(void *ptr)
{
	if (ptr == NULL)
	{
		perror("No memory");
		exit(EXIT_FAILURE);
	}
}

static void constructor(struct RingBuffer *buff)
{
	buff->write_count = 0;
	buff->mask = SIZE - 1;
	buff->data = malloc(sizeof(char) * SIZE);
	check_null(buff->data);
}

static void check_read(int read_len)
{
	if (read_len == 0)
	{
		perror("Cannot read search pattern");
		exit(EXIT_FAILURE);
	}
}

int main()
{
	char *pattern = malloc(sizeof(char) * 17);
	check_null(pattern);
	check_read(scanf("%16[^\n]%*c", pattern));
	size_t len = strlen(pattern);
	unsigned int *p = malloc(sizeof(unsigned int) * 256); //table of shifts
	check_null(p);
	for (int i = 0; i < 256; ++i)
	{
		p[i] = (unsigned int) len;
	}
	unsigned int *d = p + 128; //table shifts with negative number
	for (unsigned int i = 0; i + 1 < len; ++i)
	{
		if (d[(int) pattern[i]] + i + 1 > len)
		{
			d[(int) pattern[i]] = (unsigned int) len - i - 1; //constructing table of shifts
		}
	}
	struct RingBuffer buffer;
	constructor(&buffer);

	unsigned int pos = (unsigned int) len - 1; //position of pattern`s last symbol in text

	char *symbols = malloc(sizeof(char) * 17); //part text
	check_null(symbols);

	size_t read_symbols_count = fread(symbols, sizeof(char), (size_t) (pos - buffer.write_count) + 1, stdin);
	write(&buffer, symbols, (int) read_symbols_count);

	while (read_symbols_count != 0 && pos < buffer.write_count)
	{
	    unsigned int concurrences = 0;
		while (len >= concurrences + 1 && get_elem(&buffer, pos - concurrences) == pattern[len - concurrences - 1])
		{
			printf("%u ", pos - concurrences + 1);
			++concurrences;
		}
		if (concurrences != len)
		{
			printf("%u ", pos - concurrences + 1);
		}

		pos += d[(int) get_elem(&buffer, pos)];

		if (pos >= buffer.write_count)
		{
			read_symbols_count = fread(symbols, sizeof(char), (size_t) (pos - buffer.write_count) + 1, stdin);
			write(&buffer, symbols, (int) read_symbols_count);
		}
	}
	printf("\n");
	free(pattern);
	free(p);
	free(buffer.data);
	free(symbols);
	return 0;
}
