/*
*
* ���� ��hurricane&&storming
*
* ���� ��2021.5.28
*
*/

#include "myCounter.h"

int main() {
	myCounter* count = new myCounter();
	count->mode();
	delete count;

	system("pause");
	return 0;
}