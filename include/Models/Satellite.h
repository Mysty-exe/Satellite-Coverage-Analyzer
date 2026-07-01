#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>
#include <ctime>
#include "sgp4.h"
#include "tle.h"

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

class Satellite
{
private:
    SatelliteType satelliteType;
    std::string name;
    std::unique_ptr<libsgp4::SGP4> propogator;

public:
    Satellite();
    Satellite(std::string name, SatelliteType satelliteType, std::string TLE1, std::string TLE2);
    libsgp4::CoordGeodetic getCurrentPosition();
    libsgp4::Vector getCurrentVelocity();
    SatelliteType getSatelliteType() { return satelliteType; }
    std::string getSatelliteTypeStr();
};
