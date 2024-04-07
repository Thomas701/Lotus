#include "pch.h"
#include "Lotus.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <algorithm>


BAKKESMOD_PLUGIN(Lotus, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

bool enablePlugin = false; 
bool OwnStat = false;
bool Keep = false;

int mode = 0; 
int OwnTouchBall = 0;
int OwnTouchCar = 0; 
int OwnGoal = 0; 
int OwnPoint = 0;
int OwnTeamScore = 0; 
int opponentTeamScore = 0;
int OwnAssist = 0;
int OwnSave = 0;
int OwnShot = 0;
std::string OwnName;
Vector OwnPos; 

int team;
int sizeTeam = 0;

void Lotus::onLoad()
{
	_globalCvarManager = cvarManager;
	LOG("Lotus Plugin Loaded!");

	auto verif1 = cvarManager->registerCvar("enablePlugin", "0", "Test si le plugin est actif ou non", true, true, 0, true, 1);
	verif1.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {enablePlugin = cvar.getBoolValue();});
	auto verif2 = cvarManager->registerCvar("OwnStat", "0", "On veut nos stats?", true, true, 0, true, 1);
	verif2.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {OwnStat = cvar.getBoolValue();});
	auto verif3 = cvarManager->registerCvar("keep", "0", "on garde les replays?", true, true, 0, true, 1);
	verif3.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {Keep = cvar.getBoolValue(); });

	gameWrapper->RegisterDrawable([this](CanvasWrapper canvas)
		{
			debugStat(canvas, OwnStat);
		});

	gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput",
		[this](std::string eventName) {
			getInfo();
		});
}

void Lotus::onUnload()
{
	LOG("Unload perfect!");
}

void Lotus::debugStat(CanvasWrapper canvas, bool OwnStat)
{
	LinearColor colors;
	colors.R = 255; colors.G = 255; colors.B = 0; colors.A = 255;
	canvas.SetColor(colors);

	if (cvarManager->getCvar("enablePlugin").getBoolValue() == true)
	{
		if (OwnStat)
		{
			canvas.SetPosition(Vector2F{ 5.0, 100.0 });
			canvas.DrawString("Mode de jeu: " + st(mode)
				+ ", Mon Score: " + st(OwnTeamScore)
				+ ", Score adverse: " + st(opponentTeamScore)
				, 2.0, 2.0, false);
			canvas.SetPosition(Vector2F{ 5.0, 150.0 });
			canvas.DrawString("Points: " + st(OwnPoint)
				+ ", Goals: " + st(OwnGoal)
				+ ", Saves: " + st(OwnSave)
				+ ", Assists: " + st(OwnAssist)
				+ ", Shot: " + st(OwnShot)
				+ ", TouchBall: " + st(OwnTouchBall)
				, 2.0, 2.0, false);
			canvas.SetPosition(Vector2F{ 5.0, 200.0 });
			canvas.DrawString(
				+ "x=" + std::to_string(OwnPos.X) + ",y=" + std::to_string(OwnPos.Z) + ",z=" + std::to_string(OwnPos.Y)
				, 2.0, 2.0, false);
		}
	}
	else
		canvas.DrawString("", 2.0, 2.0, false); // 2&3 argument: taille , 4 arguments = afficher l'ombre ou pass
}

//void Lotus::updateMMR(UniqueIDWrapper id)
//{
//	ServerWrapper sw = gameWrapper->GetCurrentGameState();
//	if (!sw)
//		return;
//	GameSettingPlaylistWrapper playlist = sw.GetPlaylist();
//	if (!playlist)
//		return;
//	int playlistID = playlist.GetPlaylistId();
//	float mmr = gameWrapper->GetMMRWrapper().GetPlayerMMR(id, playlistID);
//	LOG("#################{} MMR is: {}####################", id.GetIdString(), mmr);
//}

void Lotus::getInfo()
{
	if (enablePlugin == false || gameIsNull() || getGame().GetPRIs().IsNull() || gameWrapper->GetPlayerController().IsNull() )
		return;

	mode = getMode();

	/*---------------------------Owner-----------------------------------*/
	OwnPos = getOwnPos();
	OwnPoint = getOwnPoint();
	OwnTouchCar = getOwncarTouch();
	OwnTouchBall = getOwnBallTouch();
	OwnGoal = getOwnGoal();
	OwnTeamScore = getOwnTeamScore();
	OwnAssist = getOwnAssist();
	OwnSave = getOwnShot();
	OwnShot = getOwnShot();
	/*-------------------------Opponent------------------------------------*/
	opponentTeamScore = getOpponentTeamScore();
}

void Lotus::saveDATA(const std::string& replay_path, const std::string& plugin_path)
{
	LOG("###------->{}", replay_path);
	LOG("###------->{}", plugin_path);

	std::string command = "powershell.exe -noexit -command \"cd '" + plugin_path + "'; .\\rrrocket.exe -n -c -m -p '" + replay_path + "'; exit\"";

	int result = std::system(command.c_str());

	if (result == 0) {
		std::cout << "La commande PowerShell a été exécutée avec succès." << std::endl;
	}
	else {
		std::cout << "Erreur lors de l'exécution de la commande PowerShell." << std::endl;
	}

	std::string python_command = "cd /d " + plugin_path + " && .\\.venv\\Scripts\\python.exe .\\rocketReplay.py";
	system(python_command.c_str());

	std::string data_path = plugin_path + "/Data";
	for (const auto& entry : std::filesystem::directory_iterator(data_path)) {
		if (entry.path().extension() == ".csv") {
			std::filesystem::remove(entry.path());
		}
	}

	for (const auto& entry : std::filesystem::directory_iterator(replay_path)) {
		if (entry.path().extension() == ".json") {
			std::filesystem::remove(entry.path());
		}
	}
}

void Lotus::manageReplayFiles(const std::string& path, const std::string& path2, bool keep) 
{
	std::string parent_path = std::filesystem::path(path).parent_path().string();
	std::string saved_replay_path = parent_path + "/SavedReplay";
	std::ofstream file("file_dates.txt", std::ios::app);

	if (!std::filesystem::exists(saved_replay_path))
		std::filesystem::create_directory(saved_replay_path);

	std::ofstream txtFile(path2 + "/file_info.txt", std::ios::app);
	if (!txtFile.is_open()) {
		std::cerr << "Failed to open or create file_info.txt" << std::endl;
		return;
	}


	if (keep) {
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.path().extension() == ".replay") {
				txtFile << entry.path().stem().string() << ".replay;" << std::filesystem::last_write_time(entry) << std::endl;
				std::filesystem::rename(entry.path(), saved_replay_path + "/" + entry.path().filename().string());			}
		}
	}
	else {
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.path().extension() == ".replay") {
				txtFile << entry.path().stem().string() << ".replay;" << std::filesystem::last_write_time(entry) << std::endl;
				std::filesystem::remove(entry.path());
			}
		}
	}
}

void Lotus::getData(const std::string& replay_path, const std::string& plugin_path)
{
	std::string python_command = "cd /d " + plugin_path + " && .\\.venv\\Scripts\\python.exe .\\getData.py";
	system(python_command.c_str());
}


//   std::string command = "powershell.exe -noexit -command \"cd 'C:\\Project\\Bakkesmod\\Lotus'; .\\rrrocket.exe -n -c -m -p 'C:\\Users\\thodu\\OneDrive\\Documents\\My Games\\Rocket League\\TAGame\\DemosEpic'; exit\"";
//   int result = std::system(command.c_str());

//   if (result == 0) {
//       std::cout << "La commande PowerShell a été exécutée avec succès." << std::endl;
//   } else {
//       std::cout << "Erreur lors de l'exécution de la commande PowerShell." << std::endl;
//   }

   //system("cd /d C:\\Project\\Bakkesmod\\Lotus && .\\.venv\\Scripts\\python.exe .\\rocketReplay.py");