from DependantLSystem import *
import random

class DependantRowOfTrees(DependantLSystem):

    def __init__(self):
        axiom = [Symbol('F',[500,0])]
        self.c = 1
        self.p = .3
        DependantLSystem.__init__(self,axiom,"Better Row Of Trees")
        self.maxpoints = 500
        self.q = self.c-self.p
        self.h = (self.p*self.q)**.5

        self.prob = 1

    def calculateMetric(self):
        n = len(self.state)
        points = self.state.count( Symbol('+') )
        # self.metric = self.maxpoints - points
        return points

    def updateMetric(self,neighbor_metrics):
        total_points = sum(neighbor_metrics)
        self.prob = 1 - total_points/500.0

    def substitute(self,symbol):
        if symbol == Symbol('F'):
            if(random.random() < self.prob):
                x,t = symbol.parameters
                if t == 0:
                    p = Symbol('F',[x * self.p,2])
                    h = Symbol('F',[x * self.h,1])
                    q = Symbol('F',[x * self.q,0])
                    plus = Symbol('+',[87])
                    minus = Symbol('-',[87])
                    return [p, plus, h ,minus, minus, h, plus ,q]
                else:
                    return [Symbol('F',[x,t-1])]
            else:
                return [symbol]
        else:
            return [symbol]

    def draw(self):
        actions = Visualize.basic_actions_parametric()
        V = Visualize(actions)
        V.draw(self.state)

if __name__ == '__main__':
    D1 = DependantRowOfTrees()
    D2 = DependantRowOfTrees()
    D3 = DependantRowOfTrees()
    G = LGroup([D1,D2,D3])

    for i in range(9):
        G.next()
        G.draw()
    #     D.next()
    #     print D.calculateMetric()
    #     D.updateMetric([])
    #     D.draw()
    #     wait = raw_input("PRESS ENTER TO CONTINUE")
