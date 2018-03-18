import pygame as py

py.init()

ASTEROID_IMG = py.image.load("asteroid.png")

FILENAME = "map.png"

class MapSize:
	width = 800
	height = 600

SECTOR_SIZE = 20
ASTEROID_IMG = py.transform.scale(ASTEROID_IMG, (SECTOR_SIZE, SECTOR_SIZE))

def main():
	image = py.display.set_mode((MapSize.width, MapSize.height))
	for y in range(0, MapSize.height, SECTOR_SIZE):
		for x in range(0, MapSize.width, SECTOR_SIZE):
			image.blit(ASTEROID_IMG, (x, y)) 
			
	py.display.update()
	py.image.save(image, FILENAME)   
	print("Done")    
	
main()