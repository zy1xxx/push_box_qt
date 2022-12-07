import copy
from tkinter import *
import tkinter as tk
import tkinter.messagebox
import os

# os.chdir(os.path.dirname(os.__file__))

class State:
    def __init__(self,map_filename):
        self.wall=[]
        self.box=[]
        self.des=[]
        with open(map_filename,'r') as f:
            lines=f.readlines()
        
        self.height=int(lines[0].rstrip().split(" ")[0])
        self.width=int(lines[0].rstrip().split(" ")[1])

        for i,line in enumerate(lines[1:]):
            for j,char in enumerate(line.rstrip()):
                if char=='#':
                    self.wall.append([j,i])
                elif char=='X':
                    self.box.append([j,i])
                elif char=='d':
                    self.des.append([j,i])
                elif char=='p':
                    self.player=[j,i]
                elif char=='P':
                    self.player=[j,i]
                    self.des.append([j,i])
                elif char=='d':
                    self.des.append([j,i])
                elif char=='u':
                    self.box.append([j,i])
                    self.des.append([j,i])
        
    def pos_move(self,pos,direction):
        if direction=='上':
            pos[1]-=1
        elif direction=='下':
            pos[1]+=1
        elif direction=='左':
            pos[0]-=1
        else:
            pos[0]+=1
    def move(self,direction):
        new_player=copy.deepcopy(self.player)
        self.pos_move(new_player,direction)#玩家的新位置
        if new_player in self.wall:
            return
        else:
            if new_player in self.box:
                box_index=self.box.index(new_player)
                new_box=copy.deepcopy(self.box[box_index])
                self.pos_move(new_box,direction)#箱子的新位置
                if new_box in self.wall or new_box in self.box:
                    return 
                else:
                    self.player=new_player
                    self.box[box_index]=new_box#推箱子
            else:
                self.player=new_player
    
    def display(self):
        cv.delete(tk.ALL)
        for j in range(self.height):
            for i in range(self.width):
                if [i,j] in self.wall:
                    cv.create_image(i*box_width, j*box_width, anchor=NW,image=wall)  
                elif [i,j] in self.box:
                    cv.create_image(i*box_width, j*box_width, anchor=NW,image=box)
                elif [i,j]==self.player:
                    cv.create_image(i*box_width+16, j*box_width, anchor=NW,image=player)
                elif [i,j] in self.des:
                    cv.create_image(i*box_width+16, j*box_width+16, anchor=NW,image=des)             
    def is_win(self):
        self.box.sort(key=lambda x:x[0])
        self.box.sort(key=lambda x:x[1])
        self.des.sort(key=lambda x:x[0])
        self.des.sort(key=lambda x:x[1])
        if(self.des==self.box):
            return True
        else:
            return False




def key_press(event):
    if event.keysym=="Up":
        s.move("上")
    elif event.keysym=="Down":
        s.move("下")
    elif event.keysym=="Left":
        s.move("左")
    elif event.keysym=="Right":
        s.move("右")
    else:
        print(event.keysym)
    if s.is_win():
        print("win!")
        s.display()
        cv.create_text(200, 120, text="win!", fill='red',
                    font=('Old English Text MT',50))
        if tkinter.messagebox.askyesno(title="push box game", message="是否重新开始"):
            s.__init__("./map.txt")
            s.display()
        else:
            exit(0)
        return 
    s.display()

s=State("./map.txt")
root = Tk()

box_width=64
box = PhotoImage(file = "./img/box.gif")
player = PhotoImage(file = "./img/player.gif")
des = PhotoImage(file = "./img/des.gif")
wall = PhotoImage(file = "./img/wall.gif")

cv = Canvas(root,bg = 'white',height=s.height*64,      # 设置高度
                   width=s.width*64)

if __name__=="__main__":
    cv.pack()

    s.display()
    root.bind("<KeyPress>",key_press)
    
    root.mainloop()

        








