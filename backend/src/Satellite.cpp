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

libsgp4::CoordGeodetic Satellite::getCurrentPosition()
{
    std::time_t now = std::time(nullptr);
    std::tm *local_time = std::localtime(&now);

    libsgp4::DateTime currentTime = libsgp4::DateTime(local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    return propogator->FindPosition(currentTime).ToGeodetic();
}

libsgp4::Vector Satellite::getCurrentVelocity()
{
    std::time_t now = std::time(nullptr);
    std::tm *local_time = std::localtime(&now);

    libsgp4::DateTime currentTime = libsgp4::DateTime(local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    return propogator->FindPosition(currentTime).Velocity();
}

std::string Satellite::getSatelliteTypeStr()
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

SatelliteDTO Satellite::getDTO()
{
    libsgp4::CoordGeodetic pos = getCurrentPosition();
    return SatelliteDTO(name, colour, pos.latitude, pos.longitude, pos.altitude);
}
