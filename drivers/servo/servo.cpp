#include "servo.hpp"

namespace servo {
  Servo::Servo(uint pin, Type type)
    : pin(pin), state(type) {
  }

  Servo::~Servo() {
    gpio_set_function(pin, GPIO_FUNC_NULL);
  }

  bool Servo::init() {
    pwm_cfg = pwm_get_default_config();
    pwm_config_set_wrap(&pwm_cfg, 20000 - 1);

    float div = clock_get_hz(clk_sys) / 1000000;
    pwm_config_set_clkdiv(&pwm_cfg, div);

    pwm_init(pwm_gpio_to_slice_num(pin), &pwm_cfg, true);
    gpio_set_function(pin, GPIO_FUNC_PWM);

    pwm_set_gpio_level(pin, 0);

    return true;
  }

  bool Servo::is_enabled() {
    return state.is_enabled();
  }

  void Servo::enable() {
    float new_pulse = state.enable();
    pwm_set_gpio_level(pin, (uint16_t)Converter::pulse_to_level(new_pulse, 20000));
  }

  void Servo::disable() {
    float new_pulse = state.disable();
    pwm_set_gpio_level(pin, (uint16_t)Converter::pulse_to_level(new_pulse, 20000));
  }

  float Servo::get_value() {
    return state.get_value();
  }

  void Servo::set_value(float value) {
    float new_pulse = state.set_value(value);
    pwm_set_gpio_level(pin, (uint16_t)Converter::pulse_to_level(new_pulse, 20000));
  }

  float Servo::get_pulse() {
    return state.get_pulse();
  }

  void Servo::set_pulse(float pulse) {
    float new_pulse = state.set_pulse(pulse);
    pwm_set_gpio_level(pin, (uint16_t)Converter::pulse_to_level(new_pulse, 20000));
  }

  void Servo::to_min() {
    float new_pulse = state.to_min();
    pwm_set_gpio_level(pin, (uint16_t)Converter::pulse_to_level(new_pulse, 20000));
  }

  void Servo::to_mid() {
    float new_pulse = state.to_mid();
    pwm_set_gpio_level(pin, (uint16_t)Converter::pulse_to_level(new_pulse, 20000));
  }

  void Servo::to_max() {
    float new_pulse = state.to_max();
    pwm_set_gpio_level(pin, (uint16_t)Converter::pulse_to_level(new_pulse, 20000));
  }

  void Servo::to_percent(float in, float in_min, float in_max) {
    float new_pulse = state.to_percent(in, in_min, in_max);
    pwm_set_gpio_level(pin, (uint16_t)Converter::pulse_to_level(new_pulse, 20000));
  }

  void Servo::to_percent(float in, float in_min, float in_max, float value_min, float value_max) {
    float new_pulse = state.to_percent(in, in_min, in_max, value_min, value_max);
    pwm_set_gpio_level(pin, (uint16_t)Converter::pulse_to_level(new_pulse, 20000));
  }

  Calibration& Servo::calibration() {
    return state.calibration();
  }
};