#include <iostream>
#include <string>

using namespace std;

bool rC(){
	string s;
	cin >> s;
	if(!cin) return false;
	float cc = 0, c = 0;
	for(int i = 0; i < s.size(); ++i)
		if(s[i] == '0') c++;
	for(int i = 0; i < s.size(); ++i){
		if(s[i] == s[(i+1)%s.size()] && s[i] == '0') cc++;
	}
	if (cc*s.size() > c*c) printf("SHOOT\n");
	else if (cc*s.size() == c*c) printf("EQUAL\n");
	else printf("ROTATE\n");
	return true;
}

int main(){
	while(rC());
	return 0;
}
