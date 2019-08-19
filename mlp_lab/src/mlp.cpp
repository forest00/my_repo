#include "mlp.h"
#include <cassert>

//local functions
namespace
{
    float f0(float x)
    {
        return x;
    }
    float f1(float x)
    {
        return static_cast<float>(x > 0);
    }
    float f2(float x)
    {
        return 1.0f / (1.0f + exp(-x));
    }
    float f3(float x)
    {
        return std::max(x, 0.0f);
    }
    std::vector<mlp::Node *> createLayer(std::vector<mlp::Node *> *prevLayer, int nodeNum)
    {
        assert(nodeNum >= 1);
        std::vector<mlp::Node *> layer(nodeNum);
        for (auto &node : layer)
        {
            node = new mlp::Node(prevLayer);
        }
        return layer;
    }
}

namespace mlp
{
    //------------------------------------------------------------------------------
    ActivationFunctionID::ActivationFunctionID()
        : value(0)
    {

    }
    ActivationFunctionID::ActivationFunctionID(int _value)
        : value(_value)
    {
        assert(value >= 0);
        assert(value < elementNum);
    }
    auto ActivationFunctionID::getName()const->const std::string &
    {
        return names[getValue()];
    }
    auto ActivationFunctionID::getDescription()const->const std::string &
    {
        return descriptions[getValue()];
    }
    auto ActivationFunctionID::getFunction()const->float(*)(float)
    {
        return functions[getValue()];
    }
    auto ActivationFunctionID::getValue()const->int
    {
        return value;
    }
    std::array<std::string, ActivationFunctionID::elementNum> ActivationFunctionID::names = {
        "Identity",
        "Step",
        "Sigmoid",
        "ReLU"
    };
    std::array<std::string, ActivationFunctionID::elementNum> ActivationFunctionID::descriptions = {
        "f(x) = x",
        "f(x) = 1 (x > 0), 0 (otherwise)",
        "f(x) = 1 / (1 + exp(-x))",
        "f(x) = max(x, 0)"
    };
    std::array<float(*)(float), ActivationFunctionID::elementNum> ActivationFunctionID::functions = {
        f0,
        f1,
        f2,
        f3
    };
    //------------------------------------------------------------------------------
    Node::Node(std::vector<mlp::Node *> *_inputLayer)
        : weights()
        , bias()
        , functionID()
        , output()
    {
        if (_inputLayer == nullptr)
        {
            return;
        }
        weights.resize(_inputLayer->size(), 1.0f);
    }
    Node::~Node()
    {
        weights.clear();
        weights.shrink_to_fit();
    }
    auto Node::calculateOutput(const std::vector<mlp::Node *> *inputLayer)->void
    {
        auto sum = 0.0f;
        auto iEnd = getWeightNum();
        for (auto i = 0; i < iEnd; i++)
        {
            auto inputNode = (*inputLayer)[i];
            auto inputValue = inputNode->getOutput();
            auto weight = getWeight(i);
            sum += inputValue * weight;
        }
        sum += getBias();
        auto function = functionID.getFunction();
        output = function(sum);
    }
    auto Node::getWeightNum()const->int
    {
        return static_cast<int>(weights.size());
    }
    auto Node::getWeight(int weightIndex)const->float
    {
        assert(weightIndex >= 0);
        assert(weightIndex < getWeightNum());
        return weights[weightIndex];
    }
    auto Node::getBias()const->float
    {
        return bias;
    }
    auto Node::getFunctionID()const->ActivationFunctionID
    {
        return functionID;
    }
    auto Node::getOutput()const->float
    {
        return output;
    }
    auto Node::setWeight(int weightIndex, float newWeight)->void
    {
        assert(weightIndex >= 0);
        assert(weightIndex < getWeightNum());
        weights[weightIndex] = newWeight;
    }
    auto Node::setBias(float newBias)->void
    {
        bias = newBias;
    }
    auto Node::setFunctionID(ActivationFunctionID newFunctionID)->void
    {
        functionID = newFunctionID;
    }
    //------------------------------------------------------------------------------
    MultilayerPerceptron::MultilayerPerceptron(const std::vector<int> &_nodeNums)
        : layers()
    {
        assert(_nodeNums.size() >= 2);
        auto layerNum = static_cast<int>(_nodeNums.size());
        auto inputNodeNum = _nodeNums.front();
        auto lastLayer = &layers.back();
        auto hiddenLayerNum = layerNum - 2;
        layers.reserve(layerNum);
        layers.push_back(createLayer(nullptr, inputNodeNum));
        for (auto i = 0; i < hiddenLayerNum; i++)
        {
            auto hiddenNodeNum = _nodeNums[i + 1];
            layers.push_back(createLayer(lastLayer, hiddenNodeNum));
            lastLayer = &layers.back();
        }
        auto outputNodeNum = _nodeNums.back();
        layers.push_back(createLayer(lastLayer, outputNodeNum));
    }
    MultilayerPerceptron::MultilayerPerceptron(const Genome *_genome)
        : layers()
    {
        assert(_genome != nullptr);
        auto &genome = *_genome;
        auto layerNum = genome.getElement(0);
        auto lastLayer = (decltype(layers)::value_type *)(nullptr);
        auto current = layerNum + 1;
        for (auto i = 0; i < layerNum; i++)
        {
            auto nodeNum = genome.getElement(i + 1);
            layers.push_back(createLayer(lastLayer, nodeNum));
            lastLayer = &layers.back();
            if (i == 0)
            {
                continue;
            }
            auto weightNum = genome.getElement(i);
            for (auto j = 0; j < nodeNum; j++)
            {
                auto node = (*lastLayer)[j];
                for (auto k = 0; k < weightNum; k++)
                {
                    auto weightSource = genome.getElement(current++);
                    node->setWeight(k, *(reinterpret_cast<float *>(&weightSource)));
                }
                auto biasSource = genome.getElement(current++);
                auto functionIDSource = genome.getElement(current++);
                node->setBias(*(reinterpret_cast<float *>(&biasSource)));
                node->setFunctionID(ActivationFunctionID(abs(functionIDSource % ActivationFunctionID::elementNum)));
            }
        }
    }
    MultilayerPerceptron::~MultilayerPerceptron()
    {
        for (auto &layer : layers)
        {
            for (auto &node : layer)
            {
                delete node;
                node = nullptr;
            }
        }
        layers.clear();
        layers.shrink_to_fit();
    }
    auto MultilayerPerceptron::calculateOutput()->void
    {
        auto prevLayer = (decltype(layers)::value_type *)(nullptr);
        for (auto &layer : layers)
        {
            for (auto &node : layer)
            {
                node->calculateOutput(prevLayer);
            }
            prevLayer = &layer;
        }
    }
    auto MultilayerPerceptron::getLayerNum()const->int
    {
        return static_cast<int>(layers.size());
    }
    auto MultilayerPerceptron::getNodeNum(int layerIndex)const->int
    {
        assert(layerIndex >= 0);
        assert(layerIndex < getLayerNum());
        auto &layer = layers[layerIndex];
        return static_cast<int>(layer.size());
    }
    auto MultilayerPerceptron::getWeightNum(int layerIndex)const->int
    {
        assert(layerIndex >= 0);
        assert(layerIndex < getLayerNum());
        if (layerIndex == 0)
        {
            return 0;
        }
        auto &layer = layers[layerIndex - 1];
        return static_cast<int>(layer.size());
    }
    auto MultilayerPerceptron::getWeight(int layerIndex, int nodeIndex, int weightIndex)const->float
    {
        assert(layerIndex >= 0);
        assert(layerIndex < getLayerNum());
        assert(nodeIndex >= 0);
        assert(nodeIndex < getNodeNum(layerIndex));
        auto &layer = layers[layerIndex];
        auto node = layer[nodeIndex];
        return node->getWeight(weightIndex);
    }
    auto MultilayerPerceptron::getBias(int layerIndex, int nodeIndex)const->float
    {
        assert(layerIndex >= 0);
        assert(layerIndex < getLayerNum());
        auto &layer = layers[layerIndex];
        auto node = layer[nodeIndex];
        return node->getBias();
    }
    auto MultilayerPerceptron::getFunctionID(int layerIndex, int nodeIndex)const->ActivationFunctionID
    {
        assert(layerIndex >= 0);
        assert(layerIndex < getLayerNum());
        assert(nodeIndex >= 0);
        assert(nodeIndex < getNodeNum(layerIndex));
        auto &layer = layers[layerIndex];
        auto node = layer[nodeIndex];
        return node->getFunctionID();
    }
    auto MultilayerPerceptron::getOutput(int layerIndex, int nodeIndex)const->float
    {
        assert(layerIndex >= 0);
        assert(layerIndex < getLayerNum());
        assert(nodeIndex >= 0);
        assert(nodeIndex < getNodeNum(layerIndex));
        auto &layer = layers[layerIndex];
        auto node = layer[nodeIndex];
        return node->getOutput();
    }
    auto MultilayerPerceptron::setWeight(int layerIndex, int nodeIndex, int weightIndex, float newWeight)->void
    {
        assert(layerIndex >= 0);
        assert(layerIndex < getLayerNum());
        assert(nodeIndex >= 0);
        assert(nodeIndex < getNodeNum(layerIndex));
        auto &layer = layers[layerIndex];
        auto node = layer[nodeIndex];
        node->setWeight(weightIndex, newWeight);
    }
    auto MultilayerPerceptron::setBias(int layerIndex, int nodeIndex, float newBias)->void
    {
        assert(layerIndex >= 0);
        assert(layerIndex < getLayerNum());
        assert(nodeIndex >= 0);
        assert(nodeIndex < getNodeNum(layerIndex));
        auto &layer = layers[layerIndex];
        auto node = layer[nodeIndex];
        node->setBias(newBias);
    }
    auto MultilayerPerceptron::setFunctionID(int layerIndex, int nodeIndex, ActivationFunctionID newFunctionID)->void
    {
        assert(layerIndex >= 1);
        assert(layerIndex < getLayerNum());
        assert(nodeIndex >= 0);
        assert(nodeIndex < getNodeNum(layerIndex));
        auto &layer = layers[layerIndex];
        auto node = layer[nodeIndex];
        node->setFunctionID(newFunctionID);
    }
    //------------------------------------------------------------------------------
    Genome::Genome(const Genome *_genome)
        : elements(_genome->elements)
    {

    }
    Genome::Genome(const MultilayerPerceptron *_mlp)
        : elements()
    {
        assert(_mlp != nullptr);
        auto &mlp = *_mlp;
        auto layerNum = mlp.getLayerNum();
        elements.push_back(layerNum);
        for (auto i = 0; i < layerNum; i++)
        {
            auto nodeNum = mlp.getNodeNum(i);
            elements.push_back(nodeNum);
        }
        for (auto i = 1; i < layerNum; i++)
        {
            auto weightNum = mlp.getWeightNum(i);
            auto nodeNum = mlp.getNodeNum(i);
            for (auto j = 0; j < nodeNum; j++)
            {
                for (auto k = 0; k < weightNum; k++)
                {
                    auto weight = mlp.getWeight(i, j, k);
                    elements.push_back(*(reinterpret_cast<int *>(&weight)));
                }
                auto bias = mlp.getBias(i, j);
                elements.push_back(*(reinterpret_cast<int *>(&bias)));
                auto functionID = mlp.getFunctionID(i, j);
                elements.push_back(functionID.getValue());
            }
        }
    }
    Genome::Genome(const std::vector<int> &_nodeNums)
        : elements()
    {
        assert(_nodeNums.size() >= 2);
        auto layerNum = static_cast<int>(_nodeNums.size());
        elements.push_back(layerNum);
        for (auto i = 0; i < layerNum; i++)
        {
            auto nodeNum = _nodeNums[i];
            elements.push_back(nodeNum);
        }
        for (auto i = 1; i < layerNum; i++)
        {
            auto weightNum = _nodeNums[i - 1];
            auto nodeNum = _nodeNums[i];
            for (auto j = 0; j < nodeNum; j++)
            {
                for (auto k = 0; k < weightNum; k++)
                {
                    auto weight = 1.0f;
                    elements.push_back(*(reinterpret_cast<int *>(&weight)));
                }
                auto bias = 0.0f;
                elements.push_back(*(reinterpret_cast<int *>(&bias)));
                auto functionID = ActivationFunctionID(0);
                elements.push_back(functionID.getValue());
            }
        }
    }
    Genome::~Genome()
    {
        elements.clear();
        elements.shrink_to_fit();
    }
    auto Genome::getElementNum()const->int
    {
        return static_cast<int>(elements.size());
    }
    auto Genome::getElement(int elementIndex)const->int
    {
        assert(elementIndex >= 0);
        assert(elementIndex < getElementNum());
        return elements[elementIndex];
    }
    auto Genome::getElements()const->const std::vector<int> &
    {
        return elements;
    }
    auto Genome::setElement(int elementIndex, int newElement)->void
    {
        assert(elementIndex >= 0);
        assert(elementIndex < getElementNum());
        elements[elementIndex] = newElement;
    }
    auto Genome::clone()const->Genome *
    {
        return new Genome(this);
    }
    //------------------------------------------------------------------------------
}
