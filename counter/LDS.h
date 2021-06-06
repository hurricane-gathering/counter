// LDS.h

#pragma once
#include <iostream>

int const MaxSize = 50;

// ������ջ
typedef struct LStack {
	std::string op;
	struct LStack* next;
	LStack() : next(nullptr) { }
	LStack(std::string s) : op(s), next(nullptr) { }
}LStack, * LSlist;

// ��ʼ����ջ
void initLStack(LStack*&);

// �������
typedef struct {
	char data[MaxSize];
	int front;
	int rear;
} Deque;

// ��ʼ������
void initDeque(Deque&);

// ���
void enDeque(Deque&, char&);

// ����
char deDeque(Deque&);
