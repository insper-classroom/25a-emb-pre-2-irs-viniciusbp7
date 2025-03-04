#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

volatile int flag=0;
const int BTN_R = 28;
const int BTN_G = 26;
const int LED_R =4;
const int LED_G =6;

void btn_callback(uint gpio, uint32_t events){
  if (events == 0x4) {
    if (gpio == BTN_R){
      flag=1;
    }
  }
  else if(events==0x8){
    if (gpio == BTN_G){
      flag=2;
    }
  }
}


int main() {
  stdio_init_all();

  gpio_init(BTN_R);
  gpio_set_dir(BTN_R, GPIO_IN);
  gpio_pull_up(BTN_R);

  gpio_init(BTN_G);
  gpio_set_dir(BTN_G, GPIO_IN);
  gpio_pull_up(BTN_G);

  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);
  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(BTN_R,GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  gpio_set_irq_enabled(BTN_G, GPIO_IRQ_EDGE_RISE, true);

  while (true) {
    if (flag==1){
      flag=0;
      if (!gpio_get(LED_R)){
        gpio_put(LED_R,1);
      }
      else{
        gpio_put(LED_R,0);
      }
    }
    if (flag==2){
      flag=0;
      if (!gpio_get(LED_G)){
        gpio_put(LED_G,1);
      }
      else{
        gpio_put(LED_G,0);
      }
    }
  }
}
