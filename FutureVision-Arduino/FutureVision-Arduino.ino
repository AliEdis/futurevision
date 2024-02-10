#include "LedControl.h"
char incomingData[20]; 
int dataLength = 0;    

int DIN = 13;
int CS =  12;
int CLK = 11;

int r_pin=10;
int g_pin=9;
int b_pin=8;

const int threshold = 1000;
const int debounceDelay = 50;  

int lastButtonState[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
unsigned long lastDebounceTime[6] = {0, 0, 0, 0, 0, 0};

const uint64_t digits_horizontal_IMAGES[] = {
  0x7e1818181c181800,
  0x7e060c3060663c00,
  0x3c66603860663c00,
  0x30307e3234383000,
  0x3c6660603e067e00,
  0x3c66663e06663c00,
  0x1818183030667e00,
  0x3c66663c66663c00,
  0x3c66607c66663c00,
  0x3c66666e76663c00
};

const uint64_t digits_vertical_IMAGES[] = {
  0x0001017f7f110100,
  0x0031794945672300,
  0x00367f4949632200,
  0x00047f7f24140c00,
  0x004e5f5151737200,
  0x00266f49497f3e00,
  0x0060785f47606000,
  0x00367f49497f3600,
  0x003e7f49497b3200,
  0x003e7f51497f3e00
};


const uint64_t IMAGES_sign_horizontal[]={
  0x0010107c10100000,
  0x0000003c00000000,
  0x006c38fe386c0000,
  0x00060c1830600000,
  0x60660c1830660600,
  0x00003c003c000000,
  0x383838fe7c381000,
  0x10387cfe38383800,
  0x10307efe7e301000,
  0x1018fcfefc181000,
  0x7c92aa82aa827c00,
  0x007cc6ba82aa827c,
  0x10387cfefeee4400
};

const uint64_t IMAGES_sign_vertical[] = {
  0x0008083e08080000,
  0x0000080808080000,
  0x082a3e1c3e2a0800,
  0x002030180c060200,
  0x002333180c666200,
  0x0000141414140000,
  0x08183f7f3f180800,
  0x080c7e7f7e0c0800,
  0x081c3e7f1c1c1c00,
  0x1c1c1c7f3e1c0800,
  0x3e41554355413e00,
  0x7c86aa8aaa867c00,
  0x387c3e1f3e7c3800
};




const uint64_t IMAGES_vertical_upper[] = {
  0x003f7f48487f3f00,
  0x00367f49497f7f00,
  0x00226341417f3e00,
  0x003e7f41417f7f00,
  0x00414949497f7f00,
  0x00404848487f7f00,
  0x00266745417f3e00,
  0x007f7f08087f7f00,
  0x0000417f7f410000,
  0x00407e7f41070600,
  0x004163361c7f7f00,
  0x00010101017f7f00,
  0x7f7f3018307f7f00,
  0x7f7f0c18307f7f00,
  0x003e7f41417f3e00,
  0x00387c44447f7f00,
  0x003d7f46427e3c00,
  0x00317b4e4c7f7f00,
  0x00266f49497b3200,
  0x0060407f7f406000,
  0x007f7f01017f7e00,
  0x007c7e03037e7c00,
  0x7f7f060c067f7f00,
  0x63771c081c776300,
  0x0070780f0f787000,
  0x006171594d474300
};
const uint64_t IMAGES_vertical_lower[] = {
  0x000f1f1515170200,
  0x00060f09097f7f00,
  0x000a1b11111f0e00,
  0x007f7f09090f0600,
  0x000c1d15151f0e00,
  0x002064447f3f0400,
  0x003e3f25253d1800,
  0x00070f08087f7f00,
  0x0000012f2f010000,
  0x00005e5f01070600,
  0x00111b0e047f7f00,
  0x0000007f7f000000,
  0x1f1f0c070c1f1f00,
  0x000f1f18181f1f00,
  0x000e1f11111f0e00,
  0x00183c24243f3f00,
  0x03013f3f243c1800,
  0x000c1c10101f1f00,
  0x0012151515150900,
  0x0008083f3f080800,
  0x001f1f01011f1e00,
  0x000c0e03030e0c00,
  0x1e1f010f011f1e00,
  0x00111b0e0e1b1100,
  0x001e1f05051d1800,
  0x0000191d17130000
  };


const uint64_t IMAGES_horizontal_upper[] = {
  0x6666667e66663c00,
  0x3e66663e66663e00,
  0x3c66060606663c00,
  0x3e66666666663e00,
  0x7e06063e06067e00,
  0x0606063e06067e00,
  0x3c66760606663c00,
  0x6666667e66666600,
  0x3c18181818183c00,
  0x1c36363030307800,
  0x66361e0e1e366600,
  0x7e06060606060600,
  0xc6c6c6d6feeec600,
  0xc6c6e6f6decec600,
  0x3c66666666663c00,
  0x06063e6666663e00,
  0x603c766666663c00,
  0x66361e3e66663e00,
  0x3c66603c06663c00,
  0x18181818185a7e00,
  0x7c66666666666600,
  0x183c666666666600,
  0xc6eefed6c6c6c600,
  0xc6c66c386cc6c600,
  0x1818183c66666600,
  0x7e060c1830607e00
};

const uint64_t IMAGES_horizontal_lower[] = {
  0x7c667c603c000000,
  0x3e66663e06060600,
  0x3c6606663c000000,
  0x7c66667c60606000,
  0x3c067e663c000000,
  0x0c0c3e0c0c6c3800,
  0x3c607c66667c0000,
  0x6666663e06060600,
  0x3c18181800180000,
  0x1c36363030003000,
  0x66361e3666060600,
  0x1818181818181800,
  0xd6d6feeec6000000,
  0x6666667e3e000000,
  0x3c6666663c000000,
  0x06063e66663e0000,
  0xf0b03c36363c0000,
  0x060666663e000000,
  0x3e403c027c000000,
  0x1818187e18180000,
  0x7c66666666000000,
  0x183c666600000000,
  0x7cd6d6d6c6000000,
  0x663c183c66000000,
  0x3c607c6666000000,
  0x3c0c18303c000000
  };

LedControl lc = LedControl(DIN, CLK, CS, 1);
void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  analogWrite(10,255);
  analogWrite(9,255);
  analogWrite(8,255);
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  Serial.begin(9600);
  
  
  
  delay(200);
}

void executeincomingData() {
  incomingData[dataLength] = '\0';
  
  if (strcmp(incomingData, "2on") == 0) {
    digitalWrite(2, HIGH);
  } 
  else if (strcmp(incomingData, "2off") == 0) {
    digitalWrite(2, LOW);
  }
  else if (strcmp(incomingData, "3on") == 0) {
    digitalWrite(3, HIGH);
  } 
  else if (strcmp(incomingData, "3off") == 0) {
    digitalWrite(3, LOW);
  }
  else if (strcmp(incomingData, "4on") == 0) {
    digitalWrite(4, HIGH);
  } 
  else if (strcmp(incomingData, "4off") == 0) {
    digitalWrite(4, LOW);
  }
  else if (strcmp(incomingData, "5on") == 0) {
    digitalWrite(5, HIGH);
  } 
  else if (strcmp(incomingData, "5off") == 0) {
    digitalWrite(5, LOW);
  }
  else if (strcmp(incomingData, "6on") == 0) {
    digitalWrite(6, HIGH);
  } 
  else if (strcmp(incomingData, "6off") == 0) {
    digitalWrite(6, LOW);
  }
  else if (strcmp(incomingData, "7on") == 0) {
    digitalWrite(7, HIGH);
  } 
  else if (strcmp(incomingData, "7off") == 0) {
    digitalWrite(7, LOW);
  }
  

  if(strcmp(incomingData, "1A")==0){
          drawImage(IMAGES_vertical_upper[0]);
          
  }
        if(strcmp(incomingData, "1B")==0){
          drawImage(IMAGES_vertical_upper[1]);
        }
        if(strcmp(incomingData, "1C")==0){
          drawImage(IMAGES_vertical_upper[2]);
        }
        if(strcmp(incomingData, "1D")==0){
          drawImage(IMAGES_vertical_upper[3]);
        }
        if(strcmp(incomingData, "1E")==0){
          drawImage(IMAGES_vertical_upper[4]);
        }
        if(strcmp(incomingData, "1F")==0){
          drawImage(IMAGES_vertical_upper[5]);
        }
        if(strcmp(incomingData, "1G")==0){
          drawImage(IMAGES_vertical_upper[6]);
        }
        if(strcmp(incomingData, "1H")==0){
          drawImage(IMAGES_vertical_upper[7]);
        }
        if(strcmp(incomingData, "1I")==0){
          drawImage(IMAGES_vertical_upper[8]);
        }
        if(strcmp(incomingData, "1J")==0){
          drawImage(IMAGES_vertical_upper[9]);
        }
        if(strcmp(incomingData, "1K")==0){
          drawImage(IMAGES_vertical_upper[10]);
        }
        if(strcmp(incomingData, "1L")==0){
          drawImage(IMAGES_vertical_upper[11]);
        }
        if(strcmp(incomingData, "1M")==0){
          drawImage(IMAGES_vertical_upper[12]);
        }
        if(strcmp(incomingData, "1N")==0){
          drawImage(IMAGES_vertical_upper[13]);
        }
        if(strcmp(incomingData, "1O")==0){
          drawImage(IMAGES_vertical_upper[14]);
        }
        if(strcmp(incomingData, "1P")==0){
          drawImage(IMAGES_vertical_upper[15]);
        }
        if(strcmp(incomingData, "1Q")==0){
          drawImage(IMAGES_vertical_upper[16]);
        }
        if(strcmp(incomingData, "1R")==0){
          drawImage(IMAGES_vertical_upper[17]);
        }
        if(strcmp(incomingData, "1S")==0){
          drawImage(IMAGES_vertical_upper[18]);
        }
        if(strcmp(incomingData, "1T")==0){
          drawImage(IMAGES_vertical_upper[19]);
        }
        if(strcmp(incomingData, "1U")==0){
          drawImage(IMAGES_vertical_upper[20]);
        }
        if(strcmp(incomingData, "1V")==0){
          drawImage(IMAGES_vertical_upper[21]);
        }
        if(strcmp(incomingData, "1W")==0){
          drawImage(IMAGES_vertical_upper[22]);
        }
        if(strcmp(incomingData, "1X")==0){
          drawImage(IMAGES_vertical_upper[23]);
        }
        if(strcmp(incomingData, "1Y")==0){
          drawImage(IMAGES_vertical_upper[24]);
        }
        if(strcmp(incomingData, "1Z")==0){
          drawImage(IMAGES_vertical_upper[25]);
        }
        if(strcmp(incomingData, "1clear")==0){
          lc.clearDisplay(0);
        }

        if(strcmp(incomingData, "1arti")==0){
          drawImage(IMAGES_sign_vertical[0]);
        }
        if(strcmp(incomingData, "1eksi")==0){
          drawImage(IMAGES_sign_vertical[1]);
        }
        if(strcmp(incomingData, "1carpma")==0){
          drawImage(IMAGES_sign_vertical[2]);
        }
        if(strcmp(incomingData, "1bolme")==0){
          drawImage(IMAGES_sign_vertical[3]);
        }
        if(strcmp(incomingData, "1yuz")==0){
          drawImage(IMAGES_sign_vertical[4]);
        }

        if(strcmp(incomingData, "11")==0){
          drawImage(digits_vertical_IMAGES[0]);
        }
        if(strcmp(incomingData, "12")==0){
          drawImage(digits_vertical_IMAGES[1]);
        }
        if(strcmp(incomingData, "13")==0){
          drawImage(digits_vertical_IMAGES[2]);
        }
        if(strcmp(incomingData, "14")==0){
          drawImage(digits_vertical_IMAGES[3]);
        }
        if(strcmp(incomingData, "15")==0){
          drawImage(digits_vertical_IMAGES[4]);
        }
        if(strcmp(incomingData, "16")==0){
          drawImage(digits_vertical_IMAGES[5]);
        }
        if(strcmp(incomingData, "17")==0){
          drawImage(digits_vertical_IMAGES[6]);
        }
        if(strcmp(incomingData, "18")==0){
          drawImage(digits_vertical_IMAGES[7]);
        }
        if(strcmp(incomingData, "19")==0){
          drawImage(digits_vertical_IMAGES[8]);
        }
        if(strcmp(incomingData, "10")==0){
          drawImage(digits_vertical_IMAGES[9]);
        }
        if(strcmp(incomingData, "11")==0){
          drawImage(digits_vertical_IMAGES[0]);
        }

        if(strcmp(incomingData, "1esit")==0){
          drawImage(IMAGES_sign_vertical[5]);
        }
        if(strcmp(incomingData, "1up")==0){
          drawImage(IMAGES_sign_vertical[6]);
        }
        if(strcmp(incomingData, "1down")==0){
          drawImage(IMAGES_sign_vertical[7]);
        }
        if(strcmp(incomingData, "1right")==0){
          drawImage(IMAGES_sign_vertical[8]);
        }
        if(strcmp(incomingData, "1left")==0){
          drawImage(IMAGES_sign_vertical[9]);
        }
        if(strcmp(incomingData, "1happy")==0){
          drawImage(IMAGES_sign_vertical[10]);
        }
        if(strcmp(incomingData, "1unhappy")==0){
          drawImage(IMAGES_sign_vertical[11]);
        }
        if(strcmp(incomingData, "1heart")==0){
          drawImage(IMAGES_sign_vertical[12]);
        }


        
        
        if(strcmp(incomingData, "1a")==0){
          drawImage(IMAGES_vertical_lower[0]);
        }
        if(strcmp(incomingData, "1b")==0){
          drawImage(IMAGES_vertical_lower[1]);
        }
        if(strcmp(incomingData, "1c")==0){
          drawImage(IMAGES_vertical_lower[2]);
        }
        if(strcmp(incomingData, "1d")==0){
          drawImage(IMAGES_vertical_lower[3]);
        }
        if(strcmp(incomingData, "1e")==0){
          drawImage(IMAGES_vertical_lower[4]);
        }
        if(strcmp(incomingData, "1f")==0){
          drawImage(IMAGES_vertical_lower[5]);
        }
        if(strcmp(incomingData, "1g")==0){
          drawImage(IMAGES_vertical_lower[6]);
        }
        if(strcmp(incomingData, "1h")==0){
          drawImage(IMAGES_vertical_lower[7]);
        }
        if(strcmp(incomingData, "1i")==0){
          drawImage(IMAGES_vertical_lower[8]);
        }
        if(strcmp(incomingData, "1j")==0){
          drawImage(IMAGES_vertical_lower[9]);
        }
        if(strcmp(incomingData, "1k")==0){
          drawImage(IMAGES_vertical_lower[10]);
        }
        if(strcmp(incomingData, "1l")==0){
          drawImage(IMAGES_vertical_lower[11]);
        }
        if(strcmp(incomingData, "1m")==0){
          drawImage(IMAGES_vertical_lower[12]);
        }
        if(strcmp(incomingData, "1n")==0){
          drawImage(IMAGES_vertical_lower[13]);
        }
        if(strcmp(incomingData, "1o")==0){
          drawImage(IMAGES_vertical_lower[14]);
        }
        if(strcmp(incomingData, "1p")==0){
          drawImage(IMAGES_vertical_lower[15]);
        }
        if(strcmp(incomingData, "1q")==0){
          drawImage(IMAGES_vertical_lower[16]);
        }
        if(strcmp(incomingData, "1r")==0){
          drawImage(IMAGES_vertical_lower[17]);
        }
        if(strcmp(incomingData, "1s")==0){
          drawImage(IMAGES_vertical_lower[18]);
        }
        if(strcmp(incomingData, "1t")==0){
          drawImage(IMAGES_vertical_lower[19]);
        }
        if(strcmp(incomingData, "1u")==0){
          drawImage(IMAGES_vertical_lower[20]);
    
        }
        if(strcmp(incomingData, "1v")==0){
          drawImage(IMAGES_vertical_lower[21]);
        }
        if(strcmp(incomingData, "1w")==0){
          drawImage(IMAGES_vertical_lower[22]);
        }
        if(strcmp(incomingData, "1x")==0){
          drawImage(IMAGES_vertical_lower[23]);
        }
        if(strcmp(incomingData, "1y")==0){
          drawImage(IMAGES_vertical_lower[24]);
        }
        if(strcmp(incomingData, "1z")==0){
          drawImage(IMAGES_vertical_lower[25]);
        }
        

        if(strcmp(incomingData, "0A")==0){
          drawImage(IMAGES_horizontal_upper[0]);
        }
        if(strcmp(incomingData, "0B")==0){
          drawImage(IMAGES_horizontal_upper[1]);
        }
        if(strcmp(incomingData, "0C")==0){
          drawImage(IMAGES_horizontal_upper[2]);
        }
        if(strcmp(incomingData, "0D")==0){
          drawImage(IMAGES_horizontal_upper[3]);
        }
        if(strcmp(incomingData, "0E")==0){
          drawImage(IMAGES_horizontal_upper[4]);
        }
        if(strcmp(incomingData, "0F")==0){
          drawImage(IMAGES_horizontal_upper[5]);
        }
        if(strcmp(incomingData, "0G")==0){
          drawImage(IMAGES_horizontal_upper[6]);
        }
        if(strcmp(incomingData, "0H")==0){
          drawImage(IMAGES_horizontal_upper[7]);
        }
        if(strcmp(incomingData, "0I")==0){
          drawImage(IMAGES_horizontal_upper[8]);
        }
        if(strcmp(incomingData, "0J")==0){
          drawImage(IMAGES_horizontal_upper[9]);
        }
        if(strcmp(incomingData, "0K")==0){
          drawImage(IMAGES_horizontal_upper[10]);
        }
        if(strcmp(incomingData, "0L")==0){
          drawImage(IMAGES_horizontal_upper[11]);
        }
        if(strcmp(incomingData, "0M")==0){
          drawImage(IMAGES_horizontal_upper[12]);
        }
        if(strcmp(incomingData, "0N")==0){
          drawImage(IMAGES_horizontal_upper[13]);
        }
        if(strcmp(incomingData, "0O")==0){
          drawImage(IMAGES_horizontal_upper[14]);
        }
        if(strcmp(incomingData, "0P")==0){
          drawImage(IMAGES_horizontal_upper[15]);
        }
        if(strcmp(incomingData, "0Q")==0){
          drawImage(IMAGES_horizontal_upper[16]);
        }
        if(strcmp(incomingData, "0R")==0){
          drawImage(IMAGES_horizontal_upper[17]);
        }
        if(strcmp(incomingData, "0S")==0){
          drawImage(IMAGES_horizontal_upper[18]);
        }
        if(strcmp(incomingData, "0T")==0){
          drawImage(IMAGES_horizontal_upper[19]);
        }
        if(strcmp(incomingData, "0U")==0){
          drawImage(IMAGES_horizontal_upper[20]);
        }
        if(strcmp(incomingData, "0V")==0){
          drawImage(IMAGES_horizontal_upper[21]);
        }
        if(strcmp(incomingData, "0W")==0){
          drawImage(IMAGES_horizontal_upper[22]);
        }
        if(strcmp(incomingData, "0X")==0){
          drawImage(IMAGES_horizontal_upper[23]);
        }
        if(strcmp(incomingData, "0Y")==0){
          drawImage(IMAGES_horizontal_upper[24]);
        }
        if(strcmp(incomingData, "0Z")==0){
          drawImage(IMAGES_horizontal_upper[25]);
        }
        if(strcmp(incomingData, "0clear")==0){
          lc.clearDisplay(0);
        }
        if(strcmp(incomingData, "0off")==0){
          lc.clearDisplay(0);
        }
        if(strcmp(incomingData, "1off")==0){
          lc.clearDisplay(0);
        }
        
        if(strcmp(incomingData, "0arti")==0){
          drawImage(IMAGES_sign_horizontal[0]);
        }
        if(strcmp(incomingData, "0eksi")==0){
          drawImage(IMAGES_sign_horizontal[1]);
        }
        if(strcmp(incomingData, "0carpma")==0){
          drawImage(IMAGES_sign_horizontal[2]);
        }
        if(strcmp(incomingData, "0bolme")==0){
          drawImage(IMAGES_sign_horizontal[3]);
        }
        if(strcmp(incomingData, "0yuz")==0){
          drawImage(IMAGES_sign_horizontal[4]);
        }

        if(strcmp(incomingData, "0esit")==0){
          drawImage(IMAGES_sign_horizontal[5]);
        }
        if(strcmp(incomingData, "0up")==0){
          drawImage(IMAGES_sign_horizontal[6]);
        }
        if(strcmp(incomingData, "0down")==0){
          drawImage(IMAGES_sign_horizontal[7]);
        }
        if(strcmp(incomingData, "0right")==0){
          drawImage(IMAGES_sign_horizontal[8]);
        }
        if(strcmp(incomingData, "0left")==0){
          drawImage(IMAGES_sign_horizontal[9]);
        }
        if(strcmp(incomingData, "0happy")==0){
          drawImage(IMAGES_sign_horizontal[10]);
        }
        if(strcmp(incomingData, "0unhappy")==0){
          drawImage(IMAGES_sign_horizontal[11]);
        }
        if(strcmp(incomingData, "0heart")==0){
          drawImage(IMAGES_sign_horizontal[12]);
        }



        




        if(strcmp(incomingData, "0a")==0){
          drawImage(IMAGES_horizontal_lower[0]);
        }
        if(strcmp(incomingData, "0b")==0){
          drawImage(IMAGES_horizontal_lower[1]);
        }
        if(strcmp(incomingData, "0c")==0){
          drawImage(IMAGES_horizontal_lower[2]);
        }
        if(strcmp(incomingData, "0d")==0){
          drawImage(IMAGES_horizontal_lower[3]);
        }
        if(strcmp(incomingData, "0e")==0){
          drawImage(IMAGES_horizontal_lower[4]);
        }
        if(strcmp(incomingData, "0f")==0){
          drawImage(IMAGES_horizontal_lower[5]);
        }
        if(strcmp(incomingData, "0g")==0){
          drawImage(IMAGES_horizontal_lower[6]);
        }
        if(strcmp(incomingData, "0h")==0){
          drawImage(IMAGES_horizontal_lower[7]);
        }
        if(strcmp(incomingData, "0i")==0){
          drawImage(IMAGES_horizontal_lower[8]);
        }
        if(strcmp(incomingData, "0j")==0){
          drawImage(IMAGES_horizontal_lower[9]);
        }
        if(strcmp(incomingData, "0k")==0){
          drawImage(IMAGES_horizontal_lower[10]);
        }
        if(strcmp(incomingData, "0l")==0){
          drawImage(IMAGES_horizontal_lower[11]);
        }
        if(strcmp(incomingData, "0m")==0){
          drawImage(IMAGES_horizontal_lower[12]);
        }
        if(strcmp(incomingData, "0n")==0){
          drawImage(IMAGES_horizontal_lower[13]);
        }
        if(strcmp(incomingData, "0o")==0){
          drawImage(IMAGES_horizontal_lower[14]);
        }
        if(strcmp(incomingData, "0p")==0){
          drawImage(IMAGES_horizontal_lower[15]);
        }
        if(strcmp(incomingData, "0q")==0){
          drawImage(IMAGES_horizontal_lower[16]);
        }
        if(strcmp(incomingData, "0r")==0){
          drawImage(IMAGES_horizontal_lower[17]);
        }
        if(strcmp(incomingData, "0s")==0){
          drawImage(IMAGES_horizontal_lower[18]);
        }
        if(strcmp(incomingData, "0t")==0){
          drawImage(IMAGES_horizontal_lower[19]);
        }
        if(strcmp(incomingData, "0u")==0){
          drawImage(IMAGES_horizontal_lower[20]);
        }
        if(strcmp(incomingData, "0v")==0){
          drawImage(IMAGES_horizontal_lower[21]);
        }
        if(strcmp(incomingData, "0w")==0){
          drawImage(IMAGES_horizontal_lower[22]);
        }
        if(strcmp(incomingData, "0x")==0){
          drawImage(IMAGES_horizontal_lower[23]);
        }
        if(strcmp(incomingData, "0y")==0){
          drawImage(IMAGES_horizontal_lower[24]);
        }
        if(strcmp(incomingData, "0z")==0){
          drawImage(IMAGES_horizontal_lower[25]);
        }
        if(strcmp(incomingData, "0clear")==0){
          lc.clearDisplay(0);
        }
        if(strcmp(incomingData, "01")==0){
          drawImage(digits_horizontal_IMAGES[0]);
        }
        if(strcmp(incomingData, "02")==0){
          drawImage(digits_horizontal_IMAGES[1]);
        }
        if(strcmp(incomingData, "03")==0){
          drawImage(digits_horizontal_IMAGES[2]);
        }
        if(strcmp(incomingData, "04")==0){
          drawImage(digits_horizontal_IMAGES[3]);
        }
        if(strcmp(incomingData, "05")==0){
          drawImage(digits_horizontal_IMAGES[4]);
        }
        if(strcmp(incomingData, "06")==0){
          drawImage(digits_horizontal_IMAGES[5]);
        }
        if(strcmp(incomingData, "07")==0){
          drawImage(digits_horizontal_IMAGES[6]);
        }
        if(strcmp(incomingData, "08")==0){
          drawImage(digits_horizontal_IMAGES[7]);
        }
        if(strcmp(incomingData, "09")==0){
          drawImage(digits_horizontal_IMAGES[8]);
        }
        if(strcmp(incomingData, "00")==0){
          drawImage(digits_horizontal_IMAGES[9]);
        }

        if (strcmp(incomingData,"rgbred")==0){
        
        analogWrite(r_pin, 0);
        analogWrite(g_pin, 255);
        analogWrite(b_pin, 255);
        
    }  if (strcmp(incomingData, "rgbblue") == 0) {
        analogWrite(r_pin, 255);
        analogWrite(g_pin, 255);
        analogWrite(b_pin, 0);
    }  if (strcmp(incomingData, "rgbpurple") == 0) {
        analogWrite(r_pin, 0);
        analogWrite(g_pin, 255);
        analogWrite(b_pin, 0);
    }  if (strcmp(incomingData, "rgbyellow") == 0) {
        analogWrite(r_pin, 0);
        analogWrite(g_pin, 0);
        analogWrite(b_pin, 255);
      
    }  if (strcmp(incomingData, "rgboff") == 0) {
        analogWrite(r_pin, 255);
        analogWrite(g_pin, 255);
        analogWrite(b_pin, 255);
    }  if (strcmp(incomingData, "rgbgreen") == 0) {
        analogWrite(r_pin, 255);
        analogWrite(g_pin, 0);
        analogWrite(b_pin, 255);
    }  if (strcmp(incomingData, "rgbwhite") == 0) {
        analogWrite(r_pin, 0);
        analogWrite(g_pin, 0);
        analogWrite(b_pin, 0);
    }  if (strcmp(incomingData, "rgblightblue") == 0) {
        analogWrite(r_pin, 255);
        analogWrite(g_pin, 255);
        analogWrite(b_pin, 0);
    }
        

  
  dataLength = 0;
  
  memset(incomingData, 0, sizeof(incomingData));
  
}

void loop() {
  
  for (int i = A0; i <= A5; i++) {
    int data = analogRead(i);
    
    
    if ((millis() - lastDebounceTime[i - A0]) > debounceDelay) {
      if (data > threshold) {
        
        if (lastButtonState[i - A0] == LOW) {
          Serial.println(i - A0);
          
        }
      }
    }

   
    lastButtonState[i - A0] = (data > threshold) ? HIGH : LOW;

   
    if (data > threshold) {
      lastDebounceTime[i - A0] = millis();
    }
  }

  while (Serial.available() > 0) {
  char incomingChar = Serial.read();
    
   
    if (incomingChar != '\n' && dataLength < sizeof(incomingData) - 1) {
      incomingData[dataLength] = incomingChar;
      dataLength++;
    } else {
      
      executeincomingData();
    }
    
}
delay(100);

}

void drawImage(uint64_t pattern) {

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      uint64_t mask = 1ULL << (row * 8 + col);
      lc.setLed(0, row, col, (pattern & mask) ? true : false);
    }
  }
}
