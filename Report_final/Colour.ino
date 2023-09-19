// return 1 = turn left (RED)
// return 2 = turn right (GREEN)
// return 3 = U-turn (Orange)
// return 4 = 2 successive lefts (PURPLE)
// return 5 = 2 successive rights (LIGHT BLUE)
// return 6 = End of course --> play tune(WHITE)

// 4-2 adaptor truth table logic to get respective LEDs to light up
// L/H BLUE
// H/L GREEN
// H/H RED

// find the average reading for the requested number of times of scanning LDR
int getAvgReading(int times){      
  int reading;
  int total = 0;
  for(int i = 0;i < times;i++){
     reading = analogRead(LDR);
     total = reading + total;
     delay(LDRWait);
  }
//calculate the average and return it
  return total/times;
}

// determine colour detected based on raw LDR value detected
int get_colour(int R, int G, int B)
{
  if (R > 500 && G > 810 && B > 600)
  {
    return 6; //white 
  }
  if (R > 500 && (G > 640 && G < 730) && B > 315)
  {
    return 1; //red
  }
  if (R > 500 && G >= 730 && B < 400)
  {
    return 3; //orange
  }
  if (R < 300 && G >= 700 && B > 385)
  {
    return 2; //green
  }
  if (R < 400 && G >= 750 && B > 590)
  {
    return 5; //blue
  }
  if (R > 405 && G > 680 && B > 500)
  {
    return 4; //purple
  }
  return 7; //error :(
}

/* debug function that prints the avg readings read from LDR and returns the
 *  colour detected based on the function above.
 */
int detect_colour()
{
   analogWrite(A0, 255);
   analogWrite(A1, 255);
   delay(RGBWait);
   int red = getAvgReading(10);
   delay(RGBWait);
   
   analogWrite(A0, 255);
   analogWrite(A1, 0);
   delay(RGBWait);
   int green = getAvgReading(10);
   delay(RGBWait);

   analogWrite(A0, 0);
   analogWrite(A1, 255);
   delay(RGBWait);
   int blue = getAvgReading(10);
   delay(RGBWait);
   Serial.print("R: ");
   Serial.println(red);
   Serial.print("G: ");
   Serial.println(green);
   Serial.print("B: ");
   Serial.println(blue);
   int colour = get_colour(red, green, blue);
   return colour;
}
