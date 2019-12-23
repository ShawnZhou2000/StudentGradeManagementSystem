/*
	C语言课程设计 学生成绩管理系统
*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define TEXT_MAX 23
#define TIME_BREAK 100
#define TIME_BREAK_LONGER 200
#define TIME_BREAK_SHORTER 50
// 控制程序首次运行时的动画显示
#define MAX_STUDENT_NUM 1000   // 最大学生数量
#define MAX_STRING_LENGTH 256  // 字符串最长长度 

typedef struct {
	char name[MAX_STRING_LENGTH];               // 学生姓名
	long long int stuID;                        // 学号
	int chineseScore, mathScore, englishScore;  // 语文，数学，英语成绩
	int sumScore;								// 总分
	double averageScore;						// 平均分
}student;
student stu[MAX_STUDENT_NUM];
// 学生信息数组，采用简化线性表形式
int stuNum;
// 已录入的学生个数，学生从0开始计数

const char* text[TEXT_MAX] = {					// 用于显示菜单的字符串数组
	"\n\n",
	"\t\t\t                         学生成绩管理系统\n",
	"\n",
	"\t\t\t*************************************************************************\n",
	"\t\t\t*\t\t\t系统主菜单选项列表\t\t\t\t*\n",
	"\t\t\t*\t\t\t1.  添加学生信息\t\t\t\t*\n",
	"\t\t\t*\t\t\t2.  显示全部信息\t\t\t\t*\n",
	"\t\t\t*\t\t\t3.  删除一条信息\t\t\t\t*\n",
	"\t\t\t*\t\t\t4.  修改一条信息\t\t\t\t*\n",
	"\t\t\t*\t\t\t5.  查询一条信息\t\t\t\t*\n",
	"\t\t\t*\t\t\t6.  以总分为标准降序排序\t\t\t*\n",
	"\t\t\t*\t\t\t7.  以总分为标准升序排序\t\t\t*\n",
	"\t\t\t*\t\t\t8.  以学号为标准降序排序\t\t\t*\n",
	"\t\t\t*\t\t\t9.  以学号为标准升序排序\t\t\t*\n",
	"\t\t\t*\t\t\tW.  将当前的学生信息写入文件\t\t\t*\n",
	"\t\t\t*\t\t\tR.  从文件中读取学生信息\t\t\t*\n",
	"\t\t\t*\t\t\t0.  退出系统\t\t\t\t\t*\n",
	"\t\t\t*************************************************************************\n",
	"\n",
	"\n",
	"\n",
	"\n",
	"\t\t\t\t\t\t请输入对应的菜单序号: "
};

const char* fileIdentifierText = "SCMSDATA";		// 系统用文件标识符

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
	system("title 学生成绩管理系统 By 第2课程设计小组");   // 设置程序标题
	system("color 71");								// 设置控制台前景色和背景色
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准句柄，用于控制光标状态
	CONSOLE_CURSOR_INFO CursorInfo;					// 用于存储控制台光标信息
	GetConsoleCursorInfo(handle, &CursorInfo);		// 获取控制台光标信息
	CursorInfo.bVisible = 0;						// 隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);		// 设置控制台光标状态
	slowDisplayMenu();								// 第一次以动画形式显示菜单 
	CursorInfo.bVisible = 1;						// 恢复光标显示
	SetConsoleCursorInfo(handle, &CursorInfo);		// 设置控制台光标状态
	while (1) {
		getUserInput();								// 获取并判断用户的输入 
		system("cls");								// 清屏操作，后不再赘述
		displayMenu();								// 此后的显示为直接显示 
	}
	return 0;
}

void appendRecord() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\t1.  添加学生信息\t\t\t\t\n");
	if (stuNum == MAX_STUDENT_NUM) {			// 判断异常输入
		printf("\n\n\t\t\t\t\t学生数量已达系统最大限制，无法添加新信息！\n");
		printf("\n\n\t\t\t*************************************************************************\n");
	}
	else {
		int n;
		student newStu;
		printf("\n\n\t\t\t\t\t请输入要添加的学生信息数量:");
		scanf("%d", &n);
		if (n + stuNum > MAX_STUDENT_NUM) {    // 判断异常输入
			printf("\n\n\t\t\t\t\t添加后的数量超出系统最大限制，无法添加新信息！\n");
			printf("\n\n\t\t\t*************************************************************************\n");
		}
		else {
			for (int i = 1; i <= n; i++) {		// 按顺序录入数据
				printf("\t\t\t\t请输入新添加第%d个学生(总第%d个)的姓名:", i, stuNum + 1);
				scanf("%s", newStu.name);
				printf("\t\t\t\t请输入新添加第%d个学生(总第%d个)的学号:", i, stuNum + 1);
				scanf("%lld", &newStu.stuID);
				printf("\t\t\t\t请输入新添加第%d个学生(总第%d个)的语文成绩:", i, stuNum + 1);
				scanf("%d", &newStu.chineseScore);
				if (newStu.chineseScore > 100 || newStu.chineseScore < 0) {
					printf("\t\t\t\t语文成绩输入不合法（不在0到100分之间），已将该科成绩置为0。\n");
					newStu.chineseScore = 0;
				}
				printf("\t\t\t\t请输入新添加第%d个学生(总第%d个)的数学成绩:", i, stuNum + 1);
				scanf("%d", &newStu.mathScore);
				if (newStu.mathScore > 100 || newStu.mathScore < 0) {
					printf("\t\t\t\t数学成绩输入不合法（不在0到100分之间），已将该科成绩置为0。\n");
					newStu.mathScore = 0;
				}
				printf("\t\t\t\t请输入新添加第%d个学生(总第%d个)的英语成绩:", i, stuNum + 1);
				scanf("%d", &newStu.englishScore);
				if (newStu.englishScore > 100 || newStu.englishScore < 0) {
					printf("\t\t\t\t英语成绩输入不合法（不在0到100分之间），已将该科成绩置为0。\n");
					newStu.englishScore = 0;
				}
				stu[stuNum] = newStu;
				printf("\t\t\t\t新添加第%d个学生(总第%d个)的信息添加成功\n", i, stuNum);
				stu[stuNum].sumScore = stu[stuNum].chineseScore + stu[stuNum].mathScore + stu[stuNum].englishScore;
				stu[stuNum].averageScore = stu[stuNum].sumScore / 3;
				stuNum++;
			}
			printf("\t\t\t\t\t信息添加完毕\n");

		}
	}
	system("pause");					// 等待用户输入任意键再继续运行程序，下不再赘述
}

void listRecord() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\t2.  显示全部信息\t\t\t\t\n");
	printf("\n\t\t\t\t\t  一共有%d条记录，详细信息如下:\n\n", stuNum);
	printf("\t学号\t  \t  姓名  \t语文成绩\t数学成绩\t英语成绩\t总成绩\t      平均成绩\n\n");
	for (int i = 0; i < stuNum; i++) {
		printf("\t%5lld\t%6s\t\t%4d\t\t%4d\t\t%4d\t\t%4d\t\t%.2lf\n", stu[i].stuID, stu[i].name, stu[i].chineseScore, stu[i].mathScore, stu[i].englishScore, stu[i].sumScore, stu[i].averageScore);
	}
	printf("\n\n\n\t\t\t*************************************************************************\n");
	system("pause");
}

void deleteRecord() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\t3.  删除一条信息\t\t\t\t\n");
	printf("\n\t\t\t\t请输入要删除的同学的学号:");
	long long int delID;
	scanf("%lld", &delID);
	int j;
	int flag = 0;							// 判断是否找到该学生
	for (j = 0; j < stuNum; j++)			//寻找到该学号的同学 
		if (stu[j].stuID == delID) {
			flag = 1;
			for (j; j < stuNum; j++)
				stu[j] = stu[j + 1];		//用后来的同学信息覆盖该同学的信息 
			stuNum--;
			break;
		}
	if (flag == 0)
		printf("\t\t\t\t没有找到学号为:%lld的学生。\n", delID);		//若没找到则报错 
	else
		printf("\t\t\t\t学号为%lld的学生信息已删除。\n", delID);
	printf("\n\n\n\t\t\t*************************************************************************\n");
	system("pause");
}

void modifyRecord() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\t4.  修改一条信息\t\t\t\t\n");
	printf("\n\t\t\t\t请输入要修改信息的同学的学号:");
	long long int modiID;
	scanf("%lld", &modiID);
	int choice, Chinese, Math, English;
	int j;
	int flag = 0;								// 判断有没有找到
	for (j = 0; j < stuNum; j++) {				// 寻找该学号的同学 
		if (stu[j].stuID == modiID) {
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		printf("\n\t\t\t\t没有找到学号为 %lld 的学生。\n", modiID);
	else {
		printf("\n\t\t\t\t找到学号为 %lld 的学生。\n", stu[j].stuID);
		printf("\n\t\t\t\t请选择您要修改的项目:\n");
		printf("\t\t\t\t1、修改语文成绩\n");
		printf("\t\t\t\t2、修改数学成绩\n");
		printf("\t\t\t\t3、修改英语成绩\n");
		printf("\t\t\t\t4、退出修改\n");
		printf("\t\t\t\t");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			printf("\t\t\t\t请输入要修改的语文成绩:");
			scanf("%d", &Chinese);
			stu[j].chineseScore = Chinese;
			printf("\t\t\t\t修改成功！");
			break;
		case 2:
			printf("\t\t\t\t请输入要修改的数学成绩:");
			scanf("%d", &Math);
			stu[j].mathScore = Math;
			printf("\t\t\t\t修改成功！");
			break;
		case 3:
			printf("\t\t\t\t请输入要修改的英语成绩:");
			scanf("%d", &English);
			stu[j].englishScore = English;
			printf("\t\t\t\t修改成功！");
			break;
		case 4:
			break;
		default:
			printf("\t\t\t\t输入有误，返回主菜单");
			break;
		}
		stu[j].sumScore = stu[j].chineseScore + stu[j].mathScore + stu[j].englishScore;
		stu[j].averageScore = stu[j].sumScore / 3;
	}
	printf("\n\n\n\t\t\t*************************************************************************\n");
	system("pause");
}

void searchRecord() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\t5.  查询一条信息\t\t\t\t\n");
	printf("\n\t\t\t\t查询选项:\n");
	int k, i, a = -1; char m[MAX_STRING_LENGTH];
	// a代表寻找的下标，初值为-1，也代表没有找到
	long long int b;
	printf("\t\t\t\t1.  按姓名\n\t\t\t\t2.  按学号\n\n");     //提供选择菜单
	printf("\t\t\t\t请输入查询选项：");
	scanf("%d", &k);									     //记录用户输入选项
	if (k == 1) {											 //判断选项
		printf("\t\t\t\t请输入要查询的姓名：");
		scanf("%s", &m);
		for (i = 0; i < stuNum; i++)
			if (strcmp(m, stu[i].name) == 0)				 //逐条对比姓名字符
				a = i;										 //记录学生数组下标
	}
	else if (k == 2) {										 //判断选项
		printf("\t\t\t\t请输入学号：");
		scanf("%lld", &b);
		for (i = 0; i < stuNum; i++)
			if (b == stu[i].stuID)							 //对比学生学号
				a = i;
	}
	else {
		printf("\t\t\t\t输入有误，返回主菜单\n");
		system("pause");
		return;
	}
	if (a == -1)
		printf("\t\t\t\t按此查询条件没有找到对应的同学。\n");
	else {
		printf("\n\t学号\t  \t  姓名  \t语文成绩\t数学成绩\t英语成绩\t总成绩\t      平均成绩\n\n");
		printf("\t%5lld\t%6s\t\t%4d\t\t%4d\t\t%4d\t\t%4d\t\t%.2lf\n", stu[a].stuID, stu[a].name, stu[a].chineseScore, stu[a].mathScore, stu[a].chineseScore, stu[a].sumScore, stu[a].averageScore);
	}
	printf("\n\n\n\t\t\t*************************************************************************\n");
	system("pause");
}

void sortDesBySum() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\t6.  以总分为标准降序排序\t\t\t\t\n");
	int i, j, k;
	for (i = 0; i < stuNum - 1; i++) {			 // 选择排序主要过程
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
	printf("\n\t\t\t\t\t\t总分降序排序完毕，%d条记录\n\n", stuNum);
	printf("    \t\t学号\t  \t  姓名  \t语文成绩\t数学成绩\t英语成绩\t总成绩\t      平均成绩\n\n");
	for (int i = 0; i < stuNum; i++) {
		printf("    第%d名\t%5lld\t%6s\t\t%4d\t\t%4d\t\t%4d\t\t%4d\t\t%.2lf\n", i + 1, stu[i].stuID, stu[i].name, stu[i].chineseScore, stu[i].mathScore, stu[i].chineseScore, stu[i].sumScore, stu[i].averageScore);
	}
	printf("\n\n\n\t\t\t*************************************************************************\n");
	system("pause");
}

void sortAscBySum() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\t7.  以总分为标准升序排序\t\t\t\t\n");
	int i, j, k;
	for (i = 0; i < stuNum - 1; i++) {			// 选择排序主要过程
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
	printf("\n\t\t\t\t\t\t总分升序排序完毕，%d条记录\n\n", stuNum);
	printf("    \t\t学号\t  \t  姓名  \t语文成绩\t数学成绩\t英语成绩\t总成绩\t      平均成绩\n\n");
	for (int i = stuNum - 1; i >= 0; i--) {
		printf("    第%d名\t%5lld\t%6s\t\t%4d\t\t%4d\t\t%4d\t\t%4d\t\t%.2lf\n", i + 1, stu[i].stuID, stu[i].name, stu[i].chineseScore, stu[i].mathScore, stu[i].chineseScore, stu[i].sumScore, stu[i].averageScore);
	}
	printf("\n\n\n\t\t\t*************************************************************************\n");
	system("pause");
}

void sortDesByNum() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\t8.  以学号为标准降序排序\t\t\t\t\n");
	int i, j, k;
	for (i = 0; i < stuNum - 1; i++) {			// 选择排序主要过程
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
	printf("\n\t\t\t\t\t\t学号降序排序完毕，%d条记录\n\n", stuNum);
	printf("    \t\t学号\t  \t  姓名  \t语文成绩\t数学成绩\t英语成绩\t总成绩\t      平均成绩\n\n");
	for (int i = 0; i < stuNum; i++) {
		printf("      %d  \t%5lld\t%6s\t\t%4d\t\t%4d\t\t%4d\t\t%4d\t\t%.2lf\n", i + 1, stu[i].stuID, stu[i].name, stu[i].chineseScore, stu[i].mathScore, stu[i].chineseScore, stu[i].sumScore, stu[i].averageScore);
	}
	printf("\n\n\n\t\t\t*************************************************************************\n");
	system("pause");
}

void sortAscByNum() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\t9.  以学号为标准升序排序\t\t\t\t\n");
	int i, j, k;
	for (i = 0; i < stuNum - 1; i++) {			// 选择排序主要过程
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
	printf("\n\t\t\t\t\t\t学号升序排序完毕，%d条记录\n\n", stuNum);
	printf("    \t\t学号\t  \t  姓名  \t语文成绩\t数学成绩\t英语成绩\t总成绩\t      平均成绩\n\n");
	for (int i = stuNum - 1; i >= 0; i--) {
		printf("      %d  \t%5lld\t%6s\t\t%4d\t\t%4d\t\t%4d\t\t%4d\t\t%.2lf\n", i + 1, stu[i].stuID, stu[i].name, stu[i].chineseScore, stu[i].mathScore, stu[i].chineseScore, stu[i].sumScore, stu[i].averageScore);
	}
	printf("\n\n\n\t\t\t*************************************************************************\n");
	system("pause");
}

void writeToFile() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\tW.  将当前的学生信息写入文件\t\t\t\t\n");
	FILE* file = NULL;										// 文件指针
	char rout[MAX_STRING_LENGTH] = "D:\\test\\";	// 路径名
	char fileName[MAX_STRING_LENGTH];				// 文件名
	int isPermitted = 1;							// 判断用户是否允许，默认为1，若用户不允许则变为0
	printf("\n\t\t\t\t请输入要创建的文件名：");
	scanf("%s", fileName);
	strcat(rout, fileName);
	printf("\n\t\t\t\t注意：向%s文件中写入可能会覆盖原有数据，确定这么做吗？\n", rout);
	// 追加确认，保证数据的安全性
	printf("\t\t\t\t(键入y允许打开文件，键入其他则取消打开文件):");
	char choice;
	while (1) {
		scanf("%c", &choice);
		if (choice == '\n')
			continue;
		else
			break;
	}
	if (choice != 'y')
		isPermitted = 0;
	if (isPermitted) {
		file = fopen(rout, "w");
		fprintf(file, fileIdentifierText);
		for (int i = 0; i < stuNum; i++) {
			fprintf(file, "%s %lld %d %d %d\n", stu[i].name, stu[i].stuID, stu[i].chineseScore, stu[i].mathScore, stu[i].englishScore);
		}
		printf("\t\t\t\t文件已保存在%s\n", rout);
		fclose(file);
	}
	else {
		printf("\t\t\t\t用户取消了打开文件操作。\n");
	}
	printf("\n\n\n\t\t\t*************************************************************************\n");
	system("pause");
}

void readFromFile() {
	system("cls");
	printf("\t\t\t*************************************************************************\n");
	printf("\n\n\t\t\t\t\t\tR.  从文件中读取学生信息\t\t\t\t\n");
	FILE* file;
	char rout[MAX_STRING_LENGTH] = "D:\\test\\";
	char fileName[MAX_STRING_LENGTH];
	printf("\t\t\t\t请输入要读入的文件名：");
	scanf("%s", fileName);
	file = fopen(strcat(rout, fileName), "r");
	if (file == NULL) {						// 判断文件是否可以打开，防止崩溃
		printf("\t\t\t\t找不到%s文件！", rout);
	}
	else {
		char isLegal[MAX_STRING_LENGTH];	// 校验码暂存区
		/*
		设置校验码的原因如下：若读取非系统内可识别的文件，在读入时会就出现异常而导致程序崩溃
		使用本系统输出的文件头部自带校验码，可以在一定程度上保证通过文件输入的合法性。
		*/
		fscanf(file, "%s", isLegal);
		if (strcmp(isLegal, fileIdentifierText) != 0) {
			printf("\t\t\t打开失败，文件校验错误，请检查是否为合法的系统输入文件！\n");
		}
		else {
			stuNum = 0;
			student newStud;
			while (fscanf(file, "%s %lld %d %d %d", newStud.name, &newStud.stuID, &newStud.chineseScore, &newStud.mathScore, &newStud.englishScore) == 5) {
				newStud.sumScore = newStud.chineseScore + newStud.mathScore + newStud.englishScore;
				newStud.averageScore = newStud.sumScore / 3;
				stu[stuNum++] = newStud;
			}
			printf("\t\t\t\t已从%s里导入学生信息到系统\n", rout);
		}
	}
	printf("\n\n\n\t\t\t*************************************************************************\n");
	system("pause");
}

void exitProgram() {
	printf("\t\t\t\t\t感谢使用本管理系统，请按任意键退出...\n");
	system("pause");
	exit(0);
}

void getUserInput() {
	char ch;
	while (1) {
		// 输入此字符前的输入流很可能留有残余的'\n'，这会影响读入，所以采用此种方法吸收掉输入流前全部的'\n'。
		scanf("%c", &ch);
		if (ch == '\n')
			continue;
		else
			break;
	}
	while ((ch < '0' || ch > '9') && ch != 'W' && ch != 'R' && ch != 'w' && ch != 'r') {
		printf("\t\t\t\t输入有误，请重新输入: ");
		while (1) {
			scanf("%c", &ch);
			if (ch == '\n')
				continue;
			else
				break;
		}
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
		Sleep(TIME_BREAK_SHORTER);
	}
}

void intervalOutput(DWORD time, const char* text) {
	printf("%s", text);
	Sleep(time);
}

void slowDisplayMenu() {
	//Sleep(TIME_BREAK_LONGER);
	for (int index = 0; index < TEXT_MAX; index++) {
		if (index == 0)
			printf("%s", text[index]);
		else if (index == 1)
			slowDisplay(text[index]);
		else
			intervalOutput(TIME_BREAK_LONGER, text[index]);
	}
}

void displayMenu() {
	for (int index = 0; index < TEXT_MAX; index++) {
		printf("%s", text[index]);
	}
}