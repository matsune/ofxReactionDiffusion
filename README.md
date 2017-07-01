<img src="https://github.com/matsune/ofxReactionDiffusion/blob/master/thumbs/header.png" width="700">
#### ofxReactionDiffusion is openFrameworks addon for visualizing Reaction-Diffusion System using GPU.

## Installation
Copy to `openFrameworks > addons`.

## Reaction Diffusion System
> Reaction–diffusion systems are mathematical models which correspond to several physical phenomena: the most common is the change in space and time of the concentration of one or more chemical substances: local chemical reactions in which the substances are transformed into each other, and diffusion which causes the substances to spread out over a surface in space.
> (from [Wikipedia](https://en.wikipedia.org/wiki/Reaction%E2%80%93diffusion_system))

## Models
Reaction-Diffusion System has a few mathematical models and ofxReactionDiffusion implements three models of them.

### - Gray-Scott
<img src="https://github.com/matsune/ofxReactionDiffusion/blob/master/thumbs/gs.gif" width="500">

### - FitzHugh-Nagumo
<img src="https://github.com/matsune/ofxReactionDiffusion/blob/master/thumbs/fhn.gif" width="500">

### - Belousov-Zhabotinsky
<img src="https://github.com/matsune/ofxReactionDiffusion/blob/master/thumbs/bz.gif" width="500">

## Usage
Models are defined `ReactionDiffusionMode` .  
You can switch drawing model by `void setMode(ReactionDiffusionMode _mode)` .

Since each mode has its own parameters, it is necessary to use the parameters properly according to the mode being used.
#### - Gray-Scott
```c++
float feed;
float kill;
float Du;
float Dv;
```

#### - FitzHugh-Nagumo
```c++
float a0;
float a1;
float epsilon;
float delta;
float k1;
float k2;
float k3;
```

#### - Belousov-Zhabotinsky
```c++
float alpha;
float beta;
float gamma;
```

### Extension
#### Examples > example_mesh
Values, concentration of substances, are stored in FBO(texture) and they are represented as RGB in texture in ofxReactionDiffusion. You can get source texture by `getSourceTexture`.

<img src="https://github.com/matsune/ofxReactionDiffusion/blob/master/thumbs/mesh.gif" width="500">

For example, reaction diffusion values can use for depth of VBOMesh. (See **Examples > example_mesh**)
