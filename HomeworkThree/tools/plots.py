import pandas as pd
import matplotlib.pyplot as plt

Euler10k = pd.read_csv("../data/euler_10k.csv")
Euler100k = pd.read_csv("../data/euler_100k.csv")
EulerCromer10k = pd.read_csv("../data/eulercromer_10k.csv")
EulerCromer100k = pd.read_csv("../data/eulercromer_100k.csv")

fig, ax = plt.subplots()
ax.set_title("Comparison of ODE solutions")

ax.plot(Euler10k['x'], Euler10k['y'],
        label = "Euler method 10k points")
ax.plot(Euler100k['x'], Euler100k['y'],
        label = "Euler method 100k points")
ax.plot(EulerCromer10k['x'], EulerCromer10k['y'],
        label = "Euler-Cromer 10k points")
ax.plot(EulerCromer100k['x'], EulerCromer100k['y'],
        label = "Euler-Cromer 100k points")

ax.legend()

fig.savefig("../data/plot.jpeg")
