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


#ifndef __UTILITY_H__
#define __UTILITY_H__


#include <time.h>
#include <math.h>

#define INT64 52 - 4
#define INT32 23 - 4

int approxf(double actual, double expected, int bits) ;

double calculateAngularDistance( double a1, double d1, double a2, double d2 );

double hms2deg( double Hours, double Minutes, double Seconds ); 

double dms2deg(double Degrees, double Minutes, double Seconds );

void   deg2dms( double DecimalDegrees, int *Degrees, int *Minutes, int *Seconds );

double JulianDate( struct tm tm_val );

double J2000( double JD );

double getLocalSiderealTime( double lon, double J2000 );

double getHourAngle( double RightAscension, double LocalSideRealTime );

double getAltitude( double Latitude, double Declination, double HourAngle );

double getAzimuth( double Latitude, double Declination, double HourAngle );


#endif
