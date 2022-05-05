#user
class User:
    def __init__(self, name, phone, magic):
        self.name = name
        self.phone = phone
        self.magic = magic
        self.prev = None
        self.next = None

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
    
    def delete(self, phone, magic):
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
        crnt = self.line.head 
        for i in range(self.line.len2):
            print(crnt.name, end = ' ')
            print(crnt.phone, end = ' ')
            print(crnt.magic, end = ' ')
            print()
            crnt = crnt.next

#ride
class Ride:
    def __init__(self, queue, num, time):
        self.line = queue
        self.time1 = None #waiting time for no magic pass
        self.time2 = None #waiting time for magic pass
        self.num = num #num per ride
        self.time = time #time per ride (include break time)
    
    def get_time(self):
        self.time1 = int((self.line.len1 / self.num) * self.time)
        self.time2 = int((self.line.len2 / self.num) * self.time)

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
        '''이거 스타일 예쁘게 고치기..!
        self.style = ttk.Style()
        
        self.style.map("Tbutton",
        foreground = [('pressed', 'orchid'), ('active', 'thistle')])
        self.style.configure("TButton", width = 10)
        '''
        self.b1 = ttk.Button(self.master, text = 'Add User', command = self.add_user)
        
        self.l1 = ttk.Label(self.master, text = 'Ride1')

        self.b1.place(x = 200, y = 200)
        self.l1.place(x = 100, y = 100)
    
    def add_user(self): #user 네임을 정해줘야할듯?? 왜냐면 enqueue할때 그게 필요함
        def new_user():
           name = e1.get()
           phone = e2.get()
           magic = CheckVar.get()  
           username = name
           username = User(name, phone, magic)   
           print(username.name)

        new = Toplevel(self.master)
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
    

window = Tk()
test = Mainframe(master = window)
window.mainloop()