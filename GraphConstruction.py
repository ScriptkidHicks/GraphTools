"""
This is the tool for in-taking your description of a graph from a file
There will be a couple of ways that you can structure your file to
accommodate this tool, and the tool will intake arguments from the
command line about what type of file you are feeding it. The tool
then constructs a graph object from the information you've fed it,
and passes the information it stores in a pickle file of the same
prefix name as the .txt file you fed it. This can be overridden
with the -r tag, which will instruct python that you intend to
give the pickle file a different name. Once you have the pickle
file, you can implement the other tools on that file at your
choosing. Hope this tool helps students everywhere.

First File Format:
specified by the -EdgeList tag
The first line of your file should be the number of edges
in the graph
the remaining lines of the file should be formatted as
starting node (space) ending node (space) weight
Here's an example:

12
0 3 14
1 2 8
...

Note: you can override the weight requirement by using the tag
-weight=False, and you can specify that it is an undirected graph
by using the tag -directed=False

Second File Format:
specified by the -matrix tag (not compatible with the -directed=False
tag
The first line should be a single number that is the number of
vertecies in the graph. If you give an inaccurate number of nodes
the tool will crash or not intake your entire graph. The remainder
of the file should be lines representing rows, and should be
separated by commas. The vertical line (left hand) represents 'from'
and the horizontal (top) represents 'to'. The nodes will be assigned
values on a scale from 0 to n, where n in the integer you passed in
less one. If there is no edge between two nodes you can Leave either
None or INF in that slot. This is assumed to be a weighted graph.
It is also assumed that there is a maximum of 1 edge between 2 points,
and that nodes do not have edges to themselves.
Here's an example:

4
  0  ,  5  , INF , -1
  3  ,  0  , INF , -3
 -2  , INF ,  0  ,  1
  7  ,  8  , INF ,  0
"""

import sys
import pickle
import os

if __name__ == '__main__':

    Weighted = True
    Directed = True

    Matrix = False
    EdgeList = False


    if len(sys.argv) < 2:
        sys.stdout.write("Please provide at least two arguments: -TypeTag filename.txt")
        sys.exit(2)

    for x in range(len(sys.argv)):
        if sys.argv[x].startswith('-'):
            if sys.argv[x].lower() == "-matrix":
                Matrix = True
            elif sys.argv[x].lower() == "-edgelist":
                EdgeList = True
            elif sys.argv[x].lower() == "-weight=false":
                Weighted = False
            elif sys.argv[x].lower() == "-directed=false":
                Directed = False

    if Matrix == EdgeList:
        sys.stdout.write("You must select either Matrix or Edgelist, but neither or both.")
        sys.exit(2)
