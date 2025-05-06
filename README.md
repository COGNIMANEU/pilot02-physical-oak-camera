    
# Pilot02-Physical OAK Camera ROS 2 Driver

This repository contains the ROS 2 driver for **Pilot02-Physical OAK Camera**. It includes all the necessary configurations, launch files, and a Docker setup to deploy the Camera driver in a containerized environment.

The driver is built on top of the [`depthai_ros_driver`](https://github.com/luxonis/depthai-ros), an open-source package maintained by Luxonis that bridges the [OAK (OpenCV AI Kit)](https://docs.luxonis.com/en/latest/) hardware with the ROS 2 ecosystem.

The `depthai_ros_driver` provides an interface between Luxonis' DepthAI devices and ROS 2. It exposes camera streams, depth information, IMU data, and point clouds as standard ROS topics and supports features like:
- **Synchronized RGB and depth streaming**
- **Real-time point cloud generation**
- **IMU data publishing**
- **TF tree publishing from calibration**
- **ROS 2 composition (for optimized intra-process communication)**
- **Compatibility mode with RealSense node topics**

This makes it ideal for robotics platforms that rely on depth perception, 3D mapping, SLAM, or AI vision processing, particularly in research, prototyping, and production.

## Guidelines for build and test the component 

### 1. **Build the Main Docker Image:**

In this step, we build the Docker image using the provided `Dockerfile`. The image is named `pilot02-physical-OAK-camera`.

```bash
cd src
docker build -t pilot02-physical-oak-camera .
```

Make sure the path to your configuration and launch files is correctly mapped to the Docker container.

### 2. **Run the ROS 2 Container:**

After building the Docker image, you can run the container using the following command:

```bash
cd src
docker run pilot02-physical-oak-camera
```

This will start the container and launch the ROS 2 node with the configured launch file.

### 3. **Build and Run the test automation:**

Test automation is integrated by docker-compose file:

Run: 
```bash
docker-compose up --build
```

This repository includes a test to verify whether the OAK camera is successfully publishing images on the `/oak/rgb/image_raw` topic. The test is controlled by the environment variable `HARDWARE_CONNECTED`.

In case camera hardware is ready, you should see:
```python
Hardware connected: True
[INFO] [camera_image_tester]: ✅ Image received from /oak/rgb/image_raw
```

If errors, you should see:
```python
Hardware connected: True
[ERROR] ❌ No image received from /oak/rgb/image_raw
```

When no hardware is connected (for CI/CD purposes), run with false `HARDWARE_CONNECTED` and it will show:
```python
Hardware connected: False
⚠️ No hardware detected. Skipping test.
```

## Configuration

You can customize the configuration of the camera driver by providing your own configuration files and launch files.
- **camera.yaml**: This file contains parameters specific to your camera setup. You can place your custom `camera.yaml` in the `./config/` directory.
- **camera.launch.py**: This file is used to launch the camera driver and set up the necessary nodes. You can provide your own launch file by placing it in the `./launch/` directory.

Simply replace the default files with your custom configuration files in the respective directories:
- `./config/camera.yaml`
- `./launch/camera.launch.py`

These files will be used when launching the camera driver in a containerized environment, allowing you to tailor the setup to your specific hardware or application needs.


## Contributing

Feel free to open issues or submit pull requests. Contributions are welcome!

## License

This project is licensed under the MIT Licence - see the [LICENSE](LICENSE) file for details.