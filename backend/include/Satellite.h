#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>
#include <ctime>
#include "SGP4.h"
#include "Tle.h"

enum class SatelliteType
{
    SpaceStation,
    Weather,
    EarthResources,
    SyntheticApertureRadar,
    SearchAndRescue,
    DisasterMonitoring,
    TrackingAndDataRelay,
    Argos,
    Planet,
    Spire,

    ActiveGeosynchronous,
    GeoProtectedZone,
    GeoProtectedZonePlus,
    Intelsat,
    SES,
    Eutelsat,
    Telesat,
    Starlink,
    OneWeb,
    Qianfan,
    HulianwangDigui,
    Kuiper,
    IridiumNext,
    Orbcomm,
    Globalstar,
    AmateurRadio,
    SatNOGS,
    ExperimentalComm,
    OtherComm,

    GNSS,
    GPS,
    GLONASS,
    Galileo,
    BeiDou,
    SatelliteBasedAugmentation,

    SpaceAndEarthScience,
    Geodetic,
    Engineering,
    Education,

    MiscellaneousMilitary,
    RadarCalibration,
    CubeSats
};

struct SatelliteDTO
{
    std::string name, colour;
    double lat, lon, alt;
    SatelliteDTO()
    {
    }
    SatelliteDTO(std::string name, std::string colour, double lat, double lon, double alt)
    {
        this->name = name;
        this->colour = colour;
        this->lat = lat;
        this->lon = lon;
        this->alt = alt;
    }
};

class Satellite
{
private:
    SatelliteType satelliteType;
    std::string name, colour, TleLineOne, TleLineTwo;
    std::unique_ptr<libsgp4::SGP4> propogator;

public:
    Satellite();
    Satellite(std::string name, SatelliteType satelliteType, std::string colour, std::string TLE1, std::string TLE2);
    std::string getName() { return name; };
    libsgp4::CoordGeodetic getCurrentPosition(std::time_t startDate, double tSince);
    libsgp4::Vector getCurrentVelocity(std::time_t startDate, double tSince);
    SatelliteType getSatelliteType() { return satelliteType; }
    std::string getSatelliteTypeStr();
    SatelliteDTO getDTO(std::time_t startDate, double tSince);
};
