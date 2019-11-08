import sys, re
from math import log10 
from collections import defaultdict

flatten = lambda l: [item for sublist in l for item in sublist]

def processWord(word):
	word = re.sub("[']", '', word.lower())
	word = re.sub("[^\w]", '', word)
	return word

def processSentence(sentence):
	return ([processWord(word) for word in sentence.split()][:-1], int(sentence.split()[-1]))

def createFeature(sentence, vocab):
	feature = []
	for word in vocab:
		if word in sentence[0]:
			feature.append(1)
		else:
			feature.append(0)
	feature.append(int(sentence[1]))
	return feature

def outputFeatures(vocab, features, outputf):
	outf = open(outputf, 'w')
	[outf.write(word + ",") for word in vocab]
	for feature in features:
		outf.write(str(feature)[1:-1])
		outf.write('\n')
	outf.close()

def testFeature(vocab, feature):
	sentence = [vocab[i] for i in range(len(feature)-1) if feature[i]]
	return sentence

def preprocess(inputf, outputf):
	#Get the raw sentences from the input file
	inf = open(inputf, 'r')	
	rawSentences = inf.read().splitlines()
	
	#Process and clean up the sentences
	sentences = [processSentence(sentence) for sentence in rawSentences]
	inf.close()
	
	#Set up the vocab
	vocab = {processWord(word) for sentence in rawSentences for word in sentence.split()[:-1]}
	vocab.discard('')
	vocab = sorted(vocab)

	#Get and output the features to an output file
	features = [createFeature(sentence, vocab) for sentence in sentences]
	outputFeatures(vocab, features, outputf)
	testSentence = testFeature(vocab, features[0])

	return vocab, sentences

def train(vocab, sentences, classes):
	prior = {}
	probability = defaultdict(dict)
	flatSent = {}

	def getPrior(sentences, c):
		classSentenceCount = len([sent for sent in sentences if sent[1] == c])
		totalSentenceCount = len(sentences)
		return log10(classSentenceCount / totalSentenceCount)

	def getFlatSent(sentences, c):
		return flatten([sent[0] for sent in sentences if sent[1] == c])

	for c in classes:
		prior[c] = getPrior(sentences, c)
		flatSent[c] = getFlatSent(sentences, c)
		classWordCount = sum([flatSent[c].count(word) for word in vocab])

		for word in vocab:
			wordCount = flatSent[c].count(word)
			probability[word][c] = log10((wordCount + 1) / (classWordCount + len(vocab)))

	return prior, probability

def classify(sentence, prior, probability, classes, vocab):
	sentence = [word for word in sentence[0] if word in vocab]
	prob = {}

	for c in classes:
		prob[c] = prior[c]
		for word in sentence:
			prob[c] = prob[c] + probability[word][c]

	return max(prob.keys(), key=(lambda key: prob[key]))

def printResults(results, testSents):
	incorrectSents = []
	for result, sent in zip(results, testSents):
		if result != sent[1]:
			incorrectSents.append(sent + tuple([result]))

	print("\n")
	print("=============================")
	print("= Incorrect Classifications =")
	print("=============================")
	for sent in incorrectSents:
		print('incorrect {}: guessed class: {}, actual class: {}'.format(sent[0], sent[2], sent[1]))

	correct = len(testSents) - len(incorrectSents)
	incorrect = len(incorrectSents)
	accuracy = (correct / len(testSents))*100

	print("\n")
	print("===================")
	print("= RESULTS:")
	print("= Correct:   {}".format(correct))
	print("= Incorrect: {}".format(incorrect))
	print("=------------------")
	print("= Accuracy:  {}%".format(round(accuracy, 2)))
	print("===================")

def test(testSents, prior, probability, classes, vocab):
	results = []
	for testSent in testSents:
		results.append(classify(testSent, prior, probability, classes, vocab))
	printResults(results, testSents)

def main():
	classes = [0, 1]
	#Redirect stdout to the results file
	sys.stdout = open('results.txt', 'wt')

	#Testing on training data
	vocab, sentences = preprocess('trainingSet.txt', 'preprocessed_train.txt')
	prior, probability = train(vocab, sentences, classes)

	print("============================")
	print("= Testing on training data =")
	print("============================")
	test(sentences, prior, probability, classes, vocab)

	# perform test on the testing data
	_, sentences = preprocess('testSet.txt', 'preprocessed_test.txt')

	print("\n")
	print("===========================")
	print("= Testing on testing data =")
	print("===========================")
	test(sentences, prior, probability, classes, vocab)

if __name__ == '__main__':
	main()
