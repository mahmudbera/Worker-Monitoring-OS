// worker_monitor.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

pthread_mutex_t mutLock;

void *method(void *arg){
	
	char *name = (char *) arg;
	int fd;
	int num1, num2, result, operator;	

	while(1){
		fd = open(name, O_RDONLY);
		read(fd, &num1, sizeof(int));
		close(fd);
		
		pthread_mutex_lock(&mutLock);		
		printf("%d", num1);
		
		fd = open(name, O_RDONLY);
		read(fd, &operator, sizeof(int));
		close(fd);
		
		if (operator == 0){
			printf("+");
		}else if (operator == 1){
			printf("-");
		}else if (operator == 2){
			printf("/");
		}else{
			printf("*");
		}	
		
		fd = open(name, O_RDONLY);
		read(fd, &num2, sizeof(int));
		close(fd);
		printf("%d", num2);

		fd = open(name, O_RDONLY);
		read(fd, &result, sizeof(int));
		close(fd);
		printf("%d", result);

		pthread_mutex_unlock(&mutLock);
			
	}
}

int main() {
    	
	char *adderFifo = "/tmp/adder_pipe";
	char *subtractorFifo = "/tmp/subtractor_pipe";	
	char *dividerFifo = "/tmp/divider_pipe";
	char *multiplierFifo = "/tmp/multiplier_pipe";	

	mkfifo(adderFifo, 0666);
	mkfifo(subtractorFifo, 0666);
	mkfifo(dividerFifo, 0666);
	mkfifo(multiplierFifo, 0666);

	pthread_mutex_init(&mutLock, NULL);	
	    	
	pthread_t adder_tid, subtractor_tid, multiplier_tid, divider_tid;
    	pthread_create(&adder_tid, NULL, method, (void *) adderFifo);
    	pthread_create(&subtractor_tid, NULL, method, (void *) subtractorFifo);
    	pthread_create(&multiplier_tid, NULL, method, (void *) multiplierFifo);
    	pthread_create(&divider_tid, NULL, method, (void *) dividerFifo);
 
    	pthread_join(adder_tid, NULL);
    	pthread_join(subtractor_tid, NULL);
    	pthread_join(multiplier_tid, NULL);
    	pthread_join(divider_tid, NULL);

	pthread_mutex_destroy(&mutLock);

    return 0;
}
