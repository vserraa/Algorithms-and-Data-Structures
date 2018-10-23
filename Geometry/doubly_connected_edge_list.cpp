#include <bits/stdc++.h>
using namespace std;

class doub_connected_edge_list{
private:
	struct vertex;
	struct half_edge;
	struct face;

	struct vertex{
		half_edge *incidentEdge;
		pair<double, double> coord;
	};
	struct half_edge{
		vertex *origin;
		half_edge *twin, *next, *prev;
		face *incidentFace;
	};
	struct face{
		half_edge *outterComp;
		vector<half_edge *> innerComp;
	};
public:
	vector<vertex> vertexs;
	vector<face> faces;
	vector<half_edge> half_edges;

	vertex *createVertex(pair<double, double> c, half_edge *e){
		vertex *v = new vertex;
		v->coord = c;
		v->incidentEdge = e;
		vertexs.push_back(*v);
		return v;
	}

	pair<half_edge *, half_edge *> createEdge(vertex *v1, vertex *v2){
		half_edge *e = v1->incidentEdge;
		half_edge *e1 = new half_edge;
		e1->prev = (e == NULL)?NULL:e;
		e1->incidentFace = (e == NULL)?NULL:e->incidentFace;
		e1->next = NULL;
		e1->origin = v1;
		if(e != NULL) e->next = e1; 
		v1->incidentEdge = e1;

		half_edge *e2 = new half_edge;
		e = v2->incidentEdge;
		e2->prev = (e == NULL)?NULL:e;
		e2->incidentFace = (e == NULL)?NULL:e->incidentFace;
		e2->next = NULL;
		e2->origin = v2;
		if(e != NULL) e->next = e2; 
		v2->incidentEdge = e2;
		
		e1->incidentFace = e2->incidentFace = NULL;
		e1->twin = e2;
		e2->twin = e1;

		half_edges.push_back(*e1);
		half_edges.push_back(*e2);
		return {e1, e2};
	}

	face *createFace(half_edge *e, vector<half_edge *> v){
		half_edge *at = e;
		face *f1 = new face;
		f1->outterComp = e;
		do{
			at->incidentFace = f1;
			at = at->next;
		}while(at != e);

		f1->innerComp = v;

		faces.push_back(*f1);
		return f1;
	}
};

int main(){
	ios::sync_with_stdio(0), cin.tie(0);


	return 0;
}