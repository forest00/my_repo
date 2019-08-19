//data:2019/08/15
//auther:forest00
#pragma once
#include "ga.h"
#include "mlp.h"

namespace gaTest
{
    class Unit;

    class Unit : public ga::Unit
    {
    public:
        Unit(const Unit &) = delete;
        Unit(const mlp::Genome *_genome);
        ~Unit();
        virtual auto getGeneLength()const->int override;
        virtual auto readGene(int geneIndex)const->int override;
        virtual auto writeGene(int geneIndex, int newGene)->void override;
        virtual auto rewrittenGene()->void override;
        virtual auto clone()const->Unit *override;
        virtual auto calculateOutput()->void override;
        virtual auto getInputNum()const->int override;
        virtual auto getInput(int inputIndex)const->float override;
        virtual auto setInput(int inputIndex, float newInput)->void override;
        virtual auto getOutputNum()const->int override;
        virtual auto getOutput(int outputIndex)const->float override;
    public:
        mlp::Genome *genome;
        mlp::MultilayerPerceptron *mlp;
    };
}
