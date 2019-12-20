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
#define MAX_STUDENT_NUM 100   // 最大学生数量
#define MAX_STRING_LENGTH 256  // 字符串最长长度 

typedef struct {
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
	"1. 添加学生信息\n",
	"2. 显示全部信息\n",
	"3. 删除一条信息\n",
	"4. 修改一条信息\n",
	"5. 查询一条信息\n",
	"6. 以总分为标准降序排序\n",
	"7. 以总分为标准升序排序\n",
	"8. 以学号为标准降序排序\n",
	"9. 以学号为标准升序排序\n",
	"W. 将当前的学生信息写入到文件\n",
	"R. 从文件中读取学生信息\n",
	"0. 退出系统\n",
	"请输入对应功能的菜单序号: "
};
const char* mainText = "学生成绩管理系统\n";
// 显示菜单用的字符串 

const char* fileIdentifierText = "SCMSDATA\n";

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
	if (stuNum == MAX_STUDENT_NUM) {
		printf("学生数量已达最大限制，无法添加新信息！\n");
	}
	else {
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
			printf("新添加第%d个学生(总第%d个)的信息添加成功\n", i, stuNum);
		}
		printf("信息添加完毕\n");
		getchar();
	}
	system("pause");
}

void listRecord() {
	printf("显示模块开始......\n一共有%d条记录，详细信息如下:\n",stuNum);
	printf("学号\t姓名\t语文成绩\t数学成绩\t英语成绩\t总成绩\t平均成绩\n\n");
	for (int i = 0; i < stuNum; i++) {
		stu[i].sumScore = stu[i].chineseScore + stu[i].mathScore + stu[i].englishScore;
		stu[i].averageScore = stu[i].sumScore / 3;
		printf("%5lld\t%6s\t%4d\t%4d\t%4d\t%4d\t%.2lf\n",stu[i].stuID, stu[i].name, stu[i].chineseScore, stu[i].mathScore, stu[i].chineseScore, stu[i].sumScore, stu[i].averageScore);
	}
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
		printf("没有找到学号为:%lld的学生。\n", delID);		//若没找到则报错 
	else
		printf("学号为%lld的学生信息已删除。\n", delID);
	getchar();
	system("pause");
}

void modifyRecord() {
	printf("请输入要修改信息的同学的学号:");
	long long int modiID;
	scanf("%lld", &modiID);
	int choice, Chinese, Math, English;
	int j;
	int flag = 0;
	for (j = 0; j < stuNum; j++) {				//寻找到该学号的同学 
		if (stu[j].stuID == modiID) {
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		printf("没有找到学号为 %lld 的学生。\n", modiID);
	else {
		printf("找到学号为 %lld 的学生。\n", stu[j].stuID);
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
	}
	getchar();
	system("pause");
}

void searchRecord() {
	int k, i, a = 0; char m[MAX_STRING_LENGTH];
	long long int b;
	printf("查找模块开始.....\n\n");
	printf("     ****************************************\n");
	printf("     *      1.姓名           2.学号         *\n\n");     //提供选择菜单
	printf("请输入查询选项：");
	scanf("%d", &k);           //记录用户输入选项
	if (k == 1) {              //判断选项
		printf("请输入姓名：");
		scanf("%s", &m);
		for (i = 0; i < stuNum; i++)
			if (m == stu[i].name)         //逐条对比姓名字符
				a = i;                       //记录学生数组下标
	}
	else if (k == 2) {            //判断选项
		printf("请输入学号：");
		scanf("%lld", &b);
		for (i = 0; i < stuNum; i++)
			if (b == stu[i].stuID)              //对比学生学号
				a = i;
	}
	else {
		printf("输入有误，返回主菜单");
		system("pause");
		return;
	}
	if (a == 0)
		printf("没有找到！！！\n");
	else {
		printf(" 学号\t姓名\t语文成绩\t数学\t英语成绩\t总成绩\t平均成绩\n");
		printf("%5lld %6s %4d %4d %4d %4d %.2lf\n",stu[a].stuID, stu[a].name, stu[a].chineseScore, stu[a].mathScore, stu[a].chineseScore, stu[a].sumScore, stu[a].averageScore);
	}
	getchar();
	system("pause");
}

void sortDesBySum() {
	int i, j, k;
	for (i = 0; i < stuNum - 1; i++) {
		k = i;
		for (j = i + 1; j < stuNum; j++)
			if (stu[j].sumScore > stu[k].sumScore)
				k = j;
		if (i != k) {
			student e = stu[i];
			stu[i] = stu[k];
			stu[k] = e;
		}
	}
	printf("总分降序排序完毕，%d条记录\n", stuNum);
	for (int i = 0; i < stuNum; i++)
		printf("第%d名\t学号%lld\t语文%d\t数学%d\t英语%d\t总分%d\n", i + 1, stu[i].stuID, stu[i].chineseScore, stu[i].mathScore, stu[i].englishScore, stu[i].sumScore);
	system("pause");
}

void sortAscBySum() {
	int i, j, k;
	for (i = 0; i < stuNum - 1; i++) {
		k = i;
		for (j = i + 1; j < stuNum; j++)
			if (stu[j].sumScore < stu[k].sumScore)  
				k = j;
		if (i != k) {
			student e = stu[i];
			stu[i] = stu[k];
			stu[k] = e;
		}
	}
	printf("总分升序排序完毕，%d条记录\n", stuNum);
	for (int i = 0; i < stuNum; i++)
		printf("第%d名\t学号%lld\t语文%d\t数学%d\t英语%d\t总分%d\n", stuNum - i, stu[i].stuID, stu[i].chineseScore, stu[i].mathScore, stu[i].englishScore, stu[i].sumScore);
	system("pause");
}

void sortDesByNum() {
	int i, j, k;
	for (i = 0; i < stuNum - 1; i++) {
		k = i;
		for (j = i + 1; j < stuNum; j++)
			if (stu[j].stuID < stu[k].stuID)
				k = j;
		if (i != k) {
			student e = stu[i];
			stu[i] = stu[k];
			stu[k] = e;
		}
	}
	printf("学号降序排序完毕，%d条记录\n", stuNum);
	for (int i = 0; i < stuNum; i++)
		printf("学号%lld\t语文%d\t数学%d\t英语%d\t总分%d\n", stu[i].stuID, stu[i].chineseScore, stu[i].mathScore, stu[i].englishScore, stu[i].sumScore);
	system("pause");
}

void sortAscByNum() {
	int i, j, k;
	for (i = 0; i < stuNum - 1; i++) {
		k = i;
		for (j = i + 1; j < stuNum; j++)
			if (stu[j].stuID > stu[k].stuID)
				k = j;
		if (i != k) {
			student e = stu[i];
			stu[i] = stu[k];
			stu[k] = e;
		}
	}
	printf("学号升序排序完毕，%d条记录\n", stuNum);
	for (int i = 0; i < stuNum; i++)
		printf("学号%lld\t语文%d\t数学%d\t英语%d\t总分%d\n", stu[i].stuID, stu[i].chineseScore, stu[i].mathScore, stu[i].englishScore, stu[i].sumScore);
	system("pause");
}

void writeToFile() {
	FILE* file;
	char rout[MAX_STRING_LENGTH] = "D:\\test\\";
	char fileName[MAX_STRING_LENGTH];
	int isPermitted = 1;
	printf("请输入要创建的文件名：");
	scanf("%s", fileName);
	getchar();
	file = fopen(strcat(rout, fileName), "w");
	if (!feof(file)) {
		printf("注意：%s文件已存在，要覆盖吗？(键入y允许覆盖文件，键入其他则取消打开文件):", rout);
		char choice;
		scanf("%c", &choice);
		getchar();
		if (choice != 'y')
			isPermitted = 0;
	}
	if (isPermitted) {
		fprintf(file, fileIdentifierText);
		for (int i = 0; i < stuNum; i++) {
			fprintf(file, "%s %lld %d %d %d %d %.2lf\n", stu[i].name, stu[i].stuID, stu[i].chineseScore, stu[i].mathScore, stu[i].englishScore, stu[i].sumScore, stu[i].averageScore);
		}
		printf("文件已保存在%s\n", rout);
	}
	else {
		printf("用户取消了打开文件操作。\n");
	}
	fclose(file);
	system("pause");
}

void readFromFile() {
	FILE* file;
	char rout[MAX_STRING_LENGTH] = "D:\\test\\";
	char fileName[MAX_STRING_LENGTH];
	printf("请输入要读入的文件名：");
	scanf("%s", fileName);
	file = fopen(strcat(rout, fileName), "r");
	if (file == NULL) {
		printf("找不到%s文件！", rout);
	}
	else {
		char isLegal[MAX_STRING_LENGTH];
		fscanf(file, "%s", isLegal);
		if (strcmp(isLegal, fileIdentifierText) == 0) {
			printf("打开失败，文件校验错误，请检查是否为合法的系统输入文件！\n%s\n%s",isLegal,fileIdentifierText);
		}
		else {
			student newStud;
			while (fscanf(file, "%s %lld %d %d %d %d %lf", newStud.name, &newStud.stuID, &newStud.chineseScore, &newStud.mathScore, &newStud.englishScore, &newStud.sumScore, &newStud.averageScore) == 7) {
				stu[stuNum++] = newStud;
			}
			printf("已从%s里导入学生信息到系统\n", rout);
		}
	}
	getchar();
	system("pause");
}

void exitProgram() {
	printf("感谢使用本管理系统，请按任意键退出...\n");
	system("pause");
	exit(0);
}

void getUserInput() {
	char ch;
	scanf("%c", &ch);
	getchar();
	while ((ch < '0' || ch > '9') && ch != 'W' && ch != 'R' && ch!= 'w' && ch!= 'r') {
		printf("输入有误，请重新输入: ");
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
	case 'w':
		writeToFile();
		break;
	case 'R':
		readFromFile();
		break;
	case 'r':
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