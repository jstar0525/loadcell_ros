/*
   rosserial::std_msgs::Float64 Test
   Receives a Float64 input, subtracts 1.0, and publishes it
*/

#include <ros.h>
#include <std_msgs/Float32.h>
#include "HX711.h"

#define DOUT 3
#define CLK 2

HX711 scale(DOUT, CLK);

float calibration_factor = -136;

ros::NodeHandle nh;

std_msgs::Float32 gram;
ros::Publisher p("gram", &gram);

void setup()
{
  scale.set_scale();
  scale.tare();

  long zero_factor = scale.read_average();

  nh.initNode();
  nh.advertise(p);
}

void loop()
{
  scale.set_scale(calibration_factor);

  gram.data = scale.get_units();
  p.publish( &gram );
  nh.spinOnce();
  delay(1000);

}
