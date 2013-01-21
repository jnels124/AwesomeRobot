#ifndef SETTINGS_INCLUDED
#define SETTINGS_INCLUDED

// BEGIN Port Setttings
#define ROBOT_SERIAL_PORT_SPEED 115200//9600
#define ROBOT_SERIAL_PORT_ADDRESS "/dev/ttyACM0"
#define ROBOT_SERIAL_PORT_HELLO_BYTE '+'
#define ROBOT_SERIAL_PORT_SESSION_TIMEOUT 30
#define ROBOT_MAX_MESSAGE_SIZE 200
#define ROBOT_MSG_TERMINATOR ';'
#define ROBOT_MSG_START ':'
// END Port Settings

// BEGIN Message Settings
#define ROBOT_SERIAL_MESSAGE_START ':'
#define ROBOT_SERIAL_MESSAGE_STOP ';'

// END Message Settings

// BEGIN Services
#define ROBOT_SERVICE_CAMERA 'C'
#define ROBOT_SERVICE_IMO 'I'
#define ROBOT_SERVICE_WHEEL_ANGLE 'A'
#define ROBOT_SERVICE_WHEEL_SPEED 'S'
#define ROBOT_SERVICE_WHEEL_ENCODER 'D'
#define ROBOT_SERVICE_IRSENSOR_SERVO 'I'
#define ROBOT_SERVICE_IRSENSOR_POLL 'J'
//#define ROBOT_SERVICE_ARM_SERVO 'G'
// END Services

// BEGIN Responses
#define ROBOT_RESPONSE_ERROR 'E'
#define ROBOT_RESPONSE_COMFIRM 'C'
// END Responses

// BEGIN Error
#define ROBOT_SERIAL_ERROR_BAD_MESSAGE 1
#define ROBOT_SERIAL_ERROR_NO_SERVICE 1
#define ROBOT_SERIAL_ERROR_WRONG_ARGUMENTS 1
// END Error

typedef int Number;

#endif // SETTINGS_INCLUDED

