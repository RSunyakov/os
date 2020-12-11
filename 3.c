#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int mygetch() {
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~ (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getc(stdin);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		printf("Error, check arguments\n");
		return 1;
	}
	printf("Enter symbols; End: CTRL+F\n");
	int letter;
	FILE * fo;
	fo = fopen(argv[1], "w");
	if (fo == NULL) {
		printf("Error working with file");
		return 1;
	}
	while (letter != 6) {
		letter = mygetch();
		if ((letter != 6))
		putc(letter, fo);
		putc(letter, stdout);
	}
	fclose(fo);
	printf("\n");
	return 0;
	}	
