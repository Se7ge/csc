#include <iostream>
void foo(char) { std::cout << "char" << std::endl; }
void foo(signed char) { std::cout << "signed char" << std::endl; }
void foo(unsigned char) { std::cout << "unsigned char" << std::endl; }

void promotion(char &) { std::cout << "char" << std::endl; }
void promotion(int &) { std::cout << "int" << std::endl; }
void promotion(long &) { std::cout << "long" << std::endl; }

int main(){
	foo('a');
	//foo(97);
	short sh=10;
	promotion(sh);
	return 0;
}
