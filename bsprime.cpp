/*
*/

#pragma comment(linker, "/STACK:16777216")
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <string>
#include <complex>
#include <math.h>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <stdio.h>
#include <stack>
#include <algorithm>
#include <list>
#include <ctime>
#include <memory.h>
#include <assert.h>

#define y0 sdkfaslhagaklsldk
#define y1 aasdfasdfasdf
#define yn askfhwqriuperikldjk
#define j1 assdgsdgasghsf
#define tm sdfjahlfasfh
#define lr asgasgash
#define norm asdfasdgasdgsd

#define eps 1e-9
#define M_PI 3.141592653589793
#define bs 1000000007
#define bsize 350

using namespace std;

const int INF = 1e9;
const int N = 40000000;

const int STEP = 100000;

int prime[110000];
char pr[STEP + 5];
vector<int> primes;
int tests;
int ptr;

int query[100000];
vector<pair<int, int> > queries;
int ans[100000];
int dp[1 << 16];

int count_ones(int x)
{
	if (x < (1 << 16))
	{
		return dp[x];
	}
	return count_ones(x % (1 << 16)) + dp[x >> 16];
}

int TOTAL;
int TOTAL_ones;

int get_bit(int val, int ps)
{
	return (val >> ps) & 1;
}

int count_bits(int x)
{
	int res = 0;
	while (x)
	{
		res++;
		x /= 2;
	}
	return res;
}

void add_prime(int val)
{
	if (ptr == queries.size())
		return;

	int here = count_bits(val);
	while (ptr < queries.size() && queries[ptr].first <= TOTAL + here)
	{
		//cout << val << endl;
		ans[queries[ptr].second] = TOTAL_ones;
		for (int j = 1; j <= queries[ptr].first - TOTAL; j++)
			ans[queries[ptr].second] += get_bit(val, here - j);
		++ptr;
	}
	TOTAL += here;
	TOTAL_ones += count_ones(val);
}

int main(){
	//freopen("fabro.in","r",stdin);
	//freopen("fabro.out","w",stdout);
	//freopen("F:/in.txt", "r", stdin);
	//freopen("F:/output.txt", "w", stdout);
	//ios_base::sync_with_stdio(0);
	//cin.tie(0);

	for (int i = 1; i < (1 << 16); i++)
	{
		dp[i] = dp[i / 2] + i % 2;
	}

	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++)
	{
		scanf("%d", &query[i]);
		queries.push_back(make_pair(query[i], i));
	}

	sort(queries.begin(), queries.end());

	int OPS = 0;
	prime[1] = 1;
	for (int i = 2; i <= 1000; i++)
	{
		if (prime[i] == 0)
		{
			for (int j = i * i; j <= 100000; j += i)
				prime[j] = 1;
		}
	}

	for (int i = 1; i <= 100000; i++)
	{
		if (prime[i] == 0)
			add_prime(i);
	}


	for (int start = 100000; start < 200000000; start += STEP)
	{
		if (ptr == queries.size())
			break;

		for (int i = 0; i <= STEP; i++)
		{
			pr[i] = 0;
		}
		for (int i = 2; i <= 10500 && i*i <= start + STEP; i++)
		{
			if (prime[i] == 0)
			{
				int shift = i - start %i;
				for (int j = shift + start; j <= start + STEP; j += i)
				{
					pr[(j - start)] = 1;
					++OPS;
				}
			}
		}
		for (int j = 1; j <= STEP; j++)
		{
			if (pr[j] == 0)
			{
				add_prime(j + start);
			}
		}
	}

	for (int i = 1; i <= tests; i++)
	{
		printf("%d\n", ans[i]);
	}

	//cout << OPS << endl;

	cin.get(); cin.get();
	return 0;
}