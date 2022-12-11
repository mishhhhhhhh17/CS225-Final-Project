# CS225-Final-Project Results

The output of our BFS algorithm is a vector of all the incident Nodes for which the totalLoss variable falls within a given range of the search target. We tested that the algorithm works as intended in tests-part3.cpp by running findByLoss(double, double) on a sample dataset of 9 variables. We intentionally wrote the dataset with easily computible totalLoss variables. Our test cases try a variety of targets with a variety of ranges, and check if the resulting vector contains the correct incident nodes.

The output of our Prim's algorithm is the minimum spanning tree of the graph. We test that the algorithm works in tests-part1.cpp by creating a graph from the test dataset bfs_test_data.csv, and accessing each node to make sure that it was initialized correctly.

To check that we were accurately plotting points on the map, we inputted 
the region list in the original dataset against used online resources to check that the points we plotted on the map were being plotted in the correct location. 