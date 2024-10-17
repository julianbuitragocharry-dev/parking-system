# Smart Parking System

This project builds a smart parking system using **MATLAB** for license plate recognition and **App Inventor** for management. The system integrates **Arduino** to automate operations via a mobile app, allowing real-time control and monitoring of parking spaces.

## Features
- **License Plate Processing**: Utilizes MATLAB for real-time detection and processing of license plates.
- **Mobile App Management**: Developed with App Inventor, enabling users to manage parking operations and view parking status through a mobile interface.
- **Automation**: Arduino automates the entry and exit of vehicles, controlling barriers and monitoring availability of spaces.
  
## Getting Started

1. **Clone the repository**:
   Clone the project to your local machine using the following command:
   ```bash
   git clone https://github.com/julianbuitragocharry-dev/parking-system.git
   ```
   
2. **Ensure PlatformIO is installed in Visual Studio Code**:
   Make sure you have PlatformIO installed as an extension in Visual Studio Code. If you need to install it, follow the [PlatformIO installation guide](https://docs.platformio.org/en/latest/integration/ide/vscode.html).

3. **Open the project**:
   Open the project folder in Visual Studio Code, ensuring that PlatformIO is available.

4. **Connect your hardware**:
   Connect your Arduino UNO to your computer.

5. **Build and upload the code**:
   Compile and upload the code.
   
6. **Run the project**:
   Once uploaded, the Arduino will start executing the parking system logic, interfacing with the sensors and App Inventor for parking management.

7. **Access the mobile app**:
   Use the App Inventor app on your mobile device to manage parking operations, such as registering vehicles and monitoring parking status.

## Requirements
- **Arduino IDE** or **PlatformIO** in Visual Studio Code
- **MATLAB** for license plate detection
- **MIT App Inventor** for mobile app management
- **Ultrasonic sensors**, **servo motors**, and **Bluetooth module** for automation
