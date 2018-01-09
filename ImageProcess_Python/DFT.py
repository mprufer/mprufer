import numpy as np
import cmath as cm
import numpy as np
import sys
from numpy.random import rand

class DFT:
    def init_matrix(self):
        print("Hello")
        inMatrix = np.int_(rand(15,15)*256)
        print("--Input Matrix--")
        print(inMatrix)

        print("--FFT Matrix--")
        fftMatrix = DFT.forward_transform(self, inMatrix)
        print(fftMatrix)

        print("--Inverse Matrix--")
        inverse = DFT.inverse_transform(self, fftMatrix)
        print(inverse)

        print("--Magnitue of Inverse--")
        mag = DFT.magnitude(self, inverse)
        print(mag)

        print("--Cosine Transform--")
        cos = DFT.discrete_cosine_tranform(self, inMatrix)
        print(cos)

    def forward_transform(self, matrix):
        w,h=matrix.shape

        beta = [[0 for x in range(w)] for y in range(h)]

        for a in range(15):
            for b in range(15):
                asum = 0
                for i in range(15):
                    for j in range(15):
                        asum += matrix[i][j]*((np.cos(((2*np.pi)/15)*(a*i+b*j)))
                                             -(1j*np.sin(((2*np.pi)/15)*(a*i+b*j))))
                beta[a][b] = asum
        return beta

    def inverse_transform(self, matrix):

        beta = [[0 for x in range(15)] for y in range(15)]

        for i in range(15):
            for j in range (15):
                asum = 0
                for u in range(15):
                    for v in range(15):
                        asum+=matrix[u][v]*((np.cos((2*np.pi/15)*(u*i+v*j)))
                                            +(1j*np.sin((2*np.pi/15)*(u*i+v*j))))
                beta[i][j] = asum
        return beta


    def discrete_cosine_tranform(self, matrix):
        w, h = matrix.shape

        beta = [[0 for x in range(w)] for y in range(h)]

        for a in range(h):
            for b in range(w):
                asum = 0
                for i in range(h):
                    for j in range(w):
                        asum += matrix[i][j]*(np.cos(((2 * np.pi)/w)*(a*i+b*j)))
                beta[a][b] = asum

        return beta


    def magnitude(self, matrix):
        beta = [[0 for x in range(15)] for y in range(15)]
        for a in range(15):
            for b in range(15):
                beta[a][b] = np.absolute(matrix[a][b])
        return beta
#to run code
DFT.init_matrix(DFT)