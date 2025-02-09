To do:
-Create a chuddie handler object
-Farming:
	-New textures
		-Plowed
		-Sowed
		-Ready to harvest
-Update action selection

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
E - Forage Wild Growth, Harvest farm, Weed
B - Build House        --I want to replace this with opening a menu
F - Build Farm
/ - Sleep
Enter - Use Item
I - Organize inventory

//Debug
\ - Show FPS
R - Regenerate World
P - Render world as image
G - Print player coordinates
F11 - Fullscreen
[ - Decrease game speed
] - Increase game speed
= - Reset game speed to 1
- - Skip action wait time