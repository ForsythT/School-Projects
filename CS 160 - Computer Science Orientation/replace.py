
def main():
	n = get_int()
	scores = get_scores(n)
	newscores = yes_no(scores)
	if newscores == scores:
		print("Here are your numbers:", scores)
	else:	
		print("Here are your numbers:", newscores)

def get_int():
	while True:
		n = input("How many numbers will you be entering? ")
		if n.isnumeric():
			n = int(n)
			return n	
		else:
			print("Enter a valid number.")

def get_scores(n):
	scores = [0]*n
	for x in range(n):
		while True:
			scores[x] = input("Enter #"+str(x+1)+": ")
			cont = check_score(scores, x)	
			if cont == True:
				scores[x] = float(scores[x])
				break
			else: 
				print("You've either already entered that number or it is invalid. Try again.")
	return scores		
	
def check_score(scores, x):
	try:
		float(scores[x])
		for y in range (len(scores)):
			if float(scores[x]) == float(scores[y]):
				if x == y:
					continue
				else:
					return False
			else:
				continue
		return True	
	except ValueError:
		return False

def yes_no(scores):
	while True:
		ask = input("Do you want to replace any numbers? Yes or no: ")
		if ask.isalpha():
			ask = ask.lower()
			if ask == "yes":
				remove(scores)
			elif ask == "no":
				return scores
			else: 
				print("Enter yes or no.")
				continue
		else: 
			print("Enter yes or no.")
			continue
def remove(scores):
	print(scores)
	while True:
		ask = input("What number do you want to remove? ")
		ask = float(ask)
		c = check(ask, scores)
		if c == True:
			scores.remove(ask)
			while True:
				ask2 = input("What number do you want to replace it with? ")	
				try:
					float(ask2)
					ask2 = float(ask2)
					scores.append(ask2)
					return scores
				except ValueError:
					print("Enter a valid number.")
					continue
		else:
			print("Enter one of your numbers.")
			continue
def check(ask, scores):
	for x in range (len(scores)):
		if ask == scores[x]:
			return True
		else: 
			continue
main()

