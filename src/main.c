#include "nm.h"

void print_error(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		print_error("usage: ./ft_nm [file]");
		return (1);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_error("could not open file");

	struct stat buf;
	if (fstat(fd, &buf) == -1)
		print_error("could not stat file");
		
	return (0);
}
