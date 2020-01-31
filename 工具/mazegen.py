#coding=utf-8
# 多用途迷宫生成器 DFS + Randomized Prim
# Author: limejuice
import random as rd
import sys

### 参数设置
width = 10
height = 10
pturn = 0.4 # 转弯概率
pend = 0 # 分支结束概率（只对Prim部分有效，设为0则为标准的随机Prim算法）
pback = 0.3 # 回溯概率（设为0则为标准的Prim算法，1为标准的DFS算法）
###

maze = [[[False,False] for i in range(height + 1)] for j in range(width + 1)] # [x][y][0右墙1下墙]
vis = [[False for i in range(height + 1)] for j in range(width + 1)]
extend = [] # 可能的分支起始点

def move(coord,dire):
	delta = ((0,1),(-1,0),(0,-1),(1,0)) # 方向矢量
	return (coord[0] + delta[dire][0],coord[1] + delta[dire][1])

def valid(coord):
	if(coord[0] <= 0 or coord[1] <= 0):
		return False
	if(coord[0] > width or coord[1] > height):
		return False
	if(vis[coord[0]][coord[1]]):
		return False
	return True

def testturn(coord,curdir):
	newdir = (curdir + rd.choice((1,-1)) + 4) % 4 # 随机选择一个转向
	if(valid(move(coord,newdir))):
		return newdir
	elif(valid(move(coord,(curdir * 2 - newdir + 4) % 4))): # 测试另一个方向
		return (curdir * 2 - newdir + 4) % 4
	else:
		return None

def testalone(coord,curdir):
	if(valid(move(coord,curdir))):
		return curdir
	else:
		return None

def getnextdir(coord,curdir):
	if(rd.uniform(0,1) < pturn): # 决定优先顺序
		res = (testturn(coord,curdir),testalone(coord,curdir))
	else:
		res = (testalone(coord,curdir),testturn(coord,curdir))
	for i in res:
		if(i != None):
			return i
	return None # 无路可走

def search(coord,initdir):
	curdir = initdir
	while curdir != None:
		if(curdir == 0):
			maze[coord[0]][coord[1]][1] = True
		elif(curdir == 3):
			maze[coord[0]][coord[1]][0] = True
		coord = move(coord,curdir)
		vis[coord[0]][coord[1]] = True
		extend.append(coord)
		if(curdir == 1):
			maze[coord[0]][coord[1]][0] = True
		elif(curdir == 2):
			maze[coord[0]][coord[1]][1] = True
		if(rd.uniform(0,1) < pend):
			break
		curdir = getnextdir(coord,curdir)

### main
sys.stdout.reconfigure(encoding="utf-8")

for i in range(0,width + 1):
	maze[i][0][0] = True
for i in range(0,height + 1):
	maze[0][i][1] = True

search((0,1),3)
while extend:
	ok = False
	back = rd.uniform(0,1) < pback
	while extend and not ok:
		if(back):
			start = extend[-1]
		else:
			start = rd.choice(extend)
		dirs = [i for i in range(4)]
		while dirs:
			initdir = rd.choice(dirs)
			if(valid(move(start,initdir))):
				search(start,initdir)
				ok = True
				break
			dirs.remove(initdir)
		if(not dirs):
			extend.remove(start)

wall = ('┼','┴','├','└','┬','─','┌','╶','┤','┘','│','╵','┐','╴','╷',' ')

for j in range(1,height + 2): # 打印迷宫
	for i in range(1,width + 2):
		idx = 0
		if(maze[i - 1][j - 1][1]): # 二进制压位寻址
			idx = idx + 2 # left
		if(maze[i - 1][j - 1][0]):
			idx = idx + 4 # up
		if(i > width or maze[i][j - 1][1]):
			idx = idx + 8 # right
		if(j > height or maze[i - 1][j][0]):
			idx = idx + 1 # down
		print(wall[idx],end='')
	print()