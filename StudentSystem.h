#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//ѧ������
typedef struct {
	int number;
	char name[20];
	float score;
}Student;

//�����ÿһ���ڵ�
typedef struct {
	Student stu;
	struct Node* next;
}Node;

//����
typedef struct List{
	Node* head; //ָ���һ���ڵ�
	int size; //�ڵ�����
}List;

//��ӡ���ܲ˵�
char showMenu();

//ѧ����Ϣ¼��
void getStuInfo(List* list);

//��ӡѧ����Ϣ
void printStuInfo(List* list);

//����ѧ����Ϣ
void saveStuInfo(List* list);

//��ȡѧ����Ϣ
void loadStuInfo(List* list);

//ͳ��ѧ������
void countStuNum(List* list);

//����ѧ����Ϣ
void findStuInfo(List* list);

//�޸�ѧ����Ϣ
void editStuInfo(List* list);

//ɾ��ѧ����Ϣ
void deleteStuInfo(List* list);

