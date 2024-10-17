#include "pch.h"
#include "Lotus.h"

std::string replay_path;
std::string plugin_path;
std::string name_player;
bool detect = false;
bool enable_Plugin;
bool keep;
bool own_Stat;
int pluginTime = 0; // Temps avant que "Path save" disparaisse de l'interface graphique pour Plugin Path
int replayTime = 0; // Temps avant que "Path save" disparaisse de l'interface graphique pour Replay Path
int modeDeJeu = 0;

void Lotus::RenderSettings()
{
    ImGui::Text("Welcome to the Lotus Plugin");


    if (detect == false)
    {
        initVariable();
        detect = true;
    }
    /*--- Si un des deux PATH est save, on affiche un message pendant un cours instant ---*/
    if (pluginTime > 0)                                                                  //|
        pluginTime--;                                                                    //|
                                                                                         //|
    if (replayTime > 0)                                                                  //|
        replayTime--;                                                                    //|
    /*------------------------------------------------------------------------------------*/

    LOG("#####->{}", plugin_path); //Affiche le path du plugin
    LOG("#####->{}", replay_path); //Affiche le path du replay

    /*-----------------------ENABLE BUTTON---------------------------*/

    CVarWrapper ENABLE_PLUGIN = cvarManager->getCvar("enablePlugin");
    if (!ENABLE_PLUGIN) return;
    enable_Plugin = ENABLE_PLUGIN.getBoolValue();
    if (ImGui::Checkbox("Enable plugin", &enable_Plugin)) { ENABLE_PLUGIN.setValue(enable_Plugin); }
    if (ImGui::IsItemHovered()) { ImGui::SetTooltip("Enable or disable MynoPlugin"); }

    if (!enable_Plugin)
        return;

    /*--------------------------Plugins Path-------------------------------*/
    ImGui::Text("Replays Analyser");

    static char pluginPath[256] = "";
    ImGui::InputText("Plugin Path", pluginPath, 256);
    if (ImGui::Button("Valider##Plugin")) 
    {
        plugin_path = std::string(pluginPath);
        std::string lotusDirectory = "..\\..\\Lotus";
        std::string secondPath = plugin_path;

        pluginTime = 500;
        if (!std::filesystem::exists(lotusDirectory)) {
            std::filesystem::create_directory(lotusDirectory);
        }
        std::string filePath = lotusDirectory + "\\plugin_path.txt";
        std::ofstream outputFile(filePath);

        if (outputFile.is_open()) {
            outputFile << plugin_path;
            outputFile.close();
        }
        else {
            std::cout << "Erreur : Impossible d'ouvrir le fichier plugin_path.txt pour l'�criture." << std::endl;
        }
        // Si le mec avait d�j� rempli une information dans replayPath, cela sauvegarde aussi
        if (replay_path != "")
        {
            filePath = secondPath + "\\replay_path.txt";
            std::ofstream outputFile2(filePath);

            if (outputFile2.is_open()) {
                outputFile2 << replay_path;
                outputFile2.close();
            }
            else {
                std::cout << "Erreur : Impossible d'ouvrir le fichier replay_path.txt pour l'�criture." << std::endl;
            }
        }
    }
    if (pluginTime > 0)
        ImGui::Text("Path saved!");
    std::string s1 = "Current Path : " + plugin_path;
    ImGui::Text(s1.c_str());
    if (plugin_path == "")
        return;

    /*--------------------------Replays Path-------------------------------*/
    static char replayPath[256] = "";
    ImGui::InputText("Replay Path", replayPath, 256);
    if (ImGui::Button("Valider##Replay")) 
    {
        replay_path = std::string(replayPath);
        std::string lotusDirectory = "..\\..\\Lotus";
        std::string secondPath = plugin_path;
        replayTime = 500;
        if (!std::filesystem::exists(lotusDirectory)) {
            std::filesystem::create_directory(lotusDirectory);
        }
        std::string filePath = lotusDirectory + "\\replay_path.txt";
        std::ofstream outputFile(filePath);

        if (outputFile.is_open()) {
            outputFile << replay_path;
            outputFile.close();
        }
        else {
            std::cout << "Erreur : Impossible d'ouvrir le fichier replay_path.txt pour l'�criture." << std::endl;
        }

        filePath = secondPath + "\\replay_path.txt";
        std::ofstream outputFile2(filePath);

        if (outputFile2.is_open()) {
            outputFile2 << replay_path;
            outputFile2.close();
        }
        else {
            std::cout << "Erreur : Impossible d'ouvrir le fichier plugin_path.txt pour l'�criture." << std::endl;
        }
    }

    if (replayTime > 0)
        ImGui::Text("Path saved!");
    std::string s2 = "Current Path : " + replay_path;
    ImGui::Text(s2.c_str());
    ImGui::Text("");

    CVarWrapper ENABLE_KEEP = cvarManager->getCvar("keep");
    if (!ENABLE_KEEP) return;
    own_Stat = ENABLE_KEEP.getBoolValue();
    if (ImGui::Checkbox("Keep the replays?", &keep)) { ENABLE_KEEP.setValue(keep); }
    if (ImGui::IsItemHovered()) { ImGui::SetTooltip("Enable or disable keep"); }

    ImGui::Text("");
    if (replay_path == "" || plugin_path == "")
    {
        ImGui::Text("IMPOSSIBLE :O , Replay_path or plugin path is empty !");
        return;
    }

    if (ImGui::Button("Save Data")) 
    {
        if (replay_path == "" || plugin_path == "") {return;}

        replay_path = convToBackSlash(replay_path);
        plugin_path = convToBackSlash(plugin_path);
        saveDATA(replay_path, plugin_path);
        manageReplayFiles(replay_path, plugin_path, keep);
        getData(replay_path, plugin_path);
        replay_path = convToUndoBackSlash(replay_path);
        plugin_path = convToUndoBackSlash(plugin_path);
    }

    ImGui::Text("");
    ImGui::Text("HeatMap Menu");

    static char namePlayer[256] = "";
    ImGui::InputText("Name Of Player", namePlayer, 256);

    const char* items[] = { "1", "2", "3" };
    ImGui::Combo("Mode de jeu", &modeDeJeu, items, IM_ARRAYSIZE(items));
    //ImGui::Text("Value: %d", modeDeJeu);

    if (modeDeJeu != 0 && modeDeJeu != 1 && modeDeJeu != 2)
        return;

    if (ImGui::Button("Show Heat map")) 
    {
        name_player = namePlayer;
        std::string python_command = "cd /d " + plugin_path + " && .\\.venv2\\Scripts\\python.exe .\\displayHeatMap.py " + name_player + " " + st((modeDeJeu+1));
        system(python_command.c_str());
    }
}

void Lotus::initVariable()
{
    std::string replayDirectory = "..\\..\\Lotus";
    std::string replayFilePath = replayDirectory + "\\replay_path.txt";

    if (std::filesystem::exists(replayFilePath)) {
        std::ifstream replayFile(replayFilePath);
        if (replayFile.is_open()) {
            std::getline(replayFile, replay_path);
            replayFile.close();
        }
        else {
            std::cout << "Erreur : Impossible d'ouvrir le fichier replay_path.txt pour la lecture." << std::endl;
        }
    }
    else {
        std::cout << "Erreur : Le fichier replay_path.txt n'existe pas." << std::endl;
    }

    std::string lotusDirectory = "..\\..\\Lotus";
    std::string pluginFilePath = lotusDirectory + "\\plugin_path.txt";

    if (std::filesystem::exists(pluginFilePath)) {
        std::ifstream pluginFile(pluginFilePath);
        if (pluginFile.is_open()) {
            std::getline(pluginFile, plugin_path);
            pluginFile.close();
        }
        else {
            std::cout << "Erreur : Impossible d'ouvrir le fichier plugin_path.txt pour la lecture." << std::endl;
        }
    }
    else {
        std::cout << "Erreur : Le fichier plugin_path.txt n'existe pas." << std::endl;
    }
    setPATH(plugin_path, replay_path);
}