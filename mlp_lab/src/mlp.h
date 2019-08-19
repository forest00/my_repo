//data:2019/08/10
//auther:forest00
#pragma once
#include <array>
#include <vector>

namespace mlp//Multilayer perceptron
{
    static_assert(sizeof(int) == 4, "Environment is invalid!");
    static_assert(sizeof(int) == sizeof(float), "Environment is invalid!");
    class ActivationFunctionID;
    class Node;
    class MultilayerPerceptron;
    class Genome;

    //活性化関数ID
    class ActivationFunctionID
    {
    public:
        //static constexpr int identity = 0;//f(x) = x
        //static constexpr int step = 1;//f(x) = 1 (x > 0), 0 (otherwise)
        //static constexpr int sigmoid = 2;//f(x) = 1 / (1 + exp(-x))
        //static constexpr int relu = 3;//f(x) = max(x, 0)
        static constexpr int elementNum = 4;
    public:
        ActivationFunctionID();
        explicit ActivationFunctionID(int _value);//value is 0-3
        virtual auto getName()const->const std::string &;
        virtual auto getDescription()const->const std::string &;
        virtual auto getFunction()const->float(*)(float);
        virtual auto getValue()const->int;
    protected:
        static std::array<std::string, elementNum> names;
        static std::array<std::string, elementNum> descriptions;
        static std::array<float(*)(float), elementNum> functions;
        int value;
    };

    //ノード
    class Node
    {
    public:
        Node(const Node &) = delete;
        Node(std::vector<mlp::Node *> *_inputLayer);
        ~Node();
        virtual auto calculateOutput(const std::vector<mlp::Node *> *inputLayer)->void;
        virtual auto getWeightNum()const->int;
        virtual auto getWeight(int weightIndex)const->float;
        virtual auto getBias()const->float;
        virtual auto getFunctionID()const->ActivationFunctionID;
        virtual auto getOutput()const->float;
        virtual auto setWeight(int weightIndex, float newWeight)->void;
        virtual auto setBias(float newBias)->void;
        virtual auto setFunctionID(ActivationFunctionID newFunctionID)->void;
    protected:
        std::vector<float> weights;
        float bias;
        ActivationFunctionID functionID;
        float output;
    };

    //一つの入力層と複数の隠れ層と一つの出力層を持っている
    //隠れ層の数は{レイヤーの数-2}
    //このクラスのインスタンスが一個あれば一体分のネットワークになる
    class MultilayerPerceptron
    {
    public:
        MultilayerPerceptron(const MultilayerPerceptron &) = delete;
        MultilayerPerceptron(const std::vector<int> &_nodeNums);
        MultilayerPerceptron(const Genome *_genome);
        ~MultilayerPerceptron();
        virtual auto calculateOutput()->void;
        virtual auto getLayerNum()const->int;
        virtual auto getNodeNum(int layerIndex)const->int;
        virtual auto getWeightNum(int layerIndex)const->int;
        virtual auto getWeight(int layerIndex, int nodeIndex, int weightIndex)const->float;
        virtual auto getBias(int layerIndex, int nodeIndex)const->float;
        virtual auto getFunctionID(int layerIndex, int nodeIndex)const->ActivationFunctionID;
        virtual auto getOutput(int layerIndex, int nodeIndex)const->float;
        virtual auto setWeight(int layerIndex, int nodeIndex, int weightIndex, float newWeight)->void;
        virtual auto setBias(int layerIndex, int nodeIndex, float newBias)->void;
        virtual auto setFunctionID(int layerIndex, int nodeIndex, ActivationFunctionID newFunctionID)->void;
    protected:
        std::vector<std::vector<Node *>> layers;
    };

    //NeuralNetworkクラスの構成情報
    //名前はいろいろ考えたけど、短いからこれにした
    //ネットワークの情報を全部バイナリ列にする
    //デザインは以下の通り
    //最初の1要素 : 層の数n
    //次のn要素 : i層目のノード数x[i]
    //次の(x[i - 1] + 2) * x[i] : i層目の各ノードの重みとバイアスと活性化関数ID(ただし、iは1以上)
    //intとfloatが同じバイト数じゃないと機能しない
    class Genome
    {
    public:
        Genome(const Genome &) = delete;
        Genome(const Genome *_genome);
        Genome(const MultilayerPerceptron *_mlp);
        Genome(const std::vector<int> &_nodeNums);
        ~Genome();
        virtual auto getElementNum()const->int;
        virtual auto getElement(int elementIndex)const->int;
        virtual auto getElements()const->const std::vector<int> &;
        virtual auto setElement(int elementIndex, int newElement)->void;
        virtual auto clone()const->Genome *;
    protected:
        std::vector<int> elements;
    };
}
