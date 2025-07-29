# NiftyScallop

NiftyScallop is an ImGui application that demonstrates a simple graphical user interface using the ImGui library and GLFW for window management.

## Project Structure

```
NiftyScallop
├── src
│   ├── main.cpp
├── CMakeLists.txt
└── README.md
```

## Requirements

- CMake (version 3.10 or higher)
- A C++ compiler that supports C++11 or higher
- GLFW library
- ImGui library

## Building the Project

1. Clone the repository or download the project files.
2. Open a terminal and navigate to the project directory.
3. Create a build directory:
   ```
   mkdir build
   cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Build the project:
   ```
   cmake --build .
   ```

## Running the Application

After building the project, you can run the application from the build directory:
```
./NiftyScallop
```

## License

This project is licensed under the MIT License. See the LICENSE file for details.