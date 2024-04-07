#include "pch.h"
#include "Lotus.h"
#include <cmath>

//Les fonction finissant par 'DEV' ne fonctionne que en match privé & host par le joueur !!

/*##########################--- CPP ---#############################*/


/// <summary>
/// Converti un int en string
/// </summary>
/// <param name="nbr"></param>
/// <returns></returns>
std::string Lotus::st(int nbr)
{
	return std::to_string(nbr);
}

std::string Lotus::convToBackSlash(const std::string& path) 
{
	std::string result;
	for (char c : path) {
		if (c == '\\') {
			result.push_back('\\');
		}
		result.push_back(c);
	}
	return result;
}


/*##########################--- GAME ---#############################*/


/// <summary>
/// Vérifie si le serveur existe
/// </summary>
/// <returns></returns>
bool Lotus::gameIsNull()
{
	return (gameWrapper->GetCurrentGameState()).IsNull();
}

/// <summary>
/// Retourne la game en cour (le serveur)
/// </summary>
/// <returns></returns>
ServerWrapper Lotus::getGame()
{
	return gameWrapper->GetCurrentGameState();
}

/// <summary>
/// Retourne le nombre de joueur dans la partie
/// </summary>
/// <returns></returns>
int Lotus::getNbrPlayer()
{
	return getGame().GetPRIs().Count();
}

int Lotus::getMode()
{
	GameSettingPlaylistWrapper playlist = getGame().GetPlaylist();
	if (!playlist)
	{
		LOG("ERROR in getMode, playList is NULL");
		return 0;
	}
	else 
		return playlist.GetPlaylistId();
}

/*##########################--- STAT PERSO ---#############################*/

/// <summary>
/// Retourne notre nombre de but
/// </summary>
/// <returns></returns>
int Lotus::getOwnGoal() 
{ 
	return gameWrapper->GetPlayerController().GetPRI().GetMatchOwnGoals();
}

/// <summary>
/// retourne le nombre de fois que l'on touche la balle
/// </summary>
/// <returns></returns>
int Lotus::getOwnBallTouch()
{
	return gameWrapper->GetPlayerController().GetPRI().GetBallTouches();
}

/// <summary>
/// retourne le nombre de fois où on touche une voiture adverse
/// </summary>
/// <returns></returns>
int Lotus::getOwncarTouch()
{
	return gameWrapper->GetPlayerController().GetPRI().GetCarTouches();
}

/// <summary>
/// retourne le nombre de point qu'on a obtenu pendant le match
/// </summary>
/// <returns></returns>
int Lotus::getOwnPoint()
{
	return gameWrapper->GetPlayerController().GetPRI().GetMatchScore();
}

/// <summary>
/// retourne notre position x,y,z
/// </summary>
/// <returns></returns>
Vector Lotus::getOwnPos()
{
	return gameWrapper->GetPlayerController().GetLocation();
}

/// <summary>
/// retourne le score de notre équipe
/// </summary>
/// <returns></returns>
int Lotus::getOwnTeamScore()
{
	return gameWrapper->GetPlayerController().GetPRI().GetTeam().GetScore();
}

/// <summary>
/// retourne le nombre de boost qu'on a gober pendant le match (un gros boot ou un petit = 1 dans tous les cas)
/// </summary>
/// <returns></returns>
int Lotus::getOwnPickBoostDEV()
{
	return gameWrapper->GetPlayerController().GetPRI().GetBoostPickups();
}

int Lotus::getOwnAssist()
{
	return gameWrapper->GetPlayerController().GetPRI().GetMatchAssists();
}

int Lotus::getOwnSave()
{
	return gameWrapper->GetPlayerController().GetPRI().GetMatchSaves();
}

int Lotus::getOwnPing()
{
	return gameWrapper->GetPlayerController().GetPRI().GetPing();
}

int Lotus::getOwnXP()
{
	return gameWrapper->GetPlayerController().GetPRI().GetMatchBonusXP();
}

int Lotus::getOwnShot()
{
	return gameWrapper->GetPlayerController().GetPRI().GetMatchShots();
}

int Lotus::getOwnDemo()
{
	return gameWrapper->GetPlayerController().GetPRI().GetMatchDemolishes();
}

int Lotus::getOwnDeath()
{
	return gameWrapper->GetPlayerController().GetPRI().GetDeaths();
}

int Lotus::getOwnKill()
{
	return gameWrapper->GetPlayerController().GetPRI().GetKills();
}

float Lotus::getOwnVelocity()
{
	Vector v = gameWrapper->GetPlayerController().GetPRI().GetVelocity();
	return sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}


/*##########################--- STAT ADVERSAIRES ---#############################*/
int Lotus::getOpponentTeamScore()
{
	int num, team;
	std::string myString = std::to_string(gameWrapper->GetPlayerController().GetTeamNum2());
	team = std::stoi(myString);
	num = (team == 0) ? 1 : 0;
	return gameWrapper->GetCurrentGameState().GetTeams().Get(num).GetScore();
}
