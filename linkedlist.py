#menu
def view():
    print("-----------------MENU-----------------")
    print("GET DATA                    | G")
    print("TRAVERSE FRONT              | <")
    print("TRAVERSE REAR               | >")
    print("MOVE TO POSITION(n)         | n")
    print("DELETE                      | -")
    print("ADD TO TAIL                 | T+(data)") 
    print("ADD PREVIOUS                | +(data)")
    print("ADD NEXT                    | N+(data)")
    print("REPLACE DATA                | =(data)")
    print("DATA COUNT                  | #")
    print("IS MEMBER                   | ?(data)")
    print("IS EMPTY                    | E")
    print("CLEAR LIST                  | C")
    print("TO UPPER CASE               | U")
    print("TO LOWER CASE               | D")
    print("VIEW MENU                   | V")
    print("QUIT                        | Q")
    print("===SOME WARNINGS TO KEEP IN MIND===")
    print("* n is a NUMBER, not an alphabet.")
    print("* SPACING between COMMANDS.")
    print("* ONLY 1 data per 1 command.")

#linkedlist
class Node: #doubly
    def __init__(self, data):
        self.data = None
        self.prev = None
        self.next = None

class List:
    def __init__(self):
        new = Node(None)
        self.head = new
        self.len = 0
        self.current = self.head

    def addTail(self, data):
        new = Node(data)
        while self.current.next is not None:
            self.current = self.current.next
        self.current.next = new
        new.prev = self.current
        self.current = new
        self.len += 1
       
    def add(self, data, count):
        new = Node(data)
        if count is None:
            new.data = data
            new.next = self.current
            self.current.prev = new.next
            self.len += 1
            self.current = new
        elif count == 'N':
            new.data = data
            new.next = self.current.next
            self.current.next = new
        self.current = new
        self.len += 1
    
    def replace(self, new):
        self.current.data = new
    
    def data_count(self):
        return self.len

    def is_member(self, data):
        search = self.head
        for i in range(0, self.len):
            search = search.next
            if search.data == data:
                return i+1
        return -1

    def is_empty(self):
        if self.len == 0:
            return 1
        else:
            return 0

    def delete(self):
        if self.is_empty() is True:
            print("THE LIST IS EMPTY")
            return -1
        else:
            self.current.prev.next = self.current.next
            self.current.next.prev = self.current.prev
        self.len -= 1
        self.current = self.current.next
    
    def clear(self):
        while self.is_empty() is False:
            self.delete()
        
    def upper(self):
        self.current.data = self.current.data.upper()

    def lower(self):
        self.current.data = self.current.data.lower()
       
    def get_data(self):
        if self.is_empty() is True:
            print("THE LIST IS EMPTY!")
            return -1
        return self.current.data
    
    def traverse_front(self, count):
        self.current = self.head
        for i in range(1, count+1):
            self.current = self.current.next
    
    def traverse_rear(self, count):
        while self.current.next is not None:
            self.current = self.current.next
        for i in range(1, count+1):
            self.current = self.current.prev
    
    def move_position(self, index):
        index = int(index)
        self.current = self.head
        for i in range(1, index+1):
            self.current = self.current.next
    
    def print_list(self):
        if self.is_empty() is True:
            print("THE LIST IS EMPTY!")
            return
        idx = self.head.next
        while idx != None:
            if idx == self.current:
                print("[", idx.data, "]", end = ' ')
            else: print(idx.data, end = ' ')
            idx = idx.next
        print()

#main
llist = List()
view()
while True:
    llist.print_list()
    request = input(">>> ")
    if request[0] == 'Q':
        print("THIS PROGRAM WILL END SOON!")
        break
    i = 0
    while (i < len(request)):
        if request[i] == 'G':
            llist.get_data(request[i+1])
            i += 1
        elif request[i] == '>':
            cnt = 0
            i += 1
            for j in range(10):
                if (request[i+j] != 'N'): break
                cnt += 1
                i += 1
            llist.traverse_front(cnt)
        elif request[i] == '<':
            cnt = 0
            i += 1
            for j in range(10):
                if (request[i+j] != 'P'): break
                cnt += 1
                i += 1
            llist.traverse_rear(cnt)
        elif request[i] == '-':
            llist.delete()
        elif request[i] == 'T':
            llist.addTail(request[i+2])
            i += 2
        elif request[i] == '+':
            llist.add(request[i+1], None)
            i += 1
        elif request[i] == 'N':
            llist.add(request[i+2], 'N')
            i += 2
        elif request[i] == '=':
            llist.replace(request[i+1])
        elif request[i] == '#':
            result = llist.data_count()
            print(result)
        elif request[i] == '?':
            result = llist.is_member(request[i+1])
            i += 1
            if result == -1: print("FAILED")
            else: print("%d: " %result)
        elif request[i] == 'E':
            result = llist.is_empty()
            if result == 1: print("True")
            else: print("False")
        elif request[i] == 'C':
            llist.clear()
            print("LIST IS CLEARED")
        elif request[i] == 'U':
            llist.upper()
        elif request[i] == 'D':
            llist.lower()
        elif request[i] == 'V':
            view()
        else:
            llist.move_position(request[i])
        i += 1