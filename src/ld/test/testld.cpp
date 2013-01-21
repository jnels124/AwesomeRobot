// Enable testing
#define TESTING
// For print.
#include <stdio.h>
// Testing macros.
#include "tests.h"
// For strlen()
#include <string.h>


// BEGIN Mock Declarations
#include <malloc.h>
void delay( int ) {
}
class HardwareSerial {
  public:
    const char* buffer;
    int nextChar;
    char outBuffer[1000];
    int out_nextChar;
    HardwareSerial( )
            : nextChar( 0 ), out_nextChar( 0 ) {
        outBuffer[0] = '\0';
    }
    char read() {
        char ret = buffer[ nextChar ];
        if ( ret ) {
            ++nextChar;
        }
        return ret;
    }
    int available() {
        return strlen( buffer + nextChar );
    }
    void write( char out ) {
        outBuffer[ out_nextChar++ ] = out;
        outBuffer[ out_nextChar ] = '\0';
    }
    void write( const char* out ) {
        int len = strlen( out );
        strcpy( outBuffer + out_nextChar, out );
        out_nextChar += len;
    }
    void flush() {
    }
    void begin( int ) {
    }
    void print( int out ) {
        int len = sprintf( outBuffer + out_nextChar, "%d", out );
        out_nextChar += len;
    }
};
HardwareSerial Serial;
// END Mock Declarations

// Pull in test file.
#include "../ld.pde"



// Forward declaration.
int goodBehavior_TestSuite();

/**
 * Main calls test_suite() and returns results.
 *
 * @return the number of failures.
 */
int main() {
	int ret=goodBehavior_TestSuite();
	return ret;
}

// BEGIN Results
/// Holds the number of failed assertions.
int bad_asserts = 0;
/// Holds the number of total assertions.
int total_assertions = 0;
/// Holds the number of failed tests.
int bad_tests = 0;
/// Holds the number of total tests.
int total_tests = 0;
// END Results


/**
 * Proves decodeMessage will convert a string message into
 *  a decodedMessage in most cases.
 *
 * @return TRUE if the test succeeds.
 */
bool goodBehavior_loop() {
  bool status = true;
  ++total_tests;
  // Check an empty message.
  {
      Serial.buffer = ":J123;";
      Serial.nextChar = 0;
      const char* expected = ":C123;";
      loop();
      TEST_( strcmp( expected, Serial.outBuffer ) == 0,
            printf( "FAILURE BECAUSE: expected \"%s\" and actual was \"%s\".\n", expected, Serial.outBuffer ) );
  }

  if ( status )
    printf( "Test %s successful!\n", __FUNCTION__ );
  return status;
}

/**
 * Proves decodeMessage will convert a string message into
 *  a decodedMessage in most cases.
 *
 * @return TRUE if the test succeeds.
 */
bool goodBehavior_readMessage() {
  bool status = true;
  ++total_tests;
  // Check an empty message.
  {
      Serial.buffer = ":;";
      Serial.nextChar = 0;
      TEST_EQUAL( false, readMessage() );
  }

  if ( status )
    printf( "Test %s successful!\n", __FUNCTION__ );
  return status;
}

/**
 * Runs "good" behavor tests.
 *
 * @return the number of failures
 */
int goodBehavior_TestSuite(){
  bad_asserts = 0;
  total_assertions = 0;
  printf( "BEGIN Good Behavior Tests\n");

    // Run each test and count the successes.
  if ( !goodBehavior_readMessage() )
    ++bad_tests;

  if ( !goodBehavior_loop() )
    ++bad_tests;

  printf( "END Good Behavior Tests\n");

    // Prints results.
  printf( "%d of %d assertions successful!\n", (total_assertions - bad_asserts), total_assertions );
  printf( "%d of %d tests successful!\n", (total_tests - bad_tests), total_tests );

    // Print status.
  if( bad_tests == 0 )
    printf("Success!\n");
  else
    printf("Failure!\n");

  return bad_tests;
}

