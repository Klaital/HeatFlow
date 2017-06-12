HeatFlow
========

Open-source heat-flow simulator.


Required Components
===================

1. Tools to convert from standard interchange modelling formats (like .dae) to internal Project files.
2. Tool to create/manage a Project config
 a. Should be able to manage physical properties for the objects present
 b. Set "default material" for areas not explicitly modelled in the input model (usually air, could be water, etc). Should this default to air or vaccuum?
 c. Set mesh interval
 d. Set time step interval
 e. It would be nifty if this was managed via GUI, but may need to be done by editing config files at first.
3. Simulation engine. This will take in the materials list, mesh model of the structure, and project-level configs, then iterate for the specified duration. When done, the output will be in the form of a temperature mesh, or a series of temperature meshes at specified time intervals.
4. Results visualization tools.
 a. For a given point(s) on the model, analyze the temperature over time
 b. Temperature-based heatmap of the final (or single interstitial) state of the model's temperatures.
