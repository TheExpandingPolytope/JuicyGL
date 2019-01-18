
#include "Collision.h"

vector3 Shape::support(vector3 direction)
{
	return vector3();
}

vector3 Shape::center()
{
	return vector3();
}

vector3 Sphere::support(vector3 direction)
{
	return Center+direction.normalize()*radius;
}

vector3 Sphere::center()
{
	return Center;
}

bool gjk_test(Shape *a, Shape *b)
{
	vector3 d; //search direction
	Simplex s; //Simplex
	//first search direction x+ axis
	d = a->center()-b->center();
	//add first point on the minkowoski difference to the simplex
	vector3 aa = a->support(d);
	vector3 bb = b->support(d*-1);
	s.add(aa-bb);
	//set second direction to the -x axis
	d = d * -1.0;
	int inc = 0;
	while(true)
	{ 
		//add a point to simplex from minkowski difference of a and b
		s.add(a->support(d) - b->support(d*-1));

		//make sure that the last point we added to the simplex passed the origin
		if (s.getLast().dot(d) <= 0.0)
		{
			return false;
		}
		else
		{
			//if the simplex contains the origin then A and B are colliding
			if (s.contains(vec3(0, 0, 0))) {
				epa_test(s, a, b);
				return true;
			}
				
			else
			//else, find the direction from the simplex to the origin, if a 3 simplex delete the furthest point from the origin and replace it with a closer one
				d = s.directionToOrigin;
		}
		inc++;
	}
	return false;
}


contact epa_test(Simplex initialSimplex, Shape *a, Shape *b)
{
	float EXIT_THRESHHOLD = 0.01f;
	vector3 ap, bp, p, n;
	bool isOnEdge = false;
	polytope polyhedron;
	face closestFace;
	//load initial simplex from gjk algorithm
	polyhedron = initialSimplex;
	while (true) {
		//find closest face to origin
		float smllstdist = FLT_MAX;
		face smllstface;
		for (int i = 0; i < polyhedron.faces.size(); i++)
		{
			face f = polyhedron.faces[i];
			vector3 p1_p2 = f.p2 - f.p1;
			vector3 p1_p3 = f.p3 - f.p1;
			vector3 normal = p1_p2.cross(p1_p3);
			//too make sure it points outwards
			if (normal.dot(f.p1 - polyhedron.center()) < 0)
				normal = normal * -1.0f;
			float d = fabs(normal.dot(f.p1));
			if (d < smllstdist) {
				smllstdist = d;
				smllstface = f;
				n = normal;
			}
		}
		//find point on the minkowoski difference that is in the direction of closest face normal
		ap = a->support(n);
		bp = b->support(n*-1.0);
		p = ap - bp;

		//determine if the point is farther away from the origin than closestface
		if (fabs((n.dot(p)) - smllstdist) > EXIT_THRESHHOLD)
		{
			//point is farther away than triangle
			polyhedron.expand(p);
		}
		else
		{
			std::cout << "\n" <<(n.dot(p) - smllstdist);
			contact c;
			//get contact normal	
			c.normal = n * -1.0f;
			//get penetration depth
			c.penetration = smllstdist;
			std::cout <<"\n" << c.penetration;
			//get contact point
			return c;
		}

	}
	return contact();
	//if it is then expand the polytope.. if not, then current cloasestFace is the the closest face
}




void Simplex::add(vector3 point)
{
	points.push_back(point);
}

bool Simplex::contains(vector3 point)
{
	switch (points.size())
	{
	//if a 0 simplex
	case(0): {
		return false;
	} 
	
	//if a 0 simplex
	case(1): {
		//check if the only point in the simplex is equal to the origin
		if (points[0].x == 0 && points[0].y == 0 && points[0].z == 0)
			return true;
		else
			return false;
	}
		
	//if a 1 simplex
	case(2): {
		//find direction from line to origin
		vector3 ab = points[1] - points[0];
		vector3 a0 = points[0] * -1.0;
		vector3 tmp = ab.cross(a0);
		directionToOrigin = tmp.cross(ab);

		//assume that the origin does not lie on the line
		return false;
	}
	
	//if a 2 simplex
	case(3): {
		//set direction to the origin from triangle
		vector3 ac = points[2] - points[0];
		vector3 ab = points[1] - points[0];
		directionToOrigin = ac.cross(ab);

		if (directionToOrigin.dot(points[0] * -1) < 0.0) directionToOrigin = directionToOrigin * -1;
		//assume that the triangle does not have the origin in it
		return false;
	} 
	
	//if a 3 simplex
	case(4): {
		//edge values
		vector3 da = points[3] - points[0];
		vector3 db = points[3] - points[1];
		vector3 dc = points[3] - points[2];
		vector3 d0 = points[3] * -1;

		//face normal values
		vector3 abdNorm = da.cross(db);
		vector3 bcdNorm = db.cross(dc);
		vector3 cadNorm = dc.cross(da);

		if (abdNorm.dot(d0) > 0) {
			// the origin is on the outside of triangle a-b-d
			// eliminate c!
			points.erase(points.begin()+2);
			directionToOrigin = abdNorm;
			return false;
		}
		else if (bcdNorm.dot(d0) > 0) {
			// the origin is on the outside of triangle bcd
			// eliminate a!
			points.erase(points.begin()+0);
			directionToOrigin = bcdNorm;
			return false;
		}
		else if (cadNorm.dot(d0) > 0) {
			// the origin is on the outside of triangle cad
			// eliminate b!
			points.erase(points.begin() + 1);
			directionToOrigin = cadNorm;
			return false;
		}
		else {
			// the origin is inside all of the triangles!
			return true;
		}
		

	}

	}

}


vector3 Simplex::getLast()
{
	return points[points.size() - 1];
}

void polytope::expand(vector3 point)
{
	points.push_back(point);
	//find the faces to remove THIS SECTION OFFICIALLY WORKS
	std::vector<int> facesToRemove;
	for (int i = 0; i < this->faces.size(); i++)
	{
		face f = this->faces[i];
		vector3 p1_p2 = f.p2 - f.p1;
		vector3 p1_p3 = f.p3 - f.p1;
		vector3 normal = (p1_p2.cross(p1_p3)).normalize();
		if (normal.dot(f.p1 - center()) < 0)
			normal = normal * -1.0f;
		//if current face is in the direction of the expanding point
		float k = (f.p1 - point).dot(normal);
		if (k < 0)
			facesToRemove.push_back(i);
	}

	//find the points to remove and turn them all to null pointers in their corresponding faces
	for (int i = 0; i < facesToRemove.size(); i++)
	{
		//f is a face that is pointing towards the point / or a fce that can be seen by point
		face f = faces[facesToRemove[i]];
		bool p1Stays = false, p2Stays = false, p3Stays = false;
		for (int j = 0; j < faces.size(); j++)
		{
			face ff = faces[j];
			bool ffIsAFaceToStay = true;
			for (int k = 0; k < facesToRemove.size(); k++)
			{
				if (j == facesToRemove[k])
					ffIsAFaceToStay = false;
			}
			//checking if P1 on current "FACE TO REMOVE" isnt shared with a "FACE TO STAY"
			//because if it is not, then it isnt on the edges
			if (((f.p1 == ff.p1 || f.p1 == ff.p2 || f.p1 == ff.p3)) && ffIsAFaceToStay)
				p1Stays = true;
			if (((f.p2 == ff.p1 || f.p2 == ff.p2 || f.p2 == ff.p3)) && ffIsAFaceToStay)
				p2Stays = true;
			if (((f.p3 == ff.p1 || f.p3 == ff.p2 || f.p3 == ff.p3)) && ffIsAFaceToStay)
				p3Stays = true;
		}
		if (!p1Stays)
			f.p1 = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
		if (!p2Stays)
			f.p2 = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
		if (!p3Stays)
			f.p3 = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
		faces[facesToRemove[i]] = f;
	}

	//create a list of new faces that correspond to the expanded polytope
	//then remove faces that need to be removed and then add the new Faces
	std::vector<face> newFaces;
	for (int i = 0; i < facesToRemove.size(); i++)
	{
		face fToRmve = faces[facesToRemove[i]]; face f;

		f.p1 = fToRmve.p1; f.p2 = fToRmve.p2; f.p3 = point;
		if (!(f.p1 == vec3(FLT_MAX, FLT_MAX, FLT_MAX) || f.p2 == vec3(FLT_MAX, FLT_MAX, FLT_MAX) || f.p3 == vec3(FLT_MAX, FLT_MAX, FLT_MAX)))
			newFaces.push_back(f);
		f.p1 = fToRmve.p2; f.p2 = fToRmve.p3; f.p3 = point;
		if (!(f.p1 == vec3(FLT_MAX, FLT_MAX, FLT_MAX) || f.p2 == vec3(FLT_MAX, FLT_MAX, FLT_MAX) || f.p3 == vec3(FLT_MAX, FLT_MAX, FLT_MAX)))
			newFaces.push_back(f);
		f.p1 = fToRmve.p3; f.p2 = fToRmve.p1; f.p3 = point;
		if (!(f.p1 == vec3(FLT_MAX, FLT_MAX, FLT_MAX) || f.p2 == vec3(FLT_MAX, FLT_MAX, FLT_MAX) || f.p3 == vec3(FLT_MAX, FLT_MAX, FLT_MAX)))
			newFaces.push_back(f);
	}

	

	if (facesToRemove.size() != faces.size())
		for (int i = 0; i < facesToRemove.size(); i++)
		{
			faces.erase(faces.begin() + (facesToRemove[i] - i));
		}
	else
		faces.clear();

	for (int i = 0; i < newFaces.size(); i++) {
		face ii = newFaces[i];
		bool shouldAdd = true;
		for (int j = 0; j < newFaces.size(); j++)
		{
			face jj = newFaces[j];
			if (((ii.p1 == jj.p1 && ii.p2 == jj.p2) || (ii.p1 == jj.p2 && ii.p2 == jj.p1)) && i !=j)
			{
				shouldAdd = false;
			}
		}
		if (shouldAdd)
			faces.push_back(ii);
	}

}

vector3 polytope::center()
{
	vector3 sum = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < faces.size(); i++)
	{
		sum = sum + faces[i].p1;
		sum = sum + faces[i].p2;
		sum = sum + faces[i].p3;
	}
	pointInside = sum / (faces.size()*3.0f);
	return sum/(faces.size()*3.0f);
}


polytope polytope::operator=(Simplex s)
{
	//set point data
	points = s.points;
	
	//set face data
	faces.clear(); face f;
	f.p1 = points[3]; f.p2 = points[1]; f.p3 = points[2];
	faces.push_back(f);
	f.p1 = points[3]; f.p2 = points[0]; f.p3 = points[1];
	faces.push_back(f);
	f.p1 = points[3]; f.p2 = points[2]; f.p3 = points[0];
	faces.push_back(f);
	f.p1 = points[1]; f.p2 = points[0]; f.p3 = points[2];
	faces.push_back(f);
	return *this;
}
bool triangle::test_intersection(triangle operand)
{
	return false;
}

vector3 triangle::contact_point(triangle operand)
{
	return vector3();
}

vector3 triangle::dist_from(triangle operand)
{
	return vector3();
}

triangle triangle::operator+(vector3 v)
{
	triangle t;
	t.p1 = v + p1;
	t.p2 = v + p2;
	return t;
}