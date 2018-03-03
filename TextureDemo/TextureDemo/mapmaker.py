import pygame as py

py.init()

ROAD = 1
ASTEROID = 0

ROAD_IMG =  py.image.load("road.png")
ASTEROID_IMG = py.image.load("asteroid.png")

#(IMG_WIDTH, _ ) = ASTEROID_IMG.get_rect().size



TOTAL_WIDTH_FRACTION = 8
ROAD_WIDTH_FRACTION = 4
ROAD_BOARDER_WIDTHS_FRACTION = (TOTAL_WIDTH_FRACTION - ROAD_WIDTH_FRACTION) / 2

SECTOR_SIZE = 20

ROAD_IMG = py.transform.scale(ROAD_IMG, (SECTOR_SIZE, SECTOR_SIZE))
ASTEROID_IMG = py.transform.scale(ASTEROID_IMG, (SECTOR_SIZE, SECTOR_SIZE))

FILENAME = "map.png"

def getMapSize():
    width = int(input("Map width: "))
    height = int(input("Map height: "))
    return (width, height)

def getBoarderSize(mapWidth):
    return mapWidth * (ROAD_BOARDER_WIDTHS_FRACTION / TOTAL_WIDTH_FRACTION)
    
'''def getImg(string):    
    file = open(FILENAME,'w')
    file.write(string)
    file.close()
    def stringToImage(string):
    switch(int(string)):
        case ASTEROID:
            return ASTEROID_IMG
        case ROAD_IMG:
            return ROAD_IMG'''
    
def main():
    
    #mapString = ""
    (mapWidth, mapHeight) = getMapSize()
    image = py.display.set_mode((mapWidth, mapHeight))
    boarderSize = getBoarderSize(mapWidth)

    for y in range(0, mapHeight, SECTOR_SIZE):
        for x in range(0, mapWidth, SECTOR_SIZE):
            '''xSector = x / SECTOR_SIZE
            ySector = y / SECTOR_SIZE'''
            if (x < boarderSize or x > mapWidth - boarderSize):
                #mapString += str(ASTEROID)
                image.blit(ASTEROID_IMG, (x, y))   
            else:
                image.blit(ROAD_IMG, (x, y))
                #mapString += str(ROAD)
        #if (xSector < mapWidth - SECTOR_SIZE):
        #mapString += "\n"
    py.display.update()
    py.image.save(image, FILENAME)   
    print("Done")    
    #getImg(mapString)

main()