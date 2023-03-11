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

#include <time.h>
#include <math.h>
#include "../src/utility.h"
#include "../src/star.h"
#include "utest.h"

UTEST( UtilityTests, deg2dms )
{
  int deg = 0;
  int min = 0;
  int sec = 0;

  deg2dms( 180.166944, &deg, &min, &sec );
  ASSERT_TRUE( deg == 180 );
  ASSERT_TRUE( min == 10 );
  ASSERT_TRUE( sec == 1 );
};

UTEST( UtilityTests, dms2deg )
{
  float result = dms2deg( 180, 10, 1 );

  ASSERT_TRUE( approxf( 180.166944, result, INT32 ) );
}

UTEST( UtilityTests, angularDistance )
{
  double result = calculateAngularDistance( 8.70733, 1.484090, 9.94798, 2.447672 );
  ASSERT_TRUE( approxf( result, 1.570304, INT32 ) );
}

UTEST_MAIN();
