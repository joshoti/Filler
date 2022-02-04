import numpy as np
import random
colours = ['red','green','yellow','blue','purple','black']

def one(colors):
        x = [i[:3] for i in colors]
        s = [['Na' for i in range(8)] for i in range(7)]
        ind = random.randint(0,len(x)-1)
        num = x.pop(ind)
        for row in range(len(s)):
            for col in range(len(s[row])):
                if row>0:
                    num3 = s[row-1][col].strip()
                    if num==num3:
                        tind,tnum, bnum = ind,num, s[row][col-1].strip()
                        bind = x.index(bnum)
                        x.pop(bind)
                        ind = random.randint(0,len(x)-1)
                        num = x.pop(ind)
                        x.insert(tind,tnum)
                        x.insert(bind,bnum)
                ind2 = random.randint(0,len(x)-1)
                num2 = x.pop(ind2)
                s[row][col] = num+'  '
                x.insert(ind,num)
                num, ind = num2,ind2
        s = np.array(s,dtype='<U11')
        return s
	
def run():
    while True:
        try: tab = one(colours)
        except: pass
        else: break
    tab[6][0], tab[0][7] = 'P-1','P-2'
    print(tab)
    
    p1 = [(6,0)]
    p2 = [(0,7)]
    turn = 1
    while len(p1+p2)<56:
        if turn%2==1:
            print(f"\nPlayer 1\t [ {len(p1)} ]\n{', '.join(colours)}")
            c = input("Pick a colour ")[:3]
            for x,y in p1:
                tab[x][y] = c.upper() + '-1'
                if x-1>=0: # up
                    if (tab[x-1][y].strip()==c) & ((x-1,y) not in p1+p2): p1.append((x-1,y))
                if x+1<=6: # down
                    if (tab[x+1][y].strip()==c) & ((x+1,y) not in p1+p2): p1.append((x+1,y))
                if y-1>=0: # left
                    if (tab[x][y-1].strip()==c) & ((x,y-1) not in p1+p2): p1.append((x,y-1))
                if y+1<=7: # right
                    if (tab[x][y+1].strip()==c) & ((x,y+1) not in p1+p2): p1.append((x,y+1))
            print('Now:[',len(p1),']\n')
            tab2 = []
            for i in reversed(tab): tab2+=list(reversed(i))
            tab2 = np.array(tab2, dtype='<U11')
            tab2 = np.resize(tab2,(7,8))
            print(tab2,'\n')

        else:
            print(f"\nPlayer 2\t ( {len(p2)} )\n{', '.join(colours)}")
            c = input("Pick a colour ")[:3]
            for x,y in p2:
                tab[x][y] = c.upper() + '-2'
                if x-1>=0: # up
                    if (tab[x-1][y].strip()==c) & ((x-1,y) not in p1+p2): p2.append((x-1,y))
                if x+1<=6: # down
                    if (tab[x+1][y].strip()==c) & ((x+1,y) not in p1+p2): p2.append((x+1,y))
                if y-1>=0: # left
                    if (tab[x][y-1].strip()==c) & ((x,y-1) not in p1+p2): p2.append((x,y-1))
                if y+1<=7: # right
                    if (tab[x][y+1].strip()==c) & ((x,y+1) not in p1+p2): p2.append((x,y+1))
            print('Now:(',len(p2),')\n')
            print(tab,'\n')
            turn = 0
        turn += 1
    else:
        if len(p1) > len(p2):
            print(f"Player 1 won\t[ {len(p1)} ]")
            return ('P1',len(p1))
        elif len(p2) > len(p1):
            print(f"Player 2 won\t( {len(p2)} )")
            return ('P2',len(p2))

attempts = {}
game = 0
scoreboard = {'P1':0,'P2':0}

while game<5:
    print(scoreboard)
    game+=1
    attempts[game] = run()
    log = sorted(attempts)[-1]
    if (attempts[log][0]=='P1'): scoreboard['P1']+=1
    elif (attempts[log][0]=='P2'): scoreboard['P2']+=1
    x = input('Play again? ( y/n ) ')
    game = (10,game)[x=='y']
