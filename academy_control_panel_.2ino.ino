//written by Janine Morgan for Texas Panic Room

const int keypad = 2; //begins program

const int aux = 3; //status needs to be off
const int lights = 4; //status needs to be on 
const int lab = 5; //status needs to be off
const int exterior = 6; //status needs to be on
const int classroom = 7; //status needs to be on
const int plug1 = 8; //Left plug - status needs to be connected
const int plug2 = 9; //Middle plug - status needs to be connected
const int plug3 = 10; //Right plug - status needs to be connected

const int blue = 11; //button to submit response

const int solve = 12; //sends relay signal to tell pi solved status
const int fail = 13; // sends signal to second relay to tell pi failure

// using bool to define the state of a given variable instead of flags or counting
// false means incorrect based on value read
bool aux_state = false;
bool lit_state = false;
bool lab_state = false;
bool ext_state = false;
bool clsrm_state = false;
bool p1_state = false;
bool p2_state = false;
bool p3_state = false;

// define time measurements
long start = millis(); // current time
long future = start + 600000; // 10 minutes of time

void setup() {
  

  Serial.begin(9600);
  Serial.println("Academy Control Panel");

  pinMode(keypad, INPUT_PULLUP);
  pinMode(aux, INPUT_PULLUP);
  pinMode(lights, INPUT_PULLUP);
  pinMode(lab, INPUT_PULLUP);
  pinMode(exterior, INPUT_PULLUP);
  pinMode(classroom, INPUT_PULLUP);
  pinMode(plug1, INPUT_PULLUP);
  pinMode(plug2, INPUT_PULLUP);
  pinMode(plug3, INPUT_PULLUP);
  pinMode(blue, INPUT_PULLUP);

  pinMode (solve, OUTPUT);
  pinMode (fail, OUTPUT);

  digitalWrite(solve, HIGH);
  digitalWrite(fail, LOW);
  
  Serial.println("Setup complete");

}
// note: when using input pullup HIGH means off/disconnected circuit 
// and LOW means on/closed circuit

void loop() {

Serial.println("Waiting for Activation");
{

if (digitalRead(keypad) == HIGH)
    {
      Serial.println("BEGIN - 10 Minutes to Attempt Override");
      
      start = millis();
      {

if (start > future)
  {
    Serial.println("Game Over");
    digitalWrite(fail, LOW);
    delay(1500);
  }
  
while (start < future)
{
  Serial.println("Checking Control Statuses...");
  
// check audio setting status
  if (digitalRead(aux) == LOW)
  {
    Serial.println("Alarm Audio: ON");
    aux_state = false;
  }    
  else 
    { 
      Serial.println("Alarm Audio: OFF");
      aux_state = true;
    }
  
// checking lights status
if (digitalRead(lights) == LOW)
  {
    Serial.println("Alarm Lights: ON");
    lit_state = true;
  }
  else 
    { 
      Serial.println("Alarm Lights: OFF");
      lit_state = false;
    }

  // checking lab status
  // if (digitalRead(lab) == HIGH)
 // {
 //   Serial.println("Lab Zone: ON");
 //   lab_state = false;
 // }
 // else 
  //  { 
  //    Serial.println("Lab Zone: OFF");
  //    lab_state = true;
  //  }
    
// checking exterior status
   if (digitalRead(exterior) == HIGH)
  {
    Serial.println("Exterior Zone: ON");
    ext_state = true;
  }
   else 
    { 
      Serial.println("Exterior Zone: OFF");
      ext_state = false;
    }
    
// checking lab status
   if (digitalRead(classroom) == HIGH)
  {
    Serial.println("Class Zone: ON");
    clsrm_state = true;
  }
   else 
    { 
      Serial.println("Class Zone: OFF");
      clsrm_state = false;
    }
   
// checking Left plugs status
   if (digitalRead(plug1) == LOW)
  {
    Serial.println("Left plug connected");
    p1_state = true;
  }
    else 
    { 
      Serial.println("Left plug disconnected");
      p1_state = false;
    }

// checking Middle plugs status
   if (digitalRead(plug2) == LOW)
  {
    Serial.println("Middle plug connected");
    p2_state = true;
  }
    else 
    { 
      Serial.println("Middle plug disconnected");
      p2_state = false;
    }
  
// checking Right plugs status
   if (digitalRead(plug3) == LOW)
  {
    Serial.println("Right plug connected");
    p3_state = true;
  }
    else 
    { 
      Serial.println("Right plug disconnected");
      p3_state = false;
    }

// checking Right plugs status
   if (digitalRead(blue) == LOW)
  {
    Serial.println("Blue Button Pushed");
  }
  else
  {
    Serial.println("    ");
  }

if (aux_state && lit_state && ext_state && clsrm_state && p1_state && p2_state && p3_state)
// removed LAB STATE as it was inconsistent
      {
        Serial.println("All toggles activated properly. Push button to submit attempt.");
        if (digitalRead(blue) == LOW)
        {
          Serial.println("All statuses complete. Game SOLVED!");
          digitalWrite(solve, LOW);
          delay(2000);
          digitalWrite(solve, HIGH);
          future = millis();
        }
      }
delay(2000);
  }
    }
}
}
 delay(2000);
}
