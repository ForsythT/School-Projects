while True:
	n = input("How many scores will you be entering? ")
	if n.isnumeric():
		n = int(n)
		scores = [0]*n
		for x in range (n):
			while True:
				scores[x] = input("Enter score #"+str(x+1)+": ")
				try:
					float(scores[x])
					scores[x] = float(scores[x])
					if scores[x] >= 0:
						break
					else: 
						print("Enter a valid score.")
						continue
				except ValueError:
					print("Enter a valid score.")
					continue
		break
	else:
		print("Enter a valid number.")
scores.sort()
print(scores)
print(sum(scores))
