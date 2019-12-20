#pragma once
#include <stdio.h>
#include <windows.h>
#define TEXT_MAX 13
#define TIME_BREAK 100
#define TIME_BREAK_LONGER 500
#define TIME_BREAK_SHORTER 50

const char* text[TEXT_MAX] = {
	"1. Append record\n",
	"2. List record\n",
	"3. Delete record\n",
	"4. Modify record\n",
	"5. Search record\n",
	"6. Sort in descending order by sum\n",
	"7. Sort in ascending order by sum\n",
	"8. Sort in descending order by num\n",
	"9. Sort in ascending order by num\n",
	"W. Write to a File\n",
	"R. Read from a File\n",
	"0. Exit\n",
	"Please Input your choice: "
};
const char* mainText = "Management for Student's scores\n";

void slowDisplay(const char* p);
void intervalOutput(DWORD time, const char* text);
void displayMenu();

void slowDisplay(const char* p) {
	while (1) {
		if (*p != 0)
			printf("%c", *p++);
		else
			break;
		Sleep(TIME_BREAK);
	}
}

void intervalOutput(DWORD time, const char* text) {
	printf("%s", text);
	Sleep(time);
}

void slowDisplayMenu() {
	slowDisplay(mainText);
	Sleep(TIME_BREAK_LONGER);
	for (int index = 0; index < TEXT_MAX; index++) {
		intervalOutput(TIME_BREAK_LONGER, text[index]);
	}
}

void displayMenu() {
	printf("%s", mainText);
	for (int index = 0; index < TEXT_MAX; index++) {
		printf("%s", text[index]);
	}
}