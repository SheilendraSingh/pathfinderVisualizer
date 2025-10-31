#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <set>
#include <windows.h>

using namespace std;
using namespace std::chrono_literals;

struct Cell
{
    int r, c;
    bool wall = false;
    bool visited = false;
    bool inPath = false;
};

int R = 15, C = 31;

vector<vector<Cell>> grid;

pair<int, int> startPos = {1, 1}, goalPos = {13, 29};

void intGrid()
{
    grid.assign(R, vector<Cell>(C));
    for (int i = 0; i < R; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            grid[i][j].r = i;
            grid[i][j].c = j;
            grid[i][j].wall = false;
            grid[i][j].visited = false;
            grid[i][j].inPath = false;
        }
    }

    for (int i = 0; i < R; i++)
    {
        grid[i][0].wall = grid[i][C - 1].wall = true;
    }

    for (int j = 0; j < C; j++)
    {
        grid[j][0].wall = grid[j][R - 1].wall = true;
    }

    for (int j = 5; j < 25; j++)
    {
        grid[5][j].wall = true;
    }

    for (int i = 6; i < 12; i++)
    {
        grid[i][12].wall = true;
    }
}

void printGrid()
{
    system("cls||clear");
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (startPos.first == i && startPos.second == j)
                cout << "S";
            else if (goalPos.first == i && goalPos.second == j)
                cout << "G";
            else if (grid[i][j].inPath)
                cout << "@";
            else if (grid[i][j].wall)
                cout << "#";
            else if (grid[i][j].visited)
                cout << ".";
            else
                cout << " ";
        }
        cout << "\n";
    }
    cout.flush();
}

vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool bfs_visualize(int delay_ms = 50)
{
    for (auto &row : grid)
        for (auto &cell : row)
        {
            cell.visited = false;
            cell.inPath = false;
        }
    queue<pair<int, int>> q;
    vector<vector<pair<int, int>>> parent(R, vector<pair<int, int>>(C, {-1, -1}));
    q.push(startPos);
    grid[startPos.first][startPos.second].visited = true;
    bool found = false;

    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        if (cur == goalPos)
        {
            found = true;
            break;
        }
        for (auto d : dirs)
        {
            int nr = cur.first + d.first, nc = cur.second + d.second;
            if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                continue;
            if (grid[nr][nc].wall || grid[nr][nc].visited)
                continue;
            grid[nr][nc].visited = true;
            parent[nr][nc] = cur;
            q.push({nr, nc});
        }
        printGrid();
        Sleep(delay_ms);
    }

    if (found)
    {
        auto cur = goalPos;
        while (cur != startPos)
        {
            grid[cur.first][cur.second].inPath = true;
            cur = parent[cur.first][cur.second];
            if (cur.first == -1)
                break;
            printGrid();
            Sleep(delay_ms);
        }
        return true;
    }
    return false;
}

int main()
{
    intGrid();
    printGrid();
    cout << "\nPress Enter to run BFS visualization...";
    cin.get();
    bool ok = bfs_visualize(40);
    if (ok)
        cout << "\nPath found! Press Enter to exit.\n";
    else
        cout << "\nNo path. Press Enter to exit.\n";
    cin.get();

    return 0;
}