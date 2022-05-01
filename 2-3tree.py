class Node:
    def __init__(self, data, parent = None):
        self.data = list([data])
        self.child = []
        self.parent = parent
        
    def is_leaf(self):
        if len(self.child) == 0:
            return True
        else: return False
    
    def add_node(self, new):
        for child in new.child:
            child.parent = self
        self.data.extend(new.data)
        self.data.sort()
        self.child.extend(new.child)
        self.child.sort()
        if len(self.data) >= 3:
            self.split()
    
    def insert_node(self, new):
        if self.is_leaf() is True:
            self.add_node(new)
        elif new.data[0] > self.data[-1]:
            self.child[-1].insert_node(new)
        else:
            for i in range(len(self.data)):
                if new.data[0] < self.data[i]:
                    self.child[i].insert_node(new)
                    break
    
    def search_node(self, data):
        if data in self.data:
            return data
        elif self.is_leaf():
            return False
        elif data > self.data[-1]:
            return self.child[-1].search_node(data)
        else:
            for i in range(len(self.data)):
                if data < self.data[i]:
                    return self.child[i].search_node(data)
    
    def split(self):
        left = Node(self.data[0], self)
        right = Node(self.data[2], self)
        if len(self.child) != 0:
            left.child.extend(self.child[0], self.child[1])
            right.child.extend(self.child[2], self.child[3])
            self.child[0].parent = left
            self.child[1].parent = left
            self.child[2].parent = right
            self.child[3].parent = right
        self.data = [self.data[1]]
        self.child = [left, right]
        if self.parent:
            if self in self.parent.child:
                self.parent.child.remove(self)
            self.parent.add_node(self)
        else:
            left.parent = self
            right.parent = self
        
    def preorder(self):
        for data in self.data:
            print(data, end = ' ')
        for child in self.child:
            child.preorder()
    
    def traversal(self, list):
        for data in self.data:
            list.append(data)
        for child in self.child:
            child.traversal(list)
        
class Tree:
    def __init__(self):
        self.root = None
        self.num = 0
    
    def insert(self, data):
        if self.root is None:
            self.root = Node(data)
        else:
            self.root.insert_node(Node(data))
            while self.root.parent:
                self.root = self.root.parent
        self.num += 1

    def delete_node(self, data):
        self.root.remove(data)
        tree.num -= 1
    
    def inorder_traversal(self, node):
        list = []
        self.root.traversal(list)
        list.sort()
        print(list)
    
    def right_root_left_traversal(self, node):
        list = []
        self.root.traversal(list)
        list.sort(reverse = True)
        print(list)

    def preorder_traversal(self, node):
        if self.num == 0:
            print("THE 2-3 TREE IS EMPTY!")
            return
        self.root.preorder()

    def get_min(self):
        list = []
        self.root.traversal(list)
        list.sort()
        print("MIN:", list[0])
    
    def get_max(self):
        list = []
        self.root.traversal(list)
        list.sort(reverse = True)
        print("MAX:", list[0])
    
    def clear(self):
        self.num = 0
        self.root = None

def view():
    print("---------------------MENU---------------------")
    print("CREATE                      | +(n)")
    print("INSERT NODE                 | +(n)")
    print("DELETE NODE                 | -(n)")
    print("INORDER TRAVERSE            | I")
    print("RIGHT ROOT LEFT TRAVERSE    | R")
    print("GET MIN                     | N")
    print("GET MAX                     | X")
    print("COUNT NODE                  | #")
    print("PRINT 2-3 TREE              | P")
    print("CLEAR 2-3 TREE              | C")
    print("QUIT                        | Q")
    print("VIEW MENU                   | V")
    print("===SOME WARNINGS TO KEEP IN MIND===")
    print("* 1. Do not use brackets.")
    print("* 2. No spacing between commands.")

tree = Tree()
view()
while True:
    tree.preorder_traversal(tree.root)
    print()
    request = input(">>> ")
    if request[0] == 'Q':
        print("THIS PROGRAM ENDS SOON")
        break
    for i in range(len(request)):
        if request[i] == '+':
            if len(request) == 2:
                tree.insert(int(request[1:]))
        elif request[i] == 'P':
            tree.preorder_traversal(tree.root) 
            print()   
        elif request[i] == '#':
            print("NODE COUNT:", tree.num)
        elif request[i] == '-':
            tree.delete_node(request[i+1])
        elif request[i] == 'I':
            tree.inorder_traversal(tree.root)
        elif request[i] == 'R':
            tree.right_root_left_traversal(tree.root)
        elif request[i] == 'N':
            tree.get_min()
        elif request[i] == 'X':
            tree.get_max()
        elif request[i] == 'C':
            tree.clear()
        elif request[i] == 'V':
            view()