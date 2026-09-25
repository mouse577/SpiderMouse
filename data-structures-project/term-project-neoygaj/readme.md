# CSPB 2270 – Data Structures - Term Project
## Overview
The purpose of this data structure is to organize information associated with mice that are used in experiments, and projects that use data from certain experiments from different mice, as well as projects that are associated with certain experiments.  Each mouse may have several experiments, and a particular project may only use data from one, a few, or all experiments from a particular mouse.

The object class is named "SpiderMouse", with struct spiderNode.  There are 19 public member functions.  Some of the functions are redundant, with one version as a void function and another version that returns a pointer or a vector of pointers.  Also, to search for a particular mouse node, one version takes IDtag as an input parameter and another version takes startDate as an input parameter.  There are also 2 print functions that print the details for all mice in the private member vectors mouseList and projList.  There is also a function to build a real-life example of a SpiderNode object and a master function that prompts the user for input selections to build or modify a spider node object and runs the member functions based on the user input. 

This project implements an ADT with a 3 types of a node structure that are connected to each other by adding pointers to the nodes in vectors, which are part of the node structure.  This ADT is similar to a graph, but lacks an edge structure.  There is one node structure with a variable nodeType, which defines whether the node is type mouse, experiment or project.

Each node has a vector of shared pointers to another node type that it is associated with.  The mouse node has a vector of pointers to experiment nodes, with information about experiments that were performed on that mouse.  The experiment node has a vector of pointers to project nodes that it is associated with, and the project node has a vector of pointers to experiments that it is associated with.

In addition, there are two private member vectors, one with pointers to all mice in the object and one with pointers to all projects in the object.  These facilitate searching for particular mice or projects and from there, the vector of pointers to experiments associated with the mouse or project node can be searched to find a particular experiment node.

To run the code, navigate to the build directory and enter "cmake .." , then enter "make".  To run the tests, enter "./run_tests".  To use the interactive function, enter "run_app" and follow the prompts to input information and to view details about mice, experiments or projects.


