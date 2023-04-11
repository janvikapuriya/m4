#include <iostream>
#include <fstream>
#include <string>

const int MAXIMUM_FILE_LENGTH = 200;
const int MAXIMUM_LINES_LENGTH = 200;
const int MAXIMUM_TEAMS_LENGTH = 200;

struct TeamRecord
{
    int win_game;
    int loss_game;
    int tie;
};

int main()
{
    std::ifstream TeamFile("teams.txt");
    if (!TeamFile)
    {
        std::cout << "Opning file error !!" << std::endl;
        return 1;
    }

    std::string FileNames;
    while (std::getline(TeamFile, FileNames))
    {
        FileNames.erase(std::remove(FileNames.begin(), FileNames.end(), '\n'), FileNames.end());
        tour(FileNames.c_str());
    }
    TeamFile.close();

    return 0;
}
void tour(const char *FileNames)
{
    char Tname[MAX_TEAMS_LEN];
    strncpy(Tname, FileNames, strlen(FileNames) - 4);
    Tname[strlen(FileNames) - 4] = '\0';

    std::ifstream GameFiles(FileNames);
    if (!GameFiles)
    {
        std::cout << "Opening Falied " << FileNames << std::endl;
        return;
    }

    std::string CheckLines;
    TeamRecord Records = {0, 0, 0};
    while (std::getline(GameFiles, CheckLines))
    {
        CheckLines.erase(std::remove(CheckLines.begin(), CheckLines.end(), '\n'), CheckLines.end());

        std::string::iterator it = std::find(CheckLines.begin(), CheckLines.end(), ',');
        if (it == CheckLines.end())
        {
            std::cout << "Couldn't find  " << FileNames << std::endl;
            continue;
        }
        else
        {
            *it = '\0';
            it++;
        }
        std::string::iterator dash_it = std::find(it, CheckLines.end(), '-');
        if (dash_it == CheckLines.end())
        {
            std::cout << "Couldn't findddd  " << FileNames << std::endl;
            continue;
        }
        else
        {
            *dash_it = '\0';
            dash_it++;
        }

        int myscore = std::stoi(dash_it);
        int YourTeamScore = std::stoi(it);

        if (myscore > YourTeamScore)
        {
            Records.win_game++;
        }
        else if (myscore < YourTeamScore)
        {
            Records.loss_game++;
        }
        else
        {
            Records.tie++;
        }
    }
    GameFiles.close();

    if (Records.win_game + Records.loss_game + Records.tie > 0)
    {
        double ercentage = (2.0 * Records.win_game + Records.tie) / (2.0 * (Records.win_game + Records.loss_game + Records.tie));
        std::cout << "results for " << Tname << ":\t" << ercentage << " (" << Records.win_game << "-" << Records.loss_game << "-" << Records.tie << ")" << std::endl;
    }
    else
    {
        std::cout << "No record found !!!!!! " << Tname << std::endl;
    }
}