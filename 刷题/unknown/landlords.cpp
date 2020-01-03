#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int card[15];
int ans;
const int to[]={13,11,12,0,1,2,3,4,5,6,7,8,9,10};

void solve(int d)
{
	int group[4],ans2=0;
	if(d>=ans) return;
	bool update; 
	memset(group,0,sizeof(group));
	for(int i=0;i<14;i++)
		if(card[i])
			group[card[i]-1]++;
	do {
		update=false;
		if(group[3]) {
			group[3]--;
			if(group[0]>=2) group[0]-=2;//四带二
			else if(group[1]>=2) group[1]-=2;//四带二（对）
			else if(group[1]) group[1]--;
			update=true;
		}else if(group[2]) {
			group[2]--;
			if(group[0]) group[0]--;//三带一
			else if(group[1]) group[1]--;//三带二 
			update=true;
		}else if(group[1]) {
			group[1]--;
			update=true;
		}else if(group[0]) {
			group[0]--;
			update=true;
		}
		if(update) ans2++;
	}while(update);
	ans=min(ans,d+ans2);
  	for(int i=0;i<=11;i++) {//顺子 
  		int j; 
		for(j=i;j<=11;j++) {
		    if(!card[j]) break;
		    card[j]--;
		    if(j-i>=4) solve(d+1);
		} 
	    for(j--;j>=i;j--)
	    	card[j]++;
	}
	for(int i=0;i<=11;i++) {//双顺子 
		int j; 
	    for(j=i;j<=11;j++) {
		      if(card[j]<2) break;
		      card[j]-=2;
		      if(j-i>=2) solve(d+1);
	    }
	    for(j--;j>=i;j--)
	    	card[j]+=2; 
	}
	for(int i=0;i<=11;i++) {//三顺子 
		int j; 
	    for(j=i;j<=11;j++) {
		      if(card[j]<3) break;
		      card[j]-=3;
		      if(j-i>=1) solve(d+1);
	    } 
	    for(j--;j>=i;j--)
	    	card[j]+=3; 
	}
}

int main()
{
  int T,n;
  cin>>T>>n;
  while(T--) { 
    memset(card,0,sizeof(card));
    ans=10000;
    for(int i=0;i<n;i++) {
      int a,b;
      //int a;
      cin>>a>>b;
      //cin>>a;
		card[to[a]]++;
    }
    solve(0);
    cout<<ans<<endl;
  }
  return 0;
}
