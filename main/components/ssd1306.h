#ifndef SSD1306_H
#define SSD1306_H

#include "driver/i2c_master.h"
#include "esp_log.h"

#define CLAMP(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#define I2C_PORT            0
#define SDA_GPIO            21
#define SCL_GPIO            22
#define SSD1306_ADDR        0x3C

// SSD1306 Commands
#define SSD1306_CMD_DISPLAY_OFF 0xAE
#define SSD1306_CMD_DISPLAY_ON  0xAF
#define SSD1306_CMD_CHARGE_PUMP 0x8D

static i2c_master_dev_handle_t dev_handle;

uint8_t vram[1024] __attribute__((weak));

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
  ssd1306_send_command(0x20); 
  ssd1306_send_command(0x00); 

  ssd1306_send_command(0xA1);
  ssd1306_send_command(0xC8);
  
  ssd1306_send_command(0x21); 
  ssd1306_send_command(0);   
  ssd1306_send_command(127); 

  ssd1306_send_command(0x22); 
  ssd1306_send_command(0);    
  ssd1306_send_command(7);
  ssd1306_send_command(SSD1306_CMD_CHARGE_PUMP);
  ssd1306_send_command(0x14); 
  ssd1306_send_command(SSD1306_CMD_DISPLAY_ON);
}

static inline void ssd1306_clear(void)
{
  for(int i = 0; i < 1024; i++)
  { vram[i] = 0x00; }
}

static inline void ssd1306_draw_pixel(uint8_t x, uint8_t y, bool on)
{ 
  if(x >= 128 || y >= 64) return;

  if(on)
  { vram[x + (y / 8) * 128] |= (1 << (y % 8)); }
  else
  { vram[x + (y / 8) * 128] &= ~(1 << (y % 8)); }
}

static inline void ssd1306_update(void)
{
  // set column addr range to (0 to 127)
  ssd1306_send_command(0x21); ssd1306_send_command(0); ssd1306_send_command(127);

  // set page addr range (0 to 7)
  ssd1306_send_command(0x22); ssd1306_send_command(0); ssd1306_send_command(7);

  uint8_t data_pkg[1025];
  data_pkg[0] = 0x40;
  for(int i = 0; i < 1024; i++)
  { data_pkg[i + 1] = vram[i]; }

  i2c_master_transmit(dev_handle, data_pkg, sizeof(data_pkg), -1);
}

static inline void draw_sprite_v(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *bitmap)
{
  int bytes_per_col = (h + 7) / 8;
  
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
		  int byte_index = i * bytes_per_col + (j / 8);
		  int bit_index = j % 8; 
			if(bitmap[byte_index] & (1 << bit_index))
		  { ssd1306_draw_pixel(x + i, y + j, true); }
		}
	}
}

static inline void draw_sprite_h(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *bitmap)
{
  int bytes_per_row = (w + 7) / 8;
  
  for(int i = 0; i < h; i++)
  {
    for(int j = 0; j < w; j++)
    {
      int byte_index = i * bytes_per_row + j / 8;
      int bit_index = 7 - (j % 8);
      if(bitmap[byte_index] & (1 << bit_index))
      { ssd1306_draw_pixel(x + j, y + i, true); }
    }
  }
}

#endif
