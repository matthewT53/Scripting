#!/usr/bin/python3.5

import sys
import re
from collections import defaultdict

connections = defaultdict(dict)
neighbourNodes = set()

regex = r"([^\s]*) ([^\s]*)"
for line in sys.stdin:
    match = re.search(regex, line)
    if match:
        node1 = match.group(1)
        node2 = match.group(2)
        connections[node1][node2] = 1
        neighbourNodes.add(node1)
        neighbourNodes.add(node2)
        print("node1 = " + node1 + " node2 = " + node2)

# BFS algorithm
visited = defaultdict(lambda: 0)
startNode = sys.argv[1]
queue = []
queue.append(startNode)

for node in queue:
    curNode = node
    for neighbour in neighbourNodes:
        if connections[curNode][neighbour] == 1 and visited[neighbour] == 0
