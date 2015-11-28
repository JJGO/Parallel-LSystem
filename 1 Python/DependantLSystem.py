from LSystem import *


class DependantLSystem(ParametricLSystem):

    def __init__(self,axiom,production,name = "Dependant LSystem"):
        ParametricLSystem.__init__(self,axiom,production,name)
        self.metric = 0

    def calculateMetric(self):
        raise NotImplementedError("Needs to be implemented by the subclass")

    def updateMetric(self,neighbor_metrics):
        raise NotImplementedError("Needs to be implemented by the subclass")

    def __str__(self):
        output = ""
        #Adds the title
        output += "The Parametric Lindenmayer System " +str(self.name) +" is composed by:\n"
        
        #The axiom and the current string
        output += "The axiom is: " + str(self.axiom) +"\n"
        output += "The current string after " + str(self.iteration) + " iterations is: \n" + self.state + "\n"

        return output



class LGroup(object):

    def __init__(self,lsystems=[]):
        self.lsystems = lsystems

    def add_LSystem(self,lystem):
        self.lsystems.append(lsystem)

    def reset(self):
        self.state = self.axiom
        self.iteration = 0

    def iterate(self,n):
        """
        Assumes n is a postive or zero integer
        Updates the value of the state to get the associated
        state afer n iterations starting in the axioms

        If n is not an integer raises a TypeError
        If n is negative raises a ValueError
        """
        if type(n) != int:
            raise TypeError("The number of iterations must be an integer")
        if n < 0:
            raise ValueError("The number of iterations must be grater or equal to 0")

        for i in range(n):
            self.next()

    def next(self):
        """
        Iterates one time over the current state
        """
        metrics = []
        for ls in self.lsystems:
            ls.next()
            metrics.append(ls.calculateMetric())

        for i in range(len(self.lsystems)):
            ls.updateMetric(metrics[:i]+metrics[i+1:])

    def draw(self):
        for ls in self.lsystems:
            ls.draw()
