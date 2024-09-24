# FdF Remastered

# FdF Project - Enhanced Version

This repository contains the enhanced version of the **FdF** project, a 3D wireframe viewer originally developed as part of the 42 school curriculum. The project was picked up and extended with additional features to explore the capabilities of graphics programming using the MiniLibX library. This README provides an overview of the project, including the original objectives, technical details, and new enhancements. </br></br>

The FdF project, short for "Fil de Fer" (French for "Wireframe"), is a graphics programming exercise aimed at representing 3D landscapes as wireframe models. The project involves reading 2D coordinate data from a file and using it to draw a 3D representation in an isometric view. We picked up the original project, added several new features, and made a presentation to showcase these enhancements.

## Project Objective

The primary objective of the project is to create a wireframe model representation of a 3D landscape by linking various points with line segments (edges). This involves converting 2D coordinate data into a 3D visual model using graphics programming techniques.

## Project Overview

### Problems to Solve

1. **Read Input Data:**
   - Read numbers from a file and convert them into usable data for rendering.
2. **Window Management:**
   - Create and manage a new window using the MiniLibX library.
3. **Projection Calculations:**
   - Use trigonometry and projection algorithms to map 3D points into a 2D view.
4. **Drawing Lines:**
   - Implement an algorithm to draw line segments between points to create the wireframe.

### Solution Summary

- **Read Data from text file:** Parse the input file to create an array of points.
- **3D Projection:** Convert the array of points into isometric coordinates.
- **Connect the Dots:** Implemented an algorithm to draw lines between consecutive points in the array.
- **Additional Projections:** Support for alternative projection modes beyond isometric.
- **Zoom and Translation:** Implemented zoom functionality and model translation for better navigation.
- **Model Rotation:** Rotate the model along different axes for a dynamic view.
- **Color Gradients:** Implemented different color schemes based on altitude or user preference.

To see more information on the project subject and original objectives, check this [FdF_repository](https://github.com/mjorgecruz/42_fdf).

## Additional Enhancements

Besides the 

1. **Standalone Application:**
   - Packaged as a standalone app for easy execution.
  
<img src="https://github.com/mjorgecruz/42_FdF_updated/blob/main/fdf0.gif" align="center"/>

2. **Selector Screen:**
   - Added a screen to select different maps or projection modes.
3. **Control Panel:**
   - A control panel to adjust various parameters like colors, zoom, and rotation.
4. **Color Adjustments:**
   - Manual color adjustments during execution for a customized view.
5. **Projections with a Twist:**
   - Added unique projection styles for a more creative visualization.
<img src="https://github.com/mjorgecruz/42_FdF_updated/blob/main/fdf3.gif" align="center"/>

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/fdf-enhanced.git
    cd fdf-enhanced
    ```

2. Compile the project using the provided Makefile:

    ```bash
    make
    ```

This will create the `fdf` executable in the root directory.

## Usage

Run the program with an `.fdf` file as an argument:

```bash
./fdf path/to/map.fdf
```

You can find sample `.fdf` files in the `maps` directory or create your own.

## Controls

- **Arrow Keys:** Move the map (pan).
- **+ / -:** Zoom in and out.
- **W / A / S / D:** Rotate the map around the x and y axes.
- **Q / E:** Rotate the map around the z-axis.
- **1 / 2 / 3:** Switch between different projection modes.
- **R:** Reset the view.
- **ESC:** Exit the program.


## Credits

- **Jorge Cruz:**
- **Rui Pires:**






<img src="https://github.com/mjorgecruz/42_FdF_updated/blob/main/fdf1.gif" align="center"/>

<p align="center">
	<b><i>A simplified 3D graphic representation of a relief landscape.</i></b><br>
</p>


<img src="https://github.com/Rui-Pedro-Pires/FdF/blob/main/presentation/images/france_map.png" width=600 height=400 align="center"/>

## How to run
1. Clone repository
```bash
git clone git@github.com:Rui-Pedro-Pires/FdF.git
```

To compile the program ↙️

```bash
$ cd FdF && make
```
<img src="https://github.com/Rui-Pedro-Pires/FdF/blob/main/presentation/gifs/GIFMaker_me.gif" align="center"/>

To launch the program
```bash
$ ./fdf
```
