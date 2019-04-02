#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // Подключение библиотеки
//#include <LiquidCrystal_PCF8574.h> // Подключение альтернативной библиотеки
#include <OneWire.h>
#include <DallasTemperature.h>
 
// Пин Arduino куда подключен датчик
#define ONE_WIRE_BUS 4
 
// Объявляем переменные
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
 
// тут будет хранится адрес нашего датчика. Каждый DS18B20 имеет свой уникальный адрес, зашитый на заводе
DeviceAddress insideThermometer;
LiquidCrystal_I2C lcd(0x3F,16,2); // Указываем I2C адрес (наиболее распространенное значение), а также параметры экрана (в случае LCD 1602 - 2 строки по 16 символов в каждой 
//LiquidCrystal_PCF8574 lcd(0x27); // Вариант для библиотеки PCF8574 
String str[8];  
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();                 // Подключение подсветки

  Serial.print(sensors.getDeviceCount(), DEC);
 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");  
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Не найден адрес датчика 0");  
  // устанавливаем разрешение датчика на 9 бит. Можно попробовать 10 поставить. Эта штука отвечает за точность показаний. Чем выше точность тем меньше скорость получения температуры.
  sensors.setResolution(insideThermometer, 9);
  Serial.print(sensors.getResolution(insideThermometer), DEC); 
}


void printTemperature(DeviceAddress deviceAddress)
{
  // вариант 1 - медленнее
  //Serial.print("Temp C: ");
  //Serial.print(sensors.getTempC(deviceAddress)); // в цельсиях
  //Serial.print(" Temp F: ");
  //Serial.print(sensors.getTempF(deviceAddress)); // в фаренгейтах. причем чтобы получить температуру в фаренгейтах мы делаем второй запрос к датчику.
 
  // вариант 2 - быстрее
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.println(DallasTemperature::toFahrenheit(tempC));
  lcd.setCursor(0,1);              // Установка курсора в начало первой строки
  lcd.print("temp");       // Набор текста на первой строке
  lcd.setCursor(11,1);              // Установка курсора в начало первой строки
  lcd.print(tempC);       // Набор текста на первой строке
}

void writeSensorValue(DeviceAddress deviceAddress) {
  // Выводим отладочную информацию
  Serial.print(">> Addr: ");
  printAddress(deviceAddress);
  // Формируем пакет для передачи из 10 байт (8 байт - адрес, 2 байта - значение)
  int msg[8];
  // Заполняем первые 8 байт пакета адресом датчика
  for(int k = 0; k < 8; k++)
    msg[k] = deviceAddress[k];
  for(int i = 0; i < 8; i++)
     str[i] = String(msg[i], HEX);
  lcd.setCursor(0,0);
  for(int i = 0; i < 8; i++)
      lcd.print(str[i]);
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);  
  }
}


void loop() {
  Serial.print("Получаем температуру...");
  sensors.requestTemperatures(); // Отправка команды на получение температуры
  Serial.println("готово");
  printTemperature(insideThermometer);
  delay(1000);
  writeSensorValue(insideThermometer);
}
