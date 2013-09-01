import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class mpu6050_servo extends PApplet {

//visualizing of the servo with mpu6050


Serial myPort;

final int VIEW_SIZE_X = 800, VIEW_SIZE_Y = 600;
final int CIRCLE_X = 100, CIRCLE_Y = 200;
final int CIRCLE_D =200;
final int GRAPH_X = 250, GRAPH_Y = 100;
final int GRAPH_W = 500, GRAPH_H = 400;
int offset_X = GRAPH_X;
int offset_Y = GRAPH_Y;
float m_angle = 0;
float s_angle = 0;
float[] angleM = new float[500];
float[] angleS = new float[500];
String stringMangle;
String stringSangle;
public void setup()
{
  size(VIEW_SIZE_X, VIEW_SIZE_Y, P2D);
  myPort = new Serial(this, "COM3", 115200);
  myPort.bufferUntil('\n');
  background(255,255,255);
  stroke(0,0,0);
  fill(225,225,225);
  stroke(255,255,255);
  ellipse(CIRCLE_X,CIRCLE_Y,CIRCLE_D,CIRCLE_D);
  stroke(0,0,0);
  noFill();
  rect(GRAPH_X,GRAPH_Y,GRAPH_W,GRAPH_H);
  
}

public void draw()
{
  background(255,255,255);
  stroke(0,0,0);
  fill(225,225,225);
  stroke(255,255,255);
  ellipse(CIRCLE_X,CIRCLE_Y,CIRCLE_D,CIRCLE_D);
  stroke(0,0,0);
  noFill();
  rect(GRAPH_X,GRAPH_Y,GRAPH_W,GRAPH_H);
  stroke(50);
  line(CIRCLE_X - CIRCLE_D/2 * sin(m_angle), CIRCLE_Y - CIRCLE_D/2 * cos(m_angle), CIRCLE_X + CIRCLE_D/2 * sin(m_angle), CIRCLE_Y + CIRCLE_D/2 * cos(m_angle));
  stroke(180);
  line(CIRCLE_X - CIRCLE_D/2 * sin(s_angle), CIRCLE_Y - CIRCLE_D/2 * cos(s_angle), CIRCLE_X + CIRCLE_D/2 * sin(s_angle), CIRCLE_Y + CIRCLE_D/2 * cos(s_angle));
  fill(0);
  textAlign(LEFT,TOP);
  text("Servo Angle: " + s_angle*57 + "\n" + "MPU Angle: " + m_angle*57, 20, 10);
  // graph
  stroke(0); // black
  for (int i = 1; i <= 3; i++)
    line(GRAPH_X, GRAPH_Y+GRAPH_H/4*i, GRAPH_X+GRAPH_W, GRAPH_Y+GRAPH_H/4*i); 
  convert();
  //drawAxisX();
  drawAxisX();
}

public void serialEvent (Serial myPort) {
  // get the ASCII strings:
  stringMangle = myPort.readStringUntil('\t');
  stringSangle = myPort.readStringUntil('\t');
  m_angle = PApplet.parseFloat(stringMangle) *3.14f/180;
  s_angle = PApplet.parseFloat(stringSangle) *3.14f/180;
  print(stringMangle);
  myPort.clear(); // Clear buffer

  //printAxis(); // slows down the process and can result in error readings - use for debugging
}
public void drawAxisX() {
  /* draw gyro x-axis */
  noFill();
  stroke(0,0,255); // blue
  // redraw everything
  beginShape();
  for(int i = 0; i<angleM.length;i++)
    vertex(offset_X+i,offset_Y+angleM[i]);
  endShape();
  // put all data one array back
  for(int i = 1; i<angleM.length;i++)
    angleM[i-1] = angleM[i];   
   
  /* draw acceleromter x-axis */
  noFill();
  stroke(0,255,0); // green
  // redraw everything
  beginShape();
  for(int i = 0; i<angleS.length;i++)
    vertex(offset_X+i,offset_Y+angleS[i]);  
  endShape();
  // put all data one array back
  for(int i = 1; i<angleS.length;i++)
    angleS[i-1] = angleS[i];   
   
  
}    

//convert all axis
int minAngle = 0;
int maxAngle = 360;

public void convert() {   
  /* convert the gyro x-axis */
  if (stringMangle != null) {
    // trim off any whitespace:
    stringMangle = trim(stringMangle);
    // convert to an float and map to the screen height, then save in buffer:    
    angleM[angleM.length-1] = map(PApplet.parseFloat(stringMangle), minAngle, maxAngle, 0, GRAPH_H);
  }
  
  /* convert the gyro y-axis */
  if (stringSangle != null) {    
    // trim off any whitespace:
    stringSangle = trim(stringSangle);
    // convert to an float and map to the screen height, then save in buffer:   
    angleS[angleS.length-1] = map(PApplet.parseFloat(stringSangle), minAngle, maxAngle, 0, GRAPH_H);
  }
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "mpu6050_servo" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
