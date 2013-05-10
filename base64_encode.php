<?php

/*
  +-----------------------------------------------------------------------------------------------+
  | A simple php programme for base64 encoding                                                    |
  +-----------------------------------------------------------------------------------------------+
  | Copyright ( c ) 2013 Anjan Borah < anjanborah@aol.com >                                       |
  +-----------------------------------------------------------------------------------------------+
  | Author - Anjan Borah                                                                          |
  +-----------------------------------------------------------------------------------------------+
  | GitHub - https://github.com/anjanborah/Base64_Encode                                          |
  +-----------------------------------------------------------------------------------------------+
*/

//----------[ Error reporting ]---------------------------------------------------------------------

error_reporting( 0 );

//----------[ Class Base64Encode ]------------------------------------------------------------------

class Base64Encode
{

  public function __construct( $_raw_string )
  {
    
    try {
      $this->start_engine( $_raw_string );
    } catch( Exception $_excepton ) {
      print "Exception - " . $_exception->getMessage() . "\n";
    }
    
  }
  
  public function get_encoded_string()
  {
    
    if( $this->_RAW_STRING_DATA[ '_encode_success' ] == true ) {
      return $this->_RAW_STRING_DATA[ '_final_encoded_string' ];
    } else {
      return false;
    }
    
  }
  
  private function start_engine( $_raw_string )
  {
    
    $this->_RAW_STRING_DATA[ '_raw_string' ] = $_raw_string;
    $this->_RAW_STRING_DATA[ '_raw_string_length' ] = $this->get_string_length( $this->_RAW_STRING_DATA[ '_raw_string' ] );
    $this->_RAW_STRING_DATA[ '_append_needed' ] = $this->is_append_needed( $this->_RAW_STRING_DATA[ '_raw_string_length' ] );
    $this->populate_eight_bit_array();
    $this->populate_six_bit_array();
    $this->populate_base64_values();
    $this->create_encoded_string();
    $this->_RAW_STRING_DATA[ '_encoded_string_from_built_in_function' ] = base64_encode( $this->_RAW_STRING_DATA[ '_raw_string' ] );
    $this->set_encode_success();
    
  }
  
  private function set_encode_success()
  {
    
    if( $this->_RAW_STRING_DATA[ '_final_encoded_string' ]  == $this->_RAW_STRING_DATA[ '_encoded_string_from_built_in_function' ] ) {
      $this->_RAW_STRING_DATA[ '_encode_success' ] = true;
    } else {
      $this->_RAW_STRING_DATA[ '_encode_success' ] = false;
    }
    
  }
  
  private function create_encoded_string()
  {
    
    for( $i=0; $i<count( $this->_RAW_STRING_DATA[ '_base64_values' ] ); $i++ ) {
      $this->_RAW_STRING_DATA[ '_final_encoded_string' ] = $this->_RAW_STRING_DATA[ '_final_encoded_string' ] . $this->_BASE_INDEX_TABLE[ $this->_RAW_STRING_DATA[ '_base64_values' ][ $i ] ];
    }
    
    if( $this->_RAW_STRING_DATA[ '_append_needed' ] == 1 ) {
      for( $i=1; $i<=( $this->_RAW_STRING_DATA[ '_append_count' ] ); $i++ ) {
        $this->_RAW_STRING_DATA[ '_final_encoded_string' ][ ( $this->get_string_length( $this->_RAW_STRING_DATA[ '_final_encoded_string' ] ) ) - $i ] = "=";
      }
    }
    
  }
  
  private function my_pow( $_base, $_power )
  {
    
    $_raise = 0;
    if( $_power == 0 ) {
      $_raise = 1;
    } else {
      $_temp = 1;
      for( $i=1; $i<=$_power; $i++ ) {
        $_temp = $_temp * $_base;
      }
      $_raise = $_temp;
    }
    
    return $_raise;
  }
  
  private function get_base64_index_value( $_six_bit_string )
  {
    $_base_64_value = 0;
    
    for( $i=0; $i<$this->get_string_length( $_six_bit_string ); $i++ ) {
      if( $_six_bit_string[ $i ] == '1' ) {
        $_base_64_value = $_base_64_value + $this->my_pow( 2, ( 6 - (  $i + 1 ) ) );
      }
    }
    
    return $_base_64_value;
  
  }
  
  private function populate_base64_values()
  {
    
    for( $i=0; $i<count( $this->_RAW_STRING_DATA[ '_six_bit_array' ] ); $i++ ) {
      $this->_RAW_STRING_DATA[ '_base64_values' ][ $i ] = $this->get_base64_index_value( $this->_RAW_STRING_DATA[ '_six_bit_array' ][ $i ] ); 
    }
    
  }
  
  private function populate_six_bit_array()
  {
    
    $_long_eight_bit_string = "";
    
    for( $i=0; $i<count( $this->_RAW_STRING_DATA[ '_eight_bit_array' ] ); $i++ ) {
      for( $j=0; $j<8; $j++ ) {
        $_long_eight_bit_string = $_long_eight_bit_string . $this->_RAW_STRING_DATA[ '_eight_bit_array' ][ $i ][ $j ];
      }
    }
    
    for( $i=0; $i<( ( integer )$this->get_string_length( $_long_eight_bit_string ) / 6 ); $i++ ) {
      $j = 0;
      $k = ( 6 * $i );
      while( $j<6 ) {
        $this->_RAW_STRING_DATA[ '_six_bit_array' ][ $i ] = $this->_RAW_STRING_DATA[ '_six_bit_array' ][ $i ] . $this->_RAW_STRING_DATA[ '_six_bit_array' ][ $i ][ $j ] . $_long_eight_bit_string[ $k ];
        $k = $k + 1;
        $j = $j + 1;
      }
    }
    
  }
  
  private function populate_eight_bit_array()
  {
    
    for( $i=0; $i<( $this->_RAW_STRING_DATA[ '_raw_string_length' ] + $this->_RAW_STRING_DATA[ '_append_count' ] ); $i++ ) {
      
      if( $i >= $this->_RAW_STRING_DATA[ '_raw_string_length' ] ) {
        $this->_RAW_STRING_DATA[ '_eight_bit_array' ][ $i ] = "00000000";
      } else {
        $this->_RAW_STRING_DATA[ '_eight_bit_array' ][ $i ] = $this->get_eight_bit_string( ord( $this->_RAW_STRING_DATA[ '_raw_string' ][ $i ] ) );
      }
      
    }
    
  }
  
  private function get_eight_bit_string( $_ASCII )
  {
    $_eight_bit_string = "";
    
    while( true ) {
      
      $_zero_or_one = ( $_ASCII % 2 );
      
      if( $_zero_or_one == 1 ) {
        $_eight_bit_string = "1" . $_eight_bit_string;
        $_ASCII = ( integer )( $_ASCII / 2 );
        if( $_ASCII == 0 ) {
          break;
        } else {
          continue;
        }
      } else {
        $_eight_bit_string = "0" . $_eight_bit_string;
        $_ASCII = ( integer )( $_ASCII / 2 );
        if( $_ASCII == 0 ) {
          break;
        } else {
          continue;
        }
      }
      
    }
    
    $_eight_bit_string_length = $this->get_string_length( $_eight_bit_string );
    
    if( $this->get_string_length( $_eight_bit_string ) < 8 ) {
      
      for( $i=0; $i<( 8 - $_eight_bit_string_length ); $i++ ) {
        $_eight_bit_string = "0" . $_eight_bit_string;
      }
      
    }
    
    return $_eight_bit_string;
  }
  
  private function get_string_length( $_string )
  {
    
    $_length = 0;
    
    while( $_string[ $_length ] != null ) {
      $_length = $_length + 1;
    }
    
    return $_length;
  }
  
  private function is_append_needed( $_string_length )
  {
    
    $_append_needed = 0;
    
    if( $_string_length % 3 == 0 ) {
      $_append_needed = 0;
      $this->_RAW_STRING_DATA[ '_append_count' ] = 0;
    } else {
      $_append_needed = 1;
      $this->_RAW_STRING_DATA[ '_append_count' ] = 3 - ( $_string_length % 3 );
    }
    
    return $_append_needed;
  
  }
  
  public function __destruct()
  {
    /*
     * No code block
     */
  }
  
  private $_RAW_STRING_DATA = array(
    '_raw_string' => '',
    '_raw_string_length' => 0,
    '_append_needed' => 0,
    '_append_count' => 0,
    '_eight_bit_array' => array(),
    '_six_bit_array' => array(),
    '_base64_values' => array(),
    '_final_encoded_string' => '',
    '_encoded_string_from_built_in_function' => '',
    '_encode_success' => boolean
  );
  
  private $_BASE_INDEX_TABLE = array(
    0 => 'A',
    1 => 'B',
    2 => 'C',
    3 => 'D',
    4 => 'E',
    5 => 'F',
    6 => 'G',
    7 => 'H',
    8 => 'I',
    9 => 'J',
    10 => 'K',
    11 => 'L',
    12 => 'M',
    13 => 'N',
    14 => 'O',
    15 => 'P',
    16 => 'Q',
    17 => 'R',
    18 => 'S',
    19 => 'T',
    20 => 'U',
    21 => 'V',
    22 => 'W',
    23 => 'X',
    24 => 'Y',
    25 => 'Z',
    26 => 'a',
    27 => 'b',
    28 => 'c',
    29 => 'd',
    30 => 'e',
    31 => 'f',
    32 => 'g',
    33 => 'h',
    34 => 'i',
    35 => 'j',
    36 => 'k',
    37 => 'l',
    38 => 'm',
    39 => 'n',
    40 => 'o',
    41 => 'p',
    42 => 'q',
    43 => 'r',
    44 => 's',
    45 => 't',
    46 => 'u',
    47 => 'v',
    48 => 'w',
    49 => 'x',
    50 => 'y',
    51 => 'z',
    52 => '0',
    53 => '1',
    54 => '2',
    55 => '3',
    56 => '4',
    57 => '5',
    58 => '6',
    59 => '7',
    60 => '8',
    61 => '9',
    62 => '+',
    63 => '/'
  );
}

function clear_screen()
{
  
  $_os_information = php_uname();
  
  if( strtolower( substr( $_os_information, 0, 3 ) ) == "lin" ) {
    system( "clear" );
  } elseif( strtolower( substr( $_os_information, 0, 3 ) ) == "win" ) {
  system( "cls" );
  } else {
    /*
    * No code block
    */
  }
  
}

//----------[ Function - main() ]-------------------------------------------------------------------

function main( $argc, $argv )
{
  
  clear_screen();
  
  print "                                #####  #       \n";
  print "#####     ##     ####   ###### #     # #    #  \n";
  print "#    #   #  #   #       #      #       #    #  \n";
  print "#####   #    #   ####   #####  ######  ####### \n";
  print "#    #  ######       #  #      #     #      #  \n";
  print "#    #  #    #  #    #  #      #     #      #  \n";
  print "#####   #    #   ####   ######  #####       #  \n\n";
  
  print "######  #    #   ####    ####   #####   ###### \n";
  print "#       ##   #  #    #  #    #  #    #  #      \n";
  print "#####   # #  #  #       #    #  #    #  #####  \n";
  print "#       #  # #  #       #    #  #    #  #      \n";
  print "#       #   ##  #    #  #    #  #    #  #      \n";
  print "######  #    #   ####    ####   #####   ###### \n\n";


  print "Enter the raw string-------------------------\n\n";
  $_raw_string  = ( string )trim( fgets( STDIN ) );
  $_object = new Base64Encode( $_raw_string );
  print "\nEncoded string-------------------------------\n\n" . $_object->get_encoded_string() . "\n";
}

main( $argc, $argv );

?>
