#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

FILE * fo;
int N1, N2;
int all_count = 0;
int dir_count = 0;

int scanDirectory(char *dirname, int deep){
    if (deep==0)
        return 0;
    DIR *dir;
    struct dirent *ent;
    struct stat buf;

    printf("Read of '%s':\n",dirname);

    if ((dir = opendir(dirname)) == NULL){
        printf("Error reading catalogue\n");
        return 0;
    }
    while ((ent = readdir(dir)) != NULL){
        char* name = malloc(strlen(ent->d_name) + strlen(dirname) + 1);
        strcpy(name, dirname);
        strcat(name, "/");
        strcat(name, ent->d_name);
        stat(name, &buf);
        if ((buf.st_size > N1) && (buf.st_size < N2) || (S_ISDIR(buf.st_mode))) {
            if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
                char s[255];
                s[0] = '\0';
                strcat(s, dirname);
                strcat(s, ent->d_name);
                if (opendir(s) == NULL) {
                    fputs("Path: ", fo);
                    fputs(dirname, fo);
                    fputs(" | ", fo);
                    fputs("File Name: ", fo);
                    fputs(ent->d_name, fo);
                    fputs(" | ", fo);
                    fputs("File Size: ", fo);
                    char size[10000];
                    sprintf(size,"%lld", buf.st_size);
                    fputs(size, fo);
                    fputs("\n", fo);
                } else {
                    strcat(s, "/");
                    scanDirectory(s, deep - 1);
                    dir_count += 1;
                }
            }
        }
        all_count += 1;
    }
    if (closedir(dir) != 0){
        perror("error 2");
    }
    return 0;
}

int main(int argc, char* argv[]){
    if (argc != 5) {
        printf("Error! Check arguments!\n");
        return 1;
    }
    N1 = atoi(argv[2]);
    N2 = atoi(argv[3]);
    fo = fopen(argv[4], "w");
    scanDirectory(argv[1],2);
    fclose(fo);
    printf("File count = %d\n", all_count - dir_count);
    return 0;
}

