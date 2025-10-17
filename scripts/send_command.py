import serial
import struct

def send_uart_packet(port, baudrate, floats):
    """
    Send 4 floats + checksum int over UART.

    Args:
        port (str): Serial port (e.g., '/dev/ttyUSB0' or 'COM3')
        baudrate (int): UART baudrate (e.g., 115200)
        floats (list or tuple): Four float values to send
    """
    if len(floats) != 4:
        raise ValueError("Expected 4 floats")

    # Pack the 4 floats into binary (little-endian)
    float_data = struct.pack('<4f', *floats)

    # Compute checksum (sum of bytes mod 2^16)
    checksum = sum(float_data) % (1 << 16)

    # Pack checksum as a 32-bit int
    packet = float_data + struct.pack('<i', int(checksum))

    # Send over UART
    with serial.Serial(port, baudrate, timeout=1) as ser:
        ser.write(packet)
        print(f"Sent packet ({len(packet)} bytes): {packet.hex()}")

if __name__ == "__main__":
    # Example usage
    floats_to_send = [1000., 1200, 100, -200]
    send_uart_packet('/dev/ttyUSB0', 115200, floats_to_send)

