class Node:
    def __init__(self, data = []):
        self.data = data
        self.left, self.mid, self.right = None, None, None
        self.parent = None
    
    def is_leaf(self):
        if self.left is None and self.mid is None and self.right is None:
            return True
        else: return False
    
    def insert(self, value):
        self.data.append(value)
        if len(self.data) > 1:
            self.data.sort()
        return
    
class Tree:
    def __init__(self, values = []):
        self.root = None
        self.num = 0
        for value in values:
            self.add(value)
    
    def add(self, value):
        if self.root is None:
            self.root = Node([value])
            self.num += 1
            return
        node = self.valid(self.root, value)
        node.insert(value)
        self.rebalance(node)
        self.num += 1
        return
    
    def valid(self, node, value):
        if node.is_leaf():
            return node
        path = self.path(node, value)
        if path == 'left':
            return self.valid(node.left, value)
        elif path == 'mid':
            return self.valid(node.mid, value)
        elif path == 'right':
            return self.valid(node.right, value)
        return node
    
    def path(self, node, value):
        if len(node.data) == 1:
            if value < node.data[0]:
                return 'left'
            elif value > node.data[0]:
                return 'right'
        elif len(node.data) == 2:
            if value < node.data[0]:
                return 'left'
            elif value > node.data[1]:
                return 'right'
            elif node.data[0] < value < node.data[1]:
                return 'mid'
    
    def rebalance(self, node):
        if len(node.data) < 3: return
        if node.parent is None and node.is_leaf() is True:
            self.b_one(node)
            return
        path = self.path(node.parent, node.data[0])
        if path == 'mid':
            self.b_four(node)
        elif node.mid is not None:
            self.b_three(node, path)
            self.rebalance(node.parent)
        else:
            self.b_two(node, path)
            self.rebalance(node.parent)

    def b_one(self, node):
        if len(node.data) < 3: return
        min_val = node.data.pop(0)
        left = Node([min_val])
        max_val = node.data.pop
        right = Node([max_val])
        left.parent = node
        right.parent = node
        node.left = left
        node.right = right
        return
    
    def b_two(self, node, path):
        mid = node.data.pop(1)
        node.parent.insert(mid)
        if node.parent.mid is None:
            node.parent.mid = Node(None)
        if path == 'left':
            node.parent.mid.insert(node.data.pop())
        elif path == 'right':
            node.parent.mid.insert(node.data.pop(0))
        return
    
    def b_three(self, node, path):
        crnt = Node(node.data)
        self.b_one(crnt)
        crnt.left.left = node.left
        crnt.right.right = node.right
        crnt.left.right = Node([node.mid.data[0]])
        crnt.right.left = Node([node.mid.data[1]])
        if node.parent is None:
            self.root = crnt
            return
        crnt.parent = node.parent
        if path == 'left':
            crnt.parent.left = crnt
        elif path == 'mid':
            crnt.parent.mid = crnt
        elif path == 'right':
            crnt.parent.right = crnt
        node = crnt
        return
    
    def b_four(self, node):
        parent = node.parent
        crnt = Node(parent.data)
        crnt.parent = parent.parent
        mid = node.data.pop(1)
        crnt.insert(mid)
        self.b_one(crnt)
        parent.left.parent = crnt.left
        crnt.left.left = parent.left
        parent.right = parent = crnt.right
        crnt.right.right = parent.right
        crnt.left.right = Node([node.data.pop(0)])
        crnt.left.right.parent = crnt.left.right
        crnt.right.left = Node([node.data.pop()])
        crnt.right.left.parent = crnt.right.left
        node = crnt
        if crnt.parent is None:
            self.root = crnt
        return

tree = Tree()
while True:
    request = input(">>> ")
    if request[0] == 'Q':
        print("THIS PROGRAM ENDS SOON")
        break
    for i in range(len(request)):
        if request[i] == '+':
            if len(request) == 2:
                tree.add(int(request[i+1]))
        elif request[i] == '#':
            print("cnt: ", tree.num)