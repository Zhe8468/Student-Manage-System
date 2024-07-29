#include "StudentSystem.h"


int main(void)
{
	//链表初始化
	List list;
	list.head = NULL;
	list.size = 0;
	//每次开启系统先加载学生信息
	loadStuInfo(&list);
	//程序主循环
	while (true)
	{
		switch (showMenu())
		{
		case '1':
			getStuInfo(&list);
			break;
		case '2':
			printStuInfo(&list);
			break;
		case '3':
			countStuNum(&list);
			break;
		case '4':
			findStuInfo(&list);
			break;
		case '5':
			editStuInfo(&list);
			break;
		case '6':
			deleteStuInfo(&list);
			break;
		case '0':
			printf("\n欢迎下次使用~\n");
			return 0;
		}
		system("pause");
		system("cls");
	}
	return 0;
}

//创建链表节点
static Node* createNode()
{
	Node* node = malloc(sizeof(Node));
	node->next = NULL;
	return node;
}
//显示菜单
char showMenu()
{
	printf("***********************************\n");
	printf("*        学生管理系统 by Zhe       *\n");
	printf("***********************************\n");
	printf("*        1.录入学生信息            *\n");
	printf("*        2.打印学生信息            *\n");
	printf("*        3.统计学生人数            *\n");
	printf("*        4.查找学生信息            *\n");
	printf("*        5.修改学生信息            *\n");
	printf("*        6.删除学生信息            *\n");
	printf("*        0.退出系统                *\n");
	printf("***********************************\n");
	printf("请选择>");
	return _getch();
}
//录入学生信息
void getStuInfo(List* list)
{
	//创建一个节点用来存放学生信息
	Node* node = createNode();
	//获取学生信息
	printf("\n请输入学生学号>");
	scanf("%d", &node->stu.number);
	printf("请输入学生姓名>");
	scanf("%s", node->stu.name, sizeof(node->stu.name));
	printf("请输入学生分数>");
	scanf("%f", &node->stu.score);
	//头插法
	node->next = list->head;
	list->head = node;
	list->size++;
	//保存学生数据
	saveStuInfo(list);
}
//打印学生信息
void printStuInfo(List* list)
{
	putchar('\n');
	printf("学号\t姓名\t分数\n");
	Node * p = list->head;
	while (p != NULL) {
		printf("%d\t%s\t%.2f\n", p->stu.number, p->stu.name,p->stu.score);
		p = p->next;
	}
}
//保存学生信息
void saveStuInfo(List* list)
{
	//打开文件
	FILE* fp = fopen("stuinfo", "wb");
	if (!fp) {
		printf("\n学生数据文件打开失败！\n");
		return;
	}
	//写入信息
	Node* p = list->head;
	while (p != NULL) {
		fwrite(&p->stu, sizeof(Student), 1, fp);
		p = p->next;
	}
	fclose(fp);
	printf("\n学生信息保存成功！\n");
}
//加载学生数据
void loadStuInfo(List* list)
{
	FILE* fp = fopen("stuinfo", "rb");
	if (!fp) {
		printf("\n学生数据文件打开失败！\n");
		return;
	}
	//循环读取学生信息
	while (true) {
		Node* node = createNode();
		if (fread(&node->stu, sizeof(Student), 1, fp) == 1) {
			node->next = list->head;
			list->head = node;
			list->size++;
		}
		else break;
	}
	fclose(fp);
	printf("\n学生数据加载成功！\n");
}
//统计学生人数
void countStuNum(List* list)
{
	printf("\n当前学生人数为:%d\n", list->size);
}
//查找学生信息
void findStuInfo(List* list)
{
	int id = 0;
	printf("\n请输入学生学号>");
	scanf("%d", &id);
	//查找
	Node* p = list->head;
	while (p != NULL) {
		if (p->stu.number == id) {
			printf("学号\t姓名\t分数\n");
			printf("%d\t%s\t%.2f\n", p->stu.number, p->stu.name, p->stu.score);
			return;
		}
		p = p->next;
	}
	printf("\n未找到该学生！\n");
}
//修改学生信息
void editStuInfo(List* list)
{
	int id = 0;
	char name[20];
	float score = 0;
	printf("\n请输入学生学号>");
	scanf("%d", &id);
	//查找
	Node* p = list->head;
	while (p != NULL) {
		if (p->stu.number == id) {
			printf("请输入学生姓名>");
			scanf("%s", name);
			printf("请输入学生分数>");
			scanf("%f", &score);
			strncpy(p->stu.name, name, sizeof(name)); //字符数组不能修改
			p->stu.score = score;
			printf("\n学生信息修改成功！\n");
			saveStuInfo(list);
			return;
		}
		p = p->next;
	}
	printf("\n未找到该学生\n");
}
//删除学生信息
void deleteStuInfo(List* list)
{
	//判断是否还有学生
	if (list->size == 0) {
		printf("\n当前已没有学生信息\n");
		return;
	}
	int id = 0;
	printf("\n请输入学生学号>");
	scanf("%d", &id);
	//查找
	Node* p = list->head;
	Node* pre = NULL; //pre用来记录p的上一个节点
	while (p != NULL) {
		if (p->stu.number == id) {
			if (pre == NULL) list->head = p->next;
			else pre->next = p->next;
			free(p);
			list->size--;
			printf("\n删除成功！\n");
			saveStuInfo(list);
			return;
		}
		pre = p;
		p = p->next;
	}
	printf("\n未找到该学生\n");
}