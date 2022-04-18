from socket import CAN_RTR_FLAG


class Node:
    def __init__(self, data):
        self.data = data
        self.parent = None
        self.left = None
        self.right = None
        self.degree = 0
        self.level = 0

class Tree:
    def __init__(self):
        self.root = None
        self.num = 0
    
    def create(self, root):
        root = Node(root)
        tree = Tree()
        tree.root = root
        tree.num += 1
        i += 1

    def insert_child(self, node, data, bin):
        new = Node(data)
        if bin:
            if node.left != None and node.right != None:
                print("CANNOT INSERT [%c]" %(data))
                return
            if node.left is None:
                node.left = new
            elif node.right is None:
                node.right = new
        else:
            if node.left is None:
                node.left = new
            else:
                crnt = node.left
                while crnt.right is not None:
                    crnt = crnt.right
                crnt.right = new
        new.parent = node
        new.level = node.level + 1
        node.degree += 1
        self.num += 1
    
    def insert_sibling(self, node, data, bin):
        if self.num == 0:
            print("THE TREE IS EMPTY!")
            return
        crnt = node
        if crnt is None:
            print("[%c] IS NOT IN THE TREE!" %(crnt.data))
            return
        elif crnt == self.root:
            print("[%c] IS THE ROOT NODE!" %(crnt.data))
            return
        crnt = crnt.parent
        sib = Node(data)
        sib.parent = crnt
        sib.level = crnt.level + 1
        if bin == 0:
            crnt = crnt.left
            while crnt.right is not None:
                crnt = crnt.right
                crnt.right = sib
        else:
            if crnt.left is None:
                crnt.left = sib
            elif crnt.right is None:
                crnt.right = sib
            else:
                print("CANNOT INSERT [%c]" %(data))
                return
        self.num += 1 
    
    def get_child(self, parent, bin):
        if self.num:
            print("THE TREE IS EMPTY!")
            return
        crnt = self.search(self.root, parent)
        if crnt is None:
            print("[%c] IS NOT IN THE TREE!" %(parent))
            return
        if crnt.data == parent:
            if crnt.left is None:
                print("[%c] DOES NOT HAVE CHILD!" %(parent))
                return
            if bin == 0:
                crnt = crnt.left
                print("{%c" %(crnt.data), end = '')
                while True:
                    if crnt.right is None: break
                    crnt = crnt.right
                    print(",%c" %(crnt.data), end = '')
            else:
                temp = crnt.left
                print("{%c" %(temp.data), end = '')
                if crnt.right is not None:
                    crnt = crnt.right
                    print(",%c" %(crnt.data), end = '')
            print("}")

    def get_parent(self, child):
        if self.num == 0:
            print("THE TREE IS EMPTY!")
            return
        crnt = self.search(self.root, child)
        if crnt is None:
            print("[%c] IS NOT IN THE TREE!" %(child))
            return
        if crnt.data == child:
            if crnt.parent is None:
                print("[%c] IS THE ROOT NODE!" %(child))
                return
            print("[%c] IS THE PARENT NODE OF [%c]" %(crnt.parent.data, child))
    
    def get_sibling(self, sib, bin):
        if self.num == 0:
            print("THE TREE IS EMPTY!")
            return
        idx = 0
        crnt = self.search(self.root, sib)
        if crnt is None:
            print("[%c] IS NOT IN THE TREE!" %(sib))
            return
        elif crnt == self.root:
            

    
    def search(self, node, data):
        if node is None: return None
        if node.data == data: return node
        crnt = self.search(node.left, data)
        if crnt is not None: return crnt
        crnt = self.search(node.right, data)
        if crnt is not None: return crnt
        return None
    
    def level_of_node(self, node):
        return node.level
    
    def degree_of_node(self, node):
        return node.degree
    
    def level_of_tree(self, root, node):
        if node is not None:
            self.level_of_tree(root, node.left)
            self.level_of_tree(root, node.right)
            if self.level_of_node(root, node) > self.level:
                self.level = self.level_of_node(root, node)
        return self.level
    
    def degree_of_node(self, root, node):
        if node is not None:
            self.degree_of_tree(root, node.left)
            self.degree_of_tree(root, node.right)
            if self.degree_of_node(root, node) > self.degree:
                self.degree = self.degree_of_node(root, node)
        return self.degree

def view():
    print("이따가 수정하기")

bin = int(input("CHOOSE YOUR TREE TYPE(0: GENERAL, 1: BINARY)\n>>> "))
while True:
    request = input(">>> ")
    if request[0] == 'Q':
        print("THIS PROGRAM ENDS SOON")
        break
    for i in range(len(request)):
        if request[i] == '+':
            if len(request) == 2:
                root = Node(request[i+1])
                tree = Tree()
                tree.root = root
                tree.num += 1
                i += 1
            elif request[i+2] == '(':
                node = tree.search(tree.root, request[i+1])
                if node is None:
                    print(f"{request[i+1]} IS NOT IN TREE!")
                else:
                    print()
                       


    tree.print_tree(tree.root, tree.root)
    print()