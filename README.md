# Household-Power-Cost-Calculator-C++
contains a C++ implementation of a household power consumption calculator. It models different types of devices, consumers, and their usage patterns in order to estimate energy consumption and associated costs.
The system allows users to input details about various devices (such as wattage and usage frequency) and calculate the total energy consumption in kilowatt-hours (kWh).

Key Components:
Device Class: The base class for all devices, holding a description and a link to the next device in a chain.
Consumer Class: A derived class that represents power-consuming devices, capturing wattage, usage frequency, and other details.
Immobile Class: A subclass of Consumer for devices that consume power in a standby mode (e.g., appliances with a low power draw when not in use).
Dynamic Memory Management: The program supports dynamic memory allocation and deallocation using pointers, ensuring efficient management of multiple devices.
Virtual Functions: Several virtual functions (like input, print, and annual_kWh) enable flexible behavior for different types of devices and consumers.
The goal of this project is to help users understand their household energy consumption and optimize their usage by tracking individual device power requirements.

Features:
Interactive input for device descriptions, wattage, and usage patterns.
Dynamic object creation for managing multiple devices in a linked list.
Static tracking of the total number of consumers.
Polymorphism for different device types with unique power consumption methods.
