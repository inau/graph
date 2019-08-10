//
// Created by Ivan on 09-Aug-19.
//

#ifndef GRAPH_ITOPOLOGIES_H
#define GRAPH_ITOPOLOGIES_H

#include "IGraph.h"
#include "CGraph.h"
#include "IValueGenerators.h"

namespace Graph {
    namespace Topo {
        Tmpl_V
        Graph::GridGraph1<Value> CreateGrid(unsigned width, unsigned height, Gen::IGen<Value>* gen) {
            Graph::GridGraph1<Value> gg(width, height);

            // column
            for (auto row = 0u; row < height; row++)
                for (auto col = 1u; col < width; col++) {
                    Key2D key_from(col-1u,row);
                    Key2D key_to(col,row);
                    if( gen )
                    {
                        Value val = gen->Next();
                        gg.AddEdge(key_from, key_to, val, true);
                    }
                }

            // row
            for (auto col = 0u; col < width; col++)
                for (auto row = 1u; row < height; row++) {
                    Key2D key_from(col,row-1u);
                    Key2D key_to(col,row);
                    if( gen )
                    {
                        Value val = gen->Next();
                        gg.AddEdge(key_from, key_to, val);
                    }
                }

            return gg;
        }
    }
}

#endif //GRAPH_ITOPOLOGIES_H
