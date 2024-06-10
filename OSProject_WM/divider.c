// divider.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    char *fifo = "/tmp/divider_pipe";
    mkfifo(fifo, 0666);
    int fd;

    while (1) {
        printf("Enter the first number: ");
        int num1;
        scanf("%d", &num1);

	fd = open(fifo, O_WRONLY);        
	write(fd, &num1, sizeof(int));
	close(fd);
		
	int operator = 2;
	fd = open(fifo, O_WRONLY);	
	write(fd, &operator, sizeof(int));	
	close(fd);

        printf("Enter the second number: ");
        int num2;
        scanf("%d", &num2);
	fd = open(fifo, O_WRONLY);        
	write(fd, &num2, sizeof(int));
	close(fd);

	int result = num1 + num2;	
	fd = open(fifo, O_WRONLY);
	write(fd, &result, sizeof(int));
	close(fd);

    }

    close(fd);
    return 0;
}
