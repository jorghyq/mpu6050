/**
Visualize orientation information from a FreeIMU device

INSTRUCTIONS: 
This program has to be run when you have the FreeIMU_serial
program running on your Arduino and the Arduino connected to your PC.
Remember to set the serialPort variable below to point to the name the
Arduino serial port has in your system. You can get the port using the
Arduino IDE from Tools->Serial Port: the selected entry is what you have
to use as serialPort variable.

Copyright (C) 2011-2012 Fabio Varesano - http://www.varesano.net/

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

import processing.serial.*;

Serial myPort;  // Create object from Serial class


float [] q = new float [4];
float [] Euler = new float [3]; // psi, theta, phi

int lf = 10; // 10 is '\n' in ASCII
byte[] inBuffer = new byte[22]; // this is the number of chars on each line from the Arduino (including /r/n)

PFont font;
final int VIEW_SIZE_X = 800, VIEW_SIZE_Y = 600;

int burst = 32, count = 0;


void buildBoxShape() {
  //box(60, 10, 40);
  noStroke();
  beginShape(QUADS);
  
  //Z+ (to the drawing area)
  fill(#00ff00);
  vertex(-30, -5, 20);
  vertex(30, -5, 20);
  vertex(30, 5, 20);
  vertex(-30, 5, 20);
  
  //Z-
  fill(#0000ff);
  vertex(-30, -5, -20);
  vertex(30, -5, -20);
  vertex(30, 5, -20);
  vertex(-30, 5, -20);
  
  //X-
  fill(#ff0000);
  vertex(-30, -5, -20);
  vertex(-30, -5, 20);
  vertex(-30, 5, 20);
  vertex(-30, 5, -20);
  
  //X+
  fill(#ffff00);
  vertex(30, -5, -20);
  vertex(30, -5, 20);
  vertex(30, 5, 20);
  vertex(30, 5, -20);
  
  //Y-
  fill(#ff00ff);
  vertex(-30, -5, -20);
  vertex(30, -5, -20);
  vertex(30, -5, 20);
  vertex(-30, -5, 20);
  
  //Y+
  fill(#00ffff);
  vertex(-30, 5, -20);
  vertex(30, 5, -20);
  vertex(30, 5, 20);
  vertex(-30, 5, 20);
  
  endShape();
}


void drawcompass(float heading, int circlex, int circley, int circlediameter) {
  noStroke();
  ellipse(circlex, circley, circlediameter, circlediameter);
  fill(#ff0000);
  ellipse(circlex, circley, circlediameter/20, circlediameter/20);
  stroke(#ff0000);
  strokeWeight(4);
  line(circlex, circley, circlex - circlediameter/2 * sin(-heading), circley - circlediameter/2 * cos(-heading));
  noStroke();
  fill(#ffffff);
  textAlign(CENTER, BOTTOM);
  text("N", circlex, circley - circlediameter/2 - 10);
  textAlign(CENTER, TOP);
  text("S", circlex, circley + circlediameter/2 + 10);
  textAlign(RIGHT, CENTER);
  text("W", circlex - circlediameter/2 - 10, circley);
  textAlign(LEFT, CENTER);
  text("E", circlex + circlediameter/2 + 10, circley);
}


void drawAngle(float angle, int circlex, int circley, int circlediameter, String title) {
  angle = angle + PI/2;
  
  noStroke();
  ellipse(circlex, circley, circlediameter, circlediameter);
  fill(#ff0000);
  strokeWeight(4);
  stroke(#ff0000);
  line(circlex - circlediameter/2 * sin(angle), circley - circlediameter/2 * cos(angle), circlex + circlediameter/2 * sin(angle), circley + circlediameter/2 * cos(angle));
  noStroke();
  fill(#ffffff);
  textAlign(CENTER, BOTTOM);
  text(title, circlex, circley - circlediameter/2 - 30);
}

void draw() {  

  //quaternionToYawPitchRoll(q, Euler);
  
  background(#000000);
  fill(#ffffff);
  
  //textFont(font, 20);
  //float temp_decoded = 35.0 + ((float) (temp + 13200)) / 280;
  //text("temp:\n" + temp_decoded + " C", 350, 250);
  textAlign(LEFT, TOP);
  //text("Q:\n" + q[0] + "\n" + q[1] + "\n" + q[2] + "\n" + q[3], 20, 10);
  //text("Euler Angles:\nYaw (psi)  : " + degrees(Euler[0]) + "\nPitch (theta): " + degrees(Euler[1]) + "\nRoll (phi)  : " + degrees(Euler[2]), 200, 10);
  
  drawcompass(30, VIEW_SIZE_X/2 - 250, VIEW_SIZE_Y/2, 200);
  drawAngle(60, VIEW_SIZE_X/2, VIEW_SIZE_Y/2, 200, "Pitch:");
  drawAngle(80, VIEW_SIZE_X/2 + 250, VIEW_SIZE_Y/2, 200, "Roll:");
}


void quaternionToYawPitchRoll(float [] q, float [] ypr) {
  float gx, gy, gz; // estimated gravity direction
  
  gx = 2 * (q[1]*q[3] - q[0]*q[2]);
  gy = 2 * (q[0]*q[1] + q[2]*q[3]);
  gz = q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3];
  
  ypr[0] = atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1);
  ypr[1] = atan2(gx, sqrt(gy*gy + gz*gz));
  ypr[2] = atan2(gy, sqrt(gx*gx + gz*gz));
}


