#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int>ii;
typedef vector<ii> vii;
const int mx=2e5+4;
const int INF=2e5+9;
vi g[mx];
int dp[mx][20],lv[mx],n;
void dfs1(int u,int p)
{
    for(int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if(v!=p){
            dp[v][0]=u;
            lv[v]=lv[u]+1;
            dfs1(v,u);
        }
    }
}
void preprocess()
{
    lv[1]=0;
    memset(dp,-1,sizeof dp);
    dfs1(1,-1);
    for(int j=1;(1<<j)<n;j++){
        for(int i=1;i<=n;i++)
            if(dp[i][j-1]!=-1) dp[i][j]=dp[dp[i][j-1]][j-1];
    }
}
int Lca(int p,int q)
{
    if(lv[p]<lv[q]) swap(p,q);
    int log=1;
    while(1){
        int next=log+1;
        if( (1<<next)>lv[p] ) break;
        log++;
    }
    for(int i=log;i>=0;i--)
        if(lv[p]-(1<<i)>=lv[q]) p=dp[p][i];
    if(p==q) return p;
    for(int i=log;i>=0;i--){
        if(dp[p][i]!=-1 && dp[p][i]!=dp[q][i])
            p=dp[p][i],q=dp[q][i];
    }
    return dp[p][0];
}
int dist(int u,int v){ return lv[u]+lv[v]-2*lv[Lca(u,v)]; }
int main()
{
    int i,r,u,v,x,q;
    cin>>n;
    for(i=1;i<n;i++){
        cin>>u>>v;
        g[u].pb(v);
        g[v].pb(u);
    }
    ii p[6];
    preprocess();
    cin>>q;
    while(q--){
        cin>>r>>u>>v;
        p[0].ss=r;
        p[1].ss=u;
        p[2].ss=v;
        p[3].ss=Lca(r,u);
        p[4].ss=Lca(r,v);
        p[5].ss=Lca(u,v);
        for(i=0;i<6;i++){
            int x=p[i].ss;
            p[i].ff=dist(x,r)+dist(x,u)+dist(x,v);
           //cout<<p[i].ff<<" ";
        }
        sort(p,p+6);
        //cout<<endl;
        cout<<p[0].ss<<endl;
    }
    return 0;
}
