#include "ga.h"
#include <cassert>

namespace ga
{
    InputField::InputField(int _elementNum)
        : elements(_elementNum)
    {

    }
    InputField::~InputField()
    {

    }
    auto InputField::getElementNum()const->int
    {
        return static_cast<int>(elements.size());
    }
    auto InputField::getElement(int elementIndex)const->float
    {
        return elements[elementIndex];
    }
    auto InputField::getElements()const->const std::vector<float> &
    {
        return elements;
    }
    auto InputField::setElement(int elementIndex, float newElement)->void
    {
        elements[elementIndex] = newElement;
    }
    //-----------------------------------------------------------------
    auto Unit::clone()const->Unit *
    {
        return nullptr;
    }
    //-----------------------------------------
    auto System::giveBirthChild(const Unit *a, RandomInt &random)->Unit *
    {
        assert(a != nullptr);
        auto child = a->clone();
        if (child == nullptr)
        {
            return nullptr;
        }
        auto geneLength = child->getGeneLength();
        //遺伝子書き換えを3回行う
        auto resource = 3;
        while (resource > 0)
        {
            auto geneIndex = random.getRand(geneLength);
            child->writeGene(geneIndex, random.getRand32());
            resource--;
        }
        child->rewrittenGene();
        return child;
    }
    auto System::giveBirthChild(const Unit *a, const Unit *b, RandomInt &random)->Unit *
    {
        assert(a != nullptr);
        assert(b != nullptr);
        auto child = a->clone();
        if (child == nullptr)
        {
            return nullptr;
        }
        auto geneLength = child->getGeneLength();
        //遺伝子配合を(遺伝子長 / 2)回行う
        auto resource = geneLength / 2;
        while (resource > 0)
        {
            auto geneIndex = random.getRand(geneLength);
            child->writeGene(geneIndex, b->readGene(geneIndex));
            resource--;
        }
        child->rewrittenGene();
        return child;
    }
    auto System::Mix(const Unit *a, const Unit *b)->Unit *
    {
        assert(a != nullptr);
        assert(b != nullptr);
        auto child = a->clone();
        if (child == nullptr)
        {
            return nullptr;
        }
        auto geneLength = child->getGeneLength();
        //遺伝子配合を行う
        for(auto i = 0 ; i < geneLength; i++)
        {
            auto geneIndex = i;
            auto geneA = a->readGene(geneIndex);
            auto geneB = b->readGene(geneIndex);
            auto childGene = (geneA & 0b10101010101010101010101010101010) | (geneB & 0b01010101010101010101010101010101);
            child->writeGene(geneIndex, childGene);
        }
        child->rewrittenGene();
        return child;
    }
    auto System::giveBirthMutant(const Unit * a, RandomInt &random)->Unit *
    {
        assert(a != nullptr);
        auto child = a->clone();
        if (child == nullptr)
        {
            return nullptr;
        }
        auto geneLength = child->getGeneLength();
        //遺伝子書き換えを100回行う
        auto resource = 100;
        while (resource > 0)
        {
            auto geneIndex = random.getRand(geneLength);
            child->writeGene(geneIndex, random.getRand32());
            resource--;
        }
        child->rewrittenGene();
        return child;
    }
    auto System::giveBirthMutant(const Unit * a, const Unit * b, RandomInt &random)->Unit *
    {
        assert(a != nullptr);
        assert(b != nullptr);
        auto child = a->clone();
        if (child == nullptr)
        {
            return nullptr;
        }
        auto geneLength = child->getGeneLength();
        //遺伝子配合を(遺伝子長 / 2)回行う
        auto resource = geneLength / 2;
        while (resource > 0)
        {
            auto geneIndex = random.getRand(geneLength);
            child->writeGene(geneIndex, b->readGene(geneIndex));
            resource--;
        }
        //遺伝子書き換えを更に3回行う
        resource = 3;
        while (resource > 0)
        {
            auto geneIndex = random.getRand(geneLength);
            child->writeGene(geneIndex, random.getRand32());
            resource--;
        }
        child->rewrittenGene();
        return child;
    }
    //-----------------------------------------
    RandomInt::RandomInt()
        : mt(seedGen())
    {

    }
    RandomInt::~RandomInt()
    {

    }
    auto RandomInt::getRand(int n)->int
    {
        if (n < 0)
        {
            return 0;
        }
        std::uniform_int_distribution<int> d(0, n - 1);
        return d(mt);
    }
    auto RandomInt::getRand32()->int
    {
        return mt();
    }
    auto RandomInt::getRand31()->int
    {
        return mt() & 0b01111111111111111111111111111111;
    }
    auto RandomInt::getRand30()->int
    {
        return mt() & 0b00111111111111111111111111111111;
    }
    std::random_device RandomInt::seedGen;
}
