#include <utility> // std::pair
#include <iostream>
#include <string>
#include <vector>
#include "graph.h"

int main()
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

    // Breadth first search
    std::pair<std::vector<size_t>, std::vector<size_t>> vertex_parents = 
        g.BreadthFirstSearch(ids_A_B.first);

    size_t first_vertex = vertex_parents.first[0]; // starting ID
    std::cout << "\nBFS starting at vertex " << g.GetVertexData(ids_A_B.first) << ":\n";
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

    // Depth first search
    std::vector<size_t> visit_order = g.DepthFirstSearch(ids_A_B.first, true);
    std::cout << "\nDFS starting at vertex " << g.GetVertexData(ids_A_B.first) << ":\n";
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
