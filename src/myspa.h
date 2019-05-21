#ifdef __cplusplus
extern "C" {
#endif 

#ifndef MYSPA_H
#define MYSPA_H


typedef struct
{
    //----------------------INPUT VALUES------------------------

    int year;            // 4-digit year,    valid range: -2000 to 6000, error code: 1
    int month;           // 2-digit month,         valid range: 1 to 12, error code: 2
    int day;             // 2-digit day,           valid range: 1 to 31, error code: 3
    int hour;            // Observer local hour,   valid range: 0 to 24, error code: 4
    int minute;          // Observer local minute, valid range: 0 to 59, error code: 5
    int second;          // Observer local second, valid range: 0 to 59, error code: 6

    double delta_t;      // Difference between earth rotation time and terrestrial time

                         // valid range: -8000 to 8000 seconds, error code: 7

    double timezone;     // Observer time zone (negative west of Greenwich)
                         // valid range: -12   to   12 hours,   error code: 8

    double longitude;    // Observer longitude (negative west of Greenwich)
                         // valid range: -180  to  180 degrees, error code: 9

    double latitude;     // Observer latitude (negative south of equator)
                         // valid range: -90   to   90 degrees, error code: 10

    double elevation;    // Observer elevation [meters]
                         // valid range: -6500000 or higher meters,    error code: 11

    

    double slope;        // Surface slope (measured from the horizontal plane)
                         // valid range: -360 to 360 degrees, error code: 14

    double azm_rotation; // Surface azimuth rotation (measured from south to projection of
                         //     surface normal on horizontal plane, negative west)
                         // valid range: -360 to 360 degrees, error code: 15
    double delta_prime;

     

     double ssha;
     double srha;



     

    //--------------------- OUTPUT VALUES------------------------

    double zenith;      //topocentric zenith angle [degrees]
    double azimuth180;  //topocentric azimuth angle (westward from south) [-180 to 180 degrees]
    double azimuth;     //topocentric azimuth angle (eastward from north) [   0 to 360 degrees]
    double incidence;   //surface incidence angle [degrees]

    double suntransit;  //local sun transit time (or solar noon) [fractional hour]
    double sunrise;     //local sunrise time (+/- 30 seconds) [fractional hour]
    double sunset;      //local sunset time (+/- 30 seconds) [fractional hour]

} spa_data;
int spa_calculate(spa_data *spa);
#endif
 #ifdef __cplusplus
 }
 #endif 
