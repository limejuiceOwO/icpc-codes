//>=最长路求最小解 <=最短路求最大解
//dist[v]<=dist[u]+w := u到v有长为w的边
//=可转化为>=加<=
#define CLR(X) memset(X,0,sizeof(X))
#define INF(X) memset(X,0x7f,sizeof(X))
typedef pair<int,int> PII;
vector<PII> graph[N];
int dist[N];

bool solve(int n)
{
    queue<int> que;
    static bool inQueue[N];
    static int count[N];
    CLR(inQueue);
    CLR(count);
    INF(dist);
    que.push(0); //如果没有明显的起始点可设置一超级源点
    dist[0] = 0;
    while(!que.empty()) {
        int u = que.front(); que.pop();
        inQueue[u] = false;
        if(++count[u] > n) {
            return false;
        }
        for(int j = 0;j < graph[u].size();++j) {
            int v = graph[u][j].first,w = graph[u][j].second;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if(!inQueue[v]) {
                    que.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    return true;
}
