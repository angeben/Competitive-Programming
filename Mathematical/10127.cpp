#include <iostream>
#include <string>

using namespace std;

bool rC(){
	int n;
	cin >> n;
	if(!cin) return false;
	if(n == 1) {
		cout << 1 << '\n';
		return true;
	}
	int k = 11%n, count = 2;
	while(k != 0){
		k = (k*10)+1;
		k = k % n;
		count++;
	}
	cout << count << '\n';
	return true;
}

int main(){
	while(rC());
	return 0;
}
