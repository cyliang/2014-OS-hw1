#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAX_CMD_LENGTH 1000
#define MAX_ARGS 100

void cmd();

int main() {
	signal(SIGCHLD, SIG_IGN);

	cmd();
	printf("HHH");
}
void cmd() {
	char cmd[MAX_CMD_LENGTH];
	char *pos;
	char *args[MAX_ARGS] = {NULL};
	int i = 0;
	int pid;
	int need_waiting = 1;

	printf("> ");
	gets(cmd);

	pos = strtok(cmd, " ");
	while(pos != NULL) {
		args[i++] = pos;
		pos = strtok(NULL, " ");
	}
	if(args[i-1][0] == '&') {
		args[i-1] = NULL;
		need_waiting = 0;
	}

	pid = fork();
	if(pid == 0) {
		// Child
		execvp(args[0], args);
	} else {
		// Parent
		int status;
		if(need_waiting)
			waitpid(pid, &status, 0);
	}
}
