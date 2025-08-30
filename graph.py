import networkx as nx
import matplotlib.pyplot as plt
import json

# Load your graph data
with open("sample.json") as f:
    data = json.load(f)

G = nx.Graph()
for edge in data["edges"]:
    G.add_edge(edge["u"], edge["v"], weight=edge["w"])

pos = nx.spring_layout(G)  # auto layout like GPS
nx.draw(G, pos, with_labels=True, node_color="lightblue", node_size=700)
labels = nx.get_edge_attributes(G, "weight")
nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)

plt.show()
 