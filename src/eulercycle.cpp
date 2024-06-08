#include "eulercycle.h"
#include "graph.h"
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

bool isEuler() {
    int oddCnt = 0;
    int n = Graph::getN();
    bool connected = false;
    vector<bool> visited(n, false);
    stack<int> stk;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (Graph::getAdj()[i][j] ==1) {
                stk.push(i);
                connected = true;
                break;
            }
        }
        if (connected) break;
    }

    if (!connected) return false;

    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();
        if (!visited[u]) {
            visited[u] = true;
            for (int v = 0; v < n; ++v) {
                if (Graph::getAdj()[u][v] > 0 && !visited[v]) {
                    stk.push(v);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && Graph::getDeg(i) > 0) {
            return false;
        }
    }

    for (int i = 0; i < n; ++i) {
        int deg = 0;
        for (int j = 0; j < n; ++j) {
            deg += Graph::getAdj()[i][j];
        }
        if (deg % 2 != 0) {
            oddCnt++;
        }
    }

    return (oddCnt == 0 || oddCnt == 2);
}

void findEuler() {
    if (!isEuler()) {
        cout << "No Euler cycle." << endl;
        return;
    }

    int n = Graph::getN();
    int start = 0;
    for (int i = 0; i < n; ++i) {
        int deg = 0;
        for (int j = 0; j < n; ++j) {
            deg += Graph::getAdj()[i][j];
        }
        if (deg % 2 != 0) {
            start = i;
            break;
        }
    }

    vector<int> circ;
    stack<int> stk;
    stk.push(start);
    vector<vector<int>> adj = Graph::getAdj();

    while (!stk.empty()) {
        int u = stk.top();
        bool found = false;
        for (int v = 0; v < n; ++v) {
            if (adj[u][v] > 0) {
                stk.push(v);
                adj[u][v]--;
                adj[v][u]--;
                found = true;
                break;
            }
        }
        if (!found) {
            circ.push_back(u);
            stk.pop();
        }
    }

    cout << "Euler cycle: ";
    for (int i = circ.size() - 1; i >= 0; --i) {
        cout << circ[i]+1;
        if(i > 0) cout << " -> ";
    }
    cout << endl;
}
