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

$$\frac{d[\arctan(\frac{\sin(\theta)}{\cos(\theta)})]}{dt} = -\frac{y}{x^2+y^2}dx+\frac{x}{x^2+y^2}dy$$

$$\frac{d\theta}{dt} = \frac{xdy-ydx}{x^2+y^2}$$

$$\therefore \dot \theta_r = \frac{xdy-ydx}{x^2+y^2}$$

## task 3
> find $\dot x_r$, $\ddot x_r$, $\dot y_r$, $\ddot y_r$

$$\dot x_r = -ab\sin(bt)$$

$$\ddot x_r = -ab^2\cos(bt)$$

$$\dot y_r = -ab\cos(bt)$$

$$\ddot y_r = -ab^2\sin(bt)$$

## task 4
> find $\dot x_r$, $\ddot x_r$, $\dot y_r$, $\ddot y_r$

$$\dot x_r = \bar a \bar b\sin(\bar b t)$$

$$\ddot x_r = \bar a \bar b\cos^2(\bar b t) - \bar a \bar b\sin^2(\bar b t)$$

$$\dot y_r = \bar a \bar b^2 \cos(\bar b t)$$

$$\ddot y_r = 2\bar a \bar b^2 \sin(\bar b t) \cos(\bar b t) - 2\bar a \bar b^2 \sin(\bar b t) \cos(\bar b t)$$










