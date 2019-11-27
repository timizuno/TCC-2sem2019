//Inclusão das bibliotecas para funcionamento, respectivamente, do sensor de corrente, do LCD e do sensor de voltagem
#include "ACS712.h"
#include <LiquidCrystal.h>
#include "EmonLib.h" 

//sensor de corrente ligado na porta A2, conforme esquemático
ACS712 sensor(ACS712_30A,A2);
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  //iniciando a tela LCD do arduíno
  lcd.begin(16,2);
  //É necessário calibrar o sensor antes de usar a primeira vez com o método abaixo
  Serial.begin(9600);
  sensor.calibrate();
}
 
void loop() {

  //a cada 2 segundos, os sensores irão ler qual a medida de voltagem e corrente
  delay(2000);
  //função para medir corrente
  float I = sensor.getCurrentAC(70);
  //função para medir tensão, convertendo os valores de acordo com nossas contas
  float value = analogRead(A0);
  float V = value * (12.0/415.0);

  //aparecer na tela quais os valores de tensão e corrente em todos os casos, mas cada situação aparece uma mensagem diferente conforme as condições abaixo.

  //condição errada de tensão
  if(I<0.8 && V>0.5 && V<8 || V>11){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TENSAO ERRADA");
  lcd.setCursor(0,2);
  lcd.print(String("I=") + I + "A");
  lcd.setCursor(8,2);
  lcd.print(String("V=") + V + "V");
  }

  //condição errada de corrente
  else if(I>0.8 && V>8.0){
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CORRENTE ALTA");
  lcd.setCursor(0,2);
  lcd.print(String("I=") + I + "A");
  lcd.setCursor(8,2);
  lcd.print(String("V=") + V + "V");
  }

  //condição errada de tensão e corrente
  else if(I>0.8 && V<8.0 || V>11.0){
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ERRO DE MEDIDAS“);
  lcd.setCursor(0,2);
  lcd.print(String("I=") + I + "A");
  lcd.setCursor(8,2);
  lcd.print(String("V=") + V + "V");
  }

  //condição inicial para que não apareça as mensagens de erro acima, colocando um valor mínimo
  else if(I<=0.1 && V <=0.5){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MEDICAO");
  lcd.setCursor(0,2);
  lcd.print(String("I=") + I + "A");
  lcd.setCursor(8,2);
  lcd.print(String("V=") + V + "V");
  }

  //condições corretas de medição
  else{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MEDICAO");
  lcd.setCursor(0,2);
  lcd.print(String("I=") + I + "A");
  lcd.setCursor(8,2);
  lcd.print(String("V=") + V + "V");
  }
}
