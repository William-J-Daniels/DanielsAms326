import pandas as pd
import matplotlib.pyplot as plt

Opt = pd.read_csv("../data/travel.csv")
Short = pd.read_csv("../data/shortest.csv")

figa, axa = plt.subplots()
axa.set_title("Angle vs path length")
axa.set_xlabel("Angle")
axa.set_ylabel("Path length")
axa.plot(Opt['beta'], Opt['d_travel'])
figa.savefig("../data/opt_curve.jpeg")

figb, axb = plt.subplots()
axb.set_title("Shortest path")
axb.plot(Short['x'], Short['y'])
axb.set_aspect(1.0)
figb.savefig("../data/shortest_path.jpeg")
