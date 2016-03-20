#include <cstdio>
#include <vector>
#include <map>
using namespace std;

const int oo = 0x3f3f3f3f;
const int Maxn = 150010;

bool vis[Maxn];
int n, ans, a[Maxn];
map <pair<int, int>, bool> mp;
#define m_p make_pair
vector <int> num;

void swap(int& a, int& b)
{
    a ^= b; b ^= a; a ^= b;
    return;
}

bool check()
{
    for(int i = 1; i < num.size(); ++i)
    {
        if(num[i] & 1)
            { if(a[num[i]] >= a[num[i]-1] || a[num[i]] >= a[num[i]+1]) return false; }
        else if(a[num[i]] <= a[num[i]-1] || a[num[i]] <= a[num[i]+1] ) return false;
    }
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("c.in", "r", stdin);
#endif
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", a+i);
    num.push_back(0);
    a[0] = oo;
    if(n & 1) a[n+1] = oo;
    else a[n+1] = -oo;
    for(int i = 2; i <= n; i += 2)
    {
        bool flg = false;
        if(a[i] <= a[i-1])
        {
            flg = true;
            if(!vis[i-1]) num.push_back(i-1);
            vis[i-1] = true;
        }
        if(a[i] <= a[i+1])
        {
            flg = true;
            if(!vis[i+1]) num.push_back(i+1);
            vis[i+1] = true;
        }
        if(flg)
        {
            if(!vis[i]) num.push_back(i);
            vis[i] = true;
        }
    }
    if(num.size() >= 25)
        return puts("0"),0;
    for(int i = 1; i < num.size(); ++i)
        for(int j = 1; j <= n; ++j)
        {
            if(num[i] == j) continue;
            swap(a[num[i]], a[j]);
            // for(int k = 1; k <= n; ++k) printf("%d ", a[k]);
            // printf("\n");
            if(j % 2 == 1 && (a[j] >= a[j+1] || a[j] >= a[j-1])) { swap(a[num[i]], a[j]); continue; }
            if(j % 2 == 0 && (a[j] <= a[j+1] || a[j] <= a[j-1])) { swap(a[num[i]], a[j]); continue; }
            if(!check()) { swap(a[num[i]], a[j]); continue; }
            if(num[i] < j && (!mp[m_p(num[i], j)])) mp[m_p(num[i], j)] = true, ++ans;
            else if(num[i] > j && !mp[m_p(j, num[i])]) mp[m_p(j, num[i])] = true, ++ans;
            // printf("%d\n", ans);
            swap(a[num[i]], a[j]);
        }
    printf("%d\n", ans);
    return 0;
}
