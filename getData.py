import os
import json
import csv
from datetime import datetime

# Chemin du répertoire JSON
json_dir = "./JSON"

player_data = []
file_info = {}

# Lecture du contenu du fichier file_info.txt
with open("file_info.txt", "r") as file_info_file:
    lines = file_info_file.readlines()
    for line in lines:
        filename, date_str = line.strip().split(';')
        test = filename.strip()
        file_info[test] = date_str.strip()

# Parcours des fichiers JSON dans le répertoire
for filename in os.listdir(json_dir):
    if filename.endswith(".json"):
        json_path = os.path.join(json_dir, filename)
        filename = os.path.splitext(filename)[0] 
        if filename in file_info:
            date_replay = file_info[filename]
            print("")
        else:
            print(f"No date found for {filename}")
     
        # Ouverture du fichier JSON et chargement des données
        with open(json_path) as json_file:
            data = json.load(json_file)

        # Récupération des informations du jeu
        game_metadata = data['gameMetadata']
        game_id = game_metadata.get('id', 0)
        team0_score = game_metadata['score'].get('team0Score', 0)
        team1_score = game_metadata['score'].get('team1Score', 0)
        game_length = game_metadata.get('length', 0)
        team_size = game_metadata.get('teamSize', 0)
        playlist = game_metadata.get('playlist', 0)

        # Récupération des informations des joueurs
        for player in data['players']:
            player_stats = player.get('stats', {})
            boost_stat = player_stats.get('boost', {})
            boost_usage = boost_stat.get('boostUsage', 0)
            num_small_boosts = boost_stat.get('numSmallBoosts', 0)
            num_large_boosts = boost_stat.get('numLargeBoosts', 0)
            wasted_collection = boost_stat.get('wastedCollection', 0)
            wasted_usage = boost_stat.get('wastedUsage', 0)
            time_full_boost = (boost_stat.get('timeFullBoost', 0) / game_length ) * 100.00
            time_low_boost = (boost_stat.get('timeLowBoost', 0) / game_length ) * 100.00
            num_stolen_boosts = boost_stat.get('numStolenBoosts', 0)
            average_boost_level = player_stats['boost'].get('averageBoostLevel', 0)

            distance_stat = player_stats.get('distance', {})
            time_closest_to_ball = (distance_stat.get('timeClosestToBall', 0) / game_length ) * 100.00
            time_furthest_from_ball = (distance_stat.get('timeFurthestFromBall', 0) / game_length ) * 100.00

            possession_stat = player_stats.get('possession', {})
            possession_time = (possession_stat.get('possessionTime', 0) / game_length ) * 100.00
            turnovers = possession_stat.get('turnovers', 0)
            turnovers_on_my_half = possession_stat.get('turnoversOnMyHalf', 0)
            turnovers_on_their_half = possession_stat.get('turnoversOnTheirHalf', 0)
            won_turnovers = possession_stat.get('wonTurnovers', 0)

            possessionTend_stat = player_stats.get('positionalTendencies', {})
            time_on_ground = (possessionTend_stat.get('timeOnGround', 0) / game_length ) * 100.00
            time_low_in_air = (possessionTend_stat.get('timeLowInAir', 0) / game_length ) * 100.00
            time_high_in_air = (possessionTend_stat.get('timeHighInAir', 0) / game_length ) * 100.00
            time_in_defending_half = (possessionTend_stat.get('timeInDefendingHalf', 0) / game_length ) * 100.00
            time_in_attacking_half = (possessionTend_stat.get('timeInAttackingHalf', 0) / game_length ) * 100.00
            time_in_defending_third = (possessionTend_stat.get('timeInDefendingThird', 0) / game_length ) * 100.00
            time_in_neutral_third = (possessionTend_stat.get('timeInNeutralThird', 0) / game_length ) * 100.00
            time_in_attacking_third = (possessionTend_stat.get('timeInAttackingThird', 0) / game_length ) * 100.00
            time_behind_ball = (possessionTend_stat.get('timeBehindBall', 0) / game_length ) * 100.00
            time_in_front_ball = (possessionTend_stat.get('timeInFrontBall', 0) / game_length ) * 100.00
            time_near_wall = (possessionTend_stat.get('timeNearWall', 0) / game_length ) * 100.00
            time_in_corner = (possessionTend_stat.get('timeInCorner', 0) / game_length ) * 100.00
            time_on_wall = (possessionTend_stat.get('timeOnWall', 0) / game_length ) * 100.00

            average_stat = player_stats.get('averages', {})
            average_speed = average_stat.get('averageSpeed', 0)

            hitCounts_stat = player_stats.get('hitCounts', {})
            total_hits = hitCounts_stat.get('totalHits', 0)
            total_saves = hitCounts_stat.get('totalSaves', 0)
            total_dribbles = hitCounts_stat.get('totalDribbles', 0)
            total_aerials = hitCounts_stat.get('totalAerials', 0)
            total_clears = hitCounts_stat.get('totalClears', 0)

            speed_stat = player_stats.get('speed', {})
            time_at_slow_speed = (speed_stat.get('timeAtSlowSpeed', 0) / game_length ) * 100.00
            time_at_super_sonic = (speed_stat.get('timeAtSuperSonic', 0) / game_length ) * 100.00
            time_at_boost_speed = (speed_stat.get('timeAtBoostSpeed', 0) / game_length ) * 100.00

            ball_carries = player_stats.get('ballCarries', {})
            total_carries = ball_carries.get('totalCarries', 0)
            total_flicks = ball_carries.get('totalFlicks', 0)
            longest_carry = ball_carries.get('longestCarry', 0)
            total_carry_time = ball_carries.get('totalCarryTime', 0)
            fastest_carry_speed = ball_carries.get('fastestCarrySpeed', 0)
            carry_stats = ball_carries.get('carryStats', {})
            variance_ball_z_velocity = carry_stats.get('varianceBallZVelocity', 0)

            kickoff_stat = player_stats.get('kickoffStats', {})
            total_kickoffs = kickoff_stat.get('totalKickoffs', 0)
            num_time_go_to_ball = kickoff_stat.get('numTimeGoToBall', 0)
            num_time_first_touch = kickoff_stat.get('numTimeFirstTouch', 0)
            average_boost_used = kickoff_stat.get('averageBoostUsed', 0)

            # Ajout des données du joueur à la liste
            player_data.append([
                date_replay, 
                game_id, team0_score, team1_score, game_length, team_size, playlist,
                player['id']['id'], player.get('name', ""), player.get('score', 0),
                player.get('goals', 0), player.get('assists', 0), player.get('saves', 0),
                player.get('shots', 0), player.get('isOrange', 0), boost_usage,
                num_small_boosts, num_large_boosts, wasted_collection, wasted_usage,
                time_full_boost, time_low_boost, num_stolen_boosts, average_boost_level,
                time_closest_to_ball, time_furthest_from_ball, possession_time,
                turnovers, turnovers_on_my_half, turnovers_on_their_half, won_turnovers,
                time_on_ground, time_low_in_air, time_high_in_air, time_in_defending_half,
                time_in_attacking_half, time_in_defending_third, time_in_neutral_third,
                time_in_attacking_third, time_behind_ball, time_in_front_ball, time_near_wall,
                time_in_corner, time_on_wall, average_speed, total_hits, total_saves,
                total_dribbles, total_aerials, total_clears, time_at_slow_speed,
                time_at_super_sonic, time_at_boost_speed, total_carries, total_flicks,
                longest_carry, total_carry_time, fastest_carry_speed, variance_ball_z_velocity,
                total_kickoffs, num_time_go_to_ball, num_time_first_touch, average_boost_used
            ])
        os.remove(json_path)

# Chemin du fichier de sortie
output_file = "LOTUS_DATA_BASE.csv"

# Vérification de l'existence du fichier de sortie
file_exists = os.path.isfile(output_file)

# Écriture des données dans le fichier CSV
with open(output_file, 'a', newline='') as csvfile:
    writer = csv.writer(csvfile, delimiter=';')
    if not file_exists:
        # Écriture de l'en-tête si le fichier n'existe pas
        writer.writerow([
            "DATE",
            "GameID", "BlueScore", "OrangeScore", "GameLength", "TeamSize", "Mode",
            "IdPlayer", "Name", "Score", "Goals", "Assists", "Saves", "Shots", "IsOrange",
            "BoostUsage", "SmallBoost", "LargeBoost", "BoostOverflow", "BoostDuringSuperSonic",
            "TimeFullBoost", "TimeLowBoost", "StolenBoost", "AverageBoostLevel",
            "TimeClosestToBall", "TimeFurthestFromBall", "PossessionTime",
            "TurnoversLoose", "TurnoversOnMyHalf", "TurnoverOnThierHalf", "TurnoversWin",
            "TimeOnGround", "TimeLowInAir", "TimeHightInAir", "TimeInDefendingHalf",
            "TimeInAttackingHalf", "TimeInDefendingThird", "TimeInNeutralThird",
            "TimeInAttackingThird", "TimeBehindBall", "TimeInFrontBall", "TimeNearWall",
            "TimeInCorner", "TimeOnWall", "AverageSpeed", "TotalHits", "TotalSaves",
            "TotalDribbles", "TotalAerial", "TotalClears", "TimeAtSlowSpeed",
            "TimeAtSuperSonic", "TimeAtBoostSpeed", "TotalCarries", "TotalFlick",
            "LongestCarry", "TotalCarryTime", "FastestCarrySpeed", "VarianceBallZVelocity",
            "TotalKickoffs", "NumTimeGoToBall", "NumTimeFirstTouch", "AverageBoostUsed"
        ])

    # Écriture des données des joueurs
    for player_row in player_data:
        writer.writerow(player_row)

if os.path.exists("./file_info.txt"):
    os.remove("./file_info.txt")
print("Les données ont été écrites dans le fichier CSV.")