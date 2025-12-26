idf_component_register(SRCS "main.c" 
    INCLUDE_DIRS "." "./components" "./components/games" "./components/games/space_invaders" 
    REQUIRES 
        bootloader_support 
        esp_driver_i2c 
        esp_driver_gpio 
        esp_hw_support 
        esp_system
)
