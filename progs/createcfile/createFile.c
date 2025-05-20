#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
	if (argc != 3){
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0664);

	if (fd == -1){
		perror("open");
		exit(EXIT_FAILURE);
	}
	
	char content[] = "#include <stdio.h>\nint main(int argc, char *argv){\nprintf(\"Hello World\");\nreturn 0;\n}\n";
	
	if(write(fd, content, sizeof(content) - 1)==-1){
		perror("write");
		exit(EXIT_FAILURE);
	}
	
	

	
	


	if(close(fd) == -1){
		perror("close");
		exit(EXIT_FAILURE);
	}

	char *cmd = (char*)malloc(sizeof("gcc -o") + sizeof(argv[1])/
				sizeof(argv[2]) - 2); // -2 for removing extra null characters
	sprintf(cmd, "gcc %s -o %s", argv[1], argv[2]);	
	

	if (system(cmd) == -1){
		perror("system");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
