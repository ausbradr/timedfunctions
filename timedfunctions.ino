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


long oldmillis=0; //the millis reference we check first up
long newmillis=0; //the millis we store and compare to old mills
long millisdiff=0; //the diffence between new and old used to fill the accums

//These are the tasks. You can have as many as you like, they've just got to be written in the same way that
//my examples of task1/2 are done in the program. 
//You don't even have to make them by tasks, maybe just use them by time period. 
//Eg, a task that does a whole bunch of stuff every 30sec, because that's what you need done
//Just use one task for that and put all your necessary calls in task1's function
//rather than have multiple tasks each running every 30sec.
long task1accum=0; //I add how many millis have passed to qualify a task being done. When I equal task1period, I should be reset. 
long task1period=1000; //I'm a preset time period in ms that a task should be done every second. 
long task2accum=0;
long task2period=60000; //I'm a preset time period, going every minute
void setup (void) {
Serial.begin(115200);

//capture current millis value as a reference for later on:
oldmillis=millis();

//I've defined a buzzer pin so we can have periodical beeps
  pinMode(D6, OUTPUT);
  //D6 is a pin reference on the Wemos D1 ESP8266 board. If using arduino, you might want to use below instead
//  pinMode(9, OUTPUT); 
//And obviously, hook the buzzer up to pin 9 on the arduino if doing so!

}

void loop (void) {

schedulerservice(); //run me often in a loop to take care of tasks

}


void schedulerservice(){
  //In this function, we check the time and call functions as needed 

//let's snapshot current millis 
newmillis=millis();

//MILLIS OVERFLOW HANDLING
//Millis rolls over to zero in about 48 days. As long as it takes to reach 4294967295
//So the way we'll stay safe from this is by not accumulating or running if the newmillis is lower than
//the oldmillis. Newmillis should ALWAYS be higher. If newmillis is lower, we'll just bypass
//and only update oldmillis with newmillis
//This will throw timing out by three tenths of fuck-all every 48 or so days, and shouldn't be a problem.
//If it is, then use an NTP or RTC to control your timing ffs! :P 

//Lets put the guts of this operation into one big if statement. 
//
  if(newmillis > oldmillis){
  //let's count how long has passed since last update:
  millisdiff=newmillis-oldmillis;
  
  //now let's fill the accumulators:
  task1accum = task1accum + millisdiff;
  task2accum = task2accum + millisdiff;
  
  
  //Now let's see if we have enough time in our accumulators to be able to do chores!
  if(task1accum >= task1period){
    task1accum = 0; //!! It's always important you clear your accumulator if the time's expired
    task1();
  }
  
  if(task2accum >= task2period){
    task2accum = 0; //!! It's always important you clear your accumulator if the time's expired
    task2();
  }
  }

oldmillis=newmillis; //We need to save the current millis time we worked with as reference to the next time round


  
}

void task1(){
  //I am task 1
  digitalWrite(D6,HIGH);
  delay(20);
  digitalWrite(D6,LOW);
  Serial.println("Task 1 triggered");

}

void task2(){
  //I am task 2
  digitalWrite(D6,HIGH);
  delay(50);
  digitalWrite(D6,LOW);
  delay(50);
  digitalWrite(D6,HIGH);
  delay(50);
  digitalWrite(D6,LOW);
  delay(50);
  digitalWrite(D6,HIGH);
  delay(50);
  digitalWrite(D6,LOW);
  Serial.println("Task 2 triggered");  
}
