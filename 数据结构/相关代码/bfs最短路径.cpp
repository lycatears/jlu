
void BFS_shortest_path(vector<Vertex*>& Vertexes, int original_point, vector<int>& dist, vector<int> pre)
{
	int n = Vertexes.size();
	queue<int> vertex_queue;
	for (int i = 0; i < n; i++)
	{
		dist[i] = INF;
		pre[i] = -1;
	}
	dist[original_point] = 0;
	vertex_queue.push(original_point);

	while (!vertex_queue.empty())
	{
		int v = vertex_queue.front();
		vertex_queue.pop();
		for (Edge* p = Vertexes[v]->adjacent->link; p; p = p->link)
		{
			if (dist[p->veradj] == INF)
			{
				dist[p->veradj] = dist[v] + 1;
				pre[p->veradj] = v;
			}
			vertex_queue.push(p->veradj);
		}
	}
}