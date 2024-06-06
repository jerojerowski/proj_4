#include "eulercycle.h"
#include "graph.h"
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

bool isEuler() {
    int oddCnt = 0;
    for (int i = 0; i < Graph::getN(); ++i) {
        int deg = 0;
        for (int j = 0; j < Graph::getN(); ++j) {
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

    int start = 0;
    for (int i = 0; i < Graph::getN(); ++i) {
        int deg = 0;
        for (int j = 0; j < Graph::getN(); ++j) {
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

    while (!stk.empty()) {
        int u = stk.top();
        bool found = false;
        for (int v = 0; v < Graph::getN(); ++v) {
            if (Graph::getAdj()[u][v] > 0) {
                stk.push(v);
                Graph::remEdge(u, v);
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
        if(i>0) cout<<" -> ";
    }
    cout << endl;
}
