#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char* argv[], char** env) {
	if (argc <= 1) {
	printf("Error! Check arguments!\n");
	return 1;
	}

	DIR *dir;
	struct dirent *dir1;
	dir = opendir(getenv("PWD"));
	if (!dir) {
		printf("Error reading directory\n");
		return 1;
	}
	printf("Current catalogue\n");
	printf("\n");
	while ((dir1 = readdir(dir)) != NULL) {
		printf("%s\n",dir1->d_name);
	}
	closedir(dir);
	printf("\n");
	printf("Selected catalogue\n");
	printf("\n");
	DIR *dir2;
	struct dirent *dir3;
	dir2 = opendir(argv[1]);
	if (!dir2) {
		printf("Error reading catalogue\n");
		return 1;
	}
	while ((dir3 = readdir(dir2)) != NULL) {
		printf("%s\n",dir3->d_name);
	}
	closedir(dir2);
	return 0;
}
