#user list
Userlist = []

#user
class User:
    def __init__(self, name, phone, magic):
        self.name = name
        self.phone = phone
        self.magic = magic
        self.prev = None
        self.next = None
    
    def add_to_list(self, Userlist):
        self.info = [self.name, self.phone, self.magic]
        Userlist.append(self.info)

#queue
class Queue:
    def __init__(self):
        self.head = None
        self.len1 = 0 #magic pass
        self.len2 = 0 #all
        self.cur1 = self.head #magic pass
        self.cur2 = self.head #no magic pass
    
    #functions
    def create(self, new):
        self.head = new
        if new.magic:
            self.cur1 = new
            self.len1 += 1
        self.cur2 = new
        self.len2 += 1

    def enqueue(self, new): 
        if self.len2 == 0:
            self.create(new)
            return
        if new.magic:
            self.cur1.next = new
            self.cur1.prev = self.cur1
            new.prev = self.cur1
            new.next = self.cur1.next
            self.cur1 = new
            self.len1 += 1
            if self.len2 == self.len1:
                self.cur1.next = self.cur2
                self.cur2.prev = self.cur1
                self.cur1.next = self.cur2
        else: 
            if self.len2 == self.len1:
                self.cur2 = self.cur1
                self.cur2.prev = self.cur1.prev
                self.cur2.next = self.cur1.next
            self.cur2.next = new
            self.cur2.prev = self.cur2
            new.prev = self.cur2
            new.next = None
            self.cur2 = new
        self.len2 += 1

    def dequeue(self):
        dequeued = self.head
        if dequeued.magic:
            self.len1 -= 1
        self.head = self.head.next
        self.len2 -= 1      
    
    def delete(self, phone):
        erase = self.search(phone)
        if erase is None:
            print("Error: wrong information.")
        if erase.magic:
            self.len1 -= 1
            if self.cur1 == erase:
                self.cur1 = self.cur1.prev
                self.cur1.next = self.cur1.next
            else:
                erase.prev.next = erase.next
                erase.next.prev = erase.prev
            del(erase)
        else:
            if self.cur2 == erase:
                if self.cur2 == self.head:
                    self.__init__()
                    return
                self.cur2 = self.cur2.prev
                self.cur2.next = None
            else:
                erase.prev.next = erase.next
                erase.next.prev = erase.prev
            self.len2 -= 1

    def search(self, phone):
        find = self.head
        while find is not None:
            if find.phone == phone:
                return find
            find = find.next
        return None

    def print_queue(self):
        crnt = self.head
        for i in range(self.len2):
            print(crnt.name, end = ' ')
            print(crnt.phone, end = ' ')
            if crnt.magic == False :
                print("일반 회원입니다.\n")
            else :
                print("매직패스 이용자\n")
            print()
            crnt = crnt.next

#ride
class Ride:
    def __init__(self, queue, num, time):
        self.line = queue
        self.time1 = None #waiting time for magic pass
        self.time2 = None #waiting time for no magic pass
        self.num = num #num per ride
        self.time = time #time per ride (include break time)
    
    def get_time(self):
        self.time1 = int(self.line.len1 / self.num) * self.time
        self.time2 = int(self.line.len2 / self.num) * self.time

    def print_howmuch(self):
        print("대기인원수: %d" %(self.line.len2))
        self.get_time()
        print("예상소요시간: %d" %(self.time2))

#tkinter
from tkinter import *
from tkinter import ttk

class Mainframe(ttk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.master = master
        master.title("Welcome to Queuetie Land!")
        master.geometry('600x400')
        self.create_widgets()
    
    def create_widgets(self):
        self.b1 = ttk.Button(self.master, text = 'Add User', command = self.add_user)
        self.b2 = ttk.Button(self.master, text = 'Show Line', command = self.show_line)
        self.l1 = ttk.Button(self.master, text = 'Roller coaster', command = self.manage_ride)
        
        self.b1.place(x = 200, y = 200)
        self.b2.place(x= 200, y = 150)
        self.l1.place(x = 200, y = 100)
        
        self.style = ttk.Style(self)
        self.style.configure('Tbutton', 
        foreground = [('pressed', 'orchid'), ('active', 'thistle')])
        
    def add_user(self): #user 네임을 정해줘야할듯?? 왜냐면 enqueue할때 그게 필요함
        def new_user():
           name = e1.get()
           phone = e2.get()
           magic = CheckVar.get()  
           username = phone
           username = User(name, phone, magic)   
           username.add_to_list(Userlist)
           e1.delete(0,END)
           e2.delete(0,END)
           #c1 deselect 
           print(username.name) #그냥 확인용 print, 화면에 add user 후에 어떻게 보여줄지 정해야 함

        new = Toplevel(self.master) #외부 윈도우
        new.title("User")
        new.geometry('200x200')

        l1 = ttk.Label(new, text = 'Name')
        l2 = ttk.Label(new, text = 'Phone')
        l3 = ttk.Label(new, text = 'Magic')

        CheckVar = BooleanVar()
        CheckVar.set(False)

        e1 = ttk.Entry(new)
        e2 = ttk.Entry(new)
        c1 = ttk.Checkbutton(new, text = 'Yes', variable = BooleanVar, onvalue = True, offvalue = False)

        b1 = ttk.Button(new, text = 'Add', command = new_user) 

        l1.place(x = 20, y = 20)
        l2.place(x = 20, y = 50)
        l3.place(x = 20, y = 80)
        e1.place(x = 60, y = 20)
        e2.place(x = 60, y = 50)
        c1.place(x = 100, y = 80)
        b1.place(x = 60, y = 150)

    def show_line(self):
        new = Toplevel(self.master)
        new.title("Line")
        new.geometry('400x400')

        roller.get_time()

        l1 = ttk.Label(new, text = '현재 대기줄 정보를 출력합니다.\n')
        # line1, time1도 나중에 추가
        l2 = ttk.Label(new, text = '대기 인원(매직패스): ' + str(roller.line.len1) +'\n대기 인원(전체): ' + str(roller.line.len2))
        l3 = ttk.Label(new, text = '예상 대기 시간(매직패스): ' + str(roller.time1) + '\n예상 대기 시간(전체): ' +str(roller.time2))
        l4 = ttk.Label(new, text = '현재 대기줄 인원의 전화번호')

        l1.pack()
        l2.pack()
        l3.pack()
        l4.pack()

        crnt = roller.line.head

        while crnt is not None:
            cc = crnt.name
            cc = ttk.Label(new, text = crnt.phone)
            cc.pack()
            crnt = crnt.next
        
    def manage_ride(self):
        def line_enqueue():
            def enter():
                phone = e1.get()
                for i in range(len(Userlist)):
                    if phone == Userlist[i][1]:
                        user = User(Userlist[i][0], Userlist[i][1], Userlist[i][2])
                        roller.line.enqueue(user)
                        break
                print(roller.line.head.name) #확인용
                l1.destroy()
                e1.destroy()
                b1.destroy()

            l1 = ttk.Label(new, text = "Insert Phone number")
            e1 = ttk.Entry(new) 
            b1 = ttk.Button(new, text = 'Enter', command = enter)

            l1.place(x=100, y =130, width = 200)
            e1.place(x=100, y=150, width = 200)
            b1.place(x=100, y=180, width = 200)
           
        
        def line_dequeue(): #한번 탑승 시 탑승 인원만큼 dequeue되는거임, 인원수 부족할 경우 0명 될떄까지만
            for i in range(roller.num):
                if roller.line.len2 == 0: 
                    return
                roller.line.dequeue()
        
        def line_delete(): 
            def enter(): # 엔터누르면 사라짐
                phone = e1.get()
                roller.line.delete(phone)
                print(roller.line.head.name) #확인용
                e1.destroy()
                b1.destroy()

            e1 = ttk.Entry(new) # 새로 생성
            b1 = ttk.Button(new, text = 'Enter', command = enter)

            #둘다 place로 고치기
            e1.place(x=100, y=120, width = 200)
            b1.place(x=100, y=150, width = 200)
            #사라지기
            e1.destroy()
            b1.destroy()

        new = Toplevel(self.master)
        new.title("Roller coaster")
        new.geometry('500x500')

        b1 = ttk.Button(new, text = 'Enqueue', command = line_enqueue)
        b2 = ttk.Button(new, text = 'Dequeue', command = line_dequeue)
        b3 = ttk.Button(new, text = 'Delete', command = line_delete)
        #place로 수정
        b1.place(x=100, y=10, width = 200)
        b2.place(x=100, y=50, width = 200)
        b3.place(x=100, y=100,width = 200)

window = Tk()
test = Mainframe(master = window)
line = Queue()
roller = Ride(line, 10, 5) #1회 탑승인원 10명, 탑승시간 5분

window.mainloop()