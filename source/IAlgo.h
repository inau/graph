//
// Created by Ivan on 06-Aug-19.
//

#ifndef GRAPH_IALGO_H
#define GRAPH_IALGO_H

#include "IGraph.h"
#include "IAlgo.h"
#include <vector>
#include <set>

namespace Graph {
    namespace Algs {

        // Forward decl
        Tmpl_K
        class UnionFind;

        Tmpl_K_V
        class MinimumSpanningTree {
        protected:
            std::vector<IEdge1<Key, Value> *> mst;

        public:
            MinimumSpanningTree(IGraph1<Key, Value> *graph) {
                std::vector< IEdge1<Key, Value>* > sorted;
                //std::set<Key> connected;
                // read from graph
                sorted.resize(graph->GetSizeE());
                auto res = graph->GetEdges(sorted.data(), sorted.size());

                if (res != sorted.size()) {
                    int gg = 42;
                    return;
                }
                std::sort(sorted.begin(),
                          sorted.end(),
                          [](IEdge1<Key, Value>* lhs, IEdge1<Key, Value>* rhs)
                          {
                              bool res = false;
                              if(lhs && rhs)
                              {
                                  res = lhs->GetVal() < rhs->GetVal();
                              }
                              return res;
                          }
                );

                Graph::Algs::UnionFind<Key> uf;
                IEdge1<Key, Value> *e = nullptr;
                for (auto i = 0u; i < sorted.size(); i++)
                {
                    bool added = false;
                    e = sorted[i];

                    Key p0 = uf.Find(e->GetFrom());
                    Key p1 = uf.Find(e->GetTo());

                    if( p0 != p1 )
                    {
                        /*
                        if( connected.count(e->GetFrom()) == 0 )
                        {
                            connected.insert(e->GetFrom());
                            added = true;
                        }
                        if ( connected.count(e->GetTo()) == 0 )
                        {
                            connected.insert(e->GetTo());
                            added = true;
                        }
*/
                       // if(added)
                       // {
                            mst.push_back(e);
                            uf.Union(e->GetFrom(), e->GetTo());
                       // }
                    }
                    if (mst.size() >= graph->GetSizeV()) break;
                }
            }

            std::vector<IEdge1<Key, Value> *> Edges() { return mst; };
        };

        Tmpl_K
        class UnionFind {
        protected:
            struct UFInfo {
                int Rank = 1;
                Key Parent;
            };
            std::map<Key, UFInfo> vertices;

            bool KeyExists(Key k) { return vertices.count(k) > 0; }

            bool IsRoot(Key v) { return vertices[v].Parent == v; }

            Key FindRoot(Key v) {
                Key k = v;
                while (!IsRoot(k)) { k = vertices[k].Parent; }
                //compress
                //vertices[v].Parent = k;

                return k;
            }

            void AddVertex(Key k) { vertices[k].Parent = k; };

            void AttachToComponent(Key root, Key k) {
                vertices[k].Parent = root;
                vertices[root].Rank += vertices[k].Rank;
            }

        public:

            bool Union(Key v0, Key v1) {
                bool res = false;

                if (!KeyExists(v0)) AddVertex(v0);
                if (!KeyExists(v1)) AddVertex(v1);

                if (vertices[v0].Rank >= vertices[v1].Rank) {
                    // v1
                    Key key = FindRoot(v0);
                    AttachToComponent(key, v1);
                } else {
                    // v0
                    Key key = FindRoot(v1);
                    AttachToComponent(key, v0);
                }
                res = true;
                return res;
            }

            Key Find(Key v) {
                if (!KeyExists(v)) AddVertex(v);
                return FindRoot(v);
            }


        };
    }
}

#endif //GRAPH_IALGO_H
