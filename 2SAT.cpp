#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000;

vector<int> adjacent[MAX];
vector<int> adjacentInv[MAX];
bool visited[MAX];
bool visitedInv[MAX];
stack<int> s;

void Reset();

// this array will store the SCC that the particular node belongs to
int scc[MAX];

// counter is used to maintain the number of the SCC
int counter = 1;

// This adds edges to form the original graph
void addEdges(int a, int b)
{
    adjacent[a].push_back(b);
}

// add edges to form the inverse graph/ Transpose Graph
void addEdgesInverse(int a, int b)
{
    adjacentInv[b].push_back(a);
}

// for STEP 1 of Kosaraju's Algorithm
void dfsFirst(int u)
{
    if (visited[u])
        return;

    visited[u] = 1;

    for (int i = 0; i < adjacent[u].size(); i++)
        dfsFirst(adjacent[u][i]);

    s.push(u);
}

// for STEP 2 of Kosaraju's Algorithm
void dfsSecond(int u)
{
    if (visitedInv[u])
        return;

    visitedInv[u] = 1;

    for (int i = 0; i < adjacentInv[u].size(); i++)
        dfsSecond(adjacentInv[u][i]);
    scc[u] = counter;
}

// function to check 2-Satisfiability
void is2Satisfiable(int n, int m, int a[], int b[])
{
    // adding edges to the graph
    for (int i = 0; i < m; i++)
    {
        // variable x is mapped to x
        // variable -x is mapped to n+x = n-(-x)

        // p V q === ~p -> q         (p+n) --------> q

        // for a[i] V b[i], addEdges -a[i] -> b[i]
        // AND    -b[i] -> a[i]
        if (a[i] > 0 && b[i] > 0)
        {
            addEdges(a[i] + n, b[i]);
            addEdgesInverse(a[i] + n, b[i]);
            addEdges(b[i] + n, a[i]);
            addEdgesInverse(b[i] + n, a[i]);
        }

        else if (a[i] > 0 && b[i] < 0) // X1 V ~X2 === -X1 -> ~X2
        {
            addEdges(a[i] + n, n - b[i]);
            addEdgesInverse(a[i] + n, n - b[i]);
            addEdges(-b[i], a[i]);
            addEdgesInverse(-b[i], a[i]);
        }

        else if (a[i] < 0 && b[i] > 0)
        {
            addEdges(-a[i], b[i]);
            addEdgesInverse(-a[i], b[i]);
            addEdges(b[i] + n, n - a[i]);
            addEdgesInverse(b[i] + n, n - a[i]);
        }

        else
        {
            addEdges(-a[i], n - b[i]);
            addEdgesInverse(-a[i], n - b[i]);
            addEdges(-b[i], n - a[i]);
            addEdgesInverse(-b[i], n - a[i]);
        }
    }

    // STEP 1 of Kosaraju's Algorithm which
    // traverses the original graph
    for (int i = 1; i <= 2 * n; i++)
        if (!visited[i])
            dfsFirst(i);

    // STEP 2 pf Kosaraju's Algorithm which
    // traverses the Transpose graph. After this,
    // array scc[] stores the corresponding value
    while (!s.empty())
    {
        int n = s.top();
        s.pop();

        if (!visitedInv[n])
        {
            dfsSecond(n);
            counter++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        // for any 2 variable x and -x lie in
        // same SCC
        if (scc[i] == scc[i + n])
        {
            cout << "\nThe given expression "
                    "is unsatisfiable."
                 << endl;
            return;
        }
    }

    // no such variables x and -x exist which lie
    // in same SCC
    cout << "\nThe given expression is satisfiable."
         << endl;

    Reset();

    return;
}

int main()
{
    // n is the number of variables
    // 2n is the total number of nodes
    // m is the number of clauses in CNF expression

    // UNSATISFIABLE

    //(~A V B)∧(~B V ~A)∧(A V C)∧(B V C)∧(A V A)

    int a2[] = {-1, -2, 1, 2, 1};
    int b2[] = {2, -1, 3, 3, 1};

    int n2 = 3, m2 = 5;
    is2Satisfiable(n2, m2, a2, b2);

    // SATISFIABLE

    // (A V B)∧(~B V C)∧(~A V ~B)∧(C V D)∧(~C V E)∧(~D + ~E)∧(~C V D)

    int n1 = 5, m1 = 7;
    int a1[] = {1, -2, -1, 3, -3, -4, -3};
    int b1[] = {2, 3, -2, 4, 5, -5, 4};

    is2Satisfiable(n1, m1, a1, b1);
    cout << endl;

    return 0;
}

void Reset()
{ // bool *visited[MAX], bool *visitedInv[MAX], vector <int> (&adjacent)[MAX],vector<int> (&adjacentInv)[MAX]

    visited[MAX] = {0};
    visitedInv[MAX] = {0};

    for (auto &v : adjacent)
    {
        v.clear();
    }
    for (auto &v : adjacentInv)
    {
        v.clear();
    }
}