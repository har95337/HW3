// HW3.cpp : Defines the entry point for the console application.

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <functional>
#include <utility>
#include <fstream>
#include "Graph.hpp"

using namespace std;
// Prototypes
vector<int> prims(Graph &graph, int source);

int main()
{
	// Setting up reading from input file
	int x, y, lines = 0, nodes;
	double weight;
	ifstream read("input.txt");
	read >> nodes;
	Graph custom(nodes);
	while (read >> x >> y >> weight)
	{
		custom.add_edge(x, y, weight);
	}
	// Run Prims on Custom Graph
	vector<int> MST_1 = prims(custom, 0);
	cout << "";
	for (int i = 1; i < custom.V(); i++)
	{
		cout << MST_1[i] << " - " << i << " | " << custom.edge_weight(i, MST_1[i]) << endl;
	}

	// Genererated Graph
	Graph generated(100, 0.2);
	vector<int> MST_2 = prims(generated, 0);
	for (int i = 1; i < generated.V(); i++)
	{
		cout << MST_2[i] << " - " << i << " | " << generated.edge_weight(i, MST_2[i]) << endl;
	}
	getchar();
	return 0;
}

vector<int> prims(Graph &graph, int source)
{
	priority_queue< pair<double, int>, vector< pair<double, int> >, greater<pair<double, int> >> pq;
	vector<int> parent(graph.V());
	vector<double> dist(graph.V(), INT_MAX);

	pq.push(make_pair(dist[0], source));

	for (int v = 0; v < graph.V(); v++)
	{
		if (v != source)
		{
			dist[v] = DBL_MAX;
		}
		pq.push(make_pair(dist[v], v));
	}


	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		vector<int> neighbors = graph.neighbors(u);

		for (auto v : neighbors)
		{
			double cur_dist = graph.edge_weight(u, v);
			bool visited = (find(parent.begin(), parent.end(), v) != parent.end());

			if (!visited && dist[v] > cur_dist)
			{
				dist[v] = cur_dist;
				pq.push(make_pair(dist[v], v));
				parent[v] = u;
			}
		}
	}
	return parent;
}