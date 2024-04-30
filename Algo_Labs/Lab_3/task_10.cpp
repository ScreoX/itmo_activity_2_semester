#include"iostream"
#include"algorithm"

using namespace std;

const int N = 2e6+10;

struct E{
    int u, v, w, id;
    bool operator <(const E&a)const {
        return w < a.w;
    }
}e[N];

int p[N];

int get(int x){
    if (p[x] != x){
        p[x] = get(p[x]);
    }
    return p[x];
}

struct Edge{
    int v, next, w;
}edge[N << 1];

int head[N], tot;
void connect(int u, int v, int w){
    edge[++tot] = {v, head[u], w};
    head[u] = tot;
}

int fa[N][20];
int f[N][20];
int dep[N];
long long answer[N];

void dfs(int u){
    for(int i = head[u]; i; i = edge[i].next){
        int v = edge[i].v;
        int w = edge[i].w;
        if(v == fa[u][0])
            continue;
        fa[v][0] = u;
        f[v][0] = w;
        dep[v] = dep[u] + 1;
        for(int j = 1; j <= 18; j++){
            fa[v][j] = fa[fa[v][j - 1]][j - 1];
            f[v][j] = max(f[fa[v][j - 1]][j - 1],f[v][j - 1]);
        }
        dfs(v);
    }
}
int lca(int u, int v){
    int ans = 0;
    if(dep[u] < dep[v])
        swap(u,v);
    for(int k = 18;k >= 0; k--){
        if(dep[fa[u][k]] >= dep[v]){
            ans = max(f[u][k], ans);
            u = fa[u][k];
        }
    }
    if(u != v){
        for(int k = 18; k >= 0; k--){
            if(fa[u][k] != fa[v][k]){
                ans = max({ans,f[u][k], f[v][k]});
                u = fa[u][k];
                v = fa[v][k];
            }
        }
    }
    else{
        return ans;
    }
    ans = max({ans, f[u][0], f[v][0]});
    return ans;
}

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 1;i <= m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        e[i] = {u, v, w, i};
    }
    for(int i = 1; i <= n; i++)
        p[i] = i;
    sort(e + 1, e + 1 + m);
    long long W = 0;
    for(int i = 1; i <= m; i++){
        int u = e[i].u;
        int v = e[i].v;
        int w = e[i].w;;
        u = get(u);
        v = get(v);
        if(u != v){
            p[u] = v;
            connect(e[i].u, e[i].v,w);
            connect(e[i].v, e[i].u,w);
            W += w;
        }
    }

    dep[1] = 1;
    dfs(1);
    for(int i = 1; i <= m; i++){
        int u = e[i].u;
        int v = e[i].v;
        int id = e[i].id;
        int t = lca(u,v);
        answer[id] = W - t + e[i].w;
    }

    for(int i = 1; i <= m; i++){
        cout << answer[i] << "\n";
    }
    return 0;
}
