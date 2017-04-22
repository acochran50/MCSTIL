# Notes #

### File Input ###

Need to change from 2 input files to 1, and make them easier to read/write. Check out some documentation on `<iomanip>` maybe?

Determined that it was easier to set the bounds during looping through `tissue_vector` to perform checks and print the tissue profile. Now need to figure out a good way to check for a boundary cross during the propagation algorithm.

### Photon Propagation Algorithm ###

Figured out that using `new` is effective to create a completely separate instance of a photon every time another is required within the propagation loop.

Questions:
- Do I need to `delete` every time at the end of the loop, i.e. once a photon is killed using the roulette system? Maybe I can define a method for it if that's the case.
- Look at which members are pub/priv... should these be reorganized? Does it matter? Specifically things like Photon::layer_. This question is especially important for deployment.