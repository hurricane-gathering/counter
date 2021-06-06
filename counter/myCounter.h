// myCounter.h

#pragma once
#include <string>
#include <windows.h>

#include "LDS.h"

class myCounter
{
public:
	// ���캯������������
	myCounter();
	myCounter(std::string);
	~myCounter();

	// ��׺ת��׺
	Deque InfixtoSuffix(std::string&);
	// �����׺���ʽ
	int compute(Deque&);
	// ���ز���ӡ���
	void print();
	// ģʽѡ��
	void  mode();
	// ģʽ1 ��ʷ��¼ģʽ
	void mode1();
	// ģʽ2 һ������ģʽ
	void mode2();

private:
	// ���ʽ�п�
	bool isEmpty(std::string&);
	// �������ȼ�
	int priority(char&);
	// �����м�ֵ
	int compute(int, char, int);
	// �ж��ַ��Ƿ�Ϊ����
	bool isNumber(char&);
	// ƥ������
	bool isMatch(std::string&);
	// ������
	bool isDividebyZero(std::string&);
	// ���������������
	bool isMatchOp(std::string&);
	// �������λ�Ƿ����
	bool isMatchNum(std::string&);
	// ���ַ���ȥ���ո�
	std::string deleteSpace(std::string&);

	// ����ģʽ 1
	void runMode1();
	// ����ģʽ 2
	void runMode2();
	// ����ģʽ�л�
	void runMode();

private:
	std::string  expression;
};
