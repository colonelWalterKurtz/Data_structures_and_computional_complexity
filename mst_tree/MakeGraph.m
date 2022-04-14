function graph = MakeGraph(vertex,maxWeight)

graph = zeros(vertex,vertex);
start = 2;
for i = 1:vertex
    for j = start:vertex
        graph(i,j) = ceil(rand*maxWeight);
    end
    graph(start:vertex,i) = graph(i,start:vertex);
    start = start + 1;
end

end

% csvwrite('macierzV.txt',MakeGraph(V,max))