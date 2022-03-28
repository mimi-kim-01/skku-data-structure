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
    print("PRINT LIST                  | L")
    print("QUIT                        | Q")
    print("===SOME WARNINGS TO KEEP IN MIND===")
    print("* n is a NUMBER, not an alphabet.")
    print("* SPACING between COMMANDS.")
    print("* ONLY 1 data per 1 command.")
    print("* TRAVERSE cannot be used with other options.")
    print("* < N means traverse front and move next.")
    print("* > P means traverse rear and move previous.")

#linkedlist
class Node: 
    def __init__(self, data):
        self.data = data
        self.prev = None
        self.next = None

class List: #doubly
    def __init__(self):
        new = Node(None)
        self.head = new
        self.len = 0
        self.current = self.head

    #functions
    def addTail(self, data):
        new = Node(data)
        while self.current.next is not None:
            self.current = self.current.next
        self.current.next = new
        new.prev = self.current
        self.current = new
       
    def add(self, data, count):
        new = Node(data)
        if count == '0':
            if (self.len == 0):
                self.addTail(data)
            else:
                new.next = self.current
                new.prev = self.current.prev
                self.current.prev.next = new
                self.current.prev = new
                self.current = new
        elif count == 'N':
            new.prev = self.current
            new.next = self.current.next
            self.current.next = new
            self.current = self.current.next
    
    def replace(self, new):
        self.current.data = new
    
    def data_count(self):
        return self.len

    def is_member(self, data):
        search = self.head.next
        for i in range(0, self.len):
            if search.data == data:
                return i + 1
            search = search.next
        return -1

    def is_empty(self):
        if self.len == 0:
            return 1
        else:
            return 0

    def delete(self):
        if self.len == 0:
            print("THE LIST IS EMPTY")
            return 
        elif self.len == 1: #delete the last remaining
            self.current = self.head
            self.current.next = None
        else:
            if self.current.next is None: #delete the last
                self.current.prev.next = None
                self.current = self.head.next
            else:
                self.current.prev.next = self.current.next
                self.current.next.prev = self.current.prev
                self.current = self.current.next
        self.len -= 1
    
    def clear(self):
        while self.len != 0:
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
        self.current = self.head.next
        if count != 0:
            for i in range(count):
                self.current = self.current.next
    
    def traverse_rear(self, count):
        self.current = self.head.next
        while self.current.next is not None:
            self.current = self.current.next
        if count != 0:
            for i in range(count):
                self.current = self.current.prev
    
    def move_position(self, index):
        index = int(index)
        self.current = self.head
        for i in range(index):
            self.current = self.current.next
    
    def print_list(self):
        if self.len == 0:
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
print("Our group decided to differentiate the input forms of ADD function")
print("PLEASE READ OUR MENU CAREFULLY!")
view()
while True:
    llist.print_list()
    request = input(">>> ")
    if request[0] == 'Q':
        print("THIS PROGRAM WILL END SOON!")
        break
    i = 0
    while i < len(request):
        if request[i] == 'G':
            result = llist.get_data()
            print("CURRENT DATA:", result)
        elif request[i] == '<':
            cnt = 0
            if (len(request) != 1 and request[i+2] == 'N'):
                i += 1
                for j in range(1, len(request)-1, 2):
                    if (request[i+j] != 'N'): break
                    cnt += 1
            i += cnt*2
            llist.traverse_front(cnt)
        elif request[i] == '>':
            cnt = 0
            if (len(request) != 1 and request[i+2] == 'P'):
                i += 1
                for j in range(1, len(request)-1, 2):
                    if (request[i+j] != 'P'): break
                    cnt += 1
            i += cnt*2
            llist.traverse_rear(cnt)
        elif request[i] == '-':
            llist.delete()
        elif request[i] == 'T':
            llist.addTail(request[i+2])
            llist.len += 1
            i += 2
        elif request[i] == '+':
            llist.add(request[i+1], '0')
            llist.len += 1
            i += 1
        elif request[i] == 'N':
            llist.add(request[i+2], 'N')
            i += 2
        elif request[i] == '=':
            llist.replace(request[i+1])
            i += 1
        elif request[i] == '#':
            result = llist.data_count()
            print("DATA COUNT:", result)
        elif request[i] == '?':
            result = llist.is_member(request[i+1])
            i += 1
            if result == -1: print("FAILED")
            else: print("%d: " %result, end = '')
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
        elif request[i] == 'L':
            break
        elif request[i] == 'V':
            view()
        else:
            llist.move_position(request[i])
        i += 2