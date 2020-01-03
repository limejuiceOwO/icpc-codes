#include<iostream>
#include<cstdlib> 
using namespace std;

void hanoi(int a,int b,int c,int n) // move a to b,c is backup
{
     if(n<=0) return;
     hanoi(a,c,b,n-1);
     cout << a << "->" << b << endl;
     hanoi(c,b,a,n-1);
} 

int main()
{
    int n;
    cin >> n;
    hanoi(1,2,3,n);
    return 0;
} 
