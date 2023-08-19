# Yongbin's task result

## task 1
> How to do Pull requst
- Name: yongbin lee
- ROS version: ros 2 foxy
- Programming Language: python

## task 2
> find $v_r$ and $w_r$

### task 2-1

$$ \dot x_r = v_r \cos(\theta_r) $$

$$ \dot y_r = v_r \sin(\theta_r) $$

$$ \dot x_r = w_r $$

$$ \dot x_r^2 = v_r^2 \cos^2(\theta_r) $$

$$ \dot y_r^2 = v_r^2 \sin^2(\theta_r) $$

add two equation

$$ \therefore v_r = \sqrt{\dot x_r^2 + \dot y_r^2} $$

### task 2-2

$$ \theta_r = \arctan(\frac{\dot y_r}{\dot x_r})$$

$$ \dot \theta_r = \frac{d[\arctan(\frac{\dot y_r}{\dot x_r})]}{dt}$$

$$\therefore \omega_r = \frac{\dot x_r \\ddot y_r - \ddot x_r \dot y_r}{\dot x_r^2+\dot y_r^2}$$

## task 3
> in trajectory equation, find $\dot x_r$, $\ddot x_r$, $\dot y_r$, $\ddot y_r$

$$\dot x_r = -ab\sin(bt)$$

$$\ddot x_r = -ab^2\cos(bt)$$

$$\dot y_r = -ab\cos(bt)$$

$$\ddot y_r = -ab^2\sin(bt)$$

## task 4
> in 8-shape trajectory equation, find $\dot x_r$, $\ddot x_r$, $\dot y_r$, $\ddot y_r$

$$\dot x_r = \bar a \bar b\sin(\bar b t)$$

$$\ddot x_r = \bar a \bar b^2 \cos(\bar b t)$$

$$\dot y_r = \bar a \bar b\cos^2(\bar b t) - \bar a \bar b\sin^2(\bar b t)$$

$$\ddot y_r = 2\bar a \bar b^2 \sin(\bar b t) \cos(\bar b t) - 2\bar a \bar b^2 \sin(\bar b t) \cos(\bar b t)$$

## task 5
> draw square using turtlesim 

![turtlesim_square](https://github.com/yblee1223/incsl_summer_2023/assets/54783158/3c9c45e7-4c25-45d2-a9de-726b3790bf34)

## task 6
> draw circle & 8-shape

![Screenshot from 2023-08-04 11-26-27](https://github.com/yblee1223/incsl_summer_2023/assets/54783158/343df0a8-dfdb-4e0f-8687-d2f3ad6d068c)
![Screenshot from 2023-08-04 12-25-15](https://github.com/yblee1223/incsl_summer_2023/assets/54783158/6a89b31c-0ac6-4026-849f-9e6db2df9e2e)

## task 7
> draw 8-shape with feedback control

![Screenshot from 2023-08-06 13-28-58](https://github.com/yblee1223/incsl_summer_2023/assets/54783158/0625a0b2-d1f7-4f2b-ab90-fb1b1f2cb906)

## task 8
> draw circle using Scout Mini


