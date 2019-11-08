import math #importing the math.sqrt function
while True: #infinite loop to deal with invalid number errors as well as being able to use the program again
	n = input("Please enter the number you would like to find the square root of: "); #taking input from user
	if n.isdigit()==False:
		print("Please enter a valid number."); #error message for non digit input
		continue
	elif (float(n)>0):     #make sure input is positive	
		g = float(n)/2 #initial g value
		while True:    #loop of Babylonian algorithm
			r = float(n)/g; # ^
			g = (g+r)/2;    # ^
			if (r-.00000000001)<=g<=(r+.00000000001): #threshold for g
				print("The square root of "+str(n)+" using the Babylonian algorithm is approximately "+str(g)+"."); #answer found with Babylonian algorithm
				print("The square root of "+str(n)+" using the imported square root function is approximately "+str(math.sqrt(float(n)))+"."); #answer found with the imported math function
				break #end Babylonian loop
			else:
				continue #continues the Babylonian loop until g is very close to r
		while True: #loop used to create controlled error message for using calc again
			a = input("Would you like to use this calculator again? Yes - y or No - n: "); #taking user input for using calc again
			if a in ("y","n"): #if user doesn't put y or n for answer, then enters the error message asking to input y or n
				break      #then it enters this error message vvvv          
			print("Please enter 'y' for Yes or 'n' for No (case sensitive)."); #error message
		if (a == "y"):
			continue
		else:
			print("Thanks for using this square root calculator. Good bye.") #goodbye message
			break
	elif (float(n)==0):
		print("You can't use the Babylonian algorithm to find the square root of 0. By the way, it's 0."); #error message for 0
	else: 
		print("Please enter a valid number."); #error message for negative input
		continue

