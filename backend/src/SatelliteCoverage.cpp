#include <iostream>
#include <fstream>
#include <string>
#include <emscripten/bind.h>
#include "Satellite.h"
#include "httplib.h"

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
    std::make_pair(SatelliteType::GeoProtectedZone, "gpz"),
    std::make_pair(SatelliteType::GeoProtectedZonePlus, "gpz-plus"),
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

std::string loadData()
{
    std::vector<Satellite> satellites;

    httplib::Client cli("celestrak.org");

    for (int i = 0; i < satelliteFiles.size(); i++)
    {
        auto res = cli.Get("/NORAD/elements/gp.php?GROUP=" + satelliteFiles[i].second + "&FORMAT=TLE");

        if (!res)
            std::cout << "Couldn't Connect to Web Server." << std::endl;

        if (res)
        {
            std::cout << "Status: " << res->status << std::endl;

            if (res->status == 200)
            {
                std::cout << "Path: " + satelliteFiles[i].second + "&FORMAT = TLE" << std::endl;
                std::cout << "Data successfully read from site.\n\n";

                std::ofstream satelliteData("cache/" + satelliteFiles[i].second + ".tle");

                if (!satelliteData.is_open())
                {
                    std::cout << "cache/" + satelliteFiles[i].second + ".tle" << std::endl;
                    std::cerr << "Error: Could not open the file!" << std::endl;
                    return cli.host();
                }

                satelliteData << res->body;

                satelliteData.close();
            }

            else if (res->status == 403)
            {
                std::cout << "Path: " + satelliteFiles[i].second + "&FORMAT = TLE" << std::endl;
                std::cerr << "Error: Data Has Not Been Updated.\n\n";
            }

            else
            {
                std::cout << "Path: " + satelliteFiles[i].second + "&FORMAT = TLE" << std::endl;
                std::cout << "Error Downloading Data From Site.";
            }
        }

        std::ifstream satelliteData("cache/" + satelliteFiles[i].second + ".tle");

        if (!satelliteData.is_open())
        {
            std::cerr << "Error: Could not open the file!" << std::endl;
            return cli.host();
        }

        std::string line, currentName;
        std::string currentTLELine1, currentTLELine2;

        int tleLine = 1;
        while (std::getline(satelliteData, line))
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
                    satellites.push_back(Satellite(currentName, satelliteFiles[i].first, currentTLELine1, currentTLELine2));

                tleLine = (tleLine + 1 > 3) ? 1 : tleLine + 1;
            }
        }

        satelliteData.close();
    }

    return cli.host();
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("loadData", &loadData);
}
