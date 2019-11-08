#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdio.h>

#ifndef OUTPUT_FILE
#define OUTPUT_FILE	"results.txt"
#endif

int	NowYear;		// 2019 - 2024
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;		// number of deer in the current population
int	NowNumHunter;		// number of hunters

const float GRAIN_GROWS_PER_MONTH =		8.0;
const float ONE_DEER_EATS_PER_MONTH =		0.5;
const float KILL_CHANCE_PER_HUNTER = 		0.2;

const float AVG_PRECIP_PER_MONTH =		6.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =			2.0;	// plus or minus noise

const float AVG_TEMP =				50.0;	// average
const float AMP_TEMP =				20.0;	// plus or minus
const float RANDOM_TEMP =			10.0;	// plus or minus noise

const float MIDTEMP =				40.0;
const float MIDPRECIP =				10.0;

// helper functions
float
Ranf( unsigned int *seedp,  float low, float high )
{
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX

        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}


int
Ranf( unsigned int *seedp, int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;

        return (int)(  Ranf(seedp, low,high) );
}

float
SQR( float x )
{
        return x*x;
}

unsigned int
TimeOfDaySeed( )
{
	struct tm y2k = { 0 };
	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time_t  timer;
	time( &timer );
	double seconds = difftime( timer, mktime(&y2k) );
	unsigned int seed = (unsigned int)( 1000.*seconds );    // milliseconds
	return seed;
}

void Watcher() {
	unsigned int seed = TimeOfDaySeed( ); 
	while( NowYear < 2025 ) {
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:

		// DoneComputing barrier:
		#pragma omp barrier

		// DoneAssigning barrier:
		#pragma omp barrier

		int currentMonth = ((NowYear - 2019) * 12) + NowMonth;

		float celTemp = (5./9.) * (NowTemp - 32.);	
		printf("%d\t%f\t%f\t%f\t%d\t%d\n", currentMonth, NowPrecip, celTemp, NowHeight, NowNumDeer, NowNumHunter);

		if (NowMonth == 11) {
			NowYear++;
			NowMonth = 0;	
		} else {
			NowMonth++;
		}

		float ang = ( 30.*(float)NowMonth + 15. ) * ( M_PI / 180. );

		float temp = AVG_TEMP - AMP_TEMP * cos( ang );
		NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

		float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
		NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
		if( NowPrecip < 0. )
			NowPrecip = 0.;		
	
		// DonePrinting barrier:
		#pragma omp barrier
	}
}

void Grain() {
	while( NowYear < 2025 ) {
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		
		float tempFactor = exp( -SQR( ( NowTemp - MIDTEMP ) / 10. ) );

		float precipFactor = exp( -SQR( ( NowPrecip - MIDPRECIP ) / 10. ) );
	
		float nextHeight = NowHeight;
		nextHeight += (tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH);
		nextHeight -= ((float)NowNumDeer * ONE_DEER_EATS_PER_MONTH);		
		
		if (nextHeight < 0) {
			nextHeight = 0;
		}		

		// DoneComputing barrier:
		#pragma omp barrier
		
		NowHeight = nextHeight;

		// DoneAssigning barrier:
		#pragma omp barrier
	
		// DonePrinting barrier:
		#pragma omp barrier
	}
}

void GrainDeer() {	
	unsigned int seed = TimeOfDaySeed( );
	while( NowYear < 2025 ) {
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:

		int nextDeer = NowNumDeer;

		// compute a chance to kill a deer every month depending
		// on the amount of hunters
		float chance = 0.;

		for (int i = 0; i < NowNumHunter; i++) {	
			chance = Ranf(&seed, 0, NowNumHunter) / (float)NowNumHunter;
			if(chance > (1 - KILL_CHANCE_PER_HUNTER)) {
				nextDeer--;
			}
		}

		if (NowNumDeer > NowHeight) {
			nextDeer--;
		} else if (NowNumDeer < NowHeight) {
			nextDeer++;
		}

		if (nextDeer < 0) {
			nextDeer = 0;
		}
	
		// DoneComputing barrier:
		#pragma omp barrier

		NowNumDeer = nextDeer;

		// DoneAssigning barrier:
		#pragma omp barrier

		// DonePrinting barrier:
		#pragma omp barrier
	}
}

void DeerHunter() {	
	while( NowYear < 2025 ) {
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:

		int nextHunter = NowNumHunter;

		if (nextHunter > NowNumDeer) {
			nextHunter--;
		} else if (nextHunter < NowNumDeer) {
			nextHunter++;
		}

		// DoneComputing barrier:
		#pragma omp barrier

		NowNumHunter = nextHunter;

		// DoneAssigning barrier:
		#pragma omp barrier
	
		// DonePrinting barrier:
		#pragma omp barrier
	}
}

int main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
	fprintf( stderr, "No OpenMP support!\n" );
	return 1;
#endif

	omp_set_num_threads( 4 );	// set the number of threads to use for the sections:`
	
	// starting date and time:
	NowMonth =    0;
	NowYear  = 2019;

	// starting state (feel free to change this if you want):
	NowTemp = 40.;
	NowPrecip = 5.;
	NowNumHunter = 0.;
	NowNumDeer = 1;
	NowHeight = 1.;
		
	printf("Month\tPrecip(in)\tTemp(C)\tHeight(in)\tNumDeer\tNumHunters\n");

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			GrainDeer( );
		}

		#pragma omp section
		{
			Grain( );
		}

		#pragma omp section
		{
			Watcher( );
		}

		#pragma omp section
		{
			DeerHunter( );	// has a chance to kill a deer every month depending on num hunters
		}
	}       // implied barrier -- all functions must return in order
		// to allow any of them to get past here
}
