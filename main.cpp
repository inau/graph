//
// Created by Ivan on 25-Jun-18.
//


#include <iostream>
#include "source/CVertex.h"
#include "source/CEdge.h"
#include "source/CGraph.h"
#include "source/ITopologies.h"
#include "source/IAlgo.h"
#include "source/IGraphUtil.h"

#include <string>
#include <sstream>
#include <atomic>
#include <c++/thread>

struct s
{
    char* c;
};

std::string ToStr(const Graph::Key2D& k)
{
    std::stringstream ss;
    ss << "(" << k.GetCol() << ", " << k.GetRow() << ")";
    return ss.str();
}

int main(int argc, char** argv) {
    Gen::RandomGen<int> rgen(12, 1,6);
    Graph::GridGraph1<int> gg = Graph::Topo::CreateGrid<int>(3,2, &rgen);

    std::atomic<boolean> running;
    running.store(true);

    auto thread = [&running, &gg]()
    {
        Graph::Algs::MinimumSpanningTree<Graph::Key2D, int> MST(&gg);

        auto edges = MST.Edges();

        HDC screenDC = ::GetDC(0);
        while( running.load() )
        {
            Graph::Util::PrintEdgesGfx(screenDC, edges, gg.GetWidth(), gg.GetHeight());
            Sleep(10000);
        }
        ::ReleaseDC(0, screenDC);
    };

    std::thread t(thread);



    /*
    Graph::Algs::MinimumSpanningTree<Graph::Key2D, int> MST(&gg);

    std::vector<IEdge1<Graph::Key2D, int>*> edges;
    edges.resize(gg.GetSizeE());
    auto n_edges = gg.GetEdges(edges.data(), edges.size());

    for(auto e : edges)
    {
        std::cout << ToStr(e->GetFrom()) << " -> " << ToStr(e->GetTo()) << " w: " << e->GetVal() << std::endl;
    }



//    auto mst = Graph::minimum_spanning_tree(g);
/*
    for (auto it = mst.begin(); it != mst.end(); ++it) {
        std::cout << "(" << it.operator->()->vertex_from << ", " << it.operator->()->vertex_to << ") ";
    }
*/
    /*******************************************
     *
     *******************************************/

    std::cout << "Press any key to exit";
    std::cin.get();
    running.store(false);
    t.join();

    return 0;
}
