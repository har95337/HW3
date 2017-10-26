#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;
class Graph
{
public:

	Graph(int vert_count);

	Graph(int vert_count, double density);

	vector<int> neighbors(int x);

	inline void add_edge(int x, int y, double weight);

	inline bool adjacent(int x, int y);

	inline void delete_edge(int x, int y);

	inline double edge_weight(int x, int y) { return matrix[x][y]; };

	void print_Graph();

	void print_neighbors();

	int number_neighbors();

	int V() { return vert_count; };

	int E() { return edge_count; };

private:
	vector<vector<double>> matrix;

	const int max_weight = 10;

	int vert_count;

	int edge_count;
};

#endif