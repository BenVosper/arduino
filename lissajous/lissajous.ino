#include <TaskScheduler.h>

const int y = 5;
const int x = 6;

int get_analogue_value(float pos) {
  return (int) (255 * constrain(pos, 0, 1));
  }


void draw(float x_pos, float y_pos) {
  analogWrite(x, get_analogue_value(x_pos));
  analogWrite(y, get_analogue_value(y_pos));
  }

void buzz(float x_max = 1, float y_max = 1) {
  draw(random(x_max), random(y_max));
  }
  

void setup() {
  
}

void loop() {
  buzz();

}
