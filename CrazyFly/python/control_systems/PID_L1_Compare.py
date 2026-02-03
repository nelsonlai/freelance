import numpy as np
import matplotlib.pyplot as plt

# Simulation settings
dt = 0.01
T = 10
time = np.arange(0, T, dt)

# Reference trajectory (step to 1)
y_ref = np.ones_like(time)

# Disturbance (wind gust)
def disturbance(t):
    return 0.5*np.sin(2*t) if t > 2 else 0

# ----------------------------
# PID Controller
# ----------------------------
Kp, Ki, Kd = 15.0, 2.0, 5.0
y_pid, v_pid = 0.0, 0.0
integral_pid, prev_error_pid = 0.0, 0.0
y_pid_hist = []

for t, r in zip(time, y_ref):
    error = r - y_pid
    integral_pid += error * dt
    derivative = (error - prev_error_pid) / dt

    u = Kp*error + Ki*integral_pid + Kd*derivative
    prev_error_pid = error

    # Plant dynamics with disturbance
    acc = u + disturbance(t)
    v_pid += acc * dt
    y_pid += v_pid * dt

    y_pid_hist.append(y_pid)

# ----------------------------
# L1 Adaptive Controller
# ----------------------------
# Baseline: simple proportional (like a weak PID)
Kp_base = 10.0

# L1 adaptive params
Gamma = 50.0          # adaptation gain
theta_hat = 0.0       # estimate of disturbance
filter_alpha = 20.0   # low-pass filter (smoothing)

y_l1, v_l1 = 0.0, 0.0
theta_hat_hist = []
y_l1_hist = []

for t, r in zip(time, y_ref):
    error = r - y_l1

    # Baseline control (P controller)
    u_base = Kp_base * error

    # Adaptive law: estimate disturbance
    prediction_error = v_l1 - (u_base + theta_hat)
    theta_hat_dot = -Gamma * prediction_error
    theta_hat += theta_hat_dot * dt

    # Low-pass filter on adaptive term
    adaptive_term = (filter_alpha * theta_hat * dt + theta_hat) / (1 + filter_alpha * dt)

    # Control input
    u = u_base - adaptive_term

    # Plant dynamics with disturbance
    acc = u + disturbance(t)
    v_l1 += acc * dt
    y_l1 += v_l1 * dt

    y_l1_hist.append(y_l1)
    theta_hat_hist.append(theta_hat)

# ----------------------------
# Plot results
# ----------------------------
plt.figure(figsize=(10,5))
plt.plot(time, y_ref, 'k--', label="Reference (Step)")
plt.plot(time, y_pid_hist, 'b-', label="PID Response")
plt.plot(time, y_l1_hist, 'g-', label="L1 Adaptive Response")
plt.xlabel("Time [s]")
plt.ylabel("Position y(t)")
plt.legend()
plt.title("PID vs L1 Adaptive Control (Step Response with Disturbance)")
plt.grid(True)
plt.show()