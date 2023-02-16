#ifndef __LOCATIONS_HH__
#define __LOCATIONS_HH__

#include <string>

class Locations
{
    public:
        Locations(std::string _location,double _latitude,double _longitude,double _traffic)
        {
            location=_location;
            latitude=_latitude;
            longitude=_longitude;
            traffic=_traffic;
        }
        std::string location_name(){return location;} 
        double latitude_getter(){return latitude;}
        double longitude_getter(){return longitude;}
        double traffic_getter(){return traffic;}

    private:
        std::string location;
        double latitude;
        double longitude;
        double traffic;

};

#endif