coupons = input("How many coupons do you have? ");
candy = int(coupons)//10;
gumball = (int(coupons) % 10)//3;
if int(coupons) < 0:
	print("You can't have negative coupons...")
else :
	print("You can get "+str(candy)+" candy bars and "+str(gumball)+" gumballs with "+str(coupons)+" coupons.");


