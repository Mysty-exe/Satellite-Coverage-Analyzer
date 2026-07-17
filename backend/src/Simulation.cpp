#include <Simulation.h>

Simulation::Simulation()
{
    satelliteFiles =
        {
            // Earth Observation / Mission
            {"stations", {SatelliteType::SpaceStation, "deepskyblue"}},
            {"weather", {SatelliteType::Weather, "deepskyblue"}},
            {"resource", {SatelliteType::EarthResources, "deepskyblue"}},
            {"sar", {SatelliteType::SyntheticApertureRadar, "deepskyblue"}},
            {"sarsat", {SatelliteType::SearchAndRescue, "deepskyblue"}},
            {"dmc", {SatelliteType::DisasterMonitoring, "deepskyblue"}},
            {"tdrss", {SatelliteType::TrackingAndDataRelay, "deepskyblue"}},
            {"argos", {SatelliteType::Argos, "deepskyblue"}},
            {"planet", {SatelliteType::Planet, "deepskyblue"}},
            {"spire", {SatelliteType::Spire, "deepskyblue"}},

            // Communications
            {"geo", {SatelliteType::ActiveGeosynchronous, "mediumorchid"}},
            {"intelsat", {SatelliteType::Intelsat, "mediumorchid"}},
            {"ses", {SatelliteType::SES, "mediumorchid"}},
            {"eutelsat", {SatelliteType::Eutelsat, "mediumorchid"}},
            {"telesat", {SatelliteType::Telesat, "mediumorchid"}},
            {"starlink", {SatelliteType::Starlink, "mediumorchid"}},
            {"oneweb", {SatelliteType::OneWeb, "mediumorchid"}},
            {"qianfan", {SatelliteType::Qianfan, "mediumorchid"}},
            {"hulianwang", {SatelliteType::HulianwangDigui, "mediumorchid"}},
            {"kuiper", {SatelliteType::Kuiper, "mediumorchid"}},
            {"iridium-NEXT", {SatelliteType::IridiumNext, "mediumorchid"}},
            {"orbcomm", {SatelliteType::Orbcomm, "mediumorchid"}},
            {"globalstar", {SatelliteType::Globalstar, "mediumorchid"}},
            {"amateur", {SatelliteType::AmateurRadio, "mediumorchid"}},
            {"satnogs", {SatelliteType::SatNOGS, "mediumorchid"}},
            {"x-comm", {SatelliteType::ExperimentalComm, "mediumorchid"}},
            {"other-comm", {SatelliteType::OtherComm, "mediumorchid"}},

            // Navigation
            {"gnss", {SatelliteType::GNSS, "gold"}},
            {"gps-ops", {SatelliteType::GPS, "gold"}},
            {"glo-ops", {SatelliteType::GLONASS, "gold"}},
            {"galileo", {SatelliteType::Galileo, "gold"}},
            {"beidou", {SatelliteType::BeiDou, "gold"}},
            {"sbas", {SatelliteType::SatelliteBasedAugmentation, "gold"}},

            // Science & Research
            {"science", {SatelliteType::SpaceAndEarthScience, "limegreen"}},
            {"geodetic", {SatelliteType::Geodetic, "limegreen"}},
            {"engineering", {SatelliteType::Engineering, "limegreen"}},
            {"education", {SatelliteType::Education, "limegreen"}},

            // Government & Miscellaneous
            {"military", {SatelliteType::MiscellaneousMilitary, "tomato"}},
            {"radar", {SatelliteType::RadarCalibration, "tomato"}},
            {"cubesat", {SatelliteType::CubeSats, "tomato"}}};

    startDate = std::time(nullptr);
};

void Simulation::initializeSatelliteGroup(std::string group, std::string data)
{
    std::time_t now = std::time(nullptr);
    std::tm *local_time = std::localtime(&now);

    std::string line, currentName;
    std::string currentTLELine1, currentTLELine2;
    auto type = getSatelliteType(group);
    SatelliteType groupType = std::get<0>(type);
    std::string colour = std::get<1>(type);
    std::vector<Satellite> sats;

    int tleLine = 1;
    std::stringstream ss(data);
    while (std::getline(ss, line))
    {
        if (!line.empty())
        {
            if (tleLine == 1)
                currentName = line;

            else
            {
                if (tleLine == 2)
                    currentTLELine1 = line.substr(0, line.size() - 1);
                if (tleLine == 3)
                    currentTLELine2 = line.substr(0, line.size() - 1);
            }

            if (tleLine == 3)
            {
                Satellite s = Satellite(currentName, groupType, colour, currentTLELine1, currentTLELine2);
                sats.push_back(std::move(s));
            }

            tleLine = (tleLine + 1 > 3) ? 1 : tleLine + 1;
        }
    }

    satellites.push_back(std::make_pair(groupType, std::move(sats)));
}

std::tuple<SatelliteType, std::string> Simulation::getSatelliteType(std::string group)
{
    for (int i = 0; i < satelliteFiles.size(); i++)
        if (satelliteFiles[i].first == group)
            return satelliteFiles[i].second;
}

std::vector<std::string> Simulation::getSatelliteGroups()
{
    std::vector<std::string> groups;
    for (int i = 0; i < satelliteFiles.size(); i++)
        groups.push_back(satelliteFiles[i].first);

    return groups;
}

std::vector<SatelliteDTO> Simulation::getSatellitesDTO(std::string group, std::time_t startDate, double tSince)
{
    SatelliteType groupType = std::get<0>(getSatelliteType(group));

    for (int i = 0; i < satellites.size(); i++)
    {
        if (satellites[i].first == groupType)
        {
            std::vector<SatelliteDTO> data;
            for (auto &sat : satellites[i].second)
            {
                data.push_back(sat.getDTO(startDate, tSince));
            }

            return data;
        }
    }

    return {};
}

Simulation simulation;
void initializeSatelliteGroup(std::string group, std::string data)
{
    simulation.initializeSatelliteGroup(group, data);
}

std::vector<SatelliteDTO> getSatellitesDTO(std::string group, double tSince)
{
    return simulation.getSatellitesDTO(group, simulation.getStartDate(), tSince);
}

std::vector<std::string> getSatelliteGroups()
{
    return simulation.getSatelliteGroups();
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::value_object<SatelliteDTO>("Satellite")
        .field("name", &SatelliteDTO::name)
        .field("colour", &SatelliteDTO::colour)
        .field("lat", &SatelliteDTO::lat)
        .field("lon", &SatelliteDTO::lon)
        .field("alt", &SatelliteDTO::alt);
    emscripten::function("initializeSatelliteGroup", &initializeSatelliteGroup);
    emscripten::register_vector<std::string>("SatelliteGroups");
    emscripten::function("getSatelliteGroups", &getSatelliteGroups);
    emscripten::register_vector<SatelliteDTO>("VectorSatellite");
    emscripten::function("getSatellitesDTO", &getSatellitesDTO);
}
