#include "eulercycle.h"
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

bool isEuler(Graph& g) {
    int oddCnt = 0;
    for (int i = 0; i < g.getN(); ++i) {
        int deg = 0;
        for (int j = 0; j < g.getN(); ++j) {
            deg += g.getAdj()[i][j];
        }
        if (deg % 2 != 0) {
            oddCnt++;
        }
    }
    return (oddCnt == 0 || oddCnt == 2);
}

void findEuler(Graph& g) {
    if (!isEuler(g)) {
        cout << "No Euler cycle." << endl;
        return;
    }

    int start = 0;
    for (int i = 0; i < g.getN(); ++i) {
        int deg = 0;
        for (int j = 0; j < g.getN(); ++j) {
            deg += g.getAdj()[i][j];
        }
        if (deg % 2 != 0) {
            start = i;
            break;
        }
    }

    vector<int> circ;
    stack<int> stk;
    stk.push(start);

    while (!stk.empty()) {
        int u = stk.top();
        bool found = false;
        for (int v = 0; v < g.getN(); ++v) {
            if (g.getAdj()[u][v] > 0) {
                stk.push(v);
                g.remEdge(u, v);
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
        cout << circ[i] << " ";
    }
    cout << endl;
}
