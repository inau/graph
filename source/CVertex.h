//
// Created by Ivan on 06-Aug-19.
//
#ifndef GRAPH_GRAPH_vertex_H
#define GRAPH_GRAPH_vertex_H

#include <vector>
#include <algorithm>
#include <memory>
#include "IGraph.h"

using namespace Graph;

namespace Graph
{
    Tmpl_K
    class CVertex1 : public IVertex1<Key>
    {
    protected:
        Key m_key;
        //const Key* m_key;
        std::vector<Key> m_adjacent;

    public:
        CVertex1(Key key) : m_key(key) {};

        bool    AddAdjacentVertex(Key other_id)
        {
            bool found = false;
            for( Key k : m_adjacent )
            {
                found = (k == other_id);
                if( found ) break;
            }

            // Insert if not found
            if( !found ) m_adjacent.push_back(other_id);

            return !found;
        };

        Key*    GetAdjacentVertices(unsigned int& nKeys) override { nKeys = m_adjacent.size(); return m_adjacent.data(); };
    };
}

#endif