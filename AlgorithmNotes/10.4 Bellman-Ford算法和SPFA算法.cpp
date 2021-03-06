/**
* Bellman-Ford算法：求解有负权边的最短路径问题
**/

//伪代码
//执行n-1轮操作，其中n为顶点数
{
    for (int i = 0; i < length; i++) {
        //每轮操作都遍历所有边
        for (each edge u->v) {
            //以u为中介点可以使d[v]更小
            if (d[u] + length[u->v] < d[v])
                d[v] = d[u] + length[u->v]; //松弛操作
        }
    }
//对每条边进行判断
    for (each edge u->v) {
        //如果仍可以被松弛
        if (d[u] + length[u->v] < d[v])
            return false; //说明图中有源点可达的负环
    }
    return true; //数组d的所有值都已经达到最优
}

//邻接表版
struct Node {
    int v, dis; //v为邻接边的目标顶点，dis为邻接边的边权
};
vector<Node> Adj[MAXV]; //图G的邻接表
int n; //顶点数
int d[MAXV]; //起点到达各点的最短路径长度
//s为源点
bool Bellman(int s) {
    fill(d, d + MAXV, INF); //fill函数将整个d数组赋为INF（慎用memset）
    d[s] = 0; //起点s到达自身的距离为0
    //以下为求解数组d的部分
    //执行n-1轮操作，n为顶点数
    for (int i = 0; i < n - 1; i++) {
        //每轮操作都遍历所有边
        for (int u = 0; u < n; u++) {
            for (int j = 0; j < Adj[u].size(); j++) {
                int v = Adj[u][j].v; //邻接边的顶点
                int dis = Adj[u][j].dis; //邻接边的边权
                //以u为中介点可以使d[v]更小
                if (d[u] + dis < d[v])
                    d[v] = d[u] + dis; //松弛操作
            }
        }
    }
    //以下为判断负环的部分
    //对每条边进行判断
    for (int u = 0; u < n; u++) {
        for (int j = 0; j < Adj[u].size(); j++) {
            int v = Adj[u][j].v; //邻接边的顶点
            int dis = Adj[u][j].dis; //邻接边的边权
            //如果仍可以被松弛
            if (d[u] + dis < d[v])
                return false; //说明图中有从源点可达的负环
        }
    }
    return true; //数组d的所有值都已经达到最优
}

//注意统计最短路径条数的做法，需要设置记录前驱的数组

//【PAT A1003】可用Bellman-Ford算法实现，见晴神宝典P394



//注意到，Bellman-Ford算法的每轮操作都需要都需要操作所有边，影响算法性能
//只有当某个顶点u的d[u]值改变时，从它出发的边的邻接点v的d[v]值才有可能被改变
//进行优化，优化后的算法为SPFA算法

//伪代码
{
    queue<int> Q;
    源点s入队;
    while (队列非空) {
        for (u的所有邻接边u->v) {
            if (d[u] + dis < d[v]) {
                d[v] = d[u] + dis;
                if (v不在当前队列) {
                    v入队;
                    if (v入队次数大于n - 1) {
                        说明有可达负环，return;
                    }
                }
            }
        }
    }
}

//邻接表版
vector<Node> Adj[MAXV]; //图G的邻接表
int n, d[MAXV], num[MAXV]; //num数组记录顶点的入队次数
bool inq[MAXV]; //顶点是否在队列中
bool SPFA(int s) {
    //初始化部分
    memset(inq, false, sizeof(inq));
    memset(num, 0, sizeof(num));
    fill(d, d + MAXV, INF);
    //源点入队部分
    queue<int> Q;
    Q.push(s); //源点入队
    inq[s] = true; //源点已入队
    num[s]++; //源点入队次数加1
    d[s] = 0; //源点的d值为0
    //主体部分
    while (!Q.empty()) {
        int u = Q.front(); //队首顶点编号为u
        Q.pop(); //出队
        inq[u] = false; //设置u为不在队列中
        //遍历u的所有邻接边v
        for (int j = 0; j < Adj[u].size(); j++) {
            int v = Adj[u][j].v;
            int dis = Adj[u][j].dis;
            //松弛操作
            if (d[u] + dis < d[v]) {
                d[v] = d[u] + dis;
                //如果v不在队列中
                if (!inq[v]) {
                    Q.push(v); //v入队
                    inq[v] = true; //设置v为在队列中
                    num[v]++; //v的入队次数加1
                    if (num[v] >= n)
                        return false; //有可达负环
                }
            }
        }
    }
    return true; //无可达负环
}
