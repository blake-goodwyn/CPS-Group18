# CPS-Group18

## Overview

This is a repository for all development data regarding Group 18's work toward the Cyberphysical Systems module. The scope of this project is a design sprint aimed at developing a scaled, soft-shelled Mars habitat structure that adjusts to aerodynamic shapes based on extreme wind patterns.  

The project team consists of:
- Abigail Hoover
- Richard Alexandre
- Richard "Blake" Goodwyn

## Mechanical Overview 
### (Refer to /cad folder)

![Top Level Assembly](https://github.com/blake-goodwyn/CPS-Group18/blob/main/images/tla.png)

The mechanical design of the structure consists of six mechanical arms spaced equally about the structure. Each one consists of a carefully developed 4-bar linkage system driven by a servo arm. The servo arm has a roller that is situated into a slot in a driving link.

## Software Overview
### (Refer to arduino_code)

Our software design utilises two scripts and a machine learning model: 
- an Arduino script (/arduino_code/MASTER_CODE/master_code) that handles motion of servos, packaging sensor inputs for the Wekinator module, 
and an interprets the feedback from the machine learning module
- a Processing script (machine_learning/master_processing_script/master_rx_tx_script) that takes in the analog sensor values from the Serial port and passes them to a Wekinator module
- a Wekinator machine learning module (machine_learning/final_ML_model/Finalized_ASH_ML_Model) that takes in 2 inputs in the form of float values and gives one integer output that denotes the class output of the model
