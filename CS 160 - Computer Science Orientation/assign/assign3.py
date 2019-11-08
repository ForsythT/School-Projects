while True:
	operation = input("Enter an operation you would like to use (+, -, *, /, //, %, **): ");

	if str(operation) == "+" :
		num1 = int(input("Enter your first number: "));
		num2 = int(input("Enter the number you would like to add to "+str(num1)+": "));		
		print(num1+num2);
	elif str(operation) == "-" :

		num1 = int(input("Enter your first number: "));
		num2 = int(input("Enter the number you would like to subtract from "+str(num1)+": "));
		print(num1-num2);
	elif str(operation) == "*" :
		num1 = int(input("Enter your first number: "));
		num2 = int(input("Enter the number you would like to multiple "+str(num1)+" by: "));
		print(num1*num2);
	elif str(operation) == "/" :
		num1 = int(input("Enter your first number: "));
		num2 = int(input("Enter the number you would like to divide "+str(num1)+" by: "));
		print(num1/num2);
	elif str(operation) == "//" :
		num1 = int(input("Enter your first number: "));
		num2 = int(input("Enter the number you would like to divide "+str(num1)+" by: "));	
		print(num1//num2);
	elif str(operation) == "%" :
		num1 = int(input("Enter your first number: "));
		num2 = int(input("Enter the number you would like to divide "+str(num1)+" by to find the remainder: "));
		print(num1%num2);
	elif str(operation) == "**" :
		num1 = int(input("Enter your first number: "));
		num2 = int(input("Enter the exponent: "));
		print(num1**num2);
	else :
		print("Invalid operation. Please try again.");
		continue
	while True :	
		answer = input("Would you like to use the calculator again? Yes - y or No - n: ");
		if answer in ("y", "n"):
			break
		print("Please enter 'y' for Yes or 'n' for No (case sensitive).");
	if str(answer) == "y" :
		continue
	else :
		print("Thanks for using this calculator. Good bye.");
		break


