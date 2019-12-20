/*
	C���Կγ���� ѧ���ɼ�����ϵͳ
*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define TEXT_MAX 13
#define TIME_BREAK 100
#define TIME_BREAK_LONGER 500
#define TIME_BREAK_SHORTER 50
// ���Ƴ����״�����ʱ�Ķ�����ʾ
#define MAX_STUDENT_NUM 100
// ���ѧ������

typedef struct _student {
	char* name;
	char* stuID;
	int chineseScore, mathScore, englishScore;
	int sumScore;
	double averageScore;
}student;
student stu[MAX_STUDENT_NUM];
// ѧ����Ϣ���飬���ü����Ա���ʽ
int stuNum;
// ��¼���ѧ��������ѧ����0��ʼ����

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
// ��ʾ�˵��õ��ַ��� 

void appendRecord();								// ����һ����¼ 
void listRecord();									// ��ʾ���м�¼ 
void deleteRecord();								// ɾ��һ����¼ 
void modifyRecord();								// �޸�һ����¼ 
void searchRecord();								// ����һ����¼ 
void sortDesBySum();								// ���ܷ�Ϊ���������� 
void sortAscBySum();								// ���ܷ�Ϊ������������ 
void sortDesByNum();								// ��ѧ��Ϊ���������� 
void sortAscByNum();								// ��ѧ��Ϊ������������ 
void writeToFile();									// д�뵽�ļ� 
void readFromFile();								// ���ļ��ж�ȡ 
void exitProgram();									// �˳����� 
void getUserInput();								// ��ȡ�û����� 
void slowDisplay(const char* p);					// ��������Դﵽ����Ч���ĺ��ķ��� 
void intervalOutput(DWORD time, const char* text);	// ���һ���ַ�������ͣĳһʱ�� 
void slowDisplayMenu(); 							// �Զ����������������ʽ��ӡ�˵� 
void displayMenu();									// ֱ�Ӵ�ӡ�˵� 

int main() {
	slowDisplayMenu();								// ��һ����ʾ�Զ�����ʽ 
	while (1) {
		getUserInput();								// ��ȡ���ж��û������� 
		system("cls");								// �������� 
		displayMenu();								// �˺����ʾΪֱ����ʾ 
	}
	return 0;
}
student newStu;
char* newname;
char* newID;
void appendRecord() {
	int n;
	printf("������Ҫ��ӵ�ѧ����Ϣ����:");
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		printf("����������ӵ�%d��ѧ��(�ܵ�%d��)������:", i, stuNum);
		scanf("%s", newname);
		strcpy(newStu.name, newname);
		printf("����������ӵ�%d��ѧ��(�ܵ�%d��)��ѧ��:", i, stuNum);
		scanf("%s", newID);
		strcpy(newStu.stuID, newID);
		printf("����������ӵ�%d��ѧ��(�ܵ�%d��)�����ĳɼ�:", i, stuNum);
		scanf("%d", &newStu.chineseScore);
		printf("����������ӵ�%d��ѧ��(�ܵ�%d��)����ѧ�ɼ�:", i, stuNum);
		scanf("%d", &newStu.mathScore);
		printf("����������ӵ�%d��ѧ��(�ܵ�%d��)��Ӣ��ɼ�:", i, stuNum);
		scanf("%d", &newStu.englishScore);
		stu[stuNum++] = newStu;
		printf("����ӵ�%d��ѧ��(�ܵ�%d��)����Ϣ��ӳɹ�:\n", i, stuNum);
	}
	printf("��Ϣ������\n");
	Sleep(1000);
}

void listRecord()
{

}

void deleteRecord() {
	printf("������Ҫɾ����ͬѧ��ѧ��:");
	char* delID = "";
	scanf("%s", delID);
	int j;
	for (j = 0; j < stuNum; j++)			//Ѱ�ҵ���ѧ�ŵ�ͬѧ 
		if (stu[j].stuID == delID) {
			for (j; j < stuNum; j++)
				stu[j] = stu[j + 1];	//�ú�����ͬѧ��Ϣ���Ǹ�ͬѧ����Ϣ 
			break;
		}
	if (j == stuNum)
		printf("û���ҵ�ѧ��Ϊ:%s��ѧ��\n", delID);		//��û�ҵ��򱨴� 
	Sleep(1000);
}

void modifyRecord() {
	printf("������Ҫ�޸���Ϣ��ͬѧ��ѧ��:");
	char* modiID = "";
	scanf("%s", modiID);
	int choice, Chinese, Math, English;
	int j;
	for (j = 0; j < stuNum; j++)			//Ѱ�ҵ���ѧ�ŵ�ͬѧ 
		if (stu[j].stuID == modiID) {
			printf("�ҵ�ѧ��Ϊ:%s��ѧ��\n", stu[j].stuID);
			break;
		}
	if (j == stuNum)
		printf("û���ҵ�ѧ��Ϊ:%s��ѧ��\n", modiID);
	printf("��ѡ����Ҫ�޸ĵ���Ŀ:\n");
	printf("1���޸����ĳɼ�\n");
	printf("2���޸���ѧ�ɼ�\n");
	printf("3���޸�Ӣ��ɼ�\n");
	printf("4���˳��޸�\n");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		printf("������Ҫ�޸ĵ����ĳɼ�:\n");
		scanf("%d", &Chinese);
		stu[j].chineseScore = Chinese;
		printf("�޸ĳɹ���");
		break;
	case 2:
		printf("������Ҫ�޸ĵ���ѧ�ɼ�:\n");
		scanf("%d", &Math);
		stu[j].mathScore = Math;
		printf("�޸ĳɹ���");
		break;
	case 3:
		printf("������Ҫ�޸ĵ�Ӣ��ɼ�:\n");
		scanf("%d", &English);
		stu[j].englishScore = English;
		printf("�޸ĳɹ���");
		break;
	case 4:
		break;
	default:
		printf("�������󣬷������˵�");
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