import turtle as t



class Visualize(object):

    @classmethod
    def basic_actions (left_angle, right_angle, fwd_distance):
        basic =  {
            '-': lambda _ : t.left(left_angle),
            '+': lambda _ : t.right(right_angle),
            'F': lambda _ : t.forward(fwd_distance),
            '[': lambda obj : obj.push(),
            ']': lambda obj : obj.pop(),
        }
        return basic

    def __init__(self,actions):
        self.actions = actions
        self.stack = []
        self.initDisplay()

    def initDisplay(drawColour="black"):
        screen = t.getscreen()
        screen.setup()
        # Try to make the animation of drawing reasonably fast.
        screen.tracer(50,0) # Only draw every 50th update, set delay to zero.
        screen.title ("Jose Javier's L System demo")
        
        t.reset()
        t.degrees()
        t.color(drawColour)
        t.hideturtle() # don't draw the turtle; increase drawing speed.

    def draw(state):
        for symbol in state:
            f = self.actions[symbol]
            f(self)

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

    