#include <Models/Satellite.h>

Satellite::Satellite()
{
}

Satellite::Satellite(std::string name, std::vector<std::string> TLE1, std::vector<std::string> TLE2)
{
    if (TLE1.size() != 9 || (TLE2.size() != 8 && TLE2.size() != 9))
    {
        std::cerr << "Error Initializing Satellite." << std::endl;
        return;
    }

    this->name = name;
    id = std::stoi(TLE1[1].substr(0, TLE1[1].size() - 1));
    classification = TLE1[1][TLE1[1].size() - 1];
    if (classification == "U")
        classification = "UNCLASSIFIED";

    launchDate = TLE1[2].substr(0, 2);
    launchDate = (std::stoi(launchDate) > 30) ? "19" + launchDate : "20" + launchDate;

    for (int i = TLE1[2].size() - 1; i >= 0; i--)
    {
        if (std::isalpha(TLE1[2][i]))
            primaryPayload.insert(0, 1, TLE1[2][i]);
    }
    launchNum = std::stoi(TLE1[2].substr(2, TLE1[2].size() - 2 - primaryPayload.size()));

    double x;
    epoch.year = std::stoi(TLE1[3].substr(0, 2));
    epoch.day = std::stoi(TLE1[3].substr(2, 3));
    double dayFraction = std::modf(std::stod(TLE1[3]), &x);
    epoch.hour = std::floor(dayFraction * 24);
    double hourFraction = std::modf(dayFraction * 24, &x);
    epoch.minute = std::floor(hourFraction * 60);
    double minuteFraction = std::modf(hourFraction * 60, &x);
    epoch.second = std::floor(minuteFraction * 60);

    meanMotion.meanMotion = std::stod(TLE2[6]);
    meanMotion.firstDerivMeanMotion = std::stod(TLE1[4]);
    meanMotion.secondDerivMeanMotion = std::stod(TLE1[5]);
    BSTAR = std::pow(std::stod("0." + TLE1[6].substr(0, TLE1[6].size() - 2)), (TLE1[6][TLE1[6].size() - 1]) - '0');
    ephemerisType = std::stod(TLE1[7]);

    inclination = std::stod(TLE2[2]);
    RAAN = std::stod(TLE2[3]);
    eccentricity = std::stod("0." + TLE2[4]);
    perigee = std::stod("0." + TLE2[4]);
    meanAnamoly = std::stod(TLE2[5]);
    revolutionNum = std::stod(TLE2[7]);

    std::cout << id << ", " << classification << ", " << launchDate << ", " << launchNum << ", " << primaryPayload << ", " << meanMotion.meanMotion << ", " << meanMotion.firstDerivMeanMotion << ", " << meanMotion.secondDerivMeanMotion << ", " << BSTAR << ", " << ephemerisType << inclination << ", " << RAAN << ", " << eccentricity << ", " << perigee << ", " << meanAnamoly << ", " << revolutionNum << std::endl;
    std::cout << epoch.year << ", " << epoch.day << ", " << epoch.hour << ", " << epoch.minute << ", " << epoch.second << std::endl;
}
