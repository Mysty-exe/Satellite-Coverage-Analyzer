#include <iostream>
#include <string>
#include <sstream>
#include <emscripten/bind.h>
#include "Satellite.h"

class Simulation
{
private:
    std::vector<std::pair<SatelliteType, std::string>> satelliteFiles;
    std::vector<std::pair<SatelliteType, std::vector<Satellite>>> satellites;

public:
    Simulation();
    void initializeSatelliteGroup(std::string group, std::string data);
    SatelliteType getSatelliteType(std::string group);
    std::vector<std::string> getSatelliteGroups();
    std::vector<SatelliteDTO> getSatellitesDTO(std::string group);
};