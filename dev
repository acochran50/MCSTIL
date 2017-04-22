# MCSTIL Mathematical Drafting #

Formulas/outlines in this file are taken from *A Monte Carlo Model of Light Propagation in Tissue* by S.A. Prahl (1), M. Keijzer (2), S.L. Jacques (2), A.J. Welch (1)

1. Department of Electrical and Computer Engineering, Biomedical Engineering Program - The University of Texas at Austin
2. Department of Dermatology, Wellman Laboratory - Harvard Medical School

- - -

## Simulation functions ##

### Propagation distance (delta_s) ###

`delta_s = - ln( ksi ) / mu_t`

### Photon movement ###

- `x' = x + (mu_x * delta_s)`
- `y' = y + (mu_y * delta_s)`
- `z' = z + (mu_z * delta_s)`

### Internal reflection (or transmission) ###

**Fresnel reflection coefficient** (probability the photon will be internally reflected):

`R(theta_i) = (1/2) * ( ( ((sin(theta_i - theta_t)^2)) / ((sin(theta_i + theta_t)^2)) ) + ((tan(theta_i - theta_t)^2)) / ((tan(theta_i + theta_t)^2))`

**Snell's law** (to determine angle of transmission, theta_t):

`n_i * sin(theta_i) = n_t * sin(theta_t)`

**Theta sub i** (angle of incidence on the boundary):

`theta_i = cos(mu_z)^-1`

If *R(theta_i)* is less than a randomly generated value **ksi** (uniformly dist. between 0 and 1), then the photon is internally reflected. Otherwise, it leaves the tissue and is marked as backscattered/transmitted, depending on the plane of exit.

4 different cases for layer relfection/transmission:

1. Boundary = one of two extrema; transmission
2. Boundary = one of two extrema; internal reflection
3. Boundary = internal; transmission
4. Boundary = internal; internal reflection

The *z* coordinate of the photon describes both the current layer and the boundary with which it is interacting.

### Photon absorption ###

**Implicit capture** --> assigning "weight" to photons upon tissue entry. Each step involves absorption of some photon weight (energy) and scattering the rest.

**Fraction absorbed**:

`f_abs = mu_a / (mu_a + mu_s)`

Additionally:

`f_abs = mu_a / (mu_a + mu_s) = 1 - (mu_s / (mu_a + mu_s)) = 1 - a`

where a = single particle albedo. As such, **new photon weight** equals:

`w' = a * w`

where **w' = new photon weight** and w = original photon weight. It's a good idea to design "bins" within the matrix that determine where things are absorbed. This can be applied by creating a heat map that displays where energy is absorbed. The spatial resolution can be adjusted as needed by recuding/increasing the number of bins present in the matrix/the size of the bins (important, given the geometry is defined as infinite slabs). **Fluence rate** can be determined/discussed given this approach is used.

### Photon termination (photon roulette) ###

Photon termination is done via roulette to eliminate photons with arbitrarily low amounts of energy. Once energy is too low, the amount of information gained from each step becomes inconsequential.

The roulette technique takes a photon with weight *w* (below the arbitrarily determined threshold weight) and gives a one in *m* chance to survive, upon which its weight will be *mw*. If it does not survive, its weight is reduced to zero and another photon is fired.

It's necessary to make sure that energy is conserved throughout the simulation by comparing the beginning combined weight of all photons to the final combined photon weight.

### Scattering (changing direction) ###

If *g* (**anisotropic constant**) = 0 (isotropic scattering):

`cos(theta) = (2 * ksi) - 1`

If *g* is nonzero (anisotropic scattering), use the generating function for the **Henyey-Greenstein phase function**:

`cos(theta) = (1 / (2 * g) ) * ( 1 + g^2 - ( (1 - g^2) / (1 - g + (2 * g * ksi)))^2 )`

Because this phase function has no azimuthal dependence (*phi*), the azimuthal angle is uniformly distributed between zero and _2 * pi_.

To calculate the new direction after scattering at an angle (theta, phi):

- Original direction: (*mu_x*, *mu_y*, *mu_z*)
- New direction: (*mu_x'*, *mu_y'*, *mu_z'*)

- `mu_x' = (sin(theta) / sqrt(1 - mu_z^2)) * ((mu_x * mu_z * cos(phi)) - mu_y * sin(phi)) + (mu_x * cos(theta))`
- `mu_y' = (sin(theta) / sqrt(1 - mu_z^2)) * ((mu_y * mu_z * cos(phi)) + mu_x * sin(phi)) + (mu_y * cos(theta))`
- `mu_z' = (-sin(theta) * cos(phi) * sqrt(1 - mu_z^2)) + (mu_z * cos(theta))`

If the angle (theta, phi) is too close to the normal (if |*mu_z*| is approaching 1), calculate the new direction by:

- `mu_x' = sin(theta) * cos(phi)`
- `mu_y' = sin(theta) * cos(phi)`
- `mu_z' = (mu_z / abs(mu_z) * cos(phi)`
