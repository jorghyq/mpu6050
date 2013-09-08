class Graph
{
  // Data
  int g_xpos;
  int g_ypos;
  int g_width;
  int g_height;
  int x_max;
  int x_min;
  int y_max;
  int y_min;
  float[] x_data;
  float[] y_data;
  // Constructor
  Graph(int xpos, int ypos, int gwidth, int gheight, int ymin, int ymax)
  {
    g_xpos = xpos;
    g_ypos = ypos;
    g_width = gwidth;
    g_height = gheight;
    y_min = ymin;
    y_max = ymax;
    //x_data = new float[g_width];
    //y_data = new float[g_width];
  }
  // Functions
  void g_init()
  {
    x_data = new float[g_width];
    y_data = new float[g_width];
    stroke(0, 0, 0);
    noFill();
    rect(g_xpos, g_ypos, g_width, g_height);
  }
  void g_draw()
  {
    stroke(0, 0, 0);
    noFill();
    rect(g_xpos, g_ypos, g_width, g_height);
    stroke(0); // black
    for(int i = 1; i <= 3; i++)
      line(g_xpos, g_ypos + g_height/4*i, g_xpos + g_width, g_ypos + g_height/4*i); 
    //noFill();
    stroke(0,0,255); // blue
    // redraw everything
    beginShape();
    for(int i = 0; i < x_data.length;i++)
      vertex(g_xpos + i, g_ypos + y_data[i]);
    endShape();
    // put all data one array back
    for(int i = 1; i < y_data.length;i++)
      y_data[i-1] = y_data[i]; 
    
  }
  void g_update(float data)
  {
     y_data[y_data.length-1] = map(data, y_min, y_max, 0, g_height);
  }
}
