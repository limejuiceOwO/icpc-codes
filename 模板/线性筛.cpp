#include <vector>
#include <algorithm>

bool prime[N];
int divcnt[N];
int mindiv[N],mindivcnt[N]; // minimum prime divisor of i
int phi[N];
//...

void sieve(int n)
{
	vector<int> primelist;
	fill(prime,prime + n,true);
	prime[1] = false;
	mindiv[1] = 1;
	for(int i = 2;i < n;i++) {
		if(prime[i]) {
			primelist.push_back(i);
			mindiv[i] = i;
			mindivcnt[i] = divcnt[i] = 1;
			phi[i] = i - 1;
		}
		for(vector<int>::iterator v = primelist.begin();v != primelist.end();v++) {
			int p = *v, nxt = i * p;
			if(nxt > n)
				break;
			mindiv[nxt] = p;
			prime[nxt] = false;
			divcnt[nxt] = divcnt[i] + 1;
			if(i % p == 0) {
				mindivcnt[nxt] = mindivcnt[i] + 1;
				phi[nxt] = phi[i] * p; // phi[i] * nxt / i
				break;
			} else {
				mindivcnt[nxt] = 1;
				phi[nxt] = phi[i] * (p - 1); // phi[i] * nxt * (p - 1) / i / p
			}
		}
	}
}

int main()
{
	//...
	sieve(n);
	//...
}