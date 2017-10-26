#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

#include "Graph.hpp"

using namespace std;
Graph::Graph(int vert_count)
{
	// This is a simple Graph constructor made for manual graph creation
	Graph::vert_count = vert_count;
	matrix = vector<vector<double>>(vert_count, vector<double>(vert_count));
	for(int i = 0; i < vert_count; i++)
	{
		for (int j = 0; j < vert_count; j++)
		{
			matrix[i][j] = -1.0;
		}
	}
}

Graph::Graph(int vert_count, double density)
{
	Graph::vert_count = vert_count;

	matrix = vector<vector<double>>(vert_count, vector<double>(vert_count));

	// Initialize and set ranges for random
	default_random_engine generator;
	uniform_real_distribution<double> density_distribution(0.0, 1.0);
	uniform_real_distribution<double> weight_distribution(0.0, 10.0);

	// Max neighbors limits the number of neighbors to be created
	double max_neighbors = (vert_count * density);
	for (int i = 0; i < vert_count; ++i)
	{
		for (int j = 0; j < vert_count; ++j)
		{
			double prob = density_distribution(generator);
			vector<int> neighborhood = neighbors(j);

			// Here create an edge if probability passes and making sure we avoid self connected nodes
			// Neighborhood returns a vector list of all neighbors of a certain row and we want to check it doesn't exceed max_neighbors
			if ((prob < density) && (i != j) && (neighborhood.size() <= max_neighbors))
			{
				double new_weight = weight_distribution(generator);
				add_edge(i, j, new_weight);
			}
			else {
				add_edge(i, j, -1.0);
			}
		}
	}
}

vector<int> Graph::neighbors(int x)
{
	vector<int> container(matrix.size());

	// Since each index is a node check the indexes that have edges and if there is an edge there add that index to container
	for (int i = 0; i < matrix.size(); i++)
	{
		// Fill empty spaces in the matrix with -1 so that we can erase those indexes
		if (matrix[x][i] != -1.0) container[i] = i;
		else container[i] = -2.0;
	}
	// These 2 lines delete all the -1s in container to make a vector that only has neighbors
	container.erase(remove(container.begin(), container.end(), -2), container.end());
	container.shrink_to_fit();
	return container;
}

inline void Graph::add_edge(int x, int y, double weight)
{
		matrix[x][y] = matrix[y][x] = weight;
		edge_count++;
}

inline bool Graph::adjacent(int x, int y)
{
	if ((matrix[x][y] != -1.0) && (matrix[y][x] != -1.0))
	{
		return true;
	}
	return false;
}

inline void Graph::delete_edge(int x, int y)
{
	matrix[x][y] = matrix[y][x] = -1.0;
	edge_count--;
}

void Graph::print_Graph()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < matrix.size(); j++)
		{
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
}

void Graph::print_neighbors()
{
	for (int p = 0; p < matrix.size(); p++)
	{
		auto neighborhood = neighbors(p);
		cout << p << ": ";
		for (auto i : neighborhood)
		{
			cout << i << ' ';
		}
		cout << endl;
	}
}

int Graph::number_neighbors()
{
	int num_neighbors = 0;
	for (int p = 0; p < matrix.size(); p++)
	{
		auto neighborhood = neighbors(p);
		for (auto i : neighborhood)
		{
			num_neighbors++;
		}
	}
	return num_neighbors;
}