class User:
    def __init__(self, name, phone, magic):
        self.name = None
        self.phone = None
        self.magic = None
        self.prev = None
        self.next = None
    
class Queue:
    def __init__(self):
        new = User(None)
        self.head = new
        self.len1 = 0 #magic pass
        self.len2 = 0 #all
        self.cur1 = self.head #magic pass
        self.cur2 = self.head #no magic pass
    
    def insert(self, name, phone, magic):
        new = User(name, phone, magic)
        if magic:
            new.prev = self.cur1
            new.next = self.cur1.next
            self.cur1 = new
            self.len1 += 1
        else: 
            new.prev = self.cur2
            new.next = None
            self.cur2 = new
        self.len2 += 1