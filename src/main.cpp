#include <iostream>
#include <Models/Satellite.h>
#include <httplib.h>
#include <fstream>
#include <string>

int main()
{
    std::vector<Satellite> satellites;

    httplib::Client cli("celestrak.org");

    auto res = cli.Get("/NORAD/elements/gp.php?GROUP=stations&FORMAT=TLE");

    if (!res)
        std::cout << "Couldn't Connect to Web Server." << std::endl;

    if (res)
    {
        std::cout << "Status: " << res->status << std::endl;

        if (res->status == 200)
        {
            std::cout << "Data successfully read from site.\n\n";

            std::ofstream satelliteData("cache/satellites_data.tle");

            if (!satelliteData.is_open())
            {
                std::cerr << "Error: Could not open the file!" << std::endl;
                return 1;
            }

            satelliteData << res->body;

            satelliteData.close();
        }

        else if (res->status == 403)
        {
            std::cerr << "Error: Data Has Not Been Updated" << std::endl;
        }
    }

    std::ifstream satelliteData("cache/satellites_data.tle");

    if (!satelliteData.is_open())
    {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    std::string line;
    std::string currentName;
    std::vector<std::string> currentTLELine1;
    std::vector<std::string> currentTLELine2;

    int tleLine = 1;
    while (std::getline(satelliteData, line))
    {
        if (!line.empty())
        {
            if (tleLine == 1)
                currentName = line;

            else
            {
                std::string data;
                std::vector<std::string> currentTLELine;
                for (int i = 0; i < line.size() - 1; i++)
                {
                    if (line[i] != ' ')
                        data += line[i];
                    else if (!data.empty())
                    {
                        currentTLELine.push_back(data);
                        data = "";
                    }
                }

                if (data != "")
                    currentTLELine.push_back(data);

                if (tleLine == 2)
                    currentTLELine1 = currentTLELine;
                if (tleLine == 3)
                    currentTLELine2 = currentTLELine;
            }

            if (tleLine == 3)
                satellites.push_back(Satellite(currentName, currentTLELine1, currentTLELine2));

            tleLine = (tleLine + 1 > 3) ? 1 : tleLine + 1;
        }
    }

    satelliteData.close();

    return 0;
}
