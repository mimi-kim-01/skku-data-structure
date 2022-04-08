#menu
def view():
    print("-----------------MENU-----------------")
    print("ENQUEUE                     | +(data)")
    print("DEQUEUE                     | -")
    print("PEEK                        | P")
    print("HEAD                        | H")
    print("TAIL                        | T")
    print("REPLACE DATA                | =(data)")
    print("DATA COUNT                  | #")
    print("IS MEMBER                   | ?(data)")
    print("IS FULL                     | F") #dynamic, so never full
    print("CLEAR QUEUE                 | C")
    print("TO UPPER CASE               | U")
    print("TO LOWER CASE               | D")
    print("VIEW MENU                   | V")
    print("PRINT QUEUE                 | L")
    print("QUIT                        | Q")
    print("===SOME WARNINGS TO KEEP IN MIND===")
    print("* SPACING between COMMANDS.")
    print("* ONLY 1 element per 1 command.")
    print("* 5- means DEQUEUE FOR 5 TIMES.")

#queue
class Queue: 
    def __init__(self):
        self.data = []
        self.tail = -1
        self.head = -1
        self.num = 0

    #functions
    def is_empty(self):
        if self.num == 0: return 1
        else: return 0
    
    def is_member(self, data):
        for i in range(self.num):
            if self.data[self.head+i+1] == data: return 1
        return 0
    
    def enqueue(self, data):
        self.data.append(data)
        self.tail += 1
        self.num += 1
    
    def dequeue(self):
        if self.is_empty() == 1: 
            print("NOTHING TO DEQUEUE!")
            return '~'
        dequeued = self.data[self.head+1]
        self.head += 1
        self.num -= 1
        return dequeued
    
    def peek(self):
        if self.is_empty() == 1:
            print("THE QUEUE IS EMPTY!")
            return 0
        else: return self.data[self.head+1]
    
    def replace(self, newdata):
        self.data[self.tail] = newdata
    
    def data_count(self):
        if self.is_empty() == 1:
            print("THE QUEUE IS EMPTY!")
            return 0
        else: print("DATA COUNT:", self.num)
    
    def print_queue(self):
        for i in range(self.num):
            print(self.data[self.head+i+1], end=' ')
        print()

#main
queue = Queue()
view()
while True:
    queue.print_queue()
    request = input(">>> ")
    if request[0] == 'Q':
        print("THIS PROGRAM WILL END SOON!")
        break
    i = 0
    while i < len(request):
        if request[i] == '+':
            queue.enqueue(request[i+1])
            i += 1
        elif request[i] == '-':
            print("DEQUEUED ELEMENT:", queue.dequeue())
        elif request[i] == 'P':
            result = queue.peek()
            if result != 0: print("CURRENT HEAD:", result)
        elif request[i] == 'F':
            print("THIS QUEUE IS DYNAMIC, SO IT CANNOT BE FULL.")
        elif request[i] == 'E':
            result = queue.is_empty()
            if result == 1: print("True")
            else: print("False")
        elif request[i] == '?':
            result = queue.is_member(request[i+1])
            if result == 1: print("True")
            else: print("False")
            i += 1
        elif request[i] == '#':
            queue.data_count()
        elif request[i] == 'H':
            print("CURRENT HEAD:", queue.head + 2)
        elif request[i] == 'T':
            print("CURRENT TAIL:", queue.tail + 1)
        elif request[i] == '=':
            queue.replace(request[i+1])
            i += 1
        elif request[i] == 'C':
            queue.__init__()
            print("THE QUEUE IS CLEARED!")
        elif request[i] == 'U':
            queue.data[queue.tail] = queue.data[queue.tail].upper()
        elif request[i] == 'D':
            queue.data[queue.tail] = queue.data[queue.tail].lower()
        elif request[i] == 'L':
            break
        elif request[i] == 'V':
            view()
        else:
            for i in range(int(request[i])):
                print("DEQUEUED ELEMENT:", queue.dequeue())
        i += 2