/*
	C语言课程设计 学生成绩管理系统
*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define TEXT_MAX 13
#define TIME_BREAK 100
#define TIME_BREAK_LONGER 500
#define TIME_BREAK_SHORTER 50
// 控制程序首次运行时的动画显示
#define MAX_STUDENT_NUM 100
// 最大学生数量

typedef struct _student {
	char* name;
	char* stuID;
	int chineseScore, mathScore, englishScore;
	int sumScore;
	double averageScore;
}student;
student stu[MAX_STUDENT_NUM];
// 学生信息数组，采用简化线性表形式
int stuNum;
// 已录入的学生个数，学生从0开始计数

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
// 显示菜单用的字符串 

void appendRecord();								// 增加一条记录 
void listRecord();									// 显示所有记录 
void deleteRecord();								// 删除一条记录 
void modifyRecord();								// 修改一条记录 
void searchRecord();								// 查找一条记录 
void sortDesBySum();								// 以总分为规则降序排序 
void sortAscBySum();								// 以总分为规则升序排序 
void sortDesByNum();								// 以学号为规则降序排序 
void sortAscByNum();								// 以学号为规则升序排序 
void writeToFile();									// 写入到文件 
void readFromFile();								// 从文件中读取 
void exitProgram();									// 退出程序 
void getUserInput();								// 获取用户输入 
void slowDisplay(const char* p);					// 缓慢输出以达到动画效果的核心方法 
void intervalOutput(DWORD time, const char* text);	// 输出一行字符串便暂停某一时间 
void slowDisplayMenu(); 							// 以动画（缓慢输出）形式打印菜单 
void displayMenu();									// 直接打印菜单 

int main() {
	slowDisplayMenu();								// 第一次显示以动画形式 
	while (1) {
		getUserInput();								// 获取并判断用户的输入 
		system("cls");								// 清屏操作 
		displayMenu();								// 此后的显示为直接显示 
	}
	return 0;
}
student newStu;
char* newname;
char* newID;
void appendRecord() {
	int n;
	printf("请输入要添加的学生信息数量:");
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		printf("请输入新添加第%d个学生(总第%d个)的姓名:", i, stuNum);
		scanf("%s", newname);
		strcpy(newStu.name, newname);
		printf("请输入新添加第%d个学生(总第%d个)的学号:", i, stuNum);
		scanf("%s", newID);
		strcpy(newStu.stuID, newID);
		printf("请输入新添加第%d个学生(总第%d个)的语文成绩:", i, stuNum);
		scanf("%d", &newStu.chineseScore);
		printf("请输入新添加第%d个学生(总第%d个)的数学成绩:", i, stuNum);
		scanf("%d", &newStu.mathScore);
		printf("请输入新添加第%d个学生(总第%d个)的英语成绩:", i, stuNum);
		scanf("%d", &newStu.englishScore);
		stu[stuNum++] = newStu;
		printf("新添加第%d个学生(总第%d个)的信息添加成功:\n", i, stuNum);
	}
	printf("信息添加完毕\n");
	Sleep(1000);
}

void listRecord()
{

}

void deleteRecord() {
	printf("请输入要删除的同学的学号:");
	char* delID = "";
	scanf("%s", delID);
	int j;
	for (j = 0; j < stuNum; j++)			//寻找到该学号的同学 
		if (stu[j].stuID == delID) {
			for (j; j < stuNum; j++)
				stu[j] = stu[j + 1];	//用后来的同学信息覆盖该同学的信息 
			break;
		}
	if (j == stuNum)
		printf("没有找到学号为:%s的学生\n", delID);		//若没找到则报错 
	Sleep(1000);
}

void modifyRecord() {
	printf("请输入要修改信息的同学的学号:");
	char* modiID = "";
	scanf("%s", modiID);
	int choice, Chinese, Math, English;
	int j;
	for (j = 0; j < stuNum; j++)			//寻找到该学号的同学 
		if (stu[j].stuID == modiID) {
			printf("找到学号为:%s的学生\n", stu[j].stuID);
			break;
		}
	if (j == stuNum)
		printf("没有找到学号为:%s的学生\n", modiID);
	printf("请选择您要修改的项目:\n");
	printf("1、修改语文成绩\n");
	printf("2、修改数学成绩\n");
	printf("3、修改英语成绩\n");
	printf("4、退出修改\n");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		printf("请输入要修改的语文成绩:\n");
		scanf("%d", &Chinese);
		stu[j].chineseScore = Chinese;
		printf("修改成功！");
		break;
	case 2:
		printf("请输入要修改的数学成绩:\n");
		scanf("%d", &Math);
		stu[j].mathScore = Math;
		printf("修改成功！");
		break;
	case 3:
		printf("请输入要修改的英语成绩:\n");
		scanf("%d", &English);
		stu[j].englishScore = English;
		printf("修改成功！");
		break;
	case 4:
		break;
	default:
		printf("输入有误，返回主菜单");
		break;
	}
	Sleep(1000);
}

void searchRecord() {

}

void sortDesBySum() {

}

void sortAscBySum() {

}

void sortDesByNum() {

}

void sortAscByNum() {

}

void writeToFile() {

}

void readFromFile() {

}

void exitProgram() {
	printf("Thank you for using this system, please press any key to exit...\n");
	system("pause");
	exit(0);
}

void getUserInput() {
	char ch;
	scanf("%c", &ch);
	getchar();
	while ((ch < '0' || ch > '9') && ch != 'W' && ch != 'R') {
		printf("\nInput error, please input your choice again: ");
		scanf("%c", &ch);
		getchar();
	}
	switch (ch) {
	case '1':
		appendRecord();
		break;
	case '2':
		listRecord();
		break;
	case '3':
		deleteRecord();
		break;
	case '4':
		modifyRecord();
		break;
	case '5':
		searchRecord();
		break;
	case '6':
		sortDesBySum();
		break;
	case '7':
		sortAscBySum();
		break;
	case '8':
		sortDesByNum();
		break;
	case '9':
		sortAscByNum();
		break;
	case 'W':
		writeToFile();
		break;
	case 'R':
		readFromFile();
		break;
	case '0':
		exitProgram();
		break;
	}
}

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