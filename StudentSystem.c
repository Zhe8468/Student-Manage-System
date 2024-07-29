#include "StudentSystem.h"


int main(void)
{
	//�����ʼ��
	List list;
	list.head = NULL;
	list.size = 0;
	//ÿ�ο���ϵͳ�ȼ���ѧ����Ϣ
	loadStuInfo(&list);
	//������ѭ��
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
			printf("\n��ӭ�´�ʹ��~\n");
			return 0;
		}
		system("pause");
		system("cls");
	}
	return 0;
}

//��������ڵ�
static Node* createNode()
{
	Node* node = malloc(sizeof(Node));
	node->next = NULL;
	return node;
}
//��ʾ�˵�
char showMenu()
{
	printf("***********************************\n");
	printf("*        ѧ������ϵͳ by Zhe       *\n");
	printf("***********************************\n");
	printf("*        1.¼��ѧ����Ϣ            *\n");
	printf("*        2.��ӡѧ����Ϣ            *\n");
	printf("*        3.ͳ��ѧ������            *\n");
	printf("*        4.����ѧ����Ϣ            *\n");
	printf("*        5.�޸�ѧ����Ϣ            *\n");
	printf("*        6.ɾ��ѧ����Ϣ            *\n");
	printf("*        0.�˳�ϵͳ                *\n");
	printf("***********************************\n");
	printf("��ѡ��>");
	return _getch();
}
//¼��ѧ����Ϣ
void getStuInfo(List* list)
{
	//����һ���ڵ��������ѧ����Ϣ
	Node* node = createNode();
	//��ȡѧ����Ϣ
	printf("\n������ѧ��ѧ��>");
	scanf("%d", &node->stu.number);
	printf("������ѧ������>");
	scanf("%s", node->stu.name, sizeof(node->stu.name));
	printf("������ѧ������>");
	scanf("%f", &node->stu.score);
	//ͷ�巨
	node->next = list->head;
	list->head = node;
	list->size++;
	//����ѧ������
	saveStuInfo(list);
}
//��ӡѧ����Ϣ
void printStuInfo(List* list)
{
	putchar('\n');
	printf("ѧ��\t����\t����\n");
	Node * p = list->head;
	while (p != NULL) {
		printf("%d\t%s\t%.2f\n", p->stu.number, p->stu.name,p->stu.score);
		p = p->next;
	}
}
//����ѧ����Ϣ
void saveStuInfo(List* list)
{
	//���ļ�
	FILE* fp = fopen("stuinfo", "wb");
	if (!fp) {
		printf("\nѧ�������ļ���ʧ�ܣ�\n");
		return;
	}
	//д����Ϣ
	Node* p = list->head;
	while (p != NULL) {
		fwrite(&p->stu, sizeof(Student), 1, fp);
		p = p->next;
	}
	fclose(fp);
	printf("\nѧ����Ϣ����ɹ���\n");
}
//����ѧ������
void loadStuInfo(List* list)
{
	FILE* fp = fopen("stuinfo", "rb");
	if (!fp) {
		printf("\nѧ�������ļ���ʧ�ܣ�\n");
		return;
	}
	//ѭ����ȡѧ����Ϣ
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
	printf("\nѧ�����ݼ��سɹ���\n");
}
//ͳ��ѧ������
void countStuNum(List* list)
{
	printf("\n��ǰѧ������Ϊ:%d\n", list->size);
}
//����ѧ����Ϣ
void findStuInfo(List* list)
{
	int id = 0;
	printf("\n������ѧ��ѧ��>");
	scanf("%d", &id);
	//����
	Node* p = list->head;
	while (p != NULL) {
		if (p->stu.number == id) {
			printf("ѧ��\t����\t����\n");
			printf("%d\t%s\t%.2f\n", p->stu.number, p->stu.name, p->stu.score);
			return;
		}
		p = p->next;
	}
	printf("\nδ�ҵ���ѧ����\n");
}
//�޸�ѧ����Ϣ
void editStuInfo(List* list)
{
	int id = 0;
	char name[20];
	float score = 0;
	printf("\n������ѧ��ѧ��>");
	scanf("%d", &id);
	//����
	Node* p = list->head;
	while (p != NULL) {
		if (p->stu.number == id) {
			printf("������ѧ������>");
			scanf("%s", name);
			printf("������ѧ������>");
			scanf("%f", &score);
			strncpy(p->stu.name, name, sizeof(name)); //�ַ����鲻���޸�
			p->stu.score = score;
			printf("\nѧ����Ϣ�޸ĳɹ���\n");
			saveStuInfo(list);
			return;
		}
		p = p->next;
	}
	printf("\nδ�ҵ���ѧ��\n");
}
//ɾ��ѧ����Ϣ
void deleteStuInfo(List* list)
{
	//�ж��Ƿ���ѧ��
	if (list->size == 0) {
		printf("\n��ǰ��û��ѧ����Ϣ\n");
		return;
	}
	int id = 0;
	printf("\n������ѧ��ѧ��>");
	scanf("%d", &id);
	//����
	Node* p = list->head;
	Node* pre = NULL; //pre������¼p����һ���ڵ�
	while (p != NULL) {
		if (p->stu.number == id) {
			if (pre == NULL) list->head = p->next;
			else pre->next = p->next;
			free(p);
			list->size--;
			printf("\nɾ���ɹ���\n");
			saveStuInfo(list);
			return;
		}
		pre = p;
		p = p->next;
	}
	printf("\nδ�ҵ���ѧ��\n");
}