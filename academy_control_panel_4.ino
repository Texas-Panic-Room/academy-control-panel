//written by Janine Morgan with guidance from John Nguyen
// for Texas Panic Room

const int keypad = 2; //keypad begins program
const int aux = 3; //status needs to be off
const int lights = 4; //status needs to be on
const int lab = 8; //status needs to be off
const int exterior = 6; //status needs to be on
const int classroom = 7; //status needs to be on
const int plug1 = 11; //Left plug - status needs to be connected
const int plug2 = 12; //Middle plug - status needs to be connected
const int plug3 = 13; //Right plug - status needs to be connected
const int blue = 1; //press to submit

const int began = A4; // tells pi to make sound, led on
const int solve = A3; // sends signal to change LED color and trigger pi to stop timer
const int fail = 12; //sends relay signal to tell pi it's a failure


// using bool to define the state of a given variable instead of flags or counting
bool key_state = false;
bool aux_state = false;
bool lit_state = false;
bool lab_state = false;
bool ext_state = false;
bool clsrm_state = false;
bool p1_state = false;
bool p2_state = false;
bool p3_state = false;
bool blu_state = false;
bool win = false;

void setup() {

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

  pinMode (began, OUTPUT);
  pinMode (solve, OUTPUT);
  pinMode (fail, OUTPUT);

  digitalWrite(began, LOW);
  digitalWrite(solve, LOW);
  digitalWrite(fail, LOW);

  Serial.begin(9600);
  Serial.println("Academy Control Panel");
  
}

// note: when using input pullup HIGH means off/disconnected circuit
// and LOW means on/closed circuit

void loop() {

  Serial.println("...");


  if (digitalRead(keypad) == HIGH)
  {
    key_state = true;
  }
  else
  {
    key_state = false;
  }


  if (key_state == true)
  {
    Serial.println ("BEGIN");
    digitalWrite(began, HIGH);

    unsigned long start = millis(); // begin counting time

//current time minus start time is how much time passed

    while ((millis()-start) < 600000) // no more than 10 min can go by during puzzle
    {
      // check audio setting status
      if (digitalRead(aux) == HIGH)
      {
        Serial.println("AU : 1");
        aux_state = true;
      }
      else
      {
        Serial.println("AU : 0");
        aux_state = false;
      }

      // checking lights status
      if (digitalRead(lights) == LOW)
      {
        Serial.println("LT : 1");
        lit_state = true;
      }
      else
      {
        Serial.println("LT : 0");
        lit_state = false;
      }

      // checking lab status
      // if (digitalRead(lab) == LOW)
      // {
      //   Serial.println("LZ : 1");
      //   lab_state = true;
      // }
      // else
      //  {
      //    Serial.println("LZ : 0");
      //    lab_state = false;
      //  }

      // checking exterior status
      if (digitalRead(exterior) == HIGH)
      {
        Serial.println("EX : 1");
        ext_state = true;
      }
      else
      {
        Serial.println("EX : 0");
        ext_state = false;
      }

      // checking lab status
      if (digitalRead(classroom) == HIGH)
      {
        Serial.println("CA : 1");
        clsrm_state = true;
      }
      else
      {
        Serial.println("CA : 0");
        clsrm_state = false;
      }

      // checking Left plugs status
      if (digitalRead(plug1) == LOW)
      {
        Serial.println("LP : 1");
        p1_state = true;
      }
      else
      {
        Serial.println("LP : 0");
        p1_state = false;
      }

      // checking Middle plugs status
      if (digitalRead(plug2) == LOW)
      {
        Serial.println("MP : 1");
        p2_state = true;
      }
      else
      {
        Serial.println("MP : 0");
        p2_state = false;
      }

      // checking Right plugs status
      if (digitalRead(plug3) == LOW)
      {
        Serial.println("RP : 1");
        p3_state = true;
      }
      else
      {
        Serial.println("RP : 0");
        p3_state = false;
      }

      // checking blue button status
      if (digitalRead(blue) == LOW)
      {
        Serial.println("BL : 1");
        blu_state = true;
      }
      else
      {
        Serial.println("BL : 0");
        blu_state = false;
      }

      if (aux_state && lit_state && ext_state && clsrm_state && p1_state && p2_state && p3_state && blu_state)
        // removed lab state as it was inconsistent
      {
        win = true;
        start = start + 600000;
      }
      else
      {
        win = false;
      }
      delay(500);
    } // end of while loop during the 10 min active
    
    if ((millis()-start) >= 600000) // if more than 10 min has passed
    {
      Serial.println("GAME OVER");
      if (win == true)
      {
        Serial.println("WIN");
        digitalWrite(began, HIGH); // turn off one led color
        digitalWrite(solve, LOW); // turn on one led color
      }
      else
      {
        Serial.println("FAIL");
        digitalWrite(fail, HIGH);
        digitalWrite(began, HIGH); // turn off LED color
      }
      delay(180000);
      key_state = false;
    }
  } // end of keystate loop
}
