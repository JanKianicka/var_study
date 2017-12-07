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
#include <pthread.h>
#include <time.h>


typedef struct {
    /* For running computation in multithreading mode we need 
     * IN:
     *   start_lon_idx - start longitude index
     *   end_lon_idx   - end longitude index
     *   longitude_array
     *   latitude_array
     *   year, month, day
     * OUT:
     *   sunrise_out_array 
     */
    int start_lon_idx;
    int end_lon_idx;
    int lon_size;
    int lat_size;
    int year;
    int month;
    int day;
    void *Longitudes;
    void *Latitudes;
    void *Sun_rise_hours;

} CONTEXT;

typedef struct {
    int year;
    int month;
    int day;
} date_julian;

inline double to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

inline double to_radians(double degrees){
    return (degrees * M_PI)/180.0;
}

CONTEXT *initiate_worker(int year, int month, int day, int start_lon_idx, int end_lon_idx, int lon_size, int lat_size, void *Longitudes, void *Latitudes, void *Sun_rise_hours){
    CONTEXT *context = malloc(sizeof(CONTEXT));
    
    context->year  = year;
    context->month = month;
    context->day   = day;
    context->start_lon_idx = start_lon_idx;
    context->end_lon_idx   = end_lon_idx;
    context->lon_size      = lon_size;
    context->lat_size      = lat_size;
    context->Longitudes    = Longitudes;
    context->Latitudes     = Latitudes;
    context->Sun_rise_hours = Sun_rise_hours;
    return context;
}

void *sunrise_worker(void *context){
    int i,j;
    double sunrise_new;
    CONTEXT *context_loc = (CONTEXT *) context;
    int start_lon_idx = context_loc->start_lon_idx;
    int end_lon_idx   = context_loc->end_lon_idx;
    int lon_size      = context_loc->lon_size;
    int lat_size      = context_loc->lat_size;
    double (*Latitudes)[(long unsigned int)(lon_size)];
    double (*Longitudes)[(long unsigned int)(lon_size)];
    double (*Sun_rise_hours)[(long unsigned int)(lon_size)];
    Longitudes = context_loc->Longitudes;
    Latitudes  = context_loc->Latitudes;
    Sun_rise_hours = context_loc->Sun_rise_hours;

    printf("st, en: %i, %i\n",start_lon_idx, end_lon_idx);
    printf("%.2f\n",Latitudes[0][start_lon_idx+2]);
    printf("%.2f\n",Longitudes[0][start_lon_idx+2]);

    for(i=0;i<lat_size;i++){
	for(j=start_lon_idx; j<end_lon_idx;j++){
	    
	    sunrise_new = calculateSunrise(context_loc->year, context_loc->month, context_loc->day, Latitudes[i][j], Longitudes[i][j], 0, 0);
/*	    if(Longitudes[i][j] == 1){
		printf("Lat: %.2f\n",Latitudes[i][j]);
		printf("sunrise_new: %.3f\n",sunrise_new);
		}*/
	    /* Storing into the output memory */
	    Sun_rise_hours[i][j] = sunrise_new;
	}
    }
    return NULL;
}


int main(int argv, char *argc[])
{
    int n,m,i,j;
    double i_d, j_d;
    n = 180;
    m = 360;
    double res = 0.05; /* 0.05; */
    int nThreads = 3;
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
    date_julian *date_julian_par = malloc(sizeof(date_julian)*1);
    date_julian_par->year = year;
    date_julian_par->month = month;
    date_julian_par->day = day;
    double sunrise_new;

    /* time measures */
    clock_t start, end;
    clock_t start_s, end_s;
    double cpu_time_used_sing, cpu_time_used_multi ;
    
    printf("lat_size: %i\n",lat_size);
    printf("lon_size: %i\n",lon_size);
  
    for(i=0;i<lat_size;i++){
	i_d = (double)i;
	loc_latitude = i_d*res - 90.0;
	for(j=0;j<lon_size;j++){
	    j_d = (double)j;
	    loc_longitude = j*res-180.0;
	    Longitudes[i][j] = loc_longitude;
	    Latitudes[i][j] = loc_latitude;
	    /* Actually only here the heap memory was allocated for this array */
	    Sun_rise_hours[i][j] = 0.0;
	}
    }

    /* Calculation of sunrise itself*/
    /* lat_size - runs in latitudes, lon_size - runs in longitudes */
    start = clock();
    for(i=0;i<lat_size;i++){
	for(j=0;j<lon_size;j++){
//	    sunrise_new = calculateSunrise(year, month, day, Latitudes[i][j], Longitudes[i][j], 0, 0);
	    /* lets try to use heap instead of stack which looks to be consumed here */
	    sunrise_new = calculateSunrise(date_julian_par->year, date_julian_par->month, date_julian_par->day, Latitudes[i][j], Longitudes[i][j], 0, 0);

/*	    if(Longitudes[i][j] == 0){
		printf("Lat: %.2f\n",Latitudes[i][j]);
		printf("sunrise_new: %.3f\n",sunrise_new);
		}*/
	    /* Storing into the output memory */
	    Sun_rise_hours[i][j] = sunrise_new;
	}
    }
    end = clock();
    cpu_time_used_sing = ((double) (end - start))/ CLOCKS_PER_SEC;
    
/*
  Some links collected during this excercise:
  https://stackoverflow.com/questions/7064531/sunrise-sunset-times-in-c
  https://github.com/maoserr/redshiftgui/blob/master/src/solar.c
 */


    /* Using multithreading */
    /* Initialize context */
    CONTEXT **context_arr = malloc(sizeof(CONTEXT)*nThreads);
    int increment = lon_size/nThreads;
    printf("increment:%i\n",increment);
    int start_lon_idx = 0;
    int end_lon_idx   = 0;
    pthread_t *pthreads = malloc(sizeof(pthread_t)*nThreads);
    printf("Lat test: %.2f\n",Latitudes[10][10]);

    /* Start of processing */
    start_s = clock();
    start_s = time(NULL);
    for(i=0; i<nThreads;i++){
	end_lon_idx = start_lon_idx + increment;
	if(end_lon_idx>lon_size)
	    end_lon_idx = lon_size;
	printf("end_lon_idx: %i, %i \n",start_lon_idx,end_lon_idx);
	context_arr[i] = initiate_worker(year, month, day, start_lon_idx, end_lon_idx, lon_size, lat_size, Longitudes, Latitudes, Sun_rise_hours);
	pthread_create(&pthreads[i], NULL, sunrise_worker, (void *) context_arr[i]);
	start_lon_idx = end_lon_idx + 1;
    }

    for(i=0; i<nThreads;i++){
	pthread_join(pthreads[i], NULL);
    }
    /* End of processing */
    end_s = clock(); /* clock() is measuring processor time, not the execution time */
    end_s = time(NULL);
    cpu_time_used_multi = ((double) (end_s - start_s)) / CLOCKS_PER_SEC;
    cpu_time_used_multi = ((double) (end_s - start_s));

    /* Time measures */
    printf("Single threaded processing took: %.4f sec \n",cpu_time_used_sing);
    printf("Multithread threaded processing took: %.4f sec \n",cpu_time_used_multi);

    for(i=0; i<nThreads;i++){
	free(context_arr[i]);
    }
    
    free(context_arr);
    free(pthreads);
    
    /* check printout */
    for(i=0;i<lat_size;i++){
	for(j=0;j<lon_size;j++){
	    if(Longitudes[i][j] == 0){
		printf("Lat: %.2f\n",Latitudes[i][j]);
		printf("Sunrise_hour: %.3f\n",Sun_rise_hours[i][j]);
		}
	}
    }


    free(Longitudes);
    free(Latitudes);
    free(Sun_rise_hours);

    return 0;
}
