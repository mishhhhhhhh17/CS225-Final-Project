# CS225-Final-Project
Fall 2022 CS 225 UIUC
Introduction:
Our project uses a dataset that records cases of missing migrants from 2014 to 2022, including the number of males, females, and children on the trip, the geographical coordinates of the location at which they went missing, the total number of missing or dead (which we refer to as the total number of losses), among other variables. We cleaned the dataset to include only cases from 2022, and limited to the variables to those listed above, combining the number of dead and missing as well as number of survivors into 1 variable, totalMigrants. Our graph connects incidents within 750km of each other, and keeps track of the incident with the lowest percentage of lost migrants. The goal of our project was to create a search tool that plots incidents within a given range of a target loss on a map.

Github Organization:
We referred to course MPs as a template for organizing our github repository.
All csv files including the missing migrants data file which we downloaded from https://www.kaggle.com/code/methoomirza/eda-missing-migrants-2014-2022/data?select=MissingMigrants-Global-2022.csv and cleaned to fit the goals of our project, and csv files we created for testing our code are located in the "data" folder.
The "entry" folder contains the main file from which the user can run functions.
The "lib" folder includes the HSLAPixel and PNG classes which we use to plot points on PNG images of a map.
The "src" folder contains the graph .h and .cpp files which contain the definition and implementation of our graph data structure and graph algorithms; the utilities .h and .cpp files which contain functions to clean the data set and helper functions for reading the csv into the graph data structure; and the Animation .h and .cpp files which we appropriated from MP Traversals to animate plotting points on the map.
The "tests" folder contains tests_part1 which tests that we are parsing the CSV correctly and tests our implementation of Prim's algorithm; tests_part2 which tests that the constructor accurately initializes the graph; and tests_part3 which tests out BFS algorithm and that we plot points onto the map PNG accurately.
The makefile is inside the CS225-Final-Project folder, and was written based on the makefiles provided in previous MPs.

Running Instructions:
In main, the user must first initialize the graph from the dataset included in the "data" folder. Our constructor creates the graph. The user can plot the results of their queries by calling plotPointsOnMap and pathsOnMap.
The second main component of our program is a BFS search function findByLoss which traverses the graph and returns a vector of all the incidents which reported a total loss within a given range of a target.