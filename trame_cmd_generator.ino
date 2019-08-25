#define COOL B00000000
#define HEAT B00001000
#define AUTO B00000100

//static CMD trame values
unsigned char trameCmd[12] = {
  129,  //0 - HEADER
  141,
  96,   //2 - POWER & MODE
  6,
  2,    //4 - TEMP
  30,
  188,
  188,
  188,
  188,
  0,
  0,    //10 - CHECKSUM
};



bool setTemp(float temperature) {
  byte temp = temperature;
  bool halfDegree = ((temperature * 10) - (temp * 10)) > 0;

  if(temp < 15 || temp > 33) {
    Serial.println("Error setTemp: Value must be between 15 & 33");
    return false;
  }

  byte value = temp - 2;
  value = reverseBits(value);
  value = value >> 1;
  trameCmd[4] = trameCmd[4] | value;
  if(halfDegree) {
    trameCmd[4] = trameCmd[4] | B10000000;
  }
  return true;
}



bool setMode(byte mode) {
  byte mask;

  switch (mode) {
    case HEAT:
      mask = HEAT;
      break;
    case COOL:
      mask = COOL;
      break;
    case AUTO:
      mask = AUTO;
      break;
    default:
      Serial.println("Error setMode: Unknow mode");
      return false;
  }
  trameCmd[2] = trameCmd[2] | mask;
  return true;
}


bool setPower(bool power) {
  byte mask = power ? B10000000 : B00000000;
  trameCmd[2] = trameCmd[2] | mask;
  return true;
}

byte generateChecksum() {
  unsigned int total = 0;
  for (byte i=0; i< 11; i++) {
    Serial.println(trameCmd[i], BIN);
    total += reverseBits(trameCmd[i]);
  }
  byte checksum = (total - 3) % 255;
  checksum = reverseBits(checksum);
  trameCmd[10] = trameCmd[10] | checksum;
  return checksum;
}


void printTrame() {
  Serial.println("--------------------");
  for(byte i=0; i<11; i++) {
    Serial.println(trameCmd[i], BIN);
  }
  Serial.println("--------------------");
}

// Reverse the order of bits in a byte.
// I.e. MSB is swapped with LSB, etc.
byte reverseBits(unsigned char x) {
  x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
  x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
  x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
  return x;
}


void setup() {
  Serial.begin(115200);
  setPower(true);
  setMode(HEAT);
  setTemp(21);
  generateChecksum();
  printTrame();
}

void loop() {
  // put your main code here, to run repeatedly:
}
