// Hungarian algorithm
// 1-indexed!
// a can be negative, so min/max is easy :)
// requires n <= m
// Return value is the cost. The vector passed will contain the assignment.

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int INF = 1e+9;
const int N = 205;
const int M = 205;
int n,m;
int a[N][M];

int hungarian(vector<int>& ans)
{
    vector<int> u(n + 1) , v(m + 1) , p(m + 1) , way(m + 1);
    for(int i = 1; i <= n; ++i)
    {
        p[0] = i;
        int j0 = 0;
        vector <int> minv (m + 1, INF) ;
        vector <char> used (m + 1, false) ;
        do
        {
            used[j0] = true;
            int i0 = p [j0], delta = INF, j1;
            for (int j = 1; j <= m; ++j)
            {
                if (!used [j])
                {
                    int cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            }
            for (int j = 0; j <= m; ++j)
            {
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);

        do
        {
            int j1 = way[j0];
            p[j0] = p[j1] ;
            j0 = j1 ;
        } while(j0);
    }
    ans.resize(n+1);
    for (int j = 1; j <= m; ++j)
            ans[p[j]] = j;
    return -v[0];
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        int x,y,v;
        memset(a,0,sizeof(a));
        while (true)
        {
            cin >> x >> y >> v;
            if (x == 0 && y == 0 && v == 0)
                break;
            if (n > m)
                swap(x,y);
            a[x][y] = -v;
        }
        if (n > m)
            swap(n,m);
        vector<int> ans;
        cout << -hungarian(ans) << endl;
    }
}
