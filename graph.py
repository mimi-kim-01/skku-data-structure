class Graph:
    def __init__(self):
        self.graph = {}

    def insert_vertex(self, vertex):
        self.graph[vertex] = []
    
    def add_edge(self, one, two):
        self.graph[one].append(two)
        self.graph[two].append(one)
    
    def degree_of_vertex(self, vertex):
        degree = len(self.graph[vertex])
        return degree
    
    def is_connected(self):
        #모르겟다
    
    def is_empty(self):
        