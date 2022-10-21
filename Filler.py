import numpy as np
import random
colours = ['red','green','yellow','blue','purple','black']

def MakeGrid(colours):
    """
    Parameters
        colours(list): colours that will be used in game

    Method
        pick the colour for cell 1 and pop the colour from the pool
        select the colour for cell 2 while cell 1 colour is absent
        assign cell 1's colour and return it to colour pool
        assign colour 2 to colour 1 variable 
    """
    colourPool = [i[:3] for i in colours] # 3 letters long for display on grid
    grid = [['foo' for j in range(8)] for i in range(7)] # list of lists (7x8)

    # Select current cell colour
    randomIndex1 = random.randint(0, len(colourPool)-1)
    randomColour1 = colourPool.pop(randomIndex1)
    
    for row in range(len(grid)):
        for col in range(len(grid[row])):
            if row > 0: # It has neighbour above
                neighbourColour = grid[row-1][col].strip()
                if randomColour1 == neighbourColour: # If current cell colour == top neighbour colour
                    # We change randomColour1 to increase grid variance
                    currentIndex, currentColour = randomIndex1, randomColour1                 

                    # We remove left neighbour from colour pool
                    if col > 0: # It has left neighbour
                        leftNeighbourColour = grid[row][col-1].strip()
                        leftNeighbourIndex = colourPool.index(leftNeighbourColour)                    
                        colourPool.pop(leftNeighbourIndex)

                    # Select new-current colour
                    randomIndex1 = random.randint(0, len(colourPool)-1)
                    randomColour1 = colourPool.pop(randomIndex1)

                    # Return old-current colour and left neighbour to colour pool
                    colourPool.insert(currentIndex, currentColour)                
                    if col > 0: # It has left neighbour
                        colourPool.insert(leftNeighbourIndex, leftNeighbourColour)
                        
            # Select next cell colour
            randomIndex2 = random.randint(0, len(colourPool)-1)
            randomColour2 = colourPool.pop(randomIndex2)

            # Assign current cell colour
            grid[row][col] = randomColour1 + '  ' # Space for readability
            
            # Return current cell colour to colour Pool
            colourPool.insert(randomIndex1, randomColour1)
            
            # Transfer colour variables
            randomColour1, randomIndex1 = randomColour2, randomIndex2
    grid = np.array(grid,dtype='<U11') # Transform filled grid to 2D numpy array
    return grid
	
def run():
    gameGrid = MakeGrid(colours)
    gameGrid[6][0], gameGrid[0][7] = 'P-1  ','P-2  '
    print(gameGrid)
    
    p1 = [(6,0)]
    p2 = [(0,7)]
    turn = 1
    while (len(p1)+len(p2)) < 56:
        if turn == 1:            
            print(f"\n\t\t==== P1: {len(p1)}\tP2: {len(p2)} ====")
            print(f"\nOPTIONS: {', '.join(colours)}")
            pickedColour = input("Pick a colour ")[:3]
            for row,col in p1:
                gameGrid[row][col] = pickedColour.upper() + '-1'
                if row-1 >= 0: # up
                    if (gameGrid[row-1][col].strip() == pickedColour) & ((row-1, col) not in p1+p2):
                        p1.append((row-1, col))
                if row+1 <= 6: # down
                    if (gameGrid[row+1][col].strip() == pickedColour) & ((row+1, col) not in p1+p2):
                        p1.append((row+1, col))
                if col-1 >= 0: # left
                    if (gameGrid[row][col-1].strip() == pickedColour) & ((row, col-1) not in p1+p2):
                        p1.append((row, col-1))
                if col+1 <= 7: # right
                    if (gameGrid[row][col+1].strip() == pickedColour) & ((row, col+1) not in p1+p2):
                        p1.append((row, col+1))
            rotatedGameGrid = []
            for i in reversed(gameGrid): rotatedGameGrid += list(reversed(i)) # Rotating board for player 2
            rotatedGameGrid = np.array(rotatedGameGrid, dtype='<U11')
            rotatedGameGrid = np.resize(rotatedGameGrid,(7,8))
            turn = 0
            print(rotatedGameGrid)            

        else:
            print(f"\n\t\t==== P1: {len(p1)}\tP2: {len(p2)} ====")
            print(f"\nOPTIONS: {', '.join(colours)}")
            pickedColour = input("Pick a colour ")[:3]
            for row,col in p2:
                gameGrid[row][col] = pickedColour.upper() + '-2'
                if row-1 >= 0: # up
                    if (gameGrid[row-1][col].strip() == pickedColour) & ((row-1, col) not in p2+p1):
                        p2.append((row-1,col))
                if row+1 <= 6: # down
                    if (gameGrid[row+1][col].strip() == pickedColour) & ((row+1, col) not in p2+p1):
                        p2.append((row+1,col))
                if col-1 >= 0: # left
                    if (gameGrid[row][col-1].strip() == pickedColour) & ((row, col-1) not in p2+p1):
                        p2.append((row,col-1))
                if col+1 <= 7: # right
                    if (gameGrid[row][col+1].strip() == pickedColour) & ((row, col+1) not in p2+p1):
                        p2.append((row,col+1))
            print(gameGrid)            
            turn = 1
            
    else: # Game Over
        if len(p1) > len(p2):
            print(f"Player 1 won\t[ {len(p1)} ]")
            return 'P1'
        elif len(p2) > len(p1):
            print(f"Player 2 won\t( {len(p2)} )")
            return 'P2'
        else:
            print("\nThis match was a Draw. Well Done to both players")
            return 'Draw'

game = 0
scoreboard = {'P1': 0,'P2': 0}

while game < 5:
    game += 1
    print('\Scoreboard: ',scoreboard)    
    winner = run() # Run Game
    if winner == 'Draw':
        scoreboard['P1'] += 1
        scoreboard['P2'] += 1
    else:
        scoreboard[winner] += 1
    replay = input('Play again? ( y/n ) ')
    game = (10, game)[replay == 'y']
