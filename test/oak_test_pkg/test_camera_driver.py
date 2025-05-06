import os
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
import pytest

# Detect hardware connection
hardware_connected = os.getenv('HARDWARE_CONNECTED', 'false').lower() == 'true'
image_received = False

class CameraImageTester(Node):
    def __init__(self):
        super().__init__('camera_image_tester')
        self.subscription = self.create_subscription(
            Image,
            '/oak/rgb/image_raw',  # Asegúrate de que este topic exista
            self.image_callback,
            10
        )

    def image_callback(self, msg):
        global image_received
        image_received = True
        self.get_logger().info('✅ Image received from /oak/rgb/image_raw')

def test_rgb_image_stream():
    global image_received

    print(f"Hardware connected: {hardware_connected}")
    if not hardware_connected:
        print("⚠️ No hardware detected. Skipping test.")
        return

    rclpy.init()
    node = CameraImageTester()
    try:
        timeout = 10  # seconds
        end_time = node.get_clock().now().nanoseconds / 1e9 + timeout
        while not image_received and node.get_clock().now().nanoseconds / 1e9 < end_time:
            rclpy.spin_once(node, timeout_sec=0.5)
    finally:
        node.destroy_node()
        rclpy.shutdown()

    assert image_received, "❌ No image received from /oak/rgb/image_raw"
