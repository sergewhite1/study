from typing import List
import math
import matplotlib.pyplot as plt

# Input Params:
FULL_BAND = 55
DISCRETE_COUNT = 256
SIGNAL_FREQ_CHANNEL = 48
# SIGNAL_FREQ_CHANNEL = 100

SIGNAL_AMPLITUDE = 1.0
SIGNAL_INIT_PHASE = 0.0  # rad


def generate_time_axis(t_start, t_step, discrete_count):
    ret = []

    for i in range(discrete_count):
        t = t_start + i * t_step
        ret.append(t)

    return ret


def calc_base_freq(t_observ):
    return 1/t_observ


def generate_freq_axis(base_freq, freq_channel_count):
    ret = []

    for freq_channel in range(freq_channel_count):
        f = freq_channel * base_freq
        ret.append(f)

    return ret


def signal(t, ampl, freq, init_phase):
    return ampl * math.cos(2.0 * math.pi * freq * t + init_phase)


def generate_signal_vals(ampl, freq, init_phase, time_axis: List):
    ret = []

    for t in time_axis:
        s = signal(t, ampl, freq, init_phase)
        ret.append(s)

    return ret


def dft(x: List, N):
    ret = []
    FREQ_CHANNEL_COUNT = N

    for k in range(FREQ_CHANNEL_COUNT):
        sum = 0
        for i in range(N):
            phi = (2 * math.pi * k * i) / N
            sum += x[i] * complex(math.cos(phi), -math.sin(phi))
        ret.append(sum)

    return ret


def calc_magnutudes(spectr: List[complex], freq_channel_count):
    ret = []

    for freq_channel in range(freq_channel_count):
        ret.append(abs(spectr[freq_channel]))

    return ret


# Output Params:
OBSERVED_TIME = DISCRETE_COUNT / FULL_BAND
BASE_FREQ_V = calc_base_freq(OBSERVED_TIME)
SIGNAL_FREQUENCY = SIGNAL_FREQ_CHANNEL * BASE_FREQ_V
TIME_DISCRETE = OBSERVED_TIME / DISCRETE_COUNT  # dt

time_axis = generate_time_axis(0.0, TIME_DISCRETE, DISCRETE_COUNT)
freq_axis = generate_freq_axis(BASE_FREQ_V, DISCRETE_COUNT)

signal_y = generate_signal_vals(SIGNAL_AMPLITUDE,
                                SIGNAL_FREQUENCY,
                                SIGNAL_INIT_PHASE,
                                time_axis)

spectr = dft(signal_y, DISCRETE_COUNT)
magnitude_v = calc_magnutudes(spectr, DISCRETE_COUNT)


print("Input Params:")
print(f"FULL_BAND={FULL_BAND}")
print(f"DISCRETE_COUNT={DISCRETE_COUNT}")
print(f"SIGNAL_FREQ_CHANNEL={SIGNAL_FREQ_CHANNEL}")
print(f"SIGNAL_AMPLITUDE={SIGNAL_AMPLITUDE}")
print(f"SIGNAL_INIT_PHASE={SIGNAL_INIT_PHASE}")


print("")

print("Output Params:")
print(f"OBSERVED_TIME={OBSERVED_TIME}")
print(f"BASE_FREQ_V={BASE_FREQ_V}")
print(f"SIGNAL_FREQUENCY={SIGNAL_FREQUENCY}")
print(f"TIME_DISCRETE={TIME_DISCRETE}")

fig, ax = plt.subplots()

ax.stem(time_axis, signal_y)

fig, ax = plt.subplots()

ax.stem(freq_axis, magnitude_v)

plt.show()
