# Hostel Room Simulation Using OpenGL

This project is a hostel room simulation developed using OpenGL. It visualizes a hostel room environment, demonstrating the use of graphics rendering using the OpenGL library.

## Dependencies

The project uses the following libraries:

- `GL/glut.h`
- `stdlib.h`
- `stdio.h`
- `iostream`

## Running the Code

### Prerequisites
Make sure you have OpenGL and its related libraries installed on your system. If not, install them using:

```bash
sudo apt-get update
sudo apt-get install freeglut3-dev
Compile and Run
To compile the code on a Linux system (e.g., Ubuntu), navigate to the project directory in the terminal and use the following commands
g++ main.cpp -o main -lglut -lGL -lGLU
This command compiles the main.cpp file and creates an executable named main with the necessary OpenGL libraries linked.

To run the compiled code, use the following command:
./main
