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
specified by the -edges tag
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
"""