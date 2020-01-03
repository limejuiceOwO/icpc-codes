#include<iostream>
#include<algorithm>
using namespace std;

bool cmp(int a,int b)
{
  return a>b;
}

void swap(int &a,int &b)
{
  int t=a;
  a=b;
  b=t;
}

void reverse(int *s,int *e)
{
  e--;
  while(s<e) {
    swap(*(s++),*(e--));
  }
}

bool my_next_permutation(int *s,int *e)
{
  if(s>=e) return false;
  if(!my_next_permutation(s+1,e)) {
    int *index=lower_bound(s+1,e,*s,cmp)-1;
    if(index==s) return false;
    swap(*index,*s);
    reverse(s+1,e);
  }
  return true;
}

int main()
{
  int arr[100],n;
  cin>>n;
  for(int i=0;i<n;i++)
    cin>>arr[i];
  do {
    for(int i=0;i<n;i++)
      cout<<arr[i]<<' ';
    cout<<endl;
  } while(my_next_permutation(arr,arr+n));
  return 0;
}
