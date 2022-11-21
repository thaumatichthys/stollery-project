#include "DisplayDriver.hpp"
#include "TaskScheduler.hpp"

DisplayDriver dp;
TaskScheduler DisplayMuxTask;
TaskScheduler CountDownTask;
TaskScheduler BlinkDisplayTask;

uint16_t seconds_remaining = 1500;

void setup() {
  dp.Init();
  DisplayMuxTask.Init(DisplayMuxHandler, 1);
  CountDownTask.Init(CountDownHandler, 1000);
  BlinkDisplayTask.Init(BlinkDisplayHandler, 500);
  dp.dot_state = true;
}

void BlinkDisplayHandler() { // blink the display when the time is almost out
  BlinkDisplayTask.scratch = 1 - BlinkDisplayTask.scratch;
  if (seconds_remaining < 30)
    dp.enabled = BlinkDisplayTask.scratch;
}

void DisplayMuxHandler() {
  dp.UpdateMultiplex();
}

void CountDownHandler() {
  if (seconds_remaining <= 0) {
    TimerDoneHandler();
  }
  else {
    seconds_remaining--;
    dp.WriteSeconds(seconds_remaining);
  }
}

void TimerDoneHandler() {
  // put the 'splody code here
  DisplayMuxTask.scratch = 1 - DisplayMuxTask.scratch;
  dp.dot_state = false;
  dp.WriteLOL(DisplayMuxTask.scratch);
}

void loop() {
  uint32_t milliseconds = millis();
  DisplayMuxTask.UpdateTask(milliseconds);
  CountDownTask.UpdateTask(milliseconds);
  BlinkDisplayTask.UpdateTask(milliseconds);
}
