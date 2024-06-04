#include "hamcycle.h"
#include "graph.h"
#include <vector>
#include <iostream>

using namespace std;

bool hamUtil(int v, vector<int>& path, vector<bool>& vis, int& cnt) {
    if (cnt == Graph::getN()) {
        if (Graph::getAdj()[v][path[0]] == 1) {
            return true;
        }
        return false;
    }

    vis[v] = true;
    path[cnt++] = v;

    for (int i = 0; i < Graph::getN(); ++i) {
        if (Graph::getAdj()[v][i] == 1 && !vis[i]) {
            if (hamUtil(i, path, vis, cnt)) {
                return true;
            }
        }
    }

    vis[v] = false;
    cnt--;
    return false;
}

bool isHam() {
    vector<int> path(Graph::getN());
    vector<bool> vis(Graph::getN(), false);
    int cnt = 0;

    if (!hamUtil(0, path, vis, cnt)) {
        return false;
    }

    for (int i = 0; i < Graph::getN(); ++i) {
        if (!vis[i]) {
            return false;
        }
    }

    return true;
}

void findHam() {
    if (!isHam()) {
        cout << "No Hamilton cycle." << endl;
        return;
    }

    cout << "Hamilton cycle exists." << endl;
}
