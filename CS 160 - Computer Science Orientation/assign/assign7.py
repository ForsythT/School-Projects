def main():
	cont = True
	while cont:
		num = True
		while num:
			tnum = get_num_input("tests")
			anum = get_num_input("assignments")
			enum = get_num_input("exercises")
			lnum = get_num_input("labs")
			num = check_num(tnum, anum, enum, lnum)

		weight = True
		while weight:	
			tweight = get_weight(tnum, "tests (not including a final if you have one)")
			fweight = check_final()
			aweight = get_weight(anum, "assignments")
			eweight = get_weight(enum, "exercises")
			lweight = get_weight(lnum, "labs")
			weight = check_weight(tweight, aweight, eweight, lweight, fweight)	
	
		tscores = get_scores(tnum, tweight, "test")
		ascores = get_scores(anum, aweight, "assignment")
		escores = get_scores(enum, eweight, "exercise")
		lscores = get_scores(lnum, lweight, "lab")
	
		tgrade = calc_class_grade(tscores, tweight, tnum)
		agrade = calc_class_grade(ascores, aweight, anum)
		egrade = calc_class_grade(escores, eweight, enum)
		lgrade = calc_class_grade(lscores, lweight, lnum)
	
		grade = calc_grade(tgrade, agrade, egrade, lgrade)

		print("You're grade in this class is "+str(grade)+"%.")
		while True:	
			again = input("Would you like to calculate a grade in another class? Type 'yes' or 'no': ")
			if again.isalpha():
				again = again.lower()
				if again == "yes":
					cont = True
					break
				elif again == "no":
					cont = False
					break
				else:
					print("Please enter 'yes' or 'no': ")
					continue
			else:
				print("Please enter 'yes' or 'no': ")
				continue
def get_num_input(a):
	while True:	
		n = input("Enter the number of "+str(a)+" in the course: ")					
		if n.isnumeric():
			n = int(n)
			break
		else:
			print("Enter a valid number.")
	return n		

def check_num(t, a, e, l):
	num = t + a + e + l
	if num > 0:
		return False
	else:
		print("You should have at least 1 of at least 1 of the pieces of classwork. Try again.")
		return True

def get_weight(num, a):
	if num > 0:
		while True:
			weight = input("What percentage of your grade are "+str(a)+" worth (weight)?(Ex: 50 = 50%, not .5): ")
			try:
				float(weight)
				twt = float(weight)	
				if 0 <= twt <= 100:
					weight = twt / 100
					break 
				else:
					print("Enter a valid percentage.")
			except ValueError:
				print("Enter a valid percentage.")
	elif num <= 0:
		weight = 0
	return weight

def check_final():
	while True:
		check = input("Do you have a final exam? Enter 'yes' or 'no': ")
		if check.isalpha():
			check = check.lower()
			if check == "yes":
				while True:	
					final = input("What percentage of your grade is it worth? ")
					try:
						float(final)
						fin = float(final)
						if 0 <= fin <= 100:
							final = fin / 100
							break
						else:
							print("Enter a valid percentage.")
					except ValueError:
						print("Enter a valid percentage.")
				break
			elif check == "no":
				final = 0
				break
			else:
				print("Please enter 'yes' or 'no'.")
		else:
			print("Please enter 'yes' or 'no'.")
	return final

def check_weight(t, a, e , l, f):
	weight = t + a + e + l + f
	if weight == 1:
		return False
	else:
		print("Your weight should add up to 100%! Try again.")
		return True

def get_scores(t, w, a):		
	tscores = []
	ttotal = []
	if w > 0:
		for x in range (t):
			worth = input("How many points is "+str(a)+" #"+str(x+1)+" worth? ")
			tscore = input("Enter your score for "+str(a)+" #"+str(x+1)+": ")
			try:
				float(tscore)
				tscore = float(tscore)
				if 0 <= tscore <= worth:
					tscores.append(tscore)
					ttotal.append(worth)
				else:
					print("Enter a valid score.")
			except ValueError:
				print("Enter a valid score.")
	else:
		tscores = [0]
	return tscores

def calc_class_grade(tscores, tweight, t):
	if t > 0:
		tsum = sum(tscores)
		tgrade = tsum / t * tweight	
	else:
		tgrade = 0
	return tgrade

def calc_grade(t, a, e, l):
	grade = t + a + e + l
	return grade
	
main()
