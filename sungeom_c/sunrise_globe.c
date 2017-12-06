/* 

  In multidimensional array this test file shall compute
  exact time of sun-rise for whole globe.
  We try to study multithreading and perhaps cluster computing
  in near future.

*/

#include "stdlib.h"
#include "stdio.h"
#include <math.h>
#include "sungeom.h"

inline double to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

inline double to_radians(double degrees){
    return (degrees * M_PI)/180.0;
}


int main(int argv, char *argc[])
{
    int n,m,i,j;
    double i_d, j_d;
    int jdn;
    n = 180;
    m = 360;
    double res = 0.05;
    int lat_size, lon_size;
    lat_size = n/res;
    lon_size = m/res;
    i = 0;
    j = 0;
    double loc_longitude = 0.0;
    double loc_latitude = 0.0;

    double (*Longitudes)[lon_size] = malloc(sizeof(double[lat_size][lon_size]));
    double (*Latitudes)[lon_size]  = malloc(sizeof(double[lat_size][lon_size]));
    double (*Sun_rise_hours)[lon_size]  = malloc(sizeof(double[lat_size][lon_size]));

    /* given day */
    int year = 2017;
    int month = 12;
    int day = 5;
    double num_of_days;
/*    double mean_solar_time;
    double solar_mean_anomaly;
    double equation_of_center;
    double ecplitic_longitude;
    double solar_transit;
    double declination_of_sun;
    double hour_angle;
    double jd_rise;
    double jd_set; */
    double sunrise_new;
    
    printf("lat_size: %i\n",lat_size);
    printf("lon_size: %i\n",lon_size);
    
    /* Calculation of Julian day for the given date */
    /* Incorect formula from wikipage, could be that also sunrise equiations are wrong
       jdn = 367*year - (7*(year+5001 + (month - 9)/7))/4 + (275*month)/9 + day + 1729777; */
    /* Correct formula from http://aa.usno.navy.mil/faq/docs/JD_Formula.php */
    jdn= day-32075+1461*(year+4800+(month-14)/12)/4+367*(month-2-(month-14)/12*12)/12-3*((year+4900+(month-14)/12)/100)/4;
    printf("jdn: %i\n",jdn);
    num_of_days = (double)jdn - 2451545.0 + 0.0008;
    printf("num_of_days: %.2f\n",num_of_days);
    
    for(i=0;i<lat_size;i++){
	i_d = (double)i;
	loc_latitude = i_d*res - 90.0;
	for(j=0;j<lon_size;j++){
	    j_d = (double)j;
	    loc_longitude = j*res-180.0;
	    Longitudes[i][j] = loc_longitude;
	    Latitudes[i][j] = loc_latitude;
	}
//	printf("%.2f\n",Longitudes[i][190]);
	printf("%.2f\n",Latitudes[i][0]);
    }

    /* Calculation of sunrise itself*/
    /* lat_size - runs in latitudes, lon_size - runs in longitudes */
    for(i=0;i<lat_size;i++){
	for(j=0;j<lon_size;j++){
	    /* all of these equations are from wiki page which seems to be crappy 
	       unfortunatelly. Now we can see how tricky is to rely on internet resources. */
            /*   
	    mean_solar_time = num_of_days - (Longitudes[i][j]/360.0);

	    solar_mean_anomaly = fmod((357.5291 + 0.98560028*mean_solar_time), 360.0);
	    // equation from https://github.com/maoserr/redshiftgui/blob/master/src/solar.c
	    // solar_mean_anomaly = (357.5291 + mean_solar_time*(35999.05029 - mean_solar_time*0.0001537));
	    equation_of_center = 1.9148*sin(solar_mean_anomaly) + 0.0200*sin(2*solar_mean_anomaly) + 0.0003*sin(3*solar_mean_anomaly);
	    ecplitic_longitude = fmod((solar_mean_anomaly + equation_of_center + 180.0 + 102.9372),360.0);
	    solar_transit = 2451545.5 + mean_solar_time + 0.0053*sin(solar_mean_anomaly) - 0.0069*sin(2*ecplitic_longitude);
	    declination_of_sun = asin(sin(ecplitic_longitude)*(sin(to_radians(23.44))) );
	    hour_angle = acos((sin(to_radians(-0.83)) - (sin(to_radians(Latitudes[i][j])) * sin(declination_of_sun))) / (cos(to_radians(Latitudes[i][j])) * cos(declination_of_sun)));
	    jd_rise = solar_transit - (hour_angle/to_radians(360.0));
	    jd_set  = solar_transit + (hour_angle/to_radians(360.0)); */

#if DEBUG	    
	    printf("%.2f\n",mean_solar_time);
	    printf("%.2f\n",solar_mean_anomaly);
	    printf("%.2f\n",equation_of_center);
	    printf("%.2f\n",ecplitic_longitude);
	    printf("%.2f\n",solar_transit);
	    printf("%.2f\n",declination_of_sun);
	    printf("ha: %.2f\n",hour_angle);
	    printf("Lat: %.2f\n",Latitudes[i][j]);
	    printf("jd_rise: %.2f\n",jd_rise);
	    printf("jd_set:%.2f\n",jd_set); */
	    if(Longitudes[i][j] == 17){
		printf("Lat: %.2f\n",Latitudes[i][j]);
		printf("jd_rise: %.2f\n",jd_rise);
		printf("jd_set:%.2f\n",jd_set);
		}

	    hour_angle = solar_hour_angle_from_time(solar_transit, Latitudes[i][j], Longitudes[i][j]);
	    printf("ha new: %.2f\n",hour_angle);
#endif
	    sunrise_new = calculateSunrise(year, month, day, Latitudes[i][j], Longitudes[i][j], 0, 0);
	    if(Longitudes[i][j] == 0){
		printf("Lat: %.2f\n",Latitudes[i][j]);
		printf("sunrise_new: %.3f\n",sunrise_new);
	    }
	    /* Storing into the output memory */
	    Sun_rise_hours[i][j] = sunrise_new;
/*
  Some links collected during this excercise:
  https://stackoverflow.com/questions/7064531/sunrise-sunset-times-in-c
  https://github.com/maoserr/redshiftgui/blob/master/src/solar.c
 */
	}
    }
	
    free(Longitudes);
    free(Latitudes);
    free(Sun_rise_hours);

    return 0;
}
