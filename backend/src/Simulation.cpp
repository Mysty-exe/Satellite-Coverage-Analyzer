#include <Simulation.h>

Simulation::Simulation()
{
    satelliteFiles = {
        std::make_pair(SatelliteType::SpaceStation, "stations"),
        std::make_pair(SatelliteType::Weather, "weather"),
        std::make_pair(SatelliteType::EarthResources, "resource"),
        std::make_pair(SatelliteType::SyntheticApertureRadar, "sar"),
        std::make_pair(SatelliteType::SearchAndRescue, "sarsat"),
        std::make_pair(SatelliteType::DisasterMonitoring, "dmc"),
        std::make_pair(SatelliteType::TrackingAndDataRelay, "tdrss"),
        std::make_pair(SatelliteType::Argos, "argos"),
        std::make_pair(SatelliteType::Planet, "planet"),
        std::make_pair(SatelliteType::Spire, "spire"),

        std::make_pair(SatelliteType::ActiveGeosynchronous, "geo"),
        std::make_pair(SatelliteType::Intelsat, "intelsat"),
        std::make_pair(SatelliteType::SES, "ses"),
        std::make_pair(SatelliteType::Eutelsat, "eutelsat"),
        std::make_pair(SatelliteType::Telesat, "telesat"),
        std::make_pair(SatelliteType::Starlink, "starlink"),
        std::make_pair(SatelliteType::OneWeb, "oneweb"),
        std::make_pair(SatelliteType::Qianfan, "qianfan"),
        std::make_pair(SatelliteType::HulianwangDigui, "hulianwang"),
        std::make_pair(SatelliteType::Kuiper, "kuiper"),
        std::make_pair(SatelliteType::IridiumNext, "iridium-NEXT"),
        std::make_pair(SatelliteType::Orbcomm, "orbcomm"),
        std::make_pair(SatelliteType::Globalstar, "globalstar"),
        std::make_pair(SatelliteType::AmateurRadio, "amateur"),
        std::make_pair(SatelliteType::SatNOGS, "satnogs"),
        std::make_pair(SatelliteType::ExperimentalComm, "x-comm"),
        std::make_pair(SatelliteType::OtherComm, "other-comm"),

        std::make_pair(SatelliteType::GNSS, "gnss"),
        std::make_pair(SatelliteType::GPS, "gps-ops"),
        std::make_pair(SatelliteType::GLONASS, "glo-ops"),
        std::make_pair(SatelliteType::Galileo, "galileo"),
        std::make_pair(SatelliteType::BeiDou, "beidou"),
        std::make_pair(SatelliteType::SatelliteBasedAugmentation, "sbas"),

        std::make_pair(SatelliteType::SpaceAndEarthScience, "science"),
        std::make_pair(SatelliteType::Geodetic, "geodetic"),
        std::make_pair(SatelliteType::Engineering, "engineering"),
        std::make_pair(SatelliteType::Education, "education"),

        std::make_pair(SatelliteType::MiscellaneousMilitary, "military"),
        std::make_pair(SatelliteType::RadarCalibration, "radar"),
        std::make_pair(SatelliteType::CubeSats, "cubesat")};
}

void Simulation::initializeSatelliteGroup(std::string group, std::string data)
{
    std::string line, currentName;
    std::string currentTLELine1, currentTLELine2;
    SatelliteType groupType = getSatelliteType(group);
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
                Satellite s = Satellite(currentName, groupType, currentTLELine1, currentTLELine2);
                sats.push_back(std::move(s));
            }

            tleLine = (tleLine + 1 > 3) ? 1 : tleLine + 1;
        }
    }

    satellites.push_back(std::make_pair(groupType, std::move(sats)));
}

SatelliteType Simulation::getSatelliteType(std::string group)
{
    for (int i = 0; i < satelliteFiles.size(); i++)
        if (satelliteFiles[i].second == group)
            return satelliteFiles[i].first;
}

std::vector<std::string> Simulation::getSatelliteGroups()
{
    std::vector<std::string> groups;
    for (int i = 0; i < satelliteFiles.size(); i++)
        groups.push_back(satelliteFiles[i].second);

    return groups;
}

std::vector<SatelliteDTO> Simulation::getSatellitesDTO(std::string group)
{
    SatelliteType groupType = getSatelliteType(group);
    for (int i = 0; i < satellites.size(); i++)
    {
        if (satellites[i].first == groupType)
        {
            std::vector<SatelliteDTO> data;
            for (auto &sat : satellites[i].second)
            {
                data.push_back(sat.getDTO());
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

std::vector<SatelliteDTO> getSatellitesDTO(std::string group)
{
    return simulation.getSatellitesDTO(group);
}

std::vector<std::string> getSatelliteGroups()
{
    return simulation.getSatelliteGroups();
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::value_object<SatelliteDTO>("Satellite")
        .field("name", &SatelliteDTO::name)
        .field("lat", &SatelliteDTO::lat)
        .field("lon", &SatelliteDTO::lon)
        .field("alt", &SatelliteDTO::alt);
    emscripten::function("initializeSatelliteGroup", &initializeSatelliteGroup);
    emscripten::register_vector<std::string>("SatelliteGroups");
    emscripten::function("getSatelliteGroups", &getSatelliteGroups);
    emscripten::register_vector<SatelliteDTO>("VectorSatellite");
    emscripten::function("getSatellitesDTO", &getSatellitesDTO);
}
