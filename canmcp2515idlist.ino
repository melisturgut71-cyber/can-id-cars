#include <SPI.h>
#include <mcp_can.h>

#define CAN0_CS 5 


MCP_CAN CAN0(CAN0_CS); 

long unsigned int rxId; 
unsigned char len = 0;   
unsigned char rxBuf[8];  

void setup()
{
  Serial.begin(115200); 
  
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) 
  {
    Serial.println("MCP2515 Initialized Successfully!");
    CAN0.setMode(MCP_NORMAL); 
  } 
  else 
  {
    Serial.println("Error Initializing MCP2515...");
    while(1); 
  }

  Serial.println("MCP2515 Library CAN Sniffer");
  Serial.println("---------------------------------");
  Serial.println("ID | DLC | DATA");
}

void loop()
{

  if(CAN0.checkReceive() == CAN_MSGAVAIL)
  {
    
    CAN0.readMsgBuf(&rxId, &len, rxBuf);
    
   
    Serial.print("0x");
    Serial.print(rxId, HEX);
    
   
    Serial.print(" | ");
    Serial.print(len);
    Serial.print(" | ");
    
    for(int i = 0; i<len; i++)
    {
      if(rxBuf[i] < 0x10) Serial.print("0"); 
      Serial.print(rxBuf[i], HEX);
      Serial.print(" ");
    }
    Serial.println(); 
  }
}
