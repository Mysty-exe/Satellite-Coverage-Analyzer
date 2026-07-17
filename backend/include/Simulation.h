#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <utility>
#include <emscripten/bind.h>
#include <ctime>
#include "Satellite.h"

class Simulation
{
private:
    std::vector<std::pair<std::string, std::tuple<SatelliteType, std::string>>> satelliteFiles;
    std::vector<std::pair<SatelliteType, std::vector<Satellite>>> satellites;
    std::time_t startDate;

public:
    Simulation();
    std::time_t getStartDate() { return startDate; };
    void initializeSatelliteGroup(std::string group, std::string data);
    std::tuple<SatelliteType, std::string> getSatelliteType(std::string group);
    std::vector<std::string> getSatelliteGroups();
    std::vector<SatelliteDTO> getSatellitesDTO(std::string group, std::time_t startDate, double tSince);
};
