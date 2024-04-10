import numpy as np
import matplotlib.pyplot as plt
import sys
import os

element = sys.argv[1]
mode = sys.argv[2]

#Mathis j'te Grignotte encore

matriceDIR = "./HeatMap"
x_range = (-4096, 4096)
y_range = (-6000, 6000)
case_size = 200

dic = {}
dic[element] = [[],[]]

if os.path.exists(f'{matriceDIR}/heatmap_matrix_{element}_{mode}.csv'):
    heatmap = np.loadtxt(f'{matriceDIR}/heatmap_matrix_{element}_{mode}.csv', delimiter=',')
else:
    exit()


# Display heatmap
plt.imshow(heatmap.T, extent=[x_range[0], x_range[1], y_range[0], y_range[1]], origin='lower')
plt.colorbar(label='Counts')
plt.title(f'Heatmap of {element} position')
plt.xlabel('X Position')
plt.ylabel('Y Position')
plt.grid(True)
plt.show()