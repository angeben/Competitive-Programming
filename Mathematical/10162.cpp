#include <string>
#include <iostream>

using namespace std;
int si[20] = {1,4,7,6,5,6,3,6,9,0,1,6,3,6,5,6,7,4,9,0};
int ss[20] = {1};
int s100[101] = {0};

void init(){
	for(int i = 1; i < 20; ++i)
		ss[i] = (ss[i-1] + si[i])%10;

	for(int i = 0; i < 100; ++i){
		s100[i+1] = (ss[i%20] + (i/20) * 4) %10;
		//cout << s100[i] << ' ';
	}
}

bool rc(){
	string s;
	cin >> s;
	int n ;
	if(s.size() > 1)
		n = (10*(s[s.size()-2]-'0')) + s[s.size()-1]-'0';
	else n = s[0]-'0';
	if(s == "0") return false;
	cout << s100[n] << '\n';
	return true;
}

int main(){
	init();
	while(rc());
	return 0;
}
