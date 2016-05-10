#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <io.h> 
#include <corecrt_io.h>

#pragma warning(disable:4996)
typedef struct _finddata_t  FILE_SEARCH;
void ls();
void cd(char *command);
void all();
void cls();
void cd_command_cut(char command[100]);
char *replaceAll(char *s, const char *olds, const char *news);
int isFileOrDir(char* s);

char strBuffer[_MAX_PATH] = { 0 };
char *pstrBuffer = NULL;


void main() {
	
	char command[100];
	const char exit[] = "exit ";
	const char cols[] = "ls ";
	const char cocd[] = "cd ";
	const char coall[] = "all";
	const char cocls[] = "cls";

	while (1) {
		pstrBuffer = getcwd(strBuffer, _MAX_PATH);

		printf("%s :", pstrBuffer);
		fgets(command, sizeof(command), stdin);
		if (strncmp(command,exit,4)==0) break;
		else if (strncmp(command, cols, 2) == 0) ls();
		else if (strncmp(command, cocd, 2) == 0) {
			if(strncmp(command, cocd, 3) == 0)	cd(command);
			else printf("cd \"파일의 경로\"를 입력 해 주세요!\n");
		}
		else if (strncmp(command, coall, 3) == 0) all();
		else if (strncmp(command, cocls, 3) == 0) cls();
	}

	
}
void ls() {
	long h_file;
	FILE_SEARCH file_search;
	char search_Path[100] = ".\\*.*";
	char txt[] = "";
	char *test = NULL;
	int i = 0;
	if ((h_file = _findfirst(search_Path, &file_search)) == -1L) {
		printf("No files in current directory!\n");
		exit(1);
	}
	do {
		if (strstr(file_search.name, txt)) {
			//strcpy(test, file_search.name);
			//i = isFileOrDir(file_search.name);
			if (file_search.attrib == 16) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				puts(file_search.name);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else {
				puts(file_search.name);
			}	
		}

	} while (_findnext(h_file, &file_search) == 0);
}

void cd(char *command) {
	char cut[] = " ";
	char end[] = "";
	
	char *command_cut = NULL;
	if (strcmp(command, "cd") == 0) {
		printf("cd \"파일의 경로\"를 입력 해 주세요!\n");
		return;
	}
	command_cut = strtok(command, cut);
	while (command_cut != NULL) {
		command_cut = strtok(NULL, end);
		if (command_cut != NULL) break;
	}

	pstrBuffer = getcwd(strBuffer, _MAX_PATH);
	char cd_command[100];
	strcpy(cd_command, pstrBuffer);
	strcat(cd_command, "\\");
	strcat(cd_command,command_cut);
	
	char chang[100];
	char *ch = replaceAll(cd_command, "\\", "\\\\");
	strcpy(cd_command, ch);

	cd_command[strlen(cd_command) - 1] = '\0';
	
	int error_check = chdir((char*)cd_command);
	if (error_check == -1) {
		printf("존재하지 않는 폴더 또는 파일입니다.\n");
		return;
	}
}
void all() {

}
void cls() {
	system("cls");
}
char *replaceAll(char *s, const char *olds, const char *news) {
	char *result;
	char *sr;
	size_t i, count = 0;
	size_t oldlen = strlen(olds); if (oldlen < 1) return s;
	size_t newlen = strlen(news);

	if (newlen != oldlen) {
		for (i = 0; s[i] != '\0';) {
			if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
			else i++;
		}
	}
	else i = strlen(s);


	result = (char *)malloc(i + 1 + count * (newlen - oldlen));
	if (result == NULL) return NULL;


	sr = result;
	while (*s) {
		if (memcmp(s, olds, oldlen) == 0) {
			memcpy(sr, news, newlen);
			sr += newlen;
			s += oldlen;
		}
		else *sr++ = *s++;
	}
	*sr = '\0';

	return result;
}
int isFileOrDir(char* s) {
	
}