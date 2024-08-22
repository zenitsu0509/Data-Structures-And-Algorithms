#include <bits/stdc++.h>
using namespace std;
void loop(vector<int> l)
{
    for (auto i : l)
        cout << i << " ";
    cout << endl;
}
// BFS Traversal
vector<int> bfsOfGraph(int V, vector<int> adj[])
{
    vector<int> vis(V, 0);
    vector<int> bfs;
    queue<int> q;

    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
        {
            vis[i] = 1;
            q.push(i);

            while (!q.empty())
            {
                int node = q.front();
                q.pop();
                bfs.push_back(node);

                for (int it : adj[node])
                {
                    if (!vis[it])
                    {
                        vis[it] = 1;
                        q.push(it);
                    }
                }
            }
        }
    }
    return bfs;
}
void dfs(int node, vector<int> &vis, vector<int> adj[], vector<int> &result)
{
    vis[node] = 1;
    result.push_back(node);

    for (int it : adj[node])
    {
        if (!vis[it])
        {
            dfs(it, vis, adj, result);
        }
    }
}

vector<int> dfsOfGraph(int V, vector<int> adj[])
{
    vector<int> vis(V, 0);
    vector<int> result;

    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
        {
            dfs(i, vis, adj, result);
        }
    }
    return result;
}
// Cycle Detection in Undirected Graph using BFS
bool bfsCycleDetection(int src, vector<int> adj[], vector<int> &vis)
{
    queue<pair<int, int>> q;
    vis[src] = 1;
    q.push({src, -1});

    while (!q.empty())
    {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (int i : adj[node])
        {
            if (!vis[i])
            {
                vis[i] = 1;
                q.push({i, node});
            }
            else if (i != parent)
            {
                return true;
            }
        }
    }
    return false;
}

bool isCycleUndirectedBFS(int V, vector<int> adj[])
{
    vector<int> vis(V, 0);

    for (int i = 0; i < V; i++)
    {
        if (!vis[i] && bfsCycleDetection(i, adj, vis))
        {
            return true;
        }
    }
    return false;
}
// Cycle Detection in Undirected Graph using DFS
bool dfsCycleDetection(int node, int parent, vector<int> adj[], vector<int> &vis)
{
    vis[node] = 1;

    for (int i : adj[node])
    {
        if (!vis[i])
        {
            if (dfsCycleDetection(i, node, adj, vis))
            {
                return true;
            }
        }
        else if (i != parent)
        {
            return true;
        }
    }
    return false;
}

bool isCycleUndirectedDFS(int V, vector<int> adj[])
{
    vector<int> vis(V, 0);

    for (int i = 0; i < V; i++)
    {
        if (!vis[i] && dfsCycleDetection(i, -1, adj, vis))
        {
            return true;
        }
    }
    return false;
}
// Helper function to perform DFS and detect cycles
bool dfsCycleDetectionDirected(int node, vector<int> &vis, vector<int> &pathVis, vector<int> adj[])
{
    vis[node] = 1;
    pathVis[node] = 1;

    // Traverse adjacent nodes
    for (int neighbor : adj[node])
    {
        // If the adjacent node has not been visited, recursively call the function
        if (!vis[neighbor])
        {
            if (dfsCycleDetectionDirected(neighbor, vis, pathVis, adj))
            {
                return true;
            }
        }
        // If the adjacent node is visited and also in the current path, then there is a cycle
        else if (pathVis[neighbor])
        {
            return true;
        }
    }

    pathVis[node] = 0; // Unmark the current node in the path
    return false;
}

// Function to check if there is a cycle in a directed graph using DFS
bool isCycleDirectedDFS(int V, vector<int> adj[])
{
    vector<int> vis(V, 0);
    vector<int> pathVis(V, 0);

    for (int i = 0; i < V; i++)
    {
        if (!vis[i] && dfsCycleDetectionDirected(i, vis, pathVis, adj))
        {
            return true;
        }
    }
    return false;
}
// Topological Sort using Kahn's Algorithm (BFS)
vector<int> topoSortKahn(int V, vector<int> adj[])
{
    vector<int> indegree(V, 0);
    vector<int> topo;
    queue<int> q;

    // Calculate in-degrees of all vertices
    for (int i = 0; i < V; i++)
    {
        for (int it : adj[i])
        {
            indegree[it]++;
        }
    }

    // Push all vertices with in-degree 0 into the queue
    for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    // Perform BFS and generate topological order
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        for (int it : adj[node])
        {
            indegree[it]--;
            if (indegree[it] == 0)
            {
                q.push(it);
            }
        }
    }

    // Check if there was a cycle (not all vertices are included)
    if (topo.size() != V)
    {
        cout << "Cycle detected in the graph, topological sort not possible." << endl;
        return {};
    }

    return topo;
}
void topoSortDFS(int node, vector<int> &vis, vector<pair<int, int>> adj[], stack<int> &st)
{
    vis[node] = 1;

    // Traverse adjacent nodes
    for (auto it : adj[node])
    {
        int neighbor = it.first;
        if (!vis[neighbor])
        {
            topoSortDFS(neighbor, vis, adj, st);
        }
    }

    // Push the current node onto the stack after visiting all its neighbors
    st.push(node);
}
vector<int> topoSort(int V, vector<int> edges[])
{
    vector<int> vis(V, 0);
    stack<int> st;
    vector<int> topo;
    vector<pair<int, int>> adj1[V];

    // Convert edge list to adjacency list with weights
    for (int i = 0; i < V; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];
        adj1[u].push_back({v, wt});
    }

    // Perform DFS-based topological sort
    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
        {
            topoSortDFS(i, vis, adj1, st);
        }
    }

    // Extract topological order from the stack
    while (!st.empty())
    {
        topo.push_back(st.top());
        st.pop();
    }

    return topo;
}
// Function to find the shortest paths in a DAG
vector<int> shortestPathDAG(int N, int M, vector<int> edges[])
{
    vector<pair<int, int>> adj[N];

    // Convert edge list to adjacency list with weights
    for (int i = 0; i < M; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];
        adj[u].push_back({v, wt});
    }

    stack<int> st;
    vector<int> vis(N, 0);
    vector<int> distance(N, INT_MAX);

    // Generate topological sort
    for (int i = 0; i < N; i++)
    {
        if (!vis[i])
        {
            topoSortDFS(i, vis, adj, st);
        }
    }

    // Calculate shortest paths
    distance[0] = 0; // Assuming the source node is 0
    while (!st.empty())
    {
        int node = st.top();
        st.pop();

        if (distance[node] != INT_MAX)
        {
            for (auto it : adj[node])
            {
                int v = it.first;
                int wt = it.second;
                if (distance[node] + wt < distance[v])
                {
                    distance[v] = distance[node] + wt;
                }
            }
        }
    }

    // Convert unreachable nodes' distances to -1
    for (int i = 0; i < N; i++)
    {
        if (distance[i] == INT_MAX)
        {
            distance[i] = -1;
        }
    }

    return distance;
}

// Shortest Path using BFS (for unweighted graphs)
vector<int> shortestPathBFS(vector<vector<int>> &edges, int N, int M, int src)
{
    vector<int> adj[N];
    for (auto it : edges)
    {
        adj[it[0]].push_back(it[1]);
        adj[it[1]].push_back(it[0]);
    }

    vector<int> distance(N, 1e9);
    distance[src] = 0;
    queue<int> q;
    q.push(src);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (int it : adj[node])
        {
            if (distance[node] + 1 < distance[it])
            {
                distance[it] = 1 + distance[node];
                q.push(it);
            }
        }
    }

    for (int i = 0; i < N; i++)
        if (distance[i] == 1e9)
            distance[i] = -1;

    return distance;
}
// Dijkstra's Algorithm using priority_queue
vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dis(V, 1e9);
    pq.push({0, S});
    dis[S] = 0;

    while (!pq.empty())
    {
        int weight = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for (auto it : adj[node])
        {
            int edge = it[0];
            int edgeW = it[1];
            if (edgeW + weight < dis[edge])
            {
                dis[edge] = weight + edgeW;
                pq.push({dis[edge], edge});
            }
        }
    }
    return dis;
}
// Dijkstra's Algorithm using set
vector<int> dijkstraSet(int V, vector<vector<int>> adj[], int S)
{
    set<pair<int, int>> st;
    vector<int> dis(V, 1e9);
    st.insert({0, S});
    dis[S] = 0;

    while (!st.empty())
    {
        auto it = *(st.begin());
        int node = it.second;
        int weight = it.first;
        st.erase(it);

        for (auto it : adj[node])
        {
            int edge = it[0];
            int edgeW = it[1];
            if (edgeW + weight < dis[edge])
            {
                if (dis[edge] != 1e9)
                {
                    st.erase({dis[edge], edge});
                }
                dis[edge] = weight + edgeW;
                st.insert({dis[edge], edge});
            }
        }
    }
    return dis;
}
vector<int> bellman_ford(int V, vector<vector<int>> &edges, int S)
{
    vector<int> dist(V, 1e8);
    dist[S] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        for (const auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            if (dist[u] != 1e8 && dist[u] + wt < dist[v])
            {
                dist[v] = dist[u] + wt;
            }
        }
    }

    for (const auto &edge : edges)
    {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];
        if (dist[u] != 1e8 && dist[u] + wt < dist[v])
        {
            return {-1};
        }
    }

    return dist;
}
void floyd_warshall(vector<vector<int>> &matrix)
{

    int n = matrix.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == -1)
                matrix[i][j] = 1e9;
            if (j == i)
                matrix[i][j] = 0;
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1e9)
                matrix[i][j] = -1;
            // if(j == i) matrix[i][j] = 0;
        }
    }
}
// prim algorith for finding minimum spaning tree
int spanningTree(int V, vector<vector<int>> adj[])
{
    // code here
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    vector<int> vis(V, 0);
    int sum = 0;
    while (!pq.empty())
    {
        auto it = pq.top();
        pq.pop();
        int wt = it.first;
        int node = it.second;
        if (vis[node])
            continue;
        vis[node] = 1;
        sum += wt;
        for (auto &i : adj[node])
        {
            int nd = i[0];
            int wt = i[1];
            if (!vis[nd])
            {
                pq.push({wt, nd});
            }
        }
    }
    return sum;
}
int main()
{
    int V = 5, V2 = 4, V4 = 6;
    vector<int> adj[V];
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(3);
    adj[1].push_back(4);
    adj[2].push_back(3);
    vector<int> adj2[V2];
    adj2[0].push_back(1);
    adj2[1].push_back(2);
    adj2[2].push_back(3);
    adj2[3].push_back(1);
    int V3 = 6;
    vector<int> adj3[V3];
    adj3[5].push_back(0);
    adj3[5].push_back(2);
    adj3[4].push_back(0);
    adj3[4].push_back(1);
    adj3[2].push_back(3);
    adj3[3].push_back(1);
    vector<int> edges[] = {
        {5, 0, 2},
        {5, 2, 1},
        {4, 0, 1},
        {4, 1, 3},
        {2, 3, 2},
        {3, 1, 1}};
    int N = 6;
    int M = 7;
    vector<int> edges2[] = {
        {0, 1, 5},
        {0, 2, 3},
        {1, 3, 6},
        {1, 2, 2},
        {2, 4, 4},
        {2, 5, 2},
        {4, 3, 1},
        {4, 5, 1}};
    int N1 = 6;
    int M1 = 7;
    int src1 = 0;
    vector<vector<int>> edges3 = {
        {0, 1},
        {0, 3},
        {1, 2},
        {3, 4},
        {3, 5},
        {4, 5},
        {2, 4}};
    int V7 = 5;
    int S = 0;
    vector<vector<int>> adj0[V7];
    adj0[0].push_back({1, 2});
    adj0[0].push_back({4, 1});
    adj0[1].push_back({2, 3});
    adj0[2].push_back({3, 6});
    adj0[4].push_back({2, 2});
    adj0[4].push_back({5, 4});
    adj0[5].push_back({3, 1});
    vector<int> result6 = dijkstra(V7, adj0, S);
    vector<int> result = bfsOfGraph(V, adj);

    cout << "bfs travelsal:";
    loop(result);
    vector<int> r2 = dfsOfGraph(V, adj);
    cout << "dfs of graph:";
    loop(r2);
    if (isCycleUndirectedBFS(V, adj))
        cout << "cycle detected using bfs" << endl;
    else
        cout << "cycle not detected using bfs" << endl;
    if (isCycleUndirectedDFS(V, adj))
        cout << "cycle detected using dfs" << endl;
    else
        cout << "cycle not detected using dfs" << endl;
    if (isCycleDirectedDFS(V2, adj2))
    {
        cout << "Cycle detected in the graph." << endl;
    }
    else
    {
        cout << "No cycle detected in the graph." << endl;
    }
    vector<int> tp = topoSortKahn(V3, adj3);
    cout << "topo sort(using bfs):";
    loop(tp);
    tp.clear();
    vector<int> tp1 = topoSort(V4, edges);
    cout << "topo sort using dfs:";
    loop(tp1);
    tp1.clear();
    vector<int> result4 = shortestPathDAG(N, M, edges2);

    // Print the shortest distances
    cout << "Shortest distances from node 0:";
    loop(result4);
    result4.clear();
    vector<int> result5 = shortestPathBFS(edges3, N1, M1, src1);
    cout << "Shortest distances from node " << src1 << ":";
    for (int i = 0; i < N; i++)
    {
        cout << "Node " << i << ": " << result5[i] << endl;
    }
    result5.clear();
    cout << "Shortest distances from node " << S << ":" << endl;
    for (int i = 0; i < V; i++)
    {
        if (result6[i] == 1e9)
        {
            cout << "Node " << i << ": Unreachable" << endl;
        }
        else
        {
            cout << "Node " << i << ": " << result6[i] << endl;
        }
    }
    result6.clear();
    vector<int> r1 = dijkstraSet(V7, adj0, S);
    cout << "Shortest distances from node " << S << ":" << endl;
    for (int i = 0; i < V; i++)
    {
        if (r1[i] == 1e9)
        {
            cout << "Node " << i << ": Unreachable" << endl;
        }
        else
        {
            cout << "Node " << i << ": " << r1[i] << endl;
        }
    }
    r1.clear();
    int V9 = 5; // Number of vertices
    vector<vector<int>> edges6 = {
        {0, 1, -1}, // Edge from vertex 0 to vertex 1 with weight -1
        {0, 2, 4},  // Edge from vertex 0 to vertex 2 with weight 4
        {1, 2, 3},  // Edge from vertex 1 to vertex 2 with weight 3
        {1, 3, 2},  // Edge from vertex 1 to vertex 3 with weight 2
        {1, 4, 2},  // Edge from vertex 1 to vertex 4 with weight 2
        {3, 2, 5},  // Edge from vertex 3 to vertex 2 with weight 5
        {3, 1, 1},  // Edge from vertex 3 to vertex 1 with weight 1
        {4, 3, -3}  // Edge from vertex 4 to vertex 3 with weight -3
    };

    int S6 = 0; // Source vertex

    // Call Bellman-Ford algorithm
    vector<int> result9 = bellman_ford(V9, edges6, S6);

    // Output the results
    if (result.size() == 1 && result[0] == -1)
    {
        cout << "Graph contains a negative weight cycle" << endl;
    }
    else
    {
        cout << "Shortest distances from vertex " << S << ":" << endl;
        for (int i = 0; i < V9; i++)
        {
            cout << "Vertex " << i << ": ";
            if (result[i] == 1e8)
            {
                cout << "Infinity" << endl;
            }
            else
            {
                cout << result9[i] << endl;
            }
        }
    }
    result9.clear();
    // Test Case 1: Simple graph with positive weights
    vector<vector<int>> matrix1 = {
        {0, 3, -1, 7},
        {-1, 0, 2, -1},
        {5, -1, 0, 1},
        {-1, -1, -1, 0}};

    // Call the function
    floyd_warshall(matrix1);

    // Output the result
    cout << "Test Case 1 - Shortest distances between every pair of vertices:" << endl;
    for (int i = 0; i < matrix1.size(); i++)
    {
        for (int j = 0; j < matrix1[i].size(); j++)
        {
            if (matrix1[i][j] == -1)
            {
                cout << "INF" << " ";
            }
            else
            {
                cout << matrix1[i][j] << " ";
            }
        }
        cout << endl;
    }
    matrix1.clear();
    // Test Case 2: Graph with a negative weight edge
    vector<vector<int>> matrix2 = {
        {0, 1, 4},
        {-1, 0, 2},
        {-1, -1, 0}};

    // Call the function
    floyd_warshall(matrix2);

    // Output the result
    cout << "Test Case 2 - Shortest distances between every pair of vertices:" << endl;
    for (int i = 0; i < matrix2.size(); i++)
    {
        for (int j = 0; j < matrix2[i].size(); j++)
        {
            if (matrix2[i][j] == -1)
            {
                cout << "INF" << " ";
            }
            else
            {
                cout << matrix2[i][j] << " ";
            }
        }
        cout << endl;
    }
    matrix2.clear();
    // Test Case 3: Graph with no edges
    vector<vector<int>> matrix3 = {
        {0, -1, -1},
        {-1, 0, -1},
        {-1, -1, 0}};

    // Call the function
    floyd_warshall(matrix3);

    // Output the result
    cout << "Test Case 3 - Shortest distances between every pair of vertices:" << endl;
    for (int i = 0; i < matrix3.size(); i++)
    {
        for (int j = 0; j < matrix3[i].size(); j++)
        {
            if (matrix3[i][j] == -1)
            {
                cout << "INF" << " ";
            }
            else
            {
                cout << matrix3[i][j] << " ";
            }
        }
        cout << endl;
    }
    matrix3.clear();
    return 0;
}