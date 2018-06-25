//
// Created by Ivan on 25-Jun-18.
//


#include <iostream>
#include "library.h"

int main(int argc, char** argv) {
    Graph::Graph<int> g(9);
    Graph::GridGraph<int> g2(3,3);

    std::cout << g.GraphSize() << std::endl;
    std::cout << g2.GraphSize() << std::endl;

    for(int y = 0; y < g2.RowSize() ; y++) {
        for(int x = 0; x < g2.ColSize() ; x++) {
            if( y < g2.RowSize()-1 )
                g2.AddEdgeTo(x, y, x, y+1);
            if(x == g2.ColSize()-1) continue;
                g2.AddEdgeTo(x, y, x+1, y);
        }
    }

    for(int i = 0; i < g2.GraphSize() ; i++) {
        std::cout << g2.GetVertex(i)->GetAdjacentVertices().size() << " ";
    }

    /*******************************************
     *
     *******************************************/

    return 0;
}
