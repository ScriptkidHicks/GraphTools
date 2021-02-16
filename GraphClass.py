"""
This file contains the graph and node class, which will be implemented
for most other methods and tools. If you're doing any moding of this
open source work, please don't futz around with this particular class
setup, as it could break everything else. This is a tool meant to
be accessed indirectly.
"""
import sys


class Node:
    """
    Node Class Object
        This object is stored inside the graph class, and contains
        references to all of its children.
    """

    def __init__(self):
        """
        Neither edges nor children are integral to the functioning of
        this class. Either or both can be deployed as the task demands
        """
        self.name = None
        self.children = {}
        self.edges = {}

    def add_child(self, child_and_weight:tuple):
        self.children[child_and_weight[0]] = child_and_weight[1]

    def add_children(self, children_and_weights: list):
        for child in children_and_weights:
            self.children[child[0]] = child[1]

    def remove_child(self, child):
        del self.children[child]

    def remove_children(self, children):
        for child in children:
            del self.children[child]

    def empty_children(self):
        self.children = {}


class Edge:
    """
    Edge Class Object
    Used to store information about edges, and the nodes on
    either end. Contained within the graph and/or the node
    class.

    vNode refers to the parent node in a directed graph
    uNode refers to the child node in a directed graph
    """
    def __init__(self, v_node: Node = None, u_node: Node = None, name: str = None, weight: int = 1):
        self.Name = name
        self.vNode = v_node
        self.uNode = u_node
        self.Weight = weight

    def change_weight(self, weight: int):
        self.Weight = weight

    def adoption(self, new_parent: Node):
        self.vNode = new_parent

    def disown(self, new_child: Node):
        self.uNode = new_child


class Graph:
    """
    Graph Class Object
    Used to store information about the graph as a whole.
    Information about Edges or Nodes can be implemented as
    necessary to complete tasks. The TotalWeight paramenter
    is the sum of all weights of edges in the graph.
    Potentially useful in the future. Name variable exists
    so that multiple graphs can be distinguished between.
    Negative Cycles initiated as None, and can be changed
    by other methods as necessary.
    """
    def __init__(self):
        self.Name = None
        self.Edges = {}
        self.Nodes = {}
        self.TotalWeight = None
        self.NegativeCycles = None

    def weigh_by_edges(self):
        total = 0
        for edge in self.Edges:
            total += edge.weight
        self.TotalWeight = total

    def __add__(self, other):
        if type(other) is Node:
            self.Nodes[other.Name] = other
        elif type(other) is Edge:
            self.Edges[other.Name] = other
        else:
            sys.stdout.write("an object was passed into a graph that was neither a Node nor an Edge\n"
                             "Please feed only node or edge objects to the graph object.")

    def add_child(self, child):
        if type(child) is Node:
            self.Nodes[child.Name] = child
        elif type(child) is Edge:
            self.Edges[child.Name] = child
        else:
            sys.stdout.write("an object was passed into a graph that was neither a Node nor an Edge\n"
                             "Please feed only node or edge objects to the graph object.")

    def __sub__(self, other):
        if type(other) is Node:
           del self.Nodes[other.Name]
        elif type(other) is Edge:
            del self.Edges[other.Name]
        else:
            sys.stdout.write("an object was passed into a graph that was neither a Node nor an Edge\n"
                             "Please feed only node or edge objects to the graph object.")

    def remove_child(self, child):
        if type(child) is Node:
            del self.Nodes[child.Name]
        elif type(child) is Edge:
            del self.Edges[child.Name]
        else:
            sys.stdout.write("an object was passed into a graph that was neither a Node nor an Edge\n"
                             "Please feed only node or edge objects to the graph object.")
