/*
  +-----------------------------------------------------------------------------------------------+
  | A simple Java programme for base64 encoding                                                   |
  +-----------------------------------------------------------------------------------------------+
  | Copyright ( c ) 2013 Anjan Borah < anjanborah@aol.com >                                       |
  +-----------------------------------------------------------------------------------------------+
  | Author - Anjan Borah                                                                          |
  +-----------------------------------------------------------------------------------------------+
  | GitHub - https://github.com/anjanborah/Base64_Encode                                          |
  +-----------------------------------------------------------------------------------------------+
*/

//----------[ Import Section ]---------------------------------------------------------------------

import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

//----------[ Class base64_encode ]----------------------------------------------------------------

public class base64_encode
{
  
  public static void main( String args[] )
  
  {
  
    try {
      
      Scanner _get = new Scanner( System.in );
      
      System.out.print( "                                #####  #       \n" );
      System.out.print( "#####     ##     ####   ###### #     # #    #  \n" );
      System.out.print( "#    #   #  #   #       #      #       #    #  \n" );
      System.out.print( "#####   #    #   ####   #####  ######  ####### \n" );
      System.out.print( "#    #  ######       #  #      #     #      #  \n" );
      System.out.print( "#    #  #    #  #    #  #      #     #      #  \n" );
      System.out.print( "#####   #    #   ####   ######  #####       #  \n\n" );
      System.out.print( "######  #    #   ####    ####   #####   ###### \n" );
      System.out.print( "#       ##   #  #    #  #    #  #    #  #      \n" );
      System.out.print( "#####   # #  #  #       #    #  #    #  #####  \n" );
      System.out.print( "#       #  # #  #       #    #  #    #  #      \n" );
      System.out.print( "#       #   ##  #    #  #    #  #    #  #      \n" );
      System.out.print( "######  #    #   ####    ####   #####   ###### \n\n" );
      
      System.out.print( "Enter the raw string--------------------------\n\n" );
      String _raw_string = _get.nextLine();
      Base64Encode _object = new Base64Encode( _raw_string );
      System.out.print( "\nEncoded String--------------------------------\n\n" + _object.get_encoded_string() + "\n" );
      
    } catch( Exception exception ) {
      System.out.println( "Exception - " + exception.toString() );
    }
  }
  
}

//----------[ Class Base64Encode ]-----------------------------------------------------------------

class Base64Encode
{

  public Base64Encode( String _raw_string )
  {
  
    try {
      this.start_engine( _raw_string );
    } catch( Exception exception ) {
      System.out.println( "Exception - " + exception.toString() );
    }
    
  }
  
  private void start_engine( String _raw_string ) throws Exception
  {
    
    this._raw_string = _raw_string;
    this._raw_string_length = this.get_string_length( this._raw_string );
    this._append_needed = this.is_append_needed( this._raw_string_length );
    this.populate_eight_bit_array();
    this.populate_six_bit_array();
    this.populate_base64_values();
    this.create_encoded_string();
    
  }
  
  private int get_string_length( String _string )
  {
    
    return _string.length();
    
  }
  
  private boolean is_append_needed( int _length )
  {
    
    boolean _append_needed;
    if( _length % 3 == 0 ) {
      _append_needed = false;
      this._append_count = 0;
    } else {
      _append_needed = true;
      this._append_count = 3 - ( _length % 3 );
    }
    
    return _append_needed;
    
  }
  
  private void populate_eight_bit_array()
  {
    
    for( int i=0; i<( this._raw_string_length + this._append_count ); i++ ) {
      
      if( i >= this._raw_string_length ) {
        this._eight_bit_array.add( "00000000" );
      } else {
        try {
          this._eight_bit_array.add( this.get_eight_bit_string( ( int )this._raw_string.charAt( i ) ) );
        } catch( Exception exception ) {
          System.out.println( "Exception - " + exception.toString() );
        }
      }
      
    }
    
  }
  
  private String get_eight_bit_string( int _ASCII ) throws Exception
  {
    
    String _eight_bit_string = "";
    int _zero_or_one;
    
    while( true ) {
      _zero_or_one = _ASCII % 2;
      if( _zero_or_one == 1 ) {
        _eight_bit_string = "1" + _eight_bit_string;
        _ASCII = _ASCII / 2;
        if( _ASCII == 0 ) {
          break;
        } else {
          continue;
        }
      } else {
        _eight_bit_string = "0" + _eight_bit_string;
        _ASCII = _ASCII / 2;
        if( _ASCII == 0 ) {
          break;
        } else {
          continue;
        }      
      }
    }
    
    int _eight_bit_string_length = _eight_bit_string.length();
    
    if( _eight_bit_string_length < 8 ) {
      for( int i=0; i<( 8 - _eight_bit_string_length ); i++ ) {
        _eight_bit_string = "0" + _eight_bit_string;
      }
    }
    
    return _eight_bit_string;
    
  }
  
  private void populate_six_bit_array() throws Exception
  {
    
    String _long_eight_bit_string = "";
    Iterator< String > _it = this._eight_bit_array.iterator();
    
    while( _it.hasNext() ) {
      _long_eight_bit_string = _long_eight_bit_string + _it.next();
    }
    
    for( int i=0; i<( _long_eight_bit_string.length() / 6 ); i++ ) {
      int m, n;
      m = ( 6 * i );
      n = m + 6;
      this._six_bit_array.add( _long_eight_bit_string.substring( m, n ) );
    }
    
  }
  
  private void populate_base64_values() throws Exception
  {
    
    for( String _six_bit_string : this._six_bit_array ) {
      this._base64_values.add( this.get_base64_index_value( _six_bit_string ) );
    }
    
  }
  
  private String get_base64_index_value( String _string )
  {
    
    int _base64_value = 0;
    
    for( int i=0; i<_string.length(); i++ ) {
      if( _string.charAt( i ) == '1' ) {
        _base64_value = _base64_value + this.my_pow( 2, ( 6 - ( i + 1 ) ) );
      }
    }
    
    return String.valueOf( _base64_value );
  
  }
  
  private int my_pow( int _base, int _power )
  {
    
    int _raise = 0;
    if( _power == 0 ) {
      _raise = 1;
    } else {
      int _temp = 1;
      for( int i=1; i<=_power; i++ ) {
        _temp = _temp * _base;
      }
      _raise = _temp;
    }
    
    return _raise;
    
  }
  
  private void create_encoded_string()
  {
    
    this._final_encoded_string = "";
    
    for( String _base64_value : this._base64_values ) {
      this._final_encoded_string = this._final_encoded_string + String.valueOf( this.base64_index_table[ Integer.parseInt( _base64_value ) ] );
    }
    
    if( this._append_needed ==  true ) {
      this._final_encoded_string = this._final_encoded_string.substring( 0, ( this._final_encoded_string.length() - this._append_count) );
      for( int i=1; i<=this._append_count; i++ ) {
        this._final_encoded_string = this._final_encoded_string + "=";
      }
    }
    
  }
  
  public String get_encoded_string()
  {
    
    return this._final_encoded_string;
  
  }
  
  private String _raw_string;
  private int _raw_string_length;
  private boolean _append_needed;
  private int _append_count;
  private List< String > _eight_bit_array = new ArrayList< String >();
  private List< String > _six_bit_array = new ArrayList< String >();
  private List< String > _base64_values = new ArrayList< String >();
  private String _final_encoded_string;
  private char base64_index_table[] = {
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

}

//-------------------------------------------------------------------------------------------------
