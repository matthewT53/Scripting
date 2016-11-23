#!/usr/local/bin/python3.5
import re
import sys
from collections import defaultdict
from collections import deque

# get the starting town and end town that we want to compute the distance for
argList = sys.argv
startingTown = argList[1]
endTown = argList[2]

#print ("Finding the shortest distance between: " + startingTown + " and: " + endTown)

# constant for infinite distance
max = 9999999999

# create hash table to store all the distances
townDistances = defaultdict(dict)
regexSplit = r" "
neighbourTowns = set() # create an empty set to store the neighbouring towns

# read the distances between the towns
for line in sys.stdin:
    line = re.sub(r" +", " ", line)
    line = re.sub(r"\n", "", line)
    inputs = re.split(regexSplit, line)
    #print (inputs)
    town1 = inputs[0]
    town2 = inputs[1]
    townDistances[town1][town2] = int(inputs[2])
    townDistances[town2][town1] = int(inputs[2])
    neighbourTowns.add(town1)
    neighbourTowns.add(town2)
    #print ("You entered: ", town1, town2, distance)

# now calculate the shortest distane between startingTown and endTown
visited = defaultdict(lambda: 0)

neighbourTowns.remove(startingTown)
neighbourTowns = sorted(neighbourTowns)
#print ("Neighbouring towns set:")
#print (neighbourTowns)

# store the towns we need to explore
queueList = []
queueList.append(startingTown)

# information about distances
pred = defaultdict(dict)
pred[startingTown] = startingTown
bestDistances = defaultdict(lambda: max)
bestDistances[startingTown] = 0

# Lazy to do it script way so just used Dijkstra's algorithm
for town in queueList:
    # pop a town to visit from the queue
    currentTown = town
    #print ("\nPopped: " + currentTown)
    #print ("From start of loop: ")
    #print (queueList)

    # traverse through neighbouring towns
    for potentialNeighbour in neighbourTowns:
        # make sure potentialNeighbour is actually a neighbour (could not be connected)
        if not potentialNeighbour in townDistances.get(currentTown, {}):
            continue

        # just a case that needs to be handled
        if potentialNeighbour == startingTown:
            continue

        currentDistance = bestDistances[currentTown]
        edgeDistance = townDistances[currentTown][potentialNeighbour]
        # edge relaxation, finding a better distance
        # print ("currentDistance = " + str(currentDistance) + " edgeDistance: " + str(edgeDistance) + " best: " + str(bestDistances[potentialNeighbour]))
        if currentDistance + edgeDistance < bestDistances[potentialNeighbour]:
            pred[potentialNeighbour] = currentTown
            bestDistances[potentialNeighbour] = currentDistance + edgeDistance
            queueList.append(potentialNeighbour)
            #print ("Adding neighbour to queue: " + potentialNeighbour)

    # marked the popped town as visited
    #print ("From end of loop: ")
    #print (queueList)
    visited[currentTown] = 1

# print the results
print ("Shortest route is length = %d:" % (bestDistances[endTown]), end="") # print without a newline
previousTown = endTown
route = []
route.append(previousTown)
while previousTown != startingTown:
    previousTown = pred[previousTown]
    route.append(previousTown)

route.reverse()
for town in route:
    print (" %s" % (town), end="")

# print a newline
print (".")
