/* Logic for on-board LED that corresponds to the colour detected by colour sensor
 *  no colour if colour sensor is unable to decode it.
 */
void setColor(int colour)
{
  if (colour == 1)
  {
    led.setColor(255, 0, 0); // RED
    led.show();
  }
  if (colour == 2)
  {
    led.setColor(0, 255, 0); // GREEN
    led.show();
  }
  if (colour == 3)
  {
    led.setColor(255, 138, 0); // ORANGE
    led.show();
  }
  if (colour == 4)
  {
    led.setColor(255, 0, 255); // PURPLE
    led.show();
  }
  if (colour == 5)
  {
    led.setColor(0, 0, 255); // BLUE
    led.show();
  }
  if (colour == 6)
  {
    led.setColor(255, 255, 255); // WHITE
    led.show();
  }
  if (colour == 7) // if no colour detected
  {
    led.setColor(0, 0, 0);
    led.show();
  }
}
