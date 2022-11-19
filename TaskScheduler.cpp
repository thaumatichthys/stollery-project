#include "TaskScheduler.hpp"


void TaskScheduler::Init(void (*func)(), uint32_t interval) {
  this->_interval = interval;
  this->_func = func;
}

void TaskScheduler::UpdateTask(uint32_t current_time) {
  if (this->_previous_time + this->_interval < current_time) {
    this->_previous_time = current_time;
    this->_func();
  }
}
