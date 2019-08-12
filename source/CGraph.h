//
// Created by Ivan on 06-Aug-19.
//
#ifndef GRAPH_GRAPH_graph_H
#define GRAPH_GRAPH_graph_H

#include <memory>
#include "IGraph.h"
#include "CVertex.h"

namespace Graph
{

    Tmpl_K_V
    class CGraph : public IGraph1<Key,Value>
    {
    protected:
        std::map<Key, std::shared_ptr<CVertex1<Key>>> vertices;
        std::vector<std::shared_ptr<CEdge1<Key,Value>>> edges;

        bool VertexExists(Key key) { return vertices.count(key) > 0;}

    public:
        IVertex1<Key>*              GetVertex(Key uid) override
        {
            IVertex1<Key>* res = nullptr;
            if( vertices.count(uid) > 0 ){ res = vertices[uid].get(); }
            return res;
        };

        unsigned int                GetSizeV() override {return vertices.size();};

        unsigned int                GetKeys(Key* keys, unsigned int keys_len) override
        {
            int i = 0u;
            for(auto it = vertices.begin(); it != vertices.end(); it++)
            {
                if( i < keys_len )
                {
              //      keys[i] = (*it).first;
                    i++;
                } else break;
            }
            return i;
        };

        IEdge1<Key, Value>*        GetEdge(unsigned int idx) override
        {
            IEdge1<Key, Value>* res = nullptr;
            if( idx < edges.size() ) { res = edges[idx].get(); }
            return res;
        };

        unsigned int                GetSizeE() override {return edges.size();};

        unsigned int                GetEdges(IEdge1<Key, Value>** edges_out, unsigned int edges_len) override
        {
            int i = 0u;
            for(auto it = edges.begin(); it < edges.end(); it++)
            {
                if( i < edges_len )
                {
                    edges_out[i] = (*it).get();
                    i++;
                } else break;
            }
            return i;
        };

        IVertex1<Key>*              GetVertexIdx(unsigned int idx) override
        {
            IVertex1<Key>* res = nullptr;
            auto iter = vertices.begin();
            std::advance(iter, idx);
            if( iter != vertices.end() ){ res = (*iter).second.get(); }
            return res;
        };
    public:
        bool AddVertex(Key key)
        {
            vertices.insert(std::make_pair(key,std::make_shared<CVertex1<Key>>(key)));
        }
        bool AddEdge(Key from, Key to, Value val, bool Bidirectional = false) {
            bool res = false;
            if (VertexExists(from) && VertexExists(to)) {
                edges.push_back(std::make_shared<CEdge1<Key,Value>>(from, to, val));
                vertices[from]->AddAdjacentVertex(to);
                if( Bidirectional )
                {
                    vertices[to]->AddAdjacentVertex(from);
                }
                res = true;
            };
            return res;
        }
    };

    class Key2D
    {
    protected:
        unsigned int Col, Row;

    public:
        Key2D(unsigned c, unsigned r) : Col(c), Row(r) {}
        Key2D() : Col(0u), Row(0u) {}

        unsigned GetCol() const { return Col; }
        unsigned GetRow() const { return Row; }

        inline bool operator<(const Key2D& other) const
        {
            return  std::tie(Col,Row) < std::tie(other.Col,other.Row);
        }
        //inline bool operator>(const Key2D& other) const { return !other.operator<(*this); }
        inline bool operator==(const Key2D& other) const { return !other.operator<(*this) && !this->operator<(other); }
        inline bool operator!=(const Key2D& other) const { return !other.operator==(*this); }
    };

    template <class Value>
    class GridGraph1 : public CGraph<Key2D, Value>
    {
    protected:
        unsigned w,h;
    public:
        GridGraph1(unsigned cols, unsigned rows) : w(cols), h(rows)
        {
            for (auto row = 0u; row < h; row++)
                for (auto col = 0u; col < w; col++) {
                    Key2D key(col,row);
                    CGraph<Key2D, Value>::AddVertex(key);
                }
        }

        unsigned GetWidth() { return w;}
        unsigned GetHeight() { return h;}
    };
}

#endif