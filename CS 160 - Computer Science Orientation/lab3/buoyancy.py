import math
def shapes():
	cont = True
	while (cont):
		y=62.4
		r=input("Enter the radius of your sphere: ");
		try: 
			val = float(r)
			r = float(r)
			if r > 0:
				while (cont):
					w=input("Enter the weight of your sphere: ");
					try:
						val = float(w)
						w = float(w)
						if w > 0:
							r = float(r)
							w = float(w)
							v=(4/3)*(math.pi)*r**3;
							F=v*y;
							print(F);
							if(F>=w):
									print("This sphere will float.");
							else:
								print("This sphere will sink.");
							while (cont):	
								answer = input("Would you like to use this program again? Yes - 1 or No - 0: "); 
								if answer in ("1", "0"): 
									break		
								print("Please enter 1 for yes or 0 for no.");
							if answer == "1":
								shapes()
							else:
								print("Thanks for using this program. Good bye.");		
							cont = False
						else:
							print("Please enter a valid number.")
							continue
					except ValueError:
						print("Please enter a valid number.")
						continue
			else:
				print("Please enter a valid number.")
				continue
		except ValueError:
			print("Please enter a valid number.")
			continue
	
shapes()	
