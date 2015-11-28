from LSystem import *
import random

class KochCurve(LSystem):

    def __init__(self):
        axiom = "F"
        production = {'F':"F+F-F-F+F"}
        LSystem.__init__(self,axiom,production,"Koch Curve")

    def draw(self):
        actions = Visualize.basic_actions(90,90,5)
        Visualize(actions).draw(self.state)

class ArrowHeadCurve(LSystem):

    def __init__(self):
        axiom = "A"
        production = {'A' : "B-A-B", 'B' : "A+B+A"}
        LSystem.__init__(self,axiom,production,"ArrowHead Curve")
    
    def draw(self):
        actions = Visualize.basic_actions(60,60,5)
        actions['A'] = actions['F']
        actions['B'] = actions['F']
        Visualize(actions).draw(self.state)


class HilbertCurve(LSystem):

    def __init__(self):
        axiom = "+A"
        production = {'A':"-BF+AFA+FB-", 'B': "+AF-BFB-FA+"}
        LSystem.__init__(self,axiom,production,"Hilbert Curve")

    def draw(self):
        actions = Visualize.basic_actions(90,90,5)
        actions['A'] = actions[' ']
        actions['B'] = actions[' ']
        Visualize(actions).draw(self.state)
        

class MooreCurve(HilbertCurve):
    def __init__(self):
        HilbertCurve.__init__(self)
        self.name = "MooreCurve"
        self.axiom = "AFA+F+AFA"

class KochSnowflake(LSystem):
    def __init__(self):
        axiom = "F++F++F"
        production = {'F' : "F-F++F-F"}
        LSystem.__init__(self,axiom,production,"Koch Snowflake")

    def draw(self):
        actions = Visualize.basic_actions(60,60,5)
        Visualize(actions).draw(self.state)
        

class KochIsland(LSystem):

    def __init__(self):
        axiom = "F-F-F-F"
        production = {'F' : "F-F+F+FF-F-F+F"}
        LSystem.__init__(self,axiom,production,"Koch Island")

    def draw(self):
        actions = Visualize.basic_actions(90,90,5)
        Visualize(actions).draw(self.state)

class PeanoCurve(LSystem):
    def __init__(self):
        axiom = "+A"
        production = {'A' : "AFBFA-F-BFAFB+F+AFBFA", 'B' : "BFAFB+F+AFBFA-F-BFAFB"}
        LSystem.__init__(self,axiom,production, "Peano Curve")

    def draw(self):
        actions = Visualize.basic_actions(90,90,5)
        actions['A'] = actions[' ']
        actions['B'] = actions[' ']
        Visualize(actions).draw(self.state)

class GosperCurve(LSystem):
    def __init__(self):
        axiom = "A"
        production = {'A' : "A-B--B+A++AA+B-", 'B' : "+A-BB--B-A++A+B"}
        LSystem.__init__(self,axiom,production, "Gosper Curve")

    def draw(self):
        actions = Visualize.basic_actions(60,60,5)
        actions['A'] = actions['F']
        actions['B'] = actions['F']
        Visualize(actions).draw(self.state)

class Tiles(LSystem):

    def __init__(self):
        axiom = "I"
        production = {'I' : "F+F+F+F" , 'F' : "FF+F-F+F+FF"}
        LSystem.__init__(self,axiom,production,"Tiles")

    def draw(self):
        actions = Visualize.basic_actions(90,90,4)
        Visualize(actions).draw(self.state)

class Crystal(LSystem):

    def __init__(self):
        axiom = "I"
        production = {'I' : "F+F+F+F" , 'F' : "FF+F++F+F"}
        LSystem.__init__(self,axiom,production,"Crystal")

    def draw(self):
        actions = Visualize.basic_actions(90,90,2)
        Visualize(actions).draw(self.state)

class HeighwayDragon(LSystem):

    def __init__(self):
        axiom = "FX"
        production = {'X':"X+YF+", 'Y': "-FX-Y"}
        LSystem.__init__(self,axiom,production,"Heighway Dragon Curve")

    def draw(self):
        actions = Visualize.basic_actions(90,90,5)
        actions['X'] = actions[' ']
        actions['Y'] = actions[' ']
        Visualize(actions).draw(self.state)

class TwinDragon(LSystem):

    def __init__(self):
        axiom = "FX+FX+"
        production = {'X':"X+YF", 'Y': "FX-Y"}
        LSystem.__init__(self,axiom,production,"Twindragon Curve")

    def draw(self):
        actions = Visualize.basic_actions(90,90,5)
        actions['X'] = actions[' ']
        actions['Y'] = actions[' ']
        Visualize(actions).draw(self.state)

class TerDragon(LSystem):
    def __init__(self):
        axiom = "F"
        production = {'F' : "F+F-F"}
        LSystem.__init__(self,axiom,production,"Terdragon Curve")

    def draw(self):
        actions = Visualize.basic_actions(120,120,5)
        Visualize(actions).draw(self.state)

class LevyDragon(LSystem):

    def __init__(self):
        axiom = "F"
        production = {'F' : "+F--F+"}
        LSystem.__init__(self,axiom,production,"Levy Dragon Curve")

    def draw(self):
        actions = Visualize.basic_actions(45,45,5)
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

class TwiggyTree(LSystem):

    def __init__(self):
        axiom = "X"
        production = {'F' : "FF", 'X' : "F-[[X]+X]+F[+FX]-X"}
        LSystem.__init__(self,axiom,production,"Twiggy Tree")

    def draw(self):
        actions = Visualize.basic_actions(25,25,2)
        actions['X'] = actions[' ']
        V = Visualize(actions)
        t.left(90)
        V.draw(self.state)

class Conifer(LSystem):

    def __init__(self):
        axiom = "I"
        production = {
            'I' : "VZFFF",
            'V' : "[+++W][---W]YV",
            'W' : "+X[-W]Z",
            'X' : "-W[+X]Z",
            'Y' : "YZ",
            'Z' : "[-FFF][+FFF]F",
            'F' : "F",
        }
        LSystem.__init__(self,axiom,production,"Conifer")

    def draw(self):
        actions = Visualize.basic_actions(20,20,11)
        actions['I'] = actions[' ']
        actions['V'] = actions[' ']
        actions['W'] = actions[' ']
        actions['X'] = actions[' ']
        actions['Y'] = actions[' ']
        actions['Z'] = actions[' ']
        V = Visualize(actions)
        t.left(90)
        V.draw(self.state)

class StochasticTree(ParametricLSystem):

    def __init__(self):
        axiom = "F"
        ParametricLSystem.__init__(self,axiom,"Stochastic Tree")

    def substitute(self,symbol):
        if symbol == 'F':
            x = random.random()
            if x < .33:
                return "F[+F]F[-F]F"
            elif x < .66:
                return "F[+F]F"
            else:
                return "F[-F]F"
        else:
            return symbol

    def draw(self):
        actions = Visualize.basic_actions(25.7,25.7,8)
        V = Visualize(actions)
        t.left(90)
        V.draw(self.state)

class RowOfTrees(ParametricLSystem):

    def __init__(self):
        axiom = [Symbol('F',[500])]
        self.c = 1
        self.p = .3
        self.q = self.c-self.p
        self.h = (self.p*self.q)**.5
        ParametricLSystem.__init__(self,axiom,"Row Of Trees")

    def substitute(self,symbol):
        if symbol == Symbol('F'):
                x = symbol.parameters[0]
                p = Symbol('F',[x * self.p])
                q = Symbol('F',[x * self.q])
                h = Symbol('F',[x * self.h])
                plus = Symbol('+',[87])
                minus = Symbol('-',[87])
                return [p, plus, h ,minus,minus,h,plus,q]
        else:
            return [symbol]

    def draw(self):
        actions = Visualize.basic_actions_parametric()
        actions[Symbol('F')] = lambda (obj,s) : t.forward(s.parameters[0])
        V = Visualize(actions)
        # t.left(90)
        V.draw(self.state)

class BetterRowOfTrees(ParametricLSystem):

    def __init__(self):
        axiom = [Symbol('F',[500,0])]
        self.c = 1
        self.p = .3
        self.q = self.c-self.p
        self.h = (self.p*self.q)**.5
        ParametricLSystem.__init__(self,axiom,"Better Row Of Trees")

    def substitute(self,symbol):
        if symbol == Symbol('F'):
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

    def draw(self):
        actions = Visualize.basic_actions_parametric()
        V = Visualize(actions)
        # t.left(90)
        V.draw(self.state)

if __name__ == '__main__':

    Cs = [
    # (KochCurve,         6),
    # (ArrowHeadCurve,    10),
    # (HilbertCurve,      7),
    # (MooreCurve,        7),
    # (KochSnowflake,     6),
    # (PeanoCurve,        4),
    # (GosperCurve,       4),
    # (HeighwayDragon,    13),
    # (TwinDragon,        13),
    # (TerDragon,         9),
    # (LevyDragon,        14),
    # (BushyTree,         4),
    # (TwiggyTree,        7),
    # (Conifer,           12),
    # (Crystal,           6),
    # (Tiles,             4),
    # (KochIsland,        3),
    # (StochasticTree,    5),
    # (RowOfTrees,        5),
    # (BetterRowOfTrees,  9),
    ]

    # for fractal,it in Cs:
    #     F = fractal()
    #     F.iterate(it)
    #     # print F.state
    #     F.draw()
    #     saveImg(F.name+str(F.iteration))
        # wait = raw_input("PRESS ENTER TO CONTINUE")
    

    R = RowOfTrees()
    R.iterate(2)
    print R.state
    # s = "F(45)+(87)F(68.7386)-(87)-(87)F(68.7386)+(87)F(105)+(87)F(68.7386)+(87)F(105)-(87)-(87)F(105)+(87)F(160.39)-(87)-(87)F(68.7386)+(87)F(105)-(87)-(87)F(105)+(87)F(160.39)+(87)F(105)+(87)F(160.39)-(87)-(87)F(160.39)+(87)F(245)"
    # R.setState(parseSymbols(s))
    print R.state
    R.draw()
    wait = raw_input("PRESS ENTER TO CONTINUE")