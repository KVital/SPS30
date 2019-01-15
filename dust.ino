


uint8_t buf_start[8]={0x7e, 0x00, 0x00, 0x02, 0x01, 0x03, 0xf9, 0x7e};
uint8_t buf_stop[6]={0x7e, 0x00, 0x01, 0x00, 0xfe, 0x7e};
uint8_t buf_read[6]={0x7e, 0x00, 0x03, 0x00, 0xfc, 0x7e};
uint8_t buf_rst[6]={0x7e, 0x00, 0xD3, 0x00, 0x2c, 0x7e};
uint8_t buf_PN[7]={0x7e, 0x00, 0xD0, 0x01, 0x01, 0x2D, 0x7e};
uint8_t buf_AC[7]={0x7e, 0x00, 0xD0, 0x01, 0x02, 0x2C, 0x7e};
uint8_t buf_SN[7]={0x7e, 0x00, 0xD0, 0x01, 0x03, 0x2B, 0x7e};



void setup() {
  Serial.begin(115200,SERIAL_8N1);
  delay(100);
//reset sensor
Serial.write(buf_rst,6);
readme();
delay(5000);

}



int len=0;
uint8_t buff[60];



void loop() {

 /*  Serial.write(buf_PN,7);
readme();
delay(1000);

  Serial.write(buf_AC,7);
readme();
delay(1000);

  Serial.write(buf_SN,7);
readme();
delay(1000);*/

Serial.write(buf_start,8);
readme();

delay(10000);

while(1)
{
  delay(2000);

Serial.write(buf_read,6); 
readme();}


Serial.write(buf_stop,6); 
readme();



delay(1000);
}






void errorCode(uint8_t state){

switch (state)
{
    case 0:
        Serial.println("No error");
        break;

    case 1:
        Serial.println("Wrong data length for this command (too much or little data)");
        break;

    case 2:
        Serial.println("Unknown command");
        break;

    case 3:
        Serial.println("No access right for command");
        break;

    case 4:
        Serial.println("Illegal command parameter or parameter out of allowed range");
        break;

    case 40:
        Serial.println("Internal function argument out of range");
        break;

    case 67:
        Serial.println("Command not allowed in current state");
        break;
                
    default:
        Serial.println("Unknown error code");
}
  
  
}


void CMD(uint8_t state){

switch (state)
{
    case 0:
        Serial.println("Start measurements");
        break;

    case 1:
        Serial.println("Stop measurements");
        break;

    case 3:
        Serial.println("Read measured value");
        break;

    case 0x80:
        Serial.println("Read/Write Auto Cleaning Interval");
        break;

    case 0x56:
        Serial.println("Start Fan Cleaning");
        break;

    case 0xD0:
        Serial.println("Device Information");
        break;

    case 0xd3:
        Serial.println("Reset");
        break;
                
    default:
        Serial.println("Unknown command");
}
  
  
}

float decimal = 0.0f;
int integer;
void readme(){



      if (Serial.read()==0x7e)//Start with 0x7e
    { if (Serial.read()==0)//Address is always 0
      {CMD(Serial.read());//Command
        errorCode(Serial.read());//State
      len=Serial.read();//Read data length
      int j=0;
      do{buff[j]=Serial.read();
        j++;
        }while(buff[j-1]!=0x7e); //read data+checksum to the 0x7e
        
if (len>0){//for read procedure
for(int i=0; i<(j-2);i++){//replace special values and 
        if (buff[i]==0x7d){
            
            if (buff[i+1]=0x5E){buff[i]=0x7E;};
            if (buff[i+1]=0x5D){buff[i]=0x7D;};
            if (buff[i+1]=0x31){buff[i]=0x11;};
            if (buff[i+1]=0x33){buff[i]=0x13;};
        
            for (int c = i + 1; c < (j-3); c++){buff[c] = buff[c+1];}
        }
    }
    //to float convertion
    for(int i=0;i<10;i++){
    integer=((buff[4*i]<<24)|(buff[4*i+1]<<16)|(buff[4*i+2]<<8)|buff[4*i+3]);
    memcpy(&decimal, &integer, sizeof(integer));
    Serial.print(decimal); Serial.print(" "); }//show data
}
  Serial.println();
       }}//no troubles
    else
    { Serial.println("Troubles");//is troubles
    }
  
  
  }



  
/*
void readme(){

uint8_t fb=Serial.read();

      if (fb==0x7e)//Start with 0x7e
    { if (Serial.read()==0)//Address is always 0
      {CMD(Serial.read());//Command
        errorCode(Serial.read());//State
      len=Serial.read();//Read data length
      for(int i=0;i<(len+1);i++){buff[i]=Serial.read(); }//read data+checksum
if (Serial.read()==0x7e){Serial.println("Ok"); } 

  for(int i=0;i<(len+1);i++){Serial.print(buff[i]); Serial.print(" "); }
  Serial.println();
       }}//no troubles
    else
    {Serial.print(fb); Serial.println("Troubles");//is troubles
    }
  
  
  }*/


