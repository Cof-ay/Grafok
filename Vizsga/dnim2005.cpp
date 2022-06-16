#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <ctime>

#define INF 99999

using namespace std;

void beolvas(vector <vector <int>>& graf, int& n, int& m);

void topo_rendez(const vector<vector<int>>& graf, int u, int* volt, stack<int>& topo);

void BFS(const vector<vector <int>>& graf, vector<int>& topo, int& k, vector<int>& varosok);

void kiiratas(int k, vector<int>& varosok);

int main()
{
	clock_t time = clock();

	vector <vector <int>> graf;
	stack<int> topo;
	vector<int> topo_rendezett;
	int* volt;
	int n, m;

	beolvas(graf, n, m);
	volt = new int[n] {0};

	topo_rendez(graf, 0, volt, topo);

	while (topo.size() != 0)
	{
		topo_rendezett.push_back(topo.top());
		topo.pop();
	}

	int k = 0;
	vector <int> varosok;

	BFS(graf, topo_rendezett, k, varosok);

	kiiratas(k, varosok);
	
	varosok.clear();
	topo_rendezett.clear();
	graf.clear();

	cout << double(clock() - time) / CLOCKS_PER_SEC << endl;

	return 0;
}

void beolvas(vector <vector <int>>& graf, int& n, int& m)
{
	ifstream in("varosok2.in");
	in >> n >> m;

	graf.resize(n);

	int u, v;

	for (int i = 0; i < m; ++i)
	{
		in >> u >> v;
		u--;	v--;
		graf[u].push_back(v);
	}

	in.close();
}

void topo_rendez(const vector<vector<int>>& graf, int u, int* volt, stack<int>& topo)
{
	if (volt[u] != 2)
	{
		volt[u] = 1;
		for (int i = 0; i < graf[u].size(); ++i)
		{
			topo_rendez(graf, graf[u][i], volt, topo);
		}
		volt[u] = 2;
		topo.push(u);
	}
}

void BFS(const vector<vector <int>>& graf, vector<int>& topo, int& k, vector<int>& varosok)
{
	queue<int> sor;
	bool* volt = new bool[graf.size()]{ false };
	volt[0] = true;
	k = 1;
	varosok.push_back(0);

	for (int i = 0; i < topo.size(); ++i)
		sor.push(topo[i]);

	int u, v, p = 0;

	while (!sor.empty())
	{
		u = sor.front();

		for (int i = 0; i < graf[u].size(); ++i)
		{
			v = graf[u][i];
			if (volt[v] == false)
			{
				volt[v] = true;
				sor.push(v);
			}
		}

		sor.pop();
		if (sor.size() == topo.size())
		{
			varosok.push_back(sor.front());
			k++;
		}
	}
	

	delete[] volt;
}

void kiiratas(int k, vector<int>& varosok)
{
	ofstream out("varosok.out");
	out << k << endl;

	for (int i = 0; i < varosok.size(); ++i)
	{
		out << varosok[i] + 1 << endl;
	}

	out.close();
}