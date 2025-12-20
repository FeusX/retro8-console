#ifndef SSD1306_H
#define SSD1306_H

#include "driver/i2c.h"

// HARDWARE ADDRESSES
#define I2C0_BASE_ADDR 0x3FF53000
#define I2C_DATA_FIFO_REG (I2C0_BASE_ADDR + 0x001C)

// CONFIG ADDRESSES
#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_SDA_IO 21
#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_FREQ_HZ 400000
#define SSD1306_I2C_ADDR 0x3C

// COMMAND ADDRESSES
#define SSD1306_CONTROL_BYTE_CMD 0x00
#define SSD1306_CONTROL_BYTE_DATA 0x40
#define SSD1306_CMD_DISPLAY_OFF 0xAE
#define SSD1306_CMD_DISPLAY_ON 0xAF
#define SSD1306_CMD_CHARGE_PUMP 0x8D

static inline void ssd1306_init(void)
{
  i2c_config_t conf = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = I2C_MASTER_SDA_IO,
    .scl_io_num = I2C_MASTER_SCL_IO,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .sda_pullup_en = GPIO_PULLUP_ENABLE
  };

  i2c_param_config(I2C_MASTER_NUM, &conf);
  i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);

  // wake the screen
  ssd1306_send_command(SSD1306_CMD_DISPLAY_OFF);
  ssd1306_send_command(SSD1306_CMD_CHARGE_PUMP);
  ssd1306_send_command(0x14); // magic byte for charge pump
  ssd1306_send_command(SSD1306_CMD_DISPLAY_ON);
}

static inline esp_err_t ssd1306_send_command(uint8_t command)
{
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (SSD1306_I2C_ADDR << 1) | I2C_MASTER_WRITE, true);
  i2c_master_write_byte(cmd, SSD1306_CONTROL_BYTE_CMD, true);
  i2c_master_write_byte(cmd, command, true);
  i2c_master_stop(cmd);
  
  esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(10));
  i2c_cmd_link_delete(cmd);
  return ret;
}

#endif
