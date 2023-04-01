# Atmega32_Drivers

This repository provides the complete Micro-Controller Abstraction Layer (MCAL) of the ATmega32 microcontroller of the AVR family, covering all built-in peripherals. A Hardware Abstraction Layer (HAL) accompanies, built upon the MCAL, and provides interfaces to many useful device modules.

Each driver in either the MCAL or HAL may consist of one or more of the following files:

DRIVER.h, the header file of a driver, providing an interface to the layer above in the hierarchy.
DRIVER.c, the source file of a driver (complements DRIVER.h).
DRIVER_Types.h, the type-definition file of a driver, containing all types specific to a driver.
DRIVER_Priv.h, the private header file of a driver, to be included by driver-associated files only.
DRIVER_Cfg.h, the configuration header file of a driver.
DRIVER_Cfg.c, the configuration source file of a driver (complements DRIVER_Cfg.h).
DRIVER_Reg.h or DRIVER_Map.h, the register-definition file of a driver, usually corresponding to the memory interface of a particular peripheral (relevant only in HAL).
