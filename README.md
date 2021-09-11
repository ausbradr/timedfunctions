# timedfunctions
Timed Function Scheduler for ESP8266/ESP32/Arduino. 

/*==============================================================================
 * TIMED FUNCTION SCHEDULER - 2021 - BRAD ROGERS
 * =============================================================================
 * 
 * This code sample I've written is a handy template for implementing multitasking into your projects. 
 * It makes us of the "millis()" variable. This is an unsigned long variable the controller adds 1 to, every millisecond.
 * Inevitable, an unsigned long variable is only 32 bits, so can only go from 0 to 4294967295. One the max
 * is hit, it resets to zero. To avoid glitches, we've implemented code to basically do nothing when the 
 * number has rolled over, which will resume doing again when "newmillis" is greater than "oldmillis"
 * 
 * 
 * So how does it work? 
 *---------------------- 
 *First we define and zero a bunch of variables.
 *Secondly we capture the millis value at time of "void setup". This sets an initial working value
 *for our function.
 *
 *From then, our scheduler relies on a function to be repeatedly called as your program runs. 
 *That function is schedulerservice()
 *
 *Simply put, the scheduler service will check how many milliseconds have passed since last run (oldmillis).
 *If the new millis value is greater than the old, we'l continue, else the new millis is copied to oldmillis, then exiting function (in the case of millis rollover)
 *All going well, that amount of millisconds is then added to each task's "accumulator"
 *
 *The acumulators a then compared to each tasks preset time (task1preset, etc)
 *If the accumulator for a task is greater than or equal to the task's preset, then the task is triggered
 *
 *Once all the tasks have been checked and done, newmillis is copied to oldmillis.
 *
 *
 *This code is free for all to use. It's just a simple thing to help me with timing a bunch of stuff, and
 *hopefully it gives you the answer that you need too. 
 *
 * 
 */
