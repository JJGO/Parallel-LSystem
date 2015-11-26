import pylab

class LSystem (object):

	def __init__(self,alphabet,axiom,rules,name = "LSystem"):
		"""
		Initializes the valribles of the instance:
			alphabet: 	str -> str dictionary which stores the substitution
						relationships between a letter and its associated string

			axiom:		Initial string of the system, i.e. the iteration 0

			string:		The string after iteration number of iterations, initially to 0

			rules:		str -> some dictionary which stores the rules of drawing
						The assigned values are reserved and are:
							- 'F' : Draw a forward line of 1 unit
							- int : integer, the turn in degress
									positive - counterclockwise
									negative - clockwise
						BETA : Any other action has to be passed in form of a function
			
			name:		A str with the name of the system

			iteration: 	Number of iterations, at the start 0

			X:			List containing the X values for plotting
			Y: 			List containing the Y values for plotting
						Both start at the origin of coordinates

		"""

		self.alphabet 	= alphabet
		self.axiom 		= axiom
		self.string 	= self.axiom
		self.rules		= rules
		self.name		= name
		self.iteration 	= 0
		self.X			= [0.0]
		self.Y			= [0.0]

		for e in self.rules.keys():
			if e not in self.alphabet.keys():
				self.alphabet[e] = e

	def __str__(self):
		"""
		Returns a string containing the name, alphabet, axiom and current string of the system
		"""
		output = ""
		#Adds the title
		output += "The Lindenmayer System " +str(self.name) +" is composed by:\n"
		#The alphabet
		output += "The alphabet: \n"
		for letter in self.alphabet:
			output += "\t" + letter + " -> " + self.alphabet[letter] + "\n"

		#The axiom and the current string
		output += "The axiom is: " + str(self.axiom) +"\n"
		output += "The current string after " + str(self.iteration) + " iterations is: \n" + self.string + "\n"

		return output

	def iterate(self,n):
		"""
		Assumes n is a postive or zero integer
		Updates the value of the string to get the associated
		string afer n iterations starting in the axioms

		If n is not an integer raises a TypeError
		If n is negative raises a ValueError
		"""
		if type(n) != int:
			raise TypeError("The number of iterations must be an integer")
		if n < 0:
			raise ValueError("The number of iterations must be grater or equal to 0")

		self.iteration = n
		self.string = self.axiom

		for i in range(n):
			#Creates an empty string to store the new iteration
			# (Remember we cannot change a string we are using in a loop)
			newString = ""
			for e in self.string:
				newString += self.alphabet[e]

			self.string = newString

	def draw(self):
		"""
		Updates the values of the List self.X and self.Y to obtain
		the coordinates of the figure defined by the string according
		to the "rules"
		"""

		self.X = [0.0]
		self.Y = [0.0]
		alpha = 0.0

		for letter in self.string:
			Xref = self.X[-1]
			Yref = self.Y[-1]
			i = self.rules[letter]
			if str(i) == 'F':
				newX = Xref + pylab.cos(alpha)
				newY = Yref + pylab.sin(alpha)
				self.X.append(newX)
				self.Y.append(newY)

			elif type(i) == float:
				alpha += pylab.pi*i/180.0

	def plot(self,style="r-",figure=1):
		"""
		Plots in pylab the current coordinates contained by
		the X and Y lists
		Keyword assigments
		The style is a red line by default
		The figure by default is 1
		"""
		self.draw()

		pylab.figure(figure)

		pylab.title(self.name)

		pylab.plot(self.X,self.Y,style)
		
		
	def show(self):
		pylab.show()

	def test(self,n):
		self.iterate(n)
		self.plot()
		self.show()

class KochCurve(LSystem):

	def __init__(self):
		alphabet = {'F':"F+F-F-F+F"}
		axiom = "F"
		rules = {'F' : "F", '+' : 90.0, "-" : -90.0 }
		LSystem.__init__(self,alphabet,axiom,rules,"Koch Curve")

class ArrowHeadCurve(LSystem):
	def __init__(self):
		alphabet = {'A' : "B-A-B", 'B' : "A+B+A"}
		axiom = "A"
		rules = {'A' : "F", "B" : "F", "+" : 60.0, "-" : -60.0}
		LSystem.__init__(self,alphabet,axiom,rules,"ArrowHead Curve")

class HilbertCurve(LSystem):

	def __init__(self):
		alphabet = {'A':"-BF+AFA+FB-", 'B': "+AF-BFB-FA+"}
		axiom = "A"
		rules = {'A' : "", 'B' : "", 'F' : "F", '+' : 90.0, "-" : -90.0 }
		LSystem.__init__(self,alphabet,axiom,rules,"Hilbert Curve")

class MooreCurve(HilbertCurve):
	def __init__(self):
		HilbertCurve.__init__(self)
		self.axiom = "AFA+F+AFA"

class KochSnowflake(LSystem):
	def __init__(self):
		alphabet = {'F' : "F-F++F-F"}
		axiom = "F++F++F"
		rules = {'F' : "F" , "+" : 60.0, "-" : -60.0}
		LSystem.__init__(self,alphabet,axiom,rules,"Koch Snowflake")

class PeanoCurve(LSystem):
	def __init__(self):
		alphabet = {'A' : "AFBFA-F-BFAFB+F+AFBFA", 'B' : "BFAFB+F+AFBFA-F-BFAFB"}
		axiom = "+A"
		rules = {'F' : "F","A" : "", "B":"", "+" : 90.0, "-": -90.0}
		LSystem.__init__(self,alphabet, axiom,rules, "Peano Curve")

class GosperCurve(LSystem):
	def __init__(self):
		alphabet = {'A' : "A-B--B+A++AA+B-", 'B' : "+A-BB--B-A++A+B"}
		axiom = "A"
		rules = {"A" : "F", "B":"F", "+" : 60.0, "-": -60.0}
		LSystem.__init__(self,alphabet, axiom,rules, "Gosper Curve")

class Dragon(LSystem):
	pass


class HeighwayDragon(Dragon):

	def __init__(self):
		alphabet = {'X':"X+YF+", 'Y': "-FX-Y"}
		axiom = "FX"
		rules = {'X' : "", 'Y' : "", 'F' : "F", '+' : 90.0, "-" : -90.0 }
		LSystem.__init__(self,alphabet,axiom,rules,"Heighway Dragon Curve")

class TwinDragon(Dragon):

	def __init__(self):
		alphabet = {'X':"X+YF", 'Y': "FX-Y"}
		axiom = "FX+FX+"
		rules = {'X' : "", 'Y' : "", 'F' : "F", '+' : 90.0, "-" : -90.0 }
		LSystem.__init__(self,alphabet,axiom,rules,"Twindragon Curve")

class TerDragon(Dragon):
	def __init__(self):
		alphabet = {'F' : "F+F-F"}
		axiom = "F"
		rules = {'F' : "F", '+' : 120.0, "-" : -120.0 }
		LSystem.__init__(self,alphabet,axiom,rules,"Terdragon Curve")

class LevyDragon(Dragon):

	def __init__(self):
		alphabet = {'F' : "+F--F+"}
		axiom = "F"
		rules = {'F' : "F", '+' : 45.0, "-" : -45.0 }
		LSystem.__init__(self,alphabet,axiom,rules,"Levy Dragon Curve")


if __name__ == '__main__':
	K = KochSnowflake()
	K.iterate(5)
	print K.string
	print K

