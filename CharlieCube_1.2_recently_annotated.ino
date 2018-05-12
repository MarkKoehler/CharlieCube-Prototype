 //<=0 is off, >= 10 is full brightness
 //Instead of a 4 dimensional array (x,y,z,color), a two dimensional array represents the cube.  To move along each axis, add or subtract 1, 4, or 16
  static int brightness[64][3] {
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 

                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 

                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 

                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, {10, 10, 10}, 
                              };
                              
  // analog pins are only referred to as analog here, but their analog functionality is not used. if any issues result from them not responding properly, check the engines section here, or the pinout of the board.
  // certain pins are used for onboard electronics, so a few pins were changed during development.  As a result, the modified pins are changed before pinout functions by the realPin() function, since math in the flash function requires pin numbers 0-15
  // A0 = 14 and A1 = 15, these are simply how the pins are denoted on an arduino, and the arduino engine automatically converts the values.                                                                                                       
  static int pins[16][4] = {
                            { 0,  4,  8, 12}, { 0,  5, 10, A1}, { 0,  6, 11, 13}, { 0,  7,  9, A0},
                            
                            { 1,  4, 10, 13}, { 1,  5,  8, A0}, { 1,  6,  9, 12}, { 1,  7, 11, A1},
                            
                            { 2,  4, 11, A0}, { 2,  5,  9, 13}, { 2,  6,  8, A1}, { 2,  7, 10, 12},
                            
                            { 3,  4,  9, A1}, { 3,  5, 11, 12}, { 3,  6, 10, A0}, { 3,  7,  8, 13}
                           };

  static int currentColor[3] = { 10, 0, 0 };

//test pins for troubleshooting
void setup() {
}

////////////////////////////////////////////////////////////////////////////////////////////
//                                       Animations                                       //
////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  int period = 400;
  
  //cubeShuffle(75);
  //rain(75);
  //chaser(400);
  //wireDisplay(2);
  //axisDisplay(1);
  //diagonalFade(12);
  diagonalDriftPsycho(4);
  //planarFlip(3);
  //cubeInversion(6);
  //spireTest();
  //clearCube();
  //diagonalDrift(3);
 // diagonalClear();
  //cubeFadeAnimation(50);

}

void cubeFadeAnimation(int cycles)
{
  while(cycles > 0)
  {
    int period = 400;
  for(int i = 1; i < 11; i++)
  {
    fadeCube(10, 10, 10);
    flash(period / 10);
  }
  
  for(int i = 1; i < 11; i++)
  {
    fadeCube(10, 1, 1);
    flash(period / 5);
  } 
  
  for(int i = 1; i < 11; i++)
  {
    fadeCube(8, 10, 1);
    flash(period / 10);
  }  
  
  for(int i = 1; i < 11; i++)
  {
    fadeCube(1, 10, 1);
    flash(period / 10);
  } 
  
  for(int i = 1; i < 11; i++)
  {
    fadeCube(1, 10, 10);
    flash(period / 10);
  } 
  
  for(int i = 1; i < 11; i++)
  {
    fadeCube(1, 1, 10);
    flash(period / 10);
  }
  
  for(int i = 1; i < 11; i++)
  {
    fadeCube(8, 1, 10);
    flash(period / 10);
  }
  cycles--;
  }
}

void cubeInversion(int cycles)
{
  while(cycles > 0)
  {
  monoColored(0,0,0);
  for(int i = 0; i < 4; i++)
  {
    monoColored(0,0,0);
    printHollowCube(0, 0, i, 3, 3, i, currentColor[0], currentColor[1], currentColor[2]);
    flash(75);
    advanceColor();
  }
  for(int i = 0; i < 4; i++)
  {
    monoColored(0,0,0);
    printHollowCube(1, 1, 3-i, 2, 2, 3-i, currentColor[0], currentColor[1], currentColor[2]);
    flash(75);
    advanceColor();
  }
  cycles--;
  }
}

void diagonalDrift(int cycles)
{
  int iterationMax = 30;
  while(cycles > 0)
  {
    for(int i = 0; i < iterationMax; i++)
    {
      for(int col = 0; col < 4; col++)
      {
        for(int row = 0; row < 4; row++)
        {
          for(int height = 0; height < 4; height++)
          {
            int color = (height + row + col + i + 2) % iterationMax;
            if(color == 0)
            {
              setrgb(getLED(row, col, height), 10, 0, 0);
            }
            if(color == 10)
            {
              setrgb(getLED(row, col, height), 0, 10, 0);
            }
            if(color == 20)
            {
              setrgb(getLED(row, col, height), 0, 0, 10);
            }
          }
        }
      }
      flash(75);
     // monoColored(0,0,0);
    }
    cycles--;
  }
}

void diagonalDriftPsycho(int cycles)
{
  int iterationMax = 30;
  while(cycles > 0)
  {
    for(int i = 0; i < iterationMax; i++)
    {
      for(int col = 0; col < 4; col++)
      {
        for(int row = 0; row < 4; row++)
        {
          for(int height = 0; height < 4; height++)
          {
            int color = (height + row + col + i + 2) % iterationMax;
            if(color == 0)
            {
              setrgb(getLED(row, col, height), currentColor[0], currentColor[1], currentColor[2]);
            }
            if(color == 10)
            {
              setrgb(getLED(row, col, height), currentColor[0], currentColor[1], currentColor[2]);
            }
            if(color == 20)
            {
              setrgb(getLED(row, col, height), currentColor[0], currentColor[1], currentColor[2]);
            }
          }
        }
      }
      flash(75);
      advanceColor(3);
     // monoColored(0,0,0);
    }
    cycles--;
  }
}




void diagonalClear()
{
  for(int i = 0; i < 11; i++)
    {
      for(int col = 0; col < 4; col++)
      {
        for(int row = 0; row < 4; row++)
        {
          for(int height = 0; height < 4; height++)
          {
            int color = (height + row + col + i + 1) % 10;
            if(color == 0)
            {
              setrgb(getLED(row, col, height), 0, 0, 0);
            }
            if(color == 10)
            {
              setrgb(getLED(row, col, height), 0, 0, 0);
            }
            if(color == 20)
            {
              setrgb(getLED(row, col, height), 0, 0, 0);
            }
          }
        }
      }
      flash(75);
    }
}


void planarFlip(int cycles)
{
  while(cycles > 0)
  {
    for(double i = 0; i <= 3; i += 0.5)
    {
      clearCube();
      planeXaa(0, 0, 3, i,   currentColor[0], currentColor[1], currentColor[2]);
      flash(50 - i * i * 5);
      advanceColor();
    }

    for(double i = 3; i >= 0; i -= 0.5)
    {
      clearCube();
      planeXaa(0, 0, i, 3,   currentColor[0], currentColor[1], currentColor[2]);
      flash(50 - i * i * 5);
      advanceColor();
    }
    flash(20);
    
    


    for(double i = 0; i <= 3; i += 0.5)
    {
      clearCube();
      planeXaa(0, 3, i, 0,   currentColor[0], currentColor[1], currentColor[2]);
      flash(50 - i * i * 5);
      advanceColor();
    }
    
    
    for(double i = 0; i <= 3; i += 0.5)
    {
      clearCube();
      planeXaa(3, i, 0, 3,   currentColor[0], currentColor[1], currentColor[2]);
      flash(50 - (3 - i) * (3 - i) * 5);
      advanceColor();
    }
    flash(20);


    for(double i = 3; i >= 0; i -= 0.5)
    {
      clearCube();
      planeXaa(3, 3, 0, i,   currentColor[0], currentColor[1], currentColor[2]);
      flash(50 - (3 - i) * (3 - i) * 5);
      advanceColor();
    }
    for(double i = 0; i <= 3; i += 0.5)
    {
      clearCube();
      planeXaa(3, 3, i, 0,   currentColor[0], currentColor[1], currentColor[2]);
      flash(50 - (3 - i) * (3 - i) * 5);
      advanceColor();
    }
    flash(20);

    for(double i = 3; i >= 0; i -= 0.5)
    {
      clearCube();
      planeXaa(3, 0, i, 3,   currentColor[0], currentColor[1], currentColor[2]);
      flash(50 - (3 - i) * (3 - i) * 5);
      advanceColor();
    }
    
    for(double i = 3; i >= 0; i -= 0.5)
    {
      clearCube();
      planeXaa(3, 0, 0, i,   currentColor[0], currentColor[1], currentColor[2]);
      flash(50 - i * i * 5);
      advanceColor();
    }
    
    flash(20);



    
    cycles--;
  }
}

void diagonalFade(int cycles)
{
  cycles *= 60;
  int tempColorArray[10][3] = { {64, 64, 64}, {64, 64, 64}, {64, 64, 64}, {64, 64, 64}, {64, 64, 64}, 
                                  {64, 64, 64}, {64, 64, 64}, {64, 64, 64}, {64, 64, 64}, {64, 64, 64} };
    for (int i = 0; i < 10; i++)
    {
      tempColorArray[i][0] = currentColor[0];
      tempColorArray[i][1] = currentColor[1];
      tempColorArray[i][2] = currentColor[2];
      advanceColor(6);
    };
  while(cycles > 0)
  {
    

    
    for(int led = 0; led < 64; led++)
    {
      int taxi = taxiCab(led);
      setrgb(led, tempColorArray[taxi][0], tempColorArray[taxi][1], tempColorArray[taxi][2]);
    }
    
    flash(18);

    for(int i = 0; i < 10; i++)
    {
      advanceColor(tempColorArray[i], 1);
    }
    
    cycles--;
  }
}

void axisDisplay(int cycles)
{
  while (cycles > 0)
  {
    for( int led = 0; led < 64; led++ )
    {
      clearCube();
      setrgb(led, currentColor[0], currentColor[1], currentColor[2]);
      advanceColor(3);
      flash(250);
    }
    
    
    cycles--;
  }
}

void wireDisplay(int cycles)
{
  while( cycles > 0 )
  {
  clearCube();
  for(int wire = 0; wire < 16; wire++)
  {
    for (int spire = 0; spire < 16; spire++)
    {
      if (pins[spire][wire / 4] == wire)
      {
        setrgb(spire + (wire / 4) * 16, currentColor[0], currentColor[1], currentColor[2]);
      }
    }
    flash(250);
    advanceColor(10);
    if (cycles != 1)
      clearCube();
  }
  cycles--;
  }
  flash(2000);
  
}


void chaser(int steps)
{
  clearCube();
  int pos[3] = {0,0,0};
  int prevpos[3] = {0,0,0};
  int dir = 0;
  
    /*
     * even = increment
     * odd = decrement
     * 0 = up
     * 1 = down
     * 2 = forward (x+)
     * 3 = backwards (x-)
     * 4 = left (y+)
     * 5 = right (y-)
     */

  while (steps > 0)
  {
    //clearCube();
    advanceColor();
    
    setrgb(getLED(prevpos[0] % 4, prevpos[1] % 4, prevpos[2] % 4), currentColor[0], currentColor[1], currentColor[2]);
    setrgb(getLED(pos[0] % 4, pos[1] % 4, pos[2] % 4), 10, 10, 10);
    
    prevpos[0] = pos[0];
    prevpos[1] = pos[1];
    prevpos[2] = pos[2];
    
    flash(50);
    if (random(8) == 0) // Chance to change direction
    {
      dir = random(6);
    }
    if (dir == 0)
    {
      pos[2]++;
      pos[2]%=4;
    }
      else if (dir == 1)
      {
        pos[2]--;
        pos[2]+=4;
        pos[2]%=4;
      }
      else if (dir == 2)
      {
        pos[1]++;
        pos[1]%=4;
      }
      else if (dir == 3)
      {
        pos[1]--;
        pos[1]+=4;
        pos[1]%=4;
      }
      else if (dir == 4)
      {
        pos[0]++;
        pos[0]%=4;
      }
      else if (dir == 5)
      {
        pos[0]--;
        pos[0]+=4;
        pos[0]%=4;
      }

    steps--;
  }
}


void rain(int steps)
{
  clearCube();
  int rollModifier = 1;

  while (steps > 0)
  {
    for (int led = 0; led < 48; led++)
    {
      setrgb(led, brightness[led + 16][0], brightness[led + 16][1], brightness[led + 16][2]);
    }
    for (int led = 48; led < 64; led++)
    {
      setrgb(led, 0, 0, 0);
    }
    if (rainRoll(rollModifier))
    {
      rollModifier+= random(2) + 1;
    }
    else
    {
      rollModifier--;
    }
    flash(75);
    advanceColor();
    steps--;
  }
  
  
}

boolean rainRoll(int rollModifier)
{
  int roll = random(rollModifier * 16);
  if (roll < 16)
  {
    setrgb(roll + 48, currentColor[0], currentColor[1], currentColor[2]);
    rainRoll(rollModifier + 2);
    return true;
  }
}

void cubeShuffle(int steps)
{
  int cubes[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}};
  int dir[3] = {0,2,4};
  while(steps > 0)
  {
    int cycles = 0;
    while (cycles < 2)
    {      
      clearCube();
      //checks if cube can increment
      for (int c = 0; c < 3; c++)
      {
        while(cubeShuffleRedirect(cubes[c], dir[c]))
        {
          dir[c] = random(6);
        }
      }
    
      //increments cubes in their direction
      for (int c = 0; c < 3; c++)
      {
        
        if (dir[c] == 0)
          {
            cubes[c][2]++;
          }
            else if (dir[c] == 1)
            {
              cubes[c][2]--;
            }
            else if (dir[c] == 2)
            {
              cubes[c][1]++;
            }
            else if (dir[c] == 3)
            {
              cubes[c][1]--;
            }
            else if (dir[c] == 4)
            {
              cubes[c][0]++;
            }
            else if (dir[c] == 5)
            {
              cubes[c][0]--;
            }
      }
    
      
      //prints all cubes from cubes array
      for(int x = 0; x < 2; x++)
      {
        for(int y = 0; y < 2; y++)
        {
          for(int z = 0; z < 2; z++)
          {
            for(int c = 0; c < 3; c++)
            {
              brightness[getLED(cubes[c][0] + x, cubes[c][1] + y, cubes[c][2] + z)][c] = 10;
            }
          }
        }
      }
  
      flash(70);
      cycles++;
    }
    flash(150);
    steps--;
  }

  
}

boolean cubeShuffleRedirect(int *cube, int dir)
{
  /*
     * even = increment
     * odd = decrement
     * 0 = up
     * 1 = down
     * 2 = forward (x+)
     * 3 = backwards (x-)
     * 4 = left (y+)
     * 5 = right (y-)
     */

  if(dir == 0 && cube[2] == 2)
  {
    return true;
  }
    else if(dir == 2 && cube[1] == 2)
    {
      return true;
    }
    else if(dir == 4 && cube[0] == 2)
    {
      return true;
    }
    else if(dir == 1 && cube[2] == 0)
    {
      return true;
    }
    else if(dir == 3 && cube[1] == 0)
    {
      return true;
    }
    else if(dir == 5 && cube[0] == 0)
    {
      return true;
    }
    else
      return false;
  
}

void spireTest()
{
  for(int i = 0; i < 4; i++)
    {
      zPlane(i, 10, 0, 0);
      flash(500);
      clearCube();
    }
  for(int i = 0; i < 4; i++)
    {
      zPlane(i, 0, 10, 0); 
      flash(500);
      clearCube();
    }
  for(int i = 0; i < 4; i++)
    {
      zPlane(i, 0, 0, 10);
      flash(500);
      clearCube();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
//                                        Engines                                        //
///////////////////////////////////////////////////////////////////////////////////////////

//This function tells the cube to display the brightness array on the cube for the specified duration.
void flash(unsigned long duration)
{
  unsigned long endTime = millis() + duration;

  
  
  while (endTime > millis())
  {

    
    for (int pin = 0; pin < 16; pin++) //cycle led
    {
      
  
      //get all LEDS with pin as their anode
      int ledArray[4];
      int ledCounter = 0;
      for(int led = 0; led < 16 && ledCounter < 4; led++)
      {
        if(pins[led][pin / 4] == pin)
        {
          ledArray[ledCounter] = led;
          ledCounter++;
        } 
      }

      int activatedCathodes = 0;
      //activate cathodes
      for(ledCounter = 0; ledCounter < 4; ledCounter++)
      {
        for(int c = 0; c < 3; c++)
          if(brightness[ledArray[ledCounter] + ((pin / 4) * 16)][c] > 0)
          {
            pinMode(realPin(pins[ledArray[ledCounter]][((pin / 4) + c + 1) % 4 % 4]), OUTPUT);
            activatedCathodes++;
          }
      }

      if(activatedCathodes > 0)
      {
        //activate anode
        pinMode(realPin(pin), OUTPUT);
        digitalWrite(realPin(pin), HIGH);
        
        
        //leave lights on until their brightness value says they should be turned off
        for(int i = 1; i < 10 && activatedCathodes > 0; i++)
        {
            //delay to reach the next interval
            
            delayMicroseconds((i-1) * (i-1) * 2 + 1); //adjust if flashing causes discomfort
            //check the brightness settings of all the lights
            for(ledCounter = 0; ledCounter < 4 && activatedCathodes; ledCounter++)
            {
              for(int c = 0; c < 3; c++)
                if(brightness[ledArray[ledCounter] + ((pin / 4) * 16)][c] == i)
                {
                  pinMode(realPin(pins[ledArray[ledCounter]][(pin / 4 + c + 1) % 4]), INPUT);
                  activatedCathodes--;
                }
            }
            
        }
        
        //ensure cathodes with brightness > 10 are off
        for(int i = 0; i < 18; i++)
        pinMode(i, INPUT);
      }
      
    } //led loop end
    
  } // timer end
  
} //end flash


void protectedFlash(unsigned long duration)
{
  unsigned long endTime = millis() + duration;

  
  
  while (endTime > millis())
  {

    
    for (int pin = 0; pin < 16; pin++) //cycle led
    {
      
  
      //get all LEDS with pin as their anode
      int ledArray[4];
      int ledCounter = 0;
      for(int led = 0; led < 16 && ledCounter < 4; led++)
      {
        if(pins[led][pin / 4] == pin)
        {
          ledArray[ledCounter] = led;
          ledCounter++;
        } 
      }

      int activatedCathodes = 0;
      //activate cathodes
      for(ledCounter = 0; ledCounter < 4; ledCounter++)
      {
        for(int c = 0; c < 3; c++)
          if(brightness[ledArray[ledCounter] + ((pin / 4) * 16)][c] > 0)
          {
            pinMode(realPin(pins[ledArray[ledCounter]][((pin / 4) + c + 1) % 4 % 4]), OUTPUT);
            activatedCathodes++;
          }
      }

      if(activatedCathodes > 0)
      {
        //activate anode
        pinMode(realPin(pin), OUTPUT);
        digitalWrite(realPin(pin), HIGH);
        
        
        //leave lights on until their brightness value says they should be turned off
        for(int i = 1; i < 10 && activatedCathodes > 0; i++)
        {
            //delay to reach the next interval
            
            delayMicroseconds((i-1) * (i-1) * 2 + 1); //adjust if flashing causes discomfort
              
            //check the brightness settings of all the lights
            for(ledCounter = 0; ledCounter < 4 && activatedCathodes; ledCounter++)
            {
              for(int c = 0; c < 3; c++)
                if(brightness[ledArray[ledCounter] + ((pin / 4) * 16)][c] == i)
                {
                  pinMode(realPin(pins[ledArray[ledCounter]][(pin / 4 + c + 1) % 4]), INPUT);
                  activatedCathodes--;
                }
            }
            
        }
        
        //ensure cathodes with brightness > 10 are off
        for(int i = 0; i < 18; i++)
        pinMode(i, INPUT);
      }
      else
      {
        delayMicroseconds(100);
      }

      
    } //led loop end
    
  } // timer end
  
} //end flash

void balancedFlash(unsigned long duration)
{
  unsigned long endTime = millis() + duration;

  
  
  while (endTime > millis())
  {

    
    for (int pin = 0; pin < 16; pin++) //cycle led
    {
      
  
      //get all LEDS with pin as their anode
      int ledArray[4];
      int ledCounter = 0;
      for(int led = 0; led < 16 && ledCounter < 4; led++)
      {
        if(pins[led][pin / 4] == pin)
        {
          ledArray[ledCounter] = led;
          ledCounter++;
        } 
      }

      int activatedCathodes = 0;
      //activate cathodes
      for(int c = 0; c < 3; c++)
      {
        for(ledCounter = 0; ledCounter < 4; ledCounter++)
        {
          if(brightness[ledArray[ledCounter] + ((pin / 4) * 16)][c] > 0)
          {
            pinMode(realPin(pins[ledArray[ledCounter]][((pin / 4) + c + 1) % 4 % 4]), OUTPUT);
            activatedCathodes++;
          }
      

        if(activatedCathodes > 0)
        {
          //activate anode
          pinMode(realPin(pin), OUTPUT);
          digitalWrite(realPin(pin), HIGH);
          
          
          //leave lights on until their brightness value says they should be turned off
          for(int i = 1; i < 10 && activatedCathodes > 0; i++)
          {
              //delay to reach the next interval
              
              delayMicroseconds((i-1) * (i-1) * 2 + 1); //adjust if flashing causes discomfort
                
              //check the brightness settings of all the lights
              for(ledCounter = 0; ledCounter < 4 && activatedCathodes; ledCounter++)
              {
                for(int c = 0; c < 3; c++)
                  if(brightness[ledArray[ledCounter] + ((pin / 4) * 16)][c] == i)
                  {
                    pinMode(realPin(pins[ledArray[ledCounter]][(pin / 4 + c + 1) % 4]), INPUT);
                    activatedCathodes--;
                  }
              }
              
          }
          
          //ensure cathodes with brightness > 10 are off
          for(int i = 0; i < 18; i++)
          pinMode(i, INPUT);
        }

      }
    } //led loop end
    
  } // timer end
  
} //end flash
}

void technicalFlash(unsigned long duration)
{
  unsigned long endTime = millis() + duration;
  double timeMultiplier = 2 / 1.6;
  
  
  while (endTime > millis())
  {
    
    for (int pin = 0; pin < 16; pin++) //cycle led
    {
      
  
      //get all LEDS with pin as their anode
      int ledArray[4];
      int ledCounter = 0;
      for(int led = 0; led < 16 && ledCounter < 4; led++)
      {
        if(pins[led][pin / 4] == pin)
        {
          ledArray[ledCounter] = led;
          ledCounter++;
        } 
      }


      //activate cathodes
      for(ledCounter = 0; ledCounter < 4; ledCounter++)
      {
        for(int c = 0; c < 3; c++)
          if(brightness[ledArray[ledCounter] + ((pin / 4) * 16)][c] > 0)
            pinMode(realPin(pins[ledArray[ledCounter]][((pin / 4) + c + 1) % 4]), OUTPUT);
      }

      //activate anode
      pinMode(realPin(pin), OUTPUT);
      digitalWrite(realPin(pin), HIGH);

      
      //leave lights on until their brightness value says they should be turned off
      for(int i = 1; i < 11; i++)
      {
          //delay to reach the next interval
          
          delay(((i-1) * (i-1) * 2 + 1) * timeMultiplier); //adjust if flashing causes discomfort
            
          //check the brightness settings of all the lights
          for(ledCounter = 0; ledCounter < 4; ledCounter++)
          {
            for(int c = 0; c < 3; c++)
              if(brightness[ledArray[ledCounter] + ((pin / 4) * 16)][c] == i)
                pinMode(realPin(pins[ledArray[ledCounter]][(pin / 4 + c + 1) % 4]), INPUT);
          }
          
      }
      
      //ensure cathodes with brightness > 10 are off
      for(ledCounter = 0; ledCounter < 4; ledCounter++)
      {
        for(int c = 0; c < 3; c++)
            pinMode(realPin(pins[ledArray[ledCounter]][((pin / 4) + c + 1) % 4]), INPUT);
      }
      
      pinMode(realPin(pin), INPUT);
      
      
    } //led loop end
    
  } // timer end
  
} //end flash

int realPin(int pin)
{
  if( pin < 2)
    return pin + 16;
  else
    return pin;
  
}

///////////////////////////////////////////////////////////////////////////////////////////
//                                      Get Methods                                      //
///////////////////////////////////////////////////////////////////////////////////////////


//returns the position of an LED in the RGB array from its coordinate position
int getLED(int x, int y, int z)
{
  return x + y*4 + z*16;
}

//returns X value of the LED
int getX(int led)
{
  return led % 4;
}

//returns Y value of the LED
int getY(int led)
{
  return (led % 16) / 4;
}

//returns z value of the LED
int getZ(int led)
{
  return led / 16;
}

void advanceColor()
{
  advanceColor(1);  
}

int taxiCab(int led)
{
  return getY(led) + getX(led) + getZ(led);
}


void advanceColorProtected(int *currentColorProtected, int cycles)
{
  currentColorProtected[0] = currentColor[0];
  currentColorProtected[1] = currentColor[1];
  currentColorProtected[2] = currentColor[2];
  while (cycles > 0)
  {
    if (currentColorProtected[0] == 10 && currentColorProtected[1] != 10 && currentColorProtected[2] == 0)
    {
      if (currentColorProtected[1] == 0 && cycles >= 10)
      {
        currentColorProtected[1] = 10;
        cycles -= 9;
      }
      else
       currentColorProtected[1]++;
    }
    else if (currentColorProtected[0] != 0 && currentColorProtected[1] == 10 && currentColorProtected[2] == 0)
    {
      if (currentColorProtected[0] == 10 && cycles >= 10)
      {
        currentColorProtected[0] = 0;
        cycles -= 9;
      }
      else
      currentColorProtected[0]--;
    }
    else if (currentColorProtected[0] == 0 && currentColorProtected[1] == 10 && currentColorProtected[2] != 10)
    {
      if (currentColorProtected[2] == 0 && cycles >= 10)
      {
        currentColorProtected[2] = 10;
        cycles -= 9;
      }
      else
      currentColorProtected[2]++;
    }
    else if (currentColorProtected[0] == 0 && currentColorProtected[1] != 0 && currentColorProtected[2] == 10)
    {  
      if (currentColorProtected[1] == 10 && cycles >= 10)
      {
        currentColorProtected[1] = 0;
        cycles -= 9;
      }
      else
      currentColorProtected[1]--;
    }
    else if (currentColorProtected[0] != 10 && currentColorProtected[1] == 0 && currentColorProtected[2] == 10)
    {
      if (currentColorProtected[0] == 0 && cycles >= 10)
      {
        currentColorProtected[0] = 10;
        cycles -= 9;
      }
      else
      currentColorProtected[0]++;
    }
    else if (currentColorProtected[0] == 10 && currentColorProtected[1] == 0 && currentColorProtected[2] != 0)
    {
      if (currentColorProtected[2] == 10 && cycles >= 10)
      {
        currentColorProtected[2] = 0;
        cycles -= 9;
      }
      else
      currentColorProtected[2]--;
    }

      cycles--;
  }
}


void advanceColor(int *currentColorProtected, int cycles)
{
  while (cycles > 0)
  {
    if (currentColorProtected[0] == 10 && currentColorProtected[1] != 10 && currentColorProtected[2] == 0)
    {
      if (currentColorProtected[1] == 0 && cycles >= 10)
      {
        currentColorProtected[1] = 10;
        cycles -= 9;
      }
      else
       currentColorProtected[1]++;
    }
    else if (currentColorProtected[0] != 0 && currentColorProtected[1] == 10 && currentColorProtected[2] == 0)
    {
      if (currentColorProtected[0] == 10 && cycles >= 10)
      {
        currentColorProtected[0] = 0;
        cycles -= 9;
      }
      else
      currentColorProtected[0]--;
    }
    else if (currentColorProtected[0] == 0 && currentColorProtected[1] == 10 && currentColorProtected[2] != 10)
    {
      if (currentColorProtected[2] == 0 && cycles >= 10)
      {
        currentColorProtected[2] = 10;
        cycles -= 9;
      }
      else
      currentColorProtected[2]++;
    }
    else if (currentColorProtected[0] == 0 && currentColorProtected[1] != 0 && currentColorProtected[2] == 10)
    {  
      if (currentColorProtected[1] == 10 && cycles >= 10)
      {
        currentColorProtected[1] = 0;
        cycles -= 9;
      }
      else
      currentColorProtected[1]--;
    }
    else if (currentColorProtected[0] != 10 && currentColorProtected[1] == 0 && currentColorProtected[2] == 10)
    {
      if (currentColorProtected[0] == 0 && cycles >= 10)
      {
        currentColorProtected[0] = 10;
        cycles -= 9;
      }
      else
      currentColorProtected[0]++;
    }
    else if (currentColorProtected[0] == 10 && currentColorProtected[1] == 0 && currentColorProtected[2] != 0)
    {
      if (currentColorProtected[2] == 10 && cycles >= 10)
      {
        currentColorProtected[2] = 0;
        cycles -= 9;
      }
      else
      currentColorProtected[2]--;
    }

      cycles--;
  }
}

void advanceColor(int cycles)
{
  while (cycles > 0)
  {
    if (currentColor[0] == 10 && currentColor[1] != 10 && currentColor[2] == 0)
      currentColor[1]++;
    else if (currentColor[0] != 0 && currentColor[1] == 10 && currentColor[2] == 0)
      currentColor[0]--;
    else if (currentColor[0] == 0 && currentColor[1] == 10 && currentColor[2] != 10)
      currentColor[2]++;
    else if (currentColor[0] == 0 && currentColor[1] != 0 && currentColor[2] == 10)
      currentColor[1]--;
    else if (currentColor[0] != 10 && currentColor[1] == 0 && currentColor[2] == 10)
      currentColor[0]++;
    else if (currentColor[0] == 10 && currentColor[1] == 0 && currentColor[2] != 0)
      currentColor[2]--;

    cycles--;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//                                        Printers                                        //
////////////////////////////////////////////////////////////////////////////////////////////




//prints a mono colored cube to the RGB array
void monoColored(int lightLevelRed, int lightLevelBlue,   int lightLevelGreen)
{
    for (int i = 0; i < 64; i++)
    setrgb(i, lightLevelRed, lightLevelBlue, lightLevelGreen);
}

//prints a mono colored plain across the z axis to the RGB array
void zPlane(int level, int lightLevelRed,  int lightLevelBlue,   int lightLevelGreen)
{
  for (int i = 0 + 16 * level; i < 16 + 16 * level; i++)
    setrgb(i, lightLevelRed, lightLevelGreen, lightLevelBlue);
}

//sets the colors of a pixel
void setrgb(int led,    int lightLevelRed, int lightLevelGreen,  int lightLevelBlue)
{
  brightness[led][0] = lightLevelRed;
    
  brightness[led][1] = lightLevelGreen;

  brightness[led][2] = lightLevelBlue;
}

//increments each color one closer to its target
void fadeTo(int led,    int lightLevelRed, int lightLevelGreen,  int lightLevelBlue)
{
  if (brightness[led][0] < lightLevelRed)
  {
    brightness[led][0]++;
  }
  else if (brightness[led][0] > lightLevelRed)
  {
    brightness[led][0]--;
  }

  if (brightness[led][1] < lightLevelGreen)
  {
    brightness[led][1]++;
  }
  else if (brightness[led][1] > lightLevelGreen)
  {
    brightness[led][1]--;
  }

  if (brightness[led][2] < lightLevelBlue)
  {
    brightness[led][2]++;
  }
  else if (brightness[led][2] > lightLevelBlue)
  {
    brightness[led][2]--;
  }
}


//calls fadeTo on all LEDs
void fadeCube(int lightLevelRed, int lightLevelGreen,  int lightLevelBlue)
{ 
  for(int led = 0; led < 64; led++)
    fadeTo(led, lightLevelRed, lightLevelGreen, lightLevelBlue);
}

//calls fadeTo on an entire z plane
void fadeZPlane(int level, int lightLevelRed, int lightLevelGreen,  int lightLevelBlue)
{
  for (int i = 0 + 16 * level; i < 16 + 16 * level; i++)
    fadeTo(i, lightLevelRed, lightLevelGreen, lightLevelBlue);
}



void printHollowCube(int x1, int y1, int z1, int x2, int y2, int z2, int lightLevelRed, int lightLevelGreen,  int lightLevelBlue)
{
  lineX(x1, y1, z1, x2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  lineX(x1, y2, z1, x2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  lineX(x1, y1, z2, x2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  lineX(x1, y2, z2, x2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  
  lineY(x1, y1, z1, y2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  lineY(x2, y1, z1, y2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  lineY(x1, y1, z2, y2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  lineY(x2, y1, z2, y2, lightLevelRed, lightLevelGreen, lightLevelBlue);

  lineZ(x1, y1, z1, z2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  lineZ(x1, y2, z1, z2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  lineZ(x2, y1, z1, z2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  lineZ(x2, y2, z1, z2, lightLevelRed, lightLevelGreen, lightLevelBlue);
}

void line(int x1, int y1, int z1, int x2, int y2, int z2, int lightLevelRed, int lightLevelGreen,  int lightLevelBlue)
{
  if(x1 != x2)
  {
    lineX(x1, y1, z1, x2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  }
  if(y1 != y2)
  {
    lineY(x1, y1, z1, y2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  }
  if(z1 != z2)
  {
    lineZ(x1, y1, z1, z2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  }
  else
  setrgb(getLED(x1, y1, z1), lightLevelRed, lightLevelGreen, lightLevelBlue);
  
}

//Makes a straight line at the given (y,z) coordinate
void lineX(int x, int y, int z, int target, int lightLevelRed, int lightLevelGreen,  int lightLevelBlue)
{
  while(x <= target)
  {
    setrgb(getLED(x, y, z), lightLevelRed, lightLevelGreen, lightLevelBlue);
    x++;
  }
}

//Makes a straight line at the given (x,z) coordinate
void lineY(int x, int y, int z, int target, int lightLevelRed, int lightLevelGreen,  int lightLevelBlue)
{
  while(y <= target)
  {
    setrgb(getLED(x, y, z), lightLevelRed, lightLevelGreen, lightLevelBlue);
    y++;
  }
}

//Makes a straight line at the given (x,y) coordinate
void lineZ(int x, int y, int z, int target, int lightLevelRed, int lightLevelGreen,  int lightLevelBlue)
{
  while(z <= target)
  {
    setrgb(getLED(x, y, z), lightLevelRed, lightLevelGreen, lightLevelBlue);
    z++;
  }
}

//Makes a 2D line between two (y,z) coordinate points at the given x value.
void lineXaa(int x, double y1, double z1, double y2, double z2, int lightLevelRed, int lightLevelGreen, int lightLevelBlue)
{
  if( abs(y1-y2) >= abs(z1-z2))
  {
    if (y1 > y2)
    {
      double holder = y1;
      y1 = y2;
      y2 = holder;
      
      holder = z1;
      z1 = z2;
      z2 = holder;
    }
    double slope = (z1 - z2) / (y1 - y2);
    for (int pos = y1; pos <= y2; pos++)
    {
      setrgb(getLED(x, (int)pos, (int)(.5 + z1 + pos * slope)), lightLevelRed, lightLevelGreen, lightLevelBlue);
    }
    
  }
  else
  {
    
    if (z1 > z2)
    {
      double holder = z1;
      z1 = z2;
      z2 = holder;
      
      holder = y1;
      y1 = y2;
      y2 = holder;
    }
    
    double slope = (y1 - y2) / (z1 - z2);
    for (int pos = z1; pos <= z2; pos++)
    {
      setrgb(getLED(x, (int)(.5 + y1 + pos * slope), (int)pos), lightLevelRed, lightLevelGreen, lightLevelBlue);
    }
    
  }
}


//Makes a plane between two (y,z) coordinates
void planeXaa(double y1, double z1, double y2, double z2, int lightLevelRed, int lightLevelGreen, int lightLevelBlue)
{
  for(int x = 0; x <= 3; x++)
  {
    lineXaa(x, y1, z1, y2, z2, lightLevelRed, lightLevelGreen, lightLevelBlue);
  }

  
}

void clearCube()
{
  monoColored(0,0,0);
}



