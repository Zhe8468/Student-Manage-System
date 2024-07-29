#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//学生数据
typedef struct {
	int number;
	char name[20];
	float score;
}Student;

//链表的每一个节点
typedef struct {
	Student stu;
	struct Node* next;
}Node;

//链表
typedef struct List{
	Node* head; //指向第一个节点
	int size; //节点数量
}List;

//打印功能菜单
char showMenu();

//学生信息录入
void getStuInfo(List* list);

//打印学生信息
void printStuInfo(List* list);

//保存学生信息
void saveStuInfo(List* list);

//读取学生信息
void loadStuInfo(List* list);

//统计学生人数
void countStuNum(List* list);

//查找学生信息
void findStuInfo(List* list);

//修改学生信息
void editStuInfo(List* list);

//删除学生信息
void deleteStuInfo(List* list);

