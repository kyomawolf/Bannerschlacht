# Bannerschlacht

## structural overview

TODO:
First thing to be made is the Map, all necessities are listed down below.

UI is the next thing to be implemented, firstly the map should be clickable and an interface with information of the clicked tile should be displayed.

after that, unitData shall be implemented, so that they are adressable with functions for movement and other actions, UI implementation for Units should follow.

Implementing the information system with friend/foe recognition is the next priority.

Menus and Settings are the next step afterwards.
	
Balancing (if not done already) are the next thing to do, as new unitData are being implemented.

The best idea would be some sort of rock-paper-scissors system (with more attributes oc) as its suitable for a first balancing.

### Datastructure

- Map
  - made of Tiles
    - Properties and modifier accessed by Units and UI
      - attack width for all six sides
      - stealth modifier
      - action cost when moving through
    - has pointer to unit obj
    - holds a texture, displayed by renderer
    - modifiers that can be added on top, but are seperated to avoid bugs when removed
  - holds mapmodifier applied to all tiles and are being copied
- Units
  - actions
  - data
    - has pointer to tile obj
    - modifiers
    - actions per turn
    - ressources
    - mapinformation it holds
    - hp and hp to men/attack-dmg ratio
  - holds a texture displayable by renderer
- UI
