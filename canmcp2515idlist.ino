#include <SPI.h>
#include <mcp_can.h>

// MCP2515 modülünüzün CS pinini ESP32'de hangi GPIO'ya bağladıysanız
// aşağıdaki '5' sayısını o pin numarasıyla değiştirin.
#define CAN0_CS 5 

// MCP2515 CAN modülünü tanımla
MCP_CAN CAN0(CAN0_CS); 

long unsigned int rxId; // Gelen mesajın ID'sini tutacak değişken
unsigned char len = 0;   // Gelen verinin uzunluğunu tutacak değişken
unsigned char rxBuf[8];  // Gelen verinin baytlarını tutacak dizi

void setup()
{
  Serial.begin(115200); // Seri Port Ekranı için hızı başlat
  
  // MCP2515 modülünü başlat
  // ÖNCE 500KBPS DENEYİN. ÇALIŞMAZSA BURAYI CAN_250KBPS YAPIN.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) 
  {
    Serial.println("MCP2515 Initialized Successfully!");
    CAN0.setMode(MCP_NORMAL); // Modülü normal dinleme moduna al
  } 
  else 
  {
    Serial.println("Error Initializing MCP2515...");
    while(1); // Hata varsa burada dur
  }

  Serial.println("MCP2515 Library CAN Sniffer");
  Serial.println("---------------------------------");
  Serial.println("ID | DLC | DATA");
}

void loop()
{
  // CAN hattında yeni bir mesaj var mı diye kontrol et
  if(CAN0.checkReceive() == CAN_MSGAVAIL)
  {
    // Mesajı oku
    CAN0.readMsgBuf(&rxId, &len, rxBuf);
    
    // 1. ID'yi Seri Port Ekranı'na yazdır (Hex formatında)
    Serial.print("0x");
    Serial.print(rxId, HEX);
    
    // 2. Veri Uzunluğunu (DLC) yazdır
    Serial.print(" | ");
    Serial.print(len);
    Serial.print(" | ");
    
    // 3. Verinin kendisini (DATA) bayt bayt yazdır
    for(int i = 0; i<len; i++)
    {
      if(rxBuf[i] < 0x10) Serial.print("0"); // Düzgün görünmesi için başına 0 ekle
      Serial.print(rxBuf[i], HEX);
      Serial.print(" ");
    }
    Serial.println(); // Bir sonraki mesaja geçmek için satır atla
  }
}