#user
class User:
    def __init__(self, name, phone, magic):
        self.name = None
        self.phone = None
        self.magic = None
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
    def enqueue(self, new): #처음에 enqueue하는거 따로 만들기??
        if new.magic:
            new.prev = self.cur1
            new.next = self.cur1.next
            self.cur1 = new
            self.len1 += 1
        else: 
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
    def __init__(self, queue):
        self.line = queue
        self.time1 = None #waiting time for no magic pass
        self.time2 = None #waiting time for magic pass
        self.num = None #num per ride
        self.time = None #time per ride (include break time)
    
    def time(self):
        self.time1 = (self.line.len1 / self.num) * self.time
        self.time2 = (self.line.len2 / self.num) * self.time