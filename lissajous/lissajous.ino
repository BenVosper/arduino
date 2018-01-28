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
  Serial.print(x_pos);
  Serial.print("\t");
  Serial.print(y_pos);
  Serial.println("");
  }

void buzz() {
  byte x_pos = random(x_max);
  byte y_pos = random(y_max);
  draw(x_pos, y_pos);
  }

void buzzball() {
  static byte ball_x_pos;
  static byte ball_y_pos;

  byte ball_radius = 10;

  switch (random(0, 4)) {
    case 0:
      ball_x_pos += 1;
      ball_y_pos += 1;
      break;
    case 1:
      ball_x_pos += 1;
      ball_y_pos -= 1;
      break;
    case 2:
      ball_x_pos -= 1;
      ball_y_pos += 1;
      break;
    case 3:
      ball_x_pos -= 1;
      ball_y_pos -= 1;
      break;
    }

  byte x_pos = random(ball_x_pos - ball_radius, ball_x_pos + ball_radius + 1);
  byte y_pos = random(ball_y_pos - ball_radius, ball_y_pos + ball_radius + 1);
  draw(x_pos, y_pos);
  }

void cycle() {
  static short x_pos;
  static short y_pos;

  const byte step = 100;

  x_pos += step;

  if (x_pos > 255) {
    x_pos = 0;
    y_pos += step;
    if (y_pos > 255) {
      y_pos = 0;
      }
    }

  draw(x_pos, y_pos);
  
  }

Task draw_task(period, -1, buzz);
Scheduler task_scheduler;
 
void setup() {
  Serial.begin(9600);
  task_scheduler.addTask(draw_task);
  draw_task.enable();
}

void loop() {
  task_scheduler.execute();
}
