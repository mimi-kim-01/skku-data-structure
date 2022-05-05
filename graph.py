class Graph:
    def __init__(self):
        self.graph = {}
        self.edge_cnt = 0

    def insert_vertex(self, vertex):
        self.graph[vertex] = []
    
    def add_edge(self, one, two):
        self.graph[one].append(two)
        self.graph[two].append(one)
    
    def degree_of_vertex(self, vertex):
        degree = len(self.graph[vertex])
        return degree
    
    def is_connected(self):
        if self.edge_cnt <= len(self.graph.keys) - 1:
            return True
        else: return False
    
    def is_empty(self):
        if len(self.graph.keys) == 0:
            return True
        else: return False
    
    def adjacent(self, vertex):
        print(self.graph(vertex))
    
    def delete_vertex(self, vertex): 
        for i in self.graph.keys:
            if vertex in self.graph.keys[i]:
                self.graph.keys[i].remove(vertex)
                self.edge_cnt -= 1
            if i == vertex:
                del(self.graph[vertex])
    
    def num_of_vertex(self):
        print("VERTEX NUM:", len(self.graph.keys))
    
    def num_of_edge(self):
        print("EDGE NUM:", self.edge_cnt)
    
    def path_exists(self, one, two):
        if 