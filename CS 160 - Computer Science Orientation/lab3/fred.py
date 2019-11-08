import turtle
def drawing():
	while True:
		draw = input("What shape would you like to draw? ")
		window = turtle.Screen()
		my_turtle = turtle.Turtle()
		turtle.reset()
		turtle.clear()
		if draw == "triangle":
			for x in range(3):
				turtle.fd(100)
				turtle.lt(120)
			break
		elif draw == "square":
			for x in range(4):
				turtle.fd(100)
				turtle.lt(90)
			break
		elif draw == "hexagon":
			for x in range(6):
				turtle.fd(100)
				turtle.lt(60)
			break
		elif draw == "octagon":
			for x in range(8):
				turtle.fd(100)
				turtle.lt(45)
			break
		else:
			print("Please enter one of 4 shapes: triangle, square, hexagon, octagon. (case sensitive)")
			continue

def cont():
	while True:
		c = input("Would you like to continue drawing shapes? Yes - 1 or No - 0: ")
		if c == "1":
			drawing()
		if c == "0":
			print("Thanks for drawing with me! Good bye.")
			break
		else:
			print("Please enter 1 for yes or 0 for no.")
			continue
drawing()
cont()
