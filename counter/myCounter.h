// myCounter.h

#pragma once
#include <string>
#include <windows.h>

#include "LDS.h"

class myCounter
{
public:
	// 构造函数和析构函数
	myCounter();
	myCounter(std::string);
	~myCounter();

	// 中缀转后缀
	Deque InfixtoSuffix(std::string&);
	// 计算后缀表达式
	int compute(Deque&);
	// 返回并打印结果
	void print();
	// 模式选择
	void  mode();
	// 模式1 历史记录模式
	void mode1();
	// 模式2 一次运算模式
	void mode2();

private:
	// 表达式判空
	bool isEmpty(std::string&);
	// 定义优先级
	int priority(char&);
	// 计算中间值
	int compute(int, char, int);
	// 判断字符是否为数字
	bool isNumber(char&);
	// 匹配括号
	bool isMatch(std::string&);
	// 检查除零
	bool isDividebyZero(std::string&);
	// 检查运算符输入错误
	bool isMatchOp(std::string&);
	// 检查数字位是否出错
	bool isMatchNum(std::string&);
	// 将字符串去除空格
	std::string deleteSpace(std::string&);

	// 调用模式 1
	void runMode1();
	// 调用模式 2
	void runMode2();
	// 调用模式切换
	void runMode();

private:
	std::string  expression;
};
