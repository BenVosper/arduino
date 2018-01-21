#define _TASK_MICRO_RES
#include <TaskScheduler.h>

short y = 5;
short x = 6;

byte x_max = 255;
byte y_max = 255;

const int fps = 60;
const long period = (long) 1000000 / fps;


void draw(byte x_pos, byte y_pos) {
  analogWrite(x, x_pos);
  analogWrite(y, y_pos);
//  Serial.print(x_pos);
//  Serial.print("\t");
//  Serial.print(y_pos);
//  Serial.println("");
  }

void buzz() {
  byte x_pos = random(x_max);
  byte y_pos = random(y_max);
  draw(x_pos, y_pos);
  }

void buzzball() {
  static byte ball_x_pos;
  static byte ball_y_pos;

  byte ball_radius = 5;

  if (random(2)) {
    ball_x_pos = ball_x_pos + 1;
  } else {
    ball_x_pos = ball_x_pos - 1;
  }

  if (random(2)) {
    ball_y_pos = ball_y_pos + 1;
  } else {
    ball_y_pos = ball_y_pos - 1;
  }

  byte x_pos = random(ball_x_pos - ball_radius, ball_x_pos + ball_radius);
  byte y_pos = ball_y_pos + (byte) sqrt(sq(ball_radius) - sq(x_pos));

  draw(x_pos, y_pos);
  }

Task draw_task(period, -1, buzzball);
Scheduler task_scheduler;
 
void setup() {
//  Serial.begin(9600);
  task_scheduler.addTask(draw_task);
  draw_task.enable();
}

void loop() {
  task_scheduler.execute();
}
