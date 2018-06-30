# README File 

The purpose of this assignment was to compare the performance (in terms of running times) of two popular approaches of finding the k-Nearest Neighbours - ***Sequential Scan*** algorithm, where we simply iterate over the dataset and find the kNN, and the ***Best First Search*** algorithm, in which we make use of the **kD-Tree** data structure to prune off our search space. For this assignment, we compare the performance of the two algorithms by computing the result of a *20NN query* over datasets of different dimensions. The plot can be observed in *running_time.png*. 

In addition, for 100NN queries we also observe the ratio of the second closest neighbour to the 100th closest neighbour (in other words the farthest neighbour) across different dimensions (plot is available as the file *distance_ratio.png*) and try to explain the observations (please refer to **Assignment 3 Report.pdf**).

If you wish to run this test yourself, please follow the procedures given below.

1. Run pip install -r requirements.txt

2. To generate the datasets and querysets, run:
	* g++ -o generate_dataset generate_dataset.cpp -no-pie; ./generate_dataset
	* g++ -o generate_queryset generate_queryset.cpp -no-pie; ./generate_queryset

Now we can start the analysis!

3. Run the following:
	* chmod +x part_a.sh
	* ./part_a.sh

This will take some time, but after this step, you can observe the plot of the running times of the two algorithms.

4. Run the following:
	* chmod +x part_b.sh
	* ./part_b.sh

This will let you observe the plot of the distance ratio, as explained before.

Both the plots will also be saved on your disk. They will be saved in the folder where you will be executing the program. 

To know more about what exactly "Part A" and "Part B" mean, refer to **Assignment 3.pdf** which contains the problem statement.

If you have any other query, please mail to utkarsh101097@gmail.com 