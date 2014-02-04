import random
import math

import singleton


class Room():
    def __init__(self,shape, pos, size, angle):
        self.shape = shape
        self.pos = list(pos)
        self.size = size
        self.angle = angle

class Path():
    def __init__(self, pos, angle, steps, turn, met, wait):
        self.pos = pos
        self.angle = angle
        self.steps = steps
        self.turn = turn
        self.met = met
        self.wait = wait
        self.path = []

class Trap():
    def __init__(self, pos, trigger, reset, findDc, disableDc, dammage, die, ID, roomID):
        self.pos = pos
        self.trigger = trigger
        self.reset = reset
        self.findDc = findDc
        self.disableDc = disableDc
        self.dammage = dammage
        self.die = die
        self.ID = ID
        self.roomID = roomID

class Treasure():
    def __init__(self, pos, type_, trap, ID, roomID):
        self.pos = pos
        self.type_ = type_
        self.trap = trap
        self.roomID = roomID
        self.ID = ID

class Terrain():
    __metaclass__ = singleton.Singleton
    def __init__(self, size, target_rooms, room_size, variation, resolution,
                 traps_per_room, treasure_per_room, party_level):
        self.size = size
        self.target_rooms = target_rooms
        self.room_size = room_size
        self.variation = variation
        self.resolution = resolution
        self.traps_per_room = traps_per_room
        self.treasure_per_room = treasure_per_room
        self.party_level = party_level

        self.treasure = []
        self.traps = []
        self.rooms = []
        self.paths = []
        self.grid = grid = [[0 for y in range(self.size[0])] for x in range(self.size[1])]


    def generate_terrain(self):

        met = 0;
        self.grid = grid = [[0 for y in range(self.size[0])] for x in range(self.size[1])]
        self.basic_grid = [[0 for y in range(self.size[0])] for x in range(self.size[1])]

        self.generate_rooms()
        while (len(self.paths)):
            for path in self.paths:
                if (path.steps == 0):
                    path.angle = math.atan2(self.size[1] / 2 - path.pos[1], self.size[0] / 2 - path.pos[0])
                    path.turn = random.uniform(self.variation/2*-1, self.variation/2)
                    path.angle += path.turn

                if (path.pos[0] + math.cos(path.angle) > self.size[0] - 1 or
                    path.pos[0] + math.cos(path.angle) < 1 or
                    path.pos[1] + math.sin(path.angle) > self.size[1] - 1 or
                    path.pos[1] + math.sin(path.angle) < 1):
                    self.paths.remove(path)
                    break
                else:
                    path.pos[0] += math.cos(path.angle)
                    path.pos[1] += math.sin(path.angle)
                    path.path.append(path.pos)

                    path.turn = random.uniform(self.variation/2*-1, self.variation/2)
                    path.angle += path.turn

                    if (path.wait > 0):
                        path.wait -= 1
                    if path.wait == 2:
                        path.met = 1
                        self.paths.remove(path)

                    if (path.wait == 0 and (
                        grid[int(path.pos[0])+(1 if math.cos(path.angle) > 0 else -1)][int(path.pos[1])] == 1 or
                        grid[int(path.pos[0])][int(path.pos[1])+(1 if math.sin(path.angle) > 0 else -1)] == 1 or
                        grid[int(path.pos[0]+(1 if math.cos(path.angle) > 0 else -1))][int(path.pos[1])+(1 if math.sin(path.angle) > 0 else -1)] == 1)):

                        path.wait = 3;

                    if (random.randint(1, 100) == 1):
                        self.GenerateTrap("path",path.pos)
                    if (random.randint(1, 100) == 1):
                        self.GenerateTreasure("path",path.pos)


                    if (path.steps == 0 and grid[int(path.pos[0])][int(path.pos[1])] != 4):
                        grid[int(path.pos[0])][int(path.pos[1])] = 2
                    else:
                        if (path.wait > 0 and
                            grid[int(path.pos[0])][int(path.pos[1])] == 1):
                            grid[int(path.pos[0])][int(path.pos[1])] = 3
                        elif (grid[int(path.pos[0])][int(path.pos[1])] == 0):
                            grid[int(path.pos[0])][int(path.pos[1])] = 1
                    path.steps+=1

        for i,x in enumerate(grid):
            for j,y in enumerate(x):
                if y != 0:
                    try: self.basic_grid[i][j] = 1
                    except: pass
                    try: self.basic_grid[i+1][j] = 1
                    except: pass
                    try: self.basic_grid[i-1][j] = 1
                    except: pass
                    try: self.basic_grid[i][j+1] = 1
                    except: pass
                    try: self.basic_grid[i][j-1] = 1
                    except: pass

    def generate_rooms(self):
        points = []
        for x in range(self.size[0]):
            xlist = []
            for y in range(self.size[1]):
                points.append([x,y])

        self.treasure = []
        self.traps = []
        self.rooms = []
        self.paths = []

        for target_num in range(self.target_rooms):
            location = random.choice(points) #chose random point

            angle = random.uniform(0, math.pi*2)
            self.paths.append(Path(location, angle,
                              0, 0, 0 ,0))
            room = Room(random.choice(["round", "square"]), location, 
                              random.uniform(self.room_size/2, self.room_size*2),
                              angle)
            self.rooms.append(room)
            self.grid[location[0]][location[1]] = 4

            for x in range(self.traps_per_room):
                if (random.randint(1, 100) <= 15):  # 15% * trapsPerRoom chance of traps in this room:
                    self.GenerateTrap("room",room.pos)
            for x in range(self.treasure_per_room):
                if (random.randint(1, 100) <= 15):  # 15% * treasurePerRoom chance of traps in this room:
                    self.GenerateTreasure("room",room.pos)


    def GenerateTrap(self, from_, pos):
        pos = (int(pos[0]), int(pos[1]))
        if from_ == "room":
            roomId = len(self.rooms) - 1
            trigger = random.choice(["Trip", "Area", "Chest", "Door"])

            if pos[0] < self.size[0]-1:
                self.grid[pos[0] + 1][pos[1]] = 2;
            if pos[0] > 0:
                self.grid[pos[0] - 1][pos[1]] = 2;
            if pos[1] < self.size[1]-1:
                self.grid[pos[0]][pos[1]+1] = 2;
            if pos[1] > 0:
                self.grid[pos[0]][pos[1]-1] = 2;
        if from_ == "path":
            roomId = -1
            trigger = random.choice(["Trip", "Area", "Chest"])
            self.grid[pos[0]][pos[1]] = 2
        if from_ == "treasure":
            roomId = -1
            trigger = "Chest"

        reset = random.choice(["Auto", "Manual", "None"])
        findDc = 15 + 4 + random.randint(self.party_level/2,
                                          self.party_level*3/2)
        disableDc = findDc + random.randint(4, 10)

        dammage = random.randint(self.party_level/2, self.party_level+1)
        die = random.randint(2,5)

        id_ = len(self.traps)
        trap = Trap(pos, trigger, reset, findDc, disableDc, dammage, die, id_, roomId)
        self.traps.append(trap)
        return trap

    def GenerateTreasure(self, from_, pos):
        pos = (int(pos[0]), int(pos[1]))
        if from_ == "room":
            roomId = len(self.rooms) - 1

            if pos[0] < self.size[0]-1:
                self.grid[pos[0] + 1][pos[1]+1] = 5;
            if pos[0] > 0:
                self.grid[pos[0] - 1][pos[1]-1] = 5;
        if from_ == "path":
            self.grid[pos[0]][pos[1]] = 5
            roomId = -1

        type_ = random.choice(["Gold", "Art", "Object", "Weapon", "Magic"])

        id_ = len(self.treasure)

        if random.randint(0,4) == 0:
            trap = self.GenerateTrap("treasure", pos)
        else:
            trap = -1

        self.treasure.append(Treasure(pos, type_, trap, id_, roomId))

