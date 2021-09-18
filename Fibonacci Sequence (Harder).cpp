#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
// const ll mod=998244353;
const ll mod=1000000007;
const int N=2e6+5;

ll a,b,c,d;
void fastDoublingfib(long long int n,long long int ans[])
{
    if(n == 0)
    {
        ans[0] = 0;
        ans[1] = 1;
        return;
    }
    fastDoublingfib((n/2),ans);
    a = ans[0];
    b = ans[1];
    c = 2*b - a;
    if(c < 0)
        c += mod;
    c = (a * c) % mod;
    d = (a*a + b*b) % mod;
    if(n%2 == 0)
    {
        ans[0] = c;
        ans[1] = d;
    }
    else
    {
        ans[0] = d;
        ans[1] = c+d;
    }
}

int main() {
    fast
    ll a=1, b=1, c=0, period=1;
    // while(a!=0 || b!=1) { // Uncomment to check value of period
    //     c=a;
    //     a=b;
    //     b+=c;
    //     if(b>=mod)
    //      b-=mod;
    //     period++;
    // }
    // cout<<period;
    
    // period=1996488708;
    
    period=2000000016;
    string s;
    cin>>s;
    ll res=0;
    for(ll i=0;i<s.length();i++) {
        res = (res*10 + (ll)(s[i]-'0'))%period; 
    }
    long long int ans[2]={0};
    fastDoublingfib(res,ans);
    cout<<ans[0]<<"\n";
}