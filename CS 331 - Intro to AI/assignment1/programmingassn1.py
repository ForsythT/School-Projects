# Tim Forsyth
# 932711331
# Python informational sources used:
# http://www.pythonforbeginners.com/files/reading-and-writing-files-in-python
# https://www.python-course.eu/lambda.php
# https://stackoverflow.com/questions/4843158/check-if-a-python-list-item-contains-a-string-inside-another-string?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
# https://docs.python.org/3/library/collections.html#collections.deque

import sys
import heapq
import collections

nodesExpanded = 0

# The the moves of chickens/wolves. They are expanded in this order:
# 1 chicken, 2 chickens, 1 wolf, 1 chicken 1 wolf, 2 wolves
# In the form of [chickens, wolves]
potentialMoves = [[1,0],[2,0],[0,1],[1,1],[0,2]]

class Node():
	def __init__(self, left, right, depth, cost, move, parent):
		self.left = left
		self.right = right
		self.depth = depth
		self.cost = cost
		self.move = move
		self.parent = parent

		self.state = tuple(self.left + self.right)

class PriorityQ():
	def __init__(self):
		self._queue = []
		self._index = 0

	def __len__(self):
		return len(self._queue)

	def push(self, item, priority):
		heapq.heappush(self._queue, (priority, self._index, item))
		self._index += 1

	def pop(self):
		return heapq.heappop(self._queue)[-1]

def main():
	# List of all possible search modes for this assignment
	searchModes = ["bfs","dfs","iddfs","astar"]

	# Storing the command line arguments into variables
	startStateFile = sys.argv[1]
	goalStateFile = sys.argv[2]
	mode = sys.argv[3]
	outputFile = sys.argv[4]

	# Getting start and goal state data from the files
	startStateData = getFileData(startStateFile)
	goalStateData = getFileData(goalStateFile)

	# Make the start and goal states by stripping the newlines and splitting the numbers.
	startState = Node(map(int, startStateData[0].strip('\n').split(',')), map(int, startStateData[1].strip('\n').split(',')), 0, 0, None, None)
	goalState = Node(map(int, goalStateData[0].strip('\n').split(',')), map(int, goalStateData[1].strip('\n').split(',')), 0, 0, None, None)

	# Checks if the mode is in the list of search modes and then executes the search function for the mode
	if mode in searchModes:
		if mode == "bfs":
			fringe = collections.deque()
			finalState = breadthFirstSearch(fringe, startState, goalState)
		elif mode == "dfs":
			fringe = collections.deque()
			finalState = depthFirstSearch(fringe, startState, goalState)
		elif mode == "iddfs":
			fringe = collections.deque()
			finalState = iterativeDeepDFS(fringe, startState, goalState)
		elif mode == "astar":
			fringe = PriorityQ()
			finalState = aStarSearch(fringe, startState, goalState)
		else:
			sys.exit("Search Mode Does Not Exist.")


	#printPath(startState)
	#printPath(goalState)
	# Print out the consecutive states that it took to reach the goal
	if finalState == None:
		print "No solution found"
		print "Total Expanded Nodes: {0}".format(nodesExpanded)
	else:
		print mode
		printPath(finalState, startState)

		# Write the solution path of states to the output file
		fh = open(outputFile, 'w')
		path = nodePath(finalState)
	
		fh.write("%s\n" % mode)
		fh.write("%s,%s,%s ; %s,%s,%s\n" % (startState.left[0], startState.left[1], startState.left[2], startState.right[0], startState.right[1], startState.right[2]))
		for x in reversed(range(len(path))):
			fh.write("%s,%s,%s ; %s,%s,%s\n" % (path[x].left[0], path[x].left[1], path[x].left[2], path[x].right[0], path[x].right[1], path[x].right[2]))
		fh.write("Total Expanded Nodes: %s\n" % (nodesExpanded)) 
		fh.write("Solution Path Length: %s\n" % (len(path)))
		fh.close()

def printPath(node, root):
	path = nodePath(node)

	# Print the root first (start state)
	print "{0},{1},{2} ; {3},{4},{5}".format(root.left[0], root.left[1], root.left[2], root.right[0], root.right[1], root.right[2])
	for x in reversed(range(len(path))):
		print "{0},{1},{2} ; {3},{4},{5}".format(path[x].left[0], path[x].left[1], path[x].left[2], path[x].right[0], path[x].right[1], path[x].right[2])
	print "Total Expanded Nodes: {0}".format(nodesExpanded)
	print "Solution Path Length: {0}".format(len(path))

def nodePath(node):
	path = []
	current = node
	while True:
		try:
			if current.parent != None:
				path.append(current)
		except:
			break
		current = current.parent
	
	return path

def getFileData(fileToRead):
	fh = open(fileToRead, 'r')
	data = fh.readlines()
	return data

def breadthFirstSearch(fringe, startState, goalState):
	global nodesExpanded
	
	# A dictionary for the nodes already visited
	visitedNodes = {}

	fringe.append(startState)

	while True:
		if len(fringe) == 0:
			return None

		# Pop left most element of fringe, FIFO
		current = fringe.popleft()

		# Check for the victory/goal condition
		if (current.left == goalState.left) and (current.right == goalState.right):
			return current
	
		if current.state in visitedNodes and current.depth >= visitedNodes[current.state]:
			continue
		else:
			visitedNodes[current.state] = current.depth
			map(fringe.append, expandNode(current))
			nodesExpanded += 1
		
def depthFirstSearch(fringe, startState, goalState):
	global nodesExpanded

	visitedNodes = {}

	fringe.append(startState)
	
	while True:
		if len(fringe) == 0:
			return None

		# Pop right most element of fringe, LIFO
		current = fringe.pop()

		# Check for the victory/goal condition
		if (current.left == goalState.left) and (current.right == goalState.right):
			return current
	
		# Check the hash table for duplicate nodes
		if current.state in visitedNodes and current.depth >= visitedNodes[current.state]:
			continue
		else:
			visitedNodes[current.state] = current.depth
			map(fringe.append, expandNode(current))
			nodesExpanded += 1

def iterativeDeepDFS(fringe, startState, goalState):
	maxDepth = 1
	goal = depthLimitedSearch(fringe, startState, goalState, maxDepth)
	while goal == None:
		if maxDepth > 500:
			sys.exit("Exceeded Depth Limit")
		maxDepth += 1
		goal = depthLimitedSearch(fringe, startState, goalState, maxDepth)
		continue

	return goal	

def depthLimitedSearch(fringe, startState, goalState, maxDepth):
	global nodesExpanded

	visitedNodes = {}

	fringe.append(startState)
	
	while True:
		if len(fringe) == 0:
			return None

		# Pop right most element of fringe, LIFO
		current = fringe.pop()

		# Check for the victory/goal condition
		if (current.left == goalState.left) and (current.right == goalState.right):
			return current
	
		# Check the hash table for duplicate nodes
		if current.state in visitedNodes and current.depth >= visitedNodes[current.state]:
			continue
		else:
			# Don't expand if current depth is passed the maximum depth set
			if current.depth > maxDepth:
				continue
			visitedNodes[current.state] = current.depth
			map(fringe.append, expandNode(current))
			nodesExpanded += 1

def aStarSearch(fringe, startState, goalState):
	global nodesExpanded

	visitedNodes = {}

	fringe.push(startState, startState.cost)

	while True:
		if len(fringe) == 0:
			return None

		# Pop right most element of fringe, LIFO
		current = fringe.pop()
		
		# Check for the victory/goal condition
		if (current.left == goalState.left) and (current.right == goalState.right):
			return current
	
		# Check the hash table for duplicate nodes
		if current.state in visitedNodes and current.depth >= visitedNodes[current.state]:
			continue
		else:
			visitedNodes[current.state] = current.depth
			map(lambda x: fringe.push(x, x.cost + aStarHeuristic(x, goalState)), expandNode(current))
			nodesExpanded += 1

def aStarHeuristic(node, goalState):
	# Check for which side the boat is on at the end
	# The heurstic is to take the # of animals on the starting side / # of animals that can go on the boat at once (2)
	if goalState.left[2] == 1:
		heuristic = ((node.right[0] + node.right[1]) - 1) * 2
	else:
		heuristic = ((node.left[0] + node.left[1]) - 1) * 2

	return heuristic

def expandNode(node):
	global potentialMoves

	# Get a list of legal moves that return true from isValidMove
	validMoves = filter(lambda x: isValidMove(x, node), potentialMoves)

	# Get new nodes created with the legal moves
	succNodes = map(lambda y: doMove(y, node), validMoves)

	return succNodes	

def isValidMove(move, node):
	# Check to find which side the boat is on and then do the move
	if node.left[2] == 1:
		start = list(node.left)
		end = list(node.right)
	else:
		start = list(node.right)
		end = list(node.left)
	
	# No error checking here since we already know the moves are valid
	start[0] = start[0] - move[0]
	start[1] = start[1] - move[1]
	start[2] = 0
	end[0] = end[0] + move[0]
	end[1] = end[1] + move[1]
	end[2] = 1

	# Checks for the case that the # of chickens/wolves at the start or end side are negative (invalid)
	if (start[0] < 0) or (start[1] < 0) or (end[0] < 0) or (end[1] < 0):
		return False
	# Checks for the case that there are more (or equal) chickens than wolves on each side (or there are no chickens) (valid)
	elif ((start[0] == 0) or (start[0] >= start[1])) and ((end[0] == 0) or (end[0] >= end[1])):
		return True
	else:
		return False

def doMove(move, node):	
	# Same as the isValidMove function except it "saves" the move
	# Check to find which side the boat is on and then do the move
	if node.left[2] == 1:
		start = list(node.left)
		end = list(node.right)
	else:
		start = list(node.right)
		end = list(node.left)
	
	# No error checking here since we already know the moves are valid
	start[0] = start[0] - move[0]
	start[1] = start[1] - move[1]
	start[2] = 0
	end[0] = end[0] + move[0]
	end[1] = end[1] + move[1]
	end[2] = 1

	# Check which side the boat starts on and then create the node
	# Left = Start, Right = End
	if node.left[2] == 1:
		newNode = Node(start, end, node.depth + 1, node.depth + 1, move, node)		
	# Left = End, Right = Start
	else:
		newNode = Node(end, start, node.depth + 1, node.depth + 1, move, node)	

	return newNode

main()
