#include "pico/stdlib.h"

#include "breakout_rtc.hpp"

using namespace pimoroni;

I2C i2c(BOARD::PICO_EXPLORER);
BreakoutRTC3032 rtc(&i2c);

int main() {
  stdio_init_all();
  sleep_ms(5000);
  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
#endif

  if(!rtc.init()) {
    printf("Init failed! Check your connections and i2c pin choices.\n");
  }
  if(rtc.setup(true, false, true)){
    printf("RTC setup correctly\n");
  }
  else{
    while(1){
    printf("RTC setup error !\n");
    }
  }

  // Uncomment the below line on first run to set the RTC date and time to the program's compiler time
  rtc.set_to_compiler_time();

  // Make sure we have 24-hour time
  if(rtc.is_12_hour())
    rtc.set_24_hour();

  // Set to update once per second
  rtc.enable_periodic_update_interrupt(true);
  //rtc.set_backup_switchover_mode(1);
  while(true) {
    // Has a second passed?
    
    if(rtc.read_periodic_update_interrupt_flag()) {
      rtc.clear_periodic_update_interrupt_flag();
    }
      // Update the locally stored time from the RTC
      if(rtc.update_time()) {
        printf("Date: %s, Time: %s\n", rtc.string_date(), rtc.string_time());
#ifdef PICO_DEFAULT_LED_PIN
        gpio_put(PICO_DEFAULT_LED_PIN, true);
#endif
        sleep_ms(100);
#ifdef PICO_DEFAULT_LED_PIN
        gpio_put(PICO_DEFAULT_LED_PIN, false);
#endif
      }
    //}
    sleep_ms(100);
  }

  return 0;
}
