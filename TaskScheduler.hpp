#include "Arduino.h"


class TaskScheduler {
  uint32_t _previous_time = 0;
  void (*_func)();
public:
  void Init(void (*func)(), uint32_t interval);
  void UpdateTask(uint32_t current_time);
  uint32_t _interval = 0;
  uint32_t scratch = 0; // a general purpose variable
};
