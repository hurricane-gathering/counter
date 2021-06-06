// myCounter.cpp

#include "myCounter.h"

// 构造函数和析构函数
myCounter::myCounter() { }
myCounter::myCounter(std::string _expression) : expression(_expression) { }
myCounter::~myCounter() { }

// 数据结构方法实现

// 初始化链栈
void initLStack(LStack*& ls) {
	ls = new LStack;
	ls->next = 0;
}

// 初始化队列
void initDeque(Deque& deque) {
	for (size_t i = 0; i < MaxSize; ++i) {		// 建议初始化内存
		deque.data[i] = ' ';
	}
	deque.front = deque.rear = 0;
}

// 入队
void enDeque(Deque& de, char& op) {
	if ((de.rear + 1) % MaxSize == de.front) {
		std::cerr << "队满" << '\n';
		return;
	}
	de.rear = (de.rear + 1) % MaxSize;
	de.data[de.rear] = op;
	return;
}

// 出队
char deDeque(Deque& de) {
	if (de.front == de.rear) {
		std::cerr << "队空" << '\n';
		return ' ';
	}
	de.front = (de.front + 1) % MaxSize;
	char op = de.data[de.front];
	return op;
}

// 表达式判空 为空则返回 1
bool myCounter::isEmpty(std::string& exp) {
	if (exp.size() == 0) return 1;		// 啥都没有
	for (auto const& s : exp) {
		if (s != ' ') return 0;			// 有非空格字符串
	}
	return 1;							// 全为空格
}

// 定义优先级
int myCounter::priority(char& op) {
	auto n = 0;   // 用数值 n 的大小代表优先级
	switch (op) {
	case '+':
	case '-':
		n = -1;
		break;
	case '*':
	case '/':
		n = 1;
		break;
	case '(':
		n = -2;
		break;
	case ')':
		n = 2;
	default:
		break;
	}
	return n;
}

// 计算中间值
int myCounter::compute(int a, char op, int b) {
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		if (b == 0) {
			std::cerr << "除数不能为零" << '\n';
			return 0;
		}
		else {
			return a / b;
		}
	default:
		std::cerr << "表达式有误" << '\n';
		return 0;
	}
}

// 判断字符是否为数字 是则返回 1
bool myCounter::isNumber(char& num) {
	return num >= '0' && num <= '9';
}

// 匹配括号 匹配则返回 1
bool myCounter::isMatch(std::string& brackets) {
	if (isEmpty(brackets)) {
		std::cerr << "尚未输入表达式!" << '\n';
		return 0;
	}
	// 创建链栈
	LSlist stack = new LStack;
	// 将头节点置空
	//stack->next = 0;
	// 初始化链栈，下面一行功能同上
	initLStack(stack);
	for (size_t i = 0; i < brackets.size(); ++i) {
		if (brackets[i] == '(') {		// 遇到左括号进栈
			LStack* Op = new LStack;
			Op->op = '(';
			Op->next = stack->next;
			stack->next = Op;
		}
		if (brackets[i] == ')') {		// 遇到右括号出栈
			if (stack->next == 0) {
				std::cerr << "括号匹配错误" << '\n';
				return 0;
			}
			else {
				LStack* temp = stack;	// 出栈就是删除头节点（相当于栈顶）
				stack = stack->next;
				delete temp;
				temp = 0;
			}
		}
	}
	if (stack->next == 0) {
		return 1;
	}
	else {
		std::cerr << "括号匹配失败" << '\n';
		return 0;
	}
}

// 检查除零
// 除数为 0 则返回 1
bool myCounter::isDividebyZero(std::string& brackets) {
	for (size_t i = 0; i < brackets.size() - 1; ++i) {
		if (brackets[i] == '/' && brackets[i + 1] == '0') {
			std::cerr << "除数不能为0" << '\n';
			return 1;
		}
	}
	return 0;
}

// 检查运算符输入是否有误 没错则返回 1
bool myCounter::isMatchOp(std::string& exp) {
	char op[]{ '+', '-', '*', '/' };
	auto count = 0;
	for (size_t i = 0; i < exp.size(); ++i) {
		for (auto o : op) {
			if (exp[i] == o) {
				++count;
				if (count == 2) {		// 有两个运算符连起来则表达式有误
					std::cerr << "输入表达式有误" << '\n';
					return 0;
				}
			}
			else {
				count = 0;
			}
		}
	}
	return 1;
}

// 检查数字位是否出错 没错则返回 1
bool myCounter::isMatchNum(std::string& exp) {
	for (size_t i = 0; i < exp.size() - 1; ++i) {
		if (isNumber(exp[i]) && isNumber(exp[i + 1])) {
			std::cerr << "表达式有误！" << '\n';
			return 0;
		}
	}
	return 1;
}

// 将字符串去除空格
std::string myCounter::deleteSpace(std::string& str) {
	std::string exp;
	// 去除空格
	for (auto const& t : str) {
		if (t != ' ') exp += t;
	}
	/*for (size_t i = 0; i < brackets.size(); ++i) {
		if (brackets[i] != ' ') exp += brackets[i];
	}*/
	return exp;
}

// 中缀转后缀
Deque myCounter::InfixtoSuffix(std::string& brackets) {
	std::string exp;
	// 去除空格
	exp = deleteSpace(brackets);
	// 输出原表达式的规则形式
	std::cout << "原式=" << exp << '\n';

	// 第一步判断是否输入内容
	if (isEmpty(exp)) {
		std::cerr << "表达式为空" << '\n';
		exit(0);
	}
	// 第二步判断括号是否匹配
	if (!isMatch(exp)) {
		std::cerr << "括号不匹配" << '\n';
		exit(0);
	}
	// 第三步判断有没有被除数为 0
	if (isDividebyZero(exp)) {
		std::cerr << "除数为 0" << '\n';
		exit(0);
	}
	// 第四步判断数字是否错误，本计算器只能运算个位算术
	if (!isMatchNum(exp)) {
		std::cerr << "数字输入格式有误" << '\n';
		exit(0);
	}
	// 第五步判断运算符是否有误
	if (!isMatchOp(exp)) {
		std::cerr << "运算符号输入格式有误" << '\n';
		exit(0);
	}

	Deque deque;					  // 存后缀表达式
	initDeque(deque);
	char op[MaxSize]{}; int top = -1;   // 临时操作符栈
	for (size_t i = 0; i < MaxSize; ++i) {	//初始化栈内存
		op[i] = ' ';
	}
	for (size_t i = 0; i < exp.size(); ++i) {
		if (isNumber(exp[i])) {		// 数字直接入栈
			enDeque(deque, exp[i]);
		}
		else if (top == -1 && !isNumber(exp[i])) {	// 符号栈为空，符号直接入栈
			op[++top] = exp[i];
		}
		else if (exp[i] == '(') {	// 左括号直接入栈
			op[++top] = exp[i];
		}
		else if (exp[i] == ')') {   // 右括号则先将操作符入队直到遇见左括号将其出栈
			while (top > 0 && op[top] != '(') {
				enDeque(deque, op[top]);
				--top;
			}
			--top;
		}
		else {
			while (top != -1 && priority(op[top]) >= priority(exp[i])) {  // 优先级大于等于的先入队
				enDeque(deque, op[top]);
				--top;
			}
			op[++top] = exp[i];
		}
	}
	// 不允许 top < -1
	if (top < -1) {
		exit(0);
	}
	while (top != -1) {			// 将所有操作符入队
		enDeque(deque, op[top]);
		--top;
	}

	return deque;
}

// 计算后缀表达式
int myCounter::compute(Deque& deque) {
	std::string expression;
	// 将队列元素转化为字符串便于操作
	while (deque.front != deque.rear) {
		expression += deDeque(deque);
	}
	// 输出后缀表达式
	std::cout << "后缀表达式为：" << expression << '\n';
	// 定义运算栈
	int stack[MaxSize]{}; int top = -1;
	for (size_t i = 0; i < MaxSize; ++i) {		// 建议初始化
		stack[i] = 0;
	}
	auto num1 = 0;
	auto num2 = 0;
	for (auto t : expression) {
		if (isNumber(t)) {		// 数字则直接入栈
			stack[++top] = t - '0';
		}
		else if (top > 0) {					// 否则取出两个操作数进行运算后入栈
			num2 = stack[top]; --top;
			num1 = stack[top]; --top;
			switch (t)
			{
			case '+':
				stack[++top] = compute(num1, t, num2); break;
			case '-':
				stack[++top] = compute(num1, t, num2); break;
			case '*':
				stack[++top] = compute(num1, t, num2); break;
			case '/':
				stack[++top] = compute(num1, t, num2); break;
			default:
				break;
			}
		}
	}
	// 将栈中唯一元素（即结果）出栈
	auto answer = 0;
	if (top < 0) {
		exit(0);
	}
	else {
		answer = stack[top];
		--top;
	}

	return answer;
}

// 返回并打印结果
void myCounter::print() {
	Deque dq = InfixtoSuffix(expression);
	// 为了美观，输出前去空格
	std::string temp = deleteSpace(expression);
	std::cout << temp << "=" << compute(dq) << '\n';
}

// 模式切换
void  myCounter::mode() {
	LPWSTR lp = TEXT("小小米计算器");
	SetConsoleTitle(lp);
	system("color 30");
	std::cout << "模式1 历史记录模式 \t 模式2 一次性运算模式" << '\n';
	std::cout << "1 or 2 ：";
	auto choice = 1;
	while (!(std::cin >> choice)) {
		std::cout << "输入类型都错了" << std::endl;
		std::cin.clear();  // 解锁
		std::cin.ignore(999, '\n'); // 清除缓冲区(直到空格，含空格)内容
		// 下面这一句在我的 vs 里好像不起作用，会进入死循环，让我烦了好久
		// std::cin.sync();   // 清空缓冲区内容
		std::cout << "请重输：";
	}
	if (choice != 1 && choice != 2) {
		std::cerr << "输入有误" << std::endl;
		runMode();
	}
	system("cls");
	switch (choice)
	{
	case 1:
		runMode1();
	case 2:
		runMode2();
	default:
		break;
	}
}

// 模式1 历史记录模式
void myCounter::mode1() {
	LPWSTR lp = TEXT("模式1 历史记录模式");
	SetConsoleTitle(lp);
	system("color 30");
	auto done = 1;
	auto temp = 0;
	while (done) {
		std::string input;
		std::cout << "输入运算表达式：";
		//std::cin >> input;  // cin 不能接收含空格字符串
		// 下面  std::cin.get();  std::cin.ignore(); 两种方法选一种
		// 用于接收一个字符 如 '\n'
		// std::cin.get();
		// 用于忽略一个字符 如 '\n'
		std::cin.ignore();
		getline(std::cin, input);
		myCounter* d = new myCounter(input);
		d->print();
		delete d;
		std::cout << "需要继续运算吗？ 需要请输入 1 结束输入 0  模式切换输入 -1： ";
		// 下面这行是清屏操作，加上则每次计算结束再进行计算时清屏
		std::cin >> temp;
		std::cout << '\n';
		// system("cls");
		if (temp == -1) {
			system("cls");
			// 切换模式
			runMode();
			// return mode();		// 进入模式切换
		}
		else {
			done = temp;
		}
	}
}
// 模式2 一次运算模式  多了一个清屏操作
void myCounter::mode2() {
	LPWSTR lp = TEXT("模式2 一次性运算模式");
	SetConsoleTitle(lp);
	system("color 30");
	auto done = 1;
	auto temp = 0;
	while (done) {
		std::string input;
		std::cout << "输入运算表达式：";
		//std::cin >> input;  // cin 不能接收含空格字符串
		// 下面  std::cin.get();  std::cin.ignore(); 两种方法选一种
		// 用于接收一个字符 如 '\n'
		std::cin.get();
		// 用于忽略一个字符 如 '\n'
		// std::cin.ignore();
		getline(std::cin, input);
		myCounter* d = new myCounter(input);
		d->print();
		delete d;
		std::cout << "需要继续运算吗？ 需要请输入 1 结束输入 0  模式切换输入 -1： ";
		std::cin >> temp;
		std::cout << '\n';
		if (temp == -1) {
			system("cls");
			// 切换模式
			runMode();
			// 或者用下面这种方法
			// return mode();		// 进入模式切换
		}
		else {
			done = temp;
		}
		// 下面这行是清屏操作，加上则每次计算结束再进行计算时清屏
		system("cls");
		done = temp;
	}
}

// 调用模式切换
void myCounter::runMode() {
	myCounter* m = new myCounter();
	m->mode();
	delete m;
}

// 调用模式 1
void myCounter::runMode1() {
	myCounter* m = new myCounter();
	m->mode1();
	delete m;
}
// 调用模式 2
void myCounter::runMode2() {
	myCounter* m = new myCounter();
	m->mode2();
	delete m;
}