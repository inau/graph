#ifndef GRAPH_LIBRARY_H
#define GRAPH_LIBRARY_H

#include <vector>

namespace Graph {

    template<class T>
    class Node {
    private:
        T value;
        std::vector<int> adjacent;

    public:
        void AddAdjacentVertex(int id) { this->adjacent.push_back(id); };
        std::vector<int> GetAdjacentVertices() { return this->adjacent; };

    };

    /** Graph Base Class **/
    template<class T>
    class Graph {
    protected:
        Node<T> *nodes;
        const int sz;

    public:
        Graph(int vertices) : sz(vertices) { nodes = new Node<T>[sz]; };

        Node<T> *GetVertex(int v) { return &nodes[v]; };

        void AddEdge(int v1, int v2) {
            nodes[v1].AddAdjacentVertex(v2);
            nodes[v2].AddAdjacentVertex(v1);
        }

        int GraphSize() { return sz; }
    };

    template<class T>
    class GridGraph : public Graph<T> {
    private:
        int col_sz, row_sz;
        int mapper_index(int col, int row) {
            int id = col + (row*row_sz);
            return id > this->sz ? -1 : id;
        };
    public:
        GridGraph(int col, int row)
                : Graph<T>( col*row ), col_sz(col), row_sz(row) {};

        int ColSize() { return col_sz; }
        int RowSize() { return row_sz; }

        void AddEdgeTo(int x1, int y1, int x2, int y2) {
            int v1 = mapper_index(x1, y1), v2 = mapper_index(x2,y2);
            this->AddEdge(v1, v2);
        }

        Node<T> *GetVertexAt(int col, int row) {
            return &this->nodes[ mapper_index(col, row) ];
        };

    };

    class MinimumSpanningTree {

    };
}

#endif