#include "hamcycle.h"
#include <vector>
#include <iostream>

using namespace std;

bool hamUtil(int v, Graph& g, vector<int>& path, vector<bool>& vis, int& cnt) {
    if (cnt == g.getN()) {
        if (g.getAdj()[v][path[0]] == 1) {
            return true;
        }
        return false;
    }

    vis[v] = true;
    path[cnt++] = v;

    for (int i = 0; i < g.getN(); ++i) {
        if (g.getAdj()[v][i] == 1 && !vis[i]) {
            if (hamUtil(i, g, path, vis, cnt)) {
                return true;
            }
        }
    }

    vis[v] = false;
    cnt--;
    return false;
}

bool isHam(Graph& g) {
    vector<int> path(g.getN());
    vector<bool> vis(g.getN(), false);
    int cnt = 0;

    if (!hamUtil(0, g, path, vis, cnt)) {
        return false;
    }

    for (int i = 0; i < g.getN(); ++i) {
        if (!vis[i]) {
            return false;
        }
    }

    return true;
}

void findHam(Graph& g) {
    if (!isHam(g)) {
        cout << "No Hamilton cycle." << endl;
        return;
    }

    cout << "Hamilton cycle exists." << endl;
}
