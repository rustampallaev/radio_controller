#define RADIO_CLIENT    true

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN  7
#define CSN_PIN  8 

#define PIPE        0x1234567890LL
#define DATA_LEN    50

RF24 radio(CE_PIN, CSN_PIN);
int rx_data[DATA_LEN];
int tx_data[DATA_LEN];



void radio_init()
{
#ifdef SOFTSPI
    #ifdef SOFT_SPI_MISO_PIN
        Serial.println("Start");
    #endif
#endif
    radio.begin();                                        // Инициируем работу nRF24L01+
    radio.setChannel(5);                                  // Указываем канал передачи данных (от 0 до 127), 5 - значит передача данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
    radio.setDataRate(RF24_1MBPS);                        // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
    radio.setPALevel(RF24_PA_HIGH);                       // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
#if RADIO_CLIENT
    radio.openWritingPipe(PIPE);
#else
    radio.openReadingPipe(1, PIPE);                       // Открываем 1 трубу с идентификатором 0x1234567890 для приема данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
    radio.startListening();
#endif
}

void radio_write(int *data, int len)
{
    radio.write(data, len);                     // отправляем данные из массива data указывая сколько байт массива мы хотим отправить. Отправить данные можно с проверкой их доставки: if( radio.write(&data, sizeof(data)) ){данные приняты приёмником;}else{данные не приняты приёмником;}
}

void radio_loop()
{
#if RADIO_CLIENT
#else
    if(radio.available()){                                // Если в буфере имеются принятые данные
        radio.read(&data, sizeof(data));                  // Читаем данные в массив data и указываем сколько байт читать
        dispLED.print(data[0]);                           // Выводим показания Trema слайдера на индикатор
        myservo.write(map(data[1],0,1023,0,180));         // Поворачиваем сервопривод на угол заданный Trema потенциометром
    }
#endif
}