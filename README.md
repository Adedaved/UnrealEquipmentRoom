# Unreal Equipment Room

**Project 3 of a three-project 3D portfolio.** A first-person Unreal Engine greybox for inspecting a data centre equipment installation. The C++ game mode builds a lit room, cabinet, rails, staging pedestal, equipment module, and an industrial control panel from Unreal's built-in meshes at runtime.

## CP-04 control panel integration

Adekunle Olowu integrated the CP-04 control panel into his Unreal Equipment Room working project. The [IndustrialControlPanel repository](https://github.com/Adedaved/IndustrialControlPanel) contains the editable Blender source, textures, renders, and tested GLB export. The public checkout here runs the built-in greybox panel. The imported Unreal asset and scene changes have yet to be published.

## Open and play

1. Clone this repo and install Unreal Engine 5.6 with the C++ toolchain required by Unreal for your OS.
2. Open `UnrealEquipmentRoom.uproject`. If prompted, allow Unreal to build the project module.
3. Click **Play**. The editor starts on an empty engine level because the geometry is generated when play begins.
4. Use **WASD** and the mouse to inspect the room. Press **E** to install the module. Wait for **Module seated**, then press **E** to remove it. Press **R** to return it to staging, including during installation.

The demo uses keyboard controls. The greybox panel is a visual prop. Room and cabinet geometry block the player; the animated module follows a fixed path with physics collision disabled.

## Portfolio projects

| Project | Deliverable |
| --- | --- |
| 1. [Industrial Control Panel](https://github.com/Adedaved/IndustrialControlPanel) | CP-04 hard-surface asset with editable Blender source, UV diagrams, 4K enclosure textures, renders, and a tested GLB export. |
| 2. 3D Data Centre Rack Installation and Maintenance Demonstrator | Standalone Blender project inspired by hands-on IT experience. An animated equipment installation and removal sequence demonstrates rail alignment, clearances, and serviceable moving parts. |
| 3. Unreal Equipment Room | Interactive Unreal greybox for lighting, collisions, controls, and real-time verification. |

The rack demonstrator source and authored installation animation are pending.

## Editor verification

The initial source and project configuration have been checked outside the engine. The build and Play-in-Editor checks still need to be run.

- Confirm the module starts in the staging position and the room is lit.
- Install and remove the module twice. Press **E** during travel and confirm the current move continues. Press **R** mid-installation and confirm the module returns to staging.
- Inspect the fit from the front and side. The nominal module is 44 cm wide and 8.5 cm high. The opening is 44.4 cm wide and 8.9 cm high, giving 2 mm clearance per side when centered.
- Check that the cabinet and room block player movement. Record a walkthrough and a frame-time capture with hardware and resolution.
- After importing the authored Blender assets, compare units, contact frames, and clip duration against the source.
