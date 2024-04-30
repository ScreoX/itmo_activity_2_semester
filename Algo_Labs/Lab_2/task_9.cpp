#include "iostream"
#include "vector"
#include "queue"

using namespace std;

struct Point {
    int x, y;
};

vector<Point> steps = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int INF = 100000;

void dfs(const vector<vector<char>>& mapa, vector<vector<int>>& visited, int x, int y, int component_id, int N, int M) {
    visited[x][y] = component_id;
    int nx, ny;

    for (auto &[stepx, stepy] : steps) {
        nx = x + stepx;
        ny = y + stepy;
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && mapa[nx][ny] == 'X' && visited[nx][ny] == -1) {
            dfs(mapa, visited, nx, ny, component_id, N, M);
        }
    }
}

int bfs(const vector<vector<char>>& mapa, Point start, Point end, int N, int M) {
    deque<Point> q;
    vector<vector<int>> distance(N, vector<int>(M, INF));

    q.push_back(start);
    distance[start.x][start.y] = 0;

    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();

        if (x == end.x && y == end.y) {
            return distance[x][y];
        }

        for (int d = 0; d < 4; d++){
            int tx = x + dx[d];
            int ty = y + dy[d];

            if (0 <= ty && ty < M && 0 <= tx && tx < N){
                if (mapa[tx][ty] == 'S' && distance[tx][ty] > distance[x][y] + 1){
                    q.push_back({tx, ty});
                    distance[tx][ty] = distance[x][y] + 1;
                }
                else if (mapa[tx][ty] != 'S' && mapa[tx][ty] != '.' && distance[tx][ty] > distance[x][y]){
                    q.push_front({tx, ty});
                    distance[tx][ty] = distance[x][y];
                }
            }
        }
    }
    return 0;
}

int tsp (vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));

    for (int start = 0; start < n; ++start) {
        dp[1 << start][start] = 0;
    }

    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int pos = 0; pos < n; ++pos) {
            if ((mask & (1 << pos)) != 0) {
                for (int next = 0; next < n; ++next) {
                    if ((mask & (1 << next)) == 0) {
                        dp[mask | (1 << next)][next] = min(dp[mask | (1 << next)][next], dp[mask][pos] + graph[pos][next]);
                    }
                }
            }
        }
    }

    int min_path = INT_MAX;
    for (int start = 0; start < n; ++start) {
        min_path = min(min_path, dp[(1 << n) - 1][start]);
    }

    return min_path;
}

int main() {

    int N, M;
    cin >> N >> M;

    vector<vector<char>> mapa(N, vector<char>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> mapa[i][j];
        }
    }

    vector<Point> xPoints;
    vector<vector<int>> visited_for_dfs(N, vector<int>(M, -1));
    vector<int> brights(19, -1);
    int component_id = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (mapa[i][j] == 'X' && visited_for_dfs[i][j] == -1) {
                if (brights[component_id] == -1){
                    brights[component_id] = 1;
                    xPoints.push_back({i, j});
                }
                dfs(mapa, visited_for_dfs, i, j, component_id++, N, M);
            }
        }
    }

    vector<vector<int>> matrix(component_id, vector<int>(component_id, 0));
    for (int q = 0; q < xPoints.size(); q++){
        for (int j = q + 1; j < xPoints.size(); j++){
            int res = bfs(mapa, xPoints[q], xPoints[j], N, M);
            matrix[q][j] = res;
            matrix[j][q] = res;
        }
    }

    if (component_id == 1){
        cout << 0;
        return 0;
    }
    int result = tsp(matrix);
    cout << result;

    return 0;
}
