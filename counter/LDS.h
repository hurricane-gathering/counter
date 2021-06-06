// LDS.h

#pragma once
#include <iostream>

int const MaxSize = 50;

// 定义链栈
typedef struct LStack {
	std::string op;
	struct LStack* next;
	LStack() : next(nullptr) { }
	LStack(std::string s) : op(s), next(nullptr) { }
}LStack, * LSlist;

// 初始化链栈
void initLStack(LStack*&);

// 定义队列
typedef struct {
	char data[MaxSize];
	int front;
	int rear;
} Deque;

// 初始化队列
void initDeque(Deque&);

// 入队
void enDeque(Deque&, char&);

// 出队
char deDeque(Deque&);
