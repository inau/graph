//
// Created by Ivan on 25-Jun-18.
//


#include <iostream>
#include "library.h"

int main(int argc, char** argv) {
    Graph::GridGraph<int> g(3,3);
    Graph::GridGraph<int> g2(3,3);

    std::cout << g.GraphSize() << std::endl;
   // std::cout << g2.GraphSize() << std::endl;

    for(int y = 0; y < g2.RowSize() ; y++) {
        for(int x = 0; x < g2.ColSize() ; x++) {
            if( y < g2.RowSize()-1 ) {
                g.AddEdge(x, y, x, y+1, 1, true);
                g2.AddEdge(x, y, x, y+1, 1);
            }

            if(x == g2.ColSize()-1) continue;
            g.AddEdge(x, y, x+1, y, 1, true);
            g2.AddEdge(x, y, x+1, y, 1);
        }
    }

    Graph::PrintGraph(g);
    //Graph::PrintGraph(g2);

    auto mst = Graph::minimum_spanning_tree(g);

    for (auto it = mst.begin(); it != mst.end(); ++it) {
        std::cout << "(" << it.operator->()->vertex_from << ", " << it.operator->()->vertex_to << ") ";
    }

    /*******************************************
     *
     *******************************************/

    return 0;
}
