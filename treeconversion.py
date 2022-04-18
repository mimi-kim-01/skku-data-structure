class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.degree = 0
        self.level = 0

class Tree:
    def __init__(self):
        self.root = None
        self.num = 0

    def insert_first(self, parent, data):
        new = Node(data)
        if parent.left is None:
            parent.left = new
        else:
            crnt = parent.left
            while crnt.right is not None:
                crnt = crnt.right
            crnt.right = new
        self.num += 1
        new.level = parent.level + 1
        parent.degree += 1
    
    def insert_next(self, sibling, data):
        new = Node(data)
        crnt = sibling
        while crnt.right is not None:
            crnt = crnt.right
        crnt.right = new
        self.num += 1
        new.level = crnt.level + 1

    def print_tree(self, one, two):
        if self.num == 0:
            print("THE TREE IS EMPTY!")
            return
        crnt = two.left
        if one == two:
            print("lv%d: %c" %(one.level, one.data))
        if one.left is None:
            return
        while crnt is not None:
            print("lv%d: %c" %(crnt.level, crnt.data))
            if crnt.left is not None:
                self.print_tree(one, crnt)
            crnt = crnt.right
    
    def search(self, node, data):
        if node is None: return None
        if node.data == data: return node
        crnt = self.search(node.left, data)
        if crnt is not None: return crnt
        crnt = self.search(node.right, data)
        if crnt is not None: return crnt
        return None

print('''  <<<CONVERT GENERAL TREE TO BINARY TREE!>>>
CREATE                      | +(r)
INSERT CHILD                | +p(c1, c2, ...))
QUIT                        | Q''')

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
                    i += 3
                    tree.insert_first(node, request[i])
                    i += 1
                    while request[i] != ')':
                        find = tree.search(tree.root, request[i-1])
                        tree.insert_next(find, request[i])
                        i += 1
    tree.print_tree(tree.root, tree.root)