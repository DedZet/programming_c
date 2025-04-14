#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point point;
    int dist;
} Node;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

bool canMove(int from, int to, int dir, char** maze, int M, int N) {

    int walls_from = 0;
    if (maze[from / N][from % N] >= '0' && maze[from / N][from % N] <= '9') {
        walls_from = maze[from / N][from % N] - '0';
    } else if (maze[from / N][from % N] >= 'A' && maze[from / N][from % N] <= 'F') {
        walls_from = maze[from / N][from % N] - 'A' + 10;
    }
    
    int walls_to = 0;
    if (maze[to / N][to % N] >= '0' && maze[to / N][to % N] <= '9') {
        walls_to = maze[to / N][to % N] - '0';
    } else if (maze[to / N][to % N] >= 'A' && maze[to / N][to % N] <= 'F') {
        walls_to = maze[to / N][to % N] - 'A' + 10;
    }
    

    if (dir == 0) { // вверх
        if ((walls_from & 1) || (walls_to & 4)) return false;
    } else if (dir == 1) { // вправо
        if ((walls_from & 2) || (walls_to & 8)) return false;
    } else if (dir == 2) { // вниз
        if ((walls_from & 4) || (walls_to & 1)) return false;
    } else if (dir == 3) { // влево
        if ((walls_from & 8) || (walls_to & 2)) return false;
    }
    
    return true;
}

void findShortestPath(char** maze, int M, int N) {
    bool** visited = (bool**)malloc(M * sizeof(bool*));
    int** parent = (int**)malloc(M * sizeof(int*));
    int i, j;
    for (i = 0; i < M; i++) {
        visited[i] = (bool*)calloc(N, sizeof(bool));
        parent[i] = (int*)malloc(N * sizeof(int));
        for (j = 0; j < N; j++) {
            parent[i][j] = -1;
        }
    }
    
    Node queue[M * N];
    int front = 0, rear = 0;
    
    queue[rear].point.x = 0;
    queue[rear].point.y = 0;
    queue[rear].dist = 0;
    rear++;
    visited[0][0] = true;
    
    bool found = false;
    Point end = {M - 1, N - 1};
    int distance = 0;
    
    while (front < rear) {
        Node current = queue[front++];
        Point pt = current.point;
        
        if (pt.x == end.x && pt.y == end.y) {
            found = true;
            distance = current.dist;
            break;
        }
        int i;
        for (i = 0; i < 4; i++) {
            int newX = pt.x + dx[i];
            int newY = pt.y + dy[i];
            
            if (newX >= 0 && newX < M && newY >= 0 && newY < N && !visited[newX][newY]) {
                int from = pt.x * N + pt.y;
                int to = newX * N + newY;
                
                if (canMove(from, to, i, maze, M, N)) {
                    visited[newX][newY] = true;
                    parent[newX][newY] = pt.x * N + pt.y;
                    
                    queue[rear].point.x = newX;
                    queue[rear].point.y = newY;
                    queue[rear].dist = current.dist + 1;
                    rear++;
                }
            }
        }
    }
    
    if (found) {
        printf("%d\n", distance);
        
        Point current = end;
        while (!(current.x == 0 && current.y == 0)) {
            int idx = current.x * N + current.y;
            int p = parent[current.x][current.y];
            if (p == -1) break;
            
            current.x = p / N;
            current.y = p % N;
            if (maze[current.x][current.y] != '0') {
                maze[current.x][current.y] = '*';
            }
        }
        maze[end.x][end.y] = '*';

        FILE* file = fopen("output.txt", "w");
        int i,j;
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                fprintf(file, "%c", maze[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    } else {
        printf("No path found\n");
    }
    

    for (i = 0; i < M; i++) {
        free(visited[i]);
        free(parent[i]);
    }
    free(visited);
    free(parent);
}

int main() {
    int M, N;
    scanf("%d %d", &M, &N);
    
    char** maze = (char**)malloc(M * sizeof(char*));
    int i;
    for (i = 0; i < M; i++) {
        maze[i] = (char*)malloc((N + 1) * sizeof(char));
        scanf("%s", maze[i]);
    }
    
    findShortestPath(maze, M, N);
    
    for (i = 0; i < M; i++) {
        free(maze[i]);
    }
    free(maze);
    
    return 0;
}
