import processing.serial.*; 
Serial arduino; 

String stringGyroX;
String stringGyroY;
//String stringGyroZ;

String stringAccX;
String stringAccY;

String stringCompX;
String stringCompY;

String stringKalmanX;
String stringKalmanY;
String stringKalmanZ;

float kalmanX;
float kalmanY;
float kalmanZ;
void setup()
{
  size(500,500,P3D);
  arduino = new Serial(this, Serial.list()[0], 115200);
  arduino.bufferUntil('\n'); // Buffer until line feed
  println("Waiting for IMU...");
 
}
 
void draw()
{
    //translate(width/2, height/2 + 50, 0);
    //scale(3,3,3);
    background(255);
    //rotateZ(30);
    
    drawCube();
}

void serialEvent (Serial arduino) {
  // get the ASCII strings:
  //stringGyroX = arduino.readStringUntil('\t');
  //stringGyroY = arduino.readStringUntil('\t');

  //stringAccX = arduino.readStringUntil('\t');
  //stringAccY = arduino.readStringUntil('\t');

  //stringCompX = arduino.readStringUntil('\t');
  //stringCompY = arduino.readStringUntil('\t'); 

  stringKalmanX = arduino.readStringUntil('\t');
  stringKalmanY = arduino.readStringUntil('\t');
  //stringKalmanZ = arduino.readStringUntil('\t');
  kalmanX = float(trim(stringKalmanX));
  kalmanY = float(trim(stringKalmanY));
  //kalmanZ = float(trim(stringKalmanZ));
  print(kalmanX);
  print('\t');
  print(kalmanY);
  print('\t');
  //println(kalmanZ);
  arduino.clear(); // Clear buffer

  //printAxis(); // slows down the process and can result in error readings - use for debugging
}

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

void drawCube() {  
  pushMatrix();
    
    
    translate(width/2, height/2 + 50, 0);
    scale(3,3,3);
    //background(0);
    // a demonstration of the following is at 
    // http://www.varesano.net/blog/fabio/ahrs-sensor-fusion-orientation-filter-3d-graphical-rotating-cube
    //rotateY(kalmanZ/180*3.14);
    rotateX(kalmanX/180*3.14);
    rotateZ(-kalmanY/180*3.14);
    buildBoxShape();
    
  popMatrix();
}

