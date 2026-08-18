# Pafik RC car #

This a repository of project realizing a pretty bold idea of making semi-automotive RC car named "Pafik". 


The general initial assumption is to allow the vehicle to work in two separate modes:
- *MANUAL* - when Pafik is being steered using dedicated attachment to client's laptop;
  this is mode is based on radio comunication between two Arduino boards: one in the 'attachment' and another in vehicle, which will be responsible for physical layer managment of Pafik (motors, servos)
- *AUTO* - when car is under controll of decision layer located at Raspberry Pi 5 board; this board will combine tasks of sensor data interpreting and testing decision-making algorithms including these based on simple AI models and lidar data

## LOGBOOK ##
*18.08.2026* - official start, estabilishing GitHub repo
