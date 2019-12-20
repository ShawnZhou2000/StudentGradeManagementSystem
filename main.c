/*
	C语言课程设计 学生成绩管理系统
*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define TEXT_MAX 13
#define TIME_BREAK 10
#define TIME_BREAK_LONGER 50
#define TIME_BREAK_SHORTER 5
// 控制程序首次运行时的动画显示
#define MAX_STUDENT_NUM 100
// 最大学生数量
#define MAX_STRING_LENGTH 50

typedef struct _student {
	char name[MAX_STRING_LENGTH];
	long long int stuID;
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

void appendRecord() {
	int n;
	student newStu;
	printf("请输入要添加的学生信息数量:");
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		printf("请输入新添加第%d个学生(总第%d个)的姓名:", i, stuNum + 1);
		scanf("%s", newStu.name);
		printf("请输入新添加第%d个学生(总第%d个)的学号:", i, stuNum + 1);
		scanf("%lld", &newStu.stuID);
		printf("请输入新添加第%d个学生(总第%d个)的语文成绩:", i, stuNum + 1);
		scanf("%d", &newStu.chineseScore);
		printf("请输入新添加第%d个学生(总第%d个)的数学成绩:", i, stuNum + 1);
		scanf("%d", &newStu.mathScore);
		printf("请输入新添加第%d个学生(总第%d个)的英语成绩:", i, stuNum + 1);
		scanf("%d", &newStu.englishScore);
		stu[stuNum++] = newStu;
		printf("新添加第%d个学生(总第%d个)的信息添加成功:\n", i, stuNum + 1);
	}
	printf("信息添加完毕\n");
	getchar();
	Sleep(1000);
}

void listRecord() {
	printf("%d条记录\n", stuNum);
	for (int i = 0; i < stuNum; i++)
		printf("学号%lld 语文%d 数学%d 英语%d\n", stu[i].stuID, stu[i].chineseScore, stu[i].mathScore, stu[i].englishScore);
	system("pause");
}

void deleteRecord() {
	printf("请输入要删除的同学的学号:");
	long long int delID;
	scanf("%lld", &delID);
	int j;
	int flag = 0; // 判断是否找到该学生
	for (j = 0; j < stuNum; j++)			//寻找到该学号的同学 
		if (stu[j].stuID == delID) {
			flag = 1;
			for (j; j < stuNum; j++)
				stu[j] = stu[j + 1];	//用后来的同学信息覆盖该同学的信息 
			stuNum--;
			break;
		}
	if (flag == 0)
		printf("没有找到学号为:%d的学生\n", delID);		//若没找到则报错 
	else
		printf("学号为%d的学生信息已删除。\n", delID);
	system("pause");
}

void modifyRecord() {
	printf("请输入要修改信息的同学的学号:");
	long long int modiID;
	scanf("%lld", &modiID);
	int choice, Chinese, Math, English;
	int j;
	for (j = 0; j < stuNum; j++)			//寻找到该学号的同学 
		if (stu[j].stuID == modiID) {
			printf("找到学号为:%lld的学生\n", stu[j].stuID);
			break;
		}
	if (j == stuNum)
		printf("没有找到学号为:%lld的学生\n", modiID);
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
	system("pause");
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