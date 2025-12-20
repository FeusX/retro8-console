#ifndef SSD1306_H
#define SSD1306_H

#include "driver/i2c_master.h"
#include "esp_log.h"

#define I2C_PORT            0
#define SDA_GPIO            21
#define SCL_GPIO            22
#define SSD1306_ADDR        0x3C

// SSD1306 Commands
#define SSD1306_CMD_DISPLAY_OFF 0xAE
#define SSD1306_CMD_DISPLAY_ON  0xAF
#define SSD1306_CMD_CHARGE_PUMP 0x8D

static i2c_master_dev_handle_t dev_handle;

static inline esp_err_t ssd1306_send_command(uint8_t cmd)
{
  uint8_t buffer[2] = {0x00, cmd};
  return i2c_master_transmit(dev_handle, buffer, sizeof(buffer), -1);
}

static inline void ssd1306_init(void)
{
  i2c_master_bus_config_t bus_config = {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .i2c_port = I2C_PORT,
    .scl_io_num = SCL_GPIO,
    .sda_io_num = SDA_GPIO,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
  };
  i2c_master_bus_handle_t bus_handle;
  ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));

  i2c_device_config_t dev_config = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = SSD1306_ADDR,
    .scl_speed_hz = 400000,
  };
  ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_config, &dev_handle));

  // wake the screen
  ssd1306_send_command(SSD1306_CMD_DISPLAY_OFF);
  ssd1306_send_command(SSD1306_CMD_CHARGE_PUMP);
  ssd1306_send_command(0x14); 
  ssd1306_send_command(SSD1306_CMD_DISPLAY_ON);
}

#endif
