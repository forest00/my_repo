#include "ga_test.h"
#include <iostream>
#include <ctime>

float rand0to1()
{
    return static_cast<float>(rand()) / RAND_MAX;
}

bool bernoulli(float probability)
{
    return probability > rand0to1();
}

float input(const char *caption)
{
    float buf = 0.0f;
    printf("%s", caption);
    scanf_s("%f", &buf);
    return buf;
}

std::vector<float> getCorrectOutput(float input)
{
    std::vector<float> result;
    result.push_back((input * 2.0) + 100.0f);
    result.push_back(input);
    result.push_back((input < 0.0f) * input);
    return result;
}

float calculateScoreSub(float value, float correctValue)
{
    return -abs(value - correctValue);
}

float calculateUnitScore(ga::Unit *unit)
{
    float score = 0.0f;
    for (auto i = -1000; i < 1000 + 1; i++)
    {
        float input = i / 2.0f;
        std::vector<float> correctOutput = getCorrectOutput(input);
        unit->setInput(0, input);
        unit->calculateOutput();
        score += calculateScoreSub(correctOutput[0], unit->getOutput(0));
        score += calculateScoreSub(correctOutput[1], unit->getOutput(1));
        score += calculateScoreSub(correctOutput[2], unit->getOutput(2));
    }
    return score;
}

void executeGA()
{
    constexpr int unitNum = 100;
    constexpr int generationMax = 200;
    constexpr float testInput = 100;
    ga::System gaSystem;
    ga::RandomInt gaRandom;
    std::array<ga::Unit *, unitNum> units;
    std::array<float, unitNum> scores;
    std::array<int, unitNum> ranking;
    std::vector<int> nodeNums;
    int generation = 0;
    //setup
    nodeNums.push_back(1);
    nodeNums.push_back(3);
    auto genome = new mlp::Genome(nodeNums);
    for (auto i = 0; i < unitNum; i++)
    {
        auto &unit = units[i];
        unit = new gaTest::Unit(genome);
        auto geneIndex = gaRandom.getRand(unit->getGeneLength());
        auto newGene = gaRandom.getRand30();
        unit->writeGene(geneIndex, newGene);
        unit->rewrittenGene();
    }
    delete genome;
    while (generation < generationMax)
    {
        //process
        for (auto i = 0; i < unitNum; i++)
        {
            auto &unit = units[i];
            scores[i] = calculateUnitScore(unit);
            ranking[i] = i;
        }
        //ranking
        for (auto i = 1; i < unitNum; i++)
        {
            auto j = i;
            while (j > 0)
            {
                auto scoreA = scores[ranking[j]];
                auto scoreB = scores[ranking[j - 1]];
                if (scoreA > scoreB)
                {
                    auto tmp = ranking[j];
                    ranking[j] = ranking[j - 1];
                    ranking[j - 1] = tmp;
                    j--;
                    continue;
                }
                break;
            }
        }
        //output
        std::cout << "generation = " << generation;
        std::cout << std::endl;
        std::cout << "top = ";
        std::cout << ranking.front();
        std::cout << ", ";
        std::cout << scores.front();
        std::cout << std::endl;
        std::cout << std::endl;
        //next generation
        generation++;
        for (auto i = 0; i < unitNum; i++)
        {
            if (i == ranking[0] || i == ranking[1])
            {
                continue;
            }
            auto rank1unit = units[ranking[0]];
            auto rank2unit = units[ranking[1]];
            auto &unit = units[i];
            delete unit;
            if (bernoulli(0.35f))
            {
                if (bernoulli(0.5f))
                {
                    unit = gaSystem.giveBirthMutant(rank1unit, gaRandom);
                }
                else
                {
                    unit = gaSystem.giveBirthMutant(rank1unit, rank2unit, gaRandom);
                }
            }
            else
            {
                if (bernoulli(0.5f))
                {
                    unit = gaSystem.giveBirthChild(rank1unit, gaRandom);
                }
                else
                {
                    unit = gaSystem.giveBirthChild(rank1unit, rank2unit, gaRandom);
                }
            }
        }
    }
    auto rank1unit = units[ranking[0]];
    rank1unit->setInput(0, testInput);
    rank1unit->calculateOutput();
    auto out0 = rank1unit->getOutput(0);
    auto out1 = rank1unit->getOutput(1);
    auto out2 = rank1unit->getOutput(2);
    std::cout << "out0 : ";
    std::cout << out0;
    std::cout << std::endl;
    std::cout << "out1 : ";
    std::cout << out1;
    std::cout << std::endl;
    std::cout << "out2 : ";
    std::cout << out2;
    std::cout << std::endl;
    //delete all
    for (auto i = 0; i < unitNum; i++)
    {
        auto &unit = units[i];
        delete unit;
        unit = nullptr;
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    //–{‘Ì
    executeGA();
    //ƒL[“ü—Í‘Ò‚¿
    std::cout << "press enter key to finish...";
    std::cout << std::endl;
    int getchar_return = getchar() + getchar();
    return 0;
}
