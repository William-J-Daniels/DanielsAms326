import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("../data/implicit_test.csv")

fig, ax = plt.subplots()
ax.plot(data['x'], data['y'])

fig.savefig("../data/implicit_test.jpeg")
