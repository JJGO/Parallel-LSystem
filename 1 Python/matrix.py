import numpy as np
from math import sin,cos,pi
import turtle as t
from fractals import *

S = np.eye(4)

def _rotation(axis1,axis2,alpha):
	M = np.eye(4)
	M[axis1,axis1] = cos(alpha)
	M[axis1,axis2] = -sin(alpha)
	M[axis2,axis1] = sin(alpha)
	M[axis2,axis2] = cos(alpha)
	return M

def RH(alpha):
	return _rotation(2,3,np.radians(alpha))

def RL(alpha):
	return _rotation(1,3,np.radians(alpha))

def RU(alpha):
	return _rotation(1,2,np.radians(alpha))

def F(d):
	M = np.eye(4)
	M[1,0] = d
	return M

# string = "F+F+F&F&F>>-F-F^F<<&"
istring = "F+F+F+F+"
string = "&F^F+^F&&F^F+^F&&F^F+^F&&F^F+" #^F&"

actions = {
	'F' : F(50),
	'+' : RU(90),
	'-' : RU(-90),
	'&' : RL(90),
	'^' : RL(-90),
	'>' : RH(90),
	'<' : RH(-90),
	'|' : RU(180),
}

def proy_ax(alpha,cr=2.0/3):
	proy = np.zeros([2,3])
	alpha = np.radians(alpha)
	proy[0,0] = cr*cos(alpha)
	proy[1,0] = cr*sin(alpha)
	proy[0,1] = 1
	proy[1,2] = 1
	return proy

def proy_iso(alpha):
	proy = np.zeros([2,3])
	alpha = np.radians(alpha)
	proy[0] = [-cos(alpha), cos(alpha), 0 ]
	proy[1] = [-sin(alpha), -sin(alpha), 1]
	return proy

P = proy_ax(225)
# P = proy_iso(30)
t.speed(0)
t.width(7)
H = Hilbert3D()
H.iterate(3)
print H.state.count('F')

color = 0
for char in H.state:
	if char in actions:
		M = actions[char]
		S = S.dot(M)
		pos = S.round().astype(int)[1:4,0]
		if char == 'F':
			# print pos,
			proy_pos = list(np.dot(P,pos))
			# print proy_pos
			Red = 1 if color < 256 else 1- (color%256)/256.0
			Blue = 1 if color >= 256 else color/256.0
			paleta = (Red,0,Blue)
			t.color(paleta)
			t.goto( proy_pos )
			color += 1

wait = raw_input("PRESS ENTER TO CONTINUE")

