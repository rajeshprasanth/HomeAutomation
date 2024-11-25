# Arduino Relay Timer with DS1307 RTC

This project demonstrates how to control a relay using an Arduino Nano and a DS1307 RTC module. The relay is triggered at a specific time every day and remains active for a predefined duration (30 seconds in this case). The current time, target time, and relay status are displayed in the Serial Monitor.

## Features
- Turns on a relay at a specified time.
- Keeps the relay active for a configurable duration (default: 30 seconds).
- Uses a DS1307 Real-Time Clock (RTC) module to keep track of time.
- Displays target time, current time, and relay status on the Serial Monitor.

## Components Required
1. **Arduino Nano** (or any compatible board)
2. **DS1307 RTC Module**
3. **Relay Module**
4. Jumper wires
5. Breadboard (optional)

## Circuit Diagram
### Connections:
| DS1307 RTC Module | Arduino Nano       |
|--------------------|--------------------|
| SDA               | A4                |
| SCL               | A5                |
| VCC               | 5V                |
| GND               | GND               |

| Relay Module | Arduino Nano |
|--------------|--------------|
| IN           | D8           |
| VCC          | 5V           |
| GND          | GND          |

## How It Works
1. At the specified target time (default: 9:00:00 AM), the relay is turned on.
2. The relay remains on for a predefined hold time (`holdTime = 30000 ms` or 30 seconds).
3. The relay is turned off automatically after the hold time elapses.
4. The target time, current time, and relay status (`ACTIVE` or `INACTIVE`) are printed to the Serial Monitor.

## Serial Monitor Output
The output in the Serial Monitor follows this format:

```bash
Target Time: HH:MM:SS || Current Time: HH:MM:SS || Trigger Status: ACTIVE/INACTIVE
```
## Example Output:

```bash
Target Time: 09:00:00 || Current Time: 08:59:59 || Trigger Status: INACTIVE
Target Time: 09:00:00 || Current Time: 09:00:00 || Trigger Status: ACTIVE
Target Time: 09:00:00 || Current Time: 09:00:30 || Trigger Status: INACTIVE
```
## Setup Instructions
1. Connect the DS1307 RTC module and relay module to the Arduino Nano as per the circuit diagram.
2. Upload the provided Arduino sketch to the board.
3. Open the Serial Monitor at 9600 baud to observe the output.
4. If the RTC module is not set to the correct time, uncomment the rtc.adjust() line in the code to set the RTC time to the computer's compile time.

## Customization

- **Target Time**: Modify `targetHour`, `targetMinute`, and `targetSecond` variables in the code to set your desired trigger time.
- **Hold Time**: Change the value of the `holdTime` constant (in milliseconds) to adjust how long the relay stays active.

## Dependencies

- **RTClib Library**: Ensure you have the `RTClib` library installed in your Arduino IDE.

### Install the Library

1. Open Arduino IDE.
2. Go to **Sketch > Include Library > Manage Libraries**.
3. Search for `RTClib` and click **Install**.

## License

This project is open-source and distributed under the **MIT License**. Feel free to use and modify it.

