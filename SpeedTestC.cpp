
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable : 4996)
#define SIZESTR 2000
#define SIZEWORD 500
#define SIZELST 1000000

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE* mf;
	FILE* file;
	file = fopen("Output.txt", "w");
	char str[SIZESTR];
	char word[SIZEWORD];
	char* showlst;
	char* lstlast;
	lstlast = (char*)malloc(SIZEWORD * SIZELST);
	showlst = lstlast;
	int countlst = 0;
	DWORD timeStart = timeGetTime();
	int count = 0;
	mf = fopen("Война и мир mini.txt", "r");
	char* estr;
	while ((estr = fgets(str, SIZESTR, mf)) != NULL) {
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] != ' ' && str[i]!=0 && str[i]!='\n') {
				word[count++] = tolower(str[i]);
				
			}
			else {
				word[count] = 0;
				int countclean = 0;
				char wordclean[SIZEWORD];
				wordclean[countclean] = 0;
				for (int y = 0; y < count; y++) {
					if (!(word[y] == ' '
						||word[y] == ','
						|| word[y] == ':'
						|| word[y] == ';'
						|| word[y] == '!'
						|| word[y] == '?'
						|| word[y] == '('
						|| word[y] == ')'
						|| word[y] == '-'
						|| word[y] == '—'
						|| word[y] == 0x09
						|| word[y] == '.')) {
						wordclean[countclean++] = word[y];
					}
				}
				wordclean[countclean] = 0;
				if (strlen(wordclean) != 0) {
					strcpy(lstlast, wordclean);
					lstlast += SIZEWORD;
					countlst++;
					count = 0;
				}
			}


		}

	
	}
	/*for (int i = 0; i < countlst; i++) {
		printf("%s \n", showlst + SIZEWORD * i);
	}*/
	for (int i=0; i < countlst - 1; i++) {
		bool flag = false;
		for (int j=0; j < countlst - i - 1; j++) {
			char* str = showlst + j * SIZEWORD;
			char* str2 = showlst + (j + 1) * SIZEWORD;
			//printf("%s %s \n", str, str2);
			if (strcmp(str, str2) == 1) {
				char strok[SIZEWORD];
				strcpy(strok, showlst + j * SIZEWORD);
				strcpy(showlst + j * SIZEWORD, showlst + (j + 1) * SIZEWORD);
				strcpy(showlst + (j + 1) * SIZEWORD, strok);
				
				
			}
			
		}
		printf("%d %d \n", i, countlst);
	}

	count = 0;
	for (int i = 0; i < countlst; i++) {
		if (strcmp(showlst+SIZEWORD*i, showlst + SIZEWORD * (i+1))!=0) {
			count++;
			printf("%s : %d \n", showlst + SIZEWORD * i, count);
			fprintf(file, "%s;%d \n", showlst + SIZEWORD * i, count);
			count = 0;
		}
		else {
			count++;
		}

	}
	DWORD timeEnd = timeGetTime();
	DWORD time = timeEnd - timeStart;
	float timef = time / 1000;
	printf("%3.1f", timef);
	fprintf(file, "%3.1f \n", timef);
	fclose(file);
	fclose(mf);
	
}

