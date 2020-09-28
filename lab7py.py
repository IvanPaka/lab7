from numpy import array, arange, exp, sin, cos, sqrt
from scipy import integrate
import matplotlib.pyplot as plt

data = []
with open("data.dat") as file:
    for line in file:
        data.append([float(line.split(',')[0]), float(line.split(',')[1]), float(line.split(',')[2])])

data = array(data)

x = data[:, 2]

plt.figure(figsize=(16, 9))
plt.title("Решение", fontsize=14)
plt.plot(x, data[:, 0], label="$y(x)$")
plt.plot(x, data[:, 1], label="$y'(x)$")
plt.legend(fontsize=14)
plt.minorticks_on()
plt.grid(which="both")
plt.show()

plt.figure(figsize=(16, 9))
plt.title("Фазовый портрет", fontsize=14)
plt.plot(data[:, 0], data[:, 1])
plt.xlabel("$y(x)$", fontsize=14)
plt.ylabel("$y'(x)$", fontsize=14)
plt.minorticks_on()
plt.grid(which="both")
plt.show()
