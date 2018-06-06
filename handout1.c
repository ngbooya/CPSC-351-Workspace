#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	/*fork();
	fork();
	fork();
	fprintf(stderr, "Hello\n");*/

	pid_t pid = fork();
	if(pid == 0){
		fprintf(stderr, "I will take a 100 second nap!");
		sleep(100);

		fprintf(stderr, "I am awake! Bye now.");
		exit(0);
	}else{
		exit(1);
	}

}
