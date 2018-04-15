import matplotlib.pyplot as plt
import math

x_axis = [2, 3, 5, 10, 15, 20]

file1 = open("seqscan_time.txt", "r")
y_axis_1 = []
for line in file1:
	y_axis_1.append(float(line))
plt.plot(x_axis, y_axis_1, "bo-", label="SequentialScan")

file2 = open("bestfirstsearch_time.txt", "r")
y_axis_2 = []
for line in file2:
	y_axis_2.append(float(line))
plt.plot(x_axis, y_axis_2, "rx-", label="BestFirstSearch")

plt.title("Average running time per query")
plt.xlabel("Dimension of points")
plt.ylabel("Time for finding 20NN (without O3 optimisation)")
plt.grid(True)
plt.legend(loc='upper left')

plt.show()