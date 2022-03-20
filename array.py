#functions
def menu():
    print("----------------MENU----------------")
    print("INSERT DATA                 | +(data)")
    print("DELETE                      | -")
    print("TRAVERSE_FRONT              | <")
    print("TRAVERSE_REAR               | >")
    print("PREVIOUS                    | P")
    print("NEXT                        | N")
    print("GET DATA                    | @")
    print("REPLACE DATA                | =(data)")
    print("EMPTY THE ARRAY             | E")
    print("MOVE TO POSITION            | M(position)")
    print("MOVE TO FRONT               | M")
    print("MOVE TO REAR                | Mn")
    print("MOVE TO PREVIOUS            | MP")
    print("MOVE TO NEXT                | MN")
    print("PRINT THE ARRAY             | L")
    print("TO UPPER CASE               | U")
    print("TO LOWER CASE               | D")
    print("VIEW MENU                   | V")
    print("QUIT                        | Q")
    print("===SOME WARNINGS TO KEEP IN MIND===")
    print("* Q should be used ALONE.")
    print("* SPACING between COMMANDS.")
    print("* ONLY 1 data per 1 command.")

def insert(arr, data):    
    global current
    global size
    current += 1
    if size == 30: #maximum is 30
        print("THE ARRAY IS FULL!")
    else:
        arr.insert(current, data)

def delete(arr):
    global current
    global size
    del arr[current]
    if current == size-1: current = 0

def move(arr, position):
    global current
    if current > position:
        for i in range(position, current, -1):
          arr[i], arr[i-1] = arr[i-1], arr[i]
    elif current < position:
        for i in range(current, position, 1):
          arr[i], arr[i+1] = arr[i+1], arr[i]
    current = position

def print_array(arr):
    global current
    global size
    if size == 0:
        print("THE ARRAY IS EMPTY!")
    else:
        for i in range(size):
            if i == current:
                print("["+arr[i]+"]", end=' ')
            else: 
                print(arr[i], end=' ')
        print()

#main
current = -1
size = 0
arr = [] #create array
menu()
while True: 
    size = len(arr)
    print_array(arr)
    request = input(">>> ")
    if request[0] == 'Q':
        print("THIS PROGRAM ENDS SOON")
        break
    for i in range(len(request)):
        if request[i] == '+':
            insert(arr, request[i+1])
            i += 1
        elif request[i] == '-':
            delete(arr)
        elif request[i] == '<':
            current = 0
        elif request[i] == '>':
            current = size-1
        elif request[i] == 'P':
            current -= 1
        elif request[i] == 'N':
            current += 1
        elif request[i] == '@':
            print("arr[%d]: %c" %(current, arr[current]))
        elif request[i] == '=':
            arr[current] = request[i+1]
            i += 1
        elif request[i] == 'E':
            arr.clear()
            current = -1
        elif request[i] == 'M':
            if request[i+1] is None: 
                move(arr, 0)
            elif request[i+1] == 'n':
                move(arr, size-1)
            elif request[i+1] == 'P':
                move(arr, current-1)
            elif request[i+1] == 'N':
                move(arr, current+1)
            else: move(arr, int(request[i+1]))
            i += 1
        elif request[i] == 'L':
            break
        elif request[i] == 'U':
            arr[current] = arr[current].upper()
        elif request[i] == 'D':
            arr[current] = arr[current].lower()
        elif request[i] == 'V':
            menu()