#include<bits/stdc++.h> 
using namespace std; 
int numa[20005],numb[20005],ans[40010]; 


int get_integer(int *num)
{ 
    stack<char> s;//这个栈很蛋疼，不知有没有更好的实现。。。 
    int cnt=0,cur=0,k=1; 
    char c; 
    while((c=getchar())!=EOF&&c!='\n'&&c!=' ') 
        s.push(c); 
    while(!s.empty()){ 
        c=s.top()-'0'; 
        s.pop(); 
        if(k==100000000) { 
            num[cnt++]=cur; 
            cur=c; 
            k=10; 
        } else { 
            cur+=c*k; 
            k*=10; 
        } 
    } 
    num[cnt++]=cur; 
    return cnt; 
} 


signed main() 
{ 
    int m=get_integer(numa),n=get_integer(numb); 
    for(int i=0;i<m;i++) { 
        long long ov=0; 
        for(int j=0;j<n;j++) { 
            long long q=(long long)numa[i]*numb[j]+ans[i+j]+ov; 
            ans[i+j]=q%100000000; 
            ov=q/100000000; 
        } 
        ans[i+n]=ov; 
    } 
    if(ans[m+n-1]) 
        printf("%d%08d",ans[m+n-1],ans[m+n-2]); 
    else  
        printf("%d",ans[m+n-2]); 
    for(int i=m+n-3;i>=0;i--) 
        printf("%08d",ans[i]); 
    puts(""); 
    return 0; 
} 

