//
// Created by Ivan on 06-Aug-19.
//
#ifndef GRAPH_GRAPH_edge_H
#define GRAPH_GRAPH_edge_H
#include "IGraph.h"

namespace Graph
{
    Tmpl_K_V
    class CEdge1 : public IEdge1<Key, Value>
    {
    protected:
        Key m_from;
        Key m_to;
        Value m_value;
    public:
        CEdge1(Key from, Key to, Value val) : m_from(from), m_to(to), m_value(val) {};
        Value   GetVal()    {return m_value;}
        Key     GetFrom()   {return m_from;}
        Key     GetTo()     {return m_to;}

        bool SetValue(Value v) { m_value = v;}
    };
}

template<class Identifier, class Item>
class CEdge : IEdge<Identifier, Item> {
protected:
    IVertex<Identifier,Item> v1;
    IVertex<Identifier,Item> v2;
public:
    IVertex<Identifier,Item>& From()    { return v1; };
    IVertex<Identifier,Item>& To()      { return v2; };
};

#endif