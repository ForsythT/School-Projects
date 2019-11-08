import turtle
window = turtle.Screen()
my_turtle = turtle.Turtle()
def draw(x, y):
	turtle.clear()
	turtle.reset()	   #Clearing the board
	turtle.hideturtle() #Hide turtle so user can't click it while it's drawing

	turtle.forward(50)
	turtle.right(90)  
	turtle.forward(20)
	turtle.right(90)
	turtle.forward(40)
	turtle.left(90)
	turtle.forward(80)
	turtle.right(90)
	turtle.forward(20) #Drawing T
	turtle.right(90)
	turtle.forward(80)
	turtle.left(90)
	turtle.forward(40)
	turtle.right(90)
	turtle.forward(20)
	turtle.right(90)
	turtle.forward(100)	

	turtle.penup()
	turtle.forward(20) #Adding a space between the letters
	turtle.pendown()

	turtle.forward(60)
	for x in range(2): #"I" had a loop because of the way the letter is structured it allows for one to be used easily
		turtle.right(90)
		turtle.forward(20)
		turtle.right(90)
		turtle.forward(20) #Drawing I
		turtle.left(90)
		turtle.forward(60)
		turtle.left(90)
		turtle.forward(20)
		turtle.right(90)
		turtle.forward(20)
		turtle.right(90)	
		turtle.forward(60)

	turtle.penup()
	turtle.forward(20) #Adding another space
	turtle.pendown()

	turtle.forward(20)
	turtle.right(60)
	turtle.forward(50)
	turtle.left(120)
	turtle.forward(50)
	turtle.right(60)
	turtle.forward(20)
	turtle.right(90)
	turtle.forward(100)
	turtle.right(90)
	turtle.forward(20) #Drawing M
	turtle.right(90)
	turtle.forward(60)	
	turtle.left(150)
	turtle.forward(50)
	turtle.right(120)
	turtle.forward(50)
	turtle.left(150)
	turtle.forward(60)
	turtle.right(90)
	turtle.forward(20)
	turtle.right(90)
	turtle.forward(100)
	
	turtle.showturtle() #Show turtle at the end so user can click him to draw again
turtle.onclick(draw)
window.listen()
window.mainloop()
