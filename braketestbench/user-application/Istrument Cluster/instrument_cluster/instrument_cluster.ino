/* Protocolo de Comuniação 
FP = Frame                       Analogica  
SP = Speed                       Porta A0
RP = Rotation per Minute         Porta A1
FS = Fuel Standard (Level)       Porta A2
TL = Temperature Level           Porta A3
PP = Pedal Position              Porta A4
TD = Travelled Distance          Porta A5

FE = Frame                       Digital 
BL = Brake Ligth                 Porta 2 
CL = Check Ligth                 Porta 3
RL = Refill Ligth (Battery)      Porta 4
FL = Fuel Ligth                  Porta 5 
AL = ABS Ligth                   Porta 6
HL = Handbrake Ligth             Posta 7
G1 = Gear 1 Hitched              Porta 8
G2 = Gear 2 Hitched              Porta 9
G3 = Gear 3 Hitched              Porta 10
G4 = Gear 4 Hitched              Porta 11
G5 = Gear 5 Hitched              Porta 12
GR = Reverse Gear Hitched        Porta 13
*/

//Definição de macros
#define START_ACQ_COMMAND   '@'
#define STOP_ACQ_COMMAND    '!'
#define TIMER_DELAY          10

//Declaracao de variaveis
byte byteRead;
int pinDigitalBL = 2;
int pinDigitalCL = 3;
int pinDigitalRL = 4;
int pinDigitalFL = 5;
int pinDigitalAL = 6;
int pinDigitalHL = 7;
int pinDigitalG1 = 8;
int pinDigitalG2 = 9;
int pinDigitalG3 = 10;
int pinDigitalG4 = 11;
int pinDigitalG5 = 12;
int pinDigitalGR = 13;
int SPValue;
String RPValue;
int FSValue;
int TLValue;
int PPValue;
String GearHitched;

void setup()
{
  //Configura a porta led como saida
  Serial.begin(115200); 
  //Aguarda ate a conexão com a porta
  while (!Serial);   
}

void loop()
{
  while(Serial.available() > 0)
  {
    byteRead = Serial.read();

    switch(byteRead)
    {
      case START_ACQ_COMMAND:
      {
        Serial.print("FP");
        SPValue = SPInterpolation();
        Serial.print("SP" + (String)SPValue);
        RPValue = RPInterpolation();
        Serial.print("RP" + RPValue);
        FSValue = FSInterpolation();
        Serial.print("FS" + (String)FSValue);
        TLValue = TLInterpolation();
        Serial.print("TL" + (String)TLValue);
        PPValue = PPInterpolation();
        Serial.print("PP" + (String)PPValue + "%");
        Serial.print("TD" + (String)analogRead(A5) + "Km");
        Serial.print("FE");
        Serial.print("BL" + (String)digitalRead(pinDigitalBL));
        Serial.print("CL" + (String)digitalRead(pinDigitalCL));
        Serial.print("RL" + (String)digitalRead(pinDigitalRL));
        Serial.print("FL" + (String)digitalRead(pinDigitalFL));
        Serial.print("AL" + (String)digitalRead(pinDigitalAL));
        Serial.print("HL" + (String)digitalRead(pinDigitalHL));
        GearHitched = FindGearHitched();
        Serial.print("G" + GearHitched);
      }
      break;
      case STOP_ACQ_COMMAND:
      {
        break;
      }
      break;
    }
  }
  delay(TIMER_DELAY);
}

///////// FUNCTIONS //////////

// Interpolation of Speed (SP)
int SPInterpolation()
{
  long x;
  long y = (analogRead(A0));
  x = (y * 270)/1023;
  return x;
}

//Interpolation of Rotation per minute (RP)
String RPInterpolation()
{
  String z;
  float x;
  float y = (analogRead(A1));
  x = (y * 8.0)/1023.0;
  z = (String)x;
  z.setCharAt (1, ','); 
  return z;
}

// Interpolation of Fuel Level (FS)
int FSInterpolation()
{
  long x;
  long y = (analogRead(A2));
  x = (y * 100)/1023;
  return x;
}

// Interpolation of Temperature Level (TL)
int TLInterpolation()
{
  long x;
  long y = (analogRead(A3));
  x = (y * 100)/1023;
  return x;
}

// Interpolation of Pedal Position (PP)
int PPInterpolation()
{
  long x;
  long y = (analogRead(A4));
  x = (y * 60)/1023;
  return x;
}

// Finds the gear hitched
String FindGearHitched()
{
  if (digitalRead(pinDigitalG1) == 1)
  {
    return "1";
  }
  if (digitalRead(pinDigitalG2) == 1)
  {
    return "2";
  }
  if (digitalRead(pinDigitalG3) == 1)
  {
    return "3";
  }
  if (digitalRead(pinDigitalG4) == 1)
  {
    return "4";
  }
  if (digitalRead(pinDigitalG5) == 1)
  {
    return "5";
  }
  if (digitalRead(pinDigitalGR) == 1)
  {
    return "R";
  }  
  else return "0";
}




