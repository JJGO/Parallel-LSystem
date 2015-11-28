import turtle as t
from canvasvg import canvasvg

class Symbol(object):
    """LSystem Symbol class"""

    def __init__(self, char, parameters = []):
        self.char = char
        self.parameters = parameters

    def __str__(self):
        output = self.char
        if len(self.parameters):
            output += "("+", ".join(str(i) for i in self.parameters)
            output = output[:-2]+")"
        return output

    def __repr__(self):
        return str(self)

    def __hash__(self):
        return hash(self.char)

    def __eq__(self,other):
        return self.char == other.char

    def __ne__(self,other):
        return self.char != other.char

class LSystem (object):

    def __init__(self,axiom,production,name = "LSystem"):
        """
            Initializes the variables of the instance:
            alphabet:   Set of symbols present in the system

            axiom:      Initial string of the system, i.e. the iteration 0

            state:      The state of the system after <iteration> number of iterations, initially to 0

            name:       A str with the name of the system

            iteration:  Number of iterations, at the start 0

            production: Default dictionary that implements the substitution
                        Convenient for simple non parametric LSystems
        """
        # self.alphabet   = set(alphabet)
        self.axiom      = list(axiom)
        self.production = {}
        self.state      = self.axiom
        self.name       = name
        self.iteration  = 0

        self.alphabet = set( production.keys() )
        for pred in production:
            self.production[pred] = list(production[pred])
            for symbol in production[pred]:
                if symbol not in self.alphabet:
                    self.alphabet.add(symbol)
                    self.production[symbol] = symbol

    def substitute(self,symbol):
        """
        str -> str function which stores the substitution
        relationships between a letter and its associated string
        """
        return self.production[symbol]

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
        #Creates an empty string to store the new iteration
        # (Remember we cannot change a string we are using in a loop)
        newState = []
        for e in self.state:
            newState.extend( self.substitute(e) )

        self.state = newState
        self.iteration += 1

    def __str__(self):
        """
        Returns a string containing the name, production, axiom and current string of the system
        """
        output = ""
        #Adds the title
        output += "The Lindenmayer System " +"".join(self.name) +" is composed by:\n"
        
        #The alphabet
        output += "The alphabet : "+" ".join(self.alphabet)+"\n"
        
        #The production
        
        output += "The production: \n"
        for letter in self.production:
            output += "\t" + letter + " -> " + "".join(self.production[letter]) + "\n"

        #The axiom and the current string
        output += "The axiom is: " + "".join(self.axiom) +"\n"
        output += "The current string after " + str(self.iteration) + " iterations is: \n" + "".join(self.state) + "\n"

        return output

    def draw(self):
        raise NotImplementedError("Specific Drawing must be specified by the subclass")

class ParametricLSystem(LSystem):
    """Abstract class to define a parametric variation of a LSystem"""
    
    def __init__(self,axiom,name = "Parametric LSystem"):
        # self.alphabet   = set(alphabet)
        self.axiom      = axiom
        self.state      = self.axiom
        self.name       = name
        self.iteration  = 0

    def substitute(self):
        raise NotImplementedError("Needs to be implemented by the subclass")
    
    def __str__(self):
        output = ""
        #Adds the title
        output += "The Parametric Lindenmayer System " +str(self.name) +" is composed by:\n"
        
        #The axiom and the current string
        output += "The axiom is: " + str(self.axiom) +"\n"
        output += "The current string after " + str(self.iteration) + " iterations is: \n" + self.state + "\n"

        return output

class Visualize(object):

    @classmethod
    def basic_actions (cls, left_angle, right_angle, fwd_distance):
        basic =  {
            '+': lambda _ : t.left(left_angle),
            '-': lambda _ : t.right(right_angle),
            'F': lambda _ : t.forward(fwd_distance),
            ' ': lambda (obj,s) : obj.nop(),
            '[': lambda (obj,s) : obj.push(),
            ']': lambda (obj,s) : obj.pop(),
        }
        return basic

    @classmethod
    def basic_actions_parametric (cls, left_angle, right_angle, fwd_distance):
        actions = {}
        actions[Symbol('+')] = lambda _ : t.left(left_angle)
        actions[Symbol('-')] = lambda _ : t.right(right_angle)
        actions[Symbol(' ')] = lambda (obj,s) : obj.nop()
        actions[Symbol('[')] = lambda (obj,s) : obj.push()
        actions[Symbol(']')] = lambda (obj,s) : obj.pop()
        actions[Symbol('F')] = lambda (obj,s) : t.forward(s.parameters[0])
        actions[Symbol('!')] = lambda (obj,s) : t.width(s.parameters[0])
        actions[Symbol('+')] = lambda (obj,s) : t.left(s.parameters[0])
        actions[Symbol('-')] = lambda (obj,s) : t.right(s.parameters[0])
        return actions

    def __init__(self,actions,drawColour="black"):
        self.actions = actions
        self.stack = []
        t.setup()
        # Try to make the animation of drawing reasonably fast.
        t.tracer(100,0) # Only draw every 50th update, set delay to zero.
        t.title ("Jose Javier's L System demo")
        t.reset()
        t.degrees()
        t.color(drawColour)
        t.hideturtle() # don't draw the turtle; increase drawing speed.
        # t.speed(0)

    def draw(self,state):
        for symbol in state:
            f = self.actions[symbol]
            f( (self,symbol) )
        t.update()

    def push(self):
        self.stack.append( (t.position(),t.heading() ) )

    def pop(self):
        if len(self.stack) == 0:
            raise Exception('Attempt to pop empty stack')
        (pos, head) = self.stack.pop()
        t.penup()
        t.goto(pos)
        t.setheading(head)
        t.pendown()

    def nop(self):
        pass

    def forward(self,n):
        t.forward(n)

def saveImg(name):
    name = name + ".svg"
    ts = t.getscreen().getcanvas()
    canvasvg.saveall(name, ts)

def askSaveImg():
    name = raw_input("What would you like to name it? ")
    saveImg(name)
