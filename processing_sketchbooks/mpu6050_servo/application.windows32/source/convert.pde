//convert all axis
int minAngle = 0;
int maxAngle = 360;

void convert() {   
  /* convert the gyro x-axis */
  if (stringMangle != null) {
    // trim off any whitespace:
    stringMangle = trim(stringMangle);
    // convert to an float and map to the screen height, then save in buffer:    
    angleM[angleM.length-1] = map(float(stringMangle), minAngle, maxAngle, 0, GRAPH_H);
  }
  
  /* convert the gyro y-axis */
  if (stringSangle != null) {    
    // trim off any whitespace:
    stringSangle = trim(stringSangle);
    // convert to an float and map to the screen height, then save in buffer:   
    angleS[angleS.length-1] = map(float(stringSangle), minAngle, maxAngle, 0, GRAPH_H);
  }
}
