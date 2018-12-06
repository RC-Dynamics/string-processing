import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

width = 0.35

df = pd.read_csv('compress-65535-255.csv', header=None)
f1 = []
f1.append(np.mean(df[0]))
f1.append(np.mean(df[1]))
f1.append(np.mean(df[2]))
f1.append(np.mean(df[3]))
plt.plot([5, 100, 1000, 5000], f1, label="LS = 65535 / LL = 255")

df2 = pd.read_csv('compress-512-128.csv', header=None)
f2 = []
f2.append(np.mean(df2[0]))
f2.append(np.mean(df2[1]))
f2.append(np.mean(df2[2]))
f2.append(np.mean(df2[3]))
plt.plot([5, 100, 1000, 5000], f2, label="LS = 512 / LL = 128")

df3 = pd.read_csv('compress-4096-256.csv', header=None)
f3 = []
f3.append(np.mean(df3[0]))
f3.append(np.mean(df3[1]))
f3.append(np.mean(df3[2]))
f3.append(np.mean(df3[3]))
plt.plot([5, 100, 1000, 5000], f3, label="LS = 4096 / LL = 256")

df4 = pd.read_csv('compress-4095-255.csv', header=None)
f4 = []
f4.append(np.mean(df4[0]))
f4.append(np.mean(df4[1]))
f4.append(np.mean(df4[2]))
f4.append(np.mean(df4[3]))
plt.plot([5, 100, 1000, 5000], f4, label="LS = 4095 / LL = 255")

plt.xticks([5, 100, 1000, 5000])
plt.title("Comparação de tempo execução para diferentes tamanho de buffers")
plt.ylabel('Tempo de execução em segundos')
plt.xlabel('Tamamnho do arquivo em KB')
plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)

plt.show()