/* Copyright (C) 2017 Daniel Page <csdsp@bristol.ac.uk>
 *
 * Use of this source code is restricted per the CC BY-NC-ND license, a copy of
 * which can be found via http://creativecommons.org (and should be included as
 * LICENSE.txt within the associated archive or repository).
 */

#include "lab-2_q.h"

void rep( int8_t x ) {
  printf( "%4d_{(10)} = ", x );

  for( int i = ( BITSOF( x ) - 1 ); i >= 0; i-- ) {
    printf( "%d", ( x >> i ) & 1 );
  }

  printf( "_{(2)}\n" );
}

int main( int argc, char* argv[] ) {
  int8_t t;

  t =    0; rep( t );
  t =   +1; rep( t );
  t =   -1; rep( t );
  t = +127; rep( t );
  t = -128; rep( t );

  return 0;
}
