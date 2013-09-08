//visualizing of the servo with mpu6050
import processing.serial.*;

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
Graph graph1 = new Graph(250, 100, 500, 400, 0, 360);
void setup()
{
  size(VIEW_SIZE_X, VIEW_SIZE_Y, P2D);
  myPort = new Serial(this, "COM3", 115200);
  myPort.bufferUntil('\n');
  background(255,255,255);
  stroke(0,0,0);
  fill(225,225,225);
  stroke(255,255,255);
  ellipse(CIRCLE_X,CIRCLE_Y,CIRCLE_D,CIRCLE_D);
  //stroke(0,0,0);
  //noFill();
  //rect(GRAPH_X,GRAPH_Y,GRAPH_W,GRAPH_H);
  graph1.g_init();
  
}

void draw()
{
  background(255,255,255);
  stroke(0,0,0);
  fill(225,225,225);
  stroke(255,255,255);
  ellipse(CIRCLE_X,CIRCLE_Y,CIRCLE_D,CIRCLE_D);
  stroke(50);
  line(CIRCLE_X - CIRCLE_D/2 * sin(m_angle), CIRCLE_Y - CIRCLE_D/2 * cos(m_angle), CIRCLE_X + CIRCLE_D/2 * sin(m_angle), CIRCLE_Y + CIRCLE_D/2 * cos(m_angle));
  stroke(180);
  line(CIRCLE_X - CIRCLE_D/2 * sin(s_angle), CIRCLE_Y - CIRCLE_D/2 * cos(s_angle), CIRCLE_X + CIRCLE_D/2 * sin(s_angle), CIRCLE_Y + CIRCLE_D/2 * cos(s_angle));
  fill(0);
  textAlign(LEFT,TOP);
  text("Servo Angle: " + s_angle*57 + "\n" + "MPU Angle: " + m_angle*57, 20, 10);
  // graph
  //stroke(0,0,0);
  //noFill();
  //rect(GRAPH_X,GRAPH_Y,GRAPH_W,GRAPH_H);
  //stroke(0); // black
  //for (int i = 1; i <= 3; i++)
    //line(GRAPH_X, GRAPH_Y+GRAPH_H/4*i, GRAPH_X+GRAPH_W, GRAPH_Y+GRAPH_H/4*i); 
  //convert();
  //drawAxisX();
  //drawAxisX();
  graph1.g_update(m_angle*180/3.14);
  graph1.g_draw();
}

void serialEvent (Serial myPort) {
  // get the ASCII strings:
  stringMangle = myPort.readStringUntil('\t');
  stringSangle = myPort.readStringUntil('\t');
  m_angle = float(stringMangle) *3.14/180;
  s_angle = float(stringSangle) *3.14/180;
  print(stringMangle);
  myPort.clear(); // Clear buffer

  //printAxis(); // slows down the process and can result in error readings - use for debugging
}
