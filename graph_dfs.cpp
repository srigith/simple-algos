// Sriprasadh: Aug 04, 2017.
// Graph: Depth-first search

// ----- Includes -----
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
// -------------------

using std::vector;
using std::pair;
using std::make_pair;

using vtx_t = unsigned;	// Type-alias to identify vertex
using vtx_s = unsigned;	// Type-alias for size of vertices
// -------------------

// Simple struct to store a graph as a list of neighboring vertices
// for each vertex.

struct graph
{
public:
	graph(vtx_s cnt) : num_v(cnt), neighbors(cnt)
	{}
	
	void add_edge(vtx_t a, vtx_t b, int cost)
	{
		neighbors[a].emplace_back(b, cost);
		neighbors[b].emplace_back(a, cost);
	}
	// For use from C++17 onwards:
	void add_edges(std::initializer_list<std::tuple<vtx_t, vtx_t, int>> eds)
	{
		for (const auto &e :eds)
			add_edge(std::get<0>(e), std::get<1>(e), std::get<2>(e));
	}
		
	vtx_s num_v = 0;	// Number of vertices	
	vector<vector<pair<vtx_t, int>>> neighbors; 
};
// -------------------

void dfs_recurse(const graph &G, vtx_t curr, vector<bool> &visited, std::function<void(vtx_t)> fn)
{
	visited[curr] = true;
	fn(curr);
	
	for (const auto &adj : G.neighbors[curr])
	{
		if (!visited[adj.first])
			dfs_recurse(G, adj.first, visited, fn);
	}
}

void dfs(const graph &G, vtx_t start, std::function<void(vtx_t)> fn)
{
	vector<bool> visited(G.num_v, false);
	dfs_recurse(G, start, visited, fn);
}

int main()
{
	graph g1(10);
	g1.add_edge(0, 1, 7);
	g1.add_edge(0, 2, 8);
	g1.add_edge(1, 3, 6);
	g1.add_edge(2, 3, 4);
	g1.add_edge(3, 4, 8);
	g1.add_edge(2, 4, 14);
	g1.add_edge(4, 7, 2);
	g1.add_edge(3, 8, 5);
	g1.add_edge(6, 5, 3);
	g1.add_edge(3, 5, 14);
	g1.add_edge(5, 9, 6);
	g1.add_edge(8, 6, 9);
	g1.add_edge(7, 5, 3);
	g1.add_edge(8, 9, 15);
	
	auto print_vertex = [](vtx_t v) { std::cout << v << " "; };
	
	dfs(g1, 0, print_vertex);
	
	return 0;
}
// -------------------
