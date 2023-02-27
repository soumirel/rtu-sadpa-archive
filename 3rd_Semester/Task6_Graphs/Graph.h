#pragma once

#include <vector>
#include <string>
#include <utility>

using std::string;
using std::vector;
using std::pair;

//����� �����
class Graph
{
public:
	//�����������
	Graph();

	//����������
	~Graph();

	//������� ���������� ����� � ����
	void addEdge(int firstID, int secondID, int weight);

	//����� ����� � ���� ������ ������ � �� ������
	void print();

	//������ ������� ������� �����
	int calculateVertexDegree(int ID);

	//����� ����������� ���� ���������� ��������
	void showShortestPath(int firstID, int secondID);

private:

	//��������� ������� �����
	struct Vertex
	{
		//�������� ����������� ����� - ID ������� � ������ �������
		int ID;
		vector<pair<Vertex*, int>> neighbours;

		//���� ��� ��������� ��������:
		//	- ���������� �� ��������� �������
		//	- ��������� �� ���������� ������� � ���������� ����
		//	- ����, ������������, ���� �� ������� ��������
		double shortestWayToIt;
		Vertex* vertexCameFrom;
		bool isChecked;
		
		//�����������
		Vertex(int ID)
		{
			this->ID = ID;
			shortestWayToIt = INFINITY;
			vertexCameFrom = nullptr;
			isChecked = false;
		}
	};

	//���� - ������ ���������� �� �������
	vector<Vertex*> vertices;

	//�������� �� ������������� ������� � �����
	bool isVertexInGraph(int ID);

	//�������� �� ������������� ���� ������ � �����
	bool isVerticesConnected(int firstID, int secondID);

	//���������� ���� ������ �����
	void connectVertices(int firstID, int secondID, int weight);

	//���������� ������� � ����
	void addVertex(int ID);

	//��������� ��������� �� ������� �� �� ID
	Vertex* getVertex(int ID);
};