#include <SoftwareSerial.h>
#include <Servo.h> 

// Servos Da Mão
#define DedaoDobrarServo     2 // Branco/marrom
#define DedaoMovServo        3 // Branco/laranja
#define IndicadorServo       4 // laranja
#define MeioServo            5 // Azul
#define AnelarMindinhoServo  6 // Branco/verde
//Punho 
#define PunhoServo           7 // Branco/azul
// Servos da Luva 
#define TravaDedaoServo      8
#define TravaIndicadorServo  9
#define TravaMeioServo       10
#define TravaAnelarServo     11
#define TravaMindinhoServo   12
// FSR Da Mão
#define DedaoFSR           A0
#define IndicadorFSR       A1
#define MeioFSR            A2
#define AnelarFSR          A3
#define MindinhoFSR        A4
// Potenciometro da luva 
#define DedaoPOT           A8  
#define IndicadorPOT       A9  
#define MeioPOT            A10  
#define AnelarPOT          A11 
#define MindinhoPOT        A12 

#define PunhoGirarPOT      A13

  Servo myservoDedaoDobrar;
  Servo myservoDedaoMov;
  Servo myservoIndicador;
  Servo myservoMeio;
  Servo myservoAnelarMindinho;
  Servo myservoPunho;

  Servo myservoTravaDedao;
  Servo myservoTravaIndicador;
  Servo myservoTravaMeio;
  Servo myservoTravaAnelar;
  Servo myservoTravaMindinho; 

    int MAPServo = 0;
    int FSRReading = 0;
    int POTReading = 0;
    float Media = 0; 
    int pos = 0;
    int Ocorrencia =300;
  
void setup() {
    Serial.begin(9600);   
  myservoDedaoDobrar.attach(DedaoDobrarServo);
  myservoDedaoMov.attach(DedaoMovServo);
  myservoIndicador.attach(IndicadorServo);
  myservoMeio.attach(MeioServo);
  myservoAnelarMindinho.attach(AnelarMindinhoServo);
  myservoPunho.attach(PunhoServo);
  myservoTravaDedao.attach(TravaDedaoServo);
  myservoTravaIndicador.attach(TravaIndicadorServo);
  myservoTravaMeio.attach(TravaMeioServo);
  myservoTravaAnelar.attach(TravaAnelarServo);
  myservoTravaMindinho.attach(TravaMindinhoServo);

//  Iniciar();     
  
}

void loop() {     
    DedaoDobrarMov();
    TravaDedao();
    
    IndicadorDobrar();    
    TravaIndicador();
    
    MeioDobrar();
    TravaMeio();
    
    AnelarMindinhoDobrar();
    TravaAnelar();
    TravaMindinho();
    
    PunhoGirar();    
}


  void DedaoDobrarMov(){
    ZerarVar();
    for (int i = 1; i<=Ocorrencia;i++){
      POTReading = analogRead(DedaoPOT);       
      Media = (Media + POTReading);  
      delay(1);    
    }    
    POTReading = (Media/Ocorrencia);
    MAPServo = map(POTReading, 100, 600, 0, 180);    
    myservoDedaoDobrar.write(MAPServo);    
    MAPServo = ((MAPServo - 180)*0.5);   
    if (MAPServo<=90){
    //Serial.println(MAPServo); 
      myservoDedaoMov.write(MAPServo);
    }
    
}

  void IndicadorDobrar(){  
    ZerarVar(); 
    for (int i = 1; i<=Ocorrencia;i++){
      POTReading = analogRead(IndicadorPOT);       
      Media = (Media + POTReading);
      delay(1);     
    }      
    POTReading = (Media/Ocorrencia); 
    Serial.print("Analog reading = ");
    Serial.println(POTReading);   
    //POTReading = analogRead(IndicadorPOT);      
    MAPServo = map(POTReading, 1000, 600, 0, 180);
    Serial.println(MAPServo);   
    myservoIndicador.write(MAPServo);
    
}
  void MeioDobrar(){ 
    ZerarVar();
    for (int i = 1; i<=Ocorrencia;i++){
      POTReading = analogRead(MeioPOT);       
      Media = (Media + POTReading);
      delay(1);
    }           
    POTReading = (Media/Ocorrencia);
    //POTReading = analogRead(MeioPOT);           
    MAPServo = map(POTReading, 1000, 600, 0, 180);
    myservoMeio.write(MAPServo);
    
}
  void AnelarMindinhoDobrar(){  
    ZerarVar();           
    for (int i = 1; i<=Ocorrencia;i++){
      POTReading = analogRead(AnelarPOT);       
      Media = (Media + POTReading);
      delay(1);
    }         
    POTReading = (Media/Ocorrencia); 
    //POTReading = analogRead(AnelarPOT);         
    MAPServo = map(POTReading, 1000, 600, 0, 180);
    myservoAnelarMindinho.write(MAPServo);
    
}


//--------------------------------> Trava 
  void TravaDedao(){
    ZerarVar();
    FSRReading = analogRead(DedaoFSR);          
    MAPServo = map(FSRReading, 50, 850, 15, 35);
    myservoTravaDedao.write(MAPServo);
}
  void TravaIndicador(){   
    ZerarVar();  
    
    FSRReading = analogRead(IndicadorFSR); 
    MAPServo = map(FSRReading, 50, 850, 20, 35);
    myservoTravaIndicador.write(MAPServo);    
}
  void TravaMeio(){    
    ZerarVar(); 
    FSRReading = analogRead(MeioFSR);           
    MAPServo = map(FSRReading, 50, 850, 5, 30);
    myservoTravaMeio.write(MAPServo);    
}
  void TravaAnelar(){
    ZerarVar();      
    FSRReading = analogRead(AnelarFSR);         
    
    MAPServo = map(FSRReading, 50, 850, 5, 15);
    myservoTravaAnelar.write(MAPServo);    
}
  void TravaMindinho(){      
    ZerarVar();      
    FSRReading = analogRead(MindinhoFSR); 
    MAPServo = map(FSRReading, 50, 850, 165, 180);
    myservoTravaMindinho.write(MAPServo);
}
//--------------------------------> Punho
  void PunhoGirar(){
    ZerarVar();    

    for (int i = 1; i<=Ocorrencia;i++){
      POTReading = analogRead(PunhoGirarPOT);       
      Media = (Media + POTReading);
      delay(1);
    }         
    POTReading = (Media/Ocorrencia);         
    MAPServo = map(POTReading, 100, 1023, 0, 180);    
    myservoPunho.write(MAPServo);
}

  void ZerarVar(){
     MAPServo = 0;
     FSRReading = 0;
     POTReading = 0;
     Media = 0;
}


void Iniciar(){

  for(pos = 0; pos <= 180; pos += 1) 
  {         
    myservoDedaoDobrar.write(pos);
    myservoIndicador.write(pos);
    myservoMeio.write(pos);
    myservoAnelarMindinho.write(pos);
    if (pos<90){
      myservoDedaoMov.write(90-pos);
    }
    if (pos<110)
      myservoPunho.write(110-pos);
    //delay(5);                       
  } 


    for(pos = 180; pos >= 0; pos += 1) 
  {           
    myservoDedaoDobrar.write(pos);
    myservoIndicador.write(pos);
    myservoMeio.write(pos);
    myservoAnelarMindinho.write(pos);
    if (pos<90){
      myservoDedaoMov.write(90-pos);
    }
    if (pos<=110)
      myservoPunho.write(pos);
   // delay(5);                       
  } 

  myservoTravaDedao.write(15);
  myservoTravaIndicador.write(20);
  myservoTravaMeio.write(5);
  myservoTravaAnelar.write(5);
  myservoTravaMindinho.write(165);
}





