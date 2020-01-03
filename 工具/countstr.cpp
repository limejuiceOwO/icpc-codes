#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<string,int> PAIR;
map<string,int> cnt;
vector<PAIR> t;


inline int cmp(const PAIR& x, const PAIR& y)
{
    return x.second > y.second;
}


int main()
{
	string s;
	int i=1;
	while(!getline(cin,s).eof()) cnt[s]++;
	for(map<string,int>::iterator cur=cnt.begin();cur!=cnt.end();cur++) t.push_back(make_pair(cur->first,cur->second));
	sort(t.begin(),t.end(),cmp);
	for(vector<PAIR>::iterator cur=t.begin();cur!=t.end();cur++,i++)
		cout<<i<<' '<<cur->first<<' '<<cur->second<<endl;
	return 0;
}
