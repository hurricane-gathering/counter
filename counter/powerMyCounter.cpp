/*
*
* 作者 ：hurricane&&storming
*
* 日期 ：2021.5.28
*
*/

#include "myCounter.h"

int main() {
	LPWSTR lp = TEXT("小小米计算器");
	SetConsoleTitle(lp);
	system("color 30");
	myCounter* count = new myCounter;
	count->mode();
	delete count;

	system("pause");
	return 0;
}