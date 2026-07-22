#include <Simulation.h>

Simulation::Simulation()
{
    satelliteGroupTypes =
        {
            {"Earth Observation",
             {std::make_pair(SatelliteType::SpaceStation, 0),
              std::make_pair(SatelliteType::Weather, 0),
              std::make_pair(SatelliteType::EarthResources, 0),
              std::make_pair(SatelliteType::SyntheticApertureRadar, 0),
              std::make_pair(SatelliteType::SearchAndRescue, 0),
              std::make_pair(SatelliteType::DisasterMonitoring, 0),
              std::make_pair(SatelliteType::TrackingAndDataRelay, 0),
              std::make_pair(SatelliteType::Argos, 0),
              std::make_pair(SatelliteType::Planet, 0),
              std::make_pair(SatelliteType::Spire, 0)}},

            {"Communication",
             {std::make_pair(SatelliteType::ActiveGeosynchronous, 0),
              std::make_pair(SatelliteType::Intelsat, 0),
              std::make_pair(SatelliteType::SES, 0),
              std::make_pair(SatelliteType::Eutelsat, 0),
              std::make_pair(SatelliteType::Telesat, 0),
              std::make_pair(SatelliteType::Starlink, 0),
              std::make_pair(SatelliteType::OneWeb, 0),
              std::make_pair(SatelliteType::Qianfan, 0),
              std::make_pair(SatelliteType::HulianwangDigui, 0),
              std::make_pair(SatelliteType::Kuiper, 0),
              std::make_pair(SatelliteType::IridiumNext, 0),
              std::make_pair(SatelliteType::Orbcomm, 0),
              std::make_pair(SatelliteType::Globalstar, 0),
              std::make_pair(SatelliteType::AmateurRadio, 0),
              std::make_pair(SatelliteType::SatNOGS, 0),
              std::make_pair(SatelliteType::ExperimentalComm, 0),
              std::make_pair(SatelliteType::OtherComm, 0)}},

            {"Navigation",
             {std::make_pair(SatelliteType::GNSS, 0),
              std::make_pair(SatelliteType::GPS, 0),
              std::make_pair(SatelliteType::GLONASS, 0),
              std::make_pair(SatelliteType::Galileo, 0),
              std::make_pair(SatelliteType::BeiDou, 0),
              std::make_pair(SatelliteType::SatelliteBasedAugmentation, 0)}},

            {"Science & Research",
             {std::make_pair(SatelliteType::SpaceAndEarthScience, 0),
              std::make_pair(SatelliteType::Geodetic, 0),
              std::make_pair(SatelliteType::Engineering, 0),
              std::make_pair(SatelliteType::Education, 0)}},

            {"Miscellaneous",
             {std::make_pair(SatelliteType::MiscellaneousMilitary, 0),
              std::make_pair(SatelliteType::RadarCalibration, 0),
              std::make_pair(SatelliteType::CubeSats, 0)}}};

    satelliteFiles = {// Earth Observation / Mission
                      {"stations", {SatelliteType::SpaceStation, "blue"}},
                      {"weather", {SatelliteType::Weather, "blue"}},
                      {"resource", {SatelliteType::EarthResources, "blue"}},
                      {"sar", {SatelliteType::SyntheticApertureRadar, "blue"}},
                      {"sarsat", {SatelliteType::SearchAndRescue, "blue"}},
                      {"dmc", {SatelliteType::DisasterMonitoring, "blue"}},
                      {"tdrss", {SatelliteType::TrackingAndDataRelay, "blue"}},
                      {"argos", {SatelliteType::Argos, "blue"}},
                      {"planet", {SatelliteType::Planet, "blue"}},
                      {"spire", {SatelliteType::Spire, "blue"}},

                      // Communications
                      {"geo", {SatelliteType::ActiveGeosynchronous, "aliceblue"}},
                      {"intelsat", {SatelliteType::Intelsat, "aliceblue"}},
                      {"ses", {SatelliteType::SES, "aliceblue"}},
                      {"eutelsat", {SatelliteType::Eutelsat, "aliceblue"}},
                      {"telesat", {SatelliteType::Telesat, "aliceblue"}},
                      {"starlink", {SatelliteType::Starlink, "aliceblue"}},
                      {"oneweb", {SatelliteType::OneWeb, "aliceblue"}},
                      {"qianfan", {SatelliteType::Qianfan, "aliceblue"}},
                      {"hulianwang", {SatelliteType::HulianwangDigui, "aliceblue"}},
                      {"kuiper", {SatelliteType::Kuiper, "aliceblue"}},
                      {"iridium-NEXT", {SatelliteType::IridiumNext, "aliceblue"}},
                      {"orbcomm", {SatelliteType::Orbcomm, "aliceblue"}},
                      {"globalstar", {SatelliteType::Globalstar, "aliceblue"}},
                      {"amateur", {SatelliteType::AmateurRadio, "aliceblue"}},
                      {"satnogs", {SatelliteType::SatNOGS, "aliceblue"}},
                      {"x-comm", {SatelliteType::ExperimentalComm, "aliceblue"}},
                      {"other-comm", {SatelliteType::OtherComm, "aliceblue"}},

                      // Navigation
                      {"gnss", {SatelliteType::GNSS, "darkslateblue"}},
                      {"gps-ops", {SatelliteType::GPS, "darkslateblue"}},
                      {"glo-ops", {SatelliteType::GLONASS, "darkslateblue"}},
                      {"galileo", {SatelliteType::Galileo, "darkslateblue"}},
                      {"beidou", {SatelliteType::BeiDou, "darkslateblue"}},
                      {"sbas", {SatelliteType::SatelliteBasedAugmentation, "darkslateblue"}},

                      // Science & Research
                      {"science", {SatelliteType::SpaceAndEarthScience, "darkcyan"}},
                      {"geodetic", {SatelliteType::Geodetic, "darkcyan"}},
                      {"engineering", {SatelliteType::Engineering, "darkcyan"}},
                      {"education", {SatelliteType::Education, "darkcyan"}},

                      // Government & Miscellaneous
                      {"military", {SatelliteType::MiscellaneousMilitary, "darkorchid"}},
                      {"radar", {SatelliteType::RadarCalibration, "darkorchid"}},
                      {"cubesat", {SatelliteType::CubeSats, "darkorchid"}}};

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

    std::string g = getSatelliteGroupType(group);
    for (auto &pair : satelliteGroupTypes[g])
    {
        if (pair.first == groupType)
        {
            pair.second = pair.second + sats.size();
            break;
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

std::string Simulation::getSatelliteGroupType(std::string type)
{
    SatelliteType satelliteType = std::get<0>(getSatelliteType(type));

    switch (satelliteType)
    {
    // Earth Observation
    case SatelliteType::SpaceStation:
    case SatelliteType::Weather:
    case SatelliteType::EarthResources:
    case SatelliteType::SyntheticApertureRadar:
    case SatelliteType::SearchAndRescue:
    case SatelliteType::DisasterMonitoring:
    case SatelliteType::TrackingAndDataRelay:
    case SatelliteType::Argos:
    case SatelliteType::Planet:
    case SatelliteType::Spire:
        return "Earth Observation";

    // Communication
    case SatelliteType::ActiveGeosynchronous:
    case SatelliteType::Intelsat:
    case SatelliteType::SES:
    case SatelliteType::Eutelsat:
    case SatelliteType::Telesat:
    case SatelliteType::Starlink:
    case SatelliteType::OneWeb:
    case SatelliteType::Qianfan:
    case SatelliteType::HulianwangDigui:
    case SatelliteType::Kuiper:
    case SatelliteType::IridiumNext:
    case SatelliteType::Orbcomm:
    case SatelliteType::Globalstar:
    case SatelliteType::AmateurRadio:
    case SatelliteType::SatNOGS:
    case SatelliteType::ExperimentalComm:
    case SatelliteType::OtherComm:
        return "Communication";

    // Navigation
    case SatelliteType::GNSS:
    case SatelliteType::GPS:
    case SatelliteType::GLONASS:
    case SatelliteType::Galileo:
    case SatelliteType::BeiDou:
    case SatelliteType::SatelliteBasedAugmentation:
        return "Navigation";

    // Science
    case SatelliteType::SpaceAndEarthScience:
    case SatelliteType::Geodetic:
    case SatelliteType::Engineering:
    case SatelliteType::Education:
        return "Science & Research";

    // Miscellaneous
    case SatelliteType::MiscellaneousMilitary:
    case SatelliteType::RadarCalibration:
    case SatelliteType::CubeSats:
        return "Miscellaneous";

    default:
        return "Unknown";
    }
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

int Simulation::getSatellitesNum(std::string group)
{
    SatelliteType groupType = std::get<0>(getSatelliteType(group));
    for (int i = 0; i < satellites.size(); i++)
    {
        if (satellites[i].first == groupType)
        {
            return satellites[i].second.size();
        }
    }
}

std::vector<Satellite> &Simulation::getSatelliteGroup(std::string group)
{
    SatelliteType groupType = std::get<0>(getSatelliteType(group));
    for (int i = 0; i < satellites.size(); i++)
    {
        if (satellites[i].first == groupType)
            return satellites[i].second;
    }
}

std::vector<std::string> Simulation::getSatelliteTypes(std::string group)
{
    std::vector<std::string> result;
    for (auto types : satelliteGroupTypes[group])
        result.push_back(Satellite::getSatelliteTypeStr(types.first));

    return result;
}

std::vector<int> Simulation::getSatelliteTypeInts(std::string group)
{
    std::vector<int> result;
    for (auto types : satelliteGroupTypes[group])
        result.push_back(types.second);

    return result;
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

int getSatellitesNum(std::string group)
{
    return simulation.getSatellitesNum(group);
}

SatelliteDetails getSpecificSatellite(std::string group, int index, double tSince)
{
    return simulation.getSatelliteGroup(group)[index].getDetails(simulation.getStartDate(), tSince);
}

std::vector<std::string> getSatelliteTypes(std::string group)
{
    return simulation.getSatelliteTypes(group);
}

std::vector<int> getSatelliteTypeInts(std::string group)
{
    return simulation.getSatelliteTypeInts(group);
}

std::string getSatelliteGroupColour(std::string group)
{
    if (group == "Earth Observation")
        return "blue";

    if (group == "Communication")
        return "aliceblue";

    if (group == "Navigation")
        return "darkslateblue";

    if (group == "Science & Research")
        return "darkcyan";

    if (group == "Miscellaneous")
        return "darkorchid";
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::value_object<SatelliteDTO>("SatelliteDTO")
        .field("name", &SatelliteDTO::name)
        .field("colour", &SatelliteDTO::colour)
        .field("lat", &SatelliteDTO::lat)
        .field("lon", &SatelliteDTO::lon)
        .field("alt", &SatelliteDTO::alt);

    emscripten::value_object<SatelliteDetails>("SatelliteDetails")
        .field("name", &SatelliteDetails::name)
        .field("colour", &SatelliteDetails::colour)
        .field("epoch", &SatelliteDetails::epoch)
        .field("designator", &SatelliteDetails::designator)

        .field("NORAD", &SatelliteDetails::NORAD)
        .field("orbitNumber", &SatelliteDetails::orbitNumber)

        .field("lat", &SatelliteDetails::lat)
        .field("lon", &SatelliteDetails::lon)
        .field("alt", &SatelliteDetails::alt)

        .field("velX", &SatelliteDetails::velX)
        .field("velY", &SatelliteDetails::velY)
        .field("velZ", &SatelliteDetails::velZ)

        .field("meanMotion", &SatelliteDetails::meanMotion)
        .field("meanMotionDT2", &SatelliteDetails::meanMotionDT2)
        .field("meanMotionDDT6", &SatelliteDetails::meanMotionDDT6)
        .field("bSTAR", &SatelliteDetails::bSTAR)

        .field("inclination", &SatelliteDetails::inclination)
        .field("RAN", &SatelliteDetails::RAN)
        .field("eccentricity", &SatelliteDetails::eccentricity)
        .field("argumentPerigee", &SatelliteDetails::argumentPerigee)
        .field("meanAnomaly", &SatelliteDetails::meanAnomaly);

    emscripten::function("initializeSatelliteGroup", &initializeSatelliteGroup);
    emscripten::register_vector<std::string>("SatelliteGroups");
    emscripten::function("getSatelliteGroups", &getSatelliteGroups);
    emscripten::register_vector<SatelliteDTO>("VectorSatellite");
    emscripten::function("getSatellitesDTO", &getSatellitesDTO);
    emscripten::function("getSatellitesNum", &getSatellitesNum);
    emscripten::function("getSpecificSatellite", &getSpecificSatellite);
    emscripten::function("getSatelliteTypes", &getSatelliteTypes);
    emscripten::register_vector<int>("SatelliteNums");
    emscripten::function("getSatelliteTypeInts", &getSatelliteTypeInts);
    emscripten::function("getSatelliteGroupColour", &getSatelliteGroupColour);
}
