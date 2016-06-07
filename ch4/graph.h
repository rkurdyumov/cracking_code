#ifndef GRAPH_H
#define GRAPH_H

#include <utility> // std::pair
#include <ostream>
#include <vector>

template <typename T>
class Graph
{
    public:
        Graph(bool directed = false) : directed(directed) {}

        size_t VertexCount() const;
        size_t AddVertex(const T & value);
        const T & GetVertexData(size_t vertex_id) const;
        T & GetVertexData(size_t vertex_id);
        
        void AddEdge(size_t start_id, size_t end_id, int cost = 0);
        std::pair<size_t, size_t> AddEdgeAndVertices(const T & start_value, 
                const T & end_value, int cost = 0);
        
        // BFS returns vector pair <vertex_id, parent of this vertex>
        std::pair<std::vector<size_t>, std::vector<size_t>> BreadthFirstSearch(size_t start_id) const;
        std::vector<size_t> DepthFirstSearch(size_t start_id, bool recursive = false) const;

        template <typename U>
        friend std::ostream & operator<<(std::ostream & out, const Graph<U> & g);

        class GraphIterator
        {
            public:
                typedef std::input_iterator_tag iterator_category;
                typedef size_t                  value_type;
                typedef size_t                  difference_type;
                typedef size_t *                pointer;
                typedef size_t &                reference;

                GraphIterator(size_t value) : current(value) { }

                GraphIterator & operator++() { ++current; return (*this); }
                GraphIterator operator++(int) { return GraphIterator(current++); }

                value_type operator*() const { return current; }

                bool operator==(const GraphIterator & rhs) { return current == rhs.current; }
                bool operator!=(const GraphIterator & rhs) { return !((*this) == rhs); }
            
            private:
                size_t current;
        };
        GraphIterator begin() const;
        GraphIterator end() const;

    protected:
        class Vertex; // forward declare;

        std::vector<Vertex> vertices;
        const bool directed;
        
        void DepthFirstSearchRecursive(size_t vertex_id, std::vector<size_t> & visit_order,
                std::vector<bool> & visited) const;
        void Print(std::ostream & out) const;
        
        class OutEdge
        {
            public:
                OutEdge(int end_id, int cost): dest_id(end_id), cost(cost) {}
                const size_t GetDestID() const;
                const int GetCost() const;

            private:
                size_t dest_id;
                int cost;
        };

        class Vertex
        {
            public:
                Vertex(size_t id, T value): id(id), data(value) {}
                void AddEdge(size_t end_id, int cost);
                const T & GetData() const;
                T & GetData();
                const std::vector<OutEdge> & GetOutgoingEdges() const;
            
            private:
                size_t id; // unique identifier
                T data; 
                std::vector<OutEdge> outgoing_edges;
        };

};

/*
template <typename T>
class GraphIterator
{
    friend class Graph<T>;

    public:
        GraphIterator(Graph<T> & g) : graph(g) {}
        GraphIterator begin() { return graph.vertices.begin(); }
        GraphIterator end() { return graph.vertices.end(); }
        bool operator!=(GraphIterator & other) { return *this != other; }
        GraphIterator operator++() { return ++(*this); } 

    private:
        Graph<T> & graph;
};
*/


#include "graph.tpp"

#endif
