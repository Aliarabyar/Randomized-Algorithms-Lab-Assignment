**An Exploratory Assignment on Minimum Spanning Trees Mitzenmatcher-Upfal book - Assignment 10.6.**

 
The goal is to define a function $f(n)$ to calculate the total weight of the $\operatorname{MST}$ of a complete graph with  edges which weigh of each edge has been chosen uniformly at random on $[0,1]$. I used $C$ to implement Kruskal's algorithm to find a minimum spanning tree for a weighted graph. To implement the random graph generator, I used C's built-in rand() function and seeded it with a value of my machine's local time.
Choice of MST Algorithm
There are two choices for choosing an algorithm for the graphs that are weighted, connected, and undirected: Kruskal's algorithm and Prim's algorithm.

I decided to choose Kruskal's algorithm because I realize| that its runtime performance would be much faster than Prim's algorithm for sparse graphs. The barrier will be sorting all the edges with Kruskal's algorithm, but I would simply take the shortest of the remaining ones after that. I figured out that the cost of sorting edges that should be done in Kruskal's algorithm would be much lower than the repeated searching we would have to do with Prim's algorithm. If I were to use Prim's algorithm, I would have to look at all vertices linked to the MST, and it would be very time consuming to loop repeatedly through all the edges. Therefore, I finally ended up using Kruskal's algorithm.
