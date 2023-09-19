// If you are using Port 1 of mCore, the ultrasonic sensor uses digital pin 12
// If you are using Port 2 of mCore, the ultrasonic sensor uses digital pin 10

// function that processes and returns distance sensed from ultra
float get_ultra_distance()
{
 pinMode(ULTRASONIC, OUTPUT);
 digitalWrite(ULTRASONIC, LOW);
 delayMicroseconds(2);
 digitalWrite(ULTRASONIC, HIGH);
 delayMicroseconds(10);
 digitalWrite(ULTRASONIC, LOW);

 pinMode(ULTRASONIC, INPUT);
 long duration = pulseIn(ULTRASONIC, HIGH, TIMEOUT);
 float distance = duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100;
 Serial.println(distance);
 return distance;
}

//find the average reading for the requested number of times of reading IR sensor
int getIRAverage(int times){ 
  int reading;
  int total = 0;
//take the reading as many times as requested and add them up
  for(int i = 0; i < times; i++){
     reading = analogRead(A2);
     total = reading + total;
     delay(LDRWait);
  }
  return total/times;
}

float get_ir_distance()
{
  float values = getIRAverage(5);
  Serial.println(values);
  if (values >= 950 && values <= 980) // too close to right side
  {
    return 5;
  }
  else if (values <= 935 && values >= 900)
  {
    return 10; // too close to left side
  }
  return 8; // robot is roughly in the middle OR readings are out of range
}
