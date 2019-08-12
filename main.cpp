//
// Created by Ivan on 25-Jun-18.
//


#include <stdio.h>
#include <iostream>
#include "source/CVertex.h"
#include "source/CEdge.h"
#include "source/CGraph.h"
#include "source/ITopologies.h"
#include "source/IAlgo.h"
#include "source/IGraphUtil.h"

//#include <string>
//#include <sstream>
#include <atomic>
#include <thread>

int main(int argc, char** argv) {
    unsigned w = 0u, h = 0u, s = 0u;

    std::cout << "[Width(X)] [Height(Y)] [Seed(int)]\n";
    std::string read;
    read.resize('\n', 128u);
    std::cin.read(&read[0], read.size());
    int r_n = sscanf(read.data(),"%d %d %d",&w,&h,&s);

    if( r_n != 3) {
        std::cout << "Unable to read arguments";
        exit(2);
    }
    Gen::RandomGen<int> rgen(s, 9,49);
 //   Gen::ConstGen<int> rgen(42);
    Graph::GridGraph1<int> gg = Graph::Topo::CreateGrid<int>(w,h, &rgen);

    Graph::Algs::MinimumSpanningTree<Graph::Key2D, int> MST(&gg);
    auto edges_mst = MST.Edges();

    std::vector<IEdge1<Graph::Key2D, int>*> edges;
    edges.resize(gg.GetSizeE());
    auto n_edges = gg.GetEdges(edges.data(), edges.size());

    HDC hdc = ::GetDC(0);

    struct Action
    {
        std::string label;
        std::atomic<boolean> flag;
        char chars[2];
        std::function<void(void)> apply;

        Action(std::string str, bool _flag, char c0, char c1, std::function<void(void)> f) : label(str), flag(_flag), apply(f) { chars[0] = c0, chars[1] = c1;}
        std::string Str() { return label + "( " + chars[0] + ")\n"; }
        void Apply()
        {
            if( flag.load() )
            {
                apply();
                flag.store(false);
            }
        }
    };

    Action Quit("Quit", false, 'q','Q', [](){} );
    std::vector<std::unique_ptr<Action>> actions;
    actions.push_back( std::make_unique<Action>("Redraw Graph", false, 'c','C',
                    [&hdc,&gg, &edges](){ Graph::Util::PrintEdgesGfx(hdc, edges, gg.GetWidth(), gg.GetHeight()); }));
    actions.push_back( std::make_unique<Action>("Redraw Graph MST", false, 'm','M',
                    [&hdc,&gg, &edges_mst](){ Graph::Util::PrintEdgesGfx(hdc, edges_mst, gg.GetWidth(), gg.GetHeight()); }));
    actions.push_back( std::make_unique<Action>("Print Edges Txt", false, 't','T',
                   [&edges](){ Graph::Util::PrintEdgesText(std::cout, edges); }));
    actions.push_back( std::make_unique<Action>("Print Edges Mst Txt", false, 'n','N',
                                                [&edges_mst](){ Graph::Util::PrintEdgesText(std::cout, edges_mst); }));

    auto thread = [&]()
    {

        while( !Quit.flag.load() )
        {
            for(auto& a : actions)
            {
                a->Apply();
            }
        }
    };

    std::thread t(thread);

    while( !Quit.flag.load() )
    {
        //system("cls");
        std::cout << Quit.Str();
        for(auto& a : actions)
        {
            std::cout << " > " << a->Str();
        }

        char c = std::cin.get();
        if( c == Quit.chars[0] || c == Quit.chars[1] ) Quit.flag.store(true);
        for(auto& a : actions)
        {
            if( c == a->chars[0] || c == a->chars[1] ) a->flag.store(true);
        }
    }
    t.join();
    ::ReleaseDC(0, hdc);

    return 0;
}
