# Innoguide: The Autonomous Humanoid Guide Robot

![Innoguide Prototype](./assets/innoguide_prototype.jpg)  
*A picture of the Innoguide robot prototype.*

---

## Overview
**Innoguide** is an autonomous humanoid guide robot developed at the **Centre for Innovation (CFI), IIT Madras**.  
This repository documents the project’s progress and my contributions during **May 2023 – April 2024**.

The primary goal of Innoguide is to serve as an **interactive guide** within the CFI building, demonstrating advancements in **assistive technology** and **autonomous navigation**.

---

## Key Features
- **Autonomous Navigation** – Designed to navigate indoor environments and guide visitors.
- **Humanoid Design** – Built with a humanoid form factor for intuitive human interaction.
- **Robust Chassis** – Custom-designed aluminum skeleton frame, validated with **Ansys simulations**.
- **Wireless Manual Control** – Operable from up to **50 meters** away via a joystick controller using ESP32 peer-to-peer protocol.
- **Integrated Sensor Suite** – Managed by **NVIDIA Jetson Nano** for real-time control and decision-making.

---

## Technologies & Tools Used
- **CAD/CAM**: Fusion 360, TinkerCAD  
- **Simulation**: Ansys  
- **Hardware**: Jetson Nano, Arduino, ESP32, Cytron Motor Drivers  
- **Software & Frameworks**: ROS (Robot Operating System)  
- **Prototyping**: 3D Printing (PLA), Custom PCB Design  

---

## My Contributions
As a **Project member** of the Innoguide project, I was actively involved in **mechanical design, electronics design & integration, and control systems development**.

### Mechanical Design & Fabrication
- Designed the **aluminum chassis** and performed **strength analysis** in Ansys.  
- Created and **3D printed** the robot’s outer shell.  

![Chassis & 3D Printed Parts](./assets/robot_chassis.jpg)

---

### Electronics & Circuitry
- Designed the **complete electrical circuitry**, integrating sensors and core components.  
- Implemented **power isolation techniques** for safe handling of 12V and 5V supplies.  
- Designed a custom **PWM Switcher PCB** using Multiplexers (MUX) to toggle motor control between Jetson Nano (autonomous mode) and ESP32 (manual mode).  

![Custom PWM Switcher PCB](./assets/pwm_switcher_pcb.jpg)

---

### Control Systems
- Developed **motor control** using Cytron motor drivers and Arduino-generated PWM signals.  
- Built a **wireless remote control system** using ESP32 modules, enabling manual operation within a 50m range.  
- Integrated all components with **ROS**, developing modular ROS nodes for real-time control.  

---

## Project Milestones
- **Successful Deployment** – Showcased at **CFI Open House 2024**.  
- **Media Recognition** – Featured in *The Hindu* newspaper for innovation in assistive technology.  
- [Read the article here]([https://www.thehindu.com/your-article-link](https://www.thehindu.com/news/national/tamil-nadu/iit-m-showcases-an-array-of-innovative-technology/article67910616.ece))
![Innoguide at CFI Open House](./assets/innoguide_openhouse.jpg)

---


## Future Work
- Upgrading from **Jetson Nano → Jetson Orin Nano** for enhanced AI capabilities.  
- Implementing **stereo camera + LIDAR** for advanced SLAM and indoor navigation.  
- Expanding interaction capabilities with **speech recognition and dialogue systems**.  

---

## Acknowledgements
This project was developed at the **Centre for Innovation (CFI), IIT Madras**, with support from mentors, peers, and the student community.  

---

## License
This repository is licensed under the MIT License. See [LICENSE](./LICENSE) for details.
