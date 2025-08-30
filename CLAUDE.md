# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

NanoEls is an electronic lead screw (ELS) controller for metal lathes with multiple hardware generations:
- **H1**: Basic Arduino Nano implementation
- **H2**: Arduino Nano with LCD
- **H4**: ESP32-S3 with 4-axis support and keypad
- **H5**: Latest ESP32-S3 with touch screen and PS2 keyboard (current focus)

## Hardware Constraints and Timing

- ISR max time: <10 µs in onAsyncTimer
- Step pulse low time: >=10 µs (see DLOW/DHIGH usage)
- PCNT filter values: ENCODER_FILTER=1 for spindle, MPG_PCNT_FILTER=10 for handwheels
- PCNT limits: PCNT_LIM=31000, PCNT_CLEAR=30000 (do not change without validation)
- Timing-critical sections protected by comments - require manual approval

## Development Commands

### Git Workflow
```bash
# Current main development branch is 'dev', not 'main'
git checkout dev
git pull origin dev
# Main branch used for PRs: 'main'
```

### Arduino IDE Setup
```bash
# Install required libraries via Arduino IDE Library Manager:
# - PS2KeyAdvanced
# - WebSockets
# - esp32 board package via Board Manager (add URL in preferences):
#   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

### Programming H5 Controller
1. Open `h5/h5.ino` in Arduino IDE
2. Select "ESP32S3 Dev Module" as device
3. Configure WiFi credentials in h5.ino lines 46-48
4. Upload via USB (use COM port, not USB port on ESP32)

### Screen Programming
1. Copy `h5/screen/h5.tft` to FAT32 MicroSD card (32GB max)
2. Insert card into Nextion display
3. Power on - wait for flash completion

## Code Architecture

### File Structure by Hardware Generation
- `h1/`: Arduino Nano basic ELS controller
- `h2/`: Arduino Nano with LCD interface  
- `h4/`: ESP32-S3 4-axis controller with keypad
- `h5/`: ESP32-S3 latest version with touch screen (main development focus)
- `personal/`: Private hardware configurations (git-ignored)
  - Custom PCB designs, case modifications, and personal configs
  - Copy any hardware version here for private modifications
- `docs/`: Safety and documentation files

### H5 Architecture (Main Development Focus)
- Single monolithic file: `h5/h5.ino`
- Hardware configuration constants at top (lines 1-100)
- Protected sections marked with `AI_DO_NOT_MODIFY` comments:
  - PCNT setup (line 2470)
  - PCNT/tasks attachment (line 2493) 
  - PCNT + timer ISR (line 2537)
  - Step timing loop (line 3168)
  - Spindle encoder handling (line 3547)
  - Main timing loop (line 3746)

### Key Functional Areas
- **Motion Control**: Real-time stepper control with microsecond timing
- **G-Code Processing**: CNC command interpretation and execution
- **Web Interface**: WiFi-enabled remote control and file upload
- **Threading Operations**: Automatic thread cutting with multiple passes
- **Safety Systems**: Soft limits, emergency stops, hardware interlocks

## Editing Policy

### Safe to Modify
- Configuration constants (top of h5.ino)
- UI text and validation logic
- G-code parsing (non-timing-critical parts)
- Web interface HTML/CSS
- Calibration and setup functions

### Requires Manual Approval
- Interrupt service routines (ISRs): onAsyncTimer (line ~2508)
- PCNT setup: startPulseCounter (line ~2443)
- Real-time control loops
- Hardware register manipulations
- Timing-critical motion control: step pulse generation loops
- Spindle encoder handling in main loop

### Hardware Configuration Constants
Key parameters in h5.ino that may need adjustment:
- `ENCODER_PPR`: Spindle encoder resolution (line 6)
- `MOTOR_STEPS_Z/X/Y`: Stepper motor steps per revolution
- `SCREW_Z/X/Y_DU`: Lead screw pitch in deci-microns (10^-7 meter)
- `INVERT_Z/X/Y`: Direction inversions for axes
- `INVERT_Z/X/Y_STEP`: Step pin inversion for level shifting
- `MPG_SCALE_DIVISOR`: Handwheel sensitivity (lower = more movement)
- `MPG_PCNT_FILTER`: Dedicated filter for handwheel PCNT units
- WiFi credentials (lines 46-48)

## Testing and Validation

### Hardware Testing
- Verify encoder direction: use Win key to show angle, rotate chuck forward (angle should increase)
- Test motor directions: use arrow keys for movement, verify correct direction
- Check emergency stops and limit switches
- Validate threading accuracy with test cuts

### Timing Validation
- Monitor serial output during operation
- Use oscilloscope to verify step pulse timing
- Ensure ISR execution stays under 10µs
- Test at various spindle RPMs

## Safety Considerations

- All hardware modifications require manual approval
- Test extensively before using on valuable workpieces  
- Validate limit switch operation before automated modes
- Verify emergency stop functionality
- Never bypass safety interlocks in code
- See `docs/safety.md` for detailed safety requirements:
  - E-stop handling: hardware latch + software ESTOP paths
  - Soft limits: enforce before any automated motion
  - On errors: disable steppers, stop async timer, show error

## Web Interface and G-Code

- Access via browser at controller's IP address (shown with Win key)
- Upload G-code files through web interface
- Generate G-code at <https://kachurovskiy.com/lathecode/>
- Web interface allows remote monitoring and control

## Common Issues

- Upload failures: Check USB cable and use COM port (not USB port on ESP32)
- Wrong motor direction: Modify `INVERT_Z` or `INVERT_X` constants
- Encoder direction: Swap ENCA/ENCB wires in terminal
- Screen not updating: Verify 4-wire connection (RX-TX, TX-RX)
