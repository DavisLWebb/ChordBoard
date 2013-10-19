/*
 *
 * keyboard.c: polls the state of the first 5 GPIO pins of the raspberry pi. Prints to STDIN after a chord is released.
 *
 */
    
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
    
#define BUTTON0 0
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3
#define BUTTON4 4

int buttonPressed();    /* Boolean return */

int main (void) {
   
      wiringPiSetup ();
                                  /* Set the GPIO pins as inputs */
      pinMode (BUTTON0, INPUT);
      pinMode (BUTTON1, INPUT);
      pinMode (BUTTON2, INPUT);
      pinMode (BUTTON3, INPUT);
      pinMode (BUTTON4, INPUT);
           
      int command[5];     /* array of current state of pressed/unpressed inputs */
      int new = 0;    /* a chord has been released -- initially false */
      while (1) {
            
              /* set array elements to 0 */
            command[0] = 0;
            command[1] = 0;
            command[2] = 0;
            command[3] = 0;
            command[4] = 0;
            
              /* Polls the button state to determine which, if any, buttons are pressed. */
            while(buttonPressed()) {
                  if (digitalRead(BUTTON0) == LOW)
                        command[0] = 1;
                  if (digitalRead(BUTTON1) == LOW)
                        command[1] = 1;
                  if (digitalRead(BUTTON2) == LOW)
                        command[2] = 1;
                  if (digitalRead(BUTTON3) == LOW)
                        command[3] = 1;
                  if (digitalRead(BUTTON4) == LOW)
                        command[4] = 1;
                  new = 1;
                  delay(1);
            }
            
            delay(1);
            
              /* If a new chord has been released and is ready to print. */
            if (new) {

                  /* add up the weighted sum of keypresses and print it */

                  int i;
                  int ret = 0;
                  for (i=0; i < 5; i++) {
                    /* for each button */
                        if (command[i]) {
                          /* if that button was pressed */
                              int ad = 1; /* weight of button */
                              
                              /* determine weight of button */
                              int j = 0;
                              while (j < i) {
                                    ad = ad*2; 
                                    j++;
                              }
                              
                              /* sum button weight */
                              ret = ret + ad;
                        }
                  }
                    /* print button weight */
                  printf("\n\t%d\n", ret);
                    /* ready for next chord */
                  new = 0;
            }
      }
}

int buttonPressed() {
        if (digitalRead(BUTTON0) == LOW)
                return 1;
        if (digitalRead(BUTTON1) == LOW)
                return 1;
        if (digitalRead(BUTTON2) == LOW)
                return 1;
        if (digitalRead(BUTTON3) == LOW)
                return 1;
        if (digitalRead(BUTTON4) == LOW)
                return 1;
        return 0;
}
