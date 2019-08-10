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

template<class Identifier, class Item>
class CVertex : public IVertex<Identifier, Item> {
protected:
    std::vector<IVertex<Identifier, Item>*> adjacent;
    Identifier id;
    Item item;
public:
    CVertex(Identifier i) : id(i) {};

    bool Connect(IVertex<Identifier, Item>* pOther)
    {
        bool res = false;
        if(pOther && pOther != this)
        {
            bool found = false;
            for( auto p : adjacent )
            {
                if( p == pOther )
                {
                    found = true ;
                    break;
                }
            }

            if( !found )
            {
                adjacent.push_back(pOther);
                res = true;
            }
        }
        return res;
    };
    bool Disconnect(IVertex<Identifier, Item>* pOther)
    {
        bool deleted = false;
        if(pOther && pOther != this)
        {
            auto it = adjacent.begin();
            for( ; it != adjacent.end(); it++ ) {
                if (*it == pOther)
                {
                    auto it_found = it;
                    it = adjacent.erase(it_found);
                    if (it_found != it) deleted = true;
                    break;
                }
            }
        }
        return deleted;
    };

    const Identifier                  GetId()     { return id;    };
    Item&                       GetItem()   { return item;  };
    IVertex<Identifier, Item>**  GetAdjacent(unsigned int& nResults)
    {
        nResults = adjacent.size();
        return adjacent.data();
    };
};

#endif