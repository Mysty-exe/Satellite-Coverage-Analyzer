#include <Simulation.h>

Simulation::Simulation()
{
    satelliteFiles =
        {
            {"stations", {SatelliteType::SpaceStation, "white"}},
            {"weather", {SatelliteType::Weather, "deepskyblue"}},
            {"resource", {SatelliteType::EarthResources, "forestgreen"}},
            {"sar", {SatelliteType::SyntheticApertureRadar, "mediumpurple"}},
            {"sarsat", {SatelliteType::SearchAndRescue, "gold"}},
            {"dmc", {SatelliteType::DisasterMonitoring, "orange"}},
            {"tdrss", {SatelliteType::TrackingAndDataRelay, "hotpink"}},
            {"argos", {SatelliteType::Argos, "turquoise"}},
            {"planet", {SatelliteType::Planet, "mediumseagreen"}},
            {"spire", {SatelliteType::Spire, "dodgerblue"}},

            {"geo", {SatelliteType::ActiveGeosynchronous, "lightgray"}},
            {"intelsat", {SatelliteType::Intelsat, "royalblue"}},
            {"ses", {SatelliteType::SES, "steelblue"}},
            {"eutelsat", {SatelliteType::Eutelsat, "slateblue"}},
            {"telesat", {SatelliteType::Telesat, "cornflowerblue"}},
            {"starlink", {SatelliteType::Starlink, "azure"}},
            {"oneweb", {SatelliteType::OneWeb, "skyblue"}},
            {"qianfan", {SatelliteType::Qianfan, "tomato"}},
            {"hulianwang", {SatelliteType::HulianwangDigui, "indianred"}},
            {"kuiper", {SatelliteType::Kuiper, "mediumorchid"}},
            {"iridium-NEXT", {SatelliteType::IridiumNext, "silver"}},
            {"orbcomm", {SatelliteType::Orbcomm, "darkcyan"}},
            {"globalstar", {SatelliteType::Globalstar, "teal"}},
            {"amateur", {SatelliteType::AmateurRadio, "lime"}},
            {"satnogs", {SatelliteType::SatNOGS, "springgreen"}},
            {"x-comm", {SatelliteType::ExperimentalComm, "violet"}},
            {"other-comm", {SatelliteType::OtherComm, "lightslategray"}},

            {"gnss", {SatelliteType::GNSS, "yellow"}},
            {"gps-ops", {SatelliteType::GPS, "limegreen"}},
            {"glo-ops", {SatelliteType::GLONASS, "crimson"}},
            {"galileo", {SatelliteType::Galileo, "cornsilk"}},
            {"beidou", {SatelliteType::BeiDou, "crimson"}},
            {"sbas", {SatelliteType::SatelliteBasedAugmentation, "khaki"}},

            {"science", {SatelliteType::SpaceAndEarthScience, "beige"}},
            {"geodetic", {SatelliteType::Geodetic, "cyan"}},
            {"engineering", {SatelliteType::Engineering, "darkorange"}},
            {"education", {SatelliteType::Education, "blueviolet"}},

            {"military", {SatelliteType::MiscellaneousMilitary, "deeppink"}},
            {"radar", {SatelliteType::RadarCalibration, "orchid"}},
            {"cubesat", {SatelliteType::CubeSats, "darksalmon"}}};
}

void Simulation::initializeSatelliteGroup(std::string group, std::string data)
{
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

std::vector<SatelliteDTO> Simulation::getSatellitesDTO(std::string group)
{
    SatelliteType groupType = std::get<0>(getSatelliteType(group));
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
