#include "SPI.h"
#include "Adafruit_WS2801.h"
#include "NewPing.h"

#define TRIGGER_PIN  0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE  300  //400-500 is about the most the sensor can do
uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels

int numLEDs = 25;

//frequently used named colors
uint32_t orangered = Color(255,69,0);
uint32_t orange = Color(255,165,0);
uint32_t black = Color(0,0,0);
uint32_t red = Color(255,0,0);
uint32_t green = Color(0,255,0);
uint32_t blue = Color(0,0,255);
uint32_t yellow = Color(255,255,0);
uint32_t purple = Color(255,0,255);
uint32_t seagreen = Color(84,255,159);
uint32_t indigo = Color(75,0,130);
uint32_t violet = Color(238,130,238);
uint32_t white = Color(255,255,255);
uint32_t darkgreen = Color(0,255,0);
uint32_t forestgreen = Color(34,255,34);
uint32_t darkslategray = Color(47,255,79);
uint32_t darkolivegreen = Color(85,255,47);
uint32_t shipcove = Color(115,138,189);
uint32_t poloblue = Color(118,149,200);
uint32_t deepblue = Color(0,11,76);
//doyoubelieveinmagic?
uint32_t dybim = white+1;

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(numLEDs, dataPin, clockPin);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  strip.begin();
  strip.show();
}


void loop() {
  fade(orangered,green,250,50);
  spinner(red,green,500,false);
  bulls(red,green,blue,50);
  spiral(black ,dybim, 0, true,50);        
  meander(black,dybim,true,0,false,50);
  meander(black,dybim,true,0,true,50);  
  meander(black,dybim,false,0,true,50);    
  primaryBars(500);
  unicornSpit(500);
  unicornPoo(500);
}

//BE - fade entire strand from *c1* to *c2* in *steps* increments with *wait* delay.
int fade(uint32_t c1, uint32_t c2, double steps, int loops)
{
  for(int j=0;j<loops;j++)
  {
    //get the rgb values for each color
    byte ret[3];
    double c1_r,c1_g,c1_b,c2_r,c2_g,c2_b;
    double delta_r, delta_g, delta_b;
    
    decodeColor(c1,ret);
    c1_r = ret[0];
    c1_g = ret[1];
    c1_b = ret[2];
  
    decodeColor(c2,ret);
    c2_r = ret[0];
    c2_g = ret[1];
    c2_b = ret[2];
  
    //build a precise temp color off the starting color
    double tmpC_r = c1_r;
    double tmpC_g = c1_g;
    double tmpC_b = c1_b;
    
    all(Color(tmpC_r,tmpC_g,tmpC_b));
    delay(ping_it());
  
    if(c1_r < c2_r)
    {
      delta_r = (c2_r - c1_r) / steps;
    }else{
      delta_r = -1 * ( (c1_r - c2_r)/steps);
    }
    if(c1_g < c2_g)
    {
      delta_g = (c2_g - c1_g) / steps;
    }else{
      delta_g = -1 * ( (c1_g - c2_g)/steps);
    }
    if(c1_b < c2_b)
    {
      delta_b = (c2_b - c1_b) / steps;
    }else{
      delta_b = -1 * ( (c1_b - c2_b)/steps);
    }     
    
    for(int i=0;i<steps;i++)
    {
      tmpC_r += delta_r;
      tmpC_g += delta_g;
      tmpC_b += delta_b;
      all(Color(tmpC_r,tmpC_g,tmpC_b));
      delay(ping_it());
    }
    
    //flip our to and from colors each loop
    uint32_t tmp = c1;
    c1 = c2;
    c2 = tmp;
  }
  return 1;
}


//BE - nice animated spiral
void spiral(uint32_t bc, uint32_t fc, int enddelay, boolean clears, int loops )
{
  for(int i=0;i<loops;i++)
  {
    byte pixels[] = {12,17,18,11,8,7,6,13,16,23,22,21,20,19,10,9,0,1,2,3,4,5,14,15,24};
    colorByNumber(pixels, sizeof(pixels), bc, fc, false, enddelay, clears);
    colorByNumber(pixels, sizeof(pixels), bc, fc, true, enddelay, clears);
  }    
}

//BE - take a pleasant stroll
void meander(uint32_t bc, uint32_t fc, boolean reverse, int enddelay, boolean clears, int loops )
{
  for(int i=0;i<loops;i++)
  {
    byte pixels[] = { 0, 1, 2, 7,12,11,10, 9, 8, 7,
                  12,17,18,19,10,11,12,17,22,21,
                  20,19,18,17,22,23,24,15,14,13,
                  12,17,16,15,14,5,6,7,12,17,16,
                  15,14, 5, 4, 3, 2, 7,12,13,14,
                   5, 6, 7, 8, 9};
    colorByNumber(pixels, sizeof(pixels), bc, fc, reverse, enddelay, clears);
  }
}

//BE - Bulls is intentionally truncated from one of two possible names.
void bulls(uint32_t c1, uint32_t c2, uint32_t c3, int loops)
{
  all(Color(0,0,0));
  byte smallRing[] = {12};
  byte medRing[] = {6,7,8,11,13,18,17,16};
  byte bigRing[] = {0,1,2,3,4,5,14,15,24,23,22,21,20,19,10,9};

  for(int i=0;i<loops+1;i++)
  {
    setPixelGroup(smallRing, 1, c1);
    delay(ping_it());
    setPixelGroup(medRing, 8, c1);
    setPixelGroup(smallRing, 1, c2);
    delay(ping_it());
    setPixelGroup(bigRing, 16, c1);
    setPixelGroup(medRing, 8, c2);
    setPixelGroup(smallRing, 1, c3);
    delay(ping_it());
    setPixelGroup(bigRing, 16, c2);
    setPixelGroup(medRing, 8, c3);
    setPixelGroup(smallRing, 1, c1);
    delay(ping_it());  
    setPixelGroup(bigRing, 16, c3);
    setPixelGroup(medRing, 8, c1);
    setPixelGroup(smallRing, 1, c2);
    delay(ping_it());  
    setPixelGroup(bigRing, 16, c1);
    setPixelGroup(medRing, 8, c2);
    setPixelGroup(smallRing, 1, c3);
    delay(ping_it());  
  }
}

//BE - should have called this propellor, I think.  It spins a line.
int spinner(uint32_t bgc, uint32_t fgc, int loops, boolean reversed)
{
  all(bgc);
  byte frames[4][5] = {{22,17,12,7,2},{20,18,12,6,4},{10,11,12,13,14},{0,8,12,16,24}};
  
  for(int i=0;i<loops+1;i++)
  {
    if(reversed)
    {
      for(int j=3;j>-1;j--)
      {    
        setPixelGroup(frames[j], 5, fgc);
        delay(ping_it());
        all(bgc);    
      }
    }else{
      for(int j=0;j<4;j++)
      {
        setPixelGroup(frames[j], 5, fgc);
        delay(ping_it());
        all(bgc);    
      }
    }
  }
  return 1;
}


//BE - this was called OMGP in L2C.  (Oh My GOD, PONIES!)
int primaryBars(int loops)
{
  int rows = 5;
  int cols = 5;
  int pixel = 0;
  uint32_t colors[] = {red, orangered, yellow, green, blue, indigo, violet};
  
  for(int h=0;h<loops;h++)
  {
    pixel = 0;
    for(int i=0;i<rows;i++)
    {
      for(int j=0;j<cols;j++)
      {
        strip.setPixelColor(pixel,colors[(i)]);
        pixel++;      
      }
      strip.show();
    }
    delay(ping_it());
    uint32_t temp = colors[0];
    colors[0] = colors[1];
    colors[1] = colors[2];
    colors[2] = colors[3];
    colors[3] = colors[4];
    colors[4] = colors[5];
    colors[5] = colors[6];
    colors[6] = temp;
  }
  return 1;
} 

int unicornSpit(int loops)
{
  all(Color(0,0,0));
  byte smallRing[] = {12};
  byte medRing[] = {6,7,8,11,13,18,17,16};
  byte bigRing[] = {0,1,2,3,4,5,14,15,24,23,22,21,20,19,10,9};

  uint32_t colors[] = {red, orangered, yellow, green, blue, indigo, violet};
  
  for(int i=0;i<loops+1;i++)
  {
    setPixelGroup(smallRing, 1,   colors[(i+2)%(sizeof(colors)/sizeof(uint32_t))]);
    setPixelGroup(medRing,   8,   colors[(i+1)%(sizeof(colors)/sizeof(uint32_t))]);
    setPixelGroup(bigRing,   16,  colors[(i+0)%(sizeof(colors)/sizeof(uint32_t))]);
    delay(ping_it());  
  }  
  return 1;
}

int unicornPoo(int loops)
{
  all(Color(0,0,0));
  byte smallRing[] = {12};
  byte medRing[] = {6,7,8,11,13,18,17,16};
  byte bigRing[] = {0,1,2,3,4,5,14,15,24,23,22,21,20,19,10,9};
  
  for(int i=0;i<loops+1;i++)
  {
    setPixelGroup(smallRing, 1,   Wheel((i*10)%255));
    setPixelGroup(medRing,   8,   Wheel(((i+10)*10)%255));
    setPixelGroup(bigRing,   16,  Wheel(((i+20)*10)%255));
    delay(ping_it()); 
  }  
  return 1;
}

int ping_it(){
  int ret_val;
  ret_val=0;
  while(ret_val == 0)
  {  
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    ret_val = ((uS / US_ROUNDTRIP_CM));   
    if(ret_val == 0)
      delay(20);
  }
  return ret_val/2;
}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

//BE - sometimes it's useful to get the RGB values back when passing colors to and fro.
void decodeColor(uint32_t c, byte ret[])
{
  int r,g,b;
  
  b = c & 255;
  g = c >>= 8;
  r = c >> 8;
  
  ret[0] = r;
  ret[1] = g;
  ret[2] = b;  
}

//BE - pass an array of pixels to this and it'll draw them out in order, with *wait* in ms between each pixel.
//reverse draws it backwards, useful for animation.
int colorByNumber(byte pixels[],byte pixelCount, uint32_t bc, uint32_t fc, boolean reverse, int enddelay, boolean clears)
{
  int i;
  //set bgcolor
  if(bc < white+50)
    all(bc);
  if(reverse)
  {
    for(i=0;i<pixelCount;i++)
    {
      if(clears)
        all(bc);
     
      if(fc == (white+1))
      {
        strip.setPixelColor(pixels[i],Wheel((i+1)*10));
      }else{
        strip.setPixelColor(pixels[i],fc);
      }
      strip.show();   // write all the pixels out
      delay(ping_it());   
    }  
  }else{
    for(i=pixelCount-1;i>-1;i--)
    {
      if(clears)
        all(bc);
      
      if(fc == (white+1))
      {
        strip.setPixelColor(pixels[i],Wheel((i+1)*10));
      }else{
        strip.setPixelColor(pixels[i],fc);
      }
      strip.show();   // write all the pixels out
      delay(ping_it());   
    }
  } 
  delay(enddelay);
  return 1;
}

//BE - take an array of pixels and set them all to given color.
//you probably want to do a colorWipe or all to a background color first.
int setPixelGroup(byte pixels[],byte pixelCount, uint32_t c)
{
  byte i;
  uint32_t color = c;
  for(i=0;i<pixelCount;i++)
  {
    if(c == dybim)
    {
      color = i * ( 255/pixelCount);
    }
    strip.setPixelColor(pixels[i],color);
  }
  strip.show();
  return 1;
}


void all(uint32_t c)
{
  for(int i=0;i<numLEDs;i++)
  {
    strip.setPixelColor(i,c);
  }
  strip.show();  
}
