// myCounter.cpp

#include "myCounter.h"

// ���캯������������
myCounter::myCounter() { }
myCounter::myCounter(std::string _expression) : expression(_expression) { }
myCounter::~myCounter() { }

// ���ݽṹ����ʵ��

// ��ʼ����ջ
void initLStack(LStack*& ls) {
	ls = new LStack;
	ls->next = 0;
}

// ��ʼ������
void initDeque(Deque& deque) {
	for (size_t i = 0; i < MaxSize; ++i) {		// �����ʼ���ڴ�
		deque.data[i] = ' ';
	}
	deque.front = deque.rear = 0;
}

// ���
void enDeque(Deque& de, char& op) {
	if ((de.rear + 1) % MaxSize == de.front) {
		std::cerr << "����" << '\n';
		return;
	}
	de.rear = (de.rear + 1) % MaxSize;
	de.data[de.rear] = op;
	return;
}

// ����
char deDeque(Deque& de) {
	if (de.front == de.rear) {
		std::cerr << "�ӿ�" << '\n';
		return ' ';
	}
	de.front = (de.front + 1) % MaxSize;
	char op = de.data[de.front];
	return op;
}

// ���ʽ�п� Ϊ���򷵻� 1
bool myCounter::isEmpty(std::string& exp) {
	if (exp.size() == 0) return 1;		// ɶ��û��
	for (auto const& s : exp) {
		if (s != ' ') return 0;			// �зǿո��ַ���
	}
	return 1;							// ȫΪ�ո�
}

// �������ȼ�
int myCounter::priority(char& op) {
	auto n = 0;   // ����ֵ n �Ĵ�С�������ȼ�
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

// �����м�ֵ
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
			std::cerr << "��������Ϊ��" << '\n';
			return 0;
		}
		else {
			return a / b;
		}
	default:
		std::cerr << "���ʽ����" << '\n';
		return 0;
	}
}

// �ж��ַ��Ƿ�Ϊ���� ���򷵻� 1
bool myCounter::isNumber(char& num) {
	return num >= '0' && num <= '9';
}

// ƥ������ ƥ���򷵻� 1
bool myCounter::isMatch(std::string& brackets) {
	if (isEmpty(brackets)) {
		std::cerr << "��δ������ʽ!" << '\n';
		return 0;
	}
	// ������ջ
	LSlist stack = new LStack;
	// ��ͷ�ڵ��ÿ�
	//stack->next = 0;
	// ��ʼ����ջ������һ�й���ͬ��
	initLStack(stack);
	for (size_t i = 0; i < brackets.size(); ++i) {
		if (brackets[i] == '(') {		// ���������Ž�ջ
			LStack* Op = new LStack;
			Op->op = '(';
			Op->next = stack->next;
			stack->next = Op;
		}
		if (brackets[i] == ')') {		// ���������ų�ջ
			if (stack->next == 0) {
				std::cerr << "����ƥ�����" << '\n';
				return 0;
			}
			else {
				LStack* temp = stack;	// ��ջ����ɾ��ͷ�ڵ㣨�൱��ջ����
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
		std::cerr << "����ƥ��ʧ��" << '\n';
		return 0;
	}
}

// ������
// ����Ϊ 0 �򷵻� 1
bool myCounter::isDividebyZero(std::string& brackets) {
	for (size_t i = 0; i < brackets.size() - 1; ++i) {
		if (brackets[i] == '/' && brackets[i + 1] == '0') {
			std::cerr << "��������Ϊ0" << '\n';
			return 1;
		}
	}
	return 0;
}

// �������������Ƿ����� û���򷵻� 1
bool myCounter::isMatchOp(std::string& exp) {
	char op[]{ '+', '-', '*', '/' };
	auto count = 0;
	for (size_t i = 0; i < exp.size(); ++i) {
		for (auto o : op) {
			if (exp[i] == o) {
				++count;
				if (count == 2) {		// ���������������������ʽ����
					std::cerr << "������ʽ����" << '\n';
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

// �������λ�Ƿ���� û���򷵻� 1
bool myCounter::isMatchNum(std::string& exp) {
	for (size_t i = 0; i < exp.size() - 1; ++i) {
		if (isNumber(exp[i]) && isNumber(exp[i + 1])) {
			std::cerr << "���ʽ����" << '\n';
			return 0;
		}
	}
	return 1;
}

// ���ַ���ȥ���ո�
std::string myCounter::deleteSpace(std::string& str) {
	std::string exp;
	// ȥ���ո�
	for (auto const& t : str) {
		if (t != ' ') exp += t;
	}
	/*for (size_t i = 0; i < brackets.size(); ++i) {
		if (brackets[i] != ' ') exp += brackets[i];
	}*/
	return exp;
}

// ��׺ת��׺
Deque myCounter::InfixtoSuffix(std::string& brackets) {
	std::string exp;
	// ȥ���ո�
	exp = deleteSpace(brackets);
	// ���ԭ���ʽ�Ĺ�����ʽ
	std::cout << "ԭʽ=" << exp << '\n';

	// ��һ���ж��Ƿ���������
	if (isEmpty(exp)) {
		std::cerr << "���ʽΪ��" << '\n';
		exit(0);
	}
	// �ڶ����ж������Ƿ�ƥ��
	if (!isMatch(exp)) {
		std::cerr << "���Ų�ƥ��" << '\n';
		exit(0);
	}
	// �������ж���û�б�����Ϊ 0
	if (isDividebyZero(exp)) {
		std::cerr << "����Ϊ 0" << '\n';
		exit(0);
	}
	// ���Ĳ��ж������Ƿ���󣬱�������ֻ�������λ����
	if (!isMatchNum(exp)) {
		std::cerr << "���������ʽ����" << '\n';
		exit(0);
	}
	// ���岽�ж�������Ƿ�����
	if (!isMatchOp(exp)) {
		std::cerr << "������������ʽ����" << '\n';
		exit(0);
	}

	Deque deque;					  // ���׺���ʽ
	initDeque(deque);
	char op[MaxSize]{}; int top = -1;   // ��ʱ������ջ
	for (size_t i = 0; i < MaxSize; ++i) {	//��ʼ��ջ�ڴ�
		op[i] = ' ';
	}
	for (size_t i = 0; i < exp.size(); ++i) {
		if (isNumber(exp[i])) {		// ����ֱ����ջ
			enDeque(deque, exp[i]);
		}
		else if (top == -1 && !isNumber(exp[i])) {	// ����ջΪ�գ�����ֱ����ջ
			op[++top] = exp[i];
		}
		else if (exp[i] == '(') {	// ������ֱ����ջ
			op[++top] = exp[i];
		}
		else if (exp[i] == ')') {   // ���������Ƚ����������ֱ�����������Ž����ջ
			while (top > 0 && op[top] != '(') {
				enDeque(deque, op[top]);
				--top;
			}
			--top;
		}
		else {
			while (top != -1 && priority(op[top]) >= priority(exp[i])) {  // ���ȼ����ڵ��ڵ������
				enDeque(deque, op[top]);
				--top;
			}
			op[++top] = exp[i];
		}
	}
	// ������ top < -1
	if (top < -1) {
		exit(0);
	}
	while (top != -1) {			// �����в��������
		enDeque(deque, op[top]);
		--top;
	}

	return deque;
}

// �����׺���ʽ
int myCounter::compute(Deque& deque) {
	std::string expression;
	// ������Ԫ��ת��Ϊ�ַ������ڲ���
	while (deque.front != deque.rear) {
		expression += deDeque(deque);
	}
	// �����׺���ʽ
	std::cout << "��׺���ʽΪ��" << expression << '\n';
	// ��������ջ
	int stack[MaxSize]{}; int top = -1;
	for (size_t i = 0; i < MaxSize; ++i) {		// �����ʼ��
		stack[i] = 0;
	}
	auto num1 = 0;
	auto num2 = 0;
	for (auto t : expression) {
		if (isNumber(t)) {		// ������ֱ����ջ
			stack[++top] = t - '0';
		}
		else if (top > 0) {					// ����ȡ�����������������������ջ
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
	// ��ջ��ΨһԪ�أ����������ջ
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

// ���ز���ӡ���
void myCounter::print() {
	Deque dq = InfixtoSuffix(expression);
	// Ϊ�����ۣ����ǰȥ�ո�
	std::string temp = deleteSpace(expression);
	std::cout << temp << "=" << compute(dq) << '\n';
}

// ģʽ�л�
void  myCounter::mode() {
	LPWSTR lp = TEXT("СС�׼�����");
	SetConsoleTitle(lp);
	system("color 30");
	std::cout << "ģʽ1 ��ʷ��¼ģʽ \t ģʽ2 һ��������ģʽ" << '\n';
	std::cout << "1 or 2 ��";
	auto choice = 1;
	while (!(std::cin >> choice)) {
		std::cout << "�������Ͷ�����" << std::endl;
		std::cin.clear();  // ����
		std::cin.ignore(999, '\n'); // ���������(ֱ���ո񣬺��ո�)����
		// ������һ�����ҵ� vs ����������ã��������ѭ�������ҷ��˺þ�
		// std::cin.sync();   // ��ջ���������
		std::cout << "�����䣺";
	}
	if (choice != 1 && choice != 2) {
		std::cerr << "��������" << std::endl;
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

// ģʽ1 ��ʷ��¼ģʽ
void myCounter::mode1() {
	LPWSTR lp = TEXT("ģʽ1 ��ʷ��¼ģʽ");
	SetConsoleTitle(lp);
	system("color 30");
	auto done = 1;
	auto temp = 0;
	while (done) {
		std::string input;
		std::cout << "����������ʽ��";
		//std::cin >> input;  // cin ���ܽ��պ��ո��ַ���
		// ����  std::cin.get();  std::cin.ignore(); ���ַ���ѡһ��
		// ���ڽ���һ���ַ� �� '\n'
		// std::cin.get();
		// ���ں���һ���ַ� �� '\n'
		std::cin.ignore();
		getline(std::cin, input);
		myCounter* d = new myCounter(input);
		d->print();
		delete d;
		std::cout << "��Ҫ���������� ��Ҫ������ 1 �������� 0  ģʽ�л����� -1�� ";
		// ��������������������������ÿ�μ�������ٽ��м���ʱ����
		std::cin >> temp;
		std::cout << '\n';
		// system("cls");
		if (temp == -1) {
			system("cls");
			// �л�ģʽ
			runMode();
			// return mode();		// ����ģʽ�л�
		}
		else {
			done = temp;
		}
	}
}
// ģʽ2 һ������ģʽ  ����һ����������
void myCounter::mode2() {
	LPWSTR lp = TEXT("ģʽ2 һ��������ģʽ");
	SetConsoleTitle(lp);
	system("color 30");
	auto done = 1;
	auto temp = 0;
	while (done) {
		std::string input;
		std::cout << "����������ʽ��";
		//std::cin >> input;  // cin ���ܽ��պ��ո��ַ���
		// ����  std::cin.get();  std::cin.ignore(); ���ַ���ѡһ��
		// ���ڽ���һ���ַ� �� '\n'
		std::cin.get();
		// ���ں���һ���ַ� �� '\n'
		// std::cin.ignore();
		getline(std::cin, input);
		myCounter* d = new myCounter(input);
		d->print();
		delete d;
		std::cout << "��Ҫ���������� ��Ҫ������ 1 �������� 0  ģʽ�л����� -1�� ";
		std::cin >> temp;
		std::cout << '\n';
		if (temp == -1) {
			system("cls");
			// �л�ģʽ
			runMode();
			// �������������ַ���
			// return mode();		// ����ģʽ�л�
		}
		else {
			done = temp;
		}
		// ��������������������������ÿ�μ�������ٽ��м���ʱ����
		system("cls");
		done = temp;
	}
}

// ����ģʽ�л�
void myCounter::runMode() {
	myCounter* m = new myCounter();
	m->mode();
	delete m;
}

// ����ģʽ 1
void myCounter::runMode1() {
	myCounter* m = new myCounter();
	m->mode1();
	delete m;
}
// ����ģʽ 2
void myCounter::runMode2() {
	myCounter* m = new myCounter();
	m->mode2();
	delete m;
}