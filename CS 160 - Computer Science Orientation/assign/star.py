import turtle;
window = turtle.Screen()
my_turtle = turtle.Turtle() 
def draw(x, y):
	turtle.clear()
	turtle.reset()
	turtle.hideturtle()

	for x in range(5):
		turtle.right(144)
		turtle.forward(100)
	turtle.showturtle()
turtle.onclick(draw)
window.listen()
window.mainloop()
