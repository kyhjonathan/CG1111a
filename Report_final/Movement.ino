 /*return 1 = turn left (RED)
 * return 2 = turn right (GREEN)
 * return 3 = U-turn (Orange)
 * return 4 = 2 successive lefts (PURPLE)
 * return 5 = 2 successive rights (LIGHT BLUE)
 * return 6 = End of course --> play tune(WHITE)
*/

// combine movement into 1 function, note opp motor dir for left
void move(int left, int right)
{
  leftMotor.run(-left);
  rightMotor.run(right);
}

// stop function for specified duration
void stop(int duration)
{
  leftMotor.stop();
  rightMotor.stop();
  delay(duration);
}

// colour sensor logic for turning based on decoded colour
void turn(int colour)
{
  if (colour == 1) // RED - left turn
  {
    move(-targetSpeed, targetSpeed);
    delay(TURNING_TIME_MS);
    stop(200);
  }
  if (colour == 2) // GREEN - right turn
  {
    move(targetSpeed, -targetSpeed);
    delay(TURNING_TIME_MS);
    stop(200);
  }
  if (colour == 3)// ORANGE - UTURN
  {
    move(-targetSpeed, targetSpeed);
    delay((TURNING_TIME_MS * 2) - 50);
    stop(200);
  }
  if (colour == 4)// PURPLE 2 successive lefts
  {
    move(-targetSpeed, targetSpeed);
    delay(TURNING_TIME_MS);
    stop(200);
    move(targetSpeed, targetSpeed);
    delay(1035); // go forward for 1 tile
    //2nd left
    stop(300);
    move(-targetSpeed, targetSpeed);
    delay(TURNING_TIME_MS - 10);
    stop(200);
  }
  if (colour == 5) // BLUE - 2 successive rights
  {
    move(targetSpeed, -targetSpeed);
    delay(TURNING_TIME_MS);
    stop(200);
    move(targetSpeed, targetSpeed);
    delay(1035); // go forward for 1 tile
    // 2nd right
    stop(300);
    move(targetSpeed, -targetSpeed);
    delay(TURNING_TIME_MS - 10);
    stop(200);
  }
  if (colour == 6) // WHITE
  {
    play_tune();
  }
}

// general movement function based on PD controller for ultra, on-off controller for IR
void move_maze(int targetSpeed, float last_error)
{
  float ultra = get_ultra_distance(); // check if ultrasonic is within a workable range (able to detect wall on left)
  if (ultra >= 3.0 && ultra <= 17.0)
  {
    float error = ultra - THRESHOLD;
    float derivative = error - last_error;
    float turn = (error * kp) + (derivative * kd);
    leftMotor.run(-(targetSpeed - turn));
    rightMotor.run(targetSpeed + turn);
    last_error = error;
  }
 /* if no wall detected on ultrasonic side (left), switch to ir sensor, but given its potentially
 unreliable reading, just do minor corrections to each motor instead of PID system */
  else
  {
    float ir = get_ir_distance();
    if (ir <= 5.0) // too close to right
    {
      move(targetSpeed - 20, targetSpeed + 20);
    }
    else if (ir >= 10.0) // too close to left
    {
      move(targetSpeed + 20, targetSpeed - 20);
    }
    else // if robot is in middle OR ir detected is not in range, move forward
    {
      move(targetSpeed, targetSpeed);
    }
  }
}
