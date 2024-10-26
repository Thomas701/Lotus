
![_6d9dfe74-2534-4ee6-b25a-89eedd6c1f7c](https://github.com/Thomas701/Lotus/assets/50084075/b4f9592f-a040-460e-9705-bcd0ebc41c4b)

# Result:

![image](https://github.com/user-attachments/assets/d14b05a4-0a1b-492d-a655-24ea325b5832)

![image](https://github.com/user-attachments/assets/e591755e-2ece-44fb-bdeb-a7a49402c37d)

![image](https://github.com/user-attachments/assets/68c38d03-3c94-47b8-87a4-56686340dc84)

![image](https://github.com/user-attachments/assets/a9db8505-e6fb-4de7-a0d9-bd12796e4166)

![image](https://github.com/user-attachments/assets/548da15c-ea46-4f15-b7c4-577c9868c9dd)

# How to install ?

- Download .zip
- Extract
- Download and install python 3.8.10  (https://www.python.org/downloads/release/python-3810/)
- [**OPTIONAL**] Download Visual Studio with cpp extension  ( **OPTIONAL**, only if you want to build the plugin )
- Download PowerBI Deskop (https://www.microsoft.com/fr-fr/download/details.aspx?id=58494)
- Go to the folder where you have extract the .zip
- Open a terminal in the good folder (where your plugin is) and executes the following 3 commands:

```txt
python -m venv .venv
python -m venv .venv1
python -m venv .venv2
```

- [**OPTIONAL**] To compile the plugin, do: ctrl+b in Visual Studio.
- If you don't use Visual Studio, get "Lotus.dll" in the plugin_folder: "Lotus/plugin" and copy paste this dll in Appdata Folder, here:  \AppData\Roaming\bakkesmod\bakkesmod\plugins  (To go in AppData folder, do "Windows + R" and write: "%appdata%" in the small window that opens.
- Go to Rocket League, open BakkesMod and enable Lotus
- Go to Bakkesmod and enable in Ranked tab: "Automatically save All Replays".
- Enter your plugin_path (where you have extract the .zip, like:  YOUR_COMPUTER\Lotus ) and your replays_path (often the PATH is: "YOUR_COMPUTER\Documents\My Games\Rocket League\TAGame\DemosEpic or just "Demos" for the last folder), and save. 
- Restart Lotus Plugin. (Uncheck and check Lotus in plugin manager)
![image](https://github.com/user-attachments/assets/5b3e5b2f-2c00-444e-9cbc-a95e9c7b390c)
![image](https://github.com/user-attachments/assets/ac86653c-340a-41b3-97e7-b69f2bebb3e4)
- Play and when you want, click on "Save Data". (Choice if you want keep or not your replays)
Before the next step, you have to play a little bit to be sure LOTUS_DATA_BASE.csv and mmr.csv are created.
If you select "Keep replay" in the Lotus plugin, your replays will be move in "YOUR_COMPUTER\Documents\My Games\Rocket League\TAGame\SavedReplay" else your replays will be delete, so, be careful !
- Open RocketLeagueStats.pbix, right click on "transform data", then change the source and select YOUR "LOTUS_DATA_BASE.csv", and YOUR mmr.csv always in the same folder and don't forget to right click on PowerBI on your table on "refresh data".
- ![image](https://github.com/user-attachments/assets/b3973b9c-c66e-4c20-982d-d7e5e913b10e)
- ![image](https://github.com/user-attachments/assets/27f028c3-384f-4d14-82ad-3b1323ff7bc6)
- ![image](https://github.com/user-attachments/assets/5a34a688-db99-4f24-a176-ddd8aff9e7f9)
- ![image](https://github.com/user-attachments/assets/1343c641-fbc5-431f-b974-2ffb8002f96a)

- You could see you statistics.

[ For some matches you may not have the MMR, which is normal. If you are playing casual and bots join or players leave a game before the end of the match, the ID will be wrong and the MMR will be unavailable. In other cases, you will have your MMR. ]

## Thanks to xerneas02: rocketReplay.py

https://github.com/xerneas02

## Thanks to nickbabcock: rrrocket.exe

https://github.com/nickbabcock

If you have any problem, my discord: thomas701
