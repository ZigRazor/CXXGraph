class Trajan {
public:
    vector<vector<int>> ans;
    stack<int> stk;
    vector<bool> onStack;
    vector<int> ids;
    vector<int> low;
    int id;

    void dfs(int now, vector<vector<int>> &adj, int prev){
        stk.push(now);
        onStack[now] = true;
        ids[now] = low[now] = id++;

        for(int to: adj[now]){
            if(ids[to] == -1){
                dfs(to, adj, now);
            }
            if(to != prev && onStack[to]){
                low[now] = min(low[now], low[to]);
            }
            // to is in another loop
            if(low[to] > ids[now]){
                ans.push_back({now, to});
            }
        }
        if(ids[now] == low[now]){
            for(int node = stk.top();; node = stk.top()){
                stk.pop();
                onStack[node] = false;
                low[node] = ids[now];
                if(node == now) break;
            }
        }
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        low.resize(n, 0);
        // unvisited
        ids.resize(n, -1);
        onStack.resize(n, false);
        id = 0;

        vector<vector<int>> adjacent(n);
        for(auto v: connections){
            adjacent[v[0]].push_back(v[1]);
            adjacent[v[1]].push_back(v[0]);
        }
        // Tarjan's algorithm
        for(int i = 0; i < n; i++) {
            if(ids[i] == -1){
                dfs(i, adjacent, -1);
            }
        }
        return ans;
    }
};

