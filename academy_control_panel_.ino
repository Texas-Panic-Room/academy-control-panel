//written by Janine Morgan for Texas Panic Room

const byte keypad = 2; //begins program

const byte aux = 3; //status needs to be off
const byte lights = 4; //status needs to be on
const byte lab = 5; //status needs to be on
const byte exterior = 6; //status needs to be off
const byte classroom = 7; //status needs to be on
const byte plug1 = 8; //Left plug - status needs to be connected
const byte plug2 = 9; //Middle plug - status needs to be connected
const byte plug3 = 10; //Right plug - status needs to be connected

const byte blue = 11; //button to submit response

const byte solve = 12; //sends relay signal to tell pi solved status
const byte fail = 13; // sends signal to second relay to tell pi failure

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

  pinMode (solve, OUTPUT);
  pinMode (fail, OUTPUT);

  digitalWrite(solve, HIGH);
  digitalWrite(fail, HIGH);
  
  Serial.println("Setup complete");

}
// note: when using input pullup HIGH means off/disconnected circuit 
// and LOW means on/closed circuit

void loop() {
  
  Serial.println("Status: Not Activated");
  Serial.println("Checking Control Statuses...");
  // wait for keypad to activate the game
  
// need to check statuses and assign boolean state (true/false)

// check audio setting status
  if (digitalRead, aux)
  {
    Serial.println("Alarm Audio: OFF");
    aux_state = true;
  }    
  else 
    { 
      Serial.println("Alarm Audio: ON");
      aux_state = false;
    }
  
// checking lights status
if (digitalRead, lights)
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
   if (digitalRead, lab)
  {
    Serial.println("Lab Zone: ON");
    lab_state = true;
  }
  else 
    { 
      Serial.println("Lab Zone: OFF");
      lab_state = false;
    }
    
// checking exterior status
   if (digitalRead, exterior)
  {
    Serial.println("Exterior Zone: OFF");
    ext_state = true;
  }
   else 
    { 
      Serial.println("Exterior Zone: ON");
      ext_state = false;
    }
    
// checking lab status
   if (digitalRead, classroom)
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
   if (digitalRead, plug1)
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
   if (digitalRead, plug2)
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
   if (digitalRead, plug3)
  {
    Serial.println("Right plug connected");
    p3_state = true;
  }
    else 
    { 
      Serial.println("Right plug disconnected");
      p3_state = false;
    }


// if the keypad is pressed, read the states and act appropriately   
  while (start < future)
  {
    if (digitalRead, keypad)
    {
      Serial.println("Game Time Activated");
      Serial.println("TEN Minutes to Attempt Override");
      if (aux_state && lit_state && lab_state && ext_state && clsrm_state && p1_state && p2_state && p3_state)
      {
        Serial.println("All toggles activated properly. Push button to submit attempt.");
        if (digitalRead(blue))
        {
          Serial.println("All statuses complete. Game SOLVED!");
          digitalWrite(solve, LOW);
          delay(1000);
        }
      }
      else
      {
        Serial.println("Override Attempt in Progress...");
      }
    }
    if (!digitalRead, keypad)
    {
      Serial.println("Waiting for activation...");
    }
   }

  if (start = future)
  {
    Serial.println("Time expired. Game FAILED");
    digitalWrite(fail, LOW);
    delay(1000);
  }
}
