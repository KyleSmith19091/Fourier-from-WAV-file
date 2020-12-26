import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math

def complexPlot(dataF):
    fig, ax = plt.subplots()

    xf = df.x
    yf = df.y

    ax.plot(xf,yf)
    plt.grid()
    plt.xlabel("x")
    plt.ylabel("y")
    plt.savefig("plotComplex.png")
    plt.show()

def magPlot(dataF):
    fig, ax = plt.subplots()

    xf = np.linspace(0,500,32)
    yf = np.sqrt(df.x**2 + df.y**2)

    ax.plot(xf,yf)
    plt.grid()
    plt.xlabel("Freq")
    plt.ylabel("Magnitude")
    plt.savefig("plotComplex.png")
    plt.show()


df = pd.read_csv("./coords.csv")
complexPlot(df)
magPlot(df)


