#include "ga_test.h"
#include <cassert>

namespace gaTest
{
    Unit::Unit(const mlp::Genome *_genome)
        : genome(nullptr)
        , mlp(nullptr)
    {
        genome = _genome->clone();
    }
    Unit::~Unit()
    {
        delete genome;
        delete mlp;
    }
    auto Unit::getGeneLength()const->int
    {
        return genome->getElementNum() - genome->getElement(0) - 1;
    }
    auto Unit::readGene(int geneIndex)const->int
    {
        return genome->getElement(geneIndex + genome->getElement(0) + 1);
    }
    auto Unit::writeGene(int geneIndex, int newGene)->void
    {
        genome->setElement(geneIndex + genome->getElement(0) + 1, newGene);
    }
    auto Unit::rewrittenGene()->void
    {
        delete mlp;
        mlp = new mlp::MultilayerPerceptron(genome);
    }
    auto Unit::clone()const->Unit *
    {
        return new Unit(genome);
    }
    auto Unit::calculateOutput()->void
    {
        mlp->calculateOutput();
    }
    auto Unit::getInputNum()const->int
    {
        auto layerIndex = 0;
        return mlp->getNodeNum(layerIndex);
    }
    auto Unit::getInput(int inputIndex)const->float
    {
        auto layerIndex = 0;
        return mlp->getBias(layerIndex, inputIndex);
    }
    auto Unit::setInput(int inputIndex, float newInput)->void
    {
        auto layerIndex = 0;
        mlp->setBias(layerIndex, inputIndex, newInput);
    }
    auto Unit::getOutputNum()const->int
    {
        auto layerIndex = mlp->getLayerNum() - 1;
        return mlp->getNodeNum(layerIndex);
    }
    auto Unit::getOutput(int outputIndex)const->float
    {
        auto layerIndex = mlp->getLayerNum() - 1;
        return mlp->getOutput(layerIndex, outputIndex);
    }
}
