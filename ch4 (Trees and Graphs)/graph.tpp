#include <stdexcept> // std::out_of_range
#include <queue> // for Breadth First Search
#include <stack> // for Depth First Search

template <typename T>
size_t Graph<T>::AddVertex(const T & value)
{
    size_t id = VertexCount();
    vertices.push_back(Vertex(id, value));
    return id;
}

template <typename T>
std::pair<size_t, size_t> Graph<T>::AddEdgeAndVertices(const T & start_value, 
        const T & end_value, int cost)
{
    size_t start_id = AddVertex(start_value);
    size_t end_id = AddVertex(end_value);
    AddEdge(start_id, end_id, cost);
    return std::make_pair(start_id, end_id);
}

template <typename T>
void Graph<T>::AddEdge(size_t start_id, size_t end_id, int cost)
{
    if (start_id < 0 || start_id >= VertexCount())
        throw std::out_of_range("Start vertex id out of range");
    if (end_id < 0 || end_id >= VertexCount())
        throw std::out_of_range("End vertex id out of range");
    vertices[start_id].AddEdge(end_id, cost);
    if (!directed)
        vertices[end_id].AddEdge(start_id, cost);
}

template <typename T>
size_t Graph<T>::VertexCount() const
{
    return vertices.size();
}

template <typename T>
const T & Graph<T>::GetVertexData(size_t vertex_id) const
{
    return vertices[vertex_id].GetData();
}

template <typename T>
T & Graph<T>::GetVertexData(size_t vertex_id)
{
    return vertices[vertex_id].GetData();
}

template <typename T>
std::pair<std::vector<size_t>, std::vector<size_t>> Graph<T>::BreadthFirstSearch(size_t start_id) const
{
    std::vector<size_t> parent(VertexCount(), -1);
    std::vector<size_t> vertex_ids(VertexCount(), -1);
    std::vector<bool> visited(VertexCount(), false);
    
    std::queue<size_t> q; // holds vertex ids still to be explored
    q.push(start_id);
    int index = 0;
    vertex_ids[index++] = start_id;
    parent[start_id] = -1;
    visited[start_id] = true;

    while (!q.empty())
    {
        size_t id = q.front();
        q.pop();
        // process vertex here if desired
        for (const OutEdge e : vertices[id].GetOutgoingEdges())
        {
            size_t neighbor_id = e.GetDestID();
            if (!visited[neighbor_id])
            {
                visited[neighbor_id] = true;
                vertex_ids[index++] = neighbor_id;
                parent[neighbor_id] = id;
                q.push(neighbor_id);
            }
        }
    }
    return std::make_pair(vertex_ids, parent);
}

template <typename T>
std::vector<size_t> Graph<T>::DepthFirstSearch(size_t start_id, bool recursive) const
{
    std::vector<bool> visited(VertexCount(), false);

    // Recursive implementation
    if (recursive)
    {
        std::vector<size_t> visit_order_recursive;
        DepthFirstSearchRecursive(start_id, visit_order_recursive, visited);
        return visit_order_recursive;
    }

    // Iterative implementation
    std::vector<size_t> visit_order(VertexCount(), -1);
    std::stack<size_t> s; // holds vertex ids still to be explored
    s.push(start_id);

    int index = 0;
    while (!s.empty())
    {
        size_t id = s.top();
        s.pop();
        if (!visited[id])
        {
            visited[id] = true;
            visit_order[index++] = id;
            for (const OutEdge e : vertices[id].GetOutgoingEdges())
            {
                size_t neighbor_id = e.GetDestID();
                s.push(neighbor_id);
            }
        }
    }
    return visit_order;
}

template <typename T>
std::ostream & operator<<(std::ostream & out, const Graph<T> & g)
{
    g.Print(out);
    return out;
}

template <typename T>
typename Graph<T>::GraphIterator Graph<T>::begin() const
{
    return GraphIterator(0);
}

template <typename T>
typename Graph<T>::GraphIterator Graph<T>::end() const
{
    return GraphIterator(vertices.size());
}

template <typename T>
void Graph<T>::DepthFirstSearchRecursive(size_t vertex_id, std::vector<size_t> & visit_order, 
        std::vector<bool> & visited) const
{
    visited[vertex_id] = true;
    visit_order.push_back(vertex_id); // pre-order
    for (const OutEdge e : vertices[vertex_id].GetOutgoingEdges())
    {
        size_t neighbor_id = e.GetDestID();
        if (!visited[neighbor_id])
            DepthFirstSearchRecursive(neighbor_id, visit_order, visited);
    }
    // post-order visit would go here
}


template <typename T>
void Graph<T>::Print(std::ostream & out) const
{
    out << "V = ";
    for (const Vertex v : vertices)
        out << v.GetData() << " ";
    out << "\n";
    out << "E = ";
    for (const Vertex v : vertices)
    {
        out << "[" << v.GetData() << ":";
        for (const OutEdge e : v.GetOutgoingEdges())
        {
            out << " " << vertices[e.GetDestID()].GetData();
        }
        out << "] ";
    }
    out << "\n";

}

template <typename T>
const size_t Graph<T>::OutEdge::GetDestID() const
{
    return dest_id;
}

template <typename T>
const int Graph<T>::OutEdge::GetCost() const
{
    return cost;
}

template <typename T>
void Graph<T>::Vertex::AddEdge(size_t end_id, int cost)
{
    outgoing_edges.push_back(OutEdge(end_id, cost));
}

template <typename T>
const T & Graph<T>::Vertex::GetData() const
{
    return data;
}

template <typename T>
T & Graph<T>::Vertex::GetData()
{
    return data;
}

template <typename T>
const std::vector<typename Graph<T>::OutEdge> & Graph<T>::Vertex::GetOutgoingEdges() const
{
    return outgoing_edges;
}
