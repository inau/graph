//
// Created by Ivan on 09-Aug-19.
//

#ifndef GRAPH_IVALUEGENERATORS_H
#define GRAPH_IVALUEGENERATORS_H

#include "IGraph.h"
#include "CGraph.h"
#include <random>

namespace Graph
{
    namespace Gen
    {
        Tmpl_V
        class IGen
        {
        public:
            virtual Value Next() = 0;
        };

        Tmpl_V
        class RandomGen : public IGen<Value>
        {
        protected:
            std::mt19937 Gen;
            std::uniform_int_distribution<Value> Distr;
        public:
            RandomGen(unsigned Seed, unsigned lo, unsigned hi) : Gen(Seed), Distr(lo,hi) {};
            Value Next()
            {
                Value v = Distr(Gen);
                return v;
            };
        };

        Tmpl_V
        class ConstGen : public IGen<Value>
        {
        protected:
            Value val;
        public:
            ConstGen(Value v) : val(v) {};
            Value Next()
            {
                return val;
            };
        };

        Tmpl_V
        class Key2DGen : public IGen<Value>
        {
        protected:
            std::function<Value(Graph::Key2D)> m_f;

        public:
            Key2DGen(std::function<Value(Graph::Key2D)> f) : m_f(f) {};
            void SetInput(Graph::Key2D& k);
            Value Next(Graph::Key2D& k);
        };
    }
}

#endif //GRAPH_IVALUEGENERATORS_H
