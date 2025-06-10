import serial

def validate_rgb_input(rgb_input):
    """Validate the RGB input to ensure it follows the format '### ### ###'."""
    if len(rgb_input) != 11:
        return False
    parts = rgb_input.split()
    if len(parts) != 3:
        return False
    try:
        r, g, b = (int(part) for part in parts)
        if not (0 <= r <= 255 and 0 <= g <= 255 and 0 <= b <= 255):
            return False
    except ValueError:
        return False
    return True

def send_rgb_uart(rgb_input, port='/dev/tty.usbmodem21401', baudrate=115200): #change port when needed
    """Send the RGB input over UART."""
    try:
        with serial.Serial(port, baudrate, timeout=1) as uart:
            # Add newline character to match the receiver's expected format
            formatted_data = rgb_input + '\n'
            uart.write(formatted_data.encode('utf-8'))
            print(f"Sent data: {formatted_data.strip()}")  # Strip newline for logging
    except serial.SerialException as e:
        print(f"Error communicating over UART: {e}")

if __name__ == "__main__":
    print("Please enter RGB values in the format '### ### ###' (e.g., '255 100 050').")
    print("Each number should be between 000 and 255.")
    print("\nExample RGB colors: Violet = (127, 000, 255), Yellow: (255, 255, 000), Orange: (255, 165, 000), Cyan: (000, 255, 255)")
    print("\nInput the values \"001, 000, 000\" to stop the DMA for whatever reason")
    
    while True:
        rgb_input = input("\nEnter RGB value: ")
        if validate_rgb_input(rgb_input):
            print("\nValid RGB input received")
            send_rgb_uart(rgb_input)
        else:
            print("Invalid input. Please ensure the format is '### ### ###' with each value between 000 and 255.")
