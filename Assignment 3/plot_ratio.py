import matplotlib.pyplot as plt
import math

x_axis = [2, 3, 5, 10, 15, 20]

file = open("ratio.txt", "r")
y_axis = []
for line in file:
	y_axis.append(float(line))
plt.plot(x_axis, y_axis, "ro-", label="Ratio")

plt.title("Ratio of distances of 2nd closest and 100th closest point (100NN)")
plt.xlabel("Dimension of points")
plt.ylabel("Ratio")
plt.grid(True)
plt.legend(loc='upper left')

plt.show()