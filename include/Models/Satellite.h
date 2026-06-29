#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>

struct Vector
{
    float x, y, z;
};

struct Orbit
{
    Vector position, velocity;
    float longitude, latitude, altitude;
};

struct Time
{
    int year, day, hour, minute, second;
};

struct MeanMotion
{
    double meanMotion, firstDerivMeanMotion, secondDerivMeanMotion;
};

class Satellite
{
private:
    std::string name, classification, launchDate, primaryPayload;
    int id, launchNum;
    double ephemerisType, inclination, RAAN, eccentricity, perigee, meanAnamoly, revolutionNum, BSTAR;
    MeanMotion meanMotion;
    Time epoch;
    Orbit orbitData;

public:
    Satellite();
    Satellite(std::string name, std::vector<std::string> TLE1, std::vector<std::string> TLE2);
};
