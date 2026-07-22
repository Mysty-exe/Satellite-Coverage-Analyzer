#include "Satellite.h"

Satellite::Satellite()
{
}

Satellite::Satellite(std::string name, SatelliteType satelliteType, std::string colour, std::string TLE1, std::string TLE2)
{
    this->name = name;
    this->satelliteType = satelliteType;
    this->colour = colour;
    this->TleLineOne = TLE1;
    this->TleLineTwo = TLE2;

    libsgp4::Tle TleObject = libsgp4::Tle(name, TLE1, TLE2);
    propogator = std::make_unique<libsgp4::SGP4>(TleObject);
}

libsgp4::CoordGeodetic Satellite::getCurrentPosition(std::time_t startDate, double tSince)
{
    startDate += tSince;
    std::tm *local_time = std::localtime(&startDate);

    libsgp4::DateTime currentTime = libsgp4::DateTime(local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

    try
    {
        libsgp4::Eci position = propogator->FindPosition(currentTime);
        return position.ToGeodetic();
    }
    catch (const std::exception &e)
    {
        return libsgp4::CoordGeodetic(0, 0, 0, false);
    }
}

libsgp4::Vector Satellite::getCurrentVelocity(std::time_t startDate, double tSince)
{
    startDate += tSince;
    std::tm *local_time = std::localtime(&startDate);

    libsgp4::DateTime currentTime = libsgp4::DateTime(local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

    try
    {
        libsgp4::Eci position = propogator->FindPosition(currentTime);
        return position.Velocity();
    }
    catch (const std::exception &e)
    {
        return libsgp4::Vector(0, 0, 0);
    }
}

std::string Satellite::getSatelliteTypeStr(SatelliteType satelliteType)
{
    switch (satelliteType)
    {
    case SatelliteType::SpaceStation:
        return "Space Station";
    case SatelliteType::Weather:
        return "Weather";
    case SatelliteType::EarthResources:
        return "Earth Resources";
    case SatelliteType::SyntheticApertureRadar:
        return "Synthetic Aperture Radar";
    case SatelliteType::SearchAndRescue:
        return "Search & Rescue";
    case SatelliteType::DisasterMonitoring:
        return "Disaster Monitoring";
    case SatelliteType::TrackingAndDataRelay:
        return "Tracking and Data Relay";
    case SatelliteType::Argos:
        return "ARGOS";
    case SatelliteType::Planet:
        return "Planet";
    case SatelliteType::Spire:
        return "Spire";

    case SatelliteType::ActiveGeosynchronous:
        return "Active Geosynchronous";
    case SatelliteType::GeoProtectedZone:
        return "GEO Protected Zone";
    case SatelliteType::GeoProtectedZonePlus:
        return "GEO Protected Zone Plus";
    case SatelliteType::Intelsat:
        return "Intelsat";
    case SatelliteType::SES:
        return "SES";
    case SatelliteType::Eutelsat:
        return "Eutelsat";
    case SatelliteType::Telesat:
        return "Telesat";
    case SatelliteType::Starlink:
        return "Starlink";
    case SatelliteType::OneWeb:
        return "OneWeb";
    case SatelliteType::Qianfan:
        return "Qianfan";
    case SatelliteType::HulianwangDigui:
        return "Hulianwang Digui";
    case SatelliteType::Kuiper:
        return "Kuiper";
    case SatelliteType::IridiumNext:
        return "Iridium NEXT";
    case SatelliteType::Orbcomm:
        return "Orbcomm";
    case SatelliteType::Globalstar:
        return "Globalstar";
    case SatelliteType::AmateurRadio:
        return "Amateur Radio";
    case SatelliteType::SatNOGS:
        return "SatNOGS";
    case SatelliteType::ExperimentalComm:
        return "Experimental Comm";
    case SatelliteType::OtherComm:
        return "Other Comm";

    case SatelliteType::GNSS:
        return "GNSS";
    case SatelliteType::GPS:
        return "GPS";
    case SatelliteType::GLONASS:
        return "GLONASS";
    case SatelliteType::Galileo:
        return "Galileo";
    case SatelliteType::BeiDou:
        return "BeiDou";
    case SatelliteType::SatelliteBasedAugmentation:
        return "Satellite Based Augmentation";

    case SatelliteType::SpaceAndEarthScience:
        return "Space & Earth Science";
    case SatelliteType::Geodetic:
        return "Geodetic";
    case SatelliteType::Engineering:
        return "Engineering";
    case SatelliteType::Education:
        return "Education";

    case SatelliteType::MiscellaneousMilitary:
        return "Miscellaneous Military";
    case SatelliteType::RadarCalibration:
        return "Radar Calibration";
    case SatelliteType::CubeSats:
        return "CubeSats";
    }

    return "Unknown";
}

SatelliteDTO Satellite::getDTO(std::time_t startDate, double tSince)
{
    libsgp4::CoordGeodetic pos = getCurrentPosition(startDate, tSince);
    return SatelliteDTO(name, colour, pos.latitude, pos.longitude, pos.altitude);
}

SatelliteDetails Satellite::getDetails(std::time_t startDate, double tSince)
{
    libsgp4::CoordGeodetic pos = getCurrentPosition(startDate, tSince);
    libsgp4::Vector vel = getCurrentVelocity(startDate, tSince);

    libsgp4::Tle tle = libsgp4::Tle(name, TleLineOne, TleLineTwo);
    SatelliteDetails details;

    details.name = name;
    details.colour = colour;

    details.lat = pos.latitude;
    details.lon = pos.longitude;
    details.alt = pos.altitude;

    details.velX = vel.x;
    details.velY = vel.y;
    details.velZ = vel.z;

    details.epoch = tle.Epoch().ToString();
    details.NORAD = tle.NoradNumber();
    details.designator = tle.IntDesignator();

    details.inclination = tle.Inclination(true);
    details.RAN = tle.RightAscendingNode(true);
    details.eccentricity = tle.Eccentricity();
    details.argumentPerigee = tle.ArgumentPerigee(true);
    details.meanAnomaly = tle.MeanAnomaly(true);

    details.meanMotion = tle.MeanMotion();
    details.meanMotionDT2 = tle.MeanMotionDt2();
    details.meanMotionDDT6 = tle.MeanMotionDdt6();
    details.bSTAR = tle.BStar();

    return details;
}
