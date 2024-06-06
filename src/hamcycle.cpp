#include "hamcycle.h"
#include "graph.h"
#include <vector>
#include <iostream>

using namespace std;

bool hamUtil(int v, vector<int>& path, vector<bool>& vis, int pos) {
    int n = Graph::getN();
    if (pos == n) {
        if (Graph::getAdj()[path[pos - 1]][path[0]] == 1) {
            return true;
        }
        return false;
    }

    for (int i = 0; i < n; ++i) {
        if (Graph::getAdj()[v][i] == 1 && !vis[i]) {
            vis[i] = true;
            path[pos] = i;

            if (hamUtil(i, path, vis, pos + 1)) {
                return true;
            }

            vis[i] = false;
        }
    }

    return false;
}

bool isHam() {
    int n = Graph::getN();
    vector<int> path(n);
    vector<bool> vis(n, false);

    path[0] = 0;
    vis[0] = true;

    if (!hamUtil(0, path, vis, 1)) {
        return false;
    }

    return true;
}

void findHam() {
    if (!isHam()) {
        cout << "No Hamilton cycle." << endl;
    } else {
        cout << "Hamilton cycle exists." << endl;
        int n = Graph::getN();
        vector<int> path(n);
        vector<bool> vis(n, false);

        path[0] = 0;
        vis[0] = true;

        hamUtil(0, path, vis, 1);

        for (int i = 0; i < n; ++i) {
            cout << path[i]+1;
            if (i < n - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}
