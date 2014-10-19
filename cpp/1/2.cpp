#include <iostream>
using namespace std;

int count(int a, int b) 
{
	int c = 0;
	for (int i=a; i<b; i++) {
		if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0){
			c++;
		}
	}
	return c;
}


int main()
{
    int a = 0;
    int b = 0;

    cin >> a >> b;
    
    cout << count(a, b);

    return 0;
}

