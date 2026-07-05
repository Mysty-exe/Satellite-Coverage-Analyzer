#include <iostream>
#include <string>
#include <sstream>
#include <emscripten/bind.h>
#include "Satellite.h"

const std::vector<std::pair<SatelliteType, std::string>> satelliteFiles = {
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

SatelliteType getSatelliteType(std::string group)
{
    for (int i = 0; i < satelliteFiles.size(); i++)
        if (satelliteFiles[i].second == group)
            return satelliteFiles[i].first;
}

std::vector<std::string> getSatelliteGroups()
{
    std::vector<std::string> groups;
    for (int i = 0; i < satelliteFiles.size(); i++)
        groups.push_back(satelliteFiles[i].second);

    return groups;
}

std::vector<SatelliteDTO> getSatellitesDTO(std::string group, std::string data)
{
    std::vector<SatelliteDTO> satellites;

    std::string line, currentName;
    std::string currentTLELine1, currentTLELine2;

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
                Satellite s = Satellite(currentName, getSatelliteType(group), currentTLELine1, currentTLELine2);
                satellites.push_back(s.getDTO());
            }

            tleLine = (tleLine + 1 > 3) ? 1 : tleLine + 1;
        }
    }

    return satellites;
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::value_object<SatelliteDTO>("Satellite")
        .field("name", &SatelliteDTO::name)
        .field("lat", &SatelliteDTO::lat)
        .field("lon", &SatelliteDTO::lon);
    emscripten::register_vector<std::string>("SatelliteGroups");
    emscripten::function("getSatelliteGroups", &getSatelliteGroups);
    emscripten::register_vector<SatelliteDTO>("VectorSatellite");
    emscripten::function("getSatellitesDTO", &getSatellitesDTO);
}
