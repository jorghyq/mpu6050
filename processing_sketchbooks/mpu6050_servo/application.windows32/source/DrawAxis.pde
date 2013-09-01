void drawAxisX() {
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

