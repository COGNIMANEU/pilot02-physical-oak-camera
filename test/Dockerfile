FROM ros:humble

# Install dependencies
RUN apt-get update && apt-get install -y \
    python3-pytest \
    python3-colcon-common-extensions \
    ros-humble-rclpy \
    ros-humble-sensor-msgs \
    && rm -rf /var/lib/apt/lists/*

# Create workspace
WORKDIR /test_ws
COPY ./ /test_ws/src/oak_test_pkg

# Build tests
RUN . /opt/ros/humble/setup.sh && colcon build --packages-select oak_test_pkg

# Run tests
CMD ["/bin/bash", "-c", \
     "source /opt/ros/humble/setup.bash && \
      source /test_ws/install/setup.bash && \
      echo \"Waiting for 30 seconds to allow the camera driver to initialize...\" && \
      sleep 30 && \
      colcon test --packages-select oak_test_pkg && \
      colcon test-result --verbose"]