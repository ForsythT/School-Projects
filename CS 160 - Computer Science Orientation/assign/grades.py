############################################################################################################################################################################################
# Program Filename: grades.py																				   #
# Author: Tim Forsyth                 																			   #
# Date: 11/18/2015																					   #
# Description: This program takes your scores from tests, assignments, exercises, and labs and calculates your grade in said class based on how it is weighted as specified by the user.   #
# Input: Number of tests/assignments/exercises/labs, the value and user's score on those tests/assignments/exercises/labs, and the weight of them in the class.				   #
# Output: Final class grade																				   #
############################################################################################################################################################################################

def main():								#############################################################################
	cont = True							# Function Name: main							    #	
	while cont:							# Description: The main function of the program, starts it and restarts it. #
		numcheck = True						# Parameteres: None							    #
		while numcheck:						# Return Values: None							    #
			numlist = get_num_array()			# Pre-Conditions: 							    #
			numcheck = check_num_total(numlist)		# Post-Conditions:							    #
									#############################################################################
		c = check_final()	
	
		weightcheck = True
		while weightcheck:
			final = get_final_weight(c)
			weight = get_weight_array(numlist)
			weightcheck = check_total_weight(weight, final)
	
		tvalue = get_value_array("test", numlist[0], weight[0])
		tscores = get_scores_array("test", numlist[0], tvalue, weight[0])
		avalue = get_value_array("assignment", numlist[1], weight[1])
		ascores = get_scores_array("assignment", numlist[1], avalue, weight[1])
		evalue = get_value_array("exercise", numlist[2], weight[2])
		escores = get_scores_array("exercise", numlist[2], evalue, weight[2])
		lvalue = get_value_array("lab", numlist[3], weight[3])
		lscores = get_scores_array("lab", numlist[3], lvalue, weight[3])
		if c == True:
			fvalue = get_final_value()
			fscore = get_final_score(fvalue)
			favg = calc_final(fscore, fvalue, final)
		else:
			favg = 0		
	
		tavg = calc_weighted_avg(tscores, tvalue, weight[0]) 
		aavg = calc_weighted_avg(ascores, avalue, weight[1])
		eavg = calc_weighted_avg(escores, evalue, weight[2])
		lavg = calc_weighted_avg(lscores, lvalue, weight[3])
		
		grade = calc_grade(tavg, aavg, eavg, lavg, favg)
		print("Your final grade is "+str(grade)+"%.")
		while True:
			again = input("Would you like to calculate your grade again?('yes' or 'no'): ")
			cont = check_yes_no(again)
			if cont == False:
				print("Thanks for using this calculator! Good bye.")
				break
			elif cont == True:
				break
			else: 
				continue	
		
def check_yes_no(x):							###########################################################################
	if x.isalpha():							# Function Name: check_yes_no					          #
		x = x.lower()						# Description: Checks if "x" is "yes" or "no". Good for yes or no inputs. #
		if x == "yes":						# Parameters: x - A string input by the user				  #	
			return True					# Return Values: Boolean value						  #
		elif x == "no":						# Pre-Conditions: x is a string (has characters)			  #
			return False					# Post-Conditions: None							  #
		else:							###########################################################################
			print("Please enter 'yes' or 'no'.")
			return 
	else: 
		print("Please enter 'yes' or 'no'.")
		return

def get_num_array():							###########################################################################
	num = [0]*4							# Function Name: get_num_array	 					  #
	for x in range (4):						# Description: Puts number of tests/assignments/etc. into an array.	  #
		if x == 0:						# Parameters: None							  #
			a = "tests"					# Return Values: An array containing the number of tests/assignments/etc. #
		elif x == 1:						# Pre-Conditions: None 							  #
			a = "assignments"				# Post-Conditions: An array of values goes to main			  #
		elif x == 2:						###########################################################################
			a = "exercises"
		else:
			a = "labs"
		num[x] = get_num(a)
	return num

def get_num(a):								###########################################################################
	cont = True							# Function Name: get_num						  #
	while cont:							# Description: Gets a valid, positive interger number.			  #
		num = input("Enter the number of "+a+" you have: ")	# Parameters: a - A string used purley for user interface specification.  #
		cont = check_num(num)					# Return Values: A valid interger number.				  #
		if cont == False:					# Pre-Conditions: None							  #
			num = int(num)					# Post-Conditions: A positive int goes to get_num_array			  #
			return num					###########################################################################

def check_num(num):							###########################################################################
	if num.isnumeric():						# Function Name: check_num						  #
		return False						# Description: Checks to make sure num is a valid, positive interger.	  #
	else: 								# Parameters: num - A string input by a user.			 	  #
		print("Enter a valid number.")				# Return Values: Boolean value						  #
		return True						# Pre-Conditions: Num contains characters				  #	
									# Post-Conditions: None							  #
									###########################################################################	

def check_num_total(num):						###########################################################################	
	if sum(num) > 0:						# Function Name: check_num_total					  #
		return False						# Description: Checks to make sure atleast 1 category is used.		  #
	else:								# Parameters: num - An array of integers 				  #
		print("What kind of class are you taking?! Try again.")	# Return Values: Boolean value						  #
		return True						# Pre-Conditions: Num is an array with valid ints			  #
									# Post-Conditions: None							  #
def check_final():							###########################################################################
	while True:
		final = input("Do you have a final that is weighted separately from your tests?('yes' or 'no'): ")
		cont = check_yes_no(final)				###########################################################################
		if cont == False:					# Function Name: check_final						  #
			return False					# Description: Finds out if the user has a final exam or not.		  #
			break						# Parameters: None							  #
		elif cont == True:					# Return Values: Boolean value 						  #
			return True					# Pre-Conditions: None 							  #
			break						# Post-Conditions: None							  #
		else:							###########################################################################
			continue
def get_final_weight(c):									#################################################################
	final = "k"										# Function Name: get_final_weight				#
	while check_weight(final):								# Description: Gets the weight of the final from the user.	#
		if c == True:									# Parameters: c - Boolean value telling if they have a final.	#
			final = input("What percent of your grade is the final worth(weight)? ")# Return Values: A valid float number between 0 and 100.	#
			if check_weight(final) == False:					# Pre-Conditions: None						#
				final = float(final)						# Post-Conditions: Weight of final goes to main			#
				return final							#################################################################
				break
			else: 
				print("Enter a valid percentage.")
				continue
		else:
			final = 0
			return final

def check_weight(a):							###########################################################################
	try:								# Function Name: check_weight						  #	 
		float(a)						# Description: Checks to make sure weight is float between 0 and 100.	  #
		a = float(a)						# Parameters: a - A string input by the user				  #
		if 0 <= a <= 100:					# Return Values: Boolean value						  #
			return False					# Pre-Conditions: a is a string (has characters)			  #
		else:							# Post-Conditions: None
			return True					###########################################################################
	except ValueError:
		return True

def get_weight_array(num):						##################################################################################
	weight = [0, 0, 0, 0]						# Function Name: get_weight_array						 #
	for x in range (4):						# Description: Gets an array of the weight of each category. 			 #
		if x == 0:						# Parameters: num - Not used in this function, but needed for calling get_weight #
			a = "tests"					# Return Values: An array of float numbers that range between 0 and 100.	 #
		elif x == 1:						# Pre-Conditions: None								 #
			a = "assignments"				# Post-Conditions: An array of the weight of categories goes to main		 #
		elif x == 2:						##################################################################################
			a = "exercises"
		else:
			a = "labs"	
		weight[x] = get_weight(a, num, x)
	return weight
def get_weight(a, num, x):									################################################################### 			
	if num[x] > 0:										# Function Name: get_weight					  #	
		while True:									# Description: Gets a float between 0 and 100			  #
			weight = input("What percent of your grade are "+a+" worth(weight)? ")	# Parameters: a - String used to for UI 			  #
			if check_weight(weight) == False:					# 	      num - Used to check if they have any of a category. #
				weight = float(weight)						#	      x - Number taken from for loop in get_weight_array  #
				break								# Return Values: A float between 0 and 100			  #
			else:									# Pre-Conditions: a is a string, num is an array, x is an int     #
				print("Enter a valid percentage.")				# Post-Conditions: Weight of category returns to get_weight_array #
				continue							###################################################################
	else:
		weight = 0
	return weight

def check_total_weight(weight, final):					#################################################################################
	if (sum(weight) + final)  == 100:				# Function Name: check_total_weight						#
		return False						# Description: Checks to make sure weights add up to 100.			#
	else:								# Parameters: weight - Array with all the weights, final - The weight of final  #
		print("Your total weight must add up to 100%!")		# Return Values: Boolean value							#
		return True						# Pre-Conditions: weight is an array with floats and final is a float value	#
									# Post-Conditions: None								#
									#################################################################################
def get_value_array(a, b, c):						
	scores = [0]*b											 #######################################################################	
	if c > 0:											 # Function Name: get_value_array				       #	
		for x in range (b):									 # Description: Gets an array of value of each category things (tests) #
			while True:									 # Parameters: a - String used for UI, b - num of tests etc c - weight #
				scores[x] = input("Enter how many points "+a+" #"+str(x+1)+" is worth: ")# Return Values: An array of values (how much its worth)	       #
				cont = check_value(x, scores)						 # Pre-Conditions: a is a string, b is an int, c is a positive float   #
				if cont == False:							 # Post-Conditions: An array of values goes to main		       #
					print("Please enter a valid number.")				 #######################################################################
				else:
					break
	return scores

def check_value(x, scores):						#################################################################################################
	try:								# Function Name: check_value								  	#	
		float(scores[x])					# Description: Checks if a value is a valid, positive number.					#
		scores[x] = float(scores[x])				# Parameters: x - Number from for loop in get_value_array, scores - array from get_value_array  #
		if scores[x] > 0:					# Return Values: Boolean value									#
			return True					# Pre-Conditions: x is a positive int, scores is an array					#
		else:							# Post-Conditions: None										#
			return False					#################################################################################################
	except ValueError:
		return False


def get_scores_array(a, b, value, c):										#####################################################################
	scores = [0]*b												# Function Name: get_scores_array				    #
	if c > 0:												# Description: Get array with floats between 0 and respective value #
		for x in range (b):										# Parameters: a - String used for UI, b - num tests etc, c - weight #
			while True:										# 	      value - An array of the values of tests etc	    #
				scores[x] = input("Enter the score you got for "+a+" #"+str(x+1)+": ")		# Pre-Conditions: a is a string, b is an int, c is a positive float #
				cont = check_scores(x, value, scores)						# 		  value is an array with positive floats	    #
				if cont == False:								# Post-Conditions: An array of scores goes to main		    #	
					print("Please enter a valid score between 0 and "+str(value[x])+".")	#####################################################################
				else:
					break
	return scores

def check_scores(x, value, scores):					#############################################################################################
	try: 								# Function Name: check_scores								    #
		float(scores[x])					# Description: Checks if a score is a valid, positive number.				    #
		scores[x] = float(scores[x])				# Parameters: x - Number from for loop in get_scores_array, value - array of values	    #
		if 0 <= scores[x] <= value[x]:				#	      scores - array of scores							    #
			return True					# Return Values: Boolean value								    #
		else: 							# Pre-Conditions: x is a pos int, value is an array of floats, scores is an array of floats #
			return False					# Post-Conditions: None									    #
	except ValueError:						#############################################################################################
		return False

def get_final_value():								#################################################
	while True:								# Function Name: get_final_value		#
		final = input("Enter how many points the final is worth: ")	# Description: Gets value (worth) of final	#
		try:								# Parameters: None				#
			float(final)						# Return Values: A positive float value		#
			final = float(final)					# Pre-Conditions: None				#
			if final > 0:						# Post-Conditions: Value of final goes to main	#
				break						#################################################
			else: print("Please enter a valid number.")
		except ValueError:
			print("Please enter a valid number.")
	return final

def get_final_score(value):							#################################################################
	while True:								# Function Name: get_final_score				#
		final = input("Enter the score you got on the final: ")		# Description: Gets score of final				#
		try:								# Parameters: value - positive float used to restrict input	#
			float(final)						# Return Values: A positive float value between 0 and value	#
			final = float(final)					# Pre-Conditions: value is a positive float			#
			if 0 <= final <= value:					# Post-Conditions: Score of final goes to main			#
				break						#################################################################
			else:
				print("Please enter a valid score. (between 0 and "+str(value)+")")
		except ValueError:
			print("Please enter a valid score.")
	return final

def calc_weighted_avg(scores, value, weight):				#############################################################################################################
	if weight > 0:							# Function Name: calc_weighted_avg									    #
		avg = (sum(scores) / sum(value)) * weight		# Description: Calculates the weighted average of a category.						    #
	else:								# Parameters: scores - array of scores, value - array of values, weight of category			    #
		avg = 0							# Return Values: A positive float 									    #
	return avg							# Pre-Condtitions: scores is an array of pos floats, value is an array of pos floats, weight is a pos float #
									# Post-Conditions: Weighted avg goes to main								    #
def calc_final(s, v, w):						#############################################################################################################
	final = (s / v) * w
	return final							#################################################################################
									# Function Name: calc_final							#
def calc_grade(a, b, c, d, e):						# Description: Calculates weighted score of final				#
	grade = (a + b + c + d + e)					# Parameters: s - score of final, v - value of final, w - weight of final	#
	return grade							# Return Values: A positive float						#
									# Pre-Conditions: s, v, and w are all positive floats				#
									# Post-Conditions: Weighted final goes to main					#
main()									#################################################################################
		
#################################################################################
# Function Name: calc_grade							#
# Description: Calculates the total grade in class				#
# Parameters: a, b, c, d, and e are all of the weighted avgs of the categories	#
# Return Values: A positive float between 0 and 100				#
# Pre-Conditions: a, b, c, d, and e are all positive floats between 0 and 100	#
# Post-Conditions: Final class grade goes back to main				#
#################################################################################
