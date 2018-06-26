#ifndef GRAPH_LIBRARY_H
#define GRAPH_LIBRARY_H

#include <vector>
#include <iostream>
#include <algorithm>

namespace Graph {
    extern "C++" {
    class UnionFind {
    protected:
        int *Rank, *Parent;
        const int vertices;

        bool IsRoot(int v) { return Parent[v] == v; };

        int FindRoot(int v) {
            int r = v;
            while (!IsRoot(r)) {
                r = Parent[r];
            }
            //compress
            Parent[v] = r;

            return r;
        }

        void AttachComponentToRoot(int v, int root) {
            Parent[v] = root;
            Rank[root] += Rank[v];
        }

    public:
        UnionFind(int vertex_count) : vertices(vertex_count) {
            Rank = new int[vertices];
            std::fill_n(Rank, vertices, 1);
            Parent = new int[vertices];
            for (int i = 0; i < vertices; ++i) {
                Parent[i] = i;
            }
        }

        ~UnionFind() {
            delete (Rank);
            delete (Parent);
        }

        void Union(const int v0, const int v1) {
            int r;
            if (Rank[v0] >= Rank[v1]) {
                r = FindRoot(v0);
                AttachComponentToRoot(v1, r);
            } else {
                r = FindRoot(v1);
                AttachComponentToRoot(v0, r);
            }
        }

        int Find(const int v) {
            return FindRoot(v);
        }
    };
    };

    template <class T>
    struct Edge {
        int vertex_from, vertex_to;
        T edge_weight;
        //Edge() : vertex_from(0), vertex_to(0), edge_weight(0) {};
        //Edge(int v0, int v1, T weight) : vertex_from(v0), vertex_to(v1), edge_weight(weight) {};
        bool operator<(Edge other) const {
            return edge_weight > other.edge_weight;
        }
    };

    extern "C" {
        typedef Edge<int> intEdge;
    };


    class Vertex {
    private:
        std::vector<int> adjacent;

    public:
        void AddEdge(int e_id) { this->adjacent.push_back(e_id); };

        std::vector<int> GetAdjacentVertices() { return this->adjacent; };
    };

    /**
     * Graph Base Class
     **/
    template<class T>
    class Graph {
    protected:
        Vertex *nodes;
        std::vector<Edge<T>> edges;

        const int sz;
        void _AddEdge(int v1, int v2, T weight, bool biDirectional = false) {
            Edge<T> e{v1,v2,weight};
            edges.push_back(e);
            nodes[v1].AddEdge(edges.size()-1);
            if( biDirectional )
                nodes[v2].AddEdge(edges.size()-1);
        }

    public:
        Graph(int vertices) : sz(vertices) {
            nodes = new Vertex[sz];
        };

        void AddEdge(int v1, int v2, T weight, bool biDirectional = false) {
            _AddEdge(v1,v2,weight,biDirectional);
        }

        Vertex *GetVertex(int v) { return &nodes[v]; };
        std::vector<Edge<T>> GetEdges() { return edges; };

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

        void AddEdge(int x1, int y1, int x2, int y2, T weight,  bool biDirectional = false) {
            int v1 = mapper_index(x1, y1), v2 = mapper_index(x2,y2);
            this->_AddEdge(v1, v2, weight, biDirectional);
        }


        Vertex *GetVertexAt(int col, int row) {
            return &this->nodes[ mapper_index(col, row) ];
        };

    };

    template <class T>
    std::vector<Edge<T>> minimum_spanning_tree(Graph<T> &g ) {
        std::vector<Edge<T>> mst;

        //sort edges by weight
        std::vector<Edge<T>> sortedEdges = g.GetEdges();
        std::sort(sortedEdges.begin(), sortedEdges.end() );

        //UnionFind structure
        UnionFind uf( g.GraphSize() );

        //add smallest edge
        Edge<T> *e;
        e = &sortedEdges[0];
        uf.Union( e->vertex_from , e->vertex_to );

        for (int i = 1; i < sortedEdges.size(); i++) {
            e = &sortedEdges[i];

            //find parent affiliation
            int pi = uf.Find( e->vertex_from );
            int pu = uf.Find( e->vertex_to );

            //different components
            if( pi != pu ) {
                uf.Union(e->vertex_from, e->vertex_to);
                mst.push_back(*e);
            }

            //if edges added reach V-1 we have a edge for every pair of nodes
            if( !(mst.size() < g.GraphSize()) ) break;
        }
        return mst;
    }


    template <class T>
    void PrintGraph(Graph<T> &g) {
        std::cout << "Vertex outdegree" << "\n" ;
        for (int i = 0; i < g.GraphSize(); ++i) {
            std::cout << g.GetVertex(i)->GetAdjacentVertices().size() << " " ;
        }
    }

    template <class T>
    void PrintGraph(GridGraph<T> &g) {
        std::cout << "Vertex outdegree" << "\n" ;
        for (int col = 0; col < g.ColSize(); ++col) {
            for (int row = 0; row < g.RowSize(); ++row) {
                std::cout << g.GetVertexAt(col, row)->GetAdjacentVertices().size() << " " ;
            }
            std::cout << "\n" ;
        }
    }
}
#endif