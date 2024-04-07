
import carball
import json
import os
import carball
import gzip
from carball.json_parser.game import Game
from carball.analysis.analysis_manager import AnalysisManager
import pandas as pd

OCTANE = 4284
FENNEC = 23

def invert_perspective(df):
    """
    Create a mirror version of the data of the match where the blue is orange and the orange is blue that could be used for training a bot.
    Only work with 1v1 replay.
    """
    players = df.columns.levels[0]


    df.loc[:, (players[0], 'pos_x')] *= -1
    df.loc[:, (players[1], 'pos_x')] *= -1
    df.loc[:, ('ball', 'pos_x')] *= -1

    df.loc[:, (players[0], 'pos_y')] *= -1
    df.loc[:, (players[1], 'pos_y')] *= -1
    df.loc[:, ('ball', 'pos_y')] *= -1

    df.loc[:, (players[0], 'pos_z')] *= -1
    df.loc[:, (players[1], 'pos_z')] *= -1
    df.loc[:, ('ball', 'pos_z')] *= -1

    df.loc[:, (players[0], 'rot_x')] *= -1
    df.loc[:, (players[1], 'rot_x')] *= -1
    df.loc[:, ('ball', 'rot_x')] *= -1

    df.loc[:, (players[0], 'rot_y')] *= -1
    df.loc[:, (players[1], 'rot_y')] *= -1
    df.loc[:, ('ball', 'rot_y')] *= -1

    df.loc[:, (players[0], 'rot_z')] *= -1
    df.loc[:, (players[1], 'rot_z')] *= -1
    df.loc[:, ('ball', 'rot_z')] *= -1

    df.loc[:, (players[0], 'vel_x')] *= -1
    df.loc[:, (players[1], 'vel_x')] *= -1
    df.loc[:, ('ball', 'vel_x')] *= -1

    df.loc[:, (players[0], 'vel_y')] *= -1
    df.loc[:, (players[1], 'vel_y')] *= -1
    df.loc[:, ('ball', 'vel_y')] *= -1

    df.loc[:, (players[0], 'vel_z')] *= -1
    df.loc[:, (players[1], 'vel_z')] *= -1
    df.loc[:, ('ball', 'vel_z')] *= -1

    player_columns = []
    for player in players:
        player_columns.extend([(player, col) for col in df[player].columns])


    new_columns = pd.MultiIndex.from_tuples(player_columns[::-1])


    df = df[new_columns]

    return df

def print_player_info_at_frame(df, frame_index):
    players = df.columns.levels[0][:2]  

    frame_data = df.iloc[frame_index]


    for player in players:
        print(f"Player: {player}")
        player_data = frame_data[player]
        print(player_data)


script_directory = os.path.dirname(os.path.realpath(__file__))
replay_path_file = "replay_path.txt"
with open(replay_path_file, "r") as file:
    replays_directory = file.readline().strip()

json_directory = os.path.join(script_directory, 'JSON')
if not os.path.exists(json_directory):
    os.makedirs(json_directory)

data_directory = os.path.join(script_directory, 'Data')
if not os.path.exists(data_directory):
    os.makedirs(data_directory)


for replay_file in os.listdir(replays_directory):
    if replay_file.endswith('.json'):
        replay_name = os.path.splitext(replay_file)[0]
        replay_path = os.path.join(replays_directory, replay_file)

        game = Game()
        game.initialize(file_path=f'{replays_directory}/{replay_file}')
        analysis_manager = AnalysisManager(game)
        analysis_manager.create_analysis()
        
        json_file_path = os.path.join(json_directory, f'{replay_name}.json')
        with open(json_file_path, 'w') as json_file:
            analysis_manager.write_json_out_to_file(json_file)
            
        json_data = analysis_manager.get_json_data()

        data_frame = analysis_manager.get_data_frame()

        filtered_columns = [(player, prop) for player, prop in data_frame.columns.to_list()
                            if prop != 'ping' and prop != 'ball_cam']
        data_frame = data_frame[[col for col in filtered_columns]]

        data_file_path = os.path.join(data_directory, f'Data-{replay_name}.csv')
        data_frame.to_csv(data_file_path, index=False)


        print(f"Complete {replay_file}")

print("All files done.")
