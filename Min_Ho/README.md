## Task 1

#### Create folder and specifies your preferred ROS version and programming language

- ROS version : ROS2 Foxy

- Programming Language : C++

## Task 2

#### Calculate general formula of $v_r$ and $w_r$

$$v_r = \sqrt{\dot{x}_r^2 + \dot{y}_r^2}$$

$$w_r = \frac{\ddot{y}_r \dot{x}_r - \dot{y}_r \ddot{x}_r}{\dot{x}_r^2 + \dot{y}_r^2} $$

## Task 3

#### Find the formula of $\dot{x}_r$ , $\dot{y}_r$ , $\ddot{x}_r$ , and $\ddot{y}_r$ in Circle Trajectory

$$\dot{x}_r = -a \cdot b \cdot \sin{bt}$$

$$\dot{y}_r = a \cdot b \cdot \cos{bt}$$

$$\ddot{x}_r = -a \cdot b^2 \cdot \cos{bt}$$

$$\ddot{y}_r = -a \cdot b^2 \cdot \sin{bt}$$

## Task 4

#### Find the formula of $\dot{x}_r$ , $\dot{y}_r$ , $\ddot{x}_r$ , and $\ddot{y}_r$ in 8-shape Trajectory

$$\dot{x}_r = \bar{a} \cdot \bar{b} \cdot \cos{\bar{b}t}$$

$$\dot{y}_r = \bar{a} \cdot \bar{b} \\ (\cos^2{\bar{b}t} - \sin^2{\bar{b}t})$$

$$\ddot{x}_r = -\bar{a} \cdot \bar{b}^2 \cdot \sin{\bar{b}t}$$

$$\ddot{y}_r = -4 \cdot \bar{a} \cdot \bar{b}^2 \cdot \sin{\bar{b}t} \cdot \cos{\bar{b}t}$$

## Task 5

#### Draw Square trajectory using your keyboard

![alt text](./Task5.jpg)

## Task 6

#### Control the turtlesim and make it move in both circular and 8-shaped trajectories.

![t_Task6](https://github.com/Minho-iNCSL/incsl_summer_2023/assets/60316325/6c0779f4-4cee-4b9a-8af9-2285fdad4a3f)

## Task 7 (Optional)

#### Task 6 with Feedback Controller

![Task7](https://github.com/Minho-iNCSL/incsl_summer_2023/assets/60316325/bc54c265-cd5d-457d-bdff-703fafa2e480)

I set the same initial condition (x: 5.5445, y: 5.5445 th: 0.0), but different trajectory because of the feedback controller! 

