
#define CE_PIN      1
#define CSN_PIN     2

#define SOFT_SPI
#define SOFT_SPI_MISO_PIN   3
#define SOFT_SPI_MOSI_PIN   4
#define SOFT_SPI_SCK_PIN    5

void radio_init();
void radio_loop();
void radio_write(int *data, int len);