#include <G35String.h>
#define LIGHT_COUNT (50)
#define G35_PIN (13)
#define START_STATE 0
#define OXYGEN_INCREASE_STATE 1
#define COL_N 7
#define ROW_N 7
#define N 50
#define PERIOD 10
#define PI 3.1415927
#define FREQ 0.8
#define MAX 16
G35String lights(G35_PIN, LIGHT_COUNT, LIGHT_COUNT, 0, true);
uint32_t led_array[LIGHT_COUNT];
uint32_t o2[LIGHT_COUNT];

int state = OXYGEN_INCREASE_STATE;
int index = 0;
float count = 0;

void setup() {
  Serial.begin(115200);
  lights.enumerate();
  clear_lights();
  
  for(int i = 0; i < LIGHT_COUNT; i++)
    led_array[i] = 0x0000;
}



void loop() {
  
  if(state == OXYGEN_INCREASE_STATE)
  {
    delay(PERIOD);
    double fact = 0.5 + (0.5*sin(millis()*2*PI*FREQ/1000.0));
    
    for(int i = 0; i < N; i ++)
    {
      double fact = 0.5 + (0.5*sin(((float)PI*i/N)+millis()*2*PI*FREQ/1000.0));
      led_array[i] = color((int)(MAX*fact/2 + 7), 50, 0, 255);
    }
    
    o2[index]++;
    if(o2[index] >= 200)
      {
        o2[index] = 200;
        index++;
      }
      
    for(int i = 0; i < N; i ++)
    {
      if(o2[i] > 10){
        int b = (int)15*o2[i]/200.0;
        led_array[i] = color(0, b/2, b, 255);
      }  
    }
  }

    write_leds();

}

void write_leds(){
    for(int i = 0; i < LIGHT_COUNT; i++)
      {
        lights.set_color(i, 0xFF, led_array[i]);
      }  
}

void set_row(int r, uint16_t color){
  for(int i = 0; i < COL_N; i++)
    led_array[constrain(r*COL_N+i,0,49)] = color;
 }
 
void set_bg(uint32_t color){
  for(int i = 0; i < N; i++)
    led_array[i] = color;
}

void clear_lights(){
    for(int i = 0; i < LIGHT_COUNT; i++){
      lights.set_color(i, 0x00, 0x000000);
    }
}



uint16_t red(uint16_t color){
  return color & 0x00F;
}
uint16_t green(uint16_t color){
  return (color>>4) & 0x00F;
}
uint16_t blue(uint16_t color){
  return (color>>8) & 0x00F;
}
uint16_t alpha(uint16_t color){
  return (color>>12) & 0x0FF;
}
uint32_t color(int r, int g, int b, int a) {
  a = (a << 12) & 0xFF000;
  b = (b << 8) & 0x0F00;
  g = (g << 4) & 0x00F0;
  r = r & 0x000F;
  return a | b | g | r; 
}


