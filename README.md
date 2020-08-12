# Hamiltonian-Neural-Network

Derivation of the equation for updating the new position using particle impulses:

v_new = v_old + a * TIME_STEP
v_new = v_old + F / m * TIME_STEP
p_new = p_old + F * TIME_STEP

with
r_new = r_old + v * TIME_STEP
r_new = r_old + p_new / m * TIME_STEP

insert p_new
r_new = r_old + TIME_STEP / m * (p_old + F * TIME_STEP)

```math
SE = \frac{\sigma}{\sqrt{n}}
```
