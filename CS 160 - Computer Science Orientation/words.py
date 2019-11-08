def main():
	word1 = get_user_input()
	word2 = get_user_input()
	z = num_matching_chars(word1, word2)
	y = percent_matching(word1, word2, z)
	print("The words " + word1 + " and " + word2 + " are " + str(y) + "% similar.")

def get_user_input():
	while True:
		word1 = input("Enter word: ")
		if word1.isalpha():
			return word1
		else: 
			print("Please enter letters.")
			continue

def num_matching_chars(word1, word2):
	y = 0	
	z = 0
	if len(word1) < len(word2):
		for x in range (len(word1)):
			if word1[y] == word2[y]:
				z += 1
			y += 1
	else:
		for x in range (len(word2)):
			if word1[y] == word2[y]:
				z += 1
			y += 1
	return z

def percent_matching(word1, word2, z):
	if len(word1) > len(word2):
		y = z / len(word1) * 100
	else:
		y = z / len(word2) * 100
	return y
main()
