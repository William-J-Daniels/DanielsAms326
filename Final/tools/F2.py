import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("../data/F2.csv")
plt.plot(data["a"], label="(a)")
plt.plot(data["b"], label="(b)")
plt.legend()
plt.savefig("../data/F2.jpeg")
