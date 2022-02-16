#pragma once

#include <stdint.h>
#include <math.h>

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "common/pimoroni_common.hpp"
#include "calibration.hpp"
#include "servo_state.hpp"

namespace servo {

  class Servo {
    //--------------------------------------------------
    // Constants
    //--------------------------------------------------
  public:
    static const uint16_t DEFAULT_PWM_FREQUENCY = 50;       //The standard servo update rate

  private:
    static const uint32_t MAX_PWM_WRAP = UINT16_MAX;
    static constexpr uint16_t MAX_PWM_DIVIDER = (1 << 7);

    static constexpr float MIN_VALID_PULSE = 1.0f;


    //--------------------------------------------------
    // Variables
    //--------------------------------------------------
  private:
    uint pin;
    pwm_config pwm_cfg;
    uint16_t pwm_period;
    float pwm_frequency = DEFAULT_PWM_FREQUENCY;

    ServoState state;


    //--------------------------------------------------
    // Constructors/Destructor
    //--------------------------------------------------
  public:
    Servo(uint pin, Type type = ANGULAR);
    ~Servo();

    //--------------------------------------------------
    // Methods
    //--------------------------------------------------
  public:
    bool init();

    bool is_enabled();
    void enable();
    void disable();

    float get_value();
    void set_value(float value);

    float get_pulse();
    void set_pulse(float pulse);

    void to_min();
    void to_mid();
    void to_max();
    void to_percent(float in, float in_min = 0.0f, float in_max = 1.0f);
    void to_percent(float in, float in_min, float in_max, float value_min, float value_max);

    Calibration& calibration();
  };

}