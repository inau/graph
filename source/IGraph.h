//
// Created by Ivan on 06-Aug-19.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#define Tmpl_K template<class Key>
#define Tmpl_V template<class Value>
#define Tmpl_K_V template<class Key, class Value>

#include <map>

namespace Graph
{
    Tmpl_K
    class IVertex1
    {
    public:
    //    virtual bool    AddAdjacentVertex(Key other_id) = 0;
        virtual Key*    GetAdjacentVertices(unsigned int& nKeys) = 0;
    };

    Tmpl_K_V
    class IEdge1
    {
    public:
        virtual Value   GetVal() = 0;
        virtual Key     GetFrom() = 0;
        virtual Key     GetTo() = 0;
    };

    Tmpl_K_V
    class IGraph1
    {
    public:
        virtual IVertex1<Key>*              GetVertex(Key uid) = 0;
        virtual unsigned int                GetSizeV() = 0;
        virtual unsigned int                GetKeys(Key* keys, unsigned int keys_len) = 0;

        virtual IEdge1<Key, Value>*         GetEdge(unsigned int idx) = 0;
        virtual unsigned int                GetSizeE() = 0;
        virtual unsigned int                GetEdges(IEdge1<Key, Value>** edges, unsigned int edges_len) = 0;

        virtual IVertex1<Key>*              GetVertexIdx(unsigned int uid) = 0;


    };

}
#endif //GRAPH_GRAPH_H
