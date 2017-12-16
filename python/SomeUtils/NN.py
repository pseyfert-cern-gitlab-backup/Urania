from math import *


class Neuron:
    def __init__(self, weights = [], bias = 0):
        self.weights = weights
        self.bias = bias
        

    def __call__(self, input):
        x = 0
        for i in range(len(input)):
            x + self.w[i]*input[i]
        return x + self.bias

#class Layer

#class Network:
 #   def __init__
