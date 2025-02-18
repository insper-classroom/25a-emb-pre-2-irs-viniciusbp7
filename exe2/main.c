#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

volatile int flag=0;
const int BTN = 28;
const int LED =4;

void btn_callback(uint gpio, uint32_t events){
  if (events == 0x4) {
    flag=1;
  }
}


int main() {
  stdio_init_all();

  gpio_init(BTN);
  gpio_set_dir(BTN, GPIO_IN);
  gpio_pull_up(BTN);

  gpio_init(LED);
  gpio_set_dir(LED, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(BTN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if (flag==1){
      flag=0;
      if (!gpio_get(LED)){
        gpio_put(LED,1);
      }
      else{
        gpio_put(LED,0);
      }
    }
  }
}
