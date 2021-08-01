# Algorithms-research
A project durring a course Algorithm 2 at computer science.

# Guidelines: random graph Erdos- Renyi model.

Background to the task:
Random graphs help analyze complex networks. In a random graph the amounts of nodes and arcs are random variables
Defined by a given probabilistic model.
In this exercise we will explore features of unintentional random graphs in the Erdesh-Rinia model.
In this model the number of nodes in the graph (we will mark it in V) is fixed and given in advance. However, each side between a pair of nodes will appear in the graph
In a probability p independent of the other sides, where p - is a parameter of the model.

# Purpose of the task:
In this exercise we will implement a function to create random graphs and in addition we will build auxiliary functions that will help to explore features of
The graphs.
We will examine the following 3 properties of random graphs in a graph with V nodes (V is a large enough):

1. connectivity- Threshold1 = (lnV / V) :<br>
  If Threshold1 < probability then the graph does not connected with high probability,
  And if Threshold1 > probability then the graph connected at high probability.

2. graph diameter- Threshold2 =  sqrt(2lnV/V) :<br>
  if Threshold2 > probability then in high probability the graph diameter is equal to 2.
  Otherwise the diameter of the graph is greater than 2.  
  
3.Isolated node- Threshold3 = (lnV / V) :<br>
  If Threshold3 < probability then in high probability there is an isolated node graph
  And if Threshold3 > probability then in high probability does not exist in the graph of an isolated node.
  
# Simulations:

In this section we would like to test the properties of random graphs with the help of simulation.
For each of the 3,2,1 features:<br>
Choose a list of 10 possible values for probability - so that half arrays probability will be larger than the Threshold and half arrays will be
Smaller than it.  (For each of the 3 features)
500 random graphs must be drawn for V = 1000 and for each of the probabilities. Total 5000 per feature (count several)
Graphs maintain the feature and some do not.
It is worth estimating the probability that a trait exists. It is possible to calculate a ratio between the number of graphs that sustain the trait and the quantity
The total of the graphs. Results of simulations can be saved in a file - for example a CSV file. The file can be opened
Then in EXCEL and build graphs to help summarize work results.
  
# Result for the research:
![IsIsolated](https://user-images.githubusercontent.com/68068799/127785302-eaa6b96b-f07f-457f-ae05-8ae1b500f818.png)

![Diameter](https://user-images.githubusercontent.com/68068799/127785304-a4debe02-7bf7-43b8-987e-1914cec3ffe1.png)

![Connectivity](https://user-images.githubusercontent.com/68068799/127785306-455e3135-68d9-4fe0-a16c-7fe97d106edd.png)
