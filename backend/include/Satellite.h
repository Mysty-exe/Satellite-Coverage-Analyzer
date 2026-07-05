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
    std::string name;
    double lat, lon, vel;
    SatelliteDTO()
    {
    }
    SatelliteDTO(std::string name, double lat, double lon)
    {
        this->name = name;
        this->lat = lat;
        this->lon = lon;
    }
};

class Satellite
{
private:
    SatelliteType satelliteType;
    std::string name, TleLineOne, TleLineTwo;
    std::unique_ptr<libsgp4::SGP4> propogator;

public:
    Satellite();
    Satellite(std::string name, SatelliteType satelliteType, std::string TLE1, std::string TLE2);
    std::string getName() { return name; };
    libsgp4::CoordGeodetic getCurrentPosition();
    libsgp4::Vector getCurrentVelocity();
    SatelliteType getSatelliteType() { return satelliteType; }
    std::string getSatelliteTypeStr();
    SatelliteDTO getDTO();
};
