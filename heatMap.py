import os
import json
import csv
from datetime import datetime
import numpy as np
import matplotlib.pyplot as plt

#Mathis j'te Grignotte

csv_dir = "./Data"
matriceDIR = "./HeatMap"
x_range = (-4096, 4096)
y_range = (-6000, 6000)
case_size = 200
test = False

def count_distinct_usernames(csv_filename):
    distinct_usernames = set()

    with open(csv_filename, 'r') as csvfile:
        reader = csv.reader(csvfile)
        first_row = next(reader)

        for username in first_row:
            if username not in ["game", "ball"]:
                distinct_usernames.add(username)

    return len(distinct_usernames)

for filename in os.listdir(csv_dir):
    if filename.endswith(".csv"):
        csv_path = os.path.join(csv_dir, filename)
        with open(csv_path) as csv_file:
            nombre = count_distinct_usernames(csv_path)
            lines = csv_file.readlines()           
        object_names = lines[0].strip().split(",")
        attribute_names = lines[1].strip().split(",")
        dic = {}
        mode = round(nombre / 2) if round(nombre / 2) <= 3 else 3
        for element in object_names:
            if not element in dic.keys() and element != "ball" and element != "game":
                dic[element] = [[],[]]
        
                player_index = object_names.index(element)

                pos_x_index = attribute_names.index("pos_x")
                pos_y_index = attribute_names.index("pos_y")

                prev_x = None
                prev_y = None

                for line in lines[2:]:
                    data = line.strip().split(",")

                    current_x = data[player_index + pos_x_index]
                    current_y = data[player_index + pos_y_index]
                    if current_x != '' and current_y != '':
                        if test == False:
                            inverse = (-1.0 if float(current_y) > 0.0 else 1.0)
                            test = True        
                        current_x = float(current_x) * inverse
                        current_y = float(current_y) * inverse
                        current_x_bin = int(current_x / case_size)
                        current_y_bin = int(current_y / case_size)
                        if current_x_bin != prev_x or current_y_bin != prev_y:
                            dic[element][0].append(current_x)
                            dic[element][1].append(current_y)
                            prev_x = current_x_bin
                            prev_y = current_y_bin

                new_heatmap, _, _ = np.histogram2d(dic[element][0],  dic[element][1], bins=(int((x_range[1] - x_range[0]) / case_size), int((y_range[1] - y_range[0]) / case_size)), range=[x_range, y_range])
                if os.path.exists(f'{matriceDIR}/heatmap_matrix_{element}_{mode}.csv'):
                    heatmap = np.loadtxt(f'{matriceDIR}/heatmap_matrix_{element}_{mode}.csv', delimiter=',')
                    heatmap += new_heatmap
                else:
                    heatmap = new_heatmap
                np.savetxt(f'{matriceDIR}/heatmap_matrix_{element}_{mode}.csv', heatmap, delimiter=',')
