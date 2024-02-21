#include <iostream>
#include <vector>
#include "queue"

struct Cord {
    int x,y,z;
};

std::vector<std::vector<std::vector<int>>> bfs(Cord start, std::vector<std::vector<std::vector<int>>>& dist, std::vector<std::vector<std::vector<bool>>>& v, Cord end) {

    dist[start.x][start.y][start.z] = 0;
    std::queue<Cord> q;
    q.push(start);

    while (!q.empty()) {
        Cord i = q.front();
        if (i.x == end.x && i.y == end.y && i.z == end.z) {
            break;
        }
        q.pop();
        if ((i.x + 1) < 105 && dist[i.x + 1][i.y][i.z] > dist[i.x][i.y][i.z] + 1 && !v[i.x + 1][i.y][i.z]) {
            Cord NewCord = i;
            ++NewCord.x;
            dist[i.x + 1][i.y][i.z] = dist[i.x][i.y][i.z] + 1;
            q.push(NewCord);
        }
        if ((i.x - 1) >= 0 && dist[i.x - 1][i.y][i.z] > dist[i.x][i.y][i.z] + 1 && !v[i.x - 1][i.y][i.z]) {
            Cord NewCord = i;
            --NewCord.x;
            dist[i.x - 1][i.y][i.z] = dist[i.x][i.y][i.z] + 1;
            q.push(NewCord);
        }
        if ((i.y + 1) < 105 && dist[i.x][i.y + 1][i.z] > dist[i.x][i.y][i.z] + 1 && !v[i.x][i.y + 1][i.z]) {
            Cord NewCord = i;
            ++NewCord.y;
            dist[i.x][i.y + 1][i.z] = dist[i.x][i.y][i.z] + 1;
            q.push(NewCord);
        }
        if ((i.y - 1) >= 0 && dist[i.x][i.y - 1][i.z] > dist[i.x][i.y][i.z] + 1 && !v[i.x][i.y - 1][i.z]) {
            Cord NewCord = i;
            --NewCord.y;
            dist[i.x][i.y - 1][i.z] = dist[i.x][i.y][i.z] + 1;
            q.push(NewCord);
        }
        if ((i.z + 1) < 105 && dist[i.x][i.y][i.z + 1] > dist[i.x][i.y][i.z] + 1 && !v[i.x][i.y][i.z + 1]) {
            Cord NewCord = i;
            ++NewCord.z;
            dist[i.x][i.y][i.z + 1] = dist[i.x][i.y][i.z] + 1;
            q.push(NewCord);
        }
        if ((i.z  - 1) >= 0 && dist[i.x][i.y][i.z - 1] > dist[i.x][i.y][i.z] + 1 && !v[i.x][i.y][i.z - 1]) {
            Cord NewCord = i;
            --NewCord.z;
            dist[i.x][i.y][i.z - 1] = dist[i.x][i.y][i.z] + 1;
            q.push(NewCord);
        }
    }

    return dist;

}
int main() {

    int E;
    int K;
    std::cin >> K >> E;

    Cord start{};
    std::cin >> start.x >> start.y >> start.z;

    Cord end{};
    std::cin >> end.x >> end.y >> end.z;

    if (start.x == end.x && start.y == end.y && start.z == end.z) {
        std::cout << 0;
        return 0;
    }

    std::vector<std::vector<std::vector<bool>>> visited(105, std::vector<std::vector<bool>>(105, std::vector<bool>(105,false)));
    std::vector<std::vector<std::vector<int>>> dist(105, std::vector<std::vector<int>>(105, std::vector<int>(105,INT_MAX)));

    int x,y,z,h;
    for (int i = 0; i < K; i++) {
        std::cin >> x >> y >> z >> h;
        for (int j = 0; j < h; j++) {
            visited[x][y][z + j] = true;
        }
    }

    dist = bfs(start, dist, visited, end);

    if (dist[end.x][end.y][end.z] > E) {
        std::cout << -1;
    } else {
        std::cout << dist[end.x][end.y][end.z];
    }

    return 0;
}
