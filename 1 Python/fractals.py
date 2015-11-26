from LSystem import *

class KochCurve(LSystem):

    def __init__(self):
        axiom = "F"
        production = {'F':"F-F+F+F-F"}
        LSystem.__init__(self,axiom,production,"Koch Curve")

    def draw(self):
        actions = Visualize.basic_actions(90,90,2)
        Visualize(actions).draw(self.state)

class ArrowHeadCurve(LSystem):

    def __init__(self):
        axiom = "A"
        production = {'A' : "B-A-B", 'B' : "A+B+A"}
        LSystem.__init__(self,axiom,production,"ArrowHead Curve")
    
    def draw(self):
        actions = Visualize.basic_actions(60,60,1)
        actions['A'] = actions['F']
        actions['B'] = actions['F']
        Visualize(actions).draw(self.state)


class HilbertCurve(LSystem):

    def __init__(self):
        axiom = "A"
        production = {'A':"-BF+AFA+FB-", 'B': "+AF-BFB-FA+"}
        LSystem.__init__(self,axiom,production,"Hilbert Curve")

    def draw(self):
        actions = Visualize.basic_actions(90,90,1)
        actions['A'] = actions[' ']
        actions['B'] = actions[' ']
        Visualize(actions).draw(self.state)
        

class MooreCurve(HilbertCurve):
    def __init__(self):
        HilbertCurve.__init__(self)
        self.axiom = "AFA+F+AFA"

class KochSnowflake(LSystem):
    def __init__(self):
        axiom = "F++F++F"
        production = {'F' : "F-F++F-F"}
        LSystem.__init__(self,axiom,production,"Koch Snowflake")

    def draw(self):
        actions = Visualize.basic_actions(60,60,1)
        Visualize(actions).draw(self.state)
        

class PeanoCurve(LSystem):
    def __init__(self):
        axiom = "+A"
        production = {'A' : "AFBFA-F-BFAFB+F+AFBFA", 'B' : "BFAFB+F+AFBFA-F-BFAFB"}
        LSystem.__init__(self,axiom,production, "Peano Curve")

    def draw(self):
        actions = Visualize.basic_actions(90,90,1)
        actions['A'] = actions[' ']
        actions['B'] = actions[' ']
        Visualize(actions).draw(self.state)

class GosperCurve(LSystem):
    def __init__(self):
        axiom = "A"
        production = {'A' : "A-B--B+A++AA+B-", 'B' : "+A-BB--B-A++A+B"}
        LSystem.__init__(self,axiom,production, "Gosper Curve")

    def draw(self):
        actions = Visualize.basic_actions(60,60,1)
        actions['A'] = actions['F']
        actions['B'] = actions['F']
        Visualize(actions).draw(self.state)

class HeighwayDragon(LSystem):

    def __init__(self):
        axiom = "FX"
        production = {'X':"X+YF+", 'Y': "-FX-Y"}
        LSystem.__init__(self,axiom,production,"Heighway Dragon Curve")

    def draw(self):
        actions = Visualize.basic_actions(90,90,3)
        actions['X'] = actions[' ']
        actions['Y'] = actions[' ']
        Visualize(actions).draw(self.state)

class TwinDragon(LSystem):

    def __init__(self):
        axiom = "FX+FX+"
        production = {'X':"X+YF", 'Y': "FX-Y"}
        LSystem.__init__(self,axiom,production,"Twindragon Curve")

    def draw(self):
        actions = Visualize.basic_actions(90,90,1)
        actions['X'] = actions[' ']
        actions['Y'] = actions[' ']
        Visualize(actions).draw(self.state)

class TerDragon(LSystem):
    def __init__(self):
        axiom = "F"
        production = {'F' : "F+F-F"}
        LSystem.__init__(self,axiom,production,"Terdragon Curve")

    def draw(self):
        actions = Visualize.basic_actions(120,120,1)
        Visualize(actions).draw(self.state)

class LevyDragon(LSystem):

    def __init__(self):
        axiom = "F"
        production = {'F' : "+F--F+"}
        LSystem.__init__(self,axiom,production,"Levy Dragon Curve")

    def draw(self):
        actions = Visualize.basic_actions(45,45,1)
        Visualize(actions).draw(self.state)

class BushyTree(LSystem):

    def __init__(self):
        axiom = "F"
        production = {'F' : "FF-[-F+F+F]+[+F-F-F]"}
        LSystem.__init__(self,axiom,production,"Bushy Tree")

    def draw(self):
        actions = Visualize.basic_actions(25,25,5)
        V = Visualize(actions)
        t.left(90)
        V.draw(self.state)

if __name__ == '__main__':

    Cs = [BushyTree]

    for fractal in Cs:
        F = fractal()
        F.next()
        F.iterate(5)
        # print F
        F.draw()
        # wait = raw_input("PRESS ENTER TO CONTINUE")
        saveImg(F.name+str(F.iteration))
