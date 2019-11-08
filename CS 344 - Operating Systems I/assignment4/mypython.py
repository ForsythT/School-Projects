#!usr/bin/python
import random

for i in range(3):	
	f = open("file" + str(i), "w+")
	charList = []
	for j in range(10):
		rand = random.randrange(97, 123)
		charList.append(chr(rand))

	string = "".join(map(str, charList))
	print(string)
	charList.append("\n")
	string = "".join(map(str, charList))
	f.write(string)
	f.close()

a = random.randrange(1, 43)
b = random.randrange(1, 43)
mult = a * b
print(str(a) + "\n" + str(b) + "\n" + str(mult))
