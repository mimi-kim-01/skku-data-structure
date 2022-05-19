#user list
Userlist = []
Phonelist = []

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
        Phonelist.append(self.phone)

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
            return -1

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

#tkinter
from tkinter import *
from tkinter import ttk

class Mainframe(ttk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.master = master
        master.title("Welcome to Queuetie Land!")
        master.geometry('500x500')
        self.create_widgets()
    
    def create_widgets(self):
        style = ttk.Style()
        style.theme_use('alt')
        style.configure('TButton', font=('American typewriter', 14), background='#fcbbe8', foreground='white')
        style.map('TButton', background=[('active', '#f558dd')])
        
        self.subtitle = ttk.Label(self.master, text = 'Welcome to', font = ('Arial', 15))
        self.title1 = ttk.Label(self.master, text = 'QUEUETIE LAND', font = ('Arial', 30))

        self.b1 = ttk.Button(self.master, text = 'Add User', command = self.add_user)
        self.b2 = ttk.Button(self.master, text = 'Show Line', command = self.show_line)
        self.b3 = ttk.Button(self.master, text = 'Enqueue', command = self.line_enqueue)
        self.b4 = ttk.Button(self.master, text = 'Dequeue', command = self.line_dequeue)
        self.b5 = ttk.Button(self.master, text = 'Delete', command = self.line_delete)

        self.subtitle.place(x = 110, y = 50)
        self.title1.place(x = 110, y = 90)
        self.b1.place(x = 200, y = 200)
        self.b2.place(x= 200, y = 250)
        self.b3.place(x = 200, y = 300)
        self.b4.place(x = 200, y = 350)
        self.b5.place(x = 200, y = 400)
        
    def add_user(self): 
        def new_user():
           name = e1.get()
           phone = e2.get()
           magic = CheckVar.get()   

           username = phone
           username = User(name, phone, magic)   
           username.add_to_list(Userlist)

           e1.delete(0,END)
           e2.delete(0,END)

        new = Toplevel(self.master)
        new.title("User")
        new.geometry('250x200')

        l1 = ttk.Label(new, text = 'Name')
        l2 = ttk.Label(new, text = 'Phone')
        l3 = ttk.Label(new, text = 'Magic')

        CheckVar = BooleanVar()

        e1 = ttk.Entry(new)
        e2 = ttk.Entry(new)
        c1 = ttk.Checkbutton(new, text = 'Yes', variable = CheckVar, onvalue = True, offvalue = False)

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
        new.geometry('250x250')

        roller.get_time()

        l1 = ttk.Label(new, text = "-- Current Line Info --")
        l2 = ttk.Label(new, text = 'Waiting number(Magic pass): ' + str(roller.line.len1) +'\nWaiting number(Whole): ' + str(roller.line.len2))
        l3 = ttk.Label(new, text = 'Waiting time(Magic pass): ' + str(roller.time1) + '\nWaiting time(Whole): ' + str(roller.time2))
        l4 = ttk.Label(new, text = '-- Phone Number List --')

        l1.place(x = 75, y = 0)
        l2.place(x = 50, y = 30)
        l3.place(x = 50, y = 70)
        l4.place(x = 72, y = 120)

        crnt = roller.line.head
        i = 0

        while crnt is not None:
            cc = crnt.name
            cc = ttk.Label(new, text = crnt.phone)
            cc.place(x = 30 + i, y = 145)
            crnt = crnt.next
            i += 20
    
    def line_enqueue(self):
        def enter():
            phone = e1.get()

            if phone not in Phonelist:
                l2 = ttk.Label(new, text = "Error: Wrong information.")
                l2.place(x=30, y=150, width=200) 

            elif roller.line.search(phone) is not None:
                l3 = ttk.Label(new, text = "Error: Already in line.")
                l3.place(x = 30, y=150, width=200) 

            else: 
                for i in range(len(Userlist)):
                    if phone == Userlist[i][1]:
                        user = User(Userlist[i][0], Userlist[i][1], Userlist[i][2])
                        roller.line.enqueue(user)
                        break

                l4 = ttk.Label(new, text = "Added.")
                l4.place(x = 30, y = 150, width = 200)

                crnt = roller.line.head
                i = 0

                while crnt is not None:
                    cc = crnt.name
                    cc = ttk.Label(new, text = crnt.phone)
                    cc.place(x = 30 + i, y = 170)
                    crnt = crnt.next
                    i += 20
            
            e1.delete(0,END)

        new = Toplevel(self.master)
        new.title("Enqueue")
        new.geometry('250x300')

        l1 = ttk.Label(new, text = "Insert Phone number")
        e1 = ttk.Entry(new) 
        b1 = ttk.Button(new, text = 'Enter', command = enter)
        
        l1.place(x = 30, y = 10, width = 150)
        e1.place(x = 30, y = 50, width = 200)
        b1.place(x = 30, y = 90, width = 100)          

    def line_dequeue(self):
        for i in range(roller.num):
            if roller.line.len2 == 0: 
                return
            roller.line.dequeue()

    def line_delete(self):
        def enter():
            phone = e1.get()
            result = roller.line.delete(phone)

            if result == -1:
                l3 = ttk.Label(new, text = "Error: Wrong information.")
                l3.place(x = 30, y = 150, width = 200)

            else:
                l4 = ttk.Label(new, text = "Deleted.")
                l4.place(x=30, y =150, width = 200)

            e1.delete(0,END)

        new = Toplevel(self.master)
        new.title("Delete")
        new.geometry('250x300')

        l1 = ttk.Label(new, text = "Insert Phone number")
        e1 = ttk.Entry(new) 
        b1 = ttk.Button(new, text = 'Enter', command = enter)
        
        l1.place(x = 30, y = 10, width = 150)
        e1.place(x = 30, y = 50, width = 200)
        b1.place(x = 30, y = 90, width = 100)         

window = Tk()
test = Mainframe(master = window)

line = Queue()
roller = Ride(line, 2, 5) #1회 탑승인원 2명, 탑승시간 5분

window.mainloop()