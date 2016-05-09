#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <io.h> 

#pragma warning(disable:4996)
typedef struct _finddata_t  FILE_SEARCH;
void ls();
void cd(char *command);
void all();
void cls();
void cd_command_cut(char command[100]);


char strBuffer[_MAX_PATH] = { 0 };
char *pstrBuffer = NULL;

void main() {
	
	char command[100];
	const char exit[] = "exit";
	const char cols[] = "ls";
	const char cocd[] = "cd";
	const char coall[] = "all";
	const char cocls[] = "cls";

	while (1) {
		pstrBuffer = getcwd(strBuffer, _MAX_PATH);

		printf("%s :", pstrBuffer);
		fgets(command, sizeof(command), stdin);
		if (strncmp(command,exit,4)==0) break;
		else if (strncmp(command, cols, 2) == 0) ls();
		else if (strncmp(command, cocd, 2) == 0) cd(command);
		else if (strncmp(command, coall, 3) == 0) all();
		else if (strncmp(command, cocls, 3) == 0) cls();
	}

	
}
void ls() {
	long h_file;
	FILE_SEARCH file_search;
	char search_Path[100] = ".\\*.*";
	char txt[] = "";

	if ((h_file = _findfirst(search_Path, &file_search)) == -1L) {
		printf("No files in current directory!\n");
		exit(1);
	}
	do {
		if (strstr(file_search.name, txt)) {
			puts(file_search.name);
		}

	} while (_findnext(h_file, &file_search) == 0);
}

void cd(char *command) {
	char cut[] = " ";
	char end[] = "";
	char *command_cut = NULL;
	command_cut = strtok(command, cut);
	printf("a:%s\n", command_cut);
	while (command_cut != NULL) {
		puts(command_cut);
		command_cut = strtok(NULL, end);
		if (command_cut != NULL) break;
	}
	printf("command: %s\n", command_cut);
	pstrBuffer = getcwd(strBuffer, _MAX_PATH);
	char cd_command[100];// = { pstrBuffer };
	strcpy(cd_command, pstrBuffer);
	strcat(cd_command, "\\");
	strcat(cd_command,command_cut);
	puts(cd_command);
	char strChangeDir[_MAX_PATH] = {command};
	int error_check = chdir(strChangeDir);
	if (error_check == -1) {
		printf("오류 발생\n");
		exit(1);
	}
}
void all() {

}
void cls() {
	system("cls");
}