#include <math.h>

#include "Robot.hpp"
#define ROBOT_MAP_WIDTH 30
#define ROBOT_MAP_HEIGHT 60

#define MOVE_RATE 0.5
#define SIGN( X ) ((X < 0) ? -1 : 1)
#define MIN( A, B ) ( A < B ? A : B )
#define THETA_TOLORANCE 1
#define ABS( X ) ( X < 0 ? -X : X )

Robot::Robot( State* state, int x, int y ):
    state( state ), x( x ), y( y ), mapTheta( 0 ),
    counter( 0 ), deltaX( 0 ), deltaY( 0 ), endCounter( -1 ) {
  state->onBegin( this );
}

void Robot::draw( MapDrawer* mapDrawer ) {

  double hWidth = ROBOT_MAP_WIDTH / 2;
  double hHeight = ROBOT_MAP_HEIGHT / 2;

  double frontLegth = hHeight * 1.5;
  double frontX = frontLegth * sin( -this->mapTheta );
  double frontY = frontLegth * -cos( -this->mapTheta );


  double radius = sqrt( hWidth * hWidth + hHeight * hHeight );

  double cornerTL_theta = atan( -hHeight / -hWidth );
  double cornerTL_x = radius * -cos( -cornerTL_theta - this->mapTheta );
  double cornerTL_y = radius * -sin( -cornerTL_theta - this->mapTheta );

  double cornerTR_theta = atan( -hHeight / hWidth );
  double cornerTR_x = radius * -cos( -cornerTR_theta - this->mapTheta );
  double cornerTR_y = radius * -sin( -cornerTR_theta - this->mapTheta );

  double cornerBL_theta = atan( hHeight / -hWidth );
  double cornerBL_x = radius * cos( -cornerBL_theta - this->mapTheta );
  double cornerBL_y = radius * sin( -cornerBL_theta - this->mapTheta );

  double cornerBR_theta = atan( hHeight / hWidth );
  double cornerBR_x = radius * cos( -cornerBR_theta - this->mapTheta );
  double cornerBR_y = radius * sin( -cornerBR_theta - this->mapTheta );

  mapDrawer->drawLine( this->x+cornerTL_x, this->y+cornerTL_y, this->x+cornerTR_x, this->y+cornerTR_y );
  mapDrawer->drawLine( this->x+cornerTL_x, this->y+cornerTL_y, this->x+cornerBL_x, this->y+cornerBL_y );
  mapDrawer->drawLine( this->x+cornerBL_x, this->y+cornerBL_y, this->x+cornerBR_x, this->y+cornerBR_y );
  mapDrawer->drawLine( this->x+cornerBR_x, this->y+cornerBR_y, this->x+cornerTR_x, this->y+cornerTR_y );

  mapDrawer->drawLine( this->x, this->y, this->x+frontX, this->y+frontY );
}
#include <iostream>
bool inTurn = false;
void Robot::update() {
  //std::cout << "update: this->deltaY" << this->deltaY << std::endl;
  //std::cout << "update: this->deltaX" << this->deltaX << std::endl;
  //std::cout << "update: this->deltaTheta" << this->deltaTheta << std::endl;
  //std::cout << "update: this->counter" << this->counter << std::endl;
  //std::cout << "update: this->endCounter" << this->endCounter << std::endl;
  this->x += this->deltaX;
  this->y += this->deltaY;
  this->mapTheta += this->deltaTheta;
  if ( this->endCounter > -1 &&
      this->counter > this->endCounter ) {
    std::cout << "Done! this->deltaTheta: " <<this->deltaTheta << std::endl;

    this->deltaX = 0;
    this->deltaY = 0;
    this->deltaTheta = 0;
    this->endCounter = -1;
    if ( inTurn )
      this->state->onTurn( this );
    else
      this->state->onMove( this );
  }
  ++this->counter;
}
#define PI 3.14
#define MOD( A, B ) ( A > B ? A - B * (int)(A / B) : A )
double Robot::calculateTheta( double x, double y ) {
  double totalX = x - this->x;
  double totalY = this->y - y;
  return atan2( totalY, totalX ) -PI/2;
}

// FirstMate methods:
bool Robot::needToTurn( Waypoint& next ) {
  double needTheta = this->calculateTheta( next.x, next.y ) - this->mapTheta;
  if ( THETA_TOLORANCE < ABS( needTheta ) )
    return true;
  return false;
}

#define POSITION_TOLERANCE 1
bool Robot::needToMove( Waypoint& next ) {
  if ( POSITION_TOLERANCE < ABS( this->x - next.x ) )
    return true;
  if ( POSITION_TOLERANCE < ABS( this->y - next.y ) )
    return true;
  return false;
}
#define TURN_RATE 0.01

void Robot::turn( Waypoint& next ) {
  //return;
  double pathTheta = this->calculateTheta( next.x, next.y );
  std::cout << "turn: pathTheta" << pathTheta << std::endl;
  double needTheta = pathTheta - this->mapTheta;
  std::cout << "turn: needTheta" << needTheta << std::endl;
//  if ( THETA_TOLORANCE < ABS( needTheta ) ) {
  double dif = ABS( needTheta );
  std::cout << "turn: dif" << dif << std::endl;
  this->deltaTheta = SIGN( needTheta ) * TURN_RATE;//SIGN( dif ) * dif;
  this->deltaY = 0;
  this->deltaX = 0;
  this->endCounter = this->counter + dif / TURN_RATE;
  std::cout << "turn: this->deltaTheta" << this->deltaTheta << std::endl;
  std::cout << "turn: this->deltaY" << this->deltaY << std::endl;
  std::cout << "turn: this->deltaX" << this->deltaX << std::endl;
  std::cout << "turn: this->counter" << this->counter << std::endl;
  std::cout << "turn: this->endCounter" << this->endCounter << std::endl;
  //this->mapTheta = pathTheta;
  inTurn= true;
}
void Robot::move( Waypoint& next ) {
  std::cout << "move: " << std::endl;
  std::cout << "move: this->x" << this->x << std::endl;
  std::cout << "move: this->y" << this->y << std::endl;
  std::cout << "move: next.x" << next.x << std::endl;
  std::cout << "move: next.y" << next.y << std::endl;
  double totalX = next.x - this->x;
  double totalY = next.y - this->y;
  double distance = sqrt( totalX * totalX + totalY * totalY );
  std::cout << "move: distance" << distance << std::endl;
  if ( distance < MOVE_RATE ) {
    this->deltaY = totalY;
    this->deltaX = totalX;
  }
  else {
    this->deltaY = totalY * ( MOVE_RATE / distance );
    this->deltaX = totalX * ( MOVE_RATE / distance );
  }
  std::cout << "move: this->deltaY" << this->deltaY << std::endl;
  std::cout << "move: this->deltaX" << this->deltaX << std::endl;
  this->deltaTheta = 0;
  this->endCounter = this->counter + distance / MOVE_RATE;
  std::cout << "move: this->counter" << this->counter << std::endl;
  std::cout << "move: this->endCounter" << this->endCounter << std::endl;
  inTurn = false;
}

