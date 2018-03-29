/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>

#include "primitives.h"
#include "3ds.h"

long file_length(char *f)
{
    struct stat st;
    stat(f, &st);
    return st.st_size;
}

void VectDotProduct(Vertex* v1, Vertex* v2, Vertex* v3) { 
  v3->x=(v1->y * v2->z) - (v1->z * v2->y);
  v3->y=(v1->z * v2->x) - (v1->x * v2->z);
  v3->z=(v1->x * v2->y) - (v1->y * v2->x);
} 

float VectScalarProduct(Vertex* v1, Vertex* v2) { 
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z); 
} 

float VectLenght(Vertex* v)
{ return (float)(sqrt(v->x * v->x + v->y * v->y + v->z * v->z)); } 

void VectNormalize(Vertex* v)
{
    float l_lenght;

    l_lenght = VectLenght(v);
    if (l_lenght==0) l_lenght=1;
    v->x /= l_lenght;
    v->y /= l_lenght;
    v->z /= l_lenght;
} 

void VectCreate (Vertex* v1, Vertex* v2, Vertex* v3)
{
    v3->x = v2->x - v1->x;
    v3->y = v2->y - v1->y;
    v3->z = v2->z - v1->z;
    VectNormalize(v3);
} 

void ObjCalcNormals(Object* p_object)
{
	int i;
        //Some local vectors
	Vertex l_vect1, l_vect2, l_vect3, l_vect_b1, l_vect_b2, l_normal;
        //Number of poligons around each vertex
	int l_connections_qty[MAX_VERTICES]; 

    // Resetting vertices' normals...
	for (i=0; i < p_object->vCount; i++)
	{
		p_object->normals[i].x = 0.0;
		p_object->normals[i].y = 0.0;
		p_object->normals[i].z = 0.0;
		l_connections_qty[i]=0;
	}
	
	for (i=0; i < p_object->pCount; i++)
	{
        l_vect1.x = p_object->vertices[p_object->polygons[i].a].x;
        l_vect1.y = p_object->vertices[p_object->polygons[i].a].y;
        l_vect1.z = p_object->vertices[p_object->polygons[i].a].z;
        l_vect2.x = p_object->vertices[p_object->polygons[i].b].x;
        l_vect2.y = p_object->vertices[p_object->polygons[i].b].y;
        l_vect2.z = p_object->vertices[p_object->polygons[i].b].z;
        l_vect3.x = p_object->vertices[p_object->polygons[i].c].x;
        l_vect3.y = p_object->vertices[p_object->polygons[i].c].y;
        l_vect3.z = p_object->vertices[p_object->polygons[i].c].z;         
  
        // Polygon normal calculation
	VectCreate (&l_vect1, &l_vect2, &l_vect_b1); // Vector from the first vertex to the second one
        VectCreate (&l_vect1, &l_vect3, &l_vect_b2); // Vector from the first vertex to the third one
        VectDotProduct (&l_vect_b1, &l_vect_b2, &l_normal); // Dot product between the two vectors
        VectNormalize (&l_normal); //Normalizing the resultant we obtain the polygon normal

		l_connections_qty[p_object->polygons[i].a]+=1; // For each vertex shared by this polygon we increase the number of connections
		l_connections_qty[p_object->polygons[i].b]+=1;
		l_connections_qty[p_object->polygons[i].c]+=1;

		p_object->normals[p_object->polygons[i].a].x+=l_normal.x; // For each vertex shared by this polygon we add the polygon normal
		p_object->normals[p_object->polygons[i].a].y+=l_normal.y;
		p_object->normals[p_object->polygons[i].a].z+=l_normal.z;
		p_object->normals[p_object->polygons[i].b].x+=l_normal.x;
		p_object->normals[p_object->polygons[i].b].y+=l_normal.y;
		p_object->normals[p_object->polygons[i].b].z+=l_normal.z;
		p_object->normals[p_object->polygons[i].c].x+=l_normal.x;
		p_object->normals[p_object->polygons[i].c].y+=l_normal.y;
		p_object->normals[p_object->polygons[i].c].z+=l_normal.z;	
	}	
	
    for (i=0; i < p_object->vCount; i++)
	{
		if (l_connections_qty[i] > 0)
		{
			p_object->normals[i].x /= l_connections_qty[i]; // Let's now average the polygons' normals to obtain the vertex normal!
			p_object->normals[i].y /= l_connections_qty[i];
			p_object->normals[i].z /= l_connections_qty[i];
		}
	}
}

char Load3DS (Object* p_object, const char* p_filename)
{
   int i;
   FILE *l_file;
   unsigned short l_chunk_id;
   unsigned int l_chunk_length;
   unsigned char l_char;
   unsigned short l_qty;
   unsigned short l_face_flags; 

   if ((l_file=fopen (p_filename, "rb")) == NULL) return 0; //Open the file
   
   while (ftell (l_file) < file_length((char*)p_filename)) //Loop to scan the whole file 
   { 
      fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
      fread (&l_chunk_length, 4, 1, l_file); //Read the length of the chunk 

      switch (l_chunk_id)
       {
         case 0x4d4d: 
         break; 
    
         case 0x3d3d:
         break; 
         
         case 0x4000: 
            i=0;
            do
            {
               fread (&l_char, 1, 1, l_file);
               p_object->name[i]=l_char;
               i++;
            }while(l_char != '\0' && i<20);
         break;
         
         case 0x4100:
         break; 
         
         case 0x4110: 
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
            p_object->vCount = l_qty;
            //printf("Number of vertices: %d\n",l_qty);
            for (i=0; i<l_qty; i++)
            {
               fread (&p_object->vertices[i].x, sizeof(float), 1, l_file);
               fread (&p_object->vertices[i].y, sizeof(float), 1, l_file);
               fread (&p_object->vertices[i].z, sizeof(float), 1, l_file);
            }
         break; 
         
         case 0x4120:
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
            p_object->pCount = l_qty;
            //printf("Number of polygons: %d\n",l_qty); 
            for (i=0; i<l_qty; i++)
            {
               fread (&p_object->polygons[i].a, sizeof (unsigned short), 1, l_file);
               fread (&p_object->polygons[i].b, sizeof (unsigned short), 1, l_file);
               fread (&p_object->polygons[i].c, sizeof (unsigned short), 1, l_file);
               fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
            }
         break; 
         
         case 0x4140:
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
            for (i=0; i<l_qty; i++)
            {
               fread (&p_object->mapcoords[i].u, sizeof (float), 1, l_file);
               fread (&p_object->mapcoords[i].v, sizeof (float), 1, l_file);
            }
         break; 
         
         default:
            fseek(l_file, l_chunk_length-6, SEEK_CUR);
      } 
   } 
   
   fclose (l_file); // Closes the file stream
   ObjCalcNormals(p_object);
   return (1); // Returns ok
} 
/*
struct XYZ
 { float x,y,z;
 };
 
void CreateSphere(XYZ c,double r,int n)
{
   int i,j;
   double theta1,theta2,theta3;
   XYZ e,p;

   if (r < 0)
      r = -r;
   if (n < 0)
      n = -n;
   if (n < 4 || r <= 0) {
      glBegin(GL_POINTS);
      glVertex3f(c.x,c.y,c.z);
      glEnd();
      return;
   }

   for (j=0;j<n/2;j++) {
      theta1 = j * TWOPI / n - PID2;
      theta2 = (j + 1) * TWOPI / n - PID2;

      glBegin(GL_QUAD_STRIP);
      for (i=0;i<=n;i++) {
         theta3 = i * TWOPI / n;

         e.x = cos(theta2) * cos(theta3);
         e.y = sin(theta2);
         e.z = cos(theta2) * sin(theta3);
         p.x = c.x + r * e.x;
         p.y = c.y + r * e.y;
         p.z = c.z + r * e.z;

         glNormal3f(e.x,e.y,e.z);
         glTexCoord2f(i/(double)n,2*(j+1)/(double)n);
         glVertex3f(p.x,p.y,p.z);

         e.x = cos(theta1) * cos(theta3);
         e.y = sin(theta1);
         e.z = cos(theta1) * sin(theta3);
         p.x = c.x + r * e.x;
         p.y = c.y + r * e.y;
         p.z = c.z + r * e.z;

         glNormal3f(e.x,e.y,e.z);
         glTexCoord2f(i/(double)n,2*j/(double)n);
         glVertex3f(p.x,p.y,p.z);
      }
      glEnd();
   }
}*/

