#pragma once

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <Windows.h>

constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);

class Lotus : public BakkesMod::Plugin::BakkesModPlugin
	, public SettingsWindowBase // Uncomment if you wanna render your own tab in the settings menu
	//,public PluginWindowBase // Uncomment if you want to render your own plugin window
{

	//std::shared_ptr<bool> enabled;

	std::shared_ptr<ImageWrapper> bb2;
	std::unique_ptr<MMRNotifierToken> notifierToken;
	void onLoad() override;
	void onUnload() override; // Uncomment and implement if you need a unload method
	void debugStat(CanvasWrapper canvas, bool OwnStat);
	void CreateCustomID();
	void setPATH(const std::string & pluginPath, const std::string & replayPath);
	//void updateMMR(UniqueIDWrapper id);
	void getInfo();

	//cpp
	std::string st(int nbr);
	std::string convToBackSlash(const std::string& path);
	std::string convToUndoBackSlash(const std::string& path);
	void manageReplayFiles(const std::string& path, const std::string& path2, bool keep);
	void initVariable();

	//Game
	bool gameIsNull();
	ServerWrapper getGame();
	int getNbrPlayer();
	int getMode();
	void saveDATA(const std::string& replay_path, const std::string& plugin_path);
	void getData(const std::string& replay_path, const std::string& plugin_path);

	// Own Stats
	int getOwnGoal();
	Vector getOwnPos();
	int getOwncarTouch();
	int getOwnBallTouch();
	int getOwnPickBoostDEV();
	int getOwnPoint();
	int getOwnTeamScore();
	int getOwnAssist();
	int getOwnSave();
	int getOwnPing();
	int getOwnXP();
	int getOwnShot();
	int getOwnDemo();
	int getOwnDeath();
	int getOwnKill();
	float getOwnVelocity();

	// Opponent Stats
	int getOpponentTeamScore();

public:

	void RenderSettings() override; // Uncomment if you wanna render your own tab in the settings menu
	//void RenderWindow() override; // Uncomment if you want to render your own plugin window
};
