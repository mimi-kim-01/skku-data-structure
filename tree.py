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
        self.level = 0
        self.degree = 0

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
            sib.level = crnt.level
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
        if self.num == 0:
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
            print("[%c] IS THE ROOT NODE!" %(crnt.data))
            return
        find = crnt
        if bin == 0:
            crnt = crnt.parent.left
            print("{", end = '')
            if crnt != find:
                print("%c" %(crnt.data), end = '')
                idx = 1
            while True:
                if crnt.right is None: break
                crnt = crnt.right
                if crnt != find and idx == 0:
                    print("%c" %(crnt.data), end = '')
                    idx = 1
                elif crnt != find and idx == 1:
                    print(",%c" %(crnt.data), end = '')
            print("}")
        else :
            crnt = crnt.parent
            if crnt.left != find and crnt.left is not None:
                print("THE SIBLING OF [%c] IS [%c]" %(sib, crnt.left.data))
            elif crnt.right != find and crnt.right is not None:
                print("THE SiBLING OF [%c] IS [%c]" %(sib, crnt.right.data))
            else: print("[%c] DOES NOT HAVE SIBLING!" %(sib))
    
    def get_ancestors(self, node):
        if self.num == 0:
            print("THE TREE IS EMPTY!")
            return
        crnt = self.search(self.root, node)
        idx = 0
        if crnt is None:
            print("[%c] IS NOT IN THE TREE!" %(node))
            return
        if crnt.data == node:
            if crnt.parent is None:
                print("[%c] IS THE ROOT NODE!" %(node))
                return
            while True:
                crnt = crnt.parent
                if idx == 0:
                    print("{%c" %(crnt.data), end = '')
                    idx = 1
                else: print(",%c" %(crnt.data), end = '')
                if crnt == self.root: break
            print("}")

    def get_descendants(self, node, bin):
        if self.num == 0:
            print("THE TREE IS EMPTY!")
            return
        crnt = self.search(self.root, node)
        find = crnt
        if crnt is None:
            print("[%c] IS NOT IN THE TREE!" %(node))
            return
        if crnt.data == node:
            if crnt.left is None:
                print("[%c] DOES NOT HAVE CHILD!" %(node))
                return
            if bin == 0:
                crnt = crnt.left
                print("{%c" %(crnt.data), end = '')
                while crnt.left is not None:
                    crnt = crnt.left
                    print(",%c" %(crnt.data), end = '')
                temp = crnt
                while temp.right is not None:
                    if temp == find: break
                    while crnt.right is not None:
                        print(",%c" %(crnt.right.data), end = '')
                        crnt = crnt.right
                    temp = temp.parent
                    crnt = temp
                print("}")
            else:
                crnt = crnt.left
                print("{%c" %(crnt.data), end = '')
                print(",%c" %(crnt.parent.right.data), end = '')
            print("}")

    def delete_node(self, node, bin):
        if self.num == 0:
            print("THE TREE IS EMPTY!")
            return
        find = self.search(self.root, node)
        if find is None:
            print("[%c] IS NOT IN THE TREE" %(node))
            return
        if find == self.root:
            print("[%c] IS THE ROOT NODE" %(find.data))
            return
        if bin:
            if find.left is not None or find.right is not None:
                print("CANNOT DELETE [%c]" %(find.data))
                return
            crnt = find.parent
            if find.left is None:
                if crnt.left == find:
                    if crnt.right is not None:
                        crnt.left = None
                    else:
                        crnt.left = crnt.right
                        crnt.right = None
                else: crnt.right = None
        else:
            find = self.search(tree.root, node)
            crnt = find.parent
            if find.degree != 0:
                print("CANNOT DELETE [%c]" %(find.data))
                return
            if find.left is None:
                if crnt.left == find:
                    if crnt.right is not None:
                        crnt.left = None
                        crnt.left = find.right
                    else: crnt.left = find.right
                else:
                    prev = crnt.left
                    sib = prev
                    while True:
                        sib = sib.right
                        if sib.data == find.data: break
                        prev = prev.right
                    if find.right is None:
                        prev.right = None
                    else: prev.right = find.right
        find.parent.degree -= 1
        find = None
        self.num -= 1

    def print_tree(self, one, two, bin):
        if self.num == 0:
            print("THE TREE IS EMPTY!")
            return
        if bin:
            crnt = one
            print("lv%d: %c" %(one.level, one.data))
            if one.left is not None:
                self.print_tree(one.left, two, bin)
            if one.right is not None:
                while True:
                    crnt = crnt.right
                    print("lv%d: %c" %(crnt.level, crnt.data))
                    if crnt.left is not None:
                        self.print_tree(crnt.left, two, bin)
                    if crnt.right is None: break
        else:
            crnt = two.left
            if one == two:
                print("lv%d: %c" %(one.level, one.data))
            if one.left is None: return
            while crnt is not None:
                print("lv%d: %c" %(crnt.level, crnt.data))
                if crnt.left is not None: 
                    self.print_tree(one, crnt, bin)
                crnt = crnt.right
        
    def clear(self, node):
        if self.num == 0:
            print("THE TREE IS EMPTY!")
            return
        if node.left is not None:
            self.clear(node.left)
        elif node.right is not None:
            self.clear(node.right)
        if self.root == node:
            self.num = 0
            self.root = None
        node = None
    
    def level_up(self, node):
        if node is None: return
        else:
            node.level += 1
            self.level_up(node.left)
            self.level_up(node.right)

    def join_trees(self, root):
        if self.num == 0:
            print("THE TREE IS EMPTY!")
            return
        nroot = Node(root)
        crnt = self.root
        self.num += 1
        self.root = nroot
        nroot.left = crnt
        nroot.right = None
        self.level_up(crnt)

    def search(self, node, data):
        if node is None: return None
        if node.data == data: return node
        crnt = self.search(node.left, data)
        if crnt is not None: return crnt
        crnt = self.search(node.right, data)
        if crnt is not None: return crnt
        return None
    
    def level_of_node(self, node):
        find = self.search(tree.root, node)
        return find.level
    
    def degree_of_node(self, node):
        find = self.search(tree.root, node)
        return find.degree
    
    def level_of_tree(self, root, node):
        if node is not None:
            self.level_of_tree(self.root, node.left)
            self.level_of_tree(self.root, node.right)
            if node.level > self.level:
                self.level = node.level
        return self.level
    
    def degree_of_tree(self, root, node):
        if node is not None:
            self.degree_of_tree(self.root, node.left)
            self.degree_of_tree(self.root, node.right)
            if node.degree> self.degree:
                self.degree = node.degree
        return self.degree

def view():
    print("---------------------MENU---------------------")
    print("CREATE                      | +(r)")
    print("INSERT CHILD                | +p(c1, c2, ...))")
    print("INSERT SIBLING              | =+n(s1, s2, ...))")
    print("DELETE NODE                 | -(n)")
    print("GET PARENT                  | P(c)")
    print("GET CHILD                   | C(p)")
    print("GET SIBLING                 | S(n)")
    print("GET ANCESTORS               | A(n)")
    print("GET DESCENDANTS             | D(n)")
    print("LEVEL OF NODE               | L(n)")
    print("LEVEL OF TREE               | L")
    print("DEGREE OF NODE              | G(n)")
    print("DEGREE OF TREE              | G")
    print("COUNT NODE                  | #")
    print("PRINT TREE                  | T")
    print("JOIN TREES                  | J(r)")
    print("CLEAR TREE                  | K")
    print("QUIT                        | Q")
    print("===SOME WARNINGS TO KEEP IN MIND===")
    print("* p: PARENT, c: CHILD, s: SIBLING")
    print("* t: TREE, r: ROOT, n: NODE")
    print("* 1. No spacing between commands.")
    print("* 2. Do not use brackets.")

bin = int(input("CHOOSE YOUR TREE TYPE(0: GENERAL, 1: BINARY)\n>>> "))
view()
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
                break
            elif request[i+2] == '(':
                node = tree.search(tree.root, request[i+1])
                if node is None:
                    print(f"{request[i+1]} IS NOT IN TREE!")
                else:
                    i += 3
                    while request[i] != ')':
                        tree.insert_child(node, request[i], bin)
                        i += 1
                break
        elif request[i] == '-':
            tree.delete_node(request[i+1], bin)
            break
        elif request[i] == '=':
            node = tree.search(tree.root, request[i+2])
            tree.insert_sibling(node, request[i+4], bin)
            break
        elif request[i] == 'P':
            tree.get_parent(request[i+1])
            break
        elif request[i] == 'C':
            tree.get_child(request[i+1], bin)
            break
        elif request[i] == 'S':
            tree.get_sibling(request[i+1], bin)
            break
        elif request[i] == 'A':
            tree.get_ancestors(request[i+1])
            break
        elif request[i] == 'D':
            tree.get_descendants(request[i+1], bin)
            break
        elif request[i] == 'L':
            if len(request) == 1:
                print("LEVEL OF TREE IS %d" %(tree.level_of_tree(tree.root, tree.root)))
            else:
                print("LEVEL OF NODE [%c] IS %d" %(request[i+1], tree.level_of_node(request[i+1])))
            break
        elif request[i] == 'G':
            if len(request) == 1:
                print("DEGREE OF TREE IS %d" %(tree.degree_of_tree(tree.root, tree.root)))
            else:
                print("DEGREE OF NODE [%c] IS %d" %(request[i+1], tree.degree_of_node(request[i+1])))
            break
        elif request[i] == '#':
            print("NODE COUNT: %d" %(tree.num))
            break
        elif request[i] == 'T':
            break
        elif request[i] == 'J':
            tree.join_trees(request[i+1])
            break
        elif request[i] == 'K':
            tree.clear(tree.root)          
            break              
    tree.print_tree(tree.root, tree.root, bin)