import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("../data/uniform_points.csv")

fig, ax = plt.subplots()
ax.set_title('"Random" numbers')
ax.scatter(data['x'], data['y'], marker='.')

fig.savefig("../data/uniform_points.jpeg")
