# CPS-Group18

## Overview

This is a repository for all development data regarding Group 18's work toward the Cyberphysical Systems module of the Imperial College London's Innovation Design Engineering (IDE) programme. The scope of this project is a 3-week design sprint aimed at a project of the students' choosing - in this case, developing a scale-model, soft-shelled Mars habitat structure that adjusts to aerodynamic shapes based on extreme wind patterns.  

The project team consists of:
- Abigail Hoover
- Richard Alexandre
- Richard "Blake" Goodwyn

## Working with these files

It is suggested that, due to the mechanism of how SolidWorks files are saved, anyone looking to work with the CAD files located in this repo either:
- place this repo at the C:/ location of their local machine
- open and re-save all SolidWorks once their environment has located the new file directory

This is an unfortunate side effect of mixing SolidWorks and Git, whereas an SVN system may be more appropriate. However, due to the fast-paced nature of this project and mixed media of its digital assets, GitHub seemed a reasonable solution for tracking development and hosting a final set of files.

## Mechanical Overview 
### (Refer to /cad folder)

![Top Level Assembly](https://github.com/blake-goodwyn/CPS-Group18/blob/main/images/tla.png)

The mechanical design of the structure consists of six mechanical arms spaced equally about the structure. Each one consists of a carefully developed 4-bar linkage system driven by a servo arm. The servo arm has a roller that is situated into a slot in a driving link and drives the tip of each arm up-and-down given the servo's position.

The mechanical design in this repo utilizes a top-down design ideology call **master modeling** to form all of the parts. Thus, the mechanical design is driven by three central files:
- *master.prt*, which contains critical assembly level design information like the structure's height and footprint
- *_submaster_linkage_module_4bar.prt*, which contains the critical design information for the assembly of each linkage module
- *_submaster_wind_vane.prt*, which contains the critical design information for the wind vane sub-assembly.

For more information on master modeling, you can refer to [this article from GoEngineer](https://www.goengineer.com/blog/solidworks-tutorial-master-modeling-technique).

## Software Overview
### (Refer to arduino_code)

Our software design utilises two core scripts in addition to a machine learning model to achieve its function: 
- an Arduino script (/arduino_code/MASTER_CODE/master_code) that handles motion of servos, packaging sensor inputs for the Wekinator module, 
and an interprets the feedback from the machine learning module
- a Processing script (machine_learning/master_processing_script/master_rx_tx_script) that takes in the analog sensor values from the Serial port and passes them to a Wekinator module
- a Wekinator machine learning module (machine_learning/final_ML_model/Finalized_ASH_ML_Model) that takes in 2 inputs in the form of float values and gives one integer output that denotes the class output of the model
