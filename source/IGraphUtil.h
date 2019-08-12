//
// Created by Ivan on 10-Aug-19.
//

#ifndef GRAPH_IGRAPHUTIL_H
#define GRAPH_IGRAPHUTIL_H

#include "IGraph.h"
#include "CGraph.h"
#include <Windows.h>
#include <iostream>

namespace Graph {
    namespace Util {
        struct RGBClr
        {
            long R, G, B;
        };
        RGBClr CLR[5]
                {
                        {0,   0,   0},
                        {255, 0,   0},
                        {0,   255, 0},
                        {0,   0,   255},
                        {255, 255, 255}
                };

        struct GCoord
        {
            const long int x;
            const long int y;

            GCoord(unsigned _x, unsigned _y) : x(_x), y(_y) {}
        };

        struct GRectangle
        {
            GCoord c0;
            GCoord c1;

            GRectangle(GCoord origin, unsigned w, unsigned h) : c0(origin.x, origin.y), c1(c0.x + w, c0.y + h) {}

            GRectangle(unsigned x, unsigned y, unsigned w, unsigned h) : c0(x, y), c1(c0.x + w, c0.y + h) {}
        };

        void drawRect(HDC &hdc, GRectangle &grect, unsigned clr)
        {
            if (clr >= 5) clr = 0;
            HBRUSH hBrush = CreateSolidBrush(RGB(CLR[clr].R, CLR[clr].G, CLR[clr].B));
            RECT rect = {grect.c0.x, grect.c0.y, grect.c1.x, grect.c1.y};
            ::FillRect(hdc, &rect, hBrush);
            DeleteObject(hBrush);
        }

        void drawLine(HDC &hdc, GCoord from, GCoord to, unsigned linewidth, const char *lbl = nullptr)
        {
            int dir = 0;
            if (from.x == to.x) dir = 1;
            if (from.y == to.y) dir = 2;
            long min_x = std::min(from.x, to.x);
            long min_y = std::min(from.y, to.y);
            unsigned long dist = 0u;
            switch (dir)
            {
                case 1:
                {
                    if (from.y < to.y) dist = to.y - from.y;
                    else dist = from.y - to.y;
                }
                    break;
                case 2:
                {
                    if (from.x < to.x) dist = to.x - from.x;
                    else dist = from.x - to.x;
                }
                    break;
            }

            if (dir != 0)
            {
                auto drawText = [&](GRectangle &grect, LPCSTR txt, int dir)
                {
                    HBRUSH hBrush = CreateSolidBrush(RGB(CLR[4].R, CLR[4].G, CLR[4].B));
                    long x_m = 0u;
                    long y_m = 0u;
                    if (dir == 1)
                    { y_m += 50u; }
                    if (dir == 2)
                    { x_m += 50u; }
                    RECT rect = {grect.c0.x + x_m, grect.c0.y + y_m, grect.c1.x, grect.c1.y};
                    ::DrawText(hdc, txt, -1, &rect, DT_LEFT);
                    DeleteObject(hBrush);
                };

                if (dir == 1)
                { // ver
                    GRectangle line(min_x, min_y, linewidth, dist);
                    drawRect(hdc, line, 2);
                }
                if (dir == 2)
                { // hor
                    GRectangle line(min_x, min_y, dist, linewidth);
                    drawRect(hdc, line, 3);
                }
                if (lbl)
                {
                    GRectangle line(min_x, min_y, dist, dist);
                    drawText(line, lbl, dir);
                }
            }
        }

        Tmpl_V
        void PrintEdgesGfx(HDC &hdc, std::vector<IEdge1<Graph::Key2D, Value> *> &edges, unsigned w, unsigned h)
        {

            unsigned vsize = 20u;
            unsigned cellsize = 100u;

            GRectangle Background(0, 0, (w) * cellsize + 2 * vsize, (h) * cellsize + 2 * vsize);
            drawRect(hdc, Background, 4);

            for (auto e : edges)
            {
                Graph::Key2D v0 = e->GetFrom();
                Graph::Key2D v1 = e->GetTo();
                GRectangle gv0(vsize + v0.GetCol() * cellsize, vsize + v0.GetRow() * cellsize, 2 * vsize, 2 * vsize);
                GRectangle gv1(vsize + v1.GetCol() * cellsize, vsize + v1.GetRow() * cellsize, 2 * vsize, 2 * vsize);
                drawRect(hdc, gv0, 1);
                drawRect(hdc, gv1, 1);

                GCoord line0(gv0.c0.x + vsize, gv0.c0.y + vsize);
                GCoord line1(gv1.c0.x + vsize, gv1.c0.y + vsize);
                std::string val_lbl = std::to_string(e->GetVal());
                drawLine(hdc, line0, line1, 10u, val_lbl.c_str());
//                std::cout << ToStr() << " -> " << ToStr() << " w: " << e->GetVal() << std::endl;
            }

        }

        Tmpl_V
        void PrintGridGfx(HDC &hdc, Graph::GridGraph1<Value> &gg)
        {
            std::vector<IEdge1<Graph::Key2D, Value> *> edges;
            edges.resize(gg.GetSizeE());
            auto n_edges = gg.GetEdges(edges.data(), edges.size());

            unsigned w = gg.GetWidth();
            unsigned h = gg.GetHeight();
            PrintEdgesGfx(hdc, edges, w, h);
        }

        Tmpl_V
        void PrintEdgesText(std::ostream &str, std::vector<IEdge1<Graph::Key2D, Value> *> &edges)
        {
            auto printKey = [](std::ostream &str, Graph::Key2D key)
            {
                str << "(" << key.GetCol() << ", " << key.GetRow() << ") ";
            };

            for (auto &e : edges)
            {
                if( !e) continue;
                str << std::endl;
                printKey(str, e->GetFrom());
                Value v = e->GetVal();
                str << " -- " << std::to_string(v) << " -- ";
                printKey(str, e->GetTo());
            }
        }
    }
}

#endif //GRAPH_IGRAPHUTIL_H
