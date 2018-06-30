echo -n "Running 20NN queries"
for i in 1 2 3 4 
do
	sleep 0.3
	echo -n "."
done
sleep 1
echo "."
sleep 1
echo -n "Doing sequential scan"
for i in 1 2 3 4 
do
	sleep 0.3
	echo -n "."
done
sleep 1
echo "."
g++ -std=c++14 seqscan.cpp -no-pie
./a.out
echo -n "Doing best first search"
for i in 1 2 3 4 
do
	sleep 0.3
	echo -n "."
done
sleep 1
echo "."
g++ -std=c++14 bestfirstsearch.cpp -no-pie
./a.out
echo "Plotting the graph!"
sleep 2
python3 plot_graph_times.py
rm a.out
rm seqscan_time.txt
rm bestfirstsearch_time.txt
