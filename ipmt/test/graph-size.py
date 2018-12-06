import matplotlib.pyplot as plt

f1 = []
f1.append(0.126)
f1.append(26.694)
f1.append(817.626)
f1.append(4871.082)
plt.plot([5, 100, 1000, 5000], f1, label="LS = 65535 / LL = 255")

f2 = []
f2.append(5.008)
f2.append(123.680)
f2.append(1253.168)
f2.append(5812.992)
plt.plot([5, 100, 1000, 5000], f2, label="LS = 512 / LL = 128")

f3 = []
f3.append(0.465)
f3.append(84.250)
f3.append(1008.075)
f3.append(5312.330)
plt.plot([5, 100, 1000, 5000], f3, label="LS = 4096 / LL = 256")

# f4 = []
# f4.append(0.470)
# f4.append(84.255)
# f4.append(1008.125)
# f4.append(5312.560)
# plt.plot([5, 100, 1000, 5000], f4, label="LS = 4095 / LL = 255")

plt.xticks([5, 100, 1000, 5000])
plt.title("Comparação do tamamho do arquivo de saída para diferentes tamanho de buffers")
plt.ylabel('Tempo do arquivo comprimido em KB')
plt.xlabel('Tamamnho do arquivo em KB')
plt.legend(loc='best')

plt.savefig('size.png')
# plt.show()