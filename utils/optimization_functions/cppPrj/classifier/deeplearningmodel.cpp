#include "deeplearningmodel.h"


Tensor<float> DeepLearningModel::Predict(const Tensor<float> &input){
    // Current layer activation start with the "input"
    auto currLayerAct = input;

    // Iterate forward on the graph
    for (auto layer:m_layers){
        auto currLayer = m_layers(layer);

        // Skip the input layer
        if (typeid(*currLayer) == typeid(InputLayer)) continue;

        currLayerAct = currLayer->ForwardPropagation(currLayerAct);
    }

    // Return scores (Activation of the last layer, ie: Softmax)
    return currLayerAct;
}

float DeepLearningModel::Loss(const Tensor<float> &X, const Tensor<float> &Y){
    // Do Forward propagation
    auto scores = Predict(X);

    // Get loss and gradient of the loss w.r.t to the scores
    auto LossGrad = m_loss->GetLossAndGradients(scores, Y);
    auto dataLoss = get<0>(LossGrad);
    auto gradLoss = get<1>(LossGrad);

    /*
     * Do backprop to calculate the gradients of each layer w.r.t to the correct class
     * described on Y
    */

    return 0.0f;
}

void DeepLearningModel::InitWeights(){    
    // Iterate on all layers (C++11 for each, stuff)
    for (auto layer:m_layers){
        auto currLayer = m_layers(layer);
        auto layerInput = currLayer->GetInputLayer();
        // Skip the input layer
        if (layerInput == nullptr)
            continue;
        auto shapeInput = layerInput->GetActivationShape();
        std::cout << "Layer:" << layer << " input layer:" << layerInput->GetName() << endl;

        // Initialize weights only on layers that need it
        if (typeid(*currLayer) == typeid(FullyConnected)){
            cout << "Create FC" << endl;
        }
    }
}

