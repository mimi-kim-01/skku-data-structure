class Graph:
    def __init__(self):
        self.graph = {}
        self.edge_cnt = 0

    def insert_vertex(self, vertex):
        self.graph[vertex] = []
    
    def add_edge(self, one, two):
        if one not in self.graph.keys() or two not in self.graph.keys():
            print("ERROR")
            return
        self.graph[one].append(two)
        self.graph[two].append(one)
        self.edge_cnt += 1
    
    def delete_edge(self, one, two):
        if one not in self.graph.keys() or two not in self.graph.keys():
            print("ERROR")
            return 
        if two not in self.graph[one] or one not in self.graph[two]:
            print('ERROR')
            return       
        self.graph[one].remove(two)
        self.graph[two].remove(one)
        self.edge_cnt -= 1        

    def degree_of_vertex(self, vertex):
        if vertex not in self.graph.keys():
            print("ERROR")
            return    
        degree = len(self.graph[vertex])
        return degree
    
    def is_connected(self):
        klist = list(self.graph.keys())
        for i in range(len(klist)):
            for j in range(1, len(klist)):
                if self.path_exists(klist[i], klist[j]) is False:
                    return False
        return True
    
    def is_empty(self):
        if len(self.graph) == 0:
            return True
        else: return False
    
    def adjacent(self, vertex):
        if vertex not in self.graph.keys():
            print("ERROR")
            return   
        if len(self.graph[vertex]) == 0:
            print("NONE")
            return
        print('[', end = '')
        for j in range(len(self.graph[vertex])):
                self.graph[vertex].sort()
                if len(self.graph[vertex]) == 1 or j == 0:
                    print(f"{self.graph[vertex][j]}", end = '')
                else: print(f",{self.graph[vertex][j]}", end = '')
        print(']')
    
    def delete_vertex(self, vertex): 
        if vertex not in self.graph.keys():
            print("ERROR")
            return     
        for i in list(self.graph.keys()):
            if vertex in self.graph[i]:
                self.graph[i].remove(vertex)
                self.edge_cnt -= 1
            if i == vertex:
                del(self.graph[vertex])
    
    def num_of_vertex(self):
        print("VERTEX NUM:", len(self.graph.keys()))
    
    def num_of_edge(self):
        print("EDGE NUM:", self.edge_cnt)
    
    def path_exists(self, one, two):
        start = one
        while self.graph[start] is not None:
            if two in self.graph[start]:
                return True
            for i in self.graph[start]:
                if two in self.graph[i]:
                    return True
                start = i
        return False
    
    def rename_vertex(self, vertex, new):
        for i in self.graph.keys():
            if vertex in self.graph[i]:
                self.graph[i].remove(vertex)
                self.graph[i].append(new)
        self.graph[new] = self.graph.pop(vertex)
    
    def clear(self):
        for i in list(self.graph.keys()):
            self.graph.pop(i)
    
    def print_graph(self):
        if self.is_empty():
            print("THE GRAPH IS EMPTY!")
            return
        cnt = 0
        for i in sorted(self.graph.keys()):
            if cnt == 0 and len(self.graph[i]) == 0: print(f"{i}", end = '')
            elif cnt == 0 : print(f"{i}(", end = '')
            elif len(self.graph[i]) == 0: 
                print(f",{i}", end = '')
            else: print(f",{i}(", end = '')
            for j in range(len(self.graph[i])):
                self.graph[i].sort()
                if len(self.graph[i]) == 1 or j == 0:
                    print(f"{self.graph[i][j]}", end = '')
                else: print(f",{self.graph[i][j]}", end = '')
            if len(self.graph[i]) != 0:
                print(")", end = '')
            cnt += 1
        print()
    
def view():
    print("---------------------MENU---------------------")
    print("INSERT VERTEX               | +(v)")
    print("DELETE VERTEX               | -(v)")
    print("RENAME VERTEX               | R(v1, v2)")
    print("ADD EDGE                    | E(v1, v2)")
    print("DELETE EDGE                 | D(v1, v2)")
    print("DEGREE OF VERTEX            | V(v)")
    print("IS CONNECTED                | C")
    print("IS EMPTY                    | N")
    print("ADJACENT                    | A(v)")
    print("PATH EXISTS                 | P(v1, v2)")
    print("NUM OF VERTEX               | X")
    print("NUM OF EDGE                 | H")
    print("CLEAR GRAPH                 | K")
    print("PRINT GRAPH                 | L")
    print("VIEW MENU                   | M")
    print("===SOME WARNINGS TO KEEP IN MIND===")
    print("* 1. No spacing between commands.")  
    print("* 2. No brackets for one vertex!") 

graph = Graph()
view()
while True:
    graph.print_graph()
    request = input(">>> ")
    if request[0] == 'Q':
        print("THIS PROGRAM ENDS SOON")
        break
    for i in range(len(request)):
        if request[i] == '+':
            graph.insert_vertex(request[i+1])
            break
        elif request[i] == '-':
            graph.delete_vertex(request[i+1])
            break
        elif request[i] == 'R':
            graph.rename_vertex(request[i+2], request[i+4])
            break
        elif request[i] == 'E':
            graph.add_edge(request[i+2], request[i+4])
            break
        elif request[i] == 'D':
            graph.delete_edge(request[i+2], request[i+4])
            break
        elif request[i] == 'V':
            print(f"DEGREE OF {request[i+1]}: {graph.degree_of_vertex(request[i+1])}")
            break
        elif request[i] == 'C':
            print(f"IS CONNECTED: {graph.is_connected()}")
            break
        elif request[i] == 'N':
            print(f"{graph.is_empty()}")
            break
        elif request[i] == 'A':
            graph.adjacent(request[i+1])
            break
        elif request[i] == 'P':
            print(f"{graph.path_exists(request[i+2], request[i+4])}")
            break
        elif request[i] == 'X':
            graph.num_of_vertex()
            break
        elif request[i] == 'H':
            graph.num_of_edge()
            break
        elif request[i] == 'K':
            graph.clear()
            break
        elif request[i] == 'L':
            break
        elif request[i] == 'M':
            view()
            break