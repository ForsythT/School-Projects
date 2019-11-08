word = input("Enter a word: ")
if word.isalpha:
	z = 0
	print(word[0])
	print(word[len(word)-1])
	for x in range (len(word)):
		print (word[z])
		z += 1 
