/*
	C���Կγ���� ѧ���ɼ�����ϵͳ
*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define TEXT_MAX 13
#define TIME_BREAK 10
#define TIME_BREAK_LONGER 50
#define TIME_BREAK_SHORTER 5
// ���Ƴ����״�����ʱ�Ķ�����ʾ
#define MAX_STUDENT_NUM 100
// ���ѧ������
#define MAX_STRING_LENGTH 50

typedef struct _student {
	char name[MAX_STRING_LENGTH];
	long long int stuID;
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

void appendRecord() {
	int n;
	student newStu;
	printf("������Ҫ��ӵ�ѧ����Ϣ����:");
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		printf("����������ӵ�%d��ѧ��(�ܵ�%d��)������:", i, stuNum + 1);
		scanf("%s", newStu.name);
		printf("����������ӵ�%d��ѧ��(�ܵ�%d��)��ѧ��:", i, stuNum + 1);
		scanf("%lld", &newStu.stuID);
		printf("����������ӵ�%d��ѧ��(�ܵ�%d��)�����ĳɼ�:", i, stuNum + 1);
		scanf("%d", &newStu.chineseScore);
		printf("����������ӵ�%d��ѧ��(�ܵ�%d��)����ѧ�ɼ�:", i, stuNum + 1);
		scanf("%d", &newStu.mathScore);
		printf("����������ӵ�%d��ѧ��(�ܵ�%d��)��Ӣ��ɼ�:", i, stuNum + 1);
		scanf("%d", &newStu.englishScore);
		stu[stuNum++] = newStu;
		printf("����ӵ�%d��ѧ��(�ܵ�%d��)����Ϣ��ӳɹ�:\n", i, stuNum + 1);
	}
	printf("��Ϣ������\n");
	getchar();
	Sleep(1000);
}

void listRecord() {
	printf("%d����¼\n", stuNum);
	for (int i = 0; i < stuNum; i++)
		printf("ѧ��%lld ����%d ��ѧ%d Ӣ��%d\n", stu[i].stuID, stu[i].chineseScore, stu[i].mathScore, stu[i].englishScore);
	system("pause");
}

void deleteRecord() {
	printf("������Ҫɾ����ͬѧ��ѧ��:");
	long long int delID;
	scanf("%lld", &delID);
	int j;
	int flag = 0; // �ж��Ƿ��ҵ���ѧ��
	for (j = 0; j < stuNum; j++)			//Ѱ�ҵ���ѧ�ŵ�ͬѧ 
		if (stu[j].stuID == delID) {
			flag = 1;
			for (j; j < stuNum; j++)
				stu[j] = stu[j + 1];	//�ú�����ͬѧ��Ϣ���Ǹ�ͬѧ����Ϣ 
			stuNum--;
			break;
		}
	if (flag == 0)
		printf("û���ҵ�ѧ��Ϊ:%d��ѧ��\n", delID);		//��û�ҵ��򱨴� 
	else
		printf("ѧ��Ϊ%d��ѧ����Ϣ��ɾ����\n", delID);
	system("pause");
}

void modifyRecord() {
	printf("������Ҫ�޸���Ϣ��ͬѧ��ѧ��:");
	long long int modiID;
	scanf("%lld", &modiID);
	int choice, Chinese, Math, English;
	int j;
	for (j = 0; j < stuNum; j++)			//Ѱ�ҵ���ѧ�ŵ�ͬѧ 
		if (stu[j].stuID == modiID) {
			printf("�ҵ�ѧ��Ϊ:%lld��ѧ��\n", stu[j].stuID);
			break;
		}
	if (j == stuNum)
		printf("û���ҵ�ѧ��Ϊ:%lld��ѧ��\n", modiID);
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