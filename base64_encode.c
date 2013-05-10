/*
  +-----------------------------------------------------------------------------------------------+
  | A simple C programme for base64 encoding                                                      |
  +-----------------------------------------------------------------------------------------------+
  | Copyright ( c ) 2013 Anjan Borah < anjanborah@aol.com >                                       |
  +-----------------------------------------------------------------------------------------------+
  | Author - Anjan Borah                                                                          |
  +-----------------------------------------------------------------------------------------------+
  | GitHub - https://github.com/anjanborah/Base64_Encode                                          |
  +-----------------------------------------------------------------------------------------------+
*/
#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------------------------

#define FLUSH fflush( stdin );

//-------------------------------------------------------------------------------------------------

char base64_index_table[] = {
  'A', /* Index number - 0  */
  'B', /* Index number - 1  */
  'C', /* Index number - 2  */
  'D', /* Index number - 3  */
  'E', /* Index number - 4  */
  'F', /* Index number - 5  */
  'G', /* Index number - 6  */
  'H', /* Index number - 7  */
  'I', /* Index number - 8  */
  'J', /* Index number - 9  */
  'K', /* Index number - 10 */
  'L', /* Index number - 11 */
  'M', /* Index number - 12 */
  'N', /* Index number - 13 */
  'O', /* Index number - 14 */
  'P', /* Index number - 15 */
  'Q', /* Index number - 16 */
  'R', /* Index number - 17 */
  'S', /* Index number - 18 */
  'T', /* Index number - 19 */
  'U', /* Index number - 20 */
  'V', /* Index number - 21 */
  'W', /* Index number - 22 */
  'X', /* Index number - 23 */
  'Y', /* Index number - 24 */
  'Z', /* Index number - 25 */
  'a', /* Index number - 26 */
  'b', /* Index number - 27 */
  'c', /* Index number - 28 */
  'd', /* Index number - 29 */
  'e', /* Index number - 30 */
  'f', /* Index number - 31 */
  'g', /* Index number - 32 */
  'h', /* Index number - 33 */
  'i', /* Index number - 34 */
  'j', /* Index number - 35 */
  'k', /* Index number - 36 */
  'l', /* Index number - 37 */
  'm', /* Index number - 38 */
  'n', /* Index number - 39 */
  'o', /* Index number - 40 */
  'p', /* Index number - 41 */
  'q', /* Index number - 42 */
  'r', /* Index number - 43 */
  's', /* Index number - 44 */
  't', /* Index number - 45 */
  'u', /* Index number - 46 */
  'v', /* Index number - 47 */
  'w', /* Index number - 48 */
  'x', /* Index number - 49 */
  'y', /* Index number - 50 */
  'z', /* Index number - 51 */
  '0', /* Index number - 52 */
  '1', /* Index number - 53 */
  '2', /* Index number - 54 */
  '3', /* Index number - 55 */
  '4', /* Index number - 56 */
  '5', /* Index number - 57 */
  '6', /* Index number - 58 */
  '7', /* Index number - 59 */
  '8', /* Index number - 60 */
  '9', /* Index number - 61 */
  '+', /* Index number - 62 */
  '/'  /* Index number - 63 */
};

//-------------------------------------------------------------------------------------------------

struct RAW_STRING_DATA
{
  
  char *RAW_STRING;
  int RAW_STRING_LENGTH;
  int APPEND_NEEDED;
  int APPEND_COUNT;

};

//-------------------------------------------------------------------------------------------------

struct RAW_STRING_DATA RAW_DATA;

//----------[ Function  - my_pow() ]---------------------------------------------------------------

int my_pow( int _base, int _power )
{

  int _raise = 0, i;
  if( _power == 0 ) {
    _raise = 1;
  } else {
    int _temp = 1;
    for( i=1; i<=_power; i++ ) {
      _temp = _temp * _base;
    }
    _raise = _temp;
  }
  
  return _raise;

}

//----------[ Function - get_base64_index_value() ]------------------------------------------------

int get_base64_index_value( char *_string )
{

  int _base64_index = 0;
  int i = 0;
  
  while( *_string != '\0' ) {
    if( *_string == '1' ) {
      _base64_index = _base64_index + my_pow( 2, 6 - ( i + 1 ) );
    }
    _string++;
    i = i + 1;
  }
  
  return _base64_index;

}

//----------[ Function - segment_and_get_base64_index ]--------------------------------------------

void segment_and_get_base64_index( int _string_length, char _string[ _string_length ] )
{
  
  int i, j, k = 0;
  char _six_bit_array[ _string_length / 6 ][ 7 ];
  int _base64_index_numbers[ _string_length / 6 ];
  
  for( i=0; i<( _string_length / 6 ); i++ ) {
    j = 0;
    while( j<6 ) {
      _six_bit_array[ i ][ j ] = _string[ k ];
      j = j + 1;
      k = k + 1;
    }
    _six_bit_array[ i ][ j ] = '\0';
  }
  
  for( i=0; i<( _string_length / 6 ); i++ ) {
    _base64_index_numbers[ i ] = get_base64_index_value( _six_bit_array[ i ] );
  }
  
  char _final_encoded_string[ ( _string_length / 6 ) ];
  
  for( i=0; i<( _string_length / 6 ); i++ ) {
    _final_encoded_string[ i ] = base64_index_table[ _base64_index_numbers[ i ] ];
  }
  
  _final_encoded_string[ ( _string_length / 6 ) ] = '\0';
  
  if( RAW_DATA.APPEND_NEEDED == 1 ) {
    for( i=1; i<=RAW_DATA.APPEND_COUNT; i++ ) {
      _final_encoded_string[ get_string_length( _final_encoded_string ) - i ] = '=';
    }
  }
  
  fprintf( stdout, "\nEncoded string-------------------------------\n\n%s\n", _final_encoded_string );

}

//----------[ Function - get_eight_bit_string() ]--------------------------------------------------

char *get_eight_bit_string( int _ASCII )
{

  char *_return_char;
  char _binary_string[ 9 ];
  int _while_loop_count, _mod_value;
  int i = 0, j = 0, k = 0;
  
  while( 1 ) {
    _mod_value = _ASCII % 2;
    if( _mod_value == 0 ) {
      _binary_string[ i ] = '0';
      _ASCII = _ASCII / 2;
      if( _ASCII == 0 ) {
        break;
      } else {
        i = i + 1;
        continue;
      }
    } else {
      _binary_string[ i ] = '1';
      _ASCII = _ASCII / 2;
      if( _ASCII == 0 ) {
        break;
      } else {
        i = i + 1;
        continue;
      }    
    }
  }
  
  j = 8 - i;
  
  for( k=1; k<=j; k++ ) {
    i = i + 1;
    _binary_string[ i ] = '0';
  }
  
  _binary_string[ i ] = '\0';
  
  for( i=0; i<get_string_length( _binary_string ) / 2; i++ ) {
    char _temp_char;
    _temp_char = _binary_string[ i ];
    _binary_string[ i ] = _binary_string[ ( get_string_length( _binary_string ) - 1 ) - i ];
    _binary_string[ ( get_string_length( _binary_string ) - 1 ) - i ] = _temp_char;
  }
  
  _return_char = _binary_string;
  
  return _return_char;

}

//----------[ Function - get_string_length() ]-----------------------------------------------------

int get_string_length( char *_string )
{

  int string_length = 0;
  
  while( *_string != '\0' ) {
    string_length = string_length + 1;
    _string = _string + 1;
  }
  
  return string_length;

}

//----------[ Function - is_append_needed() ]------------------------------------------------------

int is_append_needed( int string_length )
{

  if( RAW_DATA.RAW_STRING_LENGTH % 3 == 0 ) {
    RAW_DATA.APPEND_COUNT = 0;
    return 0;
  } else {
    RAW_DATA.APPEND_COUNT = 3 - ( RAW_DATA.RAW_STRING_LENGTH % 3 ); 
    return 1;
  }

}

//----------[ Function - start_engine() ]----------------------------------------------------------

void start_engine( char *_string )
{
  
  int i, j, k;
  RAW_DATA.RAW_STRING = _string;
  RAW_DATA.RAW_STRING_LENGTH = get_string_length( RAW_DATA.RAW_STRING );
  RAW_DATA.APPEND_NEEDED = is_append_needed( RAW_DATA.RAW_STRING_LENGTH );
  char _eight_string_array[ ( RAW_DATA.RAW_STRING_LENGTH + RAW_DATA.APPEND_COUNT ) ][ 9 ];
  char _eight_bit_string[ ( ( RAW_DATA.RAW_STRING_LENGTH + RAW_DATA.APPEND_COUNT ) * 9 ) + 1 ];
  char *_char_temp;
  _char_temp = RAW_DATA.RAW_STRING;
  
  for( i=0; i<( RAW_DATA.RAW_STRING_LENGTH + RAW_DATA.APPEND_COUNT ); i++ ) {
    
    if( i >= RAW_DATA.RAW_STRING_LENGTH ) {
      
      for( j=0; j<9; j++  ) {
        if( j == 8 ) {
          _eight_string_array[ i ][ j ] = '\0';
        } else {
          _eight_string_array[ i ][ j ] = '0';
        }
      }
      
    } else {
      
      char *_char_temp_local;
      _char_temp_local = get_eight_bit_string( ( int )*_char_temp );
      j = 0;
      
      while( *_char_temp_local != '\0' ) {
        _eight_string_array[ i ][ j ] = *_char_temp_local;
        _char_temp_local++;
        j = j + 1;
      }
      
      _eight_string_array[ i ][ j ] = '\0';
      _char_temp++;
    }
    
  }
  
  i = 0;
  j = 0;
  k = 0;
  
  for( i=0; i<( RAW_DATA.RAW_STRING_LENGTH + RAW_DATA.APPEND_COUNT ); i++ ) {
    for( j=0; j<get_string_length( _eight_string_array[ i ] ); j++ ) {
      _eight_bit_string[ k ] = _eight_string_array[ i ][ j ];
      k++;
    }
  }
  
  _eight_bit_string[ k ] = '\0';
  segment_and_get_base64_index( get_string_length( _eight_bit_string ), _eight_bit_string );

}

//----------[ Function - main() ]------------------------------------------------------------------

int main( int argc, char *argv[] )
{
  
  system( "clear" );
  char _string[ 1024 ];
  // Read the raw string-----------------------------
  fprintf( stdout, "                                #####  #\n" );
  fprintf( stdout, "#####     ##     ####   ###### #     # #    #\n" );
  fprintf( stdout, "#    #   #  #   #       #      #       #    #\n" );
  fprintf( stdout, "#####   #    #   ####   #####  ######  #######\n" );
  fprintf( stdout, "#    #  ######       #  #      #     #      #\n" );
  fprintf( stdout, "#    #  #    #  #    #  #      #     #      #\n" );
  fprintf( stdout, "#####   #    #   ####   ######  #####       #\n\n" );
  
  fprintf( stdout, "######  #    #   ####    ####   #####   ###### \n" );
  fprintf( stdout, "#       ##   #  #    #  #    #  #    #  #      \n" );
  fprintf( stdout, "#####   # #  #  #       #    #  #    #  #####  \n" );
  fprintf( stdout, "#       #  # #  #       #    #  #    #  #      \n" );
  fprintf( stdout, "#       #   ##  #    #  #    #  #    #  #      \n" );
  fprintf( stdout, "######  #    #   ####    ####   #####   ###### \n\n" );
  
  fprintf( stdout, "Write the raw string-------------------------\n\n" );
  //-------------------------------------------------
  gets( _string );
  FLUSH;
  // Start the engine--------------------------------
  start_engine( _string );
  //-------------------------------------------------
  return 0;
  
}
