To do:
-Create a chuddie handler object
-Chuddies must swim over water
-Health, Hunger, Stamina

Actions:
-Forage wild growth
-Build structure
	-Farm
	-House

Known Bugs:
-Chuddies do not render when (world size * 32 < screen size) (32 is pixels per tile, e.g. world wrapping is smaller than the screen)

CONTROLS

//Movement
W - Walk Up
S - Walk Down
A - Walk Left
D - Walk Right
Shift - Run (Hold)

//Actions
Q - Study Tile
E - Forage Wild Growth
B - Build House        --I want to replace this with opening a menu
F - Build Farm

//Debug
\ - Show FPS
R - Regenerate World
I - Render world as image
G - Print player coordinates
F11 - Fullscreen