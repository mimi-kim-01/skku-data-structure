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

    def enqueue(self, new): #cur1이랑 cur2연결이 잘 안되는듯, len1==len2일떄 next연결이 잘 안됨
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
        else: 
            if self.len2 == self.len1:
                self.cur1.next = new
                new.prev = self.cur1
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
        self.head += 1
        self.len2 -= 1      
    
    def delete(self, name, phone, magic):
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