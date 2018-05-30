#include <utility> // std::pair
#include <iostream>
#include <string>
#include <vector>
#include "graph.h"

void TestBFS()
{
    // Using graph from Wikipedia entry on DFS: 
    // https://en.wikipedia.org/wiki/Depth-first_search
    Graph<std::string> g;

    std::pair<size_t, size_t> ids_A_B = g.AddEdgeAndVertices("A", "B");
    std::pair<size_t, size_t> ids_C_G = g.AddEdgeAndVertices("C", "G");
    std::pair<size_t, size_t> ids_E_F = g.AddEdgeAndVertices("E", "F");
    size_t id_D = g.AddVertex("D");

    g.AddEdge(ids_A_B.first, ids_C_G.first); // A<-->C
    g.AddEdge(ids_A_B.first, ids_E_F.first); // A<-->E
    g.AddEdge(ids_A_B.second, id_D); // B<-->D
    g.AddEdge(ids_A_B.second, ids_E_F.second); // B<-->F

    std::cout << "str graph:\n";
    std::cout << g;

    size_t start = ids_A_B.first;
    // Breadth first search
    std::pair<std::vector<size_t>, std::vector<size_t>> vertex_parents = 
        g.BreadthFirstSearch(start);

    size_t first_vertex = vertex_parents.first[0]; // starting ID
    std::cout << "\nBFS starting at vertex " << g.GetVertexData(start) << ":\n";
    for (size_t i = 0; i < vertex_parents.first.size(); ++i)
    {
        size_t curr_vertex = vertex_parents.first[i];
        int distance = 0;
        while (curr_vertex != first_vertex)
        {
            std::cout << g.GetVertexData(curr_vertex) << "->";
            curr_vertex = vertex_parents.second[curr_vertex];
            ++distance;
        }
        std::cout << g.GetVertexData(first_vertex) << ", distance = " << distance << "\n";
    }
}

void TestDFS()
{
    // Using graph from Wikipedia entry on DFS: 
    // https://en.wikipedia.org/wiki/Depth-first_search
    Graph<std::string> g;

    std::pair<size_t, size_t> ids_A_B = g.AddEdgeAndVertices("A", "B");
    std::pair<size_t, size_t> ids_C_G = g.AddEdgeAndVertices("C", "G");
    std::pair<size_t, size_t> ids_E_F = g.AddEdgeAndVertices("E", "F");
    size_t id_D = g.AddVertex("D");

    g.AddEdge(ids_A_B.first, ids_C_G.first); // A<-->C
    g.AddEdge(ids_A_B.first, ids_E_F.first); // A<-->E
    g.AddEdge(ids_A_B.second, id_D); // B<-->D
    g.AddEdge(ids_A_B.second, ids_E_F.second); // B<-->F

    std::cout << "str graph:\n";
    std::cout << g;

    size_t start = ids_A_B.first;
    // Depth first search
    std::vector<size_t> visit_order = g.DepthFirstSearch(start, true);
    std::cout << "\nDFS starting at vertex " << g.GetVertexData(start) << ":\n";
    for (size_t vertex_id : visit_order)
        std::cout << g.GetVertexData(vertex_id) << "->";
    std::cout << "\n";

    std::cout << "\nAccess vertex data using iterator: ";
    for (Graph<std::string>::GraphIterator it = g.begin(); it != g.end(); ++it)
    {
        std::cout << g.GetVertexData(*it) << " ";
    }
    std::cout << "\n";
}

void TestDijkstra()
{
    // Dijkstra's shortest path
    Graph<std::string> g;

    std::pair<size_t, size_t> ids_A_B = g.AddEdgeAndVertices("A", "B", 10);
    std::pair<size_t, size_t> ids_C_E = g.AddEdgeAndVertices("C", "E", 1);
    size_t id_D = g.AddVertex("D");

    g.AddEdge(ids_A_B.first, id_D, 10); // A<-->D
    g.AddEdge(ids_A_B.second, ids_C_E.first, 5); // B<-->C
    g.AddEdge(ids_C_E.second, id_D, 7); // E<-->D

    size_t start = ids_A_B.first;
    size_t end = ids_C_E.second;

    std::vector<size_t> shortest_path = g.ShortestPathDijkstra(start, end);
    std::cout << "\nShortest path from " << g.GetVertexData(start) 
        << " to " << g.GetVertexData(end) << ":\n";
    for (size_t vertex_id : shortest_path)
    {
        std::cout << g.GetVertexData(vertex_id) << "<-";
    }
    std::cout << "start\n";
}

int main()
{
    TestBFS();
    TestDFS();
    TestDijkstra();
}
