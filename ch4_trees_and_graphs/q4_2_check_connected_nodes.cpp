/*
Given a directed graph, design an algorithm to find out whether there is a route 
between two nodes.
*/

#include <utility> // std::pair
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "graph.h"

template <typename T>
class MyGraph : public Graph<T>
{
    public:
        MyGraph(bool directed = false) : Graph<T>(directed) {}
        bool IsConnected(size_t start_id, size_t end_id) const;
};


template <typename T>
bool MyGraph<T>::IsConnected(size_t start_id, size_t end_id) const
{
    enum class State { UNDISCOVERED, DISCOVERED, PROCESSED };

    std::vector<State> state(this->VertexCount(), State::UNDISCOVERED);
    std::queue<size_t> q;
    q.push(start_id);
    state[start_id] = State::DISCOVERED;

    while (!q.empty())
    {
        size_t curr = q.front();
        q.pop();
        for (auto e : this->vertices[curr].GetOutgoingEdges())
        {
            size_t neighbor = e.GetDestID();
            if (state[neighbor] == State::UNDISCOVERED)
            {
                if (neighbor == end_id)
                    return true;
                state[neighbor] = State::DISCOVERED;
                q.push(neighbor);
            }
        }
        state[curr] = State::PROCESSED;
    }
    return false;
}

int main()
{
    // Using graph from Wikipedia entry on DFS (modified to be directed): 
    // https://en.wikipedia.org/wiki/Depth-first_search
    MyGraph<std::string> g(true);

    std::pair<size_t, size_t> ids_A_B = g.AddEdgeAndVertices("A", "B"); // A-->B
    std::pair<size_t, size_t> ids_C_G = g.AddEdgeAndVertices("C", "G"); // C-->G
    std::pair<size_t, size_t> ids_F_E = g.AddEdgeAndVertices("F", "E"); // F-->E
    size_t id_D = g.AddVertex("D");

    g.AddEdge(ids_A_B.first, ids_C_G.first); // A-->C
    g.AddEdge(ids_A_B.first, ids_F_E.second); // A-->E
    g.AddEdge(ids_A_B.second, id_D); // B-->D
    g.AddEdge(ids_A_B.second, ids_F_E.first); // B-->F

    std::cout << "str graph:\n";
    std::cout << g;

    size_t v_A = ids_A_B.first;
    size_t v_F = ids_F_E.first;
    std::cout << "IsConnected(" << g.GetVertexData(v_A) << "," <<
        g.GetVertexData(v_F) << "): " << g.IsConnected(v_A, v_F) << "\n";
    std::cout << "IsConnected(" << g.GetVertexData(v_F) << "," <<
        g.GetVertexData(v_A) << "): " << g.IsConnected(v_F, v_A) << "\n";
}
