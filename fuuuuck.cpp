#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <set>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

bool iterativ_bfs(int n, vector<vector<int>>& sz_lista, int u, int v) {
    vector<bool> latogatott(n + 1, false);
    queue<int> it_sor;
    it_sor.push(v);
    bool megtalalt = false;
    while (!it_sor.empty() && !megtalalt) {
        int m_node = it_sor.front();
        latogatott[m_node] = true;
        if (m_node == u)
            megtalalt = true;
        it_sor.pop();
        for (int i = 0; i < sz_lista[m_node].size() && !megtalalt; i++) {
            int l_node = sz_lista[m_node][i];
            if (!latogatott[l_node])
                it_sor.push(l_node);
        }
    }
    return megtalalt;
}

void input_generator_directed_acyclic(char input[], int n, int m) {
    srand(time(NULL));
    pair<int, int> dummy_pair;
    ofstream fout(input);
    set<pair<int, int>> ellista;
    vector<vector<int>> sz_lista(n + 1);
    fout << n << " " << m << endl;
    for (int i = 0; i < m; i++) {
        bool mar_van = true;
        while (mar_van) {
            int baj_szam = 0;
            dummy_pair.first = rand() % n + 1;
            dummy_pair.second = rand() % n + 1;
            if (dummy_pair.first == dummy_pair.second)
                baj_szam++;
            set<pair<int, int>>::iterator it = ellista.find(dummy_pair);
            if (it != ellista.end())
                baj_szam++;
            if (iterativ_bfs(n, sz_lista, dummy_pair.first, dummy_pair.second))
                baj_szam++;
            if (baj_szam == 0) {
                mar_van = false;
                sz_lista[dummy_pair.first].push_back(dummy_pair.second);
                ellista.insert(dummy_pair);
            }
        }
        fout << dummy_pair.first << " " << dummy_pair.second << endl;
        cout << i << endl;
    }

}

int main()
{

    char input[] = "lab1_5_2.in";

    input_generator_directed_acyclic(input, 1000000, 1000000);

    return 0;

}