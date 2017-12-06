#ifndef SUNGEOM_H
#define SUNGEOM_H

#define PI 3.1415926
#define ZENITH -.83

float calculateSunrise(int year,int month,int day,float lat, float lng,int localOffset, int daylightSavings);

#endif 
