
#include "Stack.hpp"
#include <stack>
#include <iostream>
#include <random>
#include <time.h>

int	main() {
	ft::stack<int>	stack;
	std::stack<int>	stack_off;

	srand(time(NULL));

	for (int i = 0 ; i < 20 ; ++i) {
		int	rand_numb = rand();
		stack.push(rand_numb);
		stack_off.push(rand_numb);
	}

	while (!stack.empty() && !stack_off.empty()) {
		std::cout << "Content : ";
		std::cout << stack.top() << "  |  ";
		std::cout << stack_off.top() << std::endl;
		stack.pop();
		stack_off.pop();
	}
}
