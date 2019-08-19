//data:2019/08/15
//auther:forest00
#pragma once
#include <random>

namespace ga//Genetic algorithm
{
    class InputField;
    class Unit;
    class System;
    class RandomInt;

    class InputField
    {
    public:
        InputField(const InputField &) = delete;
        InputField(int _elementNum);
        ~InputField();
        virtual auto getElementNum()const->int;
        virtual auto getElement(int elementIndex)const->float;
        virtual auto getElements()const->const std::vector<float> &;
        virtual auto setElement(int elementIndex, float newElement)->void;
    protected:
        std::vector<float> elements;
    };

    class Unit
    {
    public:
        virtual auto getGeneLength()const->int = 0;
        virtual auto readGene(int geneIndex)const->int = 0;
        virtual auto writeGene(int geneIndex, int newGene)->void = 0;
        virtual auto rewrittenGene()->void = 0;
        virtual auto clone()const->Unit *;
        virtual auto calculateOutput()->void = 0;
        virtual auto getInputNum()const->int = 0;
        virtual auto getInput(int inputIndex)const->float = 0;
        virtual auto setInput(int inputIndex, float newInput)->void = 0;
        virtual auto getOutputNum()const->int = 0;
        virtual auto getOutput(int outputIndex)const->float = 0;
    };

    class System
    {
    public:
        static auto giveBirthChild(const Unit *a, RandomInt &random)->Unit *;
        static auto giveBirthChild(const Unit *a, const Unit *b, RandomInt &random)->Unit *;
        static auto Mix(const Unit *a, const Unit *b)->Unit *;
        static auto giveBirthMutant(const Unit *a, RandomInt &random)->Unit *;
        static auto giveBirthMutant(const Unit *a, const Unit *b, RandomInt &random)->Unit *;
    };

    class RandomInt
    {
    public:
        RandomInt();
        ~RandomInt();
        //Returns a random number between 0 and (n - 1)
        //Return 0 if n is negative
        auto getRand(int n)->int;
        //Returns a 32-bit random number
        auto getRand32()->int;
        //Returns a 31-bit random number
        auto getRand31()->int;
        //Returns a 30-bit random number
        auto getRand30()->int;
    protected:
        static std::random_device seedGen;
        std::mt19937 mt;
    };
}
