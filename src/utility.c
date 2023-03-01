// MIT License
// 
// Copyright (c) 2020 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define _USE_MATH_DEFINES 

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

// approxf - Licensed under MIT License
// Copyright (c) 2017 Elliot Chance, Izyumov Konstantin and Christophe Kamphaus.
// https://github.com/elliotchance/c2go

int approxf(double actual, double expected, int bits) 
{
    // We do not handle infinities or NaN.
    if (isinf(actual) || isinf(expected) || isnan(actual) || isnan(expected)) {
        return 0;
    }
    // If we expect zero (a common case) we have a fixed epsilon from actual. If
    // allowed to continue the epsilon calculated would be zero and we would be
    // doing an exact match which is what we want to avoid.
    if (expected == 0.0) {
        return fabs(actual) < (1 / pow(2, bits));
    }
    // The epsilon is calculated based on significant bits of the actual value.
    // The amount of bits used depends on the original size of the float (in
    // terms of bits) subtracting a few to allow for very slight rounding
    // errors.
    double epsilon = fabs(expected / pow(2, bits));
    // The numbers are considered equal if the absolute difference between them
    // is less than the relative epsilon.
    return fabs(actual - expected) <= epsilon;
}

//
// alpha - Right Ascension
// delta - Declination
//
// returns angular distance in degrees
//
double calculateAngularDistance( double a1, double d1, double a2, double d2 )
{
  double CosOfAngularDistance = DBL_MAX;

  CosOfAngularDistance = sin( degToRad( d1 ) ) * sin( degToRad( d2 ) ) + 
                         cos( degToRad( d1 ) ) * cos( degToRad( d2 ) ) * 
                         cos( degToRad( a1 ) - degToRad( a2 ) ); 

  return radToDeg( acos(  CosOfAngularDistance ) );
}

double hms2deg( double Hours, double Minutes, double Seconds ) 
{
    double Harc = 360.0/24.0;
    double Marc = Harc/60.0;
    double Sarc = Marc/60.0;
    return (Harc * Hours + Marc * Minutes + Sarc * Seconds );
}

double dms2deg(double Degrees, double Minutes, double Seconds ) 
{
    double Marc = 1/60.0;
    double Sarc = 1/3600.0;
    return Degrees + Marc * Minutes + Sarc * Seconds;
}

void deg2dms( double DecimalDegrees, int *Degrees, int *Minutes, int *Seconds )
{
    *Degrees = DecimalDegrees;
    *Minutes = round( ( DecimalDegrees - *Degrees ) * 60.0 );
    *Seconds = round( ( ( DecimalDegrees - (double)*Degrees ) * 60.0  - (double)*Minutes ) * 60.0 );
}


double JulianDate( struct tm tm_val ) 
{
    int Y          = tm_val.tm_year + 1900; 
    int M          = tm_val.tm_mon;

    // If the month is January or February, subtract 1 from the year to get a new Y, and add 12 
    // to the month to get a new M. (Thus, we are thinking of January and February as being the 
    // 13th and 14th month of the previous year). This is how leap days are handled as well
    // since February is at the end the extra dat is not shifting the days of March - December
    if( M < 2 )
    {
      Y = Y - 1;
      M = M + 12;
    }

    double Sec = ( double )( tm_val.tm_sec ) / 60;
    double Min = ( double )( ( tm_val.tm_min + Sec ) / 60.0 );
    double Hou = ( double )( ( tm_val.tm_hour + Min ) / 24.0 );

    double D = ( double )( tm_val.tm_yday ) + Hou;

    int A = Y / 100;
    int B = A / 4;
    int C = 2 - A + B;
    int E = ( int )( 365.25  * ( double )( Y + 4716 ) );
    int F = ( int )( 30.6001 * ( double )( M ) );
    double JD = ( double )( C + E + F ) - 1524.5 + D;

    return JD;
}

double J2000( double JD ) 
{
    return JD - 2451545.0;
}

double getLocalSiderealTime( double lon, double J2000 ) 
{
    time_t rawtime;
    struct tm * timeinfo;

    setenv("TZ", "GMT", 1);
    time (&rawtime);
    timeinfo = localtime (&rawtime);

    double Sec = ( double )( timeinfo->tm_sec ) / 60.0;
    double Min = ( double )( timeinfo->tm_min + Sec ) / 60.0;
    double UT  = ( double )( timeinfo->tm_hour + Min);

    return ( 100.46 + 0.985647 * J2000 + lon + 15 * UT ) / 360.0;
}


double getHourAngle( double RightAscension, double LocalSideRealTime )
{
  return ( LocalSideRealTime - RightAscension );
}

double getAltitude( double Latitude, double Declination, double HourAngle )
{
   return asin( sin ( Declination * M_PI / 180.0 ) * 
          sin( Latitude * M_PI / 180 ) + 
          cos( Declination * M_PI / 180 ) * 
          cos( Latitude * M_PI / 180 ) *
          cos( HourAngle * M_PI / 180 ) );
}

double getAzimuth( double Latitude, double Declination, double HourAngle )
{
  double Altitude = getAltitude( Latitude, Declination, HourAngle );

  double A = asin( sin( Declination * M_PI / 180 ) * sin( Latitude * M_PI / 180 ) +
             cos( Declination * M_PI / 180 ) * cos( Latitude * M_PI / 180 ) * 
             cos( HourAngle * M_PI / 180 ) );

  double Azimuth = 0.0;
  if( sin( HourAngle * M_PI ) < 0 )
  {
    Azimuth = A;
  }
  else
  {
    Azimuth = M_PI - A;
  }

  return( Azimuth * 180.0 / M_PI );

}


