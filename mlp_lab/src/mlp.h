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

    //�������֐�ID
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

    //�m�[�h
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

    //��̓��͑w�ƕ����̉B��w�ƈ�̏o�͑w�������Ă���
    //�B��w�̐���{���C���[�̐�-2}
    //���̃N���X�̃C���X�^���X�������Έ�̕��̃l�b�g���[�N�ɂȂ�
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

    //NeuralNetwork�N���X�̍\�����
    //���O�͂��낢��l�������ǁA�Z�����炱��ɂ���
    //�l�b�g���[�N�̏���S���o�C�i����ɂ���
    //�f�U�C���͈ȉ��̒ʂ�
    //�ŏ���1�v�f : �w�̐�n
    //����n�v�f : i�w�ڂ̃m�[�h��x[i]
    //����(x[i - 1] + 2) * x[i] : i�w�ڂ̊e�m�[�h�̏d�݂ƃo�C�A�X�Ɗ������֐�ID(�������Ai��1�ȏ�)
    //int��float�������o�C�g������Ȃ��Ƌ@�\���Ȃ�
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
